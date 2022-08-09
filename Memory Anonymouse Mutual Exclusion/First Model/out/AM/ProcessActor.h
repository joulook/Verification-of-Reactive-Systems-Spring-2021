











#ifndef __PROCESS_ACTOR_H__
#define __PROCESS_ACTOR_H__

class MemoryActor;

#include "AbstractActor.h"

class ProcessActor :
		public virtual AbstractActor
{

public:
    ProcessActor(byte myID, char* myName, int maxQueueLength, int maxParamLength, vector<AbstractActor*>& rebecsRef
		#ifdef DEBUG_LEVEL_2 
			, ostream &out
		#endif
    				






					,int stateSize, int hashmapSize
		    );
	~ProcessActor();
	
	long methodSelectorAndExecutor();
	
    char* getClassName();
    
	virtual void exportStateVariablesInXML(ostream &out, string tab);
	virtual void exportAMessageInXML(ostream &out, string tab, int cnt);

	virtual void exportInsideStateVariablesTagInXML(ostream &out, string tab);

    virtual void marshalActorToArray(byte* array);
    void marshalVariablesToArray(byte * array);


    virtual void unmarshalActorFromArray(byte* array);
    void unmarshalVariablesFromArray(byte * array);


        	byte _ref_uid;

        	std::array<byte, 5> _ref_mem;

        	std::array<byte, 5> _ref_add;

        	boolean _ref_winner;

    
			long constructorProcess(byte creatorID
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
	        	        		);
	
           virtual void _msg_init(byte senderId
            		    	        ,
	    	        		int
	         _ref_round
	        	                )
                 ;
       virtual long msgsrvinit(
            		    	        		int
	         _ref_round
	        	                )
                ;
           virtual void _msg_get(byte senderId
            		    	        ,
	    	        		byte
	         _ref_v
	        	        , 
	        	        		int
	         _ref_l
	        	                )
                 ;
       virtual long msgsrvget(
            		    	        		byte
	         _ref_v
	        	        , 
	        	        		int
	         _ref_l
	        	                )
                ;
           virtual void _msg_crit(byte senderId
            	        )
                 ;
       virtual long msgsrvcrit(
            	        )
                ;
           virtual void _msg_starter(byte senderId
            	        )
                 ;
       virtual long msgsrvstarter(
            	        )
                ;
    
				






			protected:
	    static byte** table;
		virtual byte** getTable();
	protected:
        	byte _synchmethod_owned(
            	        )
                 ;
        	byte _synchmethod_findMostPresent(
            	        )
                 ;
    };

#endif