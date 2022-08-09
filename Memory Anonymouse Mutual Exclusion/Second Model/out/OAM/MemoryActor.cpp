                                    

#include "Types.h"
#include "MemoryActor.h"
#include <stdio.h>
#include <string.h>
#include <limits>

#include "ProcessActor.h"

// location counters (values stored in messageQueue[0])
/* There can be more than one location counter for each msgsrv when we
   want to have non-atomic message servers.
   Notice that values 0 and 1 are reserved for EMPTY and INITIAL, respectively.*/
#define RECEIVE 1
#define RESULT 2


// knownrebecs (those to whom message can be sent)
// the following format allows to use them as variables --> the ID of the rebec
#define _ref_sender (rebecs[senderQueue[0]])
#define _ref_self (dynamic_cast<MemoryActor*>(rebecs[myID]))
        	#define _ref_p1 (dynamic_cast<ProcessActor*>(rebecs[known[1]]))
	                	#define _ref_p2 (dynamic_cast<ProcessActor*>(rebecs[known[2]]))
	                	#define _ref_p3 (dynamic_cast<ProcessActor*>(rebecs[known[3]]))
	            

MemoryActor::MemoryActor(byte myID, char* myName, int maxQueueLength, int maxParamLength, vector<AbstractActor*>& rebecsRef
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
        messageNames = new char *[2 + 1];
    messagePriorities = new int[2 + 1];
	messageNames[0] = (char*)"Empty";

		
			
			
			
						       		 messageNames[1] = (char*)"RECEIVE";
       		 	    					messagePriorities[1] = std::numeric_limits<int>::max();
			  	 	       		 messageNames[2] = (char*)"RESULT";
       		 	    					messagePriorities[2] = std::numeric_limits<int>::max();
			  	 		
				






			if (table == (byte**)0xFFFFFFFF) {	// avoid reinitialization
		table = new byte* [1 << hashmapSize];
        memset (table, 0, sizeof(byte*)*(1 << hashmapSize));
	}

		
	queueTail = 0;
}

MemoryActor::~MemoryActor (){
	delete [] messageNames;
	delete [] messageQueue;
	delete [] senderQueue;
}


void MemoryActor::exportAMessageInXML(ostream &out, string tab, int cnt) {
        int i = 0;
        switch (messageQueue[cnt]) {
	                    case RECEIVE: {
                            
                        	byte _ref_u;
                        
                                    
            	                            	memcpy(&_ref_u, &paramQueue[cnt] [i], (1 * BYTE_SIZE));
	                i += (1 * BYTE_SIZE);
	                                
                        	int _ref_l;
                        
                                    
            	                            	memcpy(&_ref_l, &paramQueue[cnt] [i], (1 * INT_SIZE));
	                i += (1 * INT_SIZE);
	                                                
                    out << "receive("
                                	<< ((int)_ref_u)
                						<< ", "
					                                	<< ((int)_ref_l)
                	                                << ")";
                break;
               }
	                    case RESULT: {
                            
                        	boolean _ref_w;
                        
                                    
                        	            			            	                    
                        	boolean _ref_l;
                        
                                    
                        	            			            	                    
                        	byte _ref_u;
                        
                                    
            	                            	memcpy(&_ref_u, &paramQueue[cnt] [i], (1 * BYTE_SIZE));
	                i += (1 * BYTE_SIZE);
	                                                        _ref_w = (bool) (paramQueue[cnt] [i] & AbstractActor::coeff[0]);
_ref_l = (bool) (paramQueue[cnt] [i] & AbstractActor::coeff[1]);
++i;
                    out << "result("
                                	<< (_ref_w? "true" : "false")
                						<< ", "
					                                	<< (_ref_l? "true" : "false")
                						<< ", "
					                                	<< ((int)_ref_u)
                	                                << ")";
                break;
               }
	                	    	}
}


void MemoryActor::exportStateVariablesInXML(ostream &out, string tab) {
	out << tab << "<statevariables>" << endl;
	exportInsideStateVariablesTagInXML(out, tab);
	out << tab << "</statevariables>" << endl;
}

