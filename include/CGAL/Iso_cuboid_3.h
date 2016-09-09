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
// file          : include/CGAL/Iso_cuboid_3.h
// package       : _3 (3.23)
// revision      : $Revision: 1.9 $
// revision_date : $Date: 2001/06/27 14:49:52 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_ISO_CUBOID_3_H
#define CGAL_ISO_CUBOID_3_H

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

  Iso_cuboid_3(const RT& min_hx, const RT& min_hy, const RT& min_hz,
               const RT& max_hx, const RT& max_hy, const RT& max_hz, 
               const RT& hw)
   : RIso_cuboid_3(min_hx, min_hy, min_hz, max_hx, max_hy, max_hz, hw)
  {}

  Iso_cuboid_3(const RT& min_hx, const RT& min_hy, const RT& min_hz,
               const RT& max_hx, const RT& max_hy, const RT& max_hz)
   : RIso_cuboid_3(min_hx, min_hy, min_hz, max_hx, max_hy, max_hz)
  {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_ISO_CUBOID_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Iso_cuboid_3<R>& r)
{
  typedef typename  R::Iso_cuboid_3_base  RIso_cuboid_3;
  return  os << (const RIso_cuboid_3& )r; }
#endif // CGAL_NO_OSTREAM_INSERT_ISO_CUBOID_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_ISO_CUBOID_3
template < class R >
std::istream&
operator>>(std::istream& is, Iso_cuboid_3<R>& r)
{
  typedef typename  R::Iso_cuboid_3_base  RIso_cuboid_3;
  is >> (RIso_cuboid_3& )r;
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_ISO_CUBOID_3

CGAL_END_NAMESPACE

#endif // CGAL_ISO_CUBOID_3_H
