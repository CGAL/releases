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
// file          : include/CGAL/Cartesian/Scaling_rep_3.h
// package       : Cartesian_kernel (6.24)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2000/11/14 09:31:48 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_SCALING_REP_3_H
#define CGAL_CARTESIAN_SCALING_REP_3_H

#include <CGAL/Cartesian/redefine_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class R >
class Scaling_repC3 : public Aff_transformation_rep_baseC3<R>
{
  friend class Aff_transformation_repC3<R>;
  friend class Translation_repC3<R>;

public:
  typedef typename R::FT                                FT;
  typedef typename R::RT                                RT;
  typedef Aff_transformation_rep_baseC3<R>              Transformation_base_3;
  typedef Aff_transformation_repC3<R>                   Transformation_3;
  typedef Translation_repC3<R>                          Translation_3;
  typedef Scaling_repC3<R>                              Scaling_3;
  typedef typename Transformation_base_3::Point_3       Point_3;
  typedef typename Transformation_base_3::Vector_3      Vector_3;
  typedef typename Transformation_base_3::Direction_3   Direction_3;
  typedef typename Transformation_base_3::Aff_transformation_3
	                                                Aff_transformation_3;

  Scaling_repC3() {}
  Scaling_repC3(const FT &s) : scalefactor_(s) {}
  virtual ~Scaling_repC3() {}

  virtual Point_3      transform(const Point_3 &p) const
  {
    return Point_3(scalefactor_ * p.x(),
                   scalefactor_ * p.y(),
                   scalefactor_ * p.z());
  }

  virtual Vector_3     transform(const Vector_3 &v) const
  {
    return Vector_3(scalefactor_ * v.x(), scalefactor_ * v.y(),
                    scalefactor_ * v.z());
  }

  virtual Direction_3  transform(const Direction_3 &d) const
  {
    return d;
  }

  virtual Aff_transformation_3 operator*(const Transformation_base_3 &t) const
  {
    return t.compose(*this);
  }

  virtual Aff_transformation_3 compose(const Transformation_3 &t) const
  {
    return Aff_transformation_3(scalefactor_ * t.t11,
                                scalefactor_ * t.t12,
                                scalefactor_ * t.t13,
                                t.t14,
				
                                scalefactor_ * t.t21,
                                scalefactor_ * t.t22,
                                scalefactor_ * t.t23,
                                t.t24,
				
                                scalefactor_ * t.t31,
                                scalefactor_ * t.t32,
                                scalefactor_ * t.t33,
                                t.t34);
  }

  virtual Aff_transformation_3 compose(const Translation_3 &t) const
  {
    FT ft0(0);
    return Aff_transformation_3(scalefactor_,
                                ft0,
                                ft0,
				t.translationvector_.x(),
				
                                ft0,
				scalefactor_,
                                ft0,
				t.translationvector_.y(),
				
                                ft0,
                                ft0,
				scalefactor_,
				t.translationvector_.z());
  }

  virtual Aff_transformation_3 compose(const Scaling_3 &t) const
  {
    return Aff_transformation_3(SCALING, scalefactor_*t.scalefactor_);
  }

  virtual Aff_transformation_3 inverse() const
  {
    return Aff_transformation_3(SCALING, FT(1)/scalefactor_);
  }

  virtual Aff_transformation_3 transpose() const
  {
    return Aff_transformation_3(SCALING, scalefactor_);
  }

  virtual bool is_even() const
  {
    return true;
  }

  virtual FT cartesian(int i, int j) const
  {
    if (i!=j) return FT(0);
    if (i==3) return FT(1);
    return scalefactor_;
  }

  virtual std::ostream &print(std::ostream &os) const
  {
    FT ft0(0);
    os << "Aff_transformationC3(" << scalefactor_ << ")";
    return os;
  }

private:
  FT   scalefactor_;
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_SCALING_REP_3_H
