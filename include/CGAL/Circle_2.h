// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.1
// release_date  : 2000, January 11
// 
// source        : Circle_2.fw
// file          : include/CGAL/Circle_2.h
// package       : _2 (2.8.1)
// revision      : 2.8.1
// revision_date : 07 Nov 1999 
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
#include <CGAL/Cartesian/Circle_2.h>
#endif // CGAL_CIRCLEC2_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H

CGAL_BEGIN_NAMESPACE

template <class _R>
  class Circle_2 : public _R::Circle_2_base
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Circle_2_base  RCircle_2;

    Circle_2()
      : RCircle_2()
    {}

    Circle_2(const CGAL::Circle_2<R> &t)
      : RCircle_2((RCircle_2&)t)
    {}

    Circle_2(const RCircle_2& t)
      : RCircle_2(t)
    {}

    Circle_2(const CGAL::Point_2<R> &center,
                  const FT &squared_radius,
                  const Orientation &orientation)
      : RCircle_2(center, squared_radius, orientation)
    {}

    Circle_2(const CGAL::Point_2<R> &center,
                  const FT &squared_radius)
      : RCircle_2(center, squared_radius, COUNTERCLOCKWISE)
    {}

    Circle_2(const CGAL::Point_2<R> &p,
                  const CGAL::Point_2<R> &q,
                  const CGAL::Point_2<R> &r)
      : RCircle_2(p,q,r)
    {}

    Circle_2(const CGAL::Point_2<R> & p,
                  const CGAL::Point_2<R> & q,
                  const Orientation &orientation)
      : RCircle_2(p,q,orientation)
    {}

    Circle_2(const CGAL::Point_2<R> & p,
                  const CGAL::Point_2<R> & q)
      : RCircle_2(p,q,COUNTERCLOCKWISE)
    {}

    Circle_2(const CGAL::Point_2<R> & center,
                  const Orientation& orientation)
      : RCircle_2(center,FT(0),orientation)
    {}

    Circle_2(const CGAL::Point_2<R> & center)
      : RCircle_2(center,FT(0),COUNTERCLOCKWISE)
    {}


  CGAL::Circle_2<R>  &operator=(const CGAL::Circle_2<R> &t)
    {
      RCircle_2::operator=(t);
      return *this;
    }

  bool                operator==(const CGAL::Circle_2<R> &t) const
    {
      return RCircle_2::operator==(t);
    }

  bool                operator!=(const CGAL::Circle_2<R> &t) const
    {
      return !(*this == t);
    }

  int                 id() const
    {
      return (int)PTR;
    }

  CGAL::Point_2<R>     center() const
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


  CGAL::Circle_2<R>
            orthogonal_transform(const CGAL::Aff_transformation_2<R> &t) const
  {
    return  RCircle_2::orthogonal_transform(t);
  }

/*
  CGAL::Circle_2<R>  transform(const CGAL::Aff_transformation_2<R> &t) const
  {
    return  Circle_2::transform(t);
  }
*/

  Oriented_side           oriented_side(const CGAL::Point_2<R> &p) const
    {
      return RCircle_2::oriented_side(p);
    }

  Bounded_side           bounded_side(const CGAL::Point_2<R> &p) const
    {
      return RCircle_2::bounded_side(p);
    }

  bool                has_on_boundary(const CGAL::Point_2<R> &p) const
    {
      return RCircle_2::has_on_boundary(p);
    }

  bool                has_on_positive_side(const CGAL::Point_2<R> &p) const
    {
      return RCircle_2::has_on_positive_side(p);
    }

  bool                has_on_negative_side(const CGAL::Point_2<R> &p) const
    {
      return RCircle_2::has_on_negative_side(p);
    }

  bool                has_on_bounded_side(const CGAL::Point_2<R> &p) const
    {
      return RCircle_2::has_on_bounded_side(p);
    }

  bool                has_on_unbounded_side(const CGAL::Point_2<R> &p) const
    {
      return RCircle_2::has_on_unbounded_side(p);
    }

  bool                is_degenerate() const
    {
      return RCircle_2::is_degenerate();
    }

  CGAL::Circle_2<R>     opposite() const
    {
      return CGAL::Circle_2<R>(center(),
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
  typedef typename R::Circle_2_base  RCircle_2;
  return os << (const RCircle_2&)c;
}

#endif // NO_OSTREAM_INSERT_CIRCLE_2

#ifndef NO_ISTREAM_EXTRACT_CIRCLE_2
template < class R >
std::istream &
operator>>(std::istream &is, Circle_2<R> &c)
{
  typedef typename R::Circle_2_base  RCircle_2;
  return is >> (RCircle_2&)c;
}
#endif // NO_ISTREAM_EXTRACT_CIRCLE_2

CGAL_END_NAMESPACE


#endif  // CGAL_CIRCLE_2_H
