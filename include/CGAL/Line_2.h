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
// source        : Line_2.fw
// file          : include/CGAL/Line_2.h
// package       : _2 (1.2.2)
// revision      : 1.2.2
// revision_date : 27 Jan 1998 
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_LINE_2_H
#define CGAL_LINE_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_LINEH2_H
#include <CGAL/LineH2.h>
#endif // CGAL_LINEH2_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_LINEC2_H
#include <CGAL/LineC2.h>
#endif // CGAL_LINEC2_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_PREDICATES_ON_POINTS_2_H
#include <CGAL/predicates_on_points_2.h>
#endif // CGAL_PREDICATES_ON_POINTS_2_H
#ifndef CGAL_VECTOR_2_H
#include <CGAL/Vector_2.h>
#endif // CGAL_VECTOR_2_H

template <class _R>
class CGAL_Line_2 : public _R::Line_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Line_2                Line_2;

  CGAL_Line_2()
    : Line_2()
  {}

  ~CGAL_Line_2()
  {}

  CGAL_Line_2(const CGAL_Line_2<R>  &l)
    : Line_2((Line_2&)l)
  {}

  CGAL_Line_2(const CGAL_Point_2<R> &p, const CGAL_Point_2<R> &q)
    : Line_2(p,q)
  {}

  CGAL_Line_2(const RT &a, const RT &b, const RT &c)
    : Line_2(a,b,c)
  {}


  CGAL_Line_2(const Line_2 &l)  // conversion impl -> interface class
    : Line_2(l)
  {}


  CGAL_Line_2(const CGAL_Segment_2<R>& s)
    : Line_2(s)
  {}

  CGAL_Line_2(const CGAL_Ray_2<R>& r)
    : Line_2(r)
  {}

  CGAL_Line_2(const CGAL_Point_2<R> &p, const CGAL_Direction_2<R> &d)
    : Line_2(p,d)
  {}


  CGAL_Line_2<R> &operator=(const CGAL_Line_2<R> &l)
  {
    Line_2::operator=(l);
    return *this;
  }

  bool operator==(const CGAL_Line_2<R> &l) const
  {
    return Line_2::operator==(l);
  }

  bool operator!=(const CGAL_Line_2<R> &l) const
  {
    return !(*this == l);
  }

  int id() const
  {
    return (int) PTR;
  }

  RT a() const
  {
    return Line_2::a();
  }

  RT b() const
  {
    return Line_2::b();
  }

  RT c() const
  {
    return Line_2::c();
  }


  FT x_at_y(const FT &y) const
  {
    return Line_2::x_at_y(y);
  }

  FT y_at_x(const FT &x) const
  {
    return Line_2::y_at_x(x);
  }

  CGAL_Line_2<R> perpendicular(const CGAL_Point_2<R> &p) const
  {
    return Line_2::perpendicular(p);
  }

  CGAL_Line_2<R> opposite() const
  {
    return Line_2::opposite();
  }

  CGAL_Point_2<R> point(int i) const
  {
    return Line_2::point(i);
  }

  CGAL_Point_2<R> projection(const CGAL_Point_2<R> &p) const
  {
    return Line_2::projection(p);
  }

  CGAL_Point_2<R> point() const
  {
    return Line_2::point();
  }

  CGAL_Direction_2<R> direction() const
  {

    return Line_2::direction();
  }

  CGAL_Oriented_side oriented_side(const CGAL_Point_2<R> &p) const
  {
    return Line_2::oriented_side(p);
  }

  bool has_on(const CGAL_Point_2<R> &p) const
  {
    return Line_2::has_on_boundary(p);
  }

  bool has_on_boundary(const CGAL_Point_2<R> &p) const
  {
    return Line_2::has_on_boundary(p);
  }

  bool has_on_positive_side(const CGAL_Point_2<R> &p) const
  {
    return Line_2::has_on_positive_side(p);
  }

  bool has_on_negative_side(const CGAL_Point_2<R> &p) const
  {
    return Line_2::has_on_negative_side(p);
  }

  bool is_horizontal() const
  {

    return Line_2::is_horizontal();
  }

  bool is_vertical() const
  {

    return Line_2::is_vertical();
  }

  bool is_degenerate() const
  {

    return Line_2::is_degenerate();
  }

  CGAL_Line_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  Line_2::transform(t);
  }
};



#ifndef CGAL_NO_OSTREAM_INSERT_LINE_2
template < class R >
ostream &
operator<<(ostream &os, const CGAL_Line_2<R> &l)
{
  typedef typename  R::Line_2     Line_2;
  return os << (const Line_2&)l;
}
#endif // CGAL_NO_OSTREAM_INSERT_LINE_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINE_2
template < class R >
istream &
operator>>(istream &is, CGAL_Line_2<R> &p)
{
  typedef typename  R::Line_2     Line_2;
  return is >> (Line_2&)p;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINE_2




#ifndef CGAL_SEGMENT_2_H
#include <CGAL/Segment_2.h>
#endif // CGAL_SEGMENT_2_H
#ifndef CGAL_RAY_2_H
#include <CGAL/Ray_2.h>
#endif // CGAL_RAY_2_H

#endif  // CGAL_LINE_2_H
