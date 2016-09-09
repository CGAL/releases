

#ifndef DOUBLECOMP_H
#define DOUBLECOMP_H 1

#include <math.h>
#include <LEDA/basic.h>

inline double CGAL_to_double(double d)
{
    return d;
}

inline double CGAL_abs(double d)
{
    return fabs(d);
}

extern bool CGAL_is_finite(double d);

extern bool CGAL_is_valid(double d);

#endif
