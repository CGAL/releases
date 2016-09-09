

#ifndef DOUBLECOMP_H
#define DOUBLECOMP_H 1

#include <LEDA/basic.h>
#include <math.h>


inline double to_double(double d)
{
    return d;
}

inline double abs(double d)
{
    return fabs(d);
}

extern bool is_finite(double d);

extern bool is_valid(double d);



#endif
