// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Cartesian/predicates_on_points_3.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.17 $
// revision_date : $Date: 2002/01/23 17:59:16 $
// author(s)     : Andreas Fabri, Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_PREDICATES_ON_POINTS_3_H
#define CGAL_CARTESIAN_PREDICATES_ON_POINTS_3_H

#include <CGAL/predicates/kernel_ftC3.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
bool
x_equal(const PointC3<R> &p, const PointC3<R> &q)
{
  return p.x() == q.x();
}

template < class R >
inline
bool
y_equal(const PointC3<R> &p, const PointC3<R> &q)
{
  return p.y() == q.y();
}

template < class R >
inline
bool
z_equal(const PointC3<R> &p, const PointC3<R> &q)
{
  return p.z() == q.z();
}

template < class R >
inline
bool
less_x(const PointC3<R> &p, const PointC3<R> &q)
{
  return p.x() < q.x();
}

template < class R >
inline
bool
less_y(const PointC3<R> &p, const PointC3<R> &q)
{
  return p.y() < q.y();
}

template < class R >
inline
bool
less_z(const PointC3<R> &p, const PointC3<R> &q)
{
  return p.z() < q.z();
}

template < class R >
inline
Comparison_result
compare_x(const PointC3<R> &p, const PointC3<R> &q)
{
  return CGAL_NTS compare(p.x(), q.x());
}

template < class R >
inline
Comparison_result
compare_y(const PointC3<R> &p, const PointC3<R> &q)
{
  return CGAL_NTS compare(p.y(), q.y());
}

template < class R >
inline
Comparison_result
compare_z(const PointC3<R> &p, const PointC3<R> &q)
{
  return CGAL_NTS compare(p.z(), q.z());
}

template < class R >
inline
bool
equal_xy(const PointC3<R> &p, const PointC3<R> &q)
{
  return p.x() == q.x() && p.y() == q.y();
}

template < class R >
inline
bool
equal_xyz(const PointC3<R> &p, const PointC3<R> &q)
{
  return p.x() == q.x() && p.y() == q.y() && p.z() == q.z();
}

template < class R >
inline
Comparison_result
compare_xy(const PointC3<R> &p, 
	   const PointC3<R> &q)
{
  return compare_lexicographically_xyC2(p.x(), p.y(), q.x(), q.y()); 
}

template < class R >
inline
Comparison_result
compare_lexicographically_xy(const PointC3<R> &p, 
			     const PointC3<R> &q)
{
  return compare_lexicographically_xyC2(p.x(), p.y(), q.x(), q.y()); 
}

template < class R >
inline
bool
lexicographically_xy_smaller_or_equal(const PointC3<R> &p, 
				      const PointC3<R> &q)
{ 
  return compare_lexicographically_xy(p, q) != LARGER;
}

template < class R >
inline
bool
lexicographically_xy_smaller(const PointC3<R> &p, 
			     const PointC3<R> &q)
{ 
  return compare_lexicographically_xy(p, q) == SMALLER;
}

template < class R >
Comparison_result
compare_xyz(const PointC3<R> &p,
                              const PointC3<R> &q)
{
  return compare_lexicographically_xyzC3(p.x(), p.y(), p.z(),
                                         q.x(), q.y(), q.z());
}

template < class R >
Comparison_result
compare_lexicographically_xyz(const PointC3<R> &p,
                              const PointC3<R> &q)
{
  return compare_lexicographically_xyzC3(p.x(), p.y(), p.z(),
                                         q.x(), q.y(), q.z());
}

template < class R >
bool
lexicographically_xyz_smaller_or_equal(const PointC3<R> &p,
                                       const PointC3<R> &q)
{
  return compare_lexicographically_xyz(p, q) != LARGER;
}

template < class R >
bool
lexicographically_xyz_smaller(const PointC3<R> &p,
                              const PointC3<R> &q)
{
  return compare_lexicographically_xyz(p, q) == SMALLER;
}

template < class R >
inline
bool
strict_dominance(const PointC3<R> &p,
		 const PointC3<R> &q)
{
  return strict_dominanceC3(p.x(), p.y(), p.z(),
			    q.x(), q.y(), q.z());
}

template < class R >
inline
bool
dominance(const PointC3<R> &p,
	  const PointC3<R> &q)
{
  return dominanceC3(p.x(), p.y(), p.z(),
		     q.x(), q.y(), q.z());
}

template < class R >
inline
bool
collinear(const PointC3<R> &p,
          const PointC3<R> &q,
          const PointC3<R> &r)
{
  return collinearC3(p.x(), p.y(), p.z(),
                     q.x(), q.y(), q.z(),
                     r.x(), r.y(), r.z());
}

template < class R >
inline
Orientation
orientation(const PointC3<R> &p,
            const PointC3<R> &q,
            const PointC3<R> &r,
            const PointC3<R> &s)
{
  return orientationC3(p.x(), p.y(), p.z(),
                       q.x(), q.y(), q.z(),
                       r.x(), r.y(), r.z(),
                       s.x(), s.y(), s.z());
}

template < class R >
inline
Angle
angle(const PointC3<R> &p,
      const PointC3<R> &q,
      const PointC3<R> &r)
{
    return angleC3(p.x(), p.y(), p.z(),
	           q.x(), q.y(), q.z(),
		   r.x(), r.y(), r.z());
}

template < class R >
inline
bool
coplanar(const PointC3<R> &p,
         const PointC3<R> &q,
         const PointC3<R> &r,
         const PointC3<R> &s)
{
  return orientation(p, q, r, s) == COPLANAR;
}

