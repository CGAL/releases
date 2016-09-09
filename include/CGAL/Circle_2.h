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
// source        : Circle_2.fw
// file          : include/CGAL/Circle_2.h
// package       : _2 (1.2.2)
// revision      : 1.2.2
// revision_date : 27 Jan 1998 
// author(s)     : Andreas Fabri
//                 Sven Schoenherr
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_CIRCLE_2_H
#define CGAL_CIRCLE_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_CIRCLEH2_H
#include <CGAL/CircleH2.h>
#endif // CGAL_CIRCLEH2_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_CIRCLEC2_H
#include <CGAL/CircleC2.h>
#endif // CGAL_CIRCLEC2_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H

template <class _R>
  class CGAL_Circle_2 : public _R::Circle_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Circle_2              Circle_2;

    CGAL_Circle_2()
      : Circle_2()
    {}

    CGAL_Circle_2(const CGAL_Circle_2<R> &t)
      : Circle_2((Circle_2&)t)
    {}

    CGAL_Circle_2(const Circle_2 &t)
      : Circle_2(t)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> &center,
                  const FT &squared_radius,
                  const CGAL_Orientation &orientation)
      : Circle_2(center, squared_radius, orientation)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> &center,
                  const FT &squared_radius)
      : Circle_2(center, squared_radius, CGAL_COUNTERCLOCKWISE)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> &p,
                  const CGAL_Point_2<R> &q,
                  const CGAL_Point_2<R> &r)
      : Circle_2(p,q,r)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> & p,
                  const CGAL_Point_2<R> & q,
                  const CGAL_Orientation &orientation)
      : Circle_2(p,q,orientation)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> & p,
                  const CGAL_Point_2<R> & q)
      : Circle_2(p,q,CGAL_COUNTERCLOCKWISE)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> & center,
                  const CGAL_Orientation& orientation)
      : Circle_2(center,FT(0),orientation)
    {}

    CGAL_Circle_2(const CGAL_Point_2<R> & center)
      : Circle_2(center,FT(0),CGAL_COUNTERCLOCKWISE)
    {}


  CGAL_Circle_2<R>  &operator=(const CGAL_Circle_2<R> &t)
    {
      Circle_2::operator=(t);
      return *this;
    }

  bool                operator==(const CGAL_Circle_2<R> &t) const
    {
      return Circle_2::operator==(t);
    }

  bool                operator!=(const CGAL_Circle_2<R> &t) const
    {
      return !(*this == t);
    }

  int                 id() const
    {
      return (int)PTR;
    }

  CGAL_Point_2<R>     center() const
    {
      return Circle_2::center();
    }

  FT     squared_radius() const
    {
      return Circle_2::squared_radius();
    }

  CGAL_Orientation orientation() const
    {
      return Circle_2::orientation();
    }


  CGAL_Circle_2<R>
            orthogonal_transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  Circle_2::orthogonal_transform(t);
  }

/*
  CGAL_Circle_2<R>  transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  Circle_2::transform(t);
  }
*/

  CGAL_Oriented_side           oriented_side(const CGAL_Point_2<R> &p) const
    {
      return Circle_2::oriented_side(p);
    }

  CGAL_Bounded_side           bounded_side(const CGAL_Point_2<R> &p) const
    {
      return Circle_2::bounded_side(p);
    }

  bool                has_on_boundary(const CGAL_Point_2<R> &p) const
    {
      return Circle_2::has_on_boundary(p);
    }

  bool                has_on_positive_side(const CGAL_Point_2<R> &p) const
    {
      return Circle_2::has_on_positive_side(p);
    }

  bool                has_on_negative_side(const CGAL_Point_2<R> &p) const
    {
      return Circle_2::has_on_negative_side(p);
    }

  bool                has_on_bounded_side(const CGAL_Point_2<R> &p) const
    {
      return Circle_2::has_on_bounded_side(p);
    }

  bool                has_on_unbounded_side(const CGAL_Point_2<R> &p) const
    {
      return Circle_2::has_on_unbounded_side(p);
    }

  bool                is_degenerate() const
    {
      return Circle_2::is_degenerate();
    }

  CGAL_Circle_2<R>     opposite() const
    {
      return CGAL_Circle_2<R>(center(),
                              squared_radius(),
                              CGAL_opposite(orientation()));
    }

  CGAL_Bbox_2           bbox() const
    {
      return Circle_2::bbox();
    }
};


#ifndef CGAL_NO_OSTREAM_INSERT_CIRCLE_2
template < class R >
ostream &
operator<<(ostream &os, const CGAL_Circle_2<R> &c)
{
  typedef typename R::Circle_2   Circle_2;
  return os << (const Circle_2&)c;
}

#endif // CGAL_NO_OSTREAM_INSERT_CIRCLE_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_CIRCLE_2
template < class R >
istream &
operator>>(istream &is, CGAL_Circle_2<R> &c)
{
  typedef typename R::Circle_2   Circle_2;
  return is >> (Circle_2&)c;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_CIRCLE_2


#endif  // CGAL_CIRCLE_2_H
