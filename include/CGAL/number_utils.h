#ifndef CGAL_NUMBER_UTILS_H
#define CGAL_NUMBER_UTILS_H

#include <LEDA/basic.h> // for bool

template <class NT>
inline bool is_zero(NT x)
{
    return x == NT(0);
}

template <class NT>
inline bool is_negative(NT x)
{
    return x < NT(0);
}

template <class NT>
inline bool is_positive(NT x)
{
    return x > NT(0);
}

template <class NT>
int sign(NT x)
{
    return (x < NT(0)) ? -1: (x > NT(0)) ? 1 : 0;
}

template <class NT>
NT abs(NT x)
{
    return (x >= NT(0)) ? x: -x;
}

#endif
