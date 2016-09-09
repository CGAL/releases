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

#ifndef BOPS_I_H
#define BOPS_I_H
 
 
#include <CGAL/basic.h> 
#include <CGAL/Cartesian.h> 
#include <CGAL/Homogeneous.h> 
#include <list.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Direction_2.h>

// _R should be something like CGAL_Cartesian<CGAL_Rational>
template <class _R> 
class Bops_default_I : public _R
{
 public:
  typedef _R R;
  typedef CGAL_Point_2<R> Point;
  typedef list<Point> Container;
  typedef CGAL_Segment_2<R> Segment;
  typedef CGAL_Triangle_2<R> Triangle;
  typedef CGAL_Iso_rectangle_2<R> Iso_rectangle;
  typedef CGAL_Polygon_2<R,Container> Polygon;
  typedef CGAL_Direction_2<R> Direction;
};
#endif
 
