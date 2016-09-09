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
// file          : include/CGAL/Vector_3.h
// package       : _3 (3.23)
// revision      : $Revision: 1.9 $
// revision_date : $Date: 2001/06/27 14:49:54 $
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_VECTOR_3_H
#define CGAL_VECTOR_3_H

#include <CGAL/Point_3.h>
#include <CGAL/Direction_3.h>
#include <CGAL/Aff_transformation_3.h>

CGAL_BEGIN_NAMESPACE

template <class T> class Quotient;

template <class R_>
class Vector_3 : public R_::Vector_3_base
{
public:
  typedef          R_                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Point_3_base          RPoint_3;
  typedef typename R::Vector_3_base         RVector_3;

friend CGAL_FRIEND_INLINE
       CGAL::Vector_3<R>
       point_to_vector_conversion CGAL_NULL_TMPL_ARGS
                                       (const CGAL::Point_3<R>& p);

  Vector_3()
  {}
  Vector_3(const CGAL::Vector_3<R>& v)
    : RVector_3( static_cast<const RVector_3&>(v) )
  {}
  Vector_3(const CGAL::Point_3<R>& a, const CGAL::Point_3<R>& b)
    : RVector_3( static_cast<const RPoint_3&>(a),
	         static_cast<const RPoint_3&>(b) )
  {}
  Vector_3(const RVector_3&  v) : RVector_3(v)
  {}
  Vector_3(const Null_vector& v) : RVector_3(v)
  {}
  Vector_3(const RT& x, const RT& y, const RT& z)
    : RVector_3(x, y, z)
  {}
  Vector_3(const RT& x, const RT& y, const RT& z, const RT& w)
    : RVector_3(x, y, z, w)
  {}

  CGAL::Vector_3<R> operator+(const CGAL::Vector_3<R>& w) const
  {
      return static_cast<const RVector_3&>(*this) +
             static_cast<const RVector_3&>(w);
  }

  CGAL::Vector_3<R> operator-(const CGAL::Vector_3<R>& w) const
  {
      return static_cast<const RVector_3&>(*this) -
	     static_cast<const RVector_3&>(w);
  }

  CGAL::Vector_3<R> operator-() const
  { return RVector_3::operator-(); }

  FT operator*(const CGAL::Vector_3<R>& w) const
  {
      return static_cast<const RVector_3&>(*this) *
	     static_cast<const RVector_3&>(w);
  }

  CGAL::Vector_3<R> operator*(const RT& c) const
  { return c * static_cast<const RVector_3&>(*this) ; }

  CGAL::Vector_3<R> operator*(const Quotient<RT>& q) const
  {
    return (q.numerator() * static_cast<const RVector_3&>(*this)) /
            q.denominator();
  }

  CGAL::Vector_3<R> operator/(const Quotient<RT>& q) const
  {
    return (q.denominator() * static_cast<const RVector_3&>(*this)) /
            q.numerator();
  }

  CGAL::Vector_3<R> operator/(const RT& c) const
  { return static_cast<const RVector_3&>(*this) / c; }

  CGAL::Direction_3<R> direction() const
  { return RVector_3::direction(); }

  CGAL::Vector_3<R> transform(const CGAL::Aff_transformation_3<R>& t) const
  { return RVector_3::transform(t); }

private:
  Vector_3(const CGAL::Point_3<R>& p) : RVector_3(p)
  {}
  Vector_3(const CGAL::Direction_3<R>& d) : RVector_3(d)
  {}
};

template<class R>
inline
Vector_3<R>
cross_product(const Vector_3<R>& v, const Vector_3<R>& w)
{
  typedef typename  R::Vector_3_base  RVector_3;
  return cross_product(static_cast<const RVector_3&>(v),
	               static_cast<const RVector_3&>(w));
}

#ifndef CGAL_NO_OSTREAM_INSERT_VECTOR_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Vector_3<R>& v)
{
  typedef typename  R::Vector_3_base  RVector_3;
  return os << static_cast<const RVector_3&>(v);
}
#endif // CGAL_NO_OSTREAM_INSERT_VECTOR_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_VECTOR_3
template < class R >
std::istream&
operator>>(std::istream& is, Vector_3<R>& p)
{
  typedef typename  R::Vector_3_base  RVector_3;
  return is >> static_cast<RVector_3&>(p);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_VECTOR_3

CGAL_END_NAMESPACE

#endif // CGAL_VECTOR_3_H
