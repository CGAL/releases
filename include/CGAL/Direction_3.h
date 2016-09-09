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
// source        : Direction_3.fw
// file          : include/CGAL/Direction_3.h
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
 

#ifndef CGAL_DIRECTION_3_H
#define CGAL_DIRECTION_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_DIRECTIONH3_H
#include <CGAL/DirectionH3.h>
#endif // CGAL_DIRECTIONH3_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_DIRECTIONC3_H
#include <CGAL/DirectionC3.h>
#endif // CGAL_DIRECTIONC3_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_VECTOR_3_H
#include <CGAL/Vector_3.h>
#endif // CGAL_VECTOR_3_H

template <class _R>
class CGAL_Direction_3 : public _R::Direction_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Direction_3           Direction_3;
  typedef typename R::Vector_3              Vector_3;

  CGAL_Direction_3()
  {}
  CGAL_Direction_3(const CGAL_Direction_3<R>& d)
    : Direction_3( (const Direction_3&)d )
  {}
  CGAL_Direction_3(const Direction_3& d)
    : Direction_3(d)
  {}
  CGAL_Direction_3(const Vector_3& v)
    : Direction_3(v)
  {}
  CGAL_Direction_3(const RT& hx, const RT& hy, const RT& hz)
    : Direction_3(hx, hy, hz)
  {}
  CGAL_Direction_3<R> & operator=(const CGAL_Direction_3<R> & d)
  {
    Direction_3::operator=(d);
    return *this;
  }

  bool operator==(const CGAL_Direction_3<R> & d) const
  { return Direction_3::operator==(d); }

  bool operator!=(const CGAL_Direction_3<R> & d) const
  { return !(*this == d); }

  int id() const             /* XXX */
  { return (int) PTR; }

  CGAL_Vector_3<R> vector() const
  { return (CGAL_Vector_3<R>)Direction_3::vector(); }

  CGAL_Direction_3<R> transform(const CGAL_Aff_transformation_3<R> & t) const
  { return Direction_3::transform(t); }

  CGAL_Direction_3<R> operator-() const
  { return Direction_3::operator-(); }

  RT delta(int i) const
  { return Direction_3::delta(i); }

  RT dx() const
  { return Direction_3::dx(); }

  RT dy() const
  { return Direction_3::dy(); }

  RT dz() const
  { return Direction_3::dz(); }
};


#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTION_3
template < class R >
ostream& operator<<(ostream& os, const CGAL_Direction_3<R>& d)
{
  typedef typename  R::Direction_3    Direction_3;
  return os << (const Direction_3&)d; }
#endif // CGAL_NO_OSTREAM_INSERT_DIRECTION_3


#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTION_3
template < class R >
istream& operator>>(istream& is, CGAL_Direction_3<R>& p)
{
  typedef typename  R::Direction_3    Direction_3;
  return is >> (Direction_3&)p; }
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTION_3


#endif
