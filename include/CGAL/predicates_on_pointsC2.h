// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/predicates_on_pointsC2.h
// package       : C2 (2.1.4)
// source        : web/predicates_on_pointsC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:35 $
// author(s)     : Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
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

CGAL_BEGIN_NAMESPACE

template < class FT >
inline
bool
x_equal(const PointC2<FT> &p, const PointC2<FT> &q)
{
    return p.x() == q.x();
}


template < class FT >
inline
bool
y_equal(const PointC2<FT> &p, const PointC2<FT> &q)
{
    return p.y() == q.y();
}


template < class FT >
inline
Comparison_result
compare_x(const PointC2<FT> &p, const PointC2<FT> &q)
{
    return CGAL::compare(p.x(), q.x());
}


template < class FT >
inline
Comparison_result
compare_y(const PointC2<FT> &p, const PointC2<FT> &q)
{
    return CGAL::compare(p.y(), q.y());
}

template < class FT >
inline
Comparison_result
compare_deltax_deltay(const PointC2<FT>& p,
                      const PointC2<FT>& q,
                      const PointC2<FT>& r,
                      const PointC2<FT>& s)
{
  return compare_deltax_deltayC2(p.x(), q.x(), r.y(), s.y());
}

template < class FT >
inline
Comparison_result
compare_lexicographically_xy(const PointC2<FT> &p,
                             const PointC2<FT> &q)
{
  return compare_lexicographically_xyC2(p.x(),p.y(),q.x(),q.y());
}

template < class FT >
inline
bool
lexicographically_xy_smaller_or_equal(const PointC2<FT> &p,
                                      const PointC2<FT> &q)
{
  return ( !( compare_lexicographically_xy(p,q) == LARGER ) );
}

template < class FT >
inline
bool
lexicographically_xy_smaller(const PointC2<FT> &p,
                             const PointC2<FT> &q)
{
  return compare_lexicographically_xy(p,q) == SMALLER ;
}

template < class FT >
inline
Comparison_result
compare_lexicographically_yx(const PointC2<FT> &p,
                             const PointC2<FT> &q)
{
  return compare_lexicographically_xyC2(p.y(),p.x(),q.y(),q.x());
}


template < class FT >
inline
bool
lexicographically_yx_smaller_or_equal(const PointC2<FT> &p,
                                      const PointC2<FT> &q)
{
    return  !( compare_lexicographically_yx(p,q) == LARGER ) ;
}

template < class FT >
inline
bool
lexicographically_yx_smaller(const PointC2<FT> &p,
                             const PointC2<FT> &q)
{
    return compare_lexicographically_yx(p,q) == SMALLER ;
}

template < class FT >
inline
Orientation
orientation(const PointC2<FT> &p,
            const PointC2<FT> &q,
            const PointC2<FT> &r)
{
    return orientationC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template < class FT >
inline
bool
collinear(const PointC2<FT> &p,
               const PointC2<FT> &q,
               const PointC2<FT> &r)
{
  return (orientation(p,q,r) == COLLINEAR);
}



template < class FT >
inline
bool
collinear_are_ordered_along_line(const PointC2<FT> &p,
                                 const PointC2<FT> &q,
                                 const PointC2<FT> &r)
{
  return collinear_are_ordered_along_lineC2
             (p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}


template < class FT >
inline
bool
are_ordered_along_line(const PointC2<FT> &p,
                       const PointC2<FT> &q,
                       const PointC2<FT> &r)
{
  if (!collinear(p, q, r)) { return false; }
  return collinear_are_ordered_along_line(p, q, r);
}

template < class FT >
inline
bool
collinear_are_strictly_ordered_along_line(const PointC2<FT> &p,
                                          const PointC2<FT> &q,
                                          const PointC2<FT> &r)
{
  return collinear_are_strictly_ordered_along_lineC2
               (p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}


template < class FT >
inline
bool
are_strictly_ordered_along_line(const PointC2<FT> &p,
                                const PointC2<FT> &q,
                                const PointC2<FT> &r)
{
  if (!collinear(p, q, r)) { return false; }
  return collinear_are_strictly_ordered_along_line(p, q, r);
}

template < class FT >
inline
bool
leftturn(const PointC2<FT> &p,
         const PointC2<FT> &q,
         const PointC2<FT> &r)
{
  return (orientation(p,q,r) == LEFTTURN );
}

template < class FT >
inline
bool
leftturn(const Origin &o,
         const PointC2<FT> &q,
         const PointC2<FT> &r)
{
   return (orientationC2(FT(0), FT(0), q.x(), q.y(), r.x(), r.y())
           == LEFTTURN );
}

template < class FT >
inline
bool
rightturn(const PointC2<FT> &p,
          const PointC2<FT> &q,
          const PointC2<FT> &r)
{
   return (orientationC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y())
           == RIGHTTURN);
}

template < class FT >
inline
bool
rightturn(const Origin &o,
          const PointC2<FT> &q,
          const PointC2<FT> &r)
{
   return (orientationC2(FT(0), FT(0), q.x(), q.y(), r.x(), r.y())
           == RIGHTTURN);
}

template <class FT >
inline
Oriented_side
side_of_oriented_circle(const PointC2<FT> &p,
                        const PointC2<FT> &q,
                        const PointC2<FT> &r,
                        const PointC2<FT> &test)
{
  return side_of_oriented_circleC2
             (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),test.x(),test.y());
}


template <class FT >
inline
Bounded_side
side_of_bounded_circle(const PointC2<FT> &p,
                       const PointC2<FT> &q,
                       const PointC2<FT> &r,
                       const PointC2<FT> &test)
{
  return side_of_bounded_circleC2
             (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),test.x(),test.y());
}


CGAL_END_NAMESPACE

#endif  // CGAL_PREDICATES_ON_POINTSC2_H
