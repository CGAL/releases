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
// file          : include/CGAL/predicates_on_pointsC3.h
// package       : C3 (2.1.5)
// source        : web/predicates_on_pointsC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:39 $
// author(s)     : Herve.Bronnimann
//                 Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_POINTSC3_H
#define CGAL_PREDICATES_ON_POINTSC3_H

#ifndef CGAL_PREDICATES_ON_FTC3_H
#include <CGAL/predicates_on_ftC3.h>
#endif // CGAL_PREDICATES_ON_FTC3_H

CGAL_BEGIN_NAMESPACE

template < class FT >
Comparison_result
compare_lexicographically_xyz(const PointC3<FT> &p, const PointC3<FT> &q)
{
  return compare_lexicographically_xyzC3(p.x(),p.y(),p.z(),
                                         q.x(),q.y(),q.z());
}

template < class FT >
bool
lexicographically_xyz_smaller_or_equal(const PointC3<FT> &p,
                                       const PointC3<FT> &q)
{
  return compare_lexicographically_xyz(p,q) != LARGER;
}

template < class FT >
bool
lexicographically_xyz_smaller(const PointC3<FT> &p, const PointC3<FT> &q)
{
  return compare_lexicographically_xyz(p,q) == SMALLER;
}

template < class FT >
inline
bool
x_equal(const PointC3<FT> &p, const PointC3<FT> &q)
{
  return p.x() == q.x();
}


template < class FT >
inline
bool
y_equal(const PointC3<FT> &p, const PointC3<FT> &q)
{
  return p.y() == q.y();
}

template < class FT >
inline
bool
z_equal(const PointC3<FT> &p, const PointC3<FT> &q)
{
  return p.z() == q.z();
}


template < class FT >
inline
Comparison_result
compare_x(const PointC3<FT> &p, const PointC3<FT> &q)
{
  return CGAL::compare(p.x(), q.x());
}


template < class FT >
inline
Comparison_result
compare_y(const PointC3<FT> &p, const PointC3<FT> &q)
{
 return CGAL::compare(p.y(), q.y());
}


template < class FT >
inline
Comparison_result
compare_z(const PointC3<FT> &p, const PointC3<FT> &q)
{
 return CGAL::compare(p.z(), q.z());
}

template < class FT >
bool collinear(const PointC3<FT> &p,
               const PointC3<FT> &q,
               const PointC3<FT> &r)
{
  return collinearC3(p.x(), p.y(), p.z(),
                     q.x(), q.y(), q.z(),
                     r.x(), r.y(), r.z());
}

template < class FT >
inline
Orientation
orientation(const PointC3<FT> &p,
            const PointC3<FT> &q,
            const PointC3<FT> &r,
            const PointC3<FT> &s)
{
  return orientationC3(p.x(), p.y(), p.z(),
                       q.x(), q.y(), q.z(),
                       r.x(), r.y(), r.z(),
                       s.x(), s.y(), s.z());
}

template < class FT >
inline
bool
coplanar(const PointC3<FT> &p,
         const PointC3<FT> &q,
         const PointC3<FT> &r,
         const PointC3<FT> &s)
{
  return orientation(p, q, r, s) == COLLINEAR;
}

template < class FT>
inline
bool
are_positive_oriented(const PointC3<FT>& p,
                      const PointC3<FT>& q,
                      const PointC3<FT>& r,
                      const PointC3<FT>& s)
{
  return orientation(p,q,r,s) == POSITIVE;
}

template < class FT>
inline
bool
are_negative_oriented(const PointC3<FT>& p,
                      const PointC3<FT>& q,
                      const PointC3<FT>& r,
                      const PointC3<FT>& s)
{
  return orientation(p,q,r,s) == NEGATIVE;
}

template < class FT >
inline
bool
are_ordered_along_line(const PointC3<FT> &p,
                       const PointC3<FT> &q,
                       const PointC3<FT> &r)
{
  return (collinear(p, q, r)) ? collinear_are_ordered_along_line(p, q, r)
                              : false;
}

template < class FT >
inline
bool
collinear_are_ordered_along_line(const PointC3<FT> &p,
                                 const PointC3<FT> &q,
                                 const PointC3<FT> &r)
{
  CGAL_kernel_exactness_precondition( collinear(p, q, r) );
  return collinear_are_ordered_along_lineC3(p.x(),p.y(),p.z(),
                                            q.x(),q.y(),q.z(),
                                            r.x(),r.y(),r.z());
}


template < class FT >
inline
bool
are_strictly_ordered_along_line(const PointC3<FT> &p,
                                const PointC3<FT> &q,
                                const PointC3<FT> &r)
{
  return (collinear(p, q, r))
         ? collinear_are_strictly_ordered_along_line(p, q, r)
         : false;
}


template < class FT >
inline
bool
collinear_are_strictly_ordered_along_line(const PointC3<FT> &p,
                                          const PointC3<FT> &q,
                                          const PointC3<FT> &r)
{
  CGAL_kernel_exactness_precondition( collinear(p, q, r) );
  return collinear_are_strictly_ordered_along_lineC3(p.x(),p.y(),p.z(),
                                                     q.x(),q.y(),q.z(),
                                                     r.x(),r.y(),r.z());
}


template <class FT >
Oriented_side
side_of_oriented_sphere(const PointC3<FT> &p,
                        const PointC3<FT> &q,
                        const PointC3<FT> &r,
                        const PointC3<FT> &s,
                        const PointC3<FT> &test)
{
  return side_of_oriented_sphereC3(p.x(),p.y(),p.z(),
                                   q.x(),q.y(),q.z(),
                                   r.x(),r.y(),r.z(),
                                   s.x(),s.y(),s.z(),
                                   test.x(),test.y(),test.z());
}


template <class FT >
Bounded_side
side_of_bounded_sphere(const PointC3<FT> &p,
                       const PointC3<FT> &q,
                       const PointC3<FT> &r,
                       const PointC3<FT> &s,
                       const PointC3<FT> &test)
{
  return side_of_bounded_sphereC3(p.x(),p.y(),p.z(),
                                  q.x(),q.y(),q.z(),
                                  r.x(),r.y(),r.z(),
                                  s.x(),s.y(),s.z(),
                                  test.x(),test.y(),test.z());
}


CGAL_END_NAMESPACE

#endif // CGAL_PREDICATES_ON_POINTSC3_H
