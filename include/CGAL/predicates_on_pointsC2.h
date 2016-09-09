// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/predicates_on_pointsC2.h
// package       : C2 (1.7)
// source        : web/predicates_on_pointsC2.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1999/01/04 06:54:16 $
// author(s)     : Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_POINTSC2_H
#define CGAL_PREDICATES_ON_POINTSC2_H
#ifndef CGAL_CARTESIAN_CLASSES_H
#include <CGAL/cartesian_classes.h>
#endif // CGAL_CARTESIAN_CLASSES_H
#ifndef CGAL_POINTC2_H
#include <CGAL/PointC2.h>
#endif // CGAL_POINTC2_H
#ifndef CGAL_PREDICATES_ON_FTC2_H
#include <CGAL/predicates_on_ftC2.h>
#endif // CGAL_PREDICATES_ON_FTC2_H


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
inline
CGAL_Comparison_result
CGAL_compare_deltax_deltay(const CGAL_PointC2<FT>& p,
                           const CGAL_PointC2<FT>& q,
                           const CGAL_PointC2<FT>& r,
                           const CGAL_PointC2<FT>& s)
{
    // return CGAL_compare(CGAL_abs(p.x()-q.x()), CGAL_abs(r.y()-s.y()));
    return CGAL_compare_deltax_deltayC2(p.x(), q.x(), r.y(), s.y());
}

template < class FT >
inline
CGAL_Comparison_result
CGAL_compare_lexicographically_xy(const CGAL_PointC2<FT> &p,
                                  const CGAL_PointC2<FT> &q)
{
  return CGAL_compare_lexicographically_xyC2(p.x(),p.y(),q.x(),q.y());
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
inline
CGAL_Comparison_result
CGAL_compare_lexicographically_yx(const CGAL_PointC2<FT> &p,
                                  const CGAL_PointC2<FT> &q)
{
  return CGAL_compare_lexicographically_xyC2(p.y(),p.x(),q.y(),q.x());
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
inline
CGAL_Orientation
CGAL_orientation(const CGAL_PointC2<FT> &p,
                 const CGAL_PointC2<FT> &q,
                 const CGAL_PointC2<FT> &r)
{
    return CGAL_orientationC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template < class FT >
inline
bool
CGAL_collinear(const CGAL_PointC2<FT> &p,
               const CGAL_PointC2<FT> &q,
               const CGAL_PointC2<FT> &r)
{
  return (CGAL_orientation(p,q,r) == CGAL_COLLINEAR);
}



template < class FT >
inline
bool
CGAL_collinear_are_ordered_along_line(const CGAL_PointC2<FT> &p,
                                      const CGAL_PointC2<FT> &q,
                                      const CGAL_PointC2<FT> &r)
{
  return CGAL_collinear_are_ordered_along_lineC2
             (p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}


template < class FT >
inline
bool
CGAL_are_ordered_along_line(const CGAL_PointC2<FT> &p,
                            const CGAL_PointC2<FT> &q,
                            const CGAL_PointC2<FT> &r)
{
  if (!CGAL_collinear(p, q, r)) { return false; }
  return CGAL_collinear_are_ordered_along_line(p, q, r);
}

template < class FT >
inline
bool
CGAL_collinear_are_strictly_ordered_along_line(const CGAL_PointC2<FT> &p,
                                               const CGAL_PointC2<FT> &q,
                                               const CGAL_PointC2<FT> &r)
{
  return CGAL_collinear_are_strictly_ordered_along_lineC2
               (p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}


template < class FT >
inline
bool
CGAL_are_strictly_ordered_along_line(const CGAL_PointC2<FT> &p,
                                     const CGAL_PointC2<FT> &q,
                                     const CGAL_PointC2<FT> &r)
{
  if (!CGAL_collinear(p, q, r)) { return false; }
  return CGAL_collinear_are_strictly_ordered_along_line(p, q, r);
}

template < class FT >
inline
bool
CGAL_leftturn(const CGAL_PointC2<FT> &p,
              const CGAL_PointC2<FT> &q,
              const CGAL_PointC2<FT> &r)
{
  return (CGAL_orientation(p,q,r) == CGAL_LEFTTURN );
}

template < class FT >
inline
bool
CGAL_leftturn(const CGAL_Origin &o,
               const CGAL_PointC2<FT> &q,
               const CGAL_PointC2<FT> &r)
{
   return (CGAL_orientationC2(FT(0), FT(0), q.x(), q.y(), r.x(), r.y())
           == CGAL_LEFTTURN );
}

template < class FT >
inline
bool
CGAL_rightturn(const CGAL_PointC2<FT> &p,
               const CGAL_PointC2<FT> &q,
               const CGAL_PointC2<FT> &r)
{
   return (CGAL_orientationC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y())
           == CGAL_RIGHTTURN);
}

template < class FT >
inline
bool
CGAL_rightturn(const CGAL_Origin &o,
               const CGAL_PointC2<FT> &q,
               const CGAL_PointC2<FT> &r)
{
   return (CGAL_orientationC2(FT(0), FT(0), q.x(), q.y(), r.x(), r.y())
           == CGAL_RIGHTTURN);
}

template <class FT >
inline
CGAL_Oriented_side
CGAL_side_of_oriented_circle(const CGAL_PointC2<FT> &p,
                             const CGAL_PointC2<FT> &q,
                             const CGAL_PointC2<FT> &r,
                             const CGAL_PointC2<FT> &test)
{
  return CGAL_side_of_oriented_circleC2
             (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),test.x(),test.y());
}


template <class FT >
inline
CGAL_Bounded_side
CGAL_side_of_bounded_circle(const CGAL_PointC2<FT> &p,
                            const CGAL_PointC2<FT> &q,
                            const CGAL_PointC2<FT> &r,
                            const CGAL_PointC2<FT> &test)
{
  return CGAL_side_of_bounded_circleC2
             (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),test.x(),test.y());
}


#endif  // CGAL_PREDICATES_ON_POINTSC2_H
