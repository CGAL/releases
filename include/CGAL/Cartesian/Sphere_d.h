// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Cartesian/Sphere_d.h
// package       : Cd (1.5)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2000/06/27 14:32:29 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_CARTESIAN_SPHERE_D_H
#define CGAL_CARTESIAN_SPHERE_D_H

#ifndef CGAL_CARTESIAN_REDEFINE_NAMES_D_H
#include <CGAL/Cartesian/redefine_names_d.h>
#endif
#ifndef CGAL_CARTESIAN_SPHERE_REP_D_H
#include <CGAL/Cartesian/Sphere_rep_d.h>
#endif // CGAL_CARTESIAN_SPHERE_REP_D_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class SphereC3
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
// This is a partial specialization
<R_,Cartesian_tag>
#endif
{
public:
  typedef R_                                    R;
  typedef typename R::FT                        FT;
  typedef typename R::RT                        RT;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef SphereC3<R CGAL_CTAG>                 Self;
  typedef typename R::Point_d                   Point_d;
  typedef typename R::Aff_transformation_d      Aff_transformation_d;
#else
  typedef SphereC3<R>                           Self;
  typedef typename R::Point_D_base              Point_d;
  // typedef typename R::Aff_transformation_D_base Aff_transformation_d;
#endif

  Sphere_d(const Point_d &p, const FT &s,
           const Orientation &o = COUNTERCLOCKWISE);
  // Sphere with center p, squared radius s, orientation o
  Sphere_d(const R::Point_d &p, const R::Point_d &q,
           const R::Point_d &r, const R::Point_d &u);
  // Sphere passing through p,q,r,u, oriented by p, q, r, u
  Sphere_d(const R::Point_d &p, const R::Point_d &q, const R::Point_d &r,
	   const Orientation &o = COUNTERCLOCKWISE);
  // Sphere with great circle passing through p,q,r, oriented by o
  Sphere_d(const Point_d & p, const Point_d & q,
           const Orientation &o = COUNTERCLOCKWISE);
  // Sphere with diameter pq and orientation o
  Sphere_d(const Point_d & p,
           const Orientation& o = COUNTERCLOCKWISE);
  // Sphere centered at p, radius 0, orientation o

  Point  center() const;
  // Returns the center of c
  FT     squared_radius() const;
  // Returns the square of the radius (instead of the radius itself,
  // which would require square roots)
  Orientation orientation() const;
  // Returns the orientation of c

  Self   orthogonal_transform(const Aff_transformation_d &t) const;
  //! precond: t.is_orthogonal() (*UNDEFINED*)
  // Returns the image of c by t. Since t is orthogonal, the image is
  // always a circle

  bool   is_degenerate() const;
  // A circle is degenerate if its (squared) radius is null or negative
  Self   opposite() const;
  // Returns a circle with opposite orientation

  Oriented_side  oriented_side(const Point_d &p) const;
  //! precond: ! x.is_degenerate() (when available)
  // Returns R::ON_POSITIVE_SIDE, R::ON_ORIENTED_BOUNDARY or
  // R::ON_NEGATIVE_SIDE
  bool   has_on_boundary(const Point_d &p) const
  { return oriented_side(p)==ON_ORIENTED_BOUNDARY; }
  bool   has_on_positive_side(const Point_d &p) const;
  { return oriented_side(p)==ON_POSITIVE_SIDE; }
  bool   has_on_negative_side(const Point_d &p) const;
  { return oriented_side(p)==ON_NEGATIVE_SIDE; }

  Bounded_side   bounded_side(const Point_d &p) const;
  //! precond: ! x.is_degenerate() (when available)
  // Returns R::ON_BOUNDED_SIDE, R::ON_BOUNDARY or R::ON_UNBOUNDED_SIDE
  bool   has_on_bounded_side(const Point_d &p) const;
  { return bounded_side(p)==ON_BOUNDED_SIDE; }
  bool   has_on_unbounded_side(const Point_d &p) const;
  { return bounded_side(p)==ON_UNBOUNDED_SIDE; }

protected:
  Sphere_repC3<R> *ptr();
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_SPHERE_D_H
