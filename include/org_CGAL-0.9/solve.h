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


// Source: solve.h
// Author: Andreas Fabri


#ifndef CGAL_SOLVE_H
#define CGAL_SOLVE_H



template <class FT>
void CGAL_solve (const FT &a1, const FT &a2, const FT &a3,
                 const FT &b1, const FT &b2, const FT &b3,
                 const FT &c1, const FT &c2, const FT &c3,
                 const FT &d1, const FT &d2, const FT &d3,
                 FT &x, FT &y, FT &z)
{
  FT denom = b2*c1*a3-b1*c2*a3+c3*b1*a2+b3*c2*a1-c1*b3*a2-b2*c3*a1;

  x = - (b2*c3*d1-b2*c1*d3+c1*b3*d2+b1*c2*d3-c3*b1*d2-b3*c2*d1)/denom;

  z = (b2*d1*a3-b2*a1*d3+b1*a2*d3-b1*d2*a3-d1*b3*a2+a1*b3*d2)/denom;

  y = (a2*c3*d1-a2*c1*d3-c2*d1*a3+c2*a1*d3+d2*c1*a3-d2*c3*a1)/denom;
}


// this is for a parabola c1, c2, c3 are equal to 1
template <class FT>
void CGAL_solve_quadratic (const FT &a1, const FT &a2, const FT &a3,
                           const FT &b1, const FT &b2, const FT &b3,
                           const FT &d1, const FT &d2, const FT &d3,
                           FT &x, FT &y, FT &z)
{
  FT denom = b2*a3-b1*a3+b1*a2+b3*a1-b3*a2-b2*a1;

  x = - (b2*d1-b2*d3+b3*d2+b1*d3-b1*d2-b3*d1)/denom;

  z = (b2*d1*a3-b2*a1*d3+b1*a2*d3-b1*d2*a3-d1*b3*a2+a1*b3*d2)/denom;

  y = (a2*d1-a2*d3-d1*a3+a1*d3+d2*a3-d2*a1)/denom;
}



#endif // CGAL_SOLVE_H
