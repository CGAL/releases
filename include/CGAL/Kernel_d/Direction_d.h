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
// file          : include/CGAL/Kernel_d/Direction_d.h
// package       : Kernel_d (0.9.68)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2002/03/18 20:33:52 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_DIRECTION_D_H
#define CGAL_DIRECTION_D_H

CGAL_BEGIN_NAMESPACE

template <class pR>
class Direction_d : public pR::Direction_d_base
{ public:
  typedef typename pR::Direction_d_base Base;
  typedef Direction_d<pR>               Self;
  typedef pR R;
  typedef typename R::RT RT;
  typedef typename R::FT FT;
  typedef typename R::LA LA;
  typedef typename Base::Base_direction Base_direction;

  Direction_d(int d=0) : Base(d) {}
  Direction_d(int a, int b) : Base(a,b) {}
  Direction_d(const RT& a, const RT& b) : Base(a,b) {}
  Direction_d(int a, int b, int c) : Base(a,b,c) {}
  Direction_d(const RT& a, const RT& b, const RT& c) : Base(a,b,c) {}

#ifndef CGAL_SIMPLE_INTERFACE

  template <class InputIterator>
  Direction_d (int d, InputIterator first, InputIterator last)
    : Base(d, first, last) {}

#else
#define FIXDIRD(I) \
Direction_d (int d, I first, I last) : Base(d, first, last) {}

FIXDIRD(int*)
FIXDIRD(const int*)
FIXDIRD(RT*)
FIXDIRD(const RT*)
#undef FIXDIRD
#endif

  Direction_d(const Direction_d<R> &d) : Base(d) {}
  Direction_d(const Vector_d<R> &v) : Base(v) {}
  Direction_d(int d, Base_direction, int i) : 
    Base(d,Base_direction(),i) {}
  Direction_d(const Base& p) : Base(p) {}

  Self operator-() const { return Base::operator-(); }
  Vector_d<R> vector() const { return Base::vector(); }

  bool operator==(const Self& w) const
  { return Base::operator==(w); }
  bool operator!=(const Self& w) const
  { return Base::operator!=(w); }
};

CGAL_END_NAMESPACE
#endif //CGAL_DIRECTION_D_H
