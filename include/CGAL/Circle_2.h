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
// source        : Circle_2.fw
// file          : include/CGAL/Circle_2.h
// package       : _2 (2.1.2)
// revision      : 2.1.2
// revision_date : 09 May 1999 
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

CGAL_BEGIN_NAMESPACE

template <class _R>
  class Circle_2 : public _R::Circle_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Circle_2              RCircle_2;

    Circle_2()
      : RCircle_2()
    {}

    Circle_2(const Circle_2<R> &t)
      : RCircle_2((RCircle_2&)t)
    {}

    Circle_2(const RCircle_2& t)
      : RCircle_2(t)
    {}

    Circle_2(const Point_2<R> &center,
                  const FT &squared_radius,
                  const Orientation &orientation)
      : RCircle_2(center, squared_radius, orientation)
    {}

    Circle_2(const Point_2<R> &center,
                  const FT &squared_radius)
      : RCircle_2(center, squared_radius, COUNTERCLOCKWISE)
    {}

    Circle_2(const Point_2<R> &p,
                  const Point_2<R> &q,
                  const Point_2<R> &r)
      : RCircle_2(p,q,r)
    {}

    Circle_2(const Point_2<R> & p,
                  const Point_2<R> & q,
                  const Orientation &orientation)
      : RCircle_2(p,q,orientation)
    {}

    Circle_2(const Point_2<R> & p,
                  const Point_2<R> & q)
      : RCircle_2(p,q,COUNTERCLOCKWISE)
    {}

    Circle_2(const Point_2<R> & center,
                  const Orientation& orientation)
      : RCircle_2(center,FT(0),orientation)
    {}

    Circle_2(const Point_2<R> & center)
      : RCircle_2(center,FT(0),COUNTERCLOCKWISE)
    {}


  Circle_2<R>  &operator=(const Circle_2<R> &t)
    {
      RCircle_2::operator=(t);
      return *this;
    }

  bool                operator==(const Circle_2<R> &t) const
    {
      return RCircle_2::operator==(t);
    }

  bool                operator!=(const Circle_2<R> &t) const
    {
      return !(*this == t);
    }

  int                 id() const
    {
      return (int)PTR;
    }

  Point_2<R>     center() const
    {
      return RCircle_2::center();
    }

  FT     squared_radius() const
    {
      return RCircle_2::squared_radius();
    }

  Orientation orientation() const
    {
      return RCircle_2::orientation();
    }


  Circle_2<R>
            orthogonal_transform(const Aff_transformation_2<R> &t) const
  {
    return  RCircle_2::orthogonal_transform(t);
  }

/*
  Circle_2<R>  transform(const Aff_transformation_2<R> &t) const
  {
    return  Circle_2::transform(t);
  }
*/

  Oriented_side           oriented_side(const Point_2<R> &p) const
    {
      return RCircle_2::oriented_side(p);
    }

  Bounded_side           bounded_side(const Point_2<R> &p) const
    {
      return RCircle_2::bounded_side(p);
    }

  bool                has_on_boundary(const Point_2<R> &p) const
    {
      return RCircle_2::has_on_boundary(p);
    }

  bool                has_on_positive_side(const Point_2<R> &p) const
    {
      return RCircle_2::has_on_positive_side(p);
    }

  bool                has_on_negative_side(const Point_2<R> &p) const
    {
      return RCircle_2::has_on_negative_side(p);
    }

  bool                has_on_bounded_side(const Point_2<R> &p) const
    {
      return RCircle_2::has_on_bounded_side(p);
    }

  bool                has_on_unbounded_side(const Point_2<R> &p) const
    {
      return RCircle_2::has_on_unbounded_side(p);
    }

  bool                is_degenerate() const
    {
      return RCircle_2::is_degenerate();
    }

  Circle_2<R>     opposite() const
    {
      return Circle_2<R>(center(),
                         squared_radius(),
                         CGAL::opposite(orientation()));
    }

  Bbox_2           bbox() const
    {
      return RCircle_2::bbox();
    }
};


#ifndef NO_OSTREAM_INSERT_CIRCLE_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Circle_2<R> &c)
{
  typedef typename R::Circle_2   RCircle_2;
  return os << (const RCircle_2&)c;
}

#endif // NO_OSTREAM_INSERT_CIRCLE_2

#ifndef NO_ISTREAM_EXTRACT_CIRCLE_2
template < class R >
std::istream &
operator>>(std::istream &is, Circle_2<R> &c)
{
  typedef typename R::Circle_2   RCircle_2;
  return is >> (RCircle_2&)c;
}
#endif // NO_ISTREAM_EXTRACT_CIRCLE_2

CGAL_END_NAMESPACE


#endif  // CGAL_CIRCLE_2_H
