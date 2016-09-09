// ======================================================================
//
// Copyright (c) 1997  The CGAL Consortium

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
// file          : include/CGAL/Regular_triangulation_euclidean_traits_2.h
// package       : Triangulation (4.30)
// source        : $RCSfile: Regular_triangulation_euclidean_traits_2.h,v $
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1999/09/24 14:46:04 $
// author(s)     : Mariette Yvinec
//                 Sylvain Pion
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_REGULAR_TRIANGULATION_EUCLIDEAN_TRAITS_2_H
#define CGAL_REGULAR_TRIANGULATION_EUCLIDEAN_TRAITS_2_H

#include <CGAL/Triangulation_euclidean_traits_2.h>
#include <CGAL/Weighted_point.h>

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_CARTESIAN_H
#include <CGAL/predicates/Regular_triangulation_ftC2.h>
#endif

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/predicates/Regular_triangulation_rtH2.h>
#endif

CGAL_BEGIN_NAMESPACE 

template < class R, class W = typename R::FT>
class Regular_triangulation_euclidean_traits_2
  : public Triangulation_euclidean_traits_2<R>
{
public:
  typedef R                                     Rep;
  typedef W                                     Weight;
  typedef Triangulation_euclidean_traits_2 <R>  Traits;
  typedef typename Traits::Point                Bare_point;
  typedef Weighted_point <Bare_point, W>        Weighted_point;
  typedef Weighted_point                        Point;

  // power test for 2 dimension triangulation
  Oriented_side power_test(const Weighted_point &p,
			   const Weighted_point &q,
			   const Weighted_point &r,
			   const Weighted_point &t) const
  {
    CGAL_triangulation_precondition( ! collinear(p, q, r) );
    return CGAL::power_test(p, q, r, t);
  }

  // power test for 1 dimension triangulation
  Oriented_side power_test(const Weighted_point &p,
			   const Weighted_point &q,
			   const Weighted_point &t) const
  {
    CGAL_triangulation_precondition( collinear(p, q, t) );
    CGAL_triangulation_precondition( p.point() != q.point() );
    return CGAL::power_test(p, q, t);
  }
};

// #ifdef CGAL_CARTESIAN_H
// template < class FT, class Weight >
// inline
// Oriented_side
// power_test(const Weighted_point<Point_2<Cartesian<FT> >, Weight> &p,
//            const Weighted_point<Point_2<Cartesian<FT> >, Weight> &q,
//            const Weighted_point<Point_2<Cartesian<FT> >, Weight> &r,
//            const Weighted_point<Point_2<Cartesian<FT> >, Weight> &t)
// {
//     return power_testC2(p.x(), p.y(), FT(p.weight()),
//                         q.x(), q.y(), FT(q.weight()),
//                         r.x(), r.y(), FT(r.weight()),
//                         t.x(), t.y(), FT(t.weight()));
// }

// template < class FT, class Weight >
// inline
// Oriented_side
// power_test(const Weighted_point<Point_2<Cartesian<FT> >, Weight> &p,
//            const Weighted_point<Point_2<Cartesian<FT> >, Weight> &q,
//            const Weighted_point<Point_2<Cartesian<FT> >, Weight> &t)
// {
//     return power_testC2(p.x(), p.y(), FT(p.weight()),
//                         q.x(), q.y(), FT(q.weight()),
//                         t.x(), t.y(), FT(t.weight()));
// }
// #endif // CGAL_CARTESIAN_H

// #ifdef CGAL_HOMOGENEOUS_H
// template < class RT, class Weight >
// inline
// Oriented_side
// power_test(const Weighted_point<Point_2<Homogeneous<RT> >, Weight> &p,
//            const Weighted_point<Point_2<Homogeneous<RT> >, Weight> &q,
//            const Weighted_point<Point_2<Homogeneous<RT> >, Weight> &r,
//            const Weighted_point<Point_2<Homogeneous<RT> >, Weight> &t)
// {
//     return power_testH2(p.hx(), p.hy(), p.hw(), RT(p.weight()),
//                         q.hx(), q.hy(), q.hw(), RT(q.weight()),
//                         r.hx(), r.hy(), r.hw(), RT(r.weight()),
//                         t.hx(), t.hy(), t.hw(), RT(t.weight()));
// }

// template < class RT, class Weight >
// inline
// Oriented_side
// power_test(const Weighted_point<Point_2<Homogeneous<RT> >, Weight> &p,
//            const Weighted_point<Point_2<Homogeneous<RT> >, Weight> &q,
//            const Weighted_point<Point_2<Homogeneous<RT> >, Weight> &t)
// {
//     return power_testH2(p.hx(), p.hy(), p.hw(), RT(p.weight()),
//                         q.hx(), q.hy(), q.hw(), RT(q.weight()),
//                         t.hx(), t.hy(), t.hw(), RT(t.weight()));
// }
// #endif // CGAL_HOMOGENEOUS_H

template < class Point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Point, Weight> &p,
           const Weighted_point<Point, Weight> &q,
           const Weighted_point<Point, Weight> &r,
           const Weighted_point<Point, Weight> &t,
	   Cartesian_tag )
{
  typedef typename Point::FT  FT;
  return power_testC2(p.x(), p.y(), FT(p.weight()),
		      q.x(), q.y(), FT(q.weight()),
		      r.x(), r.y(), FT(r.weight()),
		      t.x(), t.y(), FT(t.weight()));
}

template < class Point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Point, Weight> &p,
           const Weighted_point<Point, Weight> &q,
           const Weighted_point<Point, Weight> &r,
           const Weighted_point<Point, Weight> &t,
	   Homogeneous_tag )
{
  typedef typename Point::RT  RT;
  return power_testH2(p.hx(), p.hy(), p.hw(), RT(p.weight()),
		      q.hx(), q.hy(), q.hw(), RT(q.weight()),
		      r.hx(), r.hy(), r.hw(), RT(r.weight()),
		      t.hx(), t.hy(), t.hw(), RT(t.weight()));
}

template < class Point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Point, Weight> &p,
           const Weighted_point<Point, Weight> &q,
           const Weighted_point<Point, Weight> &r,
           const Weighted_point<Point, Weight> &t)
{
  typedef typename Point::R::Rep_tag Tag;
  return power_test(p, q, r, t, Tag());
}
  
template < class Point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Point, Weight> &p,
           const Weighted_point<Point, Weight> &q,
           const Weighted_point<Point, Weight> &t,
	   Cartesian_tag )
{
    typedef typename Point::FT  FT;
    return power_testC2(p.x(), p.y(), FT(p.weight()),
                        q.x(), q.y(), FT(q.weight()),
                        t.x(), t.y(), FT(t.weight()));
}


template < class Point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Point, Weight> &p,
           const Weighted_point<Point, Weight> &q,
           const Weighted_point<Point, Weight> &t,
	   Homogeneous_tag )
{
   typedef typename Point::RT  RT;
    return power_testH2(p.hx(), p.hy(), p.hw(), RT(p.weight()),
                        q.hx(), q.hy(), q.hw(), RT(q.weight()),
                        t.hx(), t.hy(), t.hw(), RT(t.weight()));
}

template < class Point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Point, Weight> &p,
           const Weighted_point<Point, Weight> &q,
           const Weighted_point<Point, Weight> &t)
{
  typedef typename Point::R::Rep_tag Tag;
  return power_test(p, q, t, Tag());
}
CGAL_END_NAMESPACE

#endif // CGAL_REGULAR_TRIANGULATION_EUCLIDEAN_TRAITS_2_H
