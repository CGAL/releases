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
// file          : include/CGAL/Cartesian/Scaling_rep_2.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/10/03 12:41:32 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_SCALING_REP_2_H
#define CGAL_CARTESIAN_SCALING_REP_2_H

CGAL_BEGIN_NAMESPACE

template < class R >
class Scaling_repC2: public Aff_transformation_rep_baseC2<R>
{
friend class Aff_transformation_repC2<R>;
friend class Translation_repC2<R>;
friend class Rotation_repC2<R>;

public:
  typedef Aff_transformation_rep_baseC2<R> Aff_t_base;
  typedef typename Aff_t_base::FT                FT;
  typedef typename Aff_t_base::Point_2           Point_2;
  typedef typename Aff_t_base::Vector_2          Vector_2;
  typedef typename Aff_t_base::Direction_2       Direction_2;
  typedef typename Aff_t_base::Aff_transformation_2   Aff_transformation_2;
  typedef Aff_transformation_repC2<R>      Transformation;
  typedef Translation_repC2<R>             Translation;
  typedef Rotation_repC2<R>                Rotation;
  typedef Scaling_repC2<R>                 Scaling;

  Scaling_repC2()
  {}

  Scaling_repC2(const FT &scalefactor) :
    scalefactor_(scalefactor)
  {}

  ~Scaling_repC2()
  {}

  Point_2      transform(const Point_2 &p) const
  {
    return Point_2(scalefactor_ * p.x(), scalefactor_ * p.y());
  }

  Vector_2      transform(const Vector_2 &p) const
  {
    return Vector_2(scalefactor_ * p.x(), scalefactor_ * p.y());
  }

  Direction_2  transform(const Direction_2 &d) const
  {
    return d;
  }

  Aff_transformation_2 operator*(const Aff_t_base &t) const
  {
   return t.compose(*this);
  }

  Aff_transformation_2 compose(const Translation &t) const
  {
    FT ft0(0);
    return Aff_transformation_2(scalefactor_,
                                ft0,
                                t.translationvector_.x(),
                                ft0,
                                scalefactor_,
                                t.translationvector_.y());
  }

  Aff_transformation_2 compose(const Rotation &t) const
  {
    return Aff_transformation_2(scalefactor_ * t.cosinus_,
                                scalefactor_ * -t.sinus_,
                                scalefactor_ * t.sinus_,
                                scalefactor_ * t.cosinus_);
  }

  Aff_transformation_2 compose(const Scaling &t) const
  {
    return Aff_transformation_2(SCALING, scalefactor_*t.scalefactor_);
  }

  Aff_transformation_2 compose(const Transformation &t) const
  {
    return Aff_transformation_2(scalefactor_ * t.t11,
                                scalefactor_ * t.t12,
                                t.t13,
                                scalefactor_ * t.t21,
                                scalefactor_ * t.t22,
                                t.t23);
  }

  Aff_transformation_2  inverse() const
  {
    return Aff_transformation_2(SCALING, FT(1)/scalefactor_);
  }

  bool is_even() const
  {
    return true;
  }

  FT cartesian(int i, int j) const
  {
    if (i!=j) return FT(0);
    return (i==2) ? FT(1) : scalefactor_;
  }

  std::ostream &print(std::ostream &os) const
  {
    os << "Aff_transformationC2(" << scalefactor_ <<  ")";
    return os;
  }

private:
  FT scalefactor_;
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_SCALING_REP_2_H
