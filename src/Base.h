#ifndef SCRY_BASE_H
#define SCRY_BASE_H


#include <gmtl/gmtl.h>


#define SCRY_BEGIN_NAMESPACE namespace scry {
#define SCRY_END_NAMESPACE   }


// Perhaps the stuff below should go into a Utility.h.


SCRY_BEGIN_NAMESPACE


using gmtl::Vec4f;


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


template<typename T>
void delete_function(T* t) {
    delete t;
}


SCRY_END_NAMESPACE


#endif
