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
// source        : Line_2.fw
// file          : include/CGAL/Line_2.h
// package       : _2 (2.1.2)
// revision      : 2.1.2
// revision_date : 09 May 1999 
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

CGAL_BEGIN_NAMESPACE

template <class _R>
class Line_2 : public _R::Line_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Line_2                RLine_2;

  Line_2()
    : RLine_2()
  {}

  ~Line_2()
  {}

  Line_2(const Line_2<R>  &l)
    : RLine_2((RLine_2&)l)
  {}

  Line_2(const Point_2<R> &p, const Point_2<R> &q)
    : RLine_2(p,q)
  {}

  Line_2(const RT &a, const RT &b, const RT &c)
    : RLine_2(a,b,c)
  {}


  Line_2(const RLine_2& l)  // conversion impl -> interface class
    : RLine_2(l)
  {}


  Line_2(const Segment_2<R>& s)
    : RLine_2(s)
  {}

  Line_2(const Ray_2<R>& r)
    : RLine_2(r)
  {}

  Line_2(const Point_2<R> &p, const Direction_2<R> &d)
    : RLine_2(p,d)
  {}


  Line_2<R> &operator=(const Line_2<R> &l)
  {
    RLine_2::operator=(l);
    return *this;
  }

  bool operator==(const Line_2<R> &l) const
  {
    return RLine_2::operator==(l);
  }

  bool operator!=(const Line_2<R> &l) const
  {
    return !(*this == l);
  }

  int id() const
  {
    return (int) PTR;
  }

  RT a() const
  {
    return RLine_2::a();
  }

  RT b() const
  {
    return RLine_2::b();
  }

  RT c() const
  {
    return RLine_2::c();
  }


  FT x_at_y(const FT &y) const
  {
    return RLine_2::x_at_y(y);
  }

  FT y_at_x(const FT &x) const
  {
    return RLine_2::y_at_x(x);
  }

  Line_2<R> perpendicular(const Point_2<R> &p) const
  {
    return RLine_2::perpendicular(p);
  }

  Line_2<R> opposite() const
  {
    return RLine_2::opposite();
  }

  Point_2<R> point(int i) const
  {
    return RLine_2::point(i);
  }

  Point_2<R> projection(const Point_2<R> &p) const
  {
    return RLine_2::projection(p);
  }

  Point_2<R> point() const
  {
    return RLine_2::point();
  }

  Direction_2<R> direction() const
  {

    return RLine_2::direction();
  }

  Oriented_side oriented_side(const Point_2<R> &p) const
  {
    return RLine_2::oriented_side(p);
  }

  bool has_on(const Point_2<R> &p) const
  {
    return RLine_2::has_on_boundary(p);
  }

  bool has_on_boundary(const Point_2<R> &p) const
  {
    return RLine_2::has_on_boundary(p);
  }

  bool has_on_positive_side(const Point_2<R> &p) const
  {
    return RLine_2::has_on_positive_side(p);
  }

  bool has_on_negative_side(const Point_2<R> &p) const
  {
    return RLine_2::has_on_negative_side(p);
  }

  bool is_horizontal() const
  {

    return RLine_2::is_horizontal();
  }

  bool is_vertical() const
  {

    return RLine_2::is_vertical();
  }

  bool is_degenerate() const
  {

    return RLine_2::is_degenerate();
  }

  Line_2<R> transform(const Aff_transformation_2<R> &t) const
  {
    return  RLine_2::transform(t);
  }
};



#ifndef NO_OSTREAM_INSERT_LINE_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Line_2<R> &l)
{
  typedef typename  R::Line_2     RLine_2;
  return os << (const RLine_2&)l;
}
#endif // NO_OSTREAM_INSERT_LINE_2

#ifndef NO_ISTREAM_EXTRACT_LINE_2
template < class R >
std::istream &
operator>>(std::istream &is, Line_2<R> &p)
{
  typedef typename  R::Line_2     RLine_2;
  return is >> (RLine_2&)p;
}
#endif // NO_ISTREAM_EXTRACT_LINE_2



CGAL_END_NAMESPACE


#ifndef CGAL_SEGMENT_2_H
#include <CGAL/Segment_2.h>
#endif // CGAL_SEGMENT_2_H
#ifndef CGAL_RAY_2_H
#include <CGAL/Ray_2.h>
#endif // CGAL_RAY_2_H

#endif  // CGAL_LINE_2_H
