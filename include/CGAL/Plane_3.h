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
// source        : Plane_3.fw
// file          : include/CGAL/Plane_3.h
// package       : _3 (2.1.2)
// revision      : 2.1.2
// revision_date : 21 May 1999 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_PLANE_3_H
#define CGAL_PLANE_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#if defined(CGAL_CFG_INCOMPLETE_TYPE_BUG_1) && \
   !defined(CGAL_NO_PLANE_TRANSFORM_IN_AT)
#define CGAL_NO_PLANE_TRANSFORM_IN_AT
#endif // CGAL_CFG_INCOMPLETE_TYPE_BUG_1

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_PLANEH3_H
#include <CGAL/PlaneH3.h>
#endif // CGAL_PLANEH3_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_PLANEC3_H
#include <CGAL/PlaneC3.h>
#endif // CGAL_PLANEC3_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_LINE_3_H
#include <CGAL/Line_3.h>
#endif // CGAL_LINE_3_H
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H

CGAL_BEGIN_NAMESPACE

template <class _R>
class Plane_3 : public _R::Plane_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Plane_3               RPlane_3;

  Plane_3() : RPlane_3()
  {}
  Plane_3(const Plane_3<R>& p) : RPlane_3(p)
  {}
  Plane_3(const RPlane_3&  p) : RPlane_3(p)
  {}
  Plane_3(const Point_3<R>& p,
               const Point_3<R>& q,
               const Point_3<R>& r)
    : RPlane_3(p,q,r)
  {}
  Plane_3(const Point_3<R>& p, const Direction_3<R>& d)
    : RPlane_3(p,d)
  {}
  Plane_3(const Point_3<R>& p, const Vector_3<R>& v)
    : RPlane_3(p,v)
  {}
  Plane_3(const RT& a, const RT& b, const RT& c, const RT& d)
    : RPlane_3(a,b,c,d)
  {}
  Plane_3(const Line_3<R>& l, const Point_3<R>& p)
    : RPlane_3(l,p)
  {}
  Plane_3(const Segment_3<R>& s, const Point_3<R>& p)
    : RPlane_3(s,p)
  {}
  Plane_3(Ray_3<R>& r, const Point_3<R>& p)
    : RPlane_3(r,p)
  {}

  Plane_3<R>&      operator=(const Plane_3<R>& p)
  {
    RPlane_3::operator=(p);
    return *this;
  }

  bool                  operator==(const Plane_3<R>& p) const
  { return RPlane_3::operator==(p); }

  bool                  operator!=(const Plane_3<R>& p) const
  { return !(*this == p); }

  int                   id() const   /* XXX */
  { return (int) PTR ; }

  RT a() const
  { return RPlane_3::a(); }

  RT                    b() const
  { return RPlane_3::b(); }

  RT                    c() const
  { return RPlane_3::c(); }

  RT                    d() const
  { return RPlane_3::d(); }

  Line_3<R>       perpendicular_line(const Point_3<R>& p) const
  { return RPlane_3::perpendicular_line(p); }

  Plane_3<R>      opposite() const
  { return RPlane_3::opposite(); }

  Point_3<R>      projection(const Point_3<R>& p) const
  { return RPlane_3::projection(p); }

  Point_3<R>      point() const
  { return RPlane_3::point(); }

  Vector_3<R>     orthogonal_vector() const
  { return RPlane_3::orthogonal_vector(); }

  Direction_3<R>  orthogonal_direction() const
  { return RPlane_3::orthogonal_direction(); }

  Vector_3<R>     base1() const
  { return RPlane_3::base1(); }

  Vector_3<R>     base2() const
  { return RPlane_3::base2(); }

    /*
  Point_3<R>       to_plane_basis(const Point_3<R>& p) const
    {
      return R::RPlane_3::to_plane_basis(p);
    }
    */

  Point_2<R>      to_2d(const Point_3<R>& p) const
  { return RPlane_3::to_2d(p); }

  Point_3<R>      to_3d(const Point_2<R>& p) const
  { return RPlane_3::to_3d(p); }

  Plane_3<R>      transform( Aff_transformation_3<R>& t) const
  { return Plane_3<R>( RPlane_3::transform(t) ); }

  Oriented_side   oriented_side(const Point_3<R>& p) const
  { return RPlane_3::oriented_side(p); }

  bool                 has_on(const  Point_3<R>& p) const
  { return RPlane_3::has_on_boundary(p); }

  bool                 has_on(const  Line_3<R>& l) const
  { return RPlane_3::has_on_boundary(l); }

  bool                 has_on_boundary(const  Point_3<R>& p) const
  { return RPlane_3::has_on_boundary(p); }

  bool                 has_on_boundary(const  Line_3<R>& l) const
  { return RPlane_3::has_on_boundary(l); }

  bool                 has_on_positive_side(const  Point_3<R>& p) const
  { return RPlane_3::has_on_positive_side(p); }

  bool                 has_on_negative_side(const  Point_3<R>& p) const
  { return RPlane_3::has_on_negative_side(p); }

  bool                 is_degenerate() const
  { return RPlane_3::is_degenerate(); }
};

#ifndef NO_OSTREAM_INSERT_PLANE_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Plane_3<R>& p)
{
  typedef typename  R::Plane_3        RPlane_3;
  return os << (const RPlane_3& )p;
}
#endif // NO_OSTREAM_INSERT_PLANE_3

#ifndef NO_ISTREAM_EXTRACT_PLANE_3
template < class R >
std::istream&
operator>>(std::istream& is, Plane_3<R>& t)
{
  typedef typename  R::Plane_3        RPlane_3;
  return is >> (RPlane_3& )t;
}
#endif // NO_ISTREAM_EXTRACT_PLANE_3


CGAL_END_NAMESPACE


#endif // CGAL_PLANE_3_H
