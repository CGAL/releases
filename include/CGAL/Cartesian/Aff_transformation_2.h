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
// file          : include/CGAL/Cartesian/Aff_transformation_2.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.16 $
// revision_date : $Date: 2002/02/06 12:32:34 $
// author(s)     : Andreas Fabri, Lutz Kettner
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_AFF_TRANSFORMATION_2_H
#define CGAL_CARTESIAN_AFF_TRANSFORMATION_2_H

#include <cmath>

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

template < class R_ >
class Aff_transformationC2
  : public R_::Aff_transformation_handle_2
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::FT                   FT;
  typedef Aff_transformation_rep_baseC2<R_> Aff_t_base;

  typedef typename R_::Point_2              Point_2;
  typedef typename R_::Vector_2             Vector_2;
  typedef typename R_::Direction_2          Direction_2;
  typedef typename R_::Line_2               Line_2;
  typedef typename R_::Aff_transformation_2 Aff_transformation_2;

public:
  typedef R_                                R;
   
  Aff_transformationC2()
  {
    initialize_with(Aff_transformation_repC2<R>(FT(1), FT(0), FT(0), FT(1)));
  }

  Aff_transformationC2(const Identity_transformation)
  {
    initialize_with(Aff_transformation_repC2<R>(FT(1), FT(0), FT(0), FT(1)));
  }

  Aff_transformationC2(const Translation, const Vector_2 &v)
  {
    initialize_with(Translation_repC2<R>(v));
  }

  // Rational Rotation:
  Aff_transformationC2(const Rotation,
                       const Direction_2 &d,
                       const FT &num,
                       const FT &den = FT(1))
  {
    initialize_with(Rotation_repC2<R>(d, num, den));
  }

  Aff_transformationC2(const Rotation,
                       const FT &sine,
                       const FT &cosine,
                       const FT &w = FT(1))
  {
    if (w != FT(1))
      initialize_with(Rotation_repC2<R>(sine/w, cosine/w));
    else
      initialize_with(Rotation_repC2<R>(sine, cosine));
  }

  Aff_transformationC2(const Scaling, const FT &s, const FT &w = FT(1))
  {
    if (w != FT(1))
      initialize_with(Scaling_repC2<R>(s/w));
    else
      initialize_with(Scaling_repC2<R>(s));
  }

  // The general case:
  // a 3x2 matrix for the operations combining rotation, scaling, translation
  Aff_transformationC2(const FT & m11, const FT & m12, const FT & m13,
                       const FT & m21, const FT & m22, const FT & m23,
                       const FT &w = FT(1))
  {
    if (w != FT(1))
      initialize_with(Aff_transformation_repC2<R>(m11/w, m12/w, m13/w,
                                                  m21/w, m22/w, m23/w));
    else
      initialize_with(Aff_transformation_repC2<R>(m11, m12, m13,
                                                  m21, m22, m23));
  }

  Aff_transformationC2(const FT & m11, const FT & m12,
                       const FT & m21, const FT & m22,
                       const FT &w = FT(1))
  {
    initialize_with(Aff_transformation_repC2<R>(m11/w, m12/w, m21/w, m22/w));
  }

  Point_2
  transform(const Point_2 &p) const 
  { return Ptr()->transform(p); } 

  Point_2
  operator()(const Point_2 &p) const
  { return transform(p); }

  Vector_2
  transform(const Vector_2 &v) const 
  { return Ptr()->transform(v); }

  Vector_2
  operator()(const Vector_2 &v) const
  { return transform(v); } // FIXME : not compiled by the test-suite.

  Direction_2
  transform(const Direction_2 &d) const
  { return Ptr()->transform(d); }

  Direction_2
  operator()(const Direction_2 &d) const
  { return transform(d); }

  Line_2
  transform(const Line_2 &l) const
  { return l.transform(*this); }

  Line_2
  operator()(const Line_2 &l) const
  { return transform(l); }

  Aff_transformation_2 inverse() const { return Ptr()->inverse(); }

  bool is_even() const { return Ptr()->is_even(); }
  bool is_odd() const { return ! (Ptr()->is_even()); }

  FT cartesian(int i, int j) const { return Ptr()->cartesian(i,j); }
  FT homogeneous(int i, int j) const { return cartesian(i,j); }
  FT m(int i, int j) const { return cartesian(i,j); }
  FT hm(int i, int j) const { return cartesian(i,j); }

  Aff_transformation_2 operator*(const Aff_transformationC2 &t) const
  {
    return (*Ptr()) * (*t.Ptr());
  }

  std::ostream &
  print(std::ostream &os) const;
};

template < class R >
std::ostream&
Aff_transformationC2<R>::print(std::ostream &os) const
{
  Ptr()->print(os);
  return os;
}

#ifndef CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATIONC2
template < class R >
std::ostream&
operator<<(std::ostream& os, const Aff_transformationC2<R>& t)
{
  t.print(os);
  return os;
}
#endif // CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATIONC2

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_AFF_TRANSFORMATION_2_H
