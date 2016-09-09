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
// source        : Direction_3.fw
// file          : include/CGAL/Direction_3.h
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

CGAL_BEGIN_NAMESPACE

template <class _R>
class Direction_3 : public _R::Direction_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Direction_3           RDirection_3;
  typedef typename R::Vector_3              RVector_3;

  Direction_3()
  {}
  Direction_3(const Direction_3<R>& d)
    : RDirection_3( (const RDirection_3& )d )
  {}
  Direction_3(const RDirection_3&  d)
    : RDirection_3(d)
  {}
  Direction_3(const RVector_3&  v)
    : RDirection_3(v)
  {}
  Direction_3(const RT& hx, const RT& hy, const RT& hz)
    : RDirection_3(hx, hy, hz)
  {}
  Direction_3<R> & operator=(const Direction_3<R> & d)
  {
    RDirection_3::operator=(d);
    return *this;
  }

  bool operator==(const Direction_3<R> & d) const
  { return RDirection_3::operator==(d); }

  bool operator!=(const Direction_3<R> & d) const
  { return !(*this == d); }

  int id() const             /* XXX */
  { return (int) PTR; }

  Vector_3<R> vector() const
  { return (Vector_3<R>)RDirection_3::vector(); }

  Direction_3<R> transform(const Aff_transformation_3<R> & t) const
  { return RDirection_3::transform(t); }

  Direction_3<R> operator-() const
  { return RDirection_3::operator-(); }

  RT delta(int i) const
  { return RDirection_3::delta(i); }

  RT dx() const
  { return RDirection_3::dx(); }

  RT dy() const
  { return RDirection_3::dy(); }

  RT dz() const
  { return RDirection_3::dz(); }
};


#ifndef NO_OSTREAM_INSERT_DIRECTION_3
template < class R >
std::ostream& operator<<(std::ostream& os, const Direction_3<R>& d)
{
  typedef typename  R::Direction_3    RDirection_3;
  return os << (const RDirection_3& )d; }
#endif // NO_OSTREAM_INSERT_DIRECTION_3


#ifndef NO_ISTREAM_EXTRACT_DIRECTION_3
template < class R >
std::istream& operator>>(std::istream& is, Direction_3<R>& p)
{
  typedef typename  R::Direction_3    RDirection_3;
  return is >> (RDirection_3& )p; }
#endif // NO_ISTREAM_EXTRACT_DIRECTION_3

CGAL_END_NAMESPACE


#endif // CGAL_DIRECTION_3_H
