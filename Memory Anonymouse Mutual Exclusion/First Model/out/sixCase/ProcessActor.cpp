                                    

#include "Types.h"
#include "ProcessActor.h"
#include <stdio.h>
#include <string.h>
#include <limits>

#include "MemoryActor.h"

// location counters (values stored in messageQueue[0])
/* There can be more than one location counter for each msgsrv when we
   want to have non-atomic message servers.
   Notice that values 0 and 1 are reserved for EMPTY and INITIAL, respectively.*/
#define INIT 1
#define GET 2
#define CRIT 3
#define STARTER 4


// knownrebecs (those to whom message can be sent)
// the following format allows to use them as variables --> the ID of the rebec
#define _ref_sender (rebecs[senderQueue[0]])
#define _ref_self (dynamic_cast<ProcessActor*>(rebecs[myID]))
        	#define _ref_m (dynamic_cast<MemoryActor*>(rebecs[known[1]]))
	            

ProcessActor::ProcessActor(byte myID, char* myName, int maxQueueLength, int maxParamLength, vector<AbstractActor*>& rebecsRef
		#ifdef DEBUG_LEVEL_2 
			, ostream &out
		#endif
				






					,int stateSize, int hashmapSize
		)
	:
			AbstractActor (myID, myName, maxQueueLength, maxParamLength, rebecsRef
			#ifdef DEBUG_LEVEL_2 
				, out
			#endif
						






					, stateSize, hashmapSize
				)
				{
        messageNames = new char *[4 + 1];
    messagePriorities = new int[4 + 1];
	messageNames[0] = (char*)"Empty";

		
			
			
			
						       		 messageNames[1] = (char*)"INIT";
       		 	    					messagePriorities[1] = std::numeric_limits<int>::max();
			  	 	       		 messageNames[2] = (char*)"GET";
       		 	    					messagePriorities[2] = std::numeric_limits<int>::max();
			  	 	       		 messageNames[3] = (char*)"CRIT";
       		 	    					messagePriorities[3] = std::numeric_limits<int>::max();
			  	 	       		 messageNames[4] = (char*)"STARTER";
       		 	    					messagePriorities[4] = std::numeric_limits<int>::max();
			  	 		
				






			if (table == (byte**)0xFFFFFFFF) {	// avoid reinitialization
		table = new byte* [1 << hashmapSize];
        memset (table, 0, sizeof(byte*)*(1 << hashmapSize));
	}

		
	queueTail = 0;
}

ProcessActor::~ProcessActor (){
	delete [] messageNames;
	delete [] messageQueue;
	delete [] senderQueue;
}


void ProcessActor::exportAMessageInXML(ostream &out, string tab, int cnt) {
        int i = 0;
        switch (messageQueue[cnt]) {
	                    case INIT: {
                            
                        	int _ref_round;
                        
                                    
            	                            	memcpy(&_ref_round, &paramQueue[cnt] [i], (1 * INT_SIZE));
	                i += (1 * INT_SIZE);
	                                                
                    out << "init("
                                	<< ((int)_ref_round)
                	                                << ")";
                break;
               }
	                    case GET: {
                            
                        	byte _ref_v;
                        
                                    
            	                            	memcpy(&_ref_v, &paramQueue[cnt] [i], (1 * BYTE_SIZE));
	                i += (1 * BYTE_SIZE);
	                                
                        	int _ref_l;
                        
                                    
            	                            	memcpy(&_ref_l, &paramQueue[cnt] [i], (1 * INT_SIZE));
	                i += (1 * INT_SIZE);
	                                                
                    out << "get("
                                	<< ((int)_ref_v)
                						<< ", "
					                                	<< ((int)_ref_l)
                	                                << ")";
                break;
               }
	                    case CRIT: {
                                            
                    out << "crit("
                                << ")";
                break;
               }
	                    case STARTER: {
                                            
                    out << "starter("
                                << ")";
                break;
               }
	                	    	}
}


void ProcessActor::exportStateVariablesInXML(ostream &out, string tab) {
	out << tab << "<statevariables>" << endl;
	exportInsideStateVariablesTagInXML(out, tab);
	out << tab << "</statevariables>" << endl;
}

