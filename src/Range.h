#ifndef SCRY_RANGE_H
#define SCRY_RANGE_H


#include "RefCounted.h"


namespace scry {

    class Range : public RefCounted {
    protected:
        ~Range() { }

    public:
        static void bind();
        
        Range& get() { return *this; }

        virtual bool next(size_t& out) = 0;
    };
    SCRY_REF_PTR(Range);


    class LinearRange : public Range {
    protected:
        ~LinearRange() { }

    public:
        static void bind();

        LinearRange(size_t begin, size_t end, size_t step = 1) {
            SCRY_ASSERT(step > 0);

            _begin = begin;
            _end   = end;
            _step  = step;

            _current = _begin;
        }

        bool next(size_t& out) {
            if (_current > _end) {
                return false;
            }
            out = _current;
            _current += _step;
            return true;
        }

    private:
        size_t _begin;
        size_t _end;
        size_t _step;

        size_t _current;
    };
    SCRY_REF_PTR(LinearRange);


    class PowerRange/*r*/ : public Range {
    protected:
        ~PowerRange() { }

    public:
        static void bind();

        PowerRange(size_t begin, size_t end, size_t power = 2) {
            _begin = begin;
            _end   = end;
            _power = power;

            _current = _begin;
        }

        bool next(size_t& out) {
            if (_current > _end) {
                return false;
            }
            // It's too bad there's not an integer version of pow().
            out = static_cast<size_t>(pow(double(_power), double(_current)));
            _current += 1;
            return true;
        }

    private:
        size_t _begin;
        size_t _end;
        size_t _power;

        size_t _current;
    };
    SCRY_REF_PTR(PowerRange);


}


#endif
