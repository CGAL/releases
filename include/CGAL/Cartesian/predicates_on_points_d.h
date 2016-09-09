// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Cartesian/predicates_on_points_d.h
// package       : Cd (1.1.1)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/12/07 18:53:29 $
// author(s)     : Herv� Br�nnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_PREDICATES_ON_POINTS_D_H
#define CGAL_CARTESIAN_PREDICATES_ON_POINTS_D_H

#include <CGAL/Cartesian/redefine_names_d.h>

#include <CGAL/Cartesian/Point_d.h>
#include <CGAL/constructions/kernel_ftCd.h>
#include <CGAL/predicates/kernel_ftCd.h>
#include <algorithm>
#include <utility>

CGAL_BEGIN_NAMESPACE

template < class R >
Comparison_result
compare_lexicographically_d(const PointCd<R CGAL_CTAG> &p,
                            const PointCd<R CGAL_CTAG> &q)
{
  CGAL_kernel_precondition( p.dimension()==q.dimension() );
  return Comparison_result( CGAL::sign(
     std::lexicographical_compare_3way(p.begin(),p.end(),q.begin(),q.end()) ));
}

template < class R >
bool
lexicographically_d_smaller_or_equal(const PointCd<R CGAL_CTAG> &p,
                                     const PointCd<R CGAL_CTAG> &q)
{
  CGAL_kernel_precondition( p.dimension()==q.dimension() );
  return !std::lexicographical_compare(q.begin(),q.end(),p.begin(),p.end());
}

template < class R >
bool
lexicographically_d_smaller(const PointCd<R CGAL_CTAG> &p,
                            const PointCd<R CGAL_CTAG> &q)
{
  CGAL_kernel_precondition( p.dimension()==q.dimension() );
  return std::lexicographical_compare(p.begin(),p.end(),q.begin(),q.end());
}

template < class R >
bool
x_equal(const PointCd<R CGAL_CTAG> &p,
        const PointCd<R CGAL_CTAG> &q,
	int i = 0)
{
  CGAL_kernel_precondition( p.dimension()==q.dimension() );
  CGAL_kernel_precondition( 0<=i && i<p.dimension() );
  return p[i] == q[i];
}

template < class R >
Comparison_result
compare_x(const PointCd<R CGAL_CTAG> &p,
          const PointCd<R CGAL_CTAG> &q,
	  int i)
{
  CGAL_kernel_precondition( p.dimension()==q.dimension() );
  CGAL_kernel_precondition( 0<=i && i<p.dimension() );
  return CGAL::compare(p[i], q[i]);
}

template < class R >
Comparison_result
compare_dominance(const PointCd<R CGAL_CTAG> &p,
                  const PointCd<R CGAL_CTAG> &q)
{
  return compare_dominanceCd(p.begin(), p.end(),
                             q.begin(), q.end());
}

template < class R >
Comparison_result
compare_submittance(const PointCd<R CGAL_CTAG> &p,
                    const PointCd<R CGAL_CTAG> &q)
{
  return compare_submittanceCd(p.begin(), p.end(),
                               q.begin(), q.end());
}

template < class R >
inline
bool
collinear(const PointCd<R CGAL_CTAG> &p,
          const PointCd<R CGAL_CTAG> &q,
          const PointCd<R CGAL_CTAG> &r)
{
  const VectorCd<R CGAL_CTAG> pq( q-p ); // verifies precondition on dimension
  const VectorCd<R CGAL_CTAG> pr( r-p );
  return pq == NULL_VECTOR
      || is_proportionalCd(pq.begin(), pq.end(), pr.begin());
}

template < class PointIterator >
inline
Orientation
orientation(const PointIterator &first, const PointIterator &last,
            const Cartesian_tag &) // the latter need to distinguish
{
  typedef typename std::iterator_traits<PointIterator>::value_type::R R;
  return orientationCd(first, last, R());
}

