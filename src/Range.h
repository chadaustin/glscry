#ifndef TRIAGARA_RANGE_H
#define TRIAGARA_RANGE_H


#include "Base.h"


TRIAGARA_BEGIN_NAMESPACE


class Range {
public:
    Range& get() { return *this; }

    virtual bool next(size_t& out) = 0;
};


class LinearRange : public Range {
public:
    LinearRange(size_t begin, size_t end, size_t step = 1) {
        assert(step > 0);

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


class PowerRange/*r*/ : public Range {
public:
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


TRIAGARA_END_NAMESPACE


#endif
