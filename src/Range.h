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

        LinearRange(float begin, float end, float step = 1) {
            SCRY_ASSERT(step > 0);

            _begin = begin;
            _end   = end;
            _step  = step;

            _current = _begin;
        }

        bool next(size_t& out) {
            if (_current > _end) {
                _current = _begin;
                return false;
            }
            out = static_cast<size_t>(_current);
            _current += _step;
            return true;
        }

    private:
        float _begin;
        float _end;
        float _step;

        float _current;
    };
    SCRY_REF_PTR(LinearRange);


    class PowerRange/*r*/ : public Range {
    protected:
        ~PowerRange() { }

    public:
        static void bind();

        PowerRange(float begin, float end, float power = 2) {
            _begin = begin;
            _end   = end;
            _power = power;

            _current = _begin;
        }

        bool next(size_t& out) {
            if (_current > _end) {
                _current = _begin;
                return false;
            }
            // It's too bad there's not an integer version of pow().
            out = static_cast<size_t>(pow(_power, _current));
            _current += 1;
            return true;
        }

    private:
        float _begin;
        float _end;
        float _power;

        float _current;
    };
    SCRY_REF_PTR(PowerRange);


}


#endif
