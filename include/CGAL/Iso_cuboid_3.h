// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.2
// release_date  : 1999, January 18
// 
// source        : Iso_cuboid_3.fw
// file          : include/CGAL/Iso_cuboid_3.h
// package       : _3 (1.4)
// revision      : 1.4
// revision_date : 15 Dec 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_ISO_CUBOID_3_H
#define CGAL_ISO_CUBOID_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_ISO_CUBOIDH3_H
#include <CGAL/Iso_cuboidH3.h>
#endif // CGAL_ISO_CUBOIDH3_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_ISO_CUBOIDC3_H
#include <CGAL/Iso_cuboidC3.h>
#endif // CGAL_ISO_CUBOIDC3_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif // CGAL_POINT_3_H

template <class _R>
class CGAL_Iso_cuboid_3 : public _R::Iso_cuboid_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Iso_cuboid_3          Iso_cuboid_3;

  CGAL_Iso_cuboid_3() : Iso_cuboid_3() {}
  CGAL_Iso_cuboid_3(const CGAL_Iso_cuboid_3<R>& r)
    : Iso_cuboid_3(r)
  {}
  CGAL_Iso_cuboid_3(const R::Iso_cuboid_3& r) : Iso_cuboid_3(r)
  {}
  CGAL_Iso_cuboid_3(const CGAL_Point_3<R>& p,
                    const CGAL_Point_3<R>& q)
    : Iso_cuboid_3(p,q)
  {}


  CGAL_Iso_cuboid_3<R>& operator=(const CGAL_Iso_cuboid_3<R>& r)
  {
    Iso_cuboid_3::operator=(r);
    return *this;
  }
  bool     operator==(const CGAL_Iso_cuboid_3<R>& r) const
           { return (const Iso_cuboid_3&)*this == (const Iso_cuboid_3&)r ; }
  bool     operator!=(const CGAL_Iso_cuboid_3<R>& r) const
           { return !(*this == r); }
  int      id() const   /* XXX */
           { return (int) PTR; }
  CGAL_Point_3<R>
           min() const
           { return Iso_cuboid_3::min(); }
  CGAL_Point_3<R>
           max() const
           { return Iso_cuboid_3::max(); }
  FT       xmin() const
           { return Iso_cuboid_3::xmin(); }
  FT       ymin() const
           { return Iso_cuboid_3::ymin(); }
  FT       zmin() const
           { return Iso_cuboid_3::zmin(); }
  FT       xmax() const
           { return Iso_cuboid_3::xmax(); }
  FT       ymax() const
           { return Iso_cuboid_3::ymax(); }
  FT       zmax() const
           { return Iso_cuboid_3::zmax(); }
  CGAL_Point_3<R>
           vertex(int i) const
           { return Iso_cuboid_3::vertex(i); }
  CGAL_Point_3<R>
           operator[](int i) const
           { return vertex(i); }
  CGAL_Bounded_side
           bounded_side(const CGAL_Point_3<R>& p) const
           { return Iso_cuboid_3::bounded_side(p); }
  bool     has_on_boundary(const CGAL_Point_3<R>& p) const
           { return Iso_cuboid_3::has_on_boundary(p); }
  bool     has_on_bounded_side(const CGAL_Point_3<R>& p) const
           { return Iso_cuboid_3::has_on_bounded_side(p); }
  bool     has_on_unbounded_side(const CGAL_Point_3<R>& p) const
           { return Iso_cuboid_3::has_on_unbounded_side(p); }
  bool     is_degenerate() const
           { return Iso_cuboid_3::is_degenerate(); }
  CGAL_Iso_cuboid_3<R>
           transform(const CGAL_Aff_transformation_3<R>& t) const
           { return Iso_cuboid_3::transform(t); }
};

#ifndef CGAL_NO_OSTREAM_INSERT_ISO_CUBOID_3
template < class R >
ostream&
operator<<(ostream& os, const CGAL_Iso_cuboid_3<R>& r)
{
  typedef typename  R::Iso_cuboid_3   Iso_cuboid_3;
  return  os << (const Iso_cuboid_3&)r; }
#endif // CGAL_NO_OSTREAM_INSERT_ISO_CUBOID_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_ISO_CUBOID_3
template < class R >
istream&
operator>>(istream& is, CGAL_Iso_cuboid_3<R>& r)
{
  typedef typename  R::Iso_cuboid_3   Iso_cuboid_3;
  is >> (Iso_cuboid_3&)r;
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_ISO_CUBOID_3


#endif // CGAL_ISO_CUBOID_3_H
