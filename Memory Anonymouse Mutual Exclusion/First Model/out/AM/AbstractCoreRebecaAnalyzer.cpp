#include "AbstractCoreRebecaAnalyzer.h"

			#define _ref_p1 (dynamic_cast<ProcessActor*>(rebecs[0]))
	    			#define _ref_p2 (dynamic_cast<ProcessActor*>(rebecs[1]))
	    			#define _ref_p3 (dynamic_cast<ProcessActor*>(rebecs[2]))
	    			#define _ref_m (dynamic_cast<MemoryActor*>(rebecs[3]))
	    		
			boolean AbstractCoreRebecaAnalyzer::_propDef_pw1 () {
			return _ref_p1->_ref_winner;
		}
			boolean AbstractCoreRebecaAnalyzer::_propDef_pw2 () {
			return _ref_p2->_ref_winner;
		}
			boolean AbstractCoreRebecaAnalyzer::_propDef_pw3 () {
			return _ref_p3->_ref_winner;
		}
			boolean AbstractCoreRebecaAnalyzer::_propDef_mutex1 () {
			return (!(_ref_p1->_ref_winner&&_ref_p2->_ref_winner));
		}
			boolean AbstractCoreRebecaAnalyzer::_propDef_mutex2 () {
			return (!(_ref_p1->_ref_winner&&_ref_p3->_ref_winner));
		}
			boolean AbstractCoreRebecaAnalyzer::_propDef_mutex3 () {
			return (!(_ref_p2->_ref_winner&&_ref_p3->_ref_winner));
		}
		
			#define _ref_pw1 _propDef_pw1()
			#define _ref_pw2 _propDef_pw2()
			#define _ref_pw3 _propDef_pw3()
			#define _ref_mutex1 _propDef_mutex1()
			#define _ref_mutex2 _propDef_mutex2()
			#define _ref_mutex3 _propDef_mutex3()
					#undef _ref_pw1
			#undef _ref_pw2
			#undef _ref_pw3
			#undef _ref_mutex1
			#undef _ref_mutex2
			#undef _ref_mutex3
	
			#undef _ref_p1
			#undef _ref_p2
			#undef _ref_p3
			#undef _ref_m
	
AbstractCoreRebecaAnalyzer::AbstractCoreRebecaAnalyzer(ostream &outStream, int hashmapSize) : analysisOutputStream(outStream){
	this->hashmapSize = hashmapSize;
	this->numberOfTransitions = 0;
	this->numberOfStates = 0;
}

void AbstractCoreRebecaAnalyzer::unmarshalRebecs(long* node) {
	int i;
	for (i = 0; i < REBEC_COUNT; i++) {
        rebecs[i]->unmarshalActor(node[i]);   // uncompress all states of all rebecs
    }
}

void AbstractCoreRebecaAnalyzer::marshalRebecs(long* node) {
	int i;
	for (i=0; i<REBEC_COUNT; i++){
		node[i] = rebecs[i]->marshalActor();
	}
}

State* AbstractCoreRebecaAnalyzer::storeRecentlyCreatedState (byte &result, short int claim, short int fairnessCounter) {

    numberOfTransitions++;
    State *st;
    long sys[REBEC_COUNT];
	marshalRebecs(sys);
		result = NEW_STATE;
	if (st = storage->exists (sys, claim)){
		if (st->isOnStack()){
			result |= ON_STACK;	// used in detecting cycle & stack proviso
		}
		if (st->isVisited(fairnessCounter)){
			result &= ~NEW_STATE;
		}
        	}
	else
    	{
		st = storage->put(sys, claim);	//create the new State
		if (st == NULL) {
	        throw Exception("Not enough memory for continuing the state space generation.");
		}
	    st->stateID = numberOfStates++;
	    #ifdef DEBUG_LEVEL_2
			cout << "State stored successfully with id: " << st->stateID << "." << endl;
		#endif
	}
	return st;
}

