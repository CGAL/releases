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


#ifndef CGAL_FUNCTIONS_ON_ENUMS_H
#define CGAL_FUNCTIONS_ON_ENUMS_H

#include <CGAL/enum.h>

inline
CGAL_Orientation
CGAL_opposite(const CGAL_Orientation &o)
{
  return (o == CGAL_COUNTERCLOCKWISE) ?
               CGAL_CLOCKWISE :
               (o == CGAL_CLOCKWISE) ?
                     CGAL_COUNTERCLOCKWISE :
                     CGAL_COLLINEAR;
}

inline
CGAL_Oriented_side
CGAL_opposite(const CGAL_Oriented_side &os)
{
  return (os == CGAL_ON_POSITIVE_SIDE) ?
                CGAL_ON_NEGATIVE_SIDE :
                (os == CGAL_ON_NEGATIVE_SIDE) ?
                      CGAL_ON_POSITIVE_SIDE :
                      CGAL_ON_ORIENTED_BOUNDARY;
}

inline
CGAL_Bounded_side
CGAL_opposite(const CGAL_Bounded_side &bs)
{
  return (bs == CGAL_ON_UNBOUNDED_SIDE) ?
                CGAL_ON_BOUNDED_SIDE :
                (bs == CGAL_ON_BOUNDED_SIDE) ?
                       CGAL_ON_UNBOUNDED_SIDE :
                       CGAL_ON_BOUNDARY;
}


#endif // CGAL_FUNCTIONS_ON_ENUMS_H