template < class R >
inline
Orientation
coplanar_orientation(const PointC3<R> &p,
                     const PointC3<R> &q,
                     const PointC3<R> &r,
                     const PointC3<R> &s)
{
  // p,q,r,s supposed to be coplanar
  // p,q,r supposed to be non collinear
  // tests whether s is on the same side of p,q as r
  // returns :
  // COLLINEAR if pqr collinear
  // POSITIVE if qrp and qrs have the same orientation
  // NEGATIVE if qrp and qrs have opposite orientations
  CGAL_kernel_exactness_precondition( ! collinear(p, q, r) );
  CGAL_kernel_exactness_precondition( coplanar(p, q, r, s) );
  return coplanar_orientationC3(p.x(), p.y(), p.z(),
                                q.x(), q.y(), q.z(),
                                r.x(), r.y(), r.z(),
                                s.x(), s.y(), s.z());
}

template < class R >
inline
Orientation
coplanar_orientation(const PointC3<R> &p,
                     const PointC3<R> &q,
                     const PointC3<R> &r)
{
  // Returns an Orientation which is coherent for all (p,q,r) in a same plane.
  return coplanar_orientationC3(p.x(), p.y(), p.z(),
                                q.x(), q.y(), q.z(),
                                r.x(), r.y(), r.z());
}

template < class R >
inline
Bounded_side
coplanar_side_of_bounded_circle(const PointC3<R> &p,
                                const PointC3<R> &q,
                                const PointC3<R> &r,
                                const PointC3<R> &t)
{
  // p,q,r,t are supposed to be coplanar.
  // p,q,r determine an orientation of this plane (not collinear).
  // returns the equivalent of side_of_bounded_circle(p,q,r,t) in this plane
  CGAL_kernel_exactness_precondition( coplanar(p,q,r,t) );
  CGAL_kernel_exactness_precondition( !collinear(p,q,r) );
  return coplanar_side_of_bounded_circleC3(p.x(), p.y(), p.z(),
                                           q.x(), q.y(), q.z(),
                                           r.x(), r.y(), r.z(),
                                           t.x(), t.y(), t.z());
}

template < class R>
inline
bool
are_positive_oriented(const PointC3<R>& p,
                      const PointC3<R>& q,
                      const PointC3<R>& r,
                      const PointC3<R>& s)
{
  return orientation(p, q, r, s) == POSITIVE;
}

template < class R>
inline
bool
are_negative_oriented(const PointC3<R>& p,
                      const PointC3<R>& q,
                      const PointC3<R>& r,
                      const PointC3<R>& s)
{
  return orientation(p, q, r, s) == NEGATIVE;
}

template < class R >
inline
bool
are_ordered_along_line(const PointC3<R> &p,
                       const PointC3<R> &q,
                       const PointC3<R> &r)
{
  return collinear(p, q, r) ? collinear_are_ordered_along_line(p, q, r)
                            : false;
}

template < class R >
inline
bool
collinear_are_ordered_along_line(const PointC3<R> &p,
                                 const PointC3<R> &q,
                                 const PointC3<R> &r)
{
  CGAL_kernel_exactness_precondition( collinear(p, q, r) );
  return collinear_are_ordered_along_lineC3(p.x(), p.y(), p.z(),
                                            q.x(), q.y(), q.z(),
                                            r.x(), r.y(), r.z());
}

template < class R >
inline
bool
are_strictly_ordered_along_line(const PointC3<R> &p,
                                const PointC3<R> &q,
                                const PointC3<R> &r)
{
  return (collinear(p, q, r))
         ? collinear_are_strictly_ordered_along_line(p, q, r)
         : false;
}

template < class R >
inline
bool
collinear_are_strictly_ordered_along_line(const PointC3<R> &p,
                                          const PointC3<R> &q,
                                          const PointC3<R> &r)
{
  CGAL_kernel_exactness_precondition( collinear(p, q, r) );
  return collinear_are_strictly_ordered_along_lineC3(p.x(), p.y(), p.z(),
                                                     q.x(), q.y(), q.z(),
                                                     r.x(), r.y(), r.z());
}

template <class R >
inline
Oriented_side
side_of_oriented_sphere(const PointC3<R> &p,
                        const PointC3<R> &q,
                        const PointC3<R> &r,
                        const PointC3<R> &s,
                        const PointC3<R> &test)
{
  return side_of_oriented_sphereC3(p.x(), p.y(), p.z(),
                                   q.x(), q.y(), q.z(),
                                   r.x(), r.y(), r.z(),
                                   s.x(), s.y(), s.z(),
                                   test.x(), test.y(), test.z());
}

template <class R >
inline
Bounded_side
side_of_bounded_sphere(const PointC3<R> &p,
                       const PointC3<R> &q,
                       const PointC3<R> &test)
{
  return side_of_bounded_sphereC3(p.x(), p.y(), p.z(),
                                  q.x(), q.y(), q.z(),
                                  test.x(), test.y(), test.z());
}

template <class R >
inline
Bounded_side
side_of_bounded_sphere(const PointC3<R> &p,
                       const PointC3<R> &q,
                       const PointC3<R> &r,
                       const PointC3<R> &test)
{
  return side_of_bounded_sphereC3(p.x(), p.y(), p.z(),
                                  q.x(), q.y(), q.z(),
                                  r.x(), r.y(), r.z(),
                                  test.x(), test.y(), test.z());
}

template <class R >
inline
Bounded_side
side_of_bounded_sphere(const PointC3<R> &p,
                       const PointC3<R> &q,
                       const PointC3<R> &r,
                       const PointC3<R> &s,
                       const PointC3<R> &test)
{
  return side_of_bounded_sphereC3(p.x(), p.y(), p.z(),
                                  q.x(), q.y(), q.z(),
                                  r.x(), r.y(), r.z(),
                                  s.x(), s.y(), s.z(),
                                  test.x(), test.y(), test.z());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_PREDICATES_ON_POINTS_3_H
