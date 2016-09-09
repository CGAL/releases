// Source: solve.h
// Author: Andreas.Fabri@sophia.inria.fr


#ifndef CGAL_SOLVE_H
#define CGAL_SOLVE_H

#include <CGAL/VectorC3.h>


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


template <class FT>
void CGAL_solve (const CGAL_VectorC3<FT> &v0,
                 const CGAL_VectorC3<FT> &v1,
                 const CGAL_VectorC3<FT> &v2,
                 const CGAL_VectorC3<FT> &d,
                 FT &alpha, FT &beta, FT &gamma)
{
  CGAL_solve(v0.x(), v0.y(), v0.z(),
             v1.x(), v1.y(), v1.z(),
             v2.x(), v2.y(), v2.z(),
             d.x(),  d.y(),  d.z(),
             alpha, beta, gamma);
}


#endif
