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
// source        : Direction_2.fw
// file          : include/CGAL/Direction_2.h
// package       : _2 (2.1.2)
// revision      : 2.1.2
// revision_date : 09 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_DIRECTION_2_H
#define CGAL_DIRECTION_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_DIRECTIONH2_H
#include <CGAL/DirectionH2.h>
#endif // CGAL_DIRECTIONH2_H
#endif  // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_DIRECTIONC2_H
#include <CGAL/DirectionC2.h>
#endif // CGAL_DIRECTIONC2_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_VECTOR_2_H
#include <CGAL/Vector_2.h>
#endif // CGAL_VECTOR_2_H

CGAL_BEGIN_NAMESPACE

template <class _R>
class Direction_2 : public _R::Direction_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Vector_2              RVector_2;
  typedef typename R::Direction_2           RDirection_2;
  // typedef typename R::Aff_transformation_2  Aff_transformation_2;

  Direction_2()
  {}

  Direction_2(const Direction_2<R> &d)
    : RDirection_2((const RDirection_2&)d)
  {}


  Direction_2(const RDirection_2& d)
    : RDirection_2(d)
  {}


  Direction_2(const RVector_2& v)
    : RDirection_2(v)
  {}

  Direction_2(const RT &x, const RT &y)
    :  RDirection_2(x,y)
  {}

  Direction_2<R> &operator=(const Direction_2<R> &d)
  {
    RDirection_2::operator=(d);
    return *this;
  }


  bool operator==(const Direction_2<R> &d) const
  {
    return RDirection_2::operator==(d);
  }

  bool operator!=(const Direction_2<R> &d) const
  {
    return !(*this == d);
  }

  bool operator>=(const Direction_2<R> &d) const
  {
    return RDirection_2::operator>=(d);
  }

  bool operator<=(const Direction_2<R> &d) const
  {
    return RDirection_2::operator<=(d);
  }

  bool operator>(const Direction_2<R> &d) const
  {
    return RDirection_2::operator>(d);
  }

  bool operator<(const Direction_2<R> &d) const
  {
    return RDirection_2::operator<(d);
  }

  bool counterclockwise_in_between(const Direction_2<R> &d1,
                                   const Direction_2<R> &d2) const
  {
    return RDirection_2::counterclockwise_in_between(d1,d2);
  }

  int id() const
  {
    return (int)PTR;
  }

  Vector_2<R> vector() const
  {
    return (Vector_2<R>)RDirection_2::vector();
  }

  Direction_2<R> transform(const Aff_transformation_2<R> &t) const
  {
    return RDirection_2::transform(t);
  }

  Direction_2<R> operator-() const
  {
    return RDirection_2::operator-();
  }


  RT delta(int i) const
  {
    return RDirection_2::delta(i);
  }

  RT dx() const
  {
    return RDirection_2::dx();
  }

  RT dy() const
  {
    return RDirection_2::dy();
  }
};


#ifndef NO_OSTREAM_INSERT_DIRECTION_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Direction_2<R> &d)
{
  typedef typename  R::Direction_2    RDirection_2;
  return os << (const RDirection_2&)d;
}

#endif // NO_OSTREAM_INSERT_DIRECTION_2

#ifndef NO_ISTREAM_EXTRACT_DIRECTION_2
template < class R >
std::istream &
operator>>(std::istream &is, Direction_2<R> &p)
{
  typedef typename  R::Direction_2    RDirection_2;
  return is >> (RDirection_2&)p;
}
#endif // NO_ISTREAM_EXTRACT_DIRECTION_2


CGAL_END_NAMESPACE


#endif // CGAL_DIRECTION_2_H
