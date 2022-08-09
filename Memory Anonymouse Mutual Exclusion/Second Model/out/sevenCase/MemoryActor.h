











#ifndef __MEMORY_ACTOR_H__
#define __MEMORY_ACTOR_H__

class ProcessActor;

#include "AbstractActor.h"

class MemoryActor :
		public virtual AbstractActor
{

public:
    MemoryActor(byte myID, char* myName, int maxQueueLength, int maxParamLength, vector<AbstractActor*>& rebecsRef
		#ifdef DEBUG_LEVEL_2 
			, ostream &out
		#endif
    				






					,int stateSize, int hashmapSize
		    );
	~MemoryActor();
	
	long methodSelectorAndExecutor();
	
    char* getClassName();
    
	virtual void exportStateVariablesInXML(ostream &out, string tab);
	virtual void exportAMessageInXML(ostream &out, string tab, int cnt);

	virtual void exportInsideStateVariablesTagInXML(ostream &out, string tab);

    virtual void marshalActorToArray(byte* array);
    void marshalVariablesToArray(byte * array);


    virtual void unmarshalActorFromArray(byte* array);
    void unmarshalVariablesFromArray(byte * array);


        	std::array<byte, 5> _ref_reg;

        	std::array<byte, 5> _ref_swap;

        	std::array<byte, 3> _ref_p;

        	byte _ref_cntr;

        	byte _ref_cv;

    
			long constructorMemory(byte creatorID
					);
	
           virtual void _msg_receive(byte senderId
            		    	        ,
	    	        		byte
	         _ref_u
	        	        , 
	        	        		int
	         _ref_l
	        	                )
                 ;
       virtual long msgsrvreceive(
            		    	        		byte
	         _ref_u
	        	        , 
	        	        		int
	         _ref_l
	        	                )
                ;
           virtual void _msg_result(byte senderId
            		    	        ,
	    	        		boolean
	         _ref_w
	        	        , 
	        	        		boolean
	         _ref_l
	        	        , 
	        	        		byte
	         _ref_u
	        	                )
                 ;
       virtual long msgsrvresult(
            		    	        		boolean
	         _ref_w
	        	        , 
	        	        		boolean
	         _ref_l
	        	        , 
	        	        		byte
	         _ref_u
	        	                )
                ;
    
				






			protected:
	    static byte** table;
		virtual byte** getTable();
	protected:
    };

#endif