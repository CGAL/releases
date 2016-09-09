// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Vector_2.h
// package       : _2 (3.19)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/06/27 14:51:36 $
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_VECTOR_2_H
#define CGAL_VECTOR_2_H

#include <CGAL/Point_2.h>
#include <CGAL/Direction_2.h>

CGAL_BEGIN_NAMESPACE

class Null_vector;

template <class T> class Quotient;

template <class R_>
class Vector_2 : public R_::Vector_2_base
{
public:
  typedef  R_                        R;
  typedef typename R::RT             RT;
  typedef typename R::FT             FT;
  typedef typename R::Point_2_base   RPoint_2;
  typedef typename R::Vector_2_base  RVector_2;

friend CGAL_FRIEND_INLINE
       CGAL::Vector_2<R>
       CGAL_SCOPE point_to_vector_conversion CGAL_NULL_TMPL_ARGS
                                        (const CGAL::Point_2<R> &p);

  Vector_2() {}

  Vector_2(const CGAL::Vector_2<R> &v)
      : RVector_2(static_cast<const RVector_2&>(v)) {}

  Vector_2(const CGAL::Point_2<R>& a, const CGAL::Point_2<R>& b)
      : RVector_2(static_cast<const RPoint_2&>(a),
	          static_cast<const RPoint_2&>(b) ) {}

  Vector_2(const RVector_2& v) : RVector_2(v) {}

  Vector_2(const Null_vector &v) : RVector_2(v) {}

  Vector_2(const RT &x, const RT &y) : RVector_2(x,y) {}

  Vector_2(const RT &x, const RT &y, const RT &w) : RVector_2(x,y,w) {}

  CGAL::Vector_2<R>
  operator+(const CGAL::Vector_2<R> &w) const
  {
      return static_cast<const RVector_2&>(*this) +
             static_cast<const RVector_2&>(w);
  }

  CGAL::Vector_2<R>
  operator-(const CGAL::Vector_2<R> &w) const
  {
      return static_cast<const RVector_2&>(*this) -
             static_cast<const RVector_2&>(w);
  }

  CGAL::Vector_2<R>
  operator-() const
  { return RVector_2::operator-(); }

  FT
  operator*(const CGAL::Vector_2<R> &w) const
  {
      return static_cast<const RVector_2&>(*this) *
             static_cast<const RVector_2&>(w);
  }

  CGAL::Vector_2<R>
  operator*(const RT &c) const
  { return c * static_cast<const RVector_2&>(*this); }

  CGAL::Vector_2<R>
  operator*(const Quotient<RT> &q) const
  {
      return (q.numerator() * static_cast<const RVector_2&>(*this))
      / q.denominator();
  }

  CGAL::Vector_2<R>
  operator/(const Quotient<RT> &q) const
  {
      return (q.denominator() * static_cast<const RVector_2&>(*this))
	  / q.numerator();
  }

  CGAL::Vector_2<R>
  operator/(const RT &c) const
  { return static_cast<const RVector_2&>(*this) / c; }

  CGAL::Direction_2<R>
  direction() const
  { return RVector_2::direction(); }

  CGAL::Vector_2<R>
  perpendicular(const Orientation &o) const
  { return RVector_2::perpendicular(o); }

  CGAL::Vector_2<R>
  transform(const CGAL::Aff_transformation_2<R> &t) const
  { return RVector_2::transform(t); }

private:
  Vector_2(const CGAL::Point_2<R> &p) : RVector_2(p) {}

  Vector_2(const CGAL::Direction_2<R> &d) : RVector_2(d) {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_VECTOR_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Vector_2<R> &v)
{
  typedef typename  R::Vector_2_base  RVector_2;
  return os << static_cast<const RVector_2&>(v);
}
#endif // CGAL_NO_OSTREAM_INSERT_VECTOR_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_VECTOR_2
template < class R >
std::istream &
operator>>(std::istream &is, Vector_2<R> &p)
{
  typedef typename  R::Vector_2_base  RVector_2;
  return is >> static_cast<RVector_2&>(p);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_VECTOR_2

CGAL_END_NAMESPACE

#endif // CGAL_VECTOR_2_H
