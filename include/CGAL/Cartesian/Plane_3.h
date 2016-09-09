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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Cartesian/Plane_3.h
// package       : C3 (4.0.3)
// revision      : $Revision: 1.9 $
// revision_date : $Date: 1999/11/05 22:29:36 $
// author(s)     : Andreas Fabri
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_PLANE_3_H
#define CGAL_CARTESIAN_PLANE_3_H

#include <CGAL/Cartesian/redefine_names_3.h>
#include <CGAL/Fourtuple.h>

CGAL_BEGIN_NAMESPACE

template <class _R>
class PlaneC3
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
// This is a partial specialization
<_R,Cartesian_tag>
#endif
  : public Handle
{
public:
  typedef _R                                    R;
  typedef typename R::FT                        FT;
  typedef typename R::RT                        RT;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef PlaneC3<R,Cartesian_tag>              Self;
  typedef typename R::Point_2                   Point_2;
  typedef typename R::Point_3                   Point_3;
  typedef typename R::Vector_3                  Vector_3;
  typedef typename R::Direction_3               Direction_3;
  typedef typename R::Line_3                    Line_3;
  typedef typename R::Ray_3                     Ray_3;
  typedef typename R::Segment_3                 Segment_3;
  typedef typename R::Aff_transformation_3      Aff_transformation_3;
#else
  typedef PlaneC3<R>                            Self;
  typedef typename R::Point_2_base              Point_2;
  typedef typename R::Point_3_base              Point_3;
  typedef typename R::Vector_3_base             Vector_3;
  typedef typename R::Direction_3_base          Direction_3;
  typedef typename R::Line_3_base               Line_3;
  typedef typename R::Ray_3_base                Ray_3;
  typedef typename R::Segment_3_base            Segment_3;
  typedef typename R::Aff_transformation_3_base Aff_transformation_3;
#endif

  PlaneC3();
  PlaneC3(const Self &p);
  PlaneC3(const Point_3 &p, const Point_3 &q, const Point_3 &r);
  PlaneC3(const Point_3 &p, const Direction_3 &d);
  PlaneC3(const Point_3 &p, const Vector_3 &v);
  PlaneC3(const FT &a, const FT &b, const FT &c, const FT &d);
  PlaneC3(const Line_3 &l, const Point_3 &p);
  PlaneC3(const Segment_3 &s, const Point_3 &p);
  PlaneC3(const Ray_3 &r, const Point_3 &p);
  ~PlaneC3();

  Self       &operator=(const Self &p);

  bool         operator==(const Self &p) const;
  bool         operator!=(const Self &p) const;
  long         id() const;

  FT           a() const;
  FT           b() const;
  FT           c() const;
  FT           d() const;

  Line_3       perpendicular_line(const Point_3 &p) const;
  Self             opposite() const;

  Point_3      point() const;
  Point_3      projection(const Point_3 &p) const;
  Vector_3     orthogonal_vector() const;
  Direction_3  orthogonal_direction() const;
  Vector_3     base1() const;
  Vector_3     base2() const;

  Point_3      to_plane_basis(const Point_3 &p) const;

  Point_2      to_2d(const Point_3 &p) const;
  Point_3      to_3d(const Point_2 &p) const;

  Self        transform(const Aff_transformation_3 &t) const;


  Oriented_side oriented_side(const Point_3 &p) const;
  bool         has_on_boundary(const Point_3 &p) const;
  bool         has_on_boundary(const Line_3 &p) const;
  bool         has_on_positive_side(const Point_3 &l) const;
  bool         has_on_negative_side(const Point_3 &l) const;
  bool         has_on(const Point_3 &p) const;

  bool         is_degenerate() const;

private:
  _Fourtuple<FT>*   ptr() const;
  void              new_rep(const Point_3 &p,
                            const Point_3 &q,
                            const Point_3 &r);
  void              new_rep(const FT &a, const FT &b,
                            const FT &c, const FT &d);
};

CGAL_END_NAMESPACE

#ifndef CGAL_CARTESIAN_CLASS_DEFINED
#include <CGAL/Cartesian/Plane_3.C>
#endif 

#endif // CGAL_CARTESIAN_PLANE_3_H
