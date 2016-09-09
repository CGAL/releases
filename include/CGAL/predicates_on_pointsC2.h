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

// Source: predicates_on_pointsC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PREDICATES_ON_POINTSC2_H
#define CGAL_PREDICATES_ON_POINTSC2_H
#include <CGAL/cartesian_classes.h>
#include <CGAL/PointC2.h>

template < class FT >
bool CGAL_x_equal(const CGAL_PointC2<FT> &p,
                  const CGAL_PointC2<FT> &q)
{
  return p.x() == q.x();
}

template < class FT >
bool CGAL_y_equal(const CGAL_PointC2<FT> &p,
                  const CGAL_PointC2<FT> &q)
{
  return p.y() == q.y();
}

template < class FT >
CGAL_Comparison_result CGAL_compare_x(const CGAL_PointC2<FT> &p,
                                      const CGAL_PointC2<FT> &q)
{
  return CGAL_compare(p.x(), q.x());
}

template < class FT >
CGAL_Comparison_result CGAL_compare_y(const CGAL_PointC2<FT> &p,
                                      const CGAL_PointC2<FT> &q)
{
 return CGAL_compare(p.y(), q.y());
}


template < class FT >
CGAL_Comparison_result CGAL_compare_lexicographically_xy(
                                                    const CGAL_PointC2<FT> &p,
                                                    const CGAL_PointC2<FT> &q)
{
  const FT &px = p.x();
  const FT &qx = q.x();
  const FT &py = p.y();
  const FT &qy = q.y();

  if (px < qx){
    return CGAL_SMALLER;
  }

 if (px == qx){
   if (py < qy){
     return CGAL_SMALLER;
   }
   if (py == qy){
     return CGAL_EQUAL;
   }
 }
 return CGAL_LARGER;
}


template < class FT >
bool CGAL_lexicographically_xy_smaller_or_equal(const CGAL_PointC2<FT> &p,
                                                const CGAL_PointC2<FT> &q)
{
  return ( !( CGAL_compare_lexicographically_xy(p,q) == CGAL_LARGER ) );
}

template < class FT >
bool CGAL_lexicographically_xy_smaller(const CGAL_PointC2<FT> &p,
                                       const CGAL_PointC2<FT> &q)
{
  return CGAL_compare_lexicographically_xy(p,q) == CGAL_SMALLER ;
}


template < class FT >
CGAL_Orientation CGAL_orientation(const FT &px, const FT &py,
                                  const FT &qx, const FT &qy,
                                  const FT &rx, const FT &ry)
{
  FT det = px * qy - py * qx +
           py * rx - px * ry +
           qx * ry - rx * qy ;
  return  (det == FT(0)) ? CGAL_COLLINEAR
                           : ((det > FT(0))? CGAL_LEFTTURN : CGAL_RIGHTTURN);
}

template < class FT >
FT CGAL_area2(const FT &px, const FT &py,
              const FT &qx, const FT &qy,
              const FT &rx, const FT &ry)
{
  return  px * qy - py * qx +
          py * rx - px * ry +
          qx * ry - rx * qy ;
}


template < class FT >
bool CGAL_collinear(const CGAL_PointC2<FT> &p,
                    const CGAL_PointC2<FT> &q,
                    const CGAL_PointC2<FT> &r)
{
  return (CGAL_orientation(p.x(), p.y(), q.x(), q.y(), r.x(), r.y())
          == CGAL_COLLINEAR);
}

template < class FT >
bool CGAL_between(const CGAL_PointC2<FT> &p,
                  const CGAL_PointC2<FT> &q,
                  const CGAL_PointC2<FT> &r)
{
  if (!CGAL_collinear(p, q, r))
    {
      return false;
    }
  return CGAL_collinear_between(p, q, r);

}

template < class FT >
inline bool CGAL_collinear_between(const CGAL_PointC2<FT> &p,
                                   const CGAL_PointC2<FT> &q,
                                   const CGAL_PointC2<FT> &r)
{
  CGAL_exactness_precondition( CGAL_collinear(p, q, r) );

  if (p.x() != r.x())
    {
      return ((p.x() <= q.x()) && q.x() <= r.x()) ||
             ((r.x() <= q.x()) && q.x() <= p.x());
    }
  return ((p.y() <= q.y()) && q.y() <= r.y()) ||
         ((r.y() <= q.y()) && q.y() <= p.y());

}

