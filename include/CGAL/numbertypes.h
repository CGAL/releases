 
// Source: numbertypes.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_NUMBERTYPES_H
#define CGAL_NUMBERTYPES_H

#include <LEDA/real.h>
#include <CGAL/number_utils.h>
#include <CGAL/doublefield.h>
#include <CGAL/Rational.h>

 
inline
double
CGAL_to_double(const integer & i)
{
 return i.todouble();
}


inline
double
CGAL_to_double(const real & r)
{
 return r.todouble();
}
 


#endif // CGAL_NUMBERTYPES_H
