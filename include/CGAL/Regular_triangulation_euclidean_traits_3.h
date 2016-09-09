// ======================================================================
//
// Copyright (c) 1999  The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Regular_triangulation_euclidean_traits_3.h
// package       : Triangulation3 (1.42)
// revision      : $Revision: 1.13 $
// revision_date : $Date: 1999/11/02 10:50:21 $
// author(s)     : Sylvain Pion
//                 Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis 
//                 (Mariette Yvinec)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_REGULAR_TRIANGULATION_EUCLIDEAN_TRAITS_3_H
#define CGAL_REGULAR_TRIANGULATION_EUCLIDEAN_TRAITS_3_H

// This file is based on Regular_triangulation_euclidean_traits_2.h

#include <CGAL/Triangulation_geom_traits_3.h>
#include <CGAL/Weighted_point.h>

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_CARTESIAN_H
#include <CGAL/predicates/Regular_triangulation_ftC3.h>
#endif

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/predicates/Regular_triangulation_rtH3.h>
#endif

#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE 

template < class Repres, class Weight = CGAL_TYPENAME_MSVC_NULL Repres::RT >
class Regular_triangulation_euclidean_traits_3
  : public Triangulation_geom_traits_3<Repres>
{
public:
  typedef typename Triangulation_geom_traits_3<Repres>::Point Bare_point;
  typedef Weighted_point <Bare_point, Weight>   Weighted_point;
  typedef Weighted_point                        Point;

  // power test for non coplanar points
  Oriented_side power_test(const Weighted_point &p,
			   const Weighted_point &q,
			   const Weighted_point &r,
			   const Weighted_point &s,
			   const Weighted_point &t) const
    // Let S be the sphere orthogonal to weighted points p,q,r,s
    //
    // returns ON_ORIENTED_BOUNDARY if t is orthogonal to S
    // ON_NEGATIVE_SIDE if the angle between t and S is > pi/2
    // ON_POSITIVE_SIDE if the angle is < pi/2
    //
    // When all the weights are equal, the answer is exactly the same as
    // side_of_oriented_sphere(p,q,r,s,t)
  {
    CGAL_triangulation_precondition( ! coplanar(p, q, r, s) );
    return CGAL::power_test(p, q, r, s, t);
  }

  // power test for coplanar points
  Oriented_side power_test(const Weighted_point &p,
			   const Weighted_point &q,
			   const Weighted_point &r,
			   const Weighted_point &t) const
    // same as the previous test, for the circle orthogonal to p,q,r
  {
    CGAL_triangulation_precondition( ! collinear(p, q, r) );
    CGAL_triangulation_precondition( orientation(p,q,r,t) == COPLANAR );
    return CGAL::power_test(p, q, r, t);
  }

  // power test for collinear points
  Oriented_side power_test(const Weighted_point &p,
			   const Weighted_point &q,
			   const Weighted_point &t) const
  {
    CGAL_triangulation_precondition( collinear(p, q, t) );
    CGAL_triangulation_precondition( p.point() != q.point() );
    return CGAL::power_test(p, q, t);
  }
};

#ifdef CGAL_CARTESIAN_H
template < class pt, class Weight >
inline
Oriented_side
power_test(const Weighted_point<pt, Weight> &p,
           const Weighted_point<pt, Weight> &q,
           const Weighted_point<pt, Weight> &r,
           const Weighted_point<pt, Weight> &s,
           const Weighted_point<pt, Weight> &t,
	   Cartesian_tag)
{
  typedef typename pt::FT FT;
    return power_testC3(p.x(), p.y(), p.z(), FT(p.weight()),
                        q.x(), q.y(), q.z(), FT(q.weight()),
                        r.x(), r.y(), r.z(), FT(r.weight()),
                        s.x(), s.y(), s.z(), FT(s.weight()),
                        t.x(), t.y(), t.z(), FT(t.weight()));
}

template < class pt, class Weight >
inline
Oriented_side
power_test(const Weighted_point<pt, Weight> &p,
           const Weighted_point<pt, Weight> &q,
           const Weighted_point<pt, Weight> &r,
           const Weighted_point<pt, Weight> &t,
	   Cartesian_tag)
{
  typedef typename pt::FT FT;
    return power_testC3(p.x(), p.y(), p.z(), FT(p.weight()),
                        q.x(), q.y(), q.z(), FT(q.weight()),
                        r.x(), r.y(), r.z(), FT(r.weight()),
                        t.x(), t.y(), t.z(), FT(t.weight()));
}

