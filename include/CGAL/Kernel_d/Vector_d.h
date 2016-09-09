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
// file          : include/CGAL/Kernel_d/Vector_d.h
// package       : Kernel_d (0.9.47)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/06/13 15:47:53 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_VECTOR_D_H
#define CGAL_VECTOR_D_H

CGAL_BEGIN_NAMESPACE
 
template <class pR>
class Vector_d : public pR::Vector_d_base
{ public:
  typedef typename pR::Vector_d_base Base;
  typedef Vector_d<pR>               Self;
  typedef pR R;
  typedef typename R::RT RT;
  typedef typename R::FT FT;
  typedef typename R::LA LA;
  typedef typename Base::Base_vector Base_vector;

  Vector_d(int d=0) : Base(d) {}
  Vector_d(int d, Null_vector v) : Base(d,v) {}
  Vector_d(int a, int b, int c = 1) : Base(a,b,c) {}
  Vector_d(const RT& a, const RT& b, const RT& c = 1) :
    Base(a,b,c) {}
  Vector_d(int a, int b, int c, int d) : Base(a,b,c,d) {}
  Vector_d(const RT& a, const RT& b, const RT& c, const RT& d) :
    Base(a,b,c,d) {}
  Vector_d(int d, Base_vector, int i) :
    Base(d,Base_vector(),i) {}

#ifndef CGAL_SIMPLE_INTERFACE

  template <class InputIterator>
  Vector_d (int d, InputIterator first, InputIterator last)
    : Base (d, first, last) {}
  template <class InputIterator>
  Vector_d (int d, InputIterator first, InputIterator last, const RT& D)
    : Base (d, first, last, D) {}

#else
#define FIXVECD(I) \
Vector_d (int d, I first, I last) : Base (d, first, last) {} \
Vector_d(int d, I first, I last, const RT& D)  : Base (d, first, last, D) {}

FIXVECD(int*)
FIXVECD(const int*)
FIXVECD(RT*)
FIXVECD(const RT*)
#undef FIXVECD
#endif

  Vector_d(const Self& v) : Base(v) {}
  Vector_d(const Base& v) : Base(v) {}

  Direction_d<R> direction() const { return Base::direction(); }

  FT operator* (const Self& w) const
  { return Base::operator*(w); }
  Self operator+(const Self& w) const
  { return Base::operator+(w); }
  Self operator-(const Self& w) const
  { return Base::operator-(w); }
  Self operator-() const 
  { return Base::operator-(); }

  template <class NT> 
  Self operator/(const NT& n) const { return Base::operator/(n); }

  Self& operator+=(const Self& w) 
  { return static_cast<Self&>(Base::operator+=(w)); }
  Self& operator-=(const Self& w) 
  { return static_cast<Self&>(Base::operator-=(w)); }
  template <class NT> 
  Self& operator*=(const NT& n) 
  { return static_cast<Self&>(Base::operator*=(n)); }
  template <class NT> 
  Self& operator/=(const NT& n) 
  { return static_cast<Self&>(Base::operator/=(n)); }

  bool operator==(const Self& w) const
  { return Base::operator==(w); }
  bool operator!=(const Self& w) const
  { return Base::operator!=(w); }
  
};

template <class R> Point_d<R> 
operator+ (const Origin& o, const Vector_d<R>& v)
{ return Point_d<R>( o + static_cast<typename Vector_d<R>::Base>(v) ); }

template <class NT, class R>
Vector_d<R> operator*(const NT& n, const Vector_d<R>& v) 
{ return Vector_d<R>( n * static_cast<typename Vector_d<R>::Base>(v) ); }

CGAL_END_NAMESPACE
#endif //CGAL_VECTOR_D_H
