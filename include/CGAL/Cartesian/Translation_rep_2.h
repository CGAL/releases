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
// file          : include/CGAL/Cartesian/Translation_rep_2.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/10/03 12:41:34 $
// author(s)     : Andreas Fabri, Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_TRANSLATION_REP_2_H
#define CGAL_CARTESIAN_TRANSLATION_REP_2_H

CGAL_BEGIN_NAMESPACE

template < class R >
class Translation_repC2 : public Aff_transformation_rep_baseC2<R>
{
friend class Aff_transformation_repC2<R>;
friend class Rotation_repC2<R>;
friend class Scaling_repC2<R>;

public:
  typedef typename R::FT                         FT;
  typedef Aff_transformation_rep_baseC2<R>       Aff_t_base;
  typedef Aff_transformation_repC2<R>            Transformation;
  typedef Translation_repC2<R>                   Translation;
  typedef Rotation_repC2<R>                      Rotation;
  typedef Scaling_repC2<R>                       Scaling;
  typedef typename Aff_t_base::Point_2           Point_2;
  typedef typename Aff_t_base::Vector_2          Vector_2;
  typedef typename Aff_t_base::Direction_2       Direction_2;
  typedef typename Aff_t_base::Aff_transformation_2 Aff_transformation_2;

  Translation_repC2()
  {}

  Translation_repC2(const Vector_2 &tv)
    : translationvector_(tv)
  {}

  Point_2     transform(const Point_2 &p) const
                            { return p + translationvector_; }
  Vector_2    transform(const Vector_2 &v) const { return v; }
  Direction_2 transform(const Direction_2 &d) const { return d; }

  Aff_transformation_2 operator*(const Aff_t_base &t) const
  {
    return t.compose(*this);
  }

  Aff_transformation_2 compose(const Translation &t) const
  {
    return Aff_transformation_2(TRANSLATION,
                                translationvector_ + t.translationvector_);
  }

  Aff_transformation_2 compose(const Rotation &t) const
  {
    return Aff_transformation_2(t.cosinus_,
                                -t.sinus_,
                                t.cosinus_*translationvector_.x() -
                                t.sinus_*translationvector_.y(),

                                t.sinus_,
                                t.cosinus_,
                                t.sinus_*translationvector_.x() +
                                t.cosinus_*translationvector_.y());
  }

  Aff_transformation_2 compose(const Scaling &t) const
  {
    return Aff_transformation_2(t.scalefactor_,
                                FT(0),
                                t.scalefactor_*translationvector_.x(),

                                FT(0),
                                t.scalefactor_,
                                t.scalefactor_*translationvector_.y());
  }

  Aff_transformation_2 compose(const Transformation &t) const
  {
    return Aff_transformation_2(t.t11,
                                t.t12,
                                t.t11 * translationvector_.x()
                                + t.t12 * translationvector_.y()
                                + t.t13,

                                t.t21,
                                t.t22,
                                t.t21 * translationvector_.x()
                                + t.t22*translationvector_.y()
                                + t.t23);
  }

  Aff_transformation_2 inverse() const
  {
    return Aff_transformation_2(TRANSLATION, - translationvector_);
  }

  bool         is_even() const
  {
    return true;
  }

  FT cartesian(int i, int j) const
  {
    if (j==i) return FT(1);
    if (j==2) return translationvector_[i];
    return FT(0);
  }

  std::ostream &print(std::ostream &os) const
  {
    os << "Aff_transformationC2(VectorC2(" << translationvector_.x() << ", "
       << translationvector_.y()  <<  "))";
    return os;
  }

private:
  Vector_2   translationvector_;
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_TRANSLATION_REP_2_H
