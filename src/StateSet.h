#ifndef SCRY_STATE_SET_H
#define SCRY_STATE_SET_H


#include <algorithm>
#include <map>
#include "LokiTypeInfo.h"
#include "State.h"


namespace scry {


    class StateSet {
    public:
        void setState(State* state) {
            _states[typeid(*state)] = state;
        }

        void apply() {
            for (StateMapIter i = _states.begin(); i != _states.end(); ++i) {
                i->second->apply();
            }
        }

        void reset() {
            for (StateMapIter i = _states.begin(); i != _states.end(); ++i) {
                i->second->reset();
            }
        }

    private:
        typedef std::map<TypeInfo, StatePtr> StateMap;
        typedef StateMap::iterator StateMapIter;
        StateMap _states;
    };


}


#endif