void ProcessActor::exportInsideStateVariablesTagInXML(ostream &out, string tab){

	
	        	        			    	out << tab << '\t' << "<variable name=\"Process.uid\" type=\"byte\">" <<  
			    		((int)_ref_uid) << "</variable>" << endl;
    					        	        			    	out << tab << '\t' << "<variable name=\"Process.mem\" type=\"byte[5]\">" <<  
			    		"[" << ((int)_ref_mem[0]) << ", " << ((int)_ref_mem[1]) << ", " << ((int)_ref_mem[2]) << ", " << ((int)_ref_mem[3]) << ", " << ((int)_ref_mem[4]) << ", " << "]" << "</variable>" << endl;
    					        	        			    	out << tab << '\t' << "<variable name=\"Process.add\" type=\"byte[5]\">" <<  
			    		"[" << ((int)_ref_add[0]) << ", " << ((int)_ref_add[1]) << ", " << ((int)_ref_add[2]) << ", " << ((int)_ref_add[3]) << ", " << ((int)_ref_add[4]) << ", " << "]" << "</variable>" << endl;
    					        	        			    	out << tab << '\t' << "<variable name=\"Process.winner\" type=\"boolean\">" <<  
			    		(_ref_winner? "true" : "false") << "</variable>" << endl;
    					}


char* ProcessActor::getClassName() {
    return (char*)"Process";
}
void ProcessActor::marshalVariablesToArray(byte * array){
	int marshalIndex = 0;
            	
                    
                                    	                            	memcpy(&array [marshalIndex], &_ref_uid, (1 * BYTE_SIZE));
	                marshalIndex += (1 * BYTE_SIZE);
	                                            
                                    	            																											memcpy(&array [marshalIndex], _ref_mem.data(), (1 * BYTE_SIZE) * 5);					
					marshalIndex += (1 * BYTE_SIZE) * 5;
																	                                            
                                    	            																											memcpy(&array [marshalIndex], _ref_add.data(), (1 * BYTE_SIZE) * 5);					
					marshalIndex += (1 * BYTE_SIZE) * 5;
																	                                            
                                                	            					            	                                    
        array [marshalIndex] = 0;
array [marshalIndex] |= (_ref_winner ? 0xFF : 0x00) & AbstractActor::coeff[0]; 
++marshalIndex;
        
		
}
void ProcessActor::marshalActorToArray(byte* array) {
    int i,j, marshalIndex = 0;

	for (i = (shift ? 1 : 0); i < maxQueueLength; i++) {
        array[marshalIndex++] = messageQueue[i];
    }

    if (shift) {
        array[marshalIndex++] = 0;
    }
    
	for (i = (shift ? 1 : 0); i < maxQueueLength; i++) {
        array[marshalIndex++] = senderQueue[i];
    }

    if (shift) {
        array[marshalIndex++] = 0;
    }

	if(maxParamLength != 0) {
        for (i = (shift ? 1 : 0); i < maxQueueLength; i++) {
            for (j = 0; j < maxParamLength; j++) {
                array[marshalIndex++] = paramQueue[i][j];
            }
        }
        if (shift) {
            for (j = 0; j < maxParamLength; j++) {
                array[marshalIndex++] = 0;
            }
        }
    }

	 #ifdef NO_ATOMIC_EXECUTION
    	memcpy(&array [marshalIndex], &__pc, 4);
    	marshalIndex += 4;
    	//array[marshalIndex++] = __pc;
    #endif

		marshalVariablesToArray( & array[marshalIndex]);

   

}

void ProcessActor::unmarshalActorFromArray(byte* array) {

    int index = 0, i, j;
    shift = 0;

	for (i = 0; i < maxQueueLength; i++) {
        messageQueue[i] = array[index++];
    }
	
	for (i = 0; i < maxQueueLength; i++) {
        senderQueue[i] = array[index++];
    }
    
	if(maxParamLength != 0) {
        for (i = 0; i < maxQueueLength; i++) {
            for (j = 0; j < maxParamLength; j++) {
                paramQueue[i][j] = array[index++];
            }
        }
    }
    
	#ifdef NO_ATOMIC_EXECUTION
    	memcpy(&__pc, &array [index], 4);
    	index += 4;
    	//__pc = array[index++];
    #endif
    
	unmarshalVariablesFromArray( & array[index]);
}

void ProcessActor::unmarshalVariablesFromArray(byte * array){

	int index = 0;
                
                        
                                    
            	                            	memcpy(&_ref_uid, &array [index], (1 * BYTE_SIZE));
	                index += (1 * BYTE_SIZE);
	                                
                        
                                    
            	            																											memcpy(_ref_mem.data(), &array [index], (1 * BYTE_SIZE) * 5);					
					index += (1 * BYTE_SIZE) * 5;
																	                                
                        
                                    
            	            																											memcpy(_ref_add.data(), &array [index], (1 * BYTE_SIZE) * 5);					
					index += (1 * BYTE_SIZE) * 5;
																	                                
                        
                                    
                        	            			            	                                            _ref_winner = (bool) (array [index] & AbstractActor::coeff[0]);
++index;
        
		
}

/*#ifdef DEBUG
void ProcessActor::printStateContent(long stateNo) {
	out << myName << "=>[";
	byte* currentValues = getTable()[stateNo];
	for (int cnt = 0; cnt < STATE_SIZE; cnt++)
		out << (int)currentValues[cnt] << ", ";
	out << "]";
}
#endif
*/

