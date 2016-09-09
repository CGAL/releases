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
// file          : include/CGAL/Tetrahedron_3.h
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// email         : cgal@cs.uu.nl
//
// ============================================================================
 

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
#include <CGAL/TetrahedronC3.h>
#endif // CGAL_TETRAHEDRONC3_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_PLANE_3_H
#include <CGAL/Plane_3.h>
#endif // CGAL_PLANE_3_H

template <class _R>
class CGAL_Tetrahedron_3 : public _R::Tetrahedron_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Tetrahedron_3         Tetrahedron_3;

  CGAL_Tetrahedron_3() : Tetrahedron_3()
  {}
  CGAL_Tetrahedron_3(const CGAL_Tetrahedron_3<R>& t) : Tetrahedron_3(t)
  {}
  CGAL_Tetrahedron_3(const Tetrahedron_3& t) : Tetrahedron_3(t)
  {}
  CGAL_Tetrahedron_3(const CGAL_Point_3<R>& p,
                     const CGAL_Point_3<R>& q,
                     const CGAL_Point_3<R>& r,
                     const CGAL_Point_3<R>& s)
    : Tetrahedron_3(p,q,r,s)
  {}

  CGAL_Tetrahedron_3<R>&
                     operator=(const CGAL_Tetrahedron_3<R>& t)
                     {
                       Tetrahedron_3::operator=(t);
                       return *this;
                     }
  CGAL_Point_3<R>    vertex(int i) const
                     { return Tetrahedron_3::vertex(i); }
  CGAL_Point_3<R>    operator[](int i) const
                     { return vertex(i); }
  bool               operator==(const CGAL_Tetrahedron_3<R>& t) const
                     { return Tetrahedron_3::operator==(t); }
  bool               operator!=(const CGAL_Tetrahedron_3<R>& t) const
                     { return !(*this == t); }
  int                id() const    /* XXX */
                     { return (int)PTR ; }
  CGAL_Bbox_3        bbox() const
                     {
                       return vertex(0).bbox() + vertex(1).bbox()
                            + vertex(2).bbox() + vertex(3).bbox();
                     }
  CGAL_Tetrahedron_3<R>
                     transform(const CGAL_Aff_transformation_3<R>& t) const
                     {
                       return
                       CGAL_Tetrahedron_3<R>(Tetrahedron_3::transform(t));
                     }
  CGAL_Orientation   orientation() const
                     { return Tetrahedron_3::orientation(); }
  CGAL_Oriented_side oriented_side(const CGAL_Point_3<R>& p) const
                     { return Tetrahedron_3::oriented_side(p); }
  bool               has_on_positive_side(const CGAL_Point_3<R>& p) const
                     { return oriented_side(p) == CGAL_ON_POSITIVE_SIDE; }
  bool               has_on_negative_side(const CGAL_Point_3<R>& p) const
                     { return oriented_side(p) == CGAL_ON_NEGATIVE_SIDE; }
  CGAL_Bounded_side  bounded_side(const CGAL_Point_3<R>& p) const
                     { return Tetrahedron_3::bounded_side(p); }
  bool               has_on_boundary(const CGAL_Point_3<R>& p) const
                     { return bounded_side(p) == CGAL_ON_BOUNDARY; }
  bool               has_on_bounded_side(const CGAL_Point_3<R>& p) const
                     { return bounded_side(p) == CGAL_ON_BOUNDED_SIDE; }
  bool               has_on_unbounded_side(const CGAL_Point_3<R>& p) const
                     { return bounded_side(p) == CGAL_ON_UNBOUNDED_SIDE; }
  bool               is_degenerate() const
                     { return Tetrahedron_3::is_degenerate(); }
};

#ifndef CGAL_NO_OSTREAM_INSERT_TETRAHEDRON_3
template < class R >
ostream&
operator<<(ostream& os, const CGAL_Tetrahedron_3<R>& t)
{
  typedef typename  R::Tetrahedron_3       Tetrahedron_3;
  return os << (const Tetrahedron_3&)t;
}
#endif // CGAL_NO_OSTREAM_INSERT_TETRAHEDRON_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRON_3
template < class R >
istream&
operator>>(istream& is, CGAL_Tetrahedron_3<R>& t)
{
  typedef typename  R::Tetrahedron_3       Tetrahedron_3;
  return is >> (Tetrahedron_3&)t;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRON_3



#endif  // CGAL_TETRAHEDRON_3_H
