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
// file          : include/CGAL/Triangle_2.h
// package       : _2 (3.19)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/06/27 14:51:35 $
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_TRIANGLE_2_H
#define CGAL_TRIANGLE_2_H

#include <CGAL/Point_2.h>
#include <CGAL/Aff_transformation_2.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class Triangle_2 : public R_::Triangle_2_base
{
public:
  typedef  R_                          R;
  typedef typename R::RT               RT;
  typedef typename R::FT               FT;
  typedef typename R::Triangle_2_base  RTriangle_2;

  Triangle_2() : RTriangle_2() {}

  Triangle_2(const CGAL::Triangle_2<R> &t) : RTriangle_2((RTriangle_2&)t) {}

  Triangle_2(const RTriangle_2& t) : RTriangle_2(t) {}

  Triangle_2(const CGAL::Point_2<R> &p,
             const CGAL::Point_2<R> &q,
             const CGAL::Point_2<R> &r) : RTriangle_2(p,q,r) {}

  CGAL::Point_2<R>
  vertex(int i) const
  { return RTriangle_2::vertex(i); }

  CGAL::Point_2<R>
  operator[](int i) const
  { return vertex(i); }

  CGAL::Triangle_2<R>
  transform(const CGAL::Aff_transformation_2<R> &t) const
  { return  RTriangle_2::transform(t); }

  CGAL::Triangle_2<R>  opposite() const
  { return  CGAL::Triangle_2<R>(vertex(0), vertex(2), vertex(1)); }
};

#ifndef CGAL_NO_OSTREAM_INSERT_TRIANGLE_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Triangle_2<R> &t)
{
  typedef typename  R::Triangle_2_base  RTriangle_2;
  return os << (const RTriangle_2&)t;
}
#endif // CGAL_NO_OSTREAM_INSERT_TRIANGLE_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_TRIANGLE_2
template < class R >
std::istream &
operator>>(std::istream &is, Triangle_2<R> &t)
{
  typedef typename  R::Triangle_2_base  RTriangle_2;
  return is >> (RTriangle_2&)t;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TRIANGLE_2

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGLE_2_H
