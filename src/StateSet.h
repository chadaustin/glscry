#ifndef SCRY_STATE_SET_H
#define SCRY_STATE_SET_H


#include <algorithm>
#include <map>
#include "LokiTypeInfo.h"
#include "State.h"


namespace scry {

    class StateSet : public RefCounted {
    public:
        static void bind();

        void setState(State* state) {
            _states[typeid(*state)] = state;
        }
        
        void switchTo(const StateSet& to) const;

    private:
        typedef std::map<TypeInfo, StatePtr> StateMap;
        typedef StateMap::const_iterator StateMapCIter;
        StateMap _states;
    };
    SCRY_REF_PTR(StateSet);

    void setCurrentStateSet(const StateSetPtr& next);

}


#endif
