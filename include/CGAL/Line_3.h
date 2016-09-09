// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.2
// release_date  : 1999, January 18
// 
// source        : Line_3.fw
// file          : include/CGAL/Line_3.h
// package       : _3 (1.4)
// revision      : 1.4
// revision_date : 15 Dec 1998 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
 


#ifndef CGAL_LINE_3_H
#define CGAL_LINE_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_LINEH3_H
#include <CGAL/LineH3.h>
#endif // CGAL_LINEH3_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_LINEC3_H
#include <CGAL/LineC3.h>
#endif // CGAL_LINEC3_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_SEGMENT_3_H
#include <CGAL/Segment_3.h>
#endif // CGAL_SEGMENT_3_H
#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif // CGAL_POINT_3_H
#ifndef CGAL_RAY_3_H
#include <CGAL/Ray_3.h>
#endif // CGAL_RAY_3_H

template <class _R>
class CGAL_Line_3 : public _R::Line_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Line_3                Line_3;

  CGAL_Line_3() : Line_3()
  {}
  CGAL_Line_3(const CGAL_Line_3<R>  & l) : Line_3( ( const Line_3& )l)
  {}
  CGAL_Line_3(const CGAL_Point_3<R> & p,
              const CGAL_Point_3<R> & q) : Line_3(p,q)
  {}
  // conversion impl -> interface class
  CGAL_Line_3(const Line_3& l) : Line_3(l)
  {}
  CGAL_Line_3(const CGAL_Segment_3<R> & s) : Line_3( s )
  {}
  CGAL_Line_3(const CGAL_Ray_3<R> & r) : Line_3( r )
  {}
  CGAL_Line_3(const CGAL_Point_3<R> & p,
              const CGAL_Direction_3<R> & d) : Line_3( p, d )
  {}

  CGAL_Line_3<R>&     operator=(const CGAL_Line_3<R> & l)
  {
    Line_3::operator=(l);
    return *this;
  }

  bool                operator==(const CGAL_Line_3<R> & l) const
  { return Line_3::operator==(l); }

  bool                operator!=(const CGAL_Line_3<R> & l) const
  { return !(*this == l); }

  int                 id() const    /* XXX */
  { return (int) PTR; }

  CGAL_Plane_3<R>     perpendicular_plane(const CGAL_Point_3<R> & p) const
  { return Line_3::perpendicular_plane(p); }

  CGAL_Line_3<R>      opposite() const
  { return Line_3::opposite(); }

  CGAL_Point_3<R>     point() const
  { return Line_3::point(); }

  CGAL_Point_3<R>     point(int i) const
  { return Line_3::point(i); }

  CGAL_Point_3<R>     projection(const CGAL_Point_3<R>& p) const
  { return Line_3::projection(p); }

  CGAL_Direction_3<R> direction() const
  { return Line_3::direction(); }

  bool                has_on(const CGAL_Point_3<R>& p) const
  { return Line_3::has_on(p); }

  bool                is_degenerate() const
  { return Line_3::is_degenerate(); }

  CGAL_Line_3<R>      transform(const CGAL_Aff_transformation_3<R> & t) const
  { return Line_3::transform(t); }
};

#ifndef CGAL_NO_OSTREAM_INSERT_LINE_3
template < class R >
ostream&
operator<<(ostream& os, const CGAL_Line_3<R>& l)
{
  typedef typename  R::Line_3     Line_3;
  return os << (const Line_3&)l;
}
#endif // CGAL_NO_OSTREAM_INSERT_LINE_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINE_3
template < class R >
istream&
operator>>(istream & is, CGAL_Line_3<R> & p)
{
  typedef typename  R::Line_3     Line_3;
  is >> ( Line_3& )p;
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINE_3


#ifndef CGAL_PLANE_3_H
#include <CGAL/Plane_3.h>
#endif // CGAL_PLANE_3_H

#endif // CGAL_LINE_3_H
