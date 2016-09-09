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


// Source: Circle_repC2.h
// Author: Andreas Fabri

#ifndef CGAL__CIRCLEC2_H
#define CGAL__CIRCLEC2_H

template < class T >
class CGAL__CircleC2 : public CGAL_Rep
{
public:

  CGAL_PointC2<T>  center;
  T  squared_radius;
  CGAL_Orientation orientation;


  CGAL__CircleC2()
    {}

  CGAL__CircleC2(const CGAL_PointC2<T> & c,
                 const T & r,
                 const CGAL_Orientation &o)
    : center(c), squared_radius(r), orientation(o)
    {}

  ~CGAL__CircleC2()
    {}
};
#endif  // CGAL__CIRCLEC2_H
