#include "StateSet.h"
using namespace boost::python;


namespace scry {

    namespace {

        void stateSwitch(
            const State& from,
            const State& to,
            bool fullStateSwitch
        ) {
            from.switchTo(to, fullStateSwitch);
        }
        
        void switchFromDefault(const State& to, bool fullStateSwitch) {
            stateSwitch(to.getDefault(), to, fullStateSwitch);
        }

        void switchToDefault(const State& from, bool fullStateSwitch) {
            stateSwitch(from, from.getDefault(), fullStateSwitch);
        }

        template<typename T>
        T assertTrue(T t) {
            assert(t);
            return t;
        }

    }

    void StateSet::bind() {
        class_<StateSet, StateSetPtr, boost::noncopyable>("StateSet", no_init)
            .def(init<>())
            .def("setState", &StateSet::setState)
            ;
    }

    void StateSet::switchTo(const StateSet& to, bool fullStateSwitch) const {
        StateMapCIter fromIter = _states.begin();
        StateMapCIter fromEnd  = _states.end();
        StateMapCIter toIter   = to._states.begin();
        StateMapCIter toEnd    = to._states.end();

        while (fromIter != fromEnd && toIter != toEnd) {
            if (fromIter == fromEnd) {
                switchFromDefault(*assertTrue(toIter->second),
                                  fullStateSwitch);
                ++toIter;
            } else if (toIter == toEnd) {
                switchToDefault(*assertTrue(fromIter->second),
                                fullStateSwitch);
                ++fromIter;
            } else if (fromIter->first > toIter->first) {
                switchFromDefault(*assertTrue(toIter->second),
                                  fullStateSwitch);
                ++toIter;
            } else if (fromIter->first < toIter->first) {
                switchToDefault(*assertTrue(fromIter->second),
                                fullStateSwitch);
                ++fromIter;
            } else {
                stateSwitch(*assertTrue(fromIter->second),
                            *assertTrue(toIter->second),
                            fullStateSwitch);
                ++toIter;
                ++fromIter;
            }
        }
    }

    void setCurrentStateSet(const StateSetPtr& next, bool fullStateSwitch) {
        static StateSetPtr def = new StateSet;
        static StateSetPtr current;

        StateSetPtr from = (current ? current : def);
        StateSetPtr to   = (next    ? next    : def);
        from->switchTo(*to, fullStateSwitch);
        current = next;
    }

}
