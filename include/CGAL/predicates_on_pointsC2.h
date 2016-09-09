// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/predicates_on_pointsC2.h
// author(s)     : Andreas Fabri,  Stefan Schirra
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_PREDICATES_ON_POINTSC2_H
#define CGAL_PREDICATES_ON_POINTSC2_H
#ifndef CGAL_CARTESIAN_CLASSES_H
#include <CGAL/cartesian_classes.h>
#endif // CGAL_CARTESIAN_CLASSES_H
#ifndef CGAL_POINTC2_H
#include <CGAL/PointC2.h>
#endif // CGAL_POINTC2_H

template < class FT >
inline
bool
CGAL_x_equal(const CGAL_PointC2<FT> &p,
             const CGAL_PointC2<FT> &q)
{
    return p.x() == q.x();
}


template < class FT >
inline
bool
CGAL_y_equal(const CGAL_PointC2<FT> &p,
             const CGAL_PointC2<FT> &q)
{
    return p.y() == q.y();
}


template < class FT >
inline
CGAL_Comparison_result
CGAL_compare_x(const CGAL_PointC2<FT> &p,
               const CGAL_PointC2<FT> &q)
{
    return CGAL_compare(p.x(), q.x());
}


template < class FT >
inline
CGAL_Comparison_result
CGAL_compare_y(const CGAL_PointC2<FT> &p,
               const CGAL_PointC2<FT> &q)
{
    return CGAL_compare(p.y(), q.y());
}

template < class FT >
CGAL_Comparison_result
CGAL_compare_deltax_deltay(const CGAL_PointC2<FT>& p,
                           const CGAL_PointC2<FT>& q,
                           const CGAL_PointC2<FT>& r,
                           const CGAL_PointC2<FT>& s)
{
    return CGAL_compare(CGAL_abs(p.x()-q.x()),
                        CGAL_abs(r.y()-s.y()));
}

template < class FT >
CGAL_Comparison_result
CGAL_compare_lexicographically_xy(const CGAL_PointC2<FT> &p,
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
inline
bool
CGAL_lexicographically_xy_smaller_or_equal(const CGAL_PointC2<FT> &p,
                                           const CGAL_PointC2<FT> &q)
{
    return ( !( CGAL_compare_lexicographically_xy(p,q) == CGAL_LARGER ) );
}

template < class FT >
inline
bool
CGAL_lexicographically_xy_smaller(const CGAL_PointC2<FT> &p,
                                  const CGAL_PointC2<FT> &q)
{
    return CGAL_compare_lexicographically_xy(p,q) == CGAL_SMALLER ;
}

template < class FT >
CGAL_Comparison_result
CGAL_compare_lexicographically_yx(const CGAL_PointC2<FT> &p,
                                  const CGAL_PointC2<FT> &q)
{
    const FT &px = p.x();
    const FT &qx = q.x();
    const FT &py = p.y();
    const FT &qy = q.y();

    if (py < qy){
        return CGAL_SMALLER;
    }

    if (py == qy){
        if (px < qx){
            return CGAL_SMALLER;
        }
        if (px == qx){
            return CGAL_EQUAL;
        }
    }
    return CGAL_LARGER;
}


template < class FT >
inline
bool
CGAL_lexicographically_yx_smaller_or_equal(const CGAL_PointC2<FT> &p,
                                           const CGAL_PointC2<FT> &q)
{
    return  !( CGAL_compare_lexicographically_yx(p,q) == CGAL_LARGER ) ;
}

template < class FT >
inline
bool
CGAL_lexicographically_yx_smaller(const CGAL_PointC2<FT> &p,
                                  const CGAL_PointC2<FT> &q)
{
    return CGAL_compare_lexicographically_yx(p,q) == CGAL_SMALLER ;
}

template < class FT >
CGAL_Orientation CGAL_orientation(const FT &px, const FT &py,
                                  const FT &qx, const FT &qy,
                                  const FT &rx, const FT &ry)
{
  FT d1 = (px-qx)*(qy-ry);
  FT d2 = (py-qy)*(qx-rx);
  return  (d1 < d2) ? CGAL_RIGHTTURN
                           : ((d1 == d2)? CGAL_COLLINEAR : CGAL_LEFTTURN);
}

template < class FT >
FT CGAL_area2(const FT &px, const FT &py,
              const FT &qx, const FT &qy,
              const FT &rx, const FT &ry)
{
  return  (px-qx)*(qy-ry) - (py-qy)*(qx-rx);
}

template < class FT >
inline
bool
CGAL_collinear(const CGAL_PointC2<FT> &p,
               const CGAL_PointC2<FT> &q,
               const CGAL_PointC2<FT> &r)
{
  return (CGAL_orientation(p.x(), p.y(), q.x(), q.y(), r.x(), r.y())
          == CGAL_COLLINEAR);
}



template < class FT >
inline
bool
CGAL_collinear_are_ordered_along_line(const CGAL_PointC2<FT> &p,
                                      const CGAL_PointC2<FT> &q,
                                      const CGAL_PointC2<FT> &r)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );

  if (p.x() != r.x())
  {
    return !( ((q.x() < p.x()) && q.x() < r.x()) ||
              ((r.x() < q.x()) && p.x() < q.x()) );
  }
  return !( ((q.y() < p.y()) && q.y() < r.y()) ||
            ((r.y() < q.y()) && p.y() < q.y()) );

}


template < class FT >
inline
bool
CGAL_are_ordered_along_line(const CGAL_PointC2<FT> &p,
                            const CGAL_PointC2<FT> &q,
                            const CGAL_PointC2<FT> &r)
{
  if (!CGAL_collinear(p, q, r))
    {
      return false;
    }
  return CGAL_collinear_are_ordered_along_line(p, q, r);

}

