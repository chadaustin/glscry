/* [Begin Copyright Header]
 *
 * GLScry - OpenGL Performance Analysis Tool
 * Copyright (C) 2004-2005  Iowa State University
 * 
 * This software is licensed under the terms of the GNU Lesser Public
 * License, version 2.1, as published by the Free Software Foundation.
 * See the file COPYRIGHT.txt for details.
 * 
 * Authors:
 *   Chad Austin <aegisk@iastate.edu>
 *   Dirk Reiners <dreiners@iastate.edu>
 *
 * [End Copyright Header] */
#ifndef SCRY_TEST_H
#define SCRY_TEST_H


#include <string>
#include <vector>
#include "Action.h"
#include "RefCounted.h"
#include "StateSet.h"
#include "Timer.h"
#include "Transform.h"
#include "Types.h"


#define SCRY_BEGIN_RESULT_DESCS()                                       \
    static ResultDescList getClassResultDescs() {                       \
        ResultDescList rv;                                              \

#define SCRY_RESULT_DESC(name, units)           \
    rv.push_back(ResultDesc((name), (units)));

#define SCRY_END_RESULT_DESCS()                                   \
        return rv;                                                \
    }                                                             \
    ResultDescList getResultDescs() {                             \
        return getClassResultDescs();                             \
    }


namespace scry {

    struct ResultDesc {
        ResultDesc(const std::string& name_, const std::string units_)
        : name(name_)
        , units(units_) {
        }

        bool operator==(const ResultDesc& rhs) const {
            return name == rhs.name && units == rhs.units;
        }

        bool operator<(const ResultDesc& rhs) const {
            if (name < rhs.name) return true;
            if (name > rhs.name) return false;
            return units < rhs.units;
        }

        std::string name;
        std::string units;
    };

    typedef std::vector<ResultDesc> ResultDescList;


    typedef std::vector<double> ResultValues;


    class Test : public RefCounted {
    protected:
        ~Test() { }

    public:
        static void bind();

        // Public interface.

        Test(const char* name) {
            _name = name;
        }

        const char* getName() const {
            return _name.c_str();
        }

        void setTransform(TransformPtr transform) {
            _transform = transform;
        }

        TransformPtr getTransform() const {
            return _transform;
        }

        bool getFullStateSwitch() const {
            return _fullStateSwitch;
        }

        void setFullStateSwitch(bool fullStateSwitch) {
            _fullStateSwitch = fullStateSwitch;
        }

        void addStateSet(const StateSetPtr& stateSet) {
            _stateSetList.push_back(stateSet);
        }            

        void addAction(const ActionPtr& action) {
            _actionList.push_back(action);
        }

        ResultValues run(float runFor);
    

        // Overridden methods.

        virtual bool isSupported() const { return true; }
        virtual ResultDescList getResultDescs() = 0;

        virtual void setup()    { }
        virtual void iterate(ResultValues& results) = 0;
        virtual void teardown() { }

    private:
        std::string _name;
        TransformPtr _transform;

        Inited<bool, false>      _fullStateSwitch;
        std::vector<StateSetPtr> _stateSetList;
        std::vector<ActionPtr>   _actionList;
    };
    SCRY_REF_PTR(Test);


}


#endif
