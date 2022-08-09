#ifndef __ABSTRACT_CORE_REBECA_ANALYZER_H__
#define __ABSTRACT_CORE_REBECA_ANALYZER_H__







#include "CoreRebecaDFSHashmap.h"
#include "AbstractActor.h"

    #include "ProcessActor.h"
    #include "MemoryActor.h"

#include <iostream>
#include <queue>

#define ON_STACK  2

class AbstractCoreRebecaAnalyzer {

protected:
	vector<AbstractActor*> rebecs;
	CoreRebecaDFSHashmap *storage;
	// This variable is used for initialization of TimedBFSHashmap
	int hashmapSize;
	//Analysis of Timed Rebeca are based on BFS traversal which requires an open border queue
	int numberOfTransitions;
	int numberOfStates;
	
	ostream &analysisOutputStream;

	virtual void exportState(State* current, ostream& outStream);
	virtual void exportTransition(State* source, State* destination, 
		string sender, string owner, string label, ostream& outStream);
	virtual void exportTransition(string source, string destination, 
		string sender, string owner, string label, ostream& outStream);
		
	State* storeRecentlyCreatedState(byte &result, short int claim, short int fairnessCounter);

    virtual void marshalRebecs(long* node);
    virtual void unmarshalRebecs(long* node);

            	boolean _propDef_pw1 ();
        	boolean _propDef_pw2 ();
        	boolean _propDef_pw3 ();
        	boolean _propDef_mutex1 ();
        	boolean _propDef_mutex2 ();
        	boolean _propDef_mutex3 ();
    	
	    
public:

	AbstractCoreRebecaAnalyzer(std::ostream &out, int hashmapSize);
	virtual void instantiationPart();
};

#endif