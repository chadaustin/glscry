#ifndef TRIAGARA_STATE_SET_H
#define TRIAGARA_STATE_SET_H


#include <algorithm>
#include <map>
#include "Base.h"
#include "LokiTypeInfo.h"
#include "State.h"


TRIAGARA_BEGIN_NAMESPACE


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
    typedef std::map<TypeInfo, State*> StateMap;
    typedef StateMap::iterator StateMapIter;
    StateMap _states;
};


TRIAGARA_END_NAMESPACE


#endif