void AbstractCoreRebecaAnalyzer::instantiationPart() {
	vector<AbstractActor*>* referenceToRebecs = new vector<AbstractActor*>();
	byte maxRebecID = 0;
        	
    	ProcessActor* _ref_p1 = new ProcessActor(maxRebecID++, "p1", 10, 5, *referenceToRebecs 
    											#ifdef DEBUG_LEVEL_2 
    											, analysisOutputStream 
    											#endif
    											, 82    											, hashmapSize
    												    											);
		            rebecs.push_back(_ref_p1);
        referenceToRebecs->push_back(_ref_p1);
	    	
    	ProcessActor* _ref_p2 = new ProcessActor(maxRebecID++, "p2", 10, 5, *referenceToRebecs 
    											#ifdef DEBUG_LEVEL_2 
    											, analysisOutputStream 
    											#endif
    											, 82    											, hashmapSize
    												    											);
		            rebecs.push_back(_ref_p2);
        referenceToRebecs->push_back(_ref_p2);
	    	
    	ProcessActor* _ref_p3 = new ProcessActor(maxRebecID++, "p3", 10, 5, *referenceToRebecs 
    											#ifdef DEBUG_LEVEL_2 
    											, analysisOutputStream 
    											#endif
    											, 82    											, hashmapSize
    												    											);
		            rebecs.push_back(_ref_p3);
        referenceToRebecs->push_back(_ref_p3);
	    	
    	MemoryActor* _ref_m = new MemoryActor(maxRebecID++, "m", 25, 5, *referenceToRebecs 
    											#ifdef DEBUG_LEVEL_2 
    											, analysisOutputStream 
    											#endif
    											, 185    											, hashmapSize
    												    											);
		            rebecs.push_back(_ref_m);
        referenceToRebecs->push_back(_ref_m);
	
	        	_ref_p1->known = new byte[MAX_KNOWN];
    	    	_ref_p1->known[0] = _ref_p1->myID;
    	 _ref_p1->known[1] = _ref_m->myID;
    				
						_ref_p1->constructorProcess(INITIAL_SENDER
	        	        , 1
	        	        , 1
	        	        , 2
	        	        , 3
	        	        , 4
	        	        , 5
	        		);
        	    	_ref_p2->known = new byte[MAX_KNOWN];
    	    	_ref_p2->known[0] = _ref_p2->myID;
    	 _ref_p2->known[1] = _ref_m->myID;
    				
						_ref_p2->constructorProcess(INITIAL_SENDER
	        	        , 2
	        	        , 2
	        	        , 3
	        	        , 5
	        	        , 1
	        	        , 4
	        		);
        	    	_ref_p3->known = new byte[MAX_KNOWN];
    	    	_ref_p3->known[0] = _ref_p3->myID;
    	 _ref_p3->known[1] = _ref_m->myID;
    				
						_ref_p3->constructorProcess(INITIAL_SENDER
	        	        , 3
	        	        , 3
	        	        , 1
	        	        , 4
	        	        , 5
	        	        , 2
	        		);
        	    	_ref_m->known = new byte[MAX_KNOWN];
    	    	_ref_m->known[0] = _ref_m->myID;
    	 _ref_m->known[1] = _ref_p1->myID;
    				 _ref_m->known[2] = _ref_p2->myID;
    				 _ref_m->known[3] = _ref_p3->myID;
    				
						_ref_m->constructorMemory(INITIAL_SENDER
	        		);
        	
	numberOfStates = 0;
	numberOfTransitions = 0;

    #ifdef DEBUG
    	analysisOutputStream << "Rebecs are instanciated successfully." << endl;
    #endif

}

void AbstractCoreRebecaAnalyzer::exportState(State* current, ostream& outStream) {
	//<< ":" << current->claim 
	outStream << "<state id=\"" << current->stateID << "\" "; 
		outStream << "atomicpropositions=\""; 
			if (_propDef_pw1 ())
			outStream << "pw1,"; 
			if (_propDef_pw2 ())
			outStream << "pw2,"; 
			if (_propDef_pw3 ())
			outStream << "pw3,"; 
			if (_propDef_mutex1 ())
			outStream << "mutex1,"; 
			if (_propDef_mutex2 ())
			outStream << "mutex2,"; 
			if (_propDef_mutex3 ())
			outStream << "mutex3,"; 
		outStream << "\" ";
	outStream << ">" << endl;
	for (int cnt = 0; cnt < REBEC_COUNT; cnt++)
		rebecs[cnt]->exportStateInXML(outStream, "\t");
	outStream << "</state>" << endl;
}

void AbstractCoreRebecaAnalyzer::exportTransition(State* source, State* destination, 
		string sender, string owner, string label, ostream& outStream) {
	exportTransition(to_string(source->stateID), to_string(destination->stateID), sender, owner, label, outStream);  
}

void AbstractCoreRebecaAnalyzer::exportTransition(string source, string destination, 
		string sender, string owner, string label, ostream& outStream) {
    outStream << "<transition source=\"" << source << "\" destination=\"" << 
		destination << "\"> <messageserver sender=\"" << sender << 
		"\" owner=\"" << owner << "\" title=\"" << label << "\"/></transition>" << endl;
}
