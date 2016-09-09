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

#ifndef CGAL_ENUM_H
#define CGAL_ENUM_H



enum  CGAL_Sign
      { CGAL_NEGATIVE   = -1,
        CGAL_ZERO,
        CGAL_POSITIVE
      };

typedef CGAL_Sign CGAL_Orientation;

const CGAL_Orientation  CGAL_LEFTTURN   = CGAL_POSITIVE;
const CGAL_Orientation  CGAL_RIGHTTURN  = CGAL_NEGATIVE;

const CGAL_Orientation  CGAL_CLOCKWISE  = CGAL_NEGATIVE;
const CGAL_Orientation  CGAL_COUNTERCLOCKWISE = CGAL_POSITIVE;

const CGAL_Orientation  CGAL_COLLINEAR  = CGAL_ZERO;
const CGAL_Orientation  CGAL_COPLANAR   = CGAL_ZERO;
const CGAL_Orientation  CGAL_DEGENERATE = CGAL_ZERO;




enum  CGAL_Oriented_side
      { CGAL_ON_NEGATIVE_SIDE = -1,
        CGAL_ON_ORIENTED_BOUNDARY,
        CGAL_ON_POSITIVE_SIDE
      };


enum  CGAL_Bounded_side
      { CGAL_ON_BOUNDED_SIDE = -1,
        CGAL_ON_BOUNDARY,
        CGAL_ON_UNBOUNDED_SIDE
      };



enum  CGAL_Comparison_result
      { CGAL_SMALLER   = -1,
        CGAL_EQUAL,
        CGAL_LARGER
      };




#include <CGAL/functions_on_enums.h>

#endif // CGAL_ENUM_H
