#include "StateSet.h"


namespace scry {

    namespace {

        void stateSwitch(const State& from, const State& to) {
            from.switchTo(to);
        }
        
        void switchFromDefault(const State& to) {
            stateSwitch(to.getDefault(), to);
        }

        void switchToDefault(const State& from) {
            stateSwitch(from, from.getDefault());
        }

        template<typename T>
        T assertTrue(T t) {
            assert(t);
            return t;
        }

    }

    void StateSet::switchTo(const StateSet& to) const {
        StateMapCIter fromIter = _states.begin();
        StateMapCIter fromEnd  = _states.end();
        StateMapCIter toIter   = to._states.begin();
        StateMapCIter toEnd    = to._states.end();

        while (fromIter != fromEnd && toIter != toEnd) {
            if (fromIter == fromEnd) {
                switchFromDefault(*assertTrue(toIter->second));
                ++toIter;
            } else if (toIter == toEnd) {
                switchToDefault(*assertTrue(fromIter->second));
                ++fromIter;
            } else if (fromIter->first > toIter->first) {
                switchFromDefault(*assertTrue(toIter->second));
                ++toIter;
            } else if (fromIter->first < toIter->first) {
                switchToDefault(*assertTrue(fromIter->second));
                ++fromIter;
            } else {
                stateSwitch(*assertTrue(fromIter->second),
                            *assertTrue(toIter->second));
                ++toIter;
                ++fromIter;
            }
        }
    }

    void setCurrentStateSet(const StateSet& next) {
        static StateSet current;
        current.switchTo(next);
        current = next;
    }

}
