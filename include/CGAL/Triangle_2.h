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
// file          : include/CGAL/Triangle_2.h
// author(s)     : Andreas Fabri
//
// email         : cgal@cs.uu.nl
//
// ============================================================================
 

#ifndef CGAL_TRIANGLE_2_H
#define CGAL_TRIANGLE_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED


#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_TRIANGLEH2_H
#include <CGAL/TriangleH2.h>
#endif // CGAL_TRIANGLEH2_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_TRIANGLEC2_H
#include <CGAL/TriangleC2.h>
#endif // CGAL_TRIANGLEC2_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H

template <class _R>
  class CGAL_Triangle_2 : public _R::Triangle_2
{
public:
  typedef  _R   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Triangle_2            Triangle_2;

    CGAL_Triangle_2()
      : Triangle_2()
    {}

    CGAL_Triangle_2(const CGAL_Triangle_2<R> &t)
      : Triangle_2((Triangle_2&)t)
    {}

    CGAL_Triangle_2(const Triangle_2 &t)
      : Triangle_2(t)
    {}

    CGAL_Triangle_2(const CGAL_Point_2<R> &p,
                    const CGAL_Point_2<R> &q,
                    const CGAL_Point_2<R> &r)
      : Triangle_2(p,q,r)
    {}


  CGAL_Triangle_2<R>  &operator=(const CGAL_Triangle_2<R> &t)
    {
      Triangle_2::operator=(t);
      return *this;
    }

  bool                operator==(const CGAL_Triangle_2<R> &t) const
    {
      return Triangle_2::operator==(t);
    }

  bool                operator!=(const CGAL_Triangle_2<R> &t) const
    {
      return !(*this == t);
    }

  int                id() const
    {
      return (int) PTR;
    }


  CGAL_Point_2<R>     vertex(int i) const
    {
      return Triangle_2::vertex(i);
    }

  CGAL_Point_2<R>     operator[](int i) const
    {
      return vertex(i);
    }


  CGAL_Triangle_2<R>  transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  Triangle_2::transform(t);
  }

  CGAL_Triangle_2<R>  opposite() const
  {
    return  CGAL_Triangle_2<R>(vertex(0), vertex(2), vertex(1));
  }

  CGAL_Orientation  orientation() const
    {
      return Triangle_2::orientation();
    }

  CGAL_Oriented_side           oriented_side(const CGAL_Point_2<R> &p) const
    {
      return Triangle_2::oriented_side(p);
    }

  CGAL_Bounded_side           bounded_side(const CGAL_Point_2<R> &p) const
    {
      return Triangle_2::bounded_side(p);
    }

  bool                has_on_boundary(const CGAL_Point_2<R> &p) const
    {
      return Triangle_2::has_on_boundary(p);
    }

  bool                has_on_positive_side(const CGAL_Point_2<R> &p) const
    {
      return Triangle_2::has_on_positive_side(p);
    }

  bool                has_on_negative_side(const CGAL_Point_2<R> &p) const
    {
      return Triangle_2::has_on_negative_side(p);
    }

  bool                has_on_unbounded_side(const CGAL_Point_2<R> &p) const
    {
      return Triangle_2::has_on_unbounded_side(p);
    }

  bool                has_on_bounded_side(const CGAL_Point_2<R> &p) const
    {
      return Triangle_2::has_on_bounded_side(p);
    }

  bool                is_degenerate() const
    {
      return Triangle_2::is_degenerate();
    }

  CGAL_Bbox_2           bbox() const
    {
      return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
    }
};

#ifndef CGAL_NO_OSTREAM_INSERT_TRIANGLE_2
template < class R >
ostream &
operator<<(ostream &os, const CGAL_Triangle_2<R> &t)
{
  typedef typename  R::Triangle_2      Triangle_2;
  return os << (const Triangle_2&)t;
}
#endif // CGAL_NO_OSTREAM_INSERT_TRIANGLE_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_TRIANGLE_2
template < class R >
istream &
operator>>(istream &is, CGAL_Triangle_2<R> &t)
{
  typedef typename  R::Triangle_2      Triangle_2;
  return is >> (Triangle_2&)t;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TRIANGLE_2



#endif
