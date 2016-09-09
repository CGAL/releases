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
// file          : include/CGAL/Iso_rectangle_2.h
// package       : _2 (3.32)
// revision      : $Revision: 1.11 $
// revision_date : $Date: 2002/01/23 12:28:30 $
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ISO_RECTANGLE_2_H
#define CGAL_ISO_RECTANGLE_2_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class Iso_rectangle_2 : public R_::Kernel_base::Iso_rectangle_2
{
  typedef typename R_::RT                    RT;
  typedef typename R_::Point_2               Point_2;
  typedef typename R_::Kernel_base::Iso_rectangle_2  RIso_rectangle_2;
public:
  typedef  R_   R;

  Iso_rectangle_2()
    : RIso_rectangle_2() {}

  Iso_rectangle_2(const CGAL::Iso_rectangle_2<R> &r)
    : RIso_rectangle_2(r) {}

  Iso_rectangle_2(const RIso_rectangle_2& r)
    : RIso_rectangle_2(r) {}

  Iso_rectangle_2(const Point_2 &p, const Point_2 &q)
    : RIso_rectangle_2(p,q) {}

  Iso_rectangle_2(const RT& min_hx, const RT& min_hy, 
                  const RT& max_hx, const RT& max_hy)
    : RIso_rectangle_2(min_hx, min_hy, max_hx, max_hy) {}

  Iso_rectangle_2(const RT& min_hx, const RT& min_hy, 
                  const RT& max_hx, const RT& max_hy, const RT& hw)
    : RIso_rectangle_2(min_hx, min_hy, max_hx, max_hy, hw) {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_ISO_RECTANGLE_2
template < class R >
std::ostream &
operator<<(std::ostream &os, const Iso_rectangle_2<R> &r)
{
  typedef typename R::Kernel_base::Iso_rectangle_2  RIso_rectangle_2;
  return  os << (const RIso_rectangle_2&)r;
}
#endif // CGAL_NO_OSTREAM_INSERT_ISO_RECTANGLE_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_ISO_RECTANGLE_2
template < class R >
std::istream &
operator>>(std::istream &is, Iso_rectangle_2<R> &r)
{
  typedef typename R::Kernel_base::Iso_rectangle_2  RIso_rectangle_2;
  is >> (RIso_rectangle_2&)r;
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_ISO_RECTANGLE_2

CGAL_END_NAMESPACE

#endif // CGAL_ISO_RECTANGLE_2_H