//---------------------------------------------------------
/**
  Checks which action of this rebec is enabled, and executes it. Actions are the
  same as the location-counter defined at the beginning of this file.
  In the case of non-atomic message servers, a location-counter may point to the
  middle of a message server.
  If this action leads to more than one transition (non_det), this method executes
  only one of these transitions. With the help of some static variables, consecutive
  calls to this method execute different transitions caused by this action.
  Local variables must be properly valuated before any call to this method (see marshal()).

  returns: >0 : there are more possible next states (non-det transitions).
		   =0 : no more non_det transitions
		   -1 : no enabled action (empty queue)
		   -2 : Local hash table is full - immediate termination of search
 */
long ProcessActor::methodSelectorAndExecutor() {

	
    switch (messageQueue[0]) {

                    case INIT:
                {
                    int i = 0;
                                
                        	int _ref_round;
                        
                                    
            	                            	memcpy(&_ref_round, &paramQueue[0] [i], (1 * INT_SIZE));
	                i += (1 * INT_SIZE);
	                                                
                        return msgsrvinit(
                            	                        _ref_round
	                                        );
                }
                    case GET:
                {
                    int i = 0;
                                
                        	byte _ref_v;
                        
                                    
            	                            	memcpy(&_ref_v, &paramQueue[0] [i], (1 * BYTE_SIZE));
	                i += (1 * BYTE_SIZE);
	                                
                        	int _ref_l;
                        
                                    
            	                            	memcpy(&_ref_l, &paramQueue[0] [i], (1 * INT_SIZE));
	                i += (1 * INT_SIZE);
	                                                
                        return msgsrvget(
                            	                        _ref_v
	        	        , 
	                            _ref_l
	                                        );
                }
                    case CRIT:
                {
                    int i = 0;
                                                
                        return msgsrvcrit(
                                                );
                }
                    case STARTER:
                {
                    int i = 0;
                                                
                        return msgsrvstarter(
                                                );
                }
            }
    	return -1;
	}


    long ProcessActor::constructorProcess (byte creatorId 
    			    	        ,
	    	        		byte
	         _ref_u
	        	        , 
	        	        		byte
	         _ref_a
	        	        , 
	        	        		byte
	         _ref_b
	        	        , 
	        	        		byte
	         _ref_c
	        	        , 
	        	        		byte
	         _ref_d
	        	        , 
	        	        		byte
	         _ref_e
	        	            ) {
    			shift = 1;
		#ifdef SAFE_MODE
			string reactiveClassName = this->getName();
			string methodName = "Process";
		#endif

		{
			(_ref_uid=_ref_u);
			for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
				{
					(_ref_mem[_ref_i]=0);
				}
}
			(_ref_add[0]=_ref_a);
			(_ref_add[1]=_ref_b);
			(_ref_add[2]=_ref_c);
			(_ref_add[3]=_ref_d);
			(_ref_add[4]=_ref_e);
			(_ref_winner=false);
			_ref_self->_msg_init(myID, 0);
		}
		shift = 0;
		return 0;

	}

 
			byte ProcessActor::_synchmethod_owned (
    		   		 ) {
    			shift = 1;
		#ifdef SAFE_MODE
			string reactiveClassName = this->getName();
			string methodName = "owned";
		#endif

		{
			byte _ref_owner = 0;

			for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
				{
					if ((_ref_mem[_ref_i]==_ref_uid)) {
						{
							(_ref_owner++);
						}
}
				}
}
			return _ref_owner;

		}

		}
	 
			byte ProcessActor::_synchmethod_findMostPresent (
    		   		 ) {
    			shift = 1;
		#ifdef SAFE_MODE
			string reactiveClassName = this->getName();
			string methodName = "findMostPresent";
		#endif

		{
			std::array<byte, 5> _ref_temp;

			byte _ref_mostPresent = 0;

			for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
				{
					(_ref_temp[_ref_i]=0);
				}
}
			for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
				{
					for (byte _ref_j = 0;
((_ref_j<5)); (_ref_j++)) {
						{
							if ((_ref_mem[_ref_i]==_ref_mem[_ref_j])) {
								{
									(_ref_temp[_ref_i]++);
								}
}
						}
}
				}
}
			(_ref_mostPresent=_ref_temp[0]);
			for (byte _ref_i = 1;
((_ref_i<5)); (_ref_i++)) {
				{
					if ((_ref_mostPresent<_ref_temp[_ref_i])) {
						{
							(_ref_mostPresent=_ref_temp[_ref_i]);
						}
}
				}
}
			return _ref_mostPresent;

		}

		}
	

 			void ProcessActor::_msg_init (byte senderId
        		    	        ,
	    	        		int
	         _ref_round
	        	          	  ){
        queueTail = 0;
        enqueue(messageQueue, INIT);
        enqueue(senderQueue, senderId);
        
        if (maxParamLength != 0) {
            int index = 0;
            byte paramsValues[maxParamLength];
            memset(paramsValues, 0, maxParamLength);
                    	
                    
                                    	                            	memcpy(&paramsValues [index], &_ref_round, (1 * INT_SIZE));
	                index += (1 * INT_SIZE);
	                                        
        
                enqueue(paramQueue, paramsValues, maxParamLength);
        }
}
	
 			void ProcessActor::_msg_get (byte senderId
        		    	        ,
	    	        		byte
	         _ref_v
	        	        , 
	        	        		int
	         _ref_l
	        	          	  ){
        queueTail = 0;
        enqueue(messageQueue, GET);
        enqueue(senderQueue, senderId);
        
        if (maxParamLength != 0) {
            int index = 0;
            byte paramsValues[maxParamLength];
            memset(paramsValues, 0, maxParamLength);
                    	
                    
                                    	                            	memcpy(&paramsValues [index], &_ref_v, (1 * BYTE_SIZE));
	                index += (1 * BYTE_SIZE);
	                                            
                                    	                            	memcpy(&paramsValues [index], &_ref_l, (1 * INT_SIZE));
	                index += (1 * INT_SIZE);
	                                        
        
                enqueue(paramQueue, paramsValues, maxParamLength);
        }
}
	
 			void ProcessActor::_msg_crit (byte senderId
        	  	  ){
        queueTail = 0;
        enqueue(messageQueue, CRIT);
        enqueue(senderQueue, senderId);
        
        if (maxParamLength != 0) {
            int index = 0;
            byte paramsValues[maxParamLength];
            memset(paramsValues, 0, maxParamLength);
                    	
                
        
                enqueue(paramQueue, paramsValues, maxParamLength);
        }
}
	
 			void ProcessActor::_msg_starter (byte senderId
        	  	  ){
        queueTail = 0;
        enqueue(messageQueue, STARTER);
        enqueue(senderQueue, senderId);
        
        if (maxParamLength != 0) {
            int index = 0;
            byte paramsValues[maxParamLength];
            memset(paramsValues, 0, maxParamLength);
                    	
                
        
                enqueue(paramQueue, paramsValues, maxParamLength);
        }
}
	
			






		
	byte** ProcessActor::table = (byte**)0xFFFFFFFF;

	byte** ProcessActor::getTable() {
		return table;
	}
	
		    long ProcessActor::msgsrvinit (
    			    	        		int
	         _ref_round
	        	            ) {
    			shift = 1;
		#ifdef SAFE_MODE
			string reactiveClassName = this->getName();
			string methodName = "init";
		#endif

		{
			_ref_m->_msg_receive(myID, _ref_uid, _ref_round);
		}
		return 0;

}
				    long ProcessActor::msgsrvget (
    			    	        		byte
	         _ref_v
	        	        , 
	        	        		int
	         _ref_l
	        	            ) {
    			shift = 1;
		#ifdef SAFE_MODE
			string reactiveClassName = this->getName();
			string methodName = "get";
		#endif

		{
			(_ref_mem[(_ref_add[_ref_l]-1)]=_ref_v);
			if ((_ref_l!=4)) {
				{
					_ref_m->_msg_receive(myID, _ref_uid, (_ref_l+1));
				}
}
			else {
				{
					byte _ref_owner = _synchmethod_owned();

					if ((_ref_owner<_synchmethod_findMostPresent())) {
						{
							_ref_m->_msg_result(myID, false, true, _ref_uid);
						}
}
					else {
						{
							if ((_ref_owner==5)) {
								{
									(_ref_winner=true);
									_ref_self->_msg_crit(myID);
								}
}
							else {
								{
									_ref_m->_msg_result(myID, false, false, _ref_uid);
								}
}
						}
}
				}
}
		}
		return 0;

}
				    long ProcessActor::msgsrvcrit (
    		    ) {
    			shift = 1;
		#ifdef SAFE_MODE
			string reactiveClassName = this->getName();
			string methodName = "crit";
		#endif

		{
			(_ref_winner=false);
			_ref_m->_msg_result(myID, true, false, _ref_uid);
		}
		return 0;

}
				    long ProcessActor::msgsrvstarter (
    		    ) {
    			shift = 1;
		#ifdef SAFE_MODE
			string reactiveClassName = this->getName();
			string methodName = "starter";
		#endif

		{
			for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
				{
					(_ref_mem[_ref_i]=0);
				}
}
			_ref_m->_msg_receive(myID, _ref_uid, 0);
		}
		return 0;

}
		