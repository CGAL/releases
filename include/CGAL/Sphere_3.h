// ======================================================================
//
// Copyright (c) 1997  The CGAL Consortium

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
// patch         : 1
// patch_date    : 2000, December 11
//
// source        : Sphere_3.fw
// file          : include/CGAL/Sphere_3.h
// package       : _3 (3.9)
// revision      : 3.9
// revision_date : 15 Oct 2000 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_SPHERE_3_H
#define CGAL_SPHERE_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/SphereH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/Cartesian/Sphere_3.h>
#endif // CGAL_CARTESIAN_H

#ifdef CGAL_SIMPLE_CARTESIAN_H
#include <CGAL/SimpleCartesian/SphereS3.h>
#endif // CGAL_SIMPLE_CARTESIAN_H


namespace CGAL {


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

} // namespace CGAL

#endif // CGAL_SPHERE_3_H
