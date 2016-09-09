// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Cartesian/Tetrahedron_d.h
// package       : Cd (1.14)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/06/20 21:55:03 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_TETRAHEDRON_D_H
#define CGAL_CARTESIAN_TETRAHEDRON_D_H

#include <CGAL/Cartesian/redefine_names_d.h>
#include <CGAL/Fourtuple.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class TetrahedronCd CGAL_ADVANCED_KERNEL_PARTIAL_SPEC
  : public Handle
{
public:
  typedef R_                               R;
  typedef typename R::FT                   FT;
  typedef typename R::RT                   RT;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef TetrahedronCd<R CGAL_CTAG>       Self;
  typedef typename R::Point_d              Point_d;
  typedef typename R::Plane_d              Plane_d;
  typedef typename R::Aff_transformation_d Aff_transformation_d;
#else
  typedef TetrahedronCd<R>                      Self;
  typedef typename R::Point_d_base              Point_d;
  typedef typename R::Plane_d_base              Plane_d;
  typedef typename R::Aff_transformation_d_base Aff_transformation_d;
#endif

  TetrahedronCd();
  TetrahedronCd(const Self &t);
  TetrahedronCd(const Point_d &p,
                const Point_d &q,
                const Point_d &r,
                const Point_d &s);
  ~TetrahedronCd();

  Self &operator=(const Self &t);

  Point_d    vertex(int i) const;
  Point_d    operator[](int i) const;

  bool       operator==(const Self &t) const;
  bool       operator!=(const Self &t) const;
  long       id() const;
  int        dimension() const;

  // Bbox_d     bbox() const;
  Self       transform(const Aff_transformation_d &t) const;

  // Only makes sense for 3D
  Orientation   orientation() const;

  Oriented_side oriented_side(const Point_d &p) const;
  Bounded_side  bounded_side(const Point_d &p) const;

  bool          has_on_positive_side(const Point_d &p) const;
  bool          has_on_negative_side(const Point_d &p) const;
  bool          has_on_bounded_side(const Point_d &p) const;
  bool          has_on_unbounded_side(const Point_d &p) const;
  bool          has_on_boundary(const Point_d &p) const;
  bool          has_on(const Point_d &p) const;

  // Makes sense for any dimension, but only implemented in 3D
  bool       is_degenerate() const;
  // End of 3D section

private:
  _Fourtuple< Point_d >*   ptr() const;
};

CGAL_END_NAMESPACE

#ifndef CGAL_CARTESIAN_CLASS_DEFINED
#include <CGAL/Cartesian/Tetrahedron_d.C>
#endif 

#endif
