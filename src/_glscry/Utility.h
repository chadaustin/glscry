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
#ifndef SCRY_UTILITY_H
#define SCRY_UTILITY_H


#include <stdexcept>


namespace scry {

    /**
     * Inited is short for Initialized.  This template class lets you
     * initialize integer members in a class without using member
     * initializers or assignments in the constructor.  It's much easier
     * to remember to use this than those two.  ;)
     */
    template<typename T, T initVal = 0>
    class Inited {
    public:
        Inited() : _value(initVal) { }
        Inited(const T& t) : _value(t) { }

        operator       T&()       { return get(); }
        operator const T&() const { return get(); }

        T* operator&()       { return &_value; }
        const T* operator&() const { return &_value; }

        T& get()       { return _value; }
        const T& get() const { return _value; }

    private:
        T _value;
    };


    /**
     * Same as Inited<T>, but can be used with floats or other types that
     * can't be used as template parameters.
     */
    template<typename T>
    class Zeroed {
    public:
        Zeroed() : _value(0) { }
        Zeroed(const T& t) : _value(t) { }

        operator       T&()       { return get(); }
        operator const T&() const { return get(); }

        T& operator->()             { return get(); }
        const T& operator->() const { return get(); }

        T* operator&()       { return &_value; }
        const T* operator&() const { return &_value; }

        T& get()             { return _value; }
        const T& get() const { return _value; }

    private:
        T _value;
    };


#define SCRY_ASSERT(expr)                               \
    if (!(expr)) {                                      \
        throw std::runtime_error("Assertion: " #expr);  \
    }


    template<typename T>
        void delete_function(T* t) {
        delete t;
    }


    template<typename T, typename U>
    bool check_type(U* u) {
        return (!u || dynamic_cast<T>(u) ? true : false);
    }

    template<typename T, typename U>
    bool check_type_ref(U& u) {
        try {
            dynamic_cast<T>(u);
            return true;
        }
        catch (const std::bad_cast&) {
        }
        return false;
    }

    /**
     * Same as static_cast, except does some type checking in debug
     * builds.
     * @{
     */
    template<typename T, typename U>
    T checked_cast(U* u) {
        SCRY_ASSERT((check_type<T, U>(u)));
        return static_cast<T>(u);
    }

    template<typename T, typename U>
    T checked_cast_ref(U& u) {
        SCRY_ASSERT((check_type_ref<T, U>(u)));
        return static_cast<T>(u);
    }
    /**
     * @}
     */

}


#endif
