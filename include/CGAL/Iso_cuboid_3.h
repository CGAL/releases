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
// source        : Iso_cuboid_3.fw
// file          : include/CGAL/Iso_cuboid_3.h
// package       : _3 (2.1.2)
// revision      : 2.1.2
// revision_date : 21 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
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
#ifndef ISO_CUBOIDC3_H
#include <CGAL/Iso_cuboidC3.h>
#endif // ISO_CUBOIDC3_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif // CGAL_POINT_3_H

CGAL_BEGIN_NAMESPACE

template <class _R>
class Iso_cuboid_3 : public _R::Iso_cuboid_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Iso_cuboid_3          RIso_cuboid_3;

  Iso_cuboid_3() : RIso_cuboid_3() {}
  Iso_cuboid_3(const Iso_cuboid_3<R>& r)
    : RIso_cuboid_3(r)
  {}
  Iso_cuboid_3(const R::RIso_cuboid_3&  r) : RIso_cuboid_3(r)
  {}
  Iso_cuboid_3(const Point_3<R>& p,
                    const Point_3<R>& q)
    : RIso_cuboid_3(p,q)
  {}


  Iso_cuboid_3<R>& operator=(const Iso_cuboid_3<R>& r)
  {
    RIso_cuboid_3::operator=(r);
    return *this;
  }
  bool     operator==(const Iso_cuboid_3<R>& r) const
           { return (const RIso_cuboid_3& )*this == (const RIso_cuboid_3& )r ; }
  bool     operator!=(const Iso_cuboid_3<R>& r) const
           { return !(*this == r); }
  int      id() const   /* XXX */
           { return (int) PTR; }
  Point_3<R>
           min() const
           { return RIso_cuboid_3::min(); }
  Point_3<R>
           max() const
           { return RIso_cuboid_3::max(); }
  FT       xmin() const
           { return RIso_cuboid_3::xmin(); }
  FT       ymin() const
           { return RIso_cuboid_3::ymin(); }
  FT       zmin() const
           { return RIso_cuboid_3::zmin(); }
  FT       xmax() const
           { return RIso_cuboid_3::xmax(); }
  FT       ymax() const
           { return RIso_cuboid_3::ymax(); }
  FT       zmax() const
           { return RIso_cuboid_3::zmax(); }
  Point_3<R>
           vertex(int i) const
           { return RIso_cuboid_3::vertex(i); }
  Point_3<R>
           operator[](int i) const
           { return vertex(i); }
  Bounded_side
           bounded_side(const Point_3<R>& p) const
           { return RIso_cuboid_3::bounded_side(p); }
  bool     has_on_boundary(const Point_3<R>& p) const
           { return RIso_cuboid_3::has_on_boundary(p); }
  bool     has_on_bounded_side(const Point_3<R>& p) const
           { return RIso_cuboid_3::has_on_bounded_side(p); }
  bool     has_on_unbounded_side(const Point_3<R>& p) const
           { return RIso_cuboid_3::has_on_unbounded_side(p); }
  bool     is_degenerate() const
           { return RIso_cuboid_3::is_degenerate(); }
  Iso_cuboid_3<R>
           transform(const Aff_transformation_3<R>& t) const
           { return RIso_cuboid_3::transform(t); }
};

#ifndef NO_OSTREAM_INSERT_ISO_CUBOID_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Iso_cuboid_3<R>& r)
{
  typedef typename  R::Iso_cuboid_3   RIso_cuboid_3;
  return  os << (const RIso_cuboid_3& )r; }
#endif // NO_OSTREAM_INSERT_ISO_CUBOID_3

#ifndef NO_ISTREAM_EXTRACT_ISO_CUBOID_3
template < class R >
std::istream&
operator>>(std::istream& is, Iso_cuboid_3<R>& r)
{
  typedef typename  R::Iso_cuboid_3   RIso_cuboid_3;
  is >> (RIso_cuboid_3& )r;
  return is;
}
#endif // NO_ISTREAM_EXTRACT_ISO_CUBOID_3

CGAL_END_NAMESPACE


#endif // CGAL_ISO_CUBOID_3_H
