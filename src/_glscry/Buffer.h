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
#ifndef SCRY_BUFFER_H
#define SCRY_BUFFER_H


#include "Array.h"
#include "Pump.h"


namespace scry {

    struct Buffer {
              GLubyte* data_ptr()       { return &data[0]; }
        const GLubyte* data_ptr() const { return &data[0]; }

        // i is an offset into the buffer in *vectors*
              GLubyte* offset(size_t i)       { return data_ptr() + i * getVectorSize(); }
        const GLubyte* offset(size_t i) const { return data_ptr() + i * getVectorSize(); }
        

        size_t getVectorSize() const {
            return getArrayVectorSize(array);
        }

        ArrayPtr array;  // The array that filled this buffer.
        std::vector<GLubyte> data;
        Zeroed<Pump> pump;
        //Zeroed<GLsizei> stride;
    };


    class BufferIterator {
    public:
        explicit BufferIterator(const Buffer& buffer) {
            _pump = buffer.pump;
            _data = buffer.data_ptr();
        }

        void step() {
            _data = _pump(_data);
        }

    private:
        Pump _pump;
        const void* _data;
    };

    typedef std::vector<BufferIterator> BufferIteratorList;


    inline void tryAddBuffer(BufferIteratorList& bi, const Buffer& b) {
        if (b.pump) {
            bi.push_back(BufferIterator(b));
        }
    }

}


#endif
