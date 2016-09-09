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
// file          : include/CGAL/Aff_transformation_2.h
// package       : _2 (3.32)
// revision      : $Revision: 1.9 $
// revision_date : $Date: 2002/01/23 12:28:29 $
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

CGAL_BEGIN_NAMESPACE

template <class R_>
class Aff_transformation_2 : public R_::Kernel_base::Aff_transformation_2
{
  typedef typename R_::RT                    RT;
  typedef typename R_::FT                    FT;
  typedef typename R_::Line_2                Line_2;
  typedef typename R_::Direction_2           Direction_2;
  typedef typename R_::Vector_2              Vector_2;
  typedef typename R_::Kernel_base::Aff_transformation_2 RAff_transformation_2;
public:
  typedef  R_                               R;

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

  Aff_transformation_2(const Translation tag, const Vector_2 &v)
    : RAff_transformation_2(tag, v)
  {}

  // Rational Rotation:
  Aff_transformation_2(const Rotation tag,
                       const Direction_2 &d,
                       const RT &num,
                       const RT &den = RT(1))
    : RAff_transformation_2(tag, d, num, den)
  {}

  Aff_transformation_2(const Rotation tag,
                       const RT &sin,
                       const RT &cos,
                       const RT &den = RT(1))
    : RAff_transformation_2(tag, sin, cos, den)
  {}

  Aff_transformation_2(const Reflection tag, const Line_2& l )
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
};

#ifndef CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const CGAL::Aff_transformation_2<R> &t)
{
  typedef typename R::Kernel_base::Aff_transformation_2  RAff_transformation_2;
  return os << static_cast<const RAff_transformation_2&>(t);
}
#endif // CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_2
template < class R >
std::istream &
operator>>(std::istream &is, CGAL::Aff_transformation_2<R> &t)
{
  typedef typename R::Kernel_base::Aff_transformation_2  RAff_transformation_2;
  return is >> static_cast<RAff_transformation_2&>(t);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_2

CGAL_END_NAMESPACE

#endif // CGAL_AFF_TRANSFORMATION_2_H
