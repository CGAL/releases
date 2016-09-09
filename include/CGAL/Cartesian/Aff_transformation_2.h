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
// file          : include/CGAL/Cartesian/Aff_transformation_2.h
// package       : C2 (3.3.11)
// revision      : $Revision: 1.12 $
// revision_date : $Date: 1999/11/05 22:29:37 $
// author(s)     : Andreas Fabri, Lutz Kettner
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_AFF_TRANSFORMATION_2_H
#define CGAL_CARTESIAN_AFF_TRANSFORMATION_2_H

#include <cmath>
#include <CGAL/Cartesian/redefine_names_2.h>
#include <CGAL/Handle.h>

CGAL_BEGIN_NAMESPACE

class Identity_transformation;
template < class R > class Aff_transformation_rep_baseC2;
template < class R > class Aff_transformation_repC2;
template < class R > class Translation_repC2;
template < class R > class Rotation_repC2;
template < class R > class Scaling_repC2;

CGAL_END_NAMESPACE

#include <CGAL/Cartesian/Aff_transformation_rep_2.h>
#include <CGAL/Cartesian/Translation_rep_2.h>
#include <CGAL/Cartesian/Rotation_rep_2.h>
#include <CGAL/Cartesian/Scaling_rep_2.h>

CGAL_BEGIN_NAMESPACE

template < class _R >
class Aff_transformationC2
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
// This is a partial specialization
<_R,Cartesian_tag>
#endif
  : public Handle
{
public:
  typedef _R                               R;
  typedef typename R::FT                   FT;
  typedef typename R::RT                   RT;
  typedef Aff_transformation_rep_baseC2<R> Aff_t_base;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef Aff_transformationC2<R,Cartesian_tag> Self;
  typedef typename R::Point_2              Point_2;
  typedef typename R::Vector_2             Vector_2;
  typedef typename R::Direction_2          Direction_2;
  typedef typename R::Line_2               Line_2;
#else
  typedef Aff_transformationC2<R>          Self;
  typedef typename R::Point_2_base         Point_2;
  typedef typename R::Vector_2_base        Vector_2;
  typedef typename R::Direction_2_base     Direction_2;
  typedef typename R::Line_2_base          Line_2;
#endif // CGAL_CFG_NO_ADVANCED_KERNEL
   
  Aff_transformationC2();
  Aff_transformationC2(const Self &t);

  // Identity
  Aff_transformationC2(const Identity_transformation);

  // Translation:
  Aff_transformationC2(const Translation,
                       const Vector_2 &v);

  // Rational Rotation:
  Aff_transformationC2(const Rotation,
                       const Direction_2 &d,
                       const FT &num,
                       const FT &den = FT(1));

  Aff_transformationC2(const Rotation,
                       const FT &sine_rho,
                       const FT &cosine_rho,
                       const FT &hw = FT(1));

  // Scaling:
  Aff_transformationC2(const Scaling,
                       const FT &s,
                       const FT &w = FT(1));

  // The general case:
  Aff_transformationC2(const FT & m11,
                       const FT & m12,
                       const FT & m13,
                       const FT & m21,
                       const FT & m22,
                       const FT & m23,
                       const FT &w = FT(1));

  Aff_transformationC2(const FT & m11, const FT & m12,
                       const FT & m21, const FT & m22,
                       const FT &w = FT(1));

  ~Aff_transformationC2();

  Self &operator=(const Self &t);

  Point_2     transform(const Point_2 &p) const { return ptr()->transform(p); } 
  Point_2     operator()(const Point_2 &p) const { return transform(p); }

  Vector_2    transform(const Vector_2 &v) const { return ptr()->transform(v); }
  Vector_2    operator()(const Vector_2 &v) const { return transform(p); }

  Direction_2 transform(const Direction_2 &d) const
                                              { return ptr()->transform(d); }
  Direction_2 operator()(const Direction_2 &d) const { return transform(d); }

  Line_2      transform(const Line_2 &l) const { return l.transform(*this); }
  Line_2      operator()(const Line_2 &l) const {return transform(l); }

  Self        inverse() const { return ptr()->inverse(); }

  bool        is_even() const { return ptr()->is_even(); }
  bool        is_odd() const { return ! (ptr()->is_even()); }

  FT          cartesian(int i, int j) const { return ptr()->cartesian(i,j); }
  FT          homogeneous(int i, int j) const { return cartesian(i,j); }
  FT          m(int i, int j) const { return cartesian(i,j); }
  FT          hm(int i, int j) const { return cartesian(i,j); }

  Self operator*(const Self &t) const
  {
    return (*ptr()) * (*t.ptr());
  }

  std::ostream &print(std::ostream &os) const;

private:
  Aff_t_base* ptr() const { return  (Aff_t_base*)PTR; }
};

CGAL_END_NAMESPACE

#ifndef CGAL_CARTESIAN_CLASS_DEFINED
#include <CGAL/Cartesian/Aff_transformation_2.C>
#endif

#endif // CGAL_CARTESIAN_AFF_TRANSFORMATION_2_H