template < class FT >
inline
bool
CGAL_collinear_are_strictly_ordered_along_line(const CGAL_PointC2<FT> &p,
                                               const CGAL_PointC2<FT> &q,
                                               const CGAL_PointC2<FT> &r)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );

  if (p.x() != r.x())
    {
      return ((p.x() < q.x()) && q.x() < r.x()) ||
             ((r.x() < q.x()) && q.x() < p.x());
    }
  return ((p.y() < q.y()) && q.y() < r.y()) ||
         ((r.y() < q.y()) && q.y() < p.y());

}


template < class FT >
inline
bool
CGAL_are_strictly_ordered_along_line(const CGAL_PointC2<FT> &p,
                                     const CGAL_PointC2<FT> &q,
                                     const CGAL_PointC2<FT> &r)
{
  if (!CGAL_collinear(p, q, r))
    {
      return false;
    }
  return CGAL_collinear_are_strictly_ordered_along_line(p, q, r);

}

template < class FT >
inline
bool
CGAL_leftturn(const CGAL_PointC2<FT> &p,
              const CGAL_PointC2<FT> &q,
              const CGAL_PointC2<FT> &r)
{
  return (CGAL_orientation(p.x(), p.y(), q.x(), q.y(), r.x(), r.y())
          == CGAL_LEFTTURN );
}

template < class FT >
inline
bool
CGAL_rightturn(const CGAL_PointC2<FT> &p,
               const CGAL_PointC2<FT> &q,
               const CGAL_PointC2<FT> &r)
{
   return (CGAL_orientation(p.x(), p.y(), q.x(), q.y(), r.x(), r.y())
           == CGAL_RIGHTTURN);
}

template < class FT >
inline
bool
CGAL_rightturn(const CGAL_Origin &o,
               const CGAL_PointC2<FT> &q,
               const CGAL_PointC2<FT> &r)
{
   return (CGAL_orientation(FT(0), FT(0), q.x(), q.y(), r.x(), r.y())
           == CGAL_RIGHTTURN);
}

template < class FT >
inline
CGAL_Orientation
CGAL_orientation(const CGAL_PointC2<FT> &p,
                 const CGAL_PointC2<FT> &q,
                 const CGAL_PointC2<FT> &r)
{
    return CGAL_orientation(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template < class FT >
inline
FT
CGAL_area2(const CGAL_PointC2<FT> &p,
           const CGAL_PointC2<FT> &q,
           const CGAL_PointC2<FT> &r)
{
    return CGAL_area2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template <class FT >
CGAL_Oriented_side
 CGAL_side_of_oriented_circle(const FT &px,
                              const FT &py,
                              const FT &qx,
                              const FT &qy,
                              const FT &rx,
                              const FT &ry,
                              const FT &tx,
                              const FT &ty)
{
  FT FT0(0);
  FT FT1(1);
  FT det = CGAL_det4x4_by_formula(px, py, px*px + py*py, FT1,
                                  qx, qy, qx*qx + qy*qy, FT1,
                                  rx, ry, rx*rx + ry*ry, FT1,
                                  tx, ty, tx*tx + ty*ty, FT1);
  return (det<FT0) ? CGAL_ON_NEGATIVE_SIDE
           : ((det==FT0) ? CGAL_ON_ORIENTED_BOUNDARY : CGAL_ON_POSITIVE_SIDE);
}


template <class FT >
CGAL_Oriented_side
CGAL_side_of_oriented_circle(const CGAL_PointC2<FT> &p,
                             const CGAL_PointC2<FT> &q,
                             const CGAL_PointC2<FT> &r,
                             const CGAL_PointC2<FT> &test)
{
  FT FT0(0);
  FT FT1(1);
  const FT &px = p.x();
  const FT &py = p.y();
  const FT &qx = q.x();
  const FT &qy = q.y();
  const FT &rx = r.x();
  const FT &ry = r.y();
  const FT &tx = test.x();
  const FT &ty = test.y();

  FT det = CGAL_det4x4_by_formula(px, py, px*px + py*py, FT1,
                                  qx, qy, qx*qx + qy*qy, FT1,
                                  rx, ry, rx*rx + ry*ry, FT1,
                                  tx, ty, tx*tx + ty*ty, FT1);


  return (det<FT0) ? CGAL_ON_NEGATIVE_SIDE
            : ((det==FT0) ? CGAL_ON_ORIENTED_BOUNDARY : CGAL_ON_POSITIVE_SIDE);
}


template <class FT >
CGAL_Bounded_side
CGAL_side_of_bounded_circle(const CGAL_PointC2<FT> &p,
                            const CGAL_PointC2<FT> &q,
                            const CGAL_PointC2<FT> &r,
                            const CGAL_PointC2<FT> &test)
{
  FT FT0(0);
  FT FT1(1);
  const FT &px = p.x();
  const FT &py = p.y();
  const FT &qx = q.x();
  const FT &qy = q.y();
  const FT &rx = r.x();
  const FT &ry = r.y();
  const FT &tx = test.x();
  const FT &ty = test.y();

  FT det = CGAL_det4x4_by_formula(px, py, px*px + py*py, FT1,
                                  qx, qy, qx*qx + qy*qy, FT1,
                                  rx, ry, rx*rx + ry*ry, FT1,
                                  tx, ty, tx*tx + ty*ty, FT1);

  if (CGAL_orientation(px, py, qx, qy, rx, ry) == CGAL_LEFTTURN )
    {
      det = -det;
    }

  return (det<FT0) ? CGAL_ON_BOUNDED_SIDE
                  : ((det==FT0) ? CGAL_ON_BOUNDARY : CGAL_ON_UNBOUNDED_SIDE);
}


#endif  // CGAL_PREDICATES_ON_POINTSC2_H
