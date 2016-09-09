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
// file          : include/CGAL/Sphere_3.h
// package       : _3 (3.31)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2002/01/23 12:30:10 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SPHERE_3_H
#define CGAL_SPHERE_3_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class Sphere_3 : public R_::Kernel_base::Sphere_3
{
  typedef typename R_::FT                    FT;
  typedef typename R_::Point_3               Point_3;
  typedef typename R_::Kernel_base::Sphere_3  RSphere_3;
public:
  typedef          R_                       R;

      Sphere_3()
      {}

      Sphere_3(const RSphere_3& s)
      : RSphere_3(s) {}

      Sphere_3(const Point_3& p, const FT& sq_rad,
               const Orientation& o = COUNTERCLOCKWISE)
       : RSphere_3(p, sq_rad, o) {}

      Sphere_3(const Point_3& p, const Point_3& q,
               const Point_3& r, const Point_3& u)
       : RSphere_3(p, q, r, u) {}

      Sphere_3(const Point_3& p, const Point_3& q, const Point_3& r,
               const Orientation& o = COUNTERCLOCKWISE)
       : RSphere_3(p, q, r, o) {}

      Sphere_3(const Point_3& p, const Point_3&  q,
               const Orientation& o = COUNTERCLOCKWISE)
       : RSphere_3(p, q, o) {}

      Sphere_3(const Point_3& p, const Orientation& o = COUNTERCLOCKWISE)
       : RSphere_3(p, o) {}
};

CGAL_END_NAMESPACE

#endif // CGAL_SPHERE_3_H
