#ifndef SCRY_STATE_SET_H
#define SCRY_STATE_SET_H


#include <algorithm>
#include <map>
#include "LokiTypeInfo.h"
#include "State.h"


namespace scry {

    class StateSet : public RefCounted {
    protected:
        ~StateSet() { }

    public:
        static void bind();

        StateSet(const StatePtr& initial = 0) {
            if (initial) {
                setState(initial);
            }
        }

        void setState(const StatePtr& state) {
            _states[typeid(*state)] = state;
        }
        
        void switchTo(const StateSet& to, bool fullStateSwitch) const;

    private:
        typedef std::map<TypeInfo, StatePtr> StateMap;
        typedef StateMap::const_iterator StateMapCIter;
        StateMap _states;
    };
    SCRY_REF_PTR(StateSet);

    void setCurrentStateSet(const StateSetPtr& next, bool fullStateSwitch);

}


#endif
