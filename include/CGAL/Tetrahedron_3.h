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
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : Tetrahedron_3.fw
// file          : include/CGAL/Tetrahedron_3.h
// package       : _3 (3.7)
// revision      : 3.7
// revision_date : 16 Aug 2000 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_TETRAHEDRON_3_H
#define CGAL_TETRAHEDRON_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_TETRAHEDRONH3_H
#include <CGAL/TetrahedronH3.h>
#endif // CGAL_TETRAHEDRONH3_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_TETRAHEDRONC3_H
#include <CGAL/Cartesian/Tetrahedron_3.h>
#endif // CGAL_TETRAHEDRONC3_H
#endif // CGAL_CARTESIAN_H

#ifdef CGAL_SIMPLE_CARTESIAN_H
#include <CGAL/SimpleCartesian/TetrahedronS3.h>
#endif // CGAL_SIMPLE_CARTESIAN_H


#ifndef CGAL_PLANE_3_H
#include <CGAL/Plane_3.h>
#endif // CGAL_PLANE_3_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class Tetrahedron_3 : public R_::Tetrahedron_3_base
{
public:
  typedef          R_                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Tetrahedron_3_base  RTetrahedron_3;

  Tetrahedron_3() : RTetrahedron_3()
  {}
  Tetrahedron_3(const CGAL::Tetrahedron_3<R>& t) : RTetrahedron_3(t)
  {}
  Tetrahedron_3(const RTetrahedron_3&  t) : RTetrahedron_3(t)
  {}
  Tetrahedron_3(const CGAL::Point_3<R>& p,
                     const CGAL::Point_3<R>& q,
                     const CGAL::Point_3<R>& r,
                     const CGAL::Point_3<R>& s)
    : RTetrahedron_3(p,q,r,s)
  {}

  CGAL::Point_3<R>    vertex(int i) const
                     { return RTetrahedron_3::vertex(i); }
  CGAL::Point_3<R>    operator[](int i) const
                     { return vertex(i); }
  bool               operator==(const CGAL::Tetrahedron_3<R>& t) const
                     { return RTetrahedron_3::operator==(t); }
  bool               operator!=(const CGAL::Tetrahedron_3<R>& t) const
                     { return !(*this == t); }
  Bbox_3        bbox() const
                     {
                       return vertex(0).bbox() + vertex(1).bbox()
                            + vertex(2).bbox() + vertex(3).bbox();
                     }
  CGAL::Tetrahedron_3<R>
                     transform(const CGAL::Aff_transformation_3<R>& t) const
                     {
                       return
                       CGAL::Tetrahedron_3<R>(RTetrahedron_3::transform(t));
                     }
  Orientation   orientation() const
                     { return RTetrahedron_3::orientation(); }
  Oriented_side oriented_side(const CGAL::Point_3<R>& p) const
                     { return RTetrahedron_3::oriented_side(p); }
  bool               has_on_positive_side(const CGAL::Point_3<R>& p) const
                     { return oriented_side(p) == ON_POSITIVE_SIDE; }
  bool               has_on_negative_side(const CGAL::Point_3<R>& p) const
                     { return oriented_side(p) == ON_NEGATIVE_SIDE; }
  Bounded_side  bounded_side(const CGAL::Point_3<R>& p) const
                     { return RTetrahedron_3::bounded_side(p); }
  bool               has_on_boundary(const CGAL::Point_3<R>& p) const
                     { return bounded_side(p) == ON_BOUNDARY; }
  bool               has_on_bounded_side(const CGAL::Point_3<R>& p) const
                     { return bounded_side(p) == ON_BOUNDED_SIDE; }
  bool               has_on_unbounded_side(const CGAL::Point_3<R>& p) const
                     { return bounded_side(p) == ON_UNBOUNDED_SIDE; }
  bool               is_degenerate() const
                     { return RTetrahedron_3::is_degenerate(); }
};

#ifndef NO_OSTREAM_INSERT_TETRAHEDRON_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Tetrahedron_3<R>& t)
{
  typedef typename  R::Tetrahedron_3_base  RTetrahedron_3;
  return os << (const RTetrahedron_3& )t;
}
#endif // NO_OSTREAM_INSERT_TETRAHEDRON_3

#ifndef NO_ISTREAM_EXTRACT_TETRAHEDRON_3
template < class R >
std::istream&
operator>>(std::istream& is, Tetrahedron_3<R>& t)
{
  typedef typename  R::Tetrahedron_3_base  RTetrahedron_3;
  return is >> (RTetrahedron_3& )t;
}
#endif // NO_ISTREAM_EXTRACT_TETRAHEDRON_3


CGAL_END_NAMESPACE


#endif  // CGAL_TETRAHEDRON_3_H
