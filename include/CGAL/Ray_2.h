// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : Ray_2.fw
// file          : include/CGAL/Ray_2.h
// package       : _2 (1.2.2)
// revision      : 1.2.2
// revision_date : 27 Jan 1998 
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_RAY_2_H
#define CGAL_RAY_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifndef CGAL_SEGMENT_2_H
#include <CGAL/Segment_2.h>
#endif // CGAL_SEGMENT_2_H

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_RAYH2_H
#include <CGAL/RayH2.h>
#endif // CGAL_RAYH2_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_RAYC2_H
#include <CGAL/RayC2.h>
#endif // CGAL_RAYC2_H
#endif // CGAL_CARTESIAN_H

template <class _R>
class CGAL_Ray_2 : public _R::Ray_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Ray_2                 Ray_2;

    CGAL_Ray_2()
      : Ray_2()
  {}

  ~CGAL_Ray_2()
  {}

  CGAL_Ray_2(const CGAL_Ray_2<R> &r)
    : Ray_2((const Ray_2&)r)
  {

  }

  CGAL_Ray_2(const Ray_2 &r)
    : Ray_2(r)
  {

  }

  CGAL_Ray_2(const CGAL_Point_2<R> &sp,
             const CGAL_Point_2<R> &secondp)
    : Ray_2(sp, secondp)
  {}

  CGAL_Ray_2(const CGAL_Point_2<R> &sp,
             const CGAL_Direction_2<R> &d)
    : Ray_2(sp, d)
  {}


  CGAL_Ray_2<R> &operator=(const CGAL_Ray_2<R> &r)
  {


    Ray_2::operator=(r);
    return *this;
  }

  bool operator==(const CGAL_Ray_2<R> &r) const
  {
    return Ray_2::operator==(r);
  }

  bool operator!=(const CGAL_Ray_2<R> &r) const
  {
    return !(*this == r);
  }

  int id() const
  {
    return (int) PTR ;
  }

  CGAL_Point_2<R> start() const
  {
    return Ray_2::start();
  }

  CGAL_Point_2<R> source() const
  {
    return Ray_2::source();
  }

  CGAL_Point_2<R> second_point() const
  {
    return Ray_2::second_point();
  }

  CGAL_Point_2<R> point(int i) const
  {
    return Ray_2::point(i);
  }

  CGAL_Direction_2<R> direction() const
  {
    return Ray_2::direction();
  }

  CGAL_Line_2<R> supporting_line() const
  {
    return Ray_2::supporting_line();
  }

  CGAL_Ray_2<R> opposite() const
  {
    return Ray_2::opposite();
  }


  CGAL_Ray_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return Ray_2::transform(t);
  }


  bool is_horizontal() const
  {
    return Ray_2::is_horizontal();
  }

  bool is_vertical() const
  {
    return Ray_2::is_vertical();
  }

  bool is_degenerate() const
  {
    return Ray_2::is_degenerate();
  }

  bool has_on(const CGAL_Point_2<R> &p) const
  {
    return Ray_2::has_on(p);
  }
};

#ifndef CGAL_NO_OSTREAM_INSERT_RAY_2
template < class R >
ostream &
operator<<(ostream &os, const CGAL_Ray_2<R> &r)
{
  typedef typename  R::Ray_2    Ray_2;
  return os << (const Ray_2&)r;
}
#endif // CGAL_NO_OSTREAM_INSERT_RAY_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAY_2
template < class R >
istream &
operator>>(istream &is, CGAL_Ray_2<R> &r)
{
  typedef typename  R::Ray_2    Ray_2;
  return is >> (Ray_2&)r;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAY_2


#endif  // CGAL_RAY_2_H
