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
// file          : include/CGAL/Cartesian/predicates_on_points_2.h
// package       : C2 (3.3.11)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/11/05 22:30:01 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_PREDICATES_ON_POINTS_2_H
#define CGAL_CARTESIAN_PREDICATES_ON_POINTS_2_H

#include <CGAL/Cartesian/redefine_names_2.h>
#include <CGAL/Cartesian/Point_2.h>
#include <CGAL/predicates/kernel_ftC2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
bool
x_equal(const PointC2<R CGAL_CTAG> &p, const PointC2<R CGAL_CTAG> &q)
{
    return p.x() == q.x();
}

template < class R >
inline
bool
y_equal(const PointC2<R CGAL_CTAG> &p, const PointC2<R CGAL_CTAG> &q)
{
    return p.y() == q.y();
}

template < class R >
inline
Comparison_result
compare_x(const PointC2<R CGAL_CTAG> &p, const PointC2<R CGAL_CTAG> &q)
{
    return CGAL::compare(p.x(), q.x());
}

template < class R >
inline
Comparison_result
compare_y(const PointC2<R CGAL_CTAG> &p, const PointC2<R CGAL_CTAG> &q)
{
    return CGAL::compare(p.y(), q.y());
}

template < class R >
inline
Comparison_result
compare_deltax_deltay(const PointC2<R CGAL_CTAG>& p,
                      const PointC2<R CGAL_CTAG>& q,
                      const PointC2<R CGAL_CTAG>& r,
                      const PointC2<R CGAL_CTAG>& s)
{
    return compare_deltax_deltayC2(p.x(), q.x(), r.y(), s.y());
}

template < class R >
inline
Comparison_result
compare_lexicographically_xy(const PointC2<R CGAL_CTAG> &p,
                             const PointC2<R CGAL_CTAG> &q)
{
    return compare_lexicographically_xyC2(p.x(),p.y(),q.x(),q.y());
}

template < class R >
inline
bool
lexicographically_xy_smaller_or_equal(const PointC2<R CGAL_CTAG> &p,
                                      const PointC2<R CGAL_CTAG> &q)
{
    return compare_lexicographically_xy(p,q) != LARGER;
}

template < class R >
inline
bool
lexicographically_xy_larger_or_equal(const PointC2<R CGAL_CTAG> &p,
                                     const PointC2<R CGAL_CTAG> &q)
{
    return compare_lexicographically_xy(p,q) != SMALLER;
}

template < class R >
inline
bool
lexicographically_xy_smaller(const PointC2<R CGAL_CTAG> &p,
                             const PointC2<R CGAL_CTAG> &q)
{
    return compare_lexicographically_xy(p,q) == SMALLER;
}

template < class R >
inline
bool
lexicographically_xy_larger(const PointC2<R CGAL_CTAG> &p,
                            const PointC2<R CGAL_CTAG> &q)
{
    return compare_lexicographically_xy(p,q) == LARGER;
}

template < class R >
inline
Comparison_result
compare_lexicographically_yx(const PointC2<R CGAL_CTAG> &p,
                             const PointC2<R CGAL_CTAG> &q)
{
    return compare_lexicographically_xyC2(p.y(),p.x(),q.y(),q.x());
}

template < class R >
inline
bool
lexicographically_yx_smaller_or_equal(const PointC2<R CGAL_CTAG> &p,
                                      const PointC2<R CGAL_CTAG> &q)
{
    return compare_lexicographically_yx(p,q) != LARGER;
}

template < class R >
inline
bool
lexicographically_yx_larger_or_equal(const PointC2<R CGAL_CTAG> &p,
                                     const PointC2<R CGAL_CTAG> &q)
{
    return compare_lexicographically_yx(p,q) != SMALLER;
}

template < class R >
inline
bool
lexicographically_yx_smaller(const PointC2<R CGAL_CTAG> &p,
                             const PointC2<R CGAL_CTAG> &q)
{
    return compare_lexicographically_yx(p,q) == SMALLER;
}

