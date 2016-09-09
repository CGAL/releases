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
// file          : include/CGAL/Vector_3.h
// package       : _3 (3.31)
// revision      : $Revision: 1.12 $
// revision_date : $Date: 2002/01/23 12:30:13 $
// author(s)     : Andreas Fabri, Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_VECTOR_3_H
#define CGAL_VECTOR_3_H

CGAL_BEGIN_NAMESPACE

class Null_vector;

template <class R_>
class Vector_3 : public R_::Kernel_base::Vector_3
{
  typedef typename R_::RT                    RT;
  typedef typename R_::Point_3               Point_3;
  typedef typename R_::Direction_3           Direction_3;
  typedef typename R_::Kernel_base::Vector_3         RVector_3;
public:
  typedef          R_                       R;

  Vector_3()
  {}

  Vector_3(const CGAL::Vector_3<R>& v)
    : RVector_3( static_cast<const RVector_3&>(v) ) {}

  Vector_3(const Point_3& a, const Point_3& b)
    : RVector_3(a, b) {}

  Vector_3(const RVector_3& v)
      : RVector_3(v) {}

  Vector_3(const Null_vector& v)
      : RVector_3(v) {}

  Vector_3(const RT& x, const RT& y, const RT& z)
    : RVector_3(x, y, z) {}

  Vector_3(const RT& x, const RT& y, const RT& z, const RT& w)
    : RVector_3(x, y, z, w) {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_VECTOR_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Vector_3<R>& v)
{
  typedef typename  R::Kernel_base::Vector_3  RVector_3;
  return os << static_cast<const RVector_3&>(v);
}
#endif // CGAL_NO_OSTREAM_INSERT_VECTOR_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_VECTOR_3
template < class R >
std::istream&
operator>>(std::istream& is, Vector_3<R>& p)
{
  typedef typename  R::Kernel_base::Vector_3  RVector_3;
  return is >> static_cast<RVector_3&>(p);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_VECTOR_3

CGAL_END_NAMESPACE

#endif // CGAL_VECTOR_3_H
