// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// file          : include/CGAL/predicates_on_pointsC3.h
// package       : C3 (1.6)
// source        : web/predicates_on_pointsC3.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1998/12/04 12:24:08 $
// author(s)     : Herve.Bronnimann
//                 Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_POINTSC3_H
#define CGAL_PREDICATES_ON_POINTSC3_H

#ifndef CGAL_PREDICATES_ON_FTC3_H
#include <CGAL/predicates_on_ftC3.h>
#endif // CGAL_PREDICATES_ON_FTC3_H

template < class FT >
CGAL_Comparison_result
CGAL_compare_lexicographically_xyz(const CGAL_PointC3<FT> &p,
                                   const CGAL_PointC3<FT> &q)
{
  return CGAL_compare_lexicographically_xyzC3(p.x(),p.y(),p.z(),
                                              q.x(),q.y(),q.z());
}

template < class FT >
bool CGAL_lexicographically_xyz_smaller_or_equal(const CGAL_PointC3<FT> &p,
                                                 const CGAL_PointC3<FT> &q)
{
  return ( !( CGAL_compare_lexicographically_xyz(p,q) == CGAL_LARGER ) );
}

template < class FT >
bool CGAL_lexicographically_xyz_smaller(const CGAL_PointC3<FT> &p,
                                        const CGAL_PointC3<FT> &q)
{
  return CGAL_compare_lexicographically_xyz(p,q) == CGAL_SMALLER ;
}

template < class FT >
inline
bool CGAL_x_equal(const CGAL_PointC3<FT> &p,
                  const CGAL_PointC3<FT> &q)
{
  return p.x() == q.x();
}


template < class FT >
inline
bool CGAL_y_equal(const CGAL_PointC3<FT> &p,
                  const CGAL_PointC3<FT> &q)
{
  return p.y() == q.y();
}

template < class FT >
inline
bool CGAL_z_equal(const CGAL_PointC3<FT> &p,
                  const CGAL_PointC3<FT> &q)
{
  return p.z() == q.z();
}


template < class FT >
inline
CGAL_Comparison_result CGAL_compare_x(const CGAL_PointC3<FT> &p,
                                      const CGAL_PointC3<FT> &q)
{
  return CGAL_compare(p.x(), q.x());
}


template < class FT >
inline
CGAL_Comparison_result CGAL_compare_y(const CGAL_PointC3<FT> &p,
                                      const CGAL_PointC3<FT> &q)
{
 return CGAL_compare(p.y(), q.y());
}


template < class FT >
inline
CGAL_Comparison_result CGAL_compare_z(const CGAL_PointC3<FT> &p,
                                      const CGAL_PointC3<FT> &q)
{
 return CGAL_compare(p.z(), q.z());
}

template < class FT >
bool CGAL_collinear(const CGAL_PointC3<FT> &p,
                    const CGAL_PointC3<FT> &q,
                    const CGAL_PointC3<FT> &r)
{
  return CGAL_collinearC3(p.x(), p.y(), p.z(),
                          q.x(), q.y(), q.z(),
                          r.x(), r.y(), r.z());
}

template < class FT >
inline
CGAL_Orientation
CGAL_orientation(const CGAL_PointC3<FT> &p,
                 const CGAL_PointC3<FT> &q,
                 const CGAL_PointC3<FT> &r,
                 const CGAL_PointC3<FT> &s)
{
  return CGAL_orientationC3(p.x(), p.y(), p.z(),
                            q.x(), q.y(), q.z(),
                            r.x(), r.y(), r.z(),
                            s.x(), s.y(), s.z());
}

template < class FT >
inline bool CGAL_coplanar(const CGAL_PointC3<FT> &p,
                          const CGAL_PointC3<FT> &q,
                          const CGAL_PointC3<FT> &r,
                          const CGAL_PointC3<FT> &s)
{
  return (CGAL_orientation(p, q, r, s) == CGAL_COLLINEAR);
}

template < class FT>
inline bool
CGAL_are_positive_oriented(const CGAL_PointC3<FT>& p,
                           const CGAL_PointC3<FT>& q,
                           const CGAL_PointC3<FT>& r,
                           const CGAL_PointC3<FT>& s)
{
  return (CGAL_orientation(p,q,r,s) == CGAL_POSITIVE);
}

template < class FT>
inline bool
CGAL_are_negative_oriented(const CGAL_PointC3<FT>& p,
                           const CGAL_PointC3<FT>& q,
                           const CGAL_PointC3<FT>& r,
                           const CGAL_PointC3<FT>& s)
{
  return (CGAL_orientation(p,q,r,s) == CGAL_NEGATIVE);
}

template < class FT >
inline bool CGAL_are_ordered_along_line(const CGAL_PointC3<FT> &p,
                         const CGAL_PointC3<FT> &q,
                         const CGAL_PointC3<FT> &r)
{
  if (!CGAL_collinear(p, q, r)) { return false; }
  return CGAL_collinear_are_ordered_along_line(p, q, r);
}

template < class FT >
inline bool CGAL_collinear_are_ordered_along_line(const CGAL_PointC3<FT> &p,
                                   const CGAL_PointC3<FT> &q,
                                   const CGAL_PointC3<FT> &r)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );
  return CGAL_collinear_are_ordered_along_lineC3(p.x(),p.y(),p.z(),
                                                 q.x(),q.y(),q.z(),
                                                 r.x(),r.y(),r.z());
}


template < class FT >
inline
 bool
CGAL_are_strictly_ordered_along_line(const CGAL_PointC3<FT> &p,
                                     const CGAL_PointC3<FT> &q,
                                     const CGAL_PointC3<FT> &r)
{
  if (!CGAL_collinear(p, q, r)) { return false; }
  return CGAL_collinear_are_strictly_ordered_along_line(p, q, r);
}


template < class FT >
inline
 bool
CGAL_collinear_are_strictly_ordered_along_line(const CGAL_PointC3<FT> &p,
                                               const CGAL_PointC3<FT> &q,
                                               const CGAL_PointC3<FT> &r)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );
  return CGAL_collinear_are_strictly_ordered_along_lineC3(p.x(),p.y(),p.z(),
                                                          q.x(),q.y(),q.z(),
                                                          r.x(),r.y(),r.z());
}


template <class FT >
CGAL_Oriented_side
CGAL_side_of_oriented_sphere(const CGAL_PointC3<FT> &p,
                             const CGAL_PointC3<FT> &q,
                             const CGAL_PointC3<FT> &r,
                             const CGAL_PointC3<FT> &s,
                             const CGAL_PointC3<FT> &test)
{
  return CGAL_side_of_oriented_sphereC3(p.x(),p.y(),p.z(),
                                        q.x(),q.y(),q.z(),
                                        r.x(),r.y(),r.z(),
                                        s.x(),s.y(),s.z(),
                                        test.x(),test.y(),test.z());
}


template <class FT >
CGAL_Bounded_side
CGAL_side_of_bounded_sphere(const CGAL_PointC3<FT> &p,
                            const CGAL_PointC3<FT> &q,
                            const CGAL_PointC3<FT> &r,
                            const CGAL_PointC3<FT> &s,
                            const CGAL_PointC3<FT> &test)
{
  return CGAL_side_of_bounded_sphereC3(p.x(),p.y(),p.z(),
                                       q.x(),q.y(),q.z(),
                                       r.x(),r.y(),r.z(),
                                       s.x(),s.y(),s.z(),
                                       test.x(),test.y(),test.z());

}


#endif // CGAL_PREDICATES_ON_POINTSC3_H
