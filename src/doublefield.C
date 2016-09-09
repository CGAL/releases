

#include <CGAL/doublefield.h>


#ifdef __sgi

// implementation for SGI IRIX 5.3.
#include <fp_class.h>

bool is_finite(double d)
{
    switch (fp_class_d(d)) {
    case FP_POS_NORM:
    case FP_NEG_NORM:
    case FP_POS_ZERO:
    case FP_NEG_ZERO:
    case FP_POS_DENORM:
    case FP_NEG_DENORM:
        return true;
    case FP_SNAN:
    case FP_QNAN:
    case FP_POS_INF:
    case FP_NEG_INF:
        return false;
    }
    return false; // NOT REACHED
}

bool is_valid(double d)
{
    switch (fp_class_d(d)) {
    case FP_POS_NORM:
    case FP_NEG_NORM:
    case FP_POS_ZERO:
    case FP_NEG_ZERO:
    case FP_POS_INF:
    case FP_NEG_INF:
    case FP_POS_DENORM:
    case FP_NEG_DENORM:
        return true;
    case FP_SNAN:
    case FP_QNAN:
        return false;
    }
    return false; // NOT REACHED
}

#endif // __sgi





#ifdef __hpux

// implementation for HP
#include <math.h>

bool is_valid(double d)
{
    return isnan(d) == 0;
}

bool is_finite(double d)
{
    switch (fpclassify(d)) {
    case FP_PLUS_NORM:
    case FP_MINUS_NORM:
    case FP_PLUS_ZERO:
    case FP_MINUS_ZERO:
    case FP_PLUS_DENORM:
    case FP_MINUS_DENORM:
        return true;
    case FP_PLUS_INF:
    case FP_MINUS_INF:
    case FP_SNAN:
    case FP_QNAN:
        return false;
    }
    return false; // NOT REACHED
}

#endif // __hpux





#ifdef __sun

// implementation for SUN

#ifdef __SVR4  // and even more special for SOLARIS
#include <ieeefp.h>
#endif // __SVR4

#include <sunmath.h>
#include <LEDA/misc.h>
bool is_finite(double d)
{
  if(finite(d)){
    return true;
  }
  return false; // NOT REACHED
}

bool is_valid(double d)
{
  return isnan(d) == 0;
}

#endif // __sun




