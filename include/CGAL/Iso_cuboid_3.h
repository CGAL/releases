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
// source        : Iso_cuboid_3.fw
// file          : include/CGAL/Iso_cuboid_3.h
// package       : _3 (3.7)
// revision      : 3.7
// revision_date : 16 Aug 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_ISO_CUBOID_3_H
#define CGAL_ISO_CUBOID_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/Iso_cuboidH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/Cartesian/Iso_cuboid_3.h>
#endif // CGAL_CARTESIAN_H

#ifdef CGAL_SIMPLE_CARTESIAN_H
#include <CGAL/SimpleCartesian/Iso_cuboidS3.h>
#endif // CGAL_SIMPLE_CARTESIAN_H


#include <CGAL/Point_3.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class Iso_cuboid_3 : public R_::Iso_cuboid_3_base
{
public:
  typedef          R_                    R;
  typedef typename R::RT                 RT;
  typedef typename R::FT                 FT;
  typedef typename R::Iso_cuboid_3_base  RIso_cuboid_3;

  Iso_cuboid_3() : RIso_cuboid_3()
  {}

  Iso_cuboid_3(const CGAL::Iso_cuboid_3<R>& r) : RIso_cuboid_3(r)
  {}

  Iso_cuboid_3(const RIso_cuboid_3&  r) : RIso_cuboid_3(r)
  {}

  Iso_cuboid_3(const CGAL::Point_3<R>& p, const CGAL::Point_3<R>& q)
   : RIso_cuboid_3(p,q)
  {}

/*
  bool     operator==(const CGAL::Iso_cuboid_3<R>& r) const
           { return (const RIso_cuboid_3& )*this == (const RIso_cuboid_3& )r ; }
  bool     operator!=(const CGAL::Iso_cuboid_3<R>& r) const
           { return !(*this == r); }
  CGAL::Point_3<R>
           min() const
           { return RIso_cuboid_3::min(); }
  CGAL::Point_3<R>
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
  CGAL::Point_3<R>
           vertex(int i) const
           { return RIso_cuboid_3::vertex(i); }
  CGAL::Point_3<R>
           operator[](int i) const
           { return vertex(i); }
  Bounded_side
           bounded_side(const CGAL::Point_3<R>& p) const
           { return RIso_cuboid_3::bounded_side(p); }
  bool     has_on_boundary(const CGAL::Point_3<R>& p) const
           { return RIso_cuboid_3::has_on_boundary(p); }
  bool     has_on_bounded_side(const CGAL::Point_3<R>& p) const
           { return RIso_cuboid_3::has_on_bounded_side(p); }
  bool     has_on_unbounded_side(const CGAL::Point_3<R>& p) const
           { return RIso_cuboid_3::has_on_unbounded_side(p); }
  bool     is_degenerate() const
           { return RIso_cuboid_3::is_degenerate(); }
  CGAL::Iso_cuboid_3<R>
           transform(const CGAL::Aff_transformation_3<R>& t) const
           { return RIso_cuboid_3::transform(t); }
*/
};

#ifndef NO_OSTREAM_INSERT_ISO_CUBOID_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Iso_cuboid_3<R>& r)
{
  typedef typename  R::Iso_cuboid_3_base  RIso_cuboid_3;
  return  os << (const RIso_cuboid_3& )r; }
#endif // NO_OSTREAM_INSERT_ISO_CUBOID_3

#ifndef NO_ISTREAM_EXTRACT_ISO_CUBOID_3
template < class R >
std::istream&
operator>>(std::istream& is, Iso_cuboid_3<R>& r)
{
  typedef typename  R::Iso_cuboid_3_base  RIso_cuboid_3;
  is >> (RIso_cuboid_3& )r;
  return is;
}
#endif // NO_ISTREAM_EXTRACT_ISO_CUBOID_3

CGAL_END_NAMESPACE


#endif // CGAL_ISO_CUBOID_3_H
