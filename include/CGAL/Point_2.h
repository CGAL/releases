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
// file          : include/CGAL/Point_2.h
// package       : _2 (3.19)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/06/27 14:51:32 $
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_POINT_2_H
#define CGAL_POINT_2_H

#include <CGAL/point_vector_declarations_2.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class Point_2 : public R_::Point_2_base
{
public:
  typedef  R_   R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Point_2_base  RPoint_2;
  typedef typename R::Vector_2_base  RVector_2;


friend  CGAL_FRIEND_INLINE
        CGAL::Point_2<R>
        CGAL_SCOPE vector_to_point_conversion CGAL_NULL_TMPL_ARGS
                                         (const CGAL::Vector_2<R>& v);

  Point_2()
  {}

  Point_2(const Origin& o)
    : RPoint_2(o)
  {}

  Point_2(const CGAL::Point_2<R>& p)
    : RPoint_2(static_cast<const RPoint_2&>(p))
  {}

  Point_2(const RPoint_2& p)
    : RPoint_2(p)
  {}

  Point_2(const RT& hx, const RT& hy)
    : RPoint_2(hx, hy)
  {}

  Point_2(const RT& hx, const RT& hy, const RT& hw)
    : RPoint_2(hx, hy, hw)
  {}

private:

  Point_2(const RVector_2& v)
    : RPoint_2(v)
  {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_POINT_2
template < class R >
std::ostream&
operator<<(std::ostream& os, const Point_2<R>& p)
{
  typedef typename  R::Point_2_base  RPoint_2;
  return os << static_cast<const RPoint_2&>(p);
}
#endif // CGAL_NO_OSTREAM_INSERT_POINT_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINT_2
template < class R >
std::istream&
operator>>(std::istream& is, Point_2<R>& p)
{
  typedef typename  R::Point_2_base  RPoint_2;
  return is >> static_cast<RPoint_2&>(p);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINT_2

CGAL_END_NAMESPACE

#include <CGAL/Vector_2.h>
#include <CGAL/Aff_transformation_2.h>

#endif // CGAL_POINT_2_H
