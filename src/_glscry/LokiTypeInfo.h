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
////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The author or Addison-Welsey Longman make no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// Last update: May 19, 2002

#ifndef SCRY_TYPE_INFO_H
#define SCRY_TYPE_INFO_H

#include <typeinfo>
#include "Utility.h"

namespace scry {

/// Purpose: offer a first-class, comparable wrapper over std::type_info
class TypeInfo {
public:
    /// needed for containers
    TypeInfo() {
        class Nil {};
        pInfo_ = &typeid(Nil);
        SCRY_ASSERT(pInfo_ && "pInfo_ not valid");
    }
        
    /// non-explicit
    TypeInfo(const std::type_info& ti) {
        pInfo_ = &ti;
        SCRY_ASSERT(pInfo_ && "pInfo_ not valid");
    }

    /// Access for the wrapped std::type_info
    const std::type_info& Get() const {
        SCRY_ASSERT(pInfo_ && "pInfo_ not valid");
        return *pInfo_;
    }
        
    /// Compatibility functions
    bool before(const TypeInfo& rhs) const {
        SCRY_ASSERT(pInfo_ && "pInfo_ not valid");
        return pInfo_->before(*rhs.pInfo_) != 0;
    }
        
    const char* name() const {
        SCRY_ASSERT(pInfo_ && "pInfo_ not valid");
        return pInfo_->name();
    }

private:
    const std::type_info* pInfo_;
};

    
// Comparison operators
    
inline bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
{ return (lhs.Get() == rhs.Get()) != 0; }

inline bool operator<(const TypeInfo& lhs, const TypeInfo& rhs)
{ return lhs.before(rhs); }

inline bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
{ return !(lhs == rhs); }    
    
inline bool operator>(const TypeInfo& lhs, const TypeInfo& rhs)
{ return rhs < lhs; }
    
inline bool operator<=(const TypeInfo& lhs, const TypeInfo& rhs)
{ return !(lhs > rhs); }
     
inline bool operator>=(const TypeInfo& lhs, const TypeInfo& rhs)
{ return !(lhs < rhs); }
    
}


#endif