void MemoryActor::exportInsideStateVariablesTagInXML(ostream &out, string tab){

	
	        	        			    	out << tab << '\t' << "<variable name=\"Memory.reg\" type=\"byte[5]\">" <<  
			    		"[" << ((int)_ref_reg[0]) << ", " << ((int)_ref_reg[1]) << ", " << ((int)_ref_reg[2]) << ", " << ((int)_ref_reg[3]) << ", " << ((int)_ref_reg[4]) << ", " << "]" << "</variable>" << endl;
    					        	        			    	out << tab << '\t' << "<variable name=\"Memory.swap\" type=\"byte[5]\">" <<  
			    		"[" << ((int)_ref_swap[0]) << ", " << ((int)_ref_swap[1]) << ", " << ((int)_ref_swap[2]) << ", " << ((int)_ref_swap[3]) << ", " << ((int)_ref_swap[4]) << ", " << "]" << "</variable>" << endl;
    					        	        			    	out << tab << '\t' << "<variable name=\"Memory.p\" type=\"byte[3]\">" <<  
			    		"[" << ((int)_ref_p[0]) << ", " << ((int)_ref_p[1]) << ", " << ((int)_ref_p[2]) << ", " << "]" << "</variable>" << endl;
    					        	        			    	out << tab << '\t' << "<variable name=\"Memory.cntr\" type=\"byte\">" <<  
			    		((int)_ref_cntr) << "</variable>" << endl;
    					        	        			    	out << tab << '\t' << "<variable name=\"Memory.cv\" type=\"byte\">" <<  
			    		((int)_ref_cv) << "</variable>" << endl;
    					}