template < class R >
inline
bool
lexicographically_yx_larger(const PointC2<R CGAL_CTAG> &p,
                            const PointC2<R CGAL_CTAG> &q)
{
    return compare_lexicographically_yx(p,q) == LARGER;
}

template < class R >
inline
Orientation
orientation(const PointC2<R CGAL_CTAG> &p,
            const PointC2<R CGAL_CTAG> &q,
            const PointC2<R CGAL_CTAG> &r)
{
    return orientationC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
}

template < class R >
inline
bool
collinear(const PointC2<R CGAL_CTAG> &p,
          const PointC2<R CGAL_CTAG> &q,
          const PointC2<R CGAL_CTAG> &r)
{
    return orientation(p,q,r) == COLLINEAR;
}

template < class R >
inline
bool
collinear_are_ordered_along_line(const PointC2<R CGAL_CTAG> &p,
                                 const PointC2<R CGAL_CTAG> &q,
                                 const PointC2<R CGAL_CTAG> &r)
{
    return collinear_are_ordered_along_lineC2
             (p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}

template < class R >
inline
bool
are_ordered_along_line(const PointC2<R CGAL_CTAG> &p,
                       const PointC2<R CGAL_CTAG> &q,
                       const PointC2<R CGAL_CTAG> &r)
{
    return collinear(p, q, r) && collinear_are_ordered_along_line(p, q, r);
}

template < class R >
inline
bool
collinear_are_strictly_ordered_along_line(const PointC2<R CGAL_CTAG> &p,
                                          const PointC2<R CGAL_CTAG> &q,
                                          const PointC2<R CGAL_CTAG> &r)
{
  return collinear_are_strictly_ordered_along_lineC2
               (p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}

template < class R >
inline
bool
are_strictly_ordered_along_line(const PointC2<R CGAL_CTAG> &p,
                                const PointC2<R CGAL_CTAG> &q,
                                const PointC2<R CGAL_CTAG> &r)
{
    return collinear(p, q, r) &&
	   collinear_are_strictly_ordered_along_line(p, q, r);
}

template < class R >
inline
bool
leftturn(const PointC2<R CGAL_CTAG> &p,
         const PointC2<R CGAL_CTAG> &q,
         const PointC2<R CGAL_CTAG> &r)
{
    return orientation(p,q,r) == LEFTTURN;
}

template < class R >
inline
bool
leftturn(const Origin &o,
         const PointC2<R CGAL_CTAG> &q,
         const PointC2<R CGAL_CTAG> &r)
{
   return orientationC2(FT(0), FT(0), q.x(), q.y(), r.x(), r.y()) == LEFTTURN;
}

template < class R >
inline
bool
rightturn(const PointC2<R CGAL_CTAG> &p,
          const PointC2<R CGAL_CTAG> &q,
          const PointC2<R CGAL_CTAG> &r)
{
   return orientationC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y()) == RIGHTTURN;
}

template < class R >
inline
bool
rightturn(const Origin &o,
          const PointC2<R CGAL_CTAG> &q,
          const PointC2<R CGAL_CTAG> &r)
{
   return orientationC2(FT(0), FT(0), q.x(), q.y(), r.x(), r.y()) == RIGHTTURN;
}

template <class R >
inline
Oriented_side
side_of_oriented_circle(const PointC2<R CGAL_CTAG> &p,
                        const PointC2<R CGAL_CTAG> &q,
                        const PointC2<R CGAL_CTAG> &r,
                        const PointC2<R CGAL_CTAG> &test)
{
  return side_of_oriented_circleC2
             (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),test.x(),test.y());
}

template <class R >
inline
Bounded_side
side_of_bounded_circle(const PointC2<R CGAL_CTAG> &p,
                       const PointC2<R CGAL_CTAG> &q,
                       const PointC2<R CGAL_CTAG> &r,
                       const PointC2<R CGAL_CTAG> &test)
{
  return side_of_bounded_circleC2
             (p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),test.x(),test.y());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_PREDICATES_ON_POINTS_2_H