template < class PointIterator >
inline
bool
coplanar(const PointIterator &first, const PointIterator &last,
         const Cartesian_tag &) // the latter need to distinguish
{
  return orientation(first,last,Cartesian_tag()) == COPLANAR;
}

template < class R, class PointIterator >
inline
Orientation
coplanar_orientation(const PointCd<R CGAL_CTAG> &p,
   const PointIterator &first, const PointIterator &last,
   const PointCd<R CGAL_CTAG> &s)
{
  // TODO ????????????????????????????????????????????????????????????????
  // p,s and [first,last) supposed to be coplanar
  // s and [first,last) supposed to be affinely independent
  // tests whether p is on the same side of [first,last) as s
  // returns :                                                         
  // COPLANAR if pqr coplanar                                        
  // POSITIVE if [first,last)+p and [first,last)+s have the same orientation
  // NEGATIVE if [first,last)+p and [first,last)+s have opposite orientations
  // TODO
  return POSITIVE;
}

template <class PointIterator>
inline
bool
are_positive_oriented(const PointIterator &first, const PointIterator &last)
{
  return orientation(first, last) == POSITIVE;
}

template <class PointIterator>
inline
bool
are_negative_oriented(const PointIterator &first, const PointIterator &last)
{
  return orientation(first,last) == NEGATIVE;
}

template < class R >
inline
bool
are_ordered_along_line(const PointCd<R CGAL_CTAG> &p,
                       const PointCd<R CGAL_CTAG> &q,
                       const PointCd<R CGAL_CTAG> &r)
{
  return (collinear(p, q, r)) ? collinear_are_ordered_along_line(p, q, r)
                              : false;
}

template < class R >
inline
bool
collinear_are_ordered_along_line(const PointCd<R CGAL_CTAG> &p,
                                 const PointCd<R CGAL_CTAG> &q,
                                 const PointCd<R CGAL_CTAG> &r)
{
  CGAL_kernel_exactness_precondition( collinear(p, q, r) );
  return collinear_are_ordered_along_lineCd(p.begin(), p.end(),
                                            q.begin(), r.begin());
}

template < class R >
inline
bool
are_strictly_ordered_along_line(const PointCd<R CGAL_CTAG> &p,
                                const PointCd<R CGAL_CTAG> &q,
                                const PointCd<R CGAL_CTAG> &r)
{
  return (collinear(p, q, r))
         ? collinear_are_strictly_ordered_along_line(p, q, r)
         : false;
}

template < class R >
inline
bool
collinear_are_strictly_ordered_along_line(const PointCd<R CGAL_CTAG> &p,
                                          const PointCd<R CGAL_CTAG> &q,
                                          const PointCd<R CGAL_CTAG> &r)
{
  CGAL_kernel_exactness_precondition( collinear(p, q, r) );
  return collinear_are_strictly_ordered_along_lineCd(p.begin(), p.end(),
                                                     q.begin(), r.begin());
}

template < class R, class PointIterator >
inline
Bounded_side
side_of_bounded_simplex(const PointIterator &first, const PointIterator &last,
                        const PointCd<R CGAL_CTAG> &test)
{
  return side_of_bounded_simplexCd(first, last,
                                   test.begin(), test.end(), R());
}

template <class R, class PointIterator>
Oriented_side
side_of_oriented_sphere(const PointIterator &first,
                        const PointIterator &last,
                        const PointCd<R CGAL_CTAG> &test)
{
  return side_of_oriented_sphereCd(first, last,
                                   test.begin(),test.end(), R());
}

template <class R, class PointIterator>
Bounded_side
side_of_bounded_sphere(const PointIterator &first,
                       const PointIterator &last,
                       const PointCd<R CGAL_CTAG> &test)
{
  return side_of_bounded_sphereCd(first, last,
                                  test.begin(),test.end(), R());
}

CGAL_END_NAMESPACE

#endif  // CGAL_CARTESIAN_PREDICATES_ON_POINTS_2_H
