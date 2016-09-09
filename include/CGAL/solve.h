//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: solve.h
// Author: Andreas.Fabri@sophia.inria.fr


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
