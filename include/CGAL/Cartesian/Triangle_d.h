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
// file          : include/CGAL/Cartesian/Triangle_d.h
// package       : Cd (1.5)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2000/06/27 14:32:31 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_TRIANGLE_D_H
#define CGAL_CARTESIAN_TRIANGLE_D_H

#include <CGAL/Cartesian/redefine_names_d.h>
#include <CGAL/Threetuple.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class TriangleCd
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
// This is a partial specialization
<R_,Cartesian_tag>
#endif
  : public Handle
{
public:
  typedef R_                               R;
  typedef typename R::FT                   FT;
  typedef typename R::RT                   RT;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef TriangleCd<R CGAL_CTAG>          Self;
  typedef typename R::Point_d              Point_d;
  typedef typename R::Vector_d             Vector_d;
  typedef typename R::Plane_d              Plane_d;
  typedef typename R::Aff_transformation_d Aff_transformation_d;
#else
  typedef TriangleCd<R>                         Self;
  typedef typename R::Point_d_base              Point_d;
  typedef typename R::Vector_d_base             Vector_d;
  typedef typename R::Plane_d_base              Plane_d;
  typedef typename R::Aff_transformation_d_base Aff_transformation_d;
#endif

  TriangleCd();
  TriangleCd(const Self &t);
  TriangleCd(const Point_d &p, const Point_d &q, const Point_d &r);
  ~TriangleCd();

  Self       &operator=(const Self &t);

  Point_d    vertex(int i) const;
  Point_d    operator[](int i) const;

  bool       operator==(const Self &t) const;
  bool       operator!=(const Self &t) const;
  long       id() const;
  int        dimension() const;

  // Bbox_d     bbox() const;

  Self       transform(const Aff_transformation_d &t) const;

  // Only makes sense for 3D
  Plane_d    supporting_plane() const;
  // Makes sense for any dimension, but only implemented in 3D
  bool       has_on(const Point_d &p) const;
  // End of 3D section

  bool       is_degenerate() const;

private:
  _Threetuple< Point_d >*   ptr() const;
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_TRIANGLE_D_H
