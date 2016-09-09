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
// file          : include/CGAL/Cartesian/Translation_rep_3.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/10/03 12:41:35 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_TRANSLATION_REP_3_H
#define CGAL_CARTESIAN_TRANSLATION_REP_3_H

CGAL_BEGIN_NAMESPACE

template < class R >
class Translation_repC3 : public Aff_transformation_rep_baseC3<R>
{
  friend class Aff_transformation_repC3<R>;
  friend class Scaling_repC3<R>;

public:
  typedef typename R::FT                                FT;
  typedef Aff_transformation_rep_baseC3<R>              Transformation_base_3;
  typedef Aff_transformation_repC3<R>                   Transformation_3;
  typedef Translation_repC3<R>                          Translation_3;
  typedef Scaling_repC3<R>                              Scaling_3;
  typedef typename Transformation_base_3::Point_3       Point_3;
  typedef typename Transformation_base_3::Vector_3      Vector_3;
  typedef typename Transformation_base_3::Direction_3   Direction_3;
  typedef typename Transformation_base_3::Aff_transformation_3
	                                                Aff_transformation_3;

  Translation_repC3() {}
  Translation_repC3(const Vector_3 &tv) : translationvector_(tv) {}
  virtual ~Translation_repC3() {}

  virtual Point_3     transform(const Point_3 &p) const
  {
    return p + translationvector_;
  }

  virtual Vector_3    transform(const Vector_3 &v) const
  {
    return v;
  }

  virtual Direction_3 transform(const Direction_3 &d) const
  {
    return d;
  }

  virtual Aff_transformation_3 operator*(const Transformation_base_3 &t) const
  {
    return t.compose(*this);
  }

  virtual Aff_transformation_3 compose(const Transformation_3 &t) const
  {
    return Aff_transformation_3(t.t11,
                                t.t12,
				t.t13,
				t.t11 * translationvector_.x()
				+ t.t12 * translationvector_.y()
				+ t.t13 * translationvector_.z() + t.t14,
				
				t.t21,
                                t.t22,
				t.t23,
				t.t21 * translationvector_.x()
				+ t.t22 * translationvector_.y()
				+ t.t23 * translationvector_.z() + t.t24,
				
				t.t31,
                                t.t32,
				t.t33,
				t.t31 * translationvector_.x()
				+ t.t32 * translationvector_.y()
				+ t.t33 * translationvector_.z() + t.t34);
  }

  virtual Aff_transformation_3 compose(const Translation_3 &t) const
  {
    return Aff_transformation_3(TRANSLATION,
                                translationvector_ + t.translationvector_);
  }

  virtual Aff_transformation_3 compose(const Scaling_3 &t) const
  {
    FT ft0(0);
    return Aff_transformation_3(t.scalefactor_,
                                ft0,
				ft0,
				t.scalefactor_ * translationvector_.x(),
				
				ft0,
                                t.scalefactor_,
				ft0,
				t.scalefactor_ * translationvector_.y(),
				
				ft0,
                                ft0,
				t.scalefactor_,
				t.scalefactor_ * translationvector_.z());
  }

  virtual Aff_transformation_3 inverse() const
  {
    return Aff_transformation_3(TRANSLATION, - translationvector_);
  }

  virtual Aff_transformation_3 transpose() const
  {
    FT ft1(1), ft0(0);
    return Aff_transformation_3(TRANSLATION, translationvector_);
  }
  
  virtual bool is_even() const
  {
    return true;
  }

  virtual FT cartesian(int i, int j) const
  {
    if (j==i) return FT(1);
    if (j==3) return translationvector_[i];
    return FT(0);
  }

  virtual std::ostream &print(std::ostream &os) const
  {
    FT ft0(0), ft1(1);
    os << "Aff_transformationC3(VectorC3("<< translationvector_.x() << ","
       << translationvector_.y() << ","
       << translationvector_.z() << "))\n";
    return os;
  }

private:
  Vector_3   translationvector_;
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_TRANSLATION_REP_3_H