template < class pt, class Weight >
inline
Oriented_side
power_test(const Weighted_point<pt, Weight> &p,
           const Weighted_point<pt, Weight> &q,
           const Weighted_point<pt, Weight> &t,
	   Cartesian_tag)
{
  typedef typename pt::FT FT;
    return power_testC3(p.x(), p.y(), p.z(), FT(p.weight()),
                        q.x(), q.y(), q.z(), FT(q.weight()),
                        t.x(), t.y(), t.z(), FT(t.weight()));
}
#endif // CGAL_CARTESIAN_H

#ifdef CGAL_HOMOGENEOUS_H
template < class pt, class Weight >
inline
Oriented_side
power_test(const Weighted_point<pt, Weight> &p,
           const Weighted_point<pt, Weight> &q,
           const Weighted_point<pt, Weight> &r,
           const Weighted_point<pt, Weight> &s,
           const Weighted_point<pt, Weight> &t,
	   Homogeneous_tag)
{
  typedef typename pt::RT RT;
    return power_testH3(p.hx(), p.hy(), p.hz(), p.hw(), RT(p.weight()),
                        q.hx(), q.hy(), q.hz(), q.hw(), RT(q.weight()),
                        r.hx(), r.hy(), r.hz(), r.hw(), RT(r.weight()),
                        s.hx(), s.hy(), s.hz(), s.hw(), RT(s.weight()),
                        t.hx(), t.hy(), t.hz(), t.hw(), RT(t.weight()));
}

// The 2 following call the cartesian version over FT, because an homogeneous
// special version would be boring to write.

template < class pt, class Weight >
inline
Oriented_side
power_test(const Weighted_point<pt, Weight> &p,
           const Weighted_point<pt, Weight> &q,
           const Weighted_point<pt, Weight> &r,
           const Weighted_point<pt, Weight> &t,
	   Homogeneous_tag)
{
    typedef typename pt::FT FT;
    return power_testC3(p.x(), p.y(), p.z(), FT(p.weight()),
                        q.x(), q.y(), q.z(), FT(q.weight()),
                        r.x(), r.y(), r.z(), FT(r.weight()),
                        t.x(), t.y(), t.z(), FT(t.weight()));
}

template < class pt, class Weight >
inline
Oriented_side
power_test(const Weighted_point<pt, Weight> &p,
           const Weighted_point<pt, Weight> &q,
           const Weighted_point<pt, Weight> &t,
	   Homogeneous_tag)
{
    typedef typename pt::FT FT;
    return power_testC3(p.x(), p.y(), p.z(), FT(p.weight()),
                        q.x(), q.y(), q.z(), FT(q.weight()),
                        t.x(), t.y(), t.z(), FT(t.weight()));
}
#endif // CGAL_HOMOGENEOUS_H

// Kludges for M$.

template < class pt, class Weight >
inline
Oriented_side
power_test(const Weighted_point<pt,Weight> &p,
	   const Weighted_point<pt,Weight> &q,
	   const Weighted_point<pt,Weight> &r,
	   const Weighted_point<pt,Weight> &s,
	   const Weighted_point<pt,Weight> &t)
{
  typedef typename pt::R::Rep_tag Tag;
  return( power_test(p,q,r,s,t, Tag()) );
}

template < class pt, class Weight >
inline
Oriented_side
power_test(const Weighted_point<pt,Weight> &p,
	   const Weighted_point<pt,Weight> &q,
	   const Weighted_point<pt,Weight> &r,
	   const Weighted_point<pt,Weight> &t)
{
  typedef typename pt::R::Rep_tag Tag;
  return( power_test(p,q,r,t, Tag()) );
}

template < class pt, class Weight >
inline
Oriented_side
power_test(const Weighted_point<pt,Weight> &p,
	   const Weighted_point<pt,Weight> &q,
	   const Weighted_point<pt,Weight> &t)
{
  typedef typename pt::R::Rep_tag Tag;
  return( power_test(p,q,t, Tag()) );
}

CGAL_END_NAMESPACE

#endif // CGAL_REGULAR_TRIANGULATION_EUCLIDEAN_TRAITS_3_H
