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
#ifndef SCRY_REF_COUNTED_H
#define SCRY_REF_COUNTED_H


#include <boost/intrusive_ptr.hpp>
#include <boost/python.hpp>
#include "Utility.h"


namespace scry {

    /**
     * Derive from RefCounted to make your class have reference-counted
     * lifetime semantics.  Use RefPtr to manage references.  (Don't call
     * ref() or unref() directly.)
     *
     * Note:  The reference count is initialized to 0.  This makes sense,
     * because, at object construction, no RefPtrs have referenced the
     * object.  However, this can cause trouble if you (indirectly) make
     * a RefPtr to 'this' within your constructor.  When the refptr goes
     * out of scope, the count goes back to 0, and the object is deleted
     * before it even exits the constructor.  Current recommended solution:  
     * Don't make refptrs to this.  Pass 'this' by raw pointer and such.
     */
    class RefCounted {
    protected:
        // Need at least one public constructor.
        RefCounted() {
        }

        /**
         * Protected so users of refcounted classes don't use std::auto_ptr
         * or the delete operator.
         *
         * Interfaces that derive from RefCounted should define an inline,
         * empty, protected destructor as well.
         */
        virtual ~RefCounted() {
            SCRY_ASSERT(_count == 0);
        }

    public:
        /**
         * Add a reference to the internal reference count.
         */
        void ref() {
            SCRY_ASSERT(_count >= 0);
            ++_count;
        }

        /**
         * Remove a reference from the internal reference count.  When this
         * reaches 0, the object is destroyed.
         */
        void unref() {
            SCRY_ASSERT(_count > 0);
            if (--_count == 0) {
                delete this;
            }
        }

    private:
        // Copying a RefCounted object must be done manually.  Otherwise
        // the refCount gets copied too, and that's Bad.
        RefCounted(const RefCounted& rhs);
        RefCounted& operator=(const RefCounted& rhs);

        Zeroed<int> _count;
    };


    inline void intrusive_ptr_add_ref(RefCounted* ptr) {
        ptr->ref();
    }

    inline void intrusive_ptr_release(RefCounted* ptr) {
        ptr->unref();
    }


#define SCRY_REF_PTR(type) \
    typedef boost::intrusive_ptr<type> type##Ptr

    
#if 0
    // Stuff specific to Boost.Python bindings follows.
    // This is magic that Dusty Leary gave me.

    struct make_intrusive_holder {
        typedef	PyObject* result_type;

        template <class	T>
        static result_type execute(T* p) {
            typedef boost::intrusive_ptr<T> smart_pointer;
            typedef boost::python::objects::pointer_holder<smart_pointer, T>
                    holder_t;
            smart_pointer ptr(p);
            return boost::python::objects::make_ptr_instance<T, holder_t>::
                execute(ptr);
        }
    };

    template<typename T>
    struct manage_intrusive_object_requires_a_pointer_return_type {};

    struct manage_intrusive_object {
        template <class	T>
        struct apply {
            typedef typename boost::mpl::if_c<boost::is_pointer<T>::value
                , boost::python::to_python_indirect<T, make_intrusive_holder>
                , manage_intrusive_object_requires_a_pointer_return_type<T>
            >::type type;
        };
    };
#endif

}

#endif