char* MemoryActor::getClassName() {
    return (char*)"Memory";
}
void MemoryActor::marshalVariablesToArray(byte * array){
	int marshalIndex = 0;
            	
                    
                                    	            																											memcpy(&array [marshalIndex], _ref_reg.data(), (1 * BYTE_SIZE) * 5);					
					marshalIndex += (1 * BYTE_SIZE) * 5;
																	                                            
                                    	            																											memcpy(&array [marshalIndex], _ref_swap.data(), (1 * BYTE_SIZE) * 5);					
					marshalIndex += (1 * BYTE_SIZE) * 5;
																	                                            
                                    	            																											memcpy(&array [marshalIndex], _ref_p.data(), (1 * BYTE_SIZE) * 3);					
					marshalIndex += (1 * BYTE_SIZE) * 3;
																	                                            
                                    	                            	memcpy(&array [marshalIndex], &_ref_cntr, (1 * BYTE_SIZE));
	                marshalIndex += (1 * BYTE_SIZE);
	                                            
                                    	                            	memcpy(&array [marshalIndex], &_ref_cv, (1 * BYTE_SIZE));
	                marshalIndex += (1 * BYTE_SIZE);
	                                        
        
        
		
}
void MemoryActor::marshalActorToArray(byte* array) {
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

void MemoryActor::unmarshalActorFromArray(byte* array) {

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

void MemoryActor::unmarshalVariablesFromArray(byte * array){

	int index = 0;
                
                        
                                    
            	            																											memcpy(_ref_reg.data(), &array [index], (1 * BYTE_SIZE) * 5);					
					index += (1 * BYTE_SIZE) * 5;
																	                                
                        
                                    
            	            																											memcpy(_ref_swap.data(), &array [index], (1 * BYTE_SIZE) * 5);					
					index += (1 * BYTE_SIZE) * 5;
																	                                
                        
                                    
            	            																											memcpy(_ref_p.data(), &array [index], (1 * BYTE_SIZE) * 3);					
					index += (1 * BYTE_SIZE) * 3;
																	                                
                        
                                    
            	                            	memcpy(&_ref_cntr, &array [index], (1 * BYTE_SIZE));
	                index += (1 * BYTE_SIZE);
	                                
                        
                                    
            	                            	memcpy(&_ref_cv, &array [index], (1 * BYTE_SIZE));
	                index += (1 * BYTE_SIZE);
	                                                
        
		
}

/*#ifdef DEBUG
void MemoryActor::printStateContent(long stateNo) {
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
long MemoryActor::methodSelectorAndExecutor() {

	
    switch (messageQueue[0]) {

                    case RECEIVE:
                {
                    int i = 0;
                                
                        	byte _ref_u;
                        
                                    
            	                            	memcpy(&_ref_u, &paramQueue[0] [i], (1 * BYTE_SIZE));
	                i += (1 * BYTE_SIZE);
	                                
                        	int _ref_l;
                        
                                    
            	                            	memcpy(&_ref_l, &paramQueue[0] [i], (1 * INT_SIZE));
	                i += (1 * INT_SIZE);
	                                                
                        return msgsrvreceive(
                            	                        _ref_u
	        	        , 
	                            _ref_l
	                                        );
                }
                    case RESULT:
                {
                    int i = 0;
                                
                        	boolean _ref_w;
                        
                                    
                        	            			            	                    
                        	boolean _ref_l;
                        
                                    
                        	            			            	                    
                        	byte _ref_u;
                        
                                    
            	                            	memcpy(&_ref_u, &paramQueue[0] [i], (1 * BYTE_SIZE));
	                i += (1 * BYTE_SIZE);
	                                                        _ref_w = (bool) (paramQueue[0] [i] & AbstractActor::coeff[0]);
_ref_l = (bool) (paramQueue[0] [i] & AbstractActor::coeff[1]);
++i;
                        return msgsrvresult(
                            	                        _ref_w
	        	        , 
	                            _ref_l
	        	        , 
	                            _ref_u
	                                        );
                }
            }
    	return -1;
	}


    long MemoryActor::constructorMemory (byte creatorId 
    		    ) {
    			shift = 1;
		#ifdef SAFE_MODE
			string reactiveClassName = this->getName();
			string methodName = "Memory";
		#endif

		{
			for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
				{
					(_ref_reg[_ref_i]=0);
				}
}
			for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
				{
					(_ref_reg[_ref_i]=0);
				}
}
			for (byte _ref_i = 0;
((_ref_i<3)); (_ref_i++)) {
				{
					(_ref_p[_ref_i]=0);
				}
}
			(_ref_cntr=3);
			(_ref_cv=3);
		}
		shift = 0;
		return 0;

	}



 			void MemoryActor::_msg_receive (byte senderId
        		    	        ,
	    	        		byte
	         _ref_u
	        	        , 
	        	        		int
	         _ref_l
	        	          	  ){
        queueTail = 0;
        enqueue(messageQueue, RECEIVE);
        enqueue(senderQueue, senderId);
        
        if (maxParamLength != 0) {
            int index = 0;
            byte paramsValues[maxParamLength];
            memset(paramsValues, 0, maxParamLength);
                    	
                    
                                    	                            	memcpy(&paramsValues [index], &_ref_u, (1 * BYTE_SIZE));
	                index += (1 * BYTE_SIZE);
	                                            
                                    	                            	memcpy(&paramsValues [index], &_ref_l, (1 * INT_SIZE));
	                index += (1 * INT_SIZE);
	                                        
        
                enqueue(paramQueue, paramsValues, maxParamLength);
        }
}
	
 			void MemoryActor::_msg_result (byte senderId
        		    	        ,
	    	        		boolean
	         _ref_w
	        	        , 
	        	        		boolean
	         _ref_l
	        	        , 
	        	        		byte
	         _ref_u
	        	          	  ){
        queueTail = 0;
        enqueue(messageQueue, RESULT);
        enqueue(senderQueue, senderId);
        
        if (maxParamLength != 0) {
            int index = 0;
            byte paramsValues[maxParamLength];
            memset(paramsValues, 0, maxParamLength);
                    	
                    
                                                	            					            	                                
                                                	            				            	                                
                                    	                            	memcpy(&paramsValues [index], &_ref_u, (1 * BYTE_SIZE));
	                index += (1 * BYTE_SIZE);
	                                                
        paramsValues [index] = 0;
paramsValues [index] |= (_ref_w ? 0xFF : 0x00) & AbstractActor::coeff[0]; 
paramsValues [index] |= (_ref_l ? 0xFF : 0x00) & AbstractActor::coeff[1]; 
++index;
                enqueue(paramQueue, paramsValues, maxParamLength);
        }
}
	
			






		
	byte** MemoryActor::table = (byte**)0xFFFFFFFF;

	byte** MemoryActor::getTable() {
		return table;
	}
	
		    long MemoryActor::msgsrvreceive (
    			    	        		byte
	         _ref_u
	        	        , 
	        	        		int
	         _ref_l
	        	            ) {
    			shift = 1;
		#ifdef SAFE_MODE
			string reactiveClassName = this->getName();
			string methodName = "receive";
		#endif

		{
			if ((_ref_reg[_ref_l]==0)) {
				{
					(_ref_reg[_ref_l]=_ref_u);
				}
}
			(_ref_cntr--);
			if ((_ref_cntr==0)) {
				{
					(_ref_cntr=_ref_cv);
					if ((_ref_p[0]!=1)) {
						{
							_ref_p1->_msg_get(myID, _ref_reg[_ref_l], _ref_l);
						}
}
					if ((_ref_p[1]!=1)) {
						{
							_ref_p2->_msg_get(myID, _ref_reg[_ref_l], _ref_l);
						}
}
					if ((_ref_p[2]!=1)) {
						{
							_ref_p3->_msg_get(myID, _ref_reg[_ref_l], _ref_l);
						}
}
				}
}
		}
		return 0;

}
				    long MemoryActor::msgsrvresult (
    			    	        		boolean
	         _ref_w
	        	        , 
	        	        		boolean
	         _ref_l
	        	        , 
	        	        		byte
	         _ref_u
	        	            ) {
    			shift = 1;
		#ifdef SAFE_MODE
			string reactiveClassName = this->getName();
			string methodName = "result";
		#endif

		{
			if ((_ref_sender==_ref_p1)) {
				{
					if ((_ref_w==true)) {
						{
							(_ref_p[0]=3);
						}
}
					if ((_ref_l==true)) {
						{
							(_ref_p[0]=1);
							for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
								{
									if ((_ref_reg[_ref_i]==_ref_u)) {
										{
											(_ref_reg[_ref_i]=0);
											(_ref_swap[_ref_i]=_ref_u);
										}
}
								}
}
						}
}
					if (((_ref_w==false)&&(_ref_l==false))) {
						{
							(_ref_p[0]=2);
						}
}
				}
}
			if ((_ref_sender==_ref_p2)) {
				{
					if ((_ref_w==true)) {
						{
							(_ref_p[1]=3);
						}
}
					if ((_ref_l==true)) {
						{
							(_ref_p[1]=1);
							for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
								{
									if ((_ref_reg[_ref_i]==_ref_u)) {
										{
											(_ref_reg[_ref_i]=0);
											(_ref_swap[_ref_i]=_ref_u);
										}
}
								}
}
						}
}
					if (((_ref_w==false)&&(_ref_l==false))) {
						{
							(_ref_p[1]=2);
						}
}
				}
}
			if ((_ref_sender==_ref_p3)) {
				{
					if ((_ref_w==true)) {
						{
							(_ref_p[2]=3);
						}
}
					if ((_ref_l==true)) {
						{
							(_ref_p[2]=1);
							for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
								{
									if ((_ref_reg[_ref_i]==_ref_u)) {
										{
											(_ref_reg[_ref_i]=0);
											(_ref_swap[_ref_i]=_ref_u);
										}
}
								}
}
						}
}
					if (((_ref_w==false)&&(_ref_l==false))) {
						{
							(_ref_p[2]=2);
						}
}
				}
}
			if ((((_ref_p[0]!=0)&&(_ref_p[1]!=0))&&(_ref_p[2]!=0))) {
				{
					(_ref_cv=0);
					if ((((_ref_p[0]==3)||(_ref_p[1]==3))||(_ref_p[2]==3))) {
						{
							for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
								{
									(_ref_reg[_ref_i]=0);
								}
}
							for (byte _ref_i = 0;
((_ref_i<5)); (_ref_i++)) {
								{
									if ((_ref_swap[_ref_i]!=0)) {
										{
											(_ref_reg[_ref_i]=_ref_swap[_ref_i]);
										}
}
								}
}
							for (byte _ref_i = 0;
((_ref_i<3)); (_ref_i++)) {
								{
									(_ref_p[_ref_i]=0);
								}
}
							(_ref_cntr=3);
							(_ref_cv=3);
							_ref_p1->_msg_starter(myID);
							_ref_p2->_msg_starter(myID);
							_ref_p3->_msg_starter(myID);
						}
}
					else {
						{
							if ((_ref_p[0]==2)) {
								{
									_ref_p1->_msg_init(myID, 0);
								}
}
							if ((_ref_p[1]==2)) {
								{
									_ref_p2->_msg_init(myID, 0);
								}
}
							if ((_ref_p[2]==2)) {
								{
									_ref_p3->_msg_init(myID, 0);
								}
}
							for (byte _ref_i = 0;
((_ref_i<3)); (_ref_i++)) {
								{
									if ((_ref_p[_ref_i]==2)) {
										{
											(_ref_p[_ref_i]=0);
											(_ref_cv++);
										}
}
								}
}
							(_ref_cntr=_ref_cv);
						}
}
				}
}
		}
		return 0;

}
		