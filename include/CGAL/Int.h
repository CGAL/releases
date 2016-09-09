/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


#ifndef CGAL_INT_H
#define CGAL_INT_H

#include <CGAL/number_type_tags.h>

// INT

inline 
double 
CGAL_to_double(int i)
{
  return (double)i;
}

inline 
CGAL_Number_tag 
CGAL_number_type_tag(int)
{
  return CGAL_Number_tag();
}

inline 
bool 
CGAL_is_finite(int)
{
  return true;
}

inline 
bool 
CGAL_is_valid(int)
{
  return true;
}

inline
CGAL_io_Operator
CGAL_io_tag(int)
{
  return CGAL_io_Operator(); 
}

// LONG

inline 
double 
CGAL_to_double(long int i)
{
  return (double)i;
}

inline 
CGAL_Number_tag 
CGAL_number_type_tag(long int)
{
  return CGAL_Number_tag();
}

inline 
bool 
CGAL_is_finite(long int)
{
  return true;
}

inline 
bool 
CGAL_is_valid(long int)
{
  return true;
}

inline
CGAL_io_Operator
CGAL_io_tag(long int)
{
  return CGAL_io_Operator(); 
}

// SHORT

inline 
double 
CGAL_to_double(short int i)
{
  return (double)i;
}

inline 
CGAL_Number_tag 
CGAL_number_type_tag(short int)
{
  return CGAL_Number_tag();
}

inline 
bool 
CGAL_is_finite(short int)
{
  return true;
}

inline 
bool 
CGAL_is_valid(short int)
{
  return true;
}

inline
CGAL_io_Operator
CGAL_io_tag(short int)
{
  return CGAL_io_Operator(); 
}

// LONG LONG

#ifdef CGAL_LONG_LONG

inline 
double 
CGAL_to_double(long long i)
{
  return (double)i;
}

inline 
CGAL_Number_tag 
CGAL_number_type_tag(long long)
{
  return CGAL_Number_tag();
}

inline 
bool 
CGAL_is_finite(long long)
{
  return true;
}

inline 
bool 
CGAL_is_valid(long long)
{
  return true;
}
#endif // CGAL_LONG_LONG


#endif // CGAL_INT_H
