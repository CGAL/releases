// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.3
// release_date  : 2001, August 13
// 
// file          : include/CGAL/Point_3.h
// package       : _3 (3.23)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/06/27 14:49:53 $
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_POINT_3_H
#define CGAL_POINT_3_H

#include <CGAL/point_vector_declarations_3.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class Point_3 : public R_::Point_3_base
{
public:
  typedef          R_                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Point_3_base  RPoint_3;
  typedef typename R::Vector_3_base  RVector_3;

friend  CGAL_FRIEND_INLINE
        CGAL::Point_3<R>
        vector_to_point_conversion CGAL_NULL_TMPL_ARGS
                                            (const CGAL::Vector_3<R>& v);

public:
  Point_3()
  {}

  Point_3(const Origin& o) : RPoint_3(o)
  {}

  Point_3(const CGAL::Point_3<R>& p)
      : RPoint_3( static_cast<const RPoint_3&>(p) )
  {}

  Point_3(const RPoint_3&  p) : RPoint_3(p)
  {}

  Point_3(const RT& hx, const RT& hy, const RT& hz)
    : RPoint_3(hx, hy, hz)
  {}

  Point_3(const RT& hx, const RT& hy, const RT& hz, const RT& hw)
    : RPoint_3(hx, hy, hz, hw)
  {}

  CGAL::Point_3<R> transform(const CGAL::Aff_transformation_3<R>& t) const
  { return RPoint_3::transform(t); }

private:
  Point_3(const RVector_3&  v) : RPoint_3(v)
  {}
};

CGAL_END_NAMESPACE

#include <CGAL/Vector_3.h>
#include <CGAL/Aff_transformation_3.h>

CGAL_BEGIN_NAMESPACE

template <class R>
inline
bool
operator==(const Origin& o, const Point_3<R>& p)
{ return p == o; }

template <class R>
inline
bool
operator!=(const Origin& o, const Point_3<R>& p)
{ return p != o; }

#ifndef CGAL_NO_OSTREAM_INSERT_POINT_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Point_3<R>& p)
{
  typedef typename  R::Point_3_base  RPoint_3;
  return os << static_cast<const RPoint_3&>(p);
}
#endif // CGAL_NO_OSTREAM_INSERT_POINT_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINT_3
template < class R >
std::istream& operator>>(std::istream& is, Point_3<R>& p)
{
  typedef typename  R::Point_3_base  RPoint_3;
  return is >> static_cast<RPoint_3&>(p);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINT_3

CGAL_END_NAMESPACE

#endif // CGAL_POINT_3_H
