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
// file          : include/CGAL/Aff_transformation_2.h
// package       : _2 (3.19)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/06/27 14:51:27 $
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_AFF_TRANSFORMATION_2_H
#define CGAL_AFF_TRANSFORMATION_2_H

#include <CGAL/Line_2.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class Aff_transformation_2 : public R_::Aff_transformation_2_base
{
public:
  typedef  R_                               R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Line_2_base  RLine_2;
  typedef typename R::Direction_2_base  RDirection_2;
  typedef typename R::Aff_transformation_2_base  RAff_transformation_2;

  Aff_transformation_2()
    : RAff_transformation_2()
  {}

  Aff_transformation_2(const CGAL::Aff_transformation_2<R> &t)
    : RAff_transformation_2(t)
  {}

  Aff_transformation_2(const RAff_transformation_2& t)
    : RAff_transformation_2(t)
  {}

  Aff_transformation_2(const Identity_transformation tag)
    : RAff_transformation_2(tag)
  {}

  Aff_transformation_2(const Translation tag, const CGAL::Vector_2<R> &v)
    : RAff_transformation_2(tag, v)
  {}

  // Rational Rotation:
  Aff_transformation_2(const Rotation tag,
                       const CGAL::Direction_2<R> &d,
                       const RT &num,
                       const RT &den = RT(1))
    : RAff_transformation_2(tag, RDirection_2(d), num, den)
  {}

  Aff_transformation_2(const Rotation tag,
                       const RT &sin,
                       const RT &cos,
                       const RT &den = RT(1))
    : RAff_transformation_2(tag, sin, cos, den)
  {}

  Aff_transformation_2(const Reflection tag, const CGAL::Line_2<R>& l )
    : RAff_transformation_2(tag, l)
  {}

  Aff_transformation_2(const Scaling tag,
                       const RT &s,
                       const RT &w= RT(1))
    : RAff_transformation_2(tag, s, w)
  {}

  // The general case:
  Aff_transformation_2(const RT & m11,
                       const RT & m12,
                       const RT & m13,

                       const RT & m21,
                       const RT & m22,
                       const RT & m23,

                       const RT &w= RT(1))
    : RAff_transformation_2(m11, m12, m13,
                            m21, m22, m23,
                                      w)
  {}

  Aff_transformation_2(const RT & m11, const RT & m12,
                       const RT & m21, const RT & m22,
                       const RT &w = RT(1))
    : RAff_transformation_2(m11, m12,
                            m21, m22,
                                      w)
  {}

  CGAL::Point_2<R>     transform(const CGAL::Point_2<R> &p) const
                      { return RAff_transformation_2::transform(p); }

  CGAL::Point_2<R>     operator()(const CGAL::Point_2<R> &p) const
                      { return transform(p); }

  CGAL::Vector_2<R>    transform(const CGAL::Vector_2<R> &v) const
                      { return RAff_transformation_2::transform(v); }

  CGAL::Vector_2<R>    operator()(const CGAL::Vector_2<R> &v) const
                      { return transform(v); }

  CGAL::Direction_2<R> transform(const CGAL::Direction_2<R> &d) const
                      { return RAff_transformation_2::transform(d); }

  CGAL::Direction_2<R> operator()(const CGAL::Direction_2<R> &d) const
                      { return transform(d); }

  CGAL::Line_2<R>      transform(const CGAL::Line_2<R> &l) const
  {
                        return
      ((const RLine_2&)l).transform((const RAff_transformation_2&)(*this));
  }

  CGAL::Line_2<R>      operator()(const CGAL::Line_2<R> &l) const
                      { return transform(l); }


  CGAL::Aff_transformation_2<R>
                      inverse() const
                      { return RAff_transformation_2::inverse(); }

  CGAL::Aff_transformation_2<R>
                      operator*(const CGAL::Aff_transformation_2<R> &t) const
                      { return RAff_transformation_2::operator*(t); }
};

#ifndef CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const CGAL::Aff_transformation_2<R> &t)
{
  typedef typename  R::Aff_transformation_2_base  RAff_transformation_2;
  return os << static_cast<const RAff_transformation_2&>(t);
}
#endif // CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_2
template < class R >
std::istream &
operator>>(std::istream &is, CGAL::Aff_transformation_2<R> &t)
{
  typedef typename  R::Aff_transformation_2_base  RAff_transformation_2;
  return is >> static_cast<RAff_transformation_2&>(t);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_2

CGAL_END_NAMESPACE

#endif // CGAL_AFF_TRANSFORMATION_2_H
