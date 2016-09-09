// ======================================================================
//
// Copyright (c) 2000,2001 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Kernel_d/Hyperplane_d.h
// package       : Kernel_d (0.9.47)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/06/06 11:11:50 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_HYPERPLANE_D_H
#define CGAL_HYPERPLANE_D_H

CGAL_BEGIN_NAMESPACE

template <class pR>
class Hyperplane_d : public pR::Hyperplane_d_base
{ public:
  typedef typename pR::Hyperplane_d_base Base;
  typedef Hyperplane_d<pR>               Self;
  typedef pR R;
  typedef typename R::RT RT;
  typedef typename R::FT FT;
  typedef typename R::LA LA;

  Hyperplane_d(int d=0) : Base(d) {}
  Hyperplane_d(int a, int b, int c) : Base(a,b,c) {}
  Hyperplane_d(const RT& a, const RT& b, const RT& c) : 
    Base(a,b,c) {}
  Hyperplane_d(int a, int b, int c, int d) : Base(a,b,c,d) {}
  Hyperplane_d(const RT& a, const RT& b, const RT& c, const RT& d) : 
    Base(a,b,c,d) {}

  Hyperplane_d(const Point_d<R>& p, const Direction_d<R>& dir) :
    Base(p,dir) {}

  Hyperplane_d(const Hyperplane_d<R> &h) : Base(h) {}
  Hyperplane_d(const Base& p) : Base(p) {}

#ifndef CGAL_SIMPLE_INTERFACE

  template <class InputIterator>
  Hyperplane_d(int d, InputIterator first, InputIterator last)
    : Base (d, first, last) {}

  template <class InputIterator>
  Hyperplane_d(int d, InputIterator first, InputIterator last,
               const RT& D)
    : Base (d, first, last, D) {}

  template <class ForwardIterator>
  Hyperplane_d(ForwardIterator first, ForwardIterator last, 
               const Point_d<R>& o, Oriented_side side = Oriented_side(0)) :
    Base(first,last,o,side) {}

#else
#define FIXHYPD(I) \
Hyperplane_d(int d, I first, I last) : Base (d,first,last) {} \
Hyperplane_d(int d, I first, I last, const RT& D) : Base (d,first,last,D) {}
#define FIXHYPDD(I) \
Hyperplane_d(I first, I last, const Point_d<R>& o, Oriented_side side = \
Oriented_side(0)) : Base(o.dimension()) \
{ construct_from_points(first,last,o,side); }

	     //Oriented_side(0)) : Base(first,last,o,side) {}

FIXHYPD(int*)
FIXHYPD(const int*)
FIXHYPD(RT*)
FIXHYPD(const RT*)
#undef FIXHYPD

#ifdef _MSC_VER
FIXHYPDD(typename std::vector< Point_d<R> >::iterator)
FIXHYPDD(typename std::vector< Point_d<R> >::const_iterator)
#endif // MSC

FIXHYPDD(Point_d<R>*)
FIXHYPDD(const Point_d<R>*)
#undef FIXHYPDD
#endif

  Vector_d<R> orthogonal_vector() const 
  { return Base::orthogonal_vector(); }
  Direction_d<R> orthogonal_direction() const 
  { return Base::orthogonal_direction(); }

  bool operator==(const Self& w) const
  { return Base::operator==(w); }
  bool operator!=(const Self& w) const
  { return Base::operator!=(w); }
};

CGAL_END_NAMESPACE
#endif //CGAL_HYPERPLANE_D_H
