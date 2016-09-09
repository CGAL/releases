// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Ray_3.h
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// email         : cgal@cs.uu.nl
//
// ============================================================================
 

#ifndef CGAL_RAY_3_H
#define CGAL_RAY_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_RAYH3_H
#include <CGAL/RayH3.h>
#endif // CGAL_RAYH3_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_RAYC3_H
#include <CGAL/RayC3.h>
#endif // CGAL_RAYC3_H
#endif // CGAL_CARTESIAN_H

template <class _R>
class CGAL_Ray_3 : public _R::Ray_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Ray_3                 Ray_3;

  CGAL_Ray_3() : Ray_3()
  {}
  CGAL_Ray_3(const CGAL_Ray_3<R>& r) : Ray_3(r)
  {}
  CGAL_Ray_3(const Ray_3& r) : Ray_3(r)
  {}
  CGAL_Ray_3(const CGAL_Point_3<R>& sp,
            const CGAL_Point_3<R>& secondp)
    : Ray_3(sp, secondp)
  {}
  CGAL_Ray_3(const CGAL_Point_3<R>& sp,
            const CGAL_Direction_3<R>& d)
    : Ray_3(sp, d)
  {}

  CGAL_Ray_3<R>&      operator=(const CGAL_Ray_3<R>& r)
  {
      Ray_3::operator=(r);
      return *this;
  }
  bool                operator==(const CGAL_Ray_3<R>& r) const
  { return Ray_3::operator==(r); }
  bool                operator!=(const CGAL_Ray_3<R>& r) const
  { return !(*this == r); }

  int                 id() const  /* XXX */
  { return (int)  PTR ; }

  CGAL_Point_3<R>     start() const
  { return Ray_3::start(); }
  CGAL_Point_3<R>     source() const
  { return Ray_3::source(); }
  CGAL_Point_3<R>     second_point() const
  { return Ray_3::second_point(); }
  CGAL_Point_3<R>     point(int i) const
  { return Ray_3::point(i); }
  CGAL_Direction_3<R> direction() const
  { return Ray_3::direction(); }
  CGAL_Line_3<R>      supporting_line() const
  { return Ray_3::supporting_line(); }
  CGAL_Ray_3<R>       opposite() const
  { return Ray_3::opposite(); }
  CGAL_Ray_3<R>       transform(const CGAL_Aff_transformation_3<R>& t) const
  { return Ray_3::transform(t); }
  bool                is_degenerate() const
  { return Ray_3::is_degenerate(); }
  bool                has_on(const CGAL_Point_3<R>& p) const
  { return Ray_3::has_on(p); }
};

#ifndef CGAL_NO_OSTREAM_INSERT_RAY_3
template < class R >
ostream&
operator<<(ostream& os, const CGAL_Ray_3<R>& r)
{
  typedef typename  R::Ray_3        Ray_3;
  return os << (const Ray_3&)r;
}
#endif // CGAL_NO_OSTREAM_INSERT_RAY_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAY_3
template < class R >
istream&
operator>>(istream& is, CGAL_Ray_3<R>& r)
{
  typedef typename  R::Ray_3        Ray_3;
  return is >> (Ray_3&)r;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAY_3



#ifndef CGAL_LINE_3_H
#include <CGAL/Line_3.h>
#endif // CGAL_LINE_3_H

#endif // CGAL_RAY_3_H