template < class FT >
inline bool CGAL_leftturn(const CGAL_PointC2<FT> &p,
                          const CGAL_PointC2<FT> &q,
                          const CGAL_PointC2<FT> &r)
{
  return (CGAL_orientation(p.x(), p.y(), q.x(), q.y(), r.x(), r.y())
          == CGAL_LEFTTURN );
}

template < class FT >
inline bool CGAL_rightturn(const CGAL_PointC2<FT> &p,
                           const CGAL_PointC2<FT> &q,
                           const CGAL_PointC2<FT> &r)
{
   return (CGAL_orientation(p.x(), p.y(), q.x(), q.y(), r.x(), r.y())
           == CGAL_RIGHTTURN);
}

template < class FT >
inline bool CGAL_rightturn(const CGAL_Origin &o,
                           const CGAL_PointC2<FT> &q,
                           const CGAL_PointC2<FT> &r)
{
   return (CGAL_orientation(FT(0), FT(0), q.x(), q.y(), r.x(), r.y())
           == CGAL_RIGHTTURN);
}

template < class FT >
inline CGAL_Orientation CGAL_orientation(const CGAL_PointC2<FT> &p,
                                         const CGAL_PointC2<FT> &q,
                                         const CGAL_PointC2<FT> &r)
{
  return CGAL_orientation(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template < class FT >
inline FT CGAL_area2(const CGAL_PointC2<FT> &p,
                     const CGAL_PointC2<FT> &q,
                     const CGAL_PointC2<FT> &r)
{
  return CGAL_area2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class FT >
CGAL_Oriented_side CGAL_side_of_oriented_circle(const CGAL_PointC2<FT> &p,
                                                const CGAL_PointC2<FT> &q,
                                                const CGAL_PointC2<FT> &r,
                                                const CGAL_PointC2<FT> &test)
{
  const FT &px = p.x();
  const FT &py = p.y();
  const FT &qx = q.x();
  const FT &qy = q.y();
  const FT &rx = r.x();
  const FT &ry = r.y();
  const FT &tx = test.x();
  const FT &ty = test.y();

  FT det = CGAL_det4x4_by_formula(px, py, px*px + py*py, FT(1),
                                  qx, qy, qx*qx + qy*qy, FT(1),
                                  rx, ry, rx*rx + ry*ry, FT(1),
                                  tx, ty, tx*tx + ty*ty, FT(1));

  return (det==0) ? CGAL_ON_ORIENTED_BOUNDARY
                  : ((det<0) ? CGAL_ON_NEGATIVE_SIDE : CGAL_ON_POSITIVE_SIDE);
}


template <class FT >
CGAL_Bounded_side CGAL_side_of_bounded_circle(const CGAL_PointC2<FT> &p,
                                              const CGAL_PointC2<FT> &q,
                                              const CGAL_PointC2<FT> &r,
                                              const CGAL_PointC2<FT> &test)
{
  const FT &px = p.x();
  const FT &py = p.y();
  const FT &qx = q.x();
  const FT &qy = q.y();
  const FT &rx = r.x();
  const FT &ry = r.y();
  const FT &tx = test.x();
  const FT &ty = test.y();

  FT det = CGAL_det4x4_by_formula(px, py, px*px + py*py, FT(1),
                                  qx, qy, qx*qx + qy*qy, FT(1),
                                  rx, ry, rx*rx + ry*ry, FT(1),
                                  tx, ty, tx*tx + ty*ty, FT(1));

  if (CGAL_orientation(px, py, qx, qy, rx, ry) == CGAL_LEFTTURN )
    {
      det = -det;
    }

  return (det==0) ? CGAL_ON_BOUNDARY
                  : ((det<0) ? CGAL_ON_BOUNDED_SIDE : CGAL_ON_UNBOUNDED_SIDE);
}


#endif  // CGAL_PREDICATES_ON_POINTSC2_H
