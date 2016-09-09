// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : Ray_2.fw
// file          : include/CGAL/Ray_2.h
// package       : _2 (2.1.2)
// revision      : 2.1.2
// revision_date : 09 May 1999 
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

CGAL_BEGIN_NAMESPACE

template <class _R>
class Ray_2 : public _R::Ray_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Ray_2                 RRay_2;

    Ray_2()
      : RRay_2()
  {}

  ~Ray_2()
  {}

  Ray_2(const Ray_2<R> &r)
    : RRay_2((const RRay_2&)r)
  {

  }

  Ray_2(const RRay_2& r)
    : RRay_2(r)
  {

  }

  Ray_2(const Point_2<R> &sp,
             const Point_2<R> &secondp)
    : RRay_2(sp, secondp)
  {}

  Ray_2(const Point_2<R> &sp,
             const Direction_2<R> &d)
    : RRay_2(sp, d)
  {}


  Ray_2<R> &operator=(const Ray_2<R> &r)
  {


    RRay_2::operator=(r);
    return *this;
  }

  bool operator==(const Ray_2<R> &r) const
  { return RRay_2::operator==(r); }

  bool operator!=(const Ray_2<R> &r) const
  { return !(*this == r); }

  int id() const
  { return (int) PTR ; }

  Point_2<R> start() const
  { return RRay_2::start(); }

  Point_2<R> source() const
  { return RRay_2::source(); }

  Point_2<R> second_point() const
  { return RRay_2::second_point(); }

  Point_2<R> point(int i) const
  { return RRay_2::point(i); }

  Direction_2<R> direction() const
  { return RRay_2::direction(); }

  Line_2<R> supporting_line() const
  { return RRay_2::supporting_line(); }

  Ray_2<R> opposite() const
  { return RRay_2::opposite(); }

  Ray_2<R> transform(const Aff_transformation_2<R> &t) const
  { return RRay_2::transform(t); }

  bool is_horizontal() const
  { return RRay_2::is_horizontal(); }

  bool is_vertical() const
  { return RRay_2::is_vertical(); }

  bool is_degenerate() const
  { return RRay_2::is_degenerate(); }

  bool has_on(const Point_2<R> &p) const
  { return RRay_2::has_on(p); }

  bool collinear_has_on(const Point_2<R> &p) const
  { return RRay_2::collinear_has_on(p); }

};

#ifndef NO_OSTREAM_INSERT_RAY_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Ray_2<R> &r)
{
  typedef typename  R::Ray_2    RRay_2;
  return os << (const RRay_2&)r;
}
#endif // NO_OSTREAM_INSERT_RAY_2

#ifndef NO_ISTREAM_EXTRACT_RAY_2
template < class R >
std::istream &
operator>>(std::istream &is, Ray_2<R> &r)
{
  typedef typename  R::Ray_2    RRay_2;
  return is >> (RRay_2&)r;
}
#endif // NO_ISTREAM_EXTRACT_RAY_2

CGAL_END_NAMESPACE


#endif  // CGAL_RAY_2_H
