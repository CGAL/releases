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
// file          : include/CGAL/Cartesian/Aff_transformation_3.h
// package       : C3 (4.0.3)
// revision      : $Revision: 1.13 $
// revision_date : $Date: 1999/11/05 22:29:31 $
// author(s)     : Andreas Fabri
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_AFF_TRANSFORMATION_3_H
#define CGAL_CARTESIAN_AFF_TRANSFORMATION_3_H

#include <CGAL/Cartesian/redefine_names_3.h>
#include <cmath>

CGAL_BEGIN_NAMESPACE

class Identity_transformation;
template <class R> class Aff_transformation_rep_baseC3;
template <class R> class Aff_transformation_repC3;
template <class R> class Translation_repC3;
template <class R> class Scaling_repC3;

CGAL_END_NAMESPACE

#include <CGAL/Cartesian/Aff_transformation_rep_3.h>
#include <CGAL/Cartesian/Translation_rep_3.h>
#include <CGAL/Cartesian/Scaling_rep_3.h>

CGAL_BEGIN_NAMESPACE

template < class _R >
class Aff_transformationC3
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
// This is a partial specialization
<_R,Cartesian_tag>
#endif
  : public Handle
{
  friend class PlaneC3<_R CGAL_CTAG>;

public:
  typedef _R                               R;
  typedef typename R::FT                   FT;
  typedef typename R::FT                   RT;
  typedef Aff_transformation_rep_baseC3<R> Aff_t_base;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef Aff_transformationC3<R,Cartesian_tag> Self;
  typedef typename R::Point_3              Point_3;
  typedef typename R::Vector_3             Vector_3;
  typedef typename R::Direction_3          Direction_3;
  typedef typename R::Plane_3              Plane_3;
#else
  typedef Aff_transformationC3<R>          Self;
  typedef typename R::Point_3_base         Point_3;
  typedef typename R::Vector_3_base        Vector_3;
  typedef typename R::Direction_3_base     Direction_3;
  typedef typename R::Plane_3_base         Plane_3;
#endif

  Aff_transformationC3();
  // Aff_transformationC3(const Self &t); // Provided by default

  // Identity constructor:
  Aff_transformationC3(const Identity_transformation &);

  // Translation:
  Aff_transformationC3(const Translation,
                       const Vector_3 &v);

  // Scaling:
  Aff_transformationC3(const Scaling,
                       const FT &s,
                       const FT &w = FT(1));

  // General form: without translation
  Aff_transformationC3(const FT& m11, const FT& m12, const FT& m13,
                       const FT& m21, const FT& m22, const FT& m23,
                       const FT& m31, const FT& m32, const FT& m33,
                       const FT& w= FT(1));

  // General form: with translation
  Aff_transformationC3(const FT& m11, const FT& m12, const FT& m13,
                                                           const FT& m14,
                       const FT& m21, const FT& m22, const FT& m23,
                                                           const FT& m24,
                       const FT& m31, const FT& m32, const FT& m33,
                                                           const FT& m34,
                       const FT& w = FT(1));

  ~Aff_transformationC3();

  Point_3     transform(const Point_3 &p) const { return ptr()->transform(p); }
  Point_3     operator()(const Point_3 &p) const { return transform(p); }

  Vector_3    transform(const Vector_3 &v) const
                                           { return ptr()->transform(v); }
  Vector_3    operator()(const Vector_3 &v) const { return transform(v); }

  Direction_3 transform(const Direction_3 &d) const
                                              { return ptr()->transform(d); }
  Direction_3 operator()(const Direction_3 &d) const { return transform(d); }

  Plane_3     transform(const Plane_3& p) const { return p.transform(*this); }
  Plane_3     operator()(const Plane_3& p) const { return transform(l); }

  Self        inverse() const { return ptr()->inverse(); }
  
  bool        is_even() const { return ptr()->is_even(); }
  bool        is_odd() const { return  ! (ptr()->is_even()); }
  
  FT          cartesian(int i, int j) const { return ptr()->cartesian(i,j); }
  FT          homogeneous(int i, int j) const { return cartesian(i,j); }
  FT          m(int i, int j) const { return cartesian(i,j); }
  FT          hm(int i, int j) const { return cartesian(i,j); }

  Self operator*(const Self &t) const { return (*ptr()) * (*t.ptr()); }

protected:
  Self        transpose() const { return ptr()->transpose(); }

private:
  Aff_t_base*       ptr() const { return  (Aff_t_base*)PTR; }
};

CGAL_END_NAMESPACE

#ifndef CGAL_CARTESIAN_CLASS_DEFINED
#include <CGAL/Cartesian/Aff_transformation_3.C>
#endif 

#endif // CGAL_CARTESIAN_AFF_TRANSFORMATION_3_H
