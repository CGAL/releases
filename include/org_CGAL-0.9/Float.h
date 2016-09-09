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



#ifndef CGAL_FLOAT_H
#define CGAL_FLOAT_H 1

#include <CGAL/basic.h>
#include <math.h>



inline double CGAL_to_double(float f)
{
    return (double)f;
}
/*
inline float CGAL_abs(float f)
{
    return fabs(f);
}
*/
inline float CGAL_denominator(float)
{
  return 1.0;
}

inline float CGAL_numerator(float f)
{
  return f;
}

inline CGAL_Number_tag CGAL_number_type_tag(float)
{
  return CGAL_Number_tag();
}

extern bool CGAL_is_finite(float f);

extern bool CGAL_is_valid(float f);

inline
CGAL_io_Operator
CGAL_io_tag(float)
{
  return CGAL_io_Operator();
}



#endif // CGAL_FLOAT_H
