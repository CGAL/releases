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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.4
// release_date  : 2002, May 16
// 
// file          : include/CGAL/Iso_cuboid_3.h
// package       : _3 (3.31)
// revision      : $Revision: 1.11 $
// revision_date : $Date: 2002/01/23 12:30:06 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_ISO_CUBOID_3_H
#define CGAL_ISO_CUBOID_3_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class Iso_cuboid_3 : public R_::Kernel_base::Iso_cuboid_3
{
  typedef typename R_::RT                 RT;
  typedef typename R_::Point_3            Point_3;
  typedef typename R_::Kernel_base::Iso_cuboid_3  RIso_cuboid_3;
public:
  typedef          R_                    R;

  Iso_cuboid_3() : RIso_cuboid_3()
  {}

  Iso_cuboid_3(const CGAL::Iso_cuboid_3<R>& r)
      : RIso_cuboid_3(r) {}

  Iso_cuboid_3(const RIso_cuboid_3&  r)
      : RIso_cuboid_3(r) {}

  Iso_cuboid_3(const Point_3& p, const Point_3& q)
   : RIso_cuboid_3(p,q) {}

  Iso_cuboid_3(const RT& min_hx, const RT& min_hy, const RT& min_hz,
               const RT& max_hx, const RT& max_hy, const RT& max_hz, 
               const RT& hw)
   : RIso_cuboid_3(min_hx, min_hy, min_hz, max_hx, max_hy, max_hz, hw) {}

  Iso_cuboid_3(const RT& min_hx, const RT& min_hy, const RT& min_hz,
               const RT& max_hx, const RT& max_hy, const RT& max_hz)
   : RIso_cuboid_3(min_hx, min_hy, min_hz, max_hx, max_hy, max_hz) {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_ISO_CUBOID_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Iso_cuboid_3<R>& r)
{
  typedef typename  R::Kernel_base::Iso_cuboid_3  RIso_cuboid_3;
  return  os << (const RIso_cuboid_3& )r; }
#endif // CGAL_NO_OSTREAM_INSERT_ISO_CUBOID_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_ISO_CUBOID_3
template < class R >
std::istream&
operator>>(std::istream& is, Iso_cuboid_3<R>& r)
{
  typedef typename  R::Kernel_base::Iso_cuboid_3  RIso_cuboid_3;
  is >> (RIso_cuboid_3& )r;
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_ISO_CUBOID_3

CGAL_END_NAMESPACE

#endif // CGAL_ISO_CUBOID_3_H
