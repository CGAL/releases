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
// file          : include/CGAL/Plane_3.h
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// email         : cgal@cs.uu.nl
//
// ============================================================================
 

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

template <class _R>
class CGAL_Plane_3 : public _R::Plane_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Plane_3               Plane_3;

  CGAL_Plane_3() : Plane_3()
  {}
  CGAL_Plane_3(const CGAL_Plane_3<R>& p) : Plane_3(p)
  {}
  CGAL_Plane_3(const Plane_3& p) : Plane_3(p)
  {}
  CGAL_Plane_3(const CGAL_Point_3<R>& p,
               const CGAL_Point_3<R>& q,
               const CGAL_Point_3<R>& r)
    : Plane_3(p,q,r)
  {}
  CGAL_Plane_3(const CGAL_Point_3<R>& p, const CGAL_Direction_3<R>& d)
    : Plane_3(p,d)
  {}
  CGAL_Plane_3(const CGAL_Point_3<R>& p, const CGAL_Vector_3<R>& v)
    : Plane_3(p,v)
  {}
  CGAL_Plane_3(const RT& a, const RT& b, const RT& c, const RT& d)
    : Plane_3(a,b,c,d)
  {}
  CGAL_Plane_3(const CGAL_Line_3<R>& l, const CGAL_Point_3<R>& p)
    : Plane_3(l,p)
  {}
  CGAL_Plane_3(const CGAL_Segment_3<R>& s, const CGAL_Point_3<R>& p)
    : Plane_3(s,p)
  {}
  CGAL_Plane_3(CGAL_Ray_3<R>& r, const CGAL_Point_3<R>& p)
    : Plane_3(r,p)
  {}

  CGAL_Plane_3<R>&      operator=(const CGAL_Plane_3<R>& p)
  {
    Plane_3::operator=(p);
    return *this;
  }

  bool                  operator==(const CGAL_Plane_3<R>& p) const
  { return Plane_3::operator==(p); }

  bool                  operator!=(const CGAL_Plane_3<R>& p) const
  { return !(*this == p); }

  int                   id() const   /* XXX */
  { return (int) PTR ; }

  RT a() const
  { return Plane_3::a(); }

  RT                    b() const
  { return Plane_3::b(); }

  RT                    c() const
  { return Plane_3::c(); }

  RT                    d() const
  { return Plane_3::d(); }

  CGAL_Line_3<R>       perpendicular_line(const CGAL_Point_3<R>& p) const
  { return Plane_3::perpendicular_line(p); }

  CGAL_Plane_3<R>      opposite() const
  { return Plane_3::opposite(); }

  CGAL_Point_3<R>      projection(const CGAL_Point_3<R>& p) const
  { return Plane_3::projection(p); }

  CGAL_Point_3<R>      point() const
  { return Plane_3::point(); }

  CGAL_Vector_3<R>     orthogonal_vector() const
  { return Plane_3::orthogonal_vector(); }

  CGAL_Direction_3<R>  orthogonal_direction() const
  { return Plane_3::orthogonal_direction(); }

  CGAL_Vector_3<R>     base1() const
  { return Plane_3::base1(); }

  CGAL_Vector_3<R>     base2() const
  { return Plane_3::base2(); }

    /*
  CGAL_Point_3<R>       to_plane_basis(const CGAL_Point_3<R>& p) const
    {
      return R::Plane_3::to_plane_basis(p);
    }
    */

  CGAL_Point_2<R>      to_2d(const CGAL_Point_3<R>& p) const
  { return Plane_3::to_2d(p); }

  CGAL_Point_3<R>      to_3d(const CGAL_Point_2<R>& p) const
  { return Plane_3::to_3d(p); }

  CGAL_Plane_3<R>      transform( CGAL_Aff_transformation_3<R>& t) const
  { return CGAL_Plane_3<R>( Plane_3::transform(t) ); }

  CGAL_Oriented_side   oriented_side(const CGAL_Point_3<R>& p) const
  { return Plane_3::oriented_side(p); }

  bool                 has_on(const  CGAL_Point_3<R>& p) const
  { return Plane_3::has_on_boundary(p); }

  bool                 has_on(const  CGAL_Line_3<R>& l) const
  { return Plane_3::has_on_boundary(l); }

  bool                 has_on_boundary(const  CGAL_Point_3<R>& p) const
  { return Plane_3::has_on_boundary(p); }

  bool                 has_on_boundary(const  CGAL_Line_3<R>& l) const
  { return Plane_3::has_on_boundary(l); }

  bool                 has_on_positive_side(const  CGAL_Point_3<R>& p) const
  { return Plane_3::has_on_positive_side(p); }

  bool                 has_on_negative_side(const  CGAL_Point_3<R>& p) const
  { return Plane_3::has_on_negative_side(p); }

  bool                 is_degenerate() const
  { return Plane_3::is_degenerate(); }
};

#ifndef CGAL_NO_OSTREAM_INSERT_PLANE_3
template < class R >
ostream&
operator<<(ostream& os, const CGAL_Plane_3<R>& p)
{
  typedef typename  R::Plane_3        Plane_3;
  return os << (const Plane_3&)p;
}
#endif // CGAL_NO_OSTREAM_INSERT_PLANE_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_PLANE_3
template < class R >
istream&
operator>>(istream& is, CGAL_Plane_3<R>& t)
{
  typedef typename  R::Plane_3        Plane_3;
  return is >> (Plane_3&)t;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_PLANE_3



#endif // CGAL_PLANE_3_H
