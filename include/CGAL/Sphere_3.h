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
// file          : include/CGAL/Sphere_3.h
// package       : _3 (3.23)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/06/20 12:25:25 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SPHERE_3_H
#define CGAL_SPHERE_3_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class Sphere_3 : public R_::Sphere_3_base
{
public:

  typedef          R_                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Sphere_3_base  RSphere_3;

      Sphere_3()
      {}

      Sphere_3(const RSphere_3& s)
      : RSphere_3(s)
      {}

      Sphere_3(const CGAL::Point_3<R>& p, const FT& sq_rad,
               const Orientation& o = COUNTERCLOCKWISE)
       : RSphere_3(p, sq_rad, o)
      {}

      Sphere_3(const CGAL::Point_3<R>& p, const CGAL::Point_3<R>& q,
               const CGAL::Point_3<R>& r, const CGAL::Point_3<R>& u)
       : RSphere_3(p, q, r, u)
      {}

      Sphere_3(const CGAL::Point_3<R>& p, const CGAL::Point_3<R>& q,
               const CGAL::Point_3<R>& r,
               const Orientation& o = COUNTERCLOCKWISE)
       : RSphere_3(p, q, r, o)
      {}

      Sphere_3(const CGAL::Point_3<R>&  p, const CGAL::Point_3<R>&  q,
               const Orientation& o = COUNTERCLOCKWISE)
       : RSphere_3(p, q, o)
      {}

      Sphere_3(const CGAL::Point_3<R>&  p,
               const Orientation& o = COUNTERCLOCKWISE)
       : RSphere_3(p, o)
      {}
};

CGAL_END_NAMESPACE

#endif // CGAL_SPHERE_3_H
