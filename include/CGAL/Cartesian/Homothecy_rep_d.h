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
// file          : include/CGAL/Cartesian/Homothecy_rep_d.h
// package       : Cd (1.14)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/20 21:54:59 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_HOMOTHECY_REP_D_H
#define CGAL_CARTESIAN_HOMOTHECY_REP_D_H

#include <CGAL/Cartesian/redefine_names_d.h>

#ifdef _MSC_VER
#define typename
#endif

CGAL_BEGIN_NAMESPACE

template < class R >
class Homothecy_repC3 : public Aff_transformation_rep_baseC3<R>
{
  friend class Aff_transformation_repCd<R>;
  friend class Translation_repCd<R>;
  friend class Scaling_repCd<R>;

public:
  typedef typename R::FT                                FT;
  typedef typename R::RT                                RT;
  typedef Aff_transformation_rep_baseC3<R>              Transformation_base_d;
  typedef Aff_transformation_repC3<R>                   Transformation_d;
  typedef Translation_repC3<R>                          Translation_d;
  typedef Homothecy_repC3<R>                            Homothecy_d;
  typedef typename Transformation_base_d::Point_d       Point_d;
  typedef typename Transformation_base_d::Vector_d      Vector_d;
  typedef typename Transformation_base_d::Direction_d   Direction_d;
  typedef typename Transformation_base_d::Aff_transformation_d
	                                                Aff_transformation_d;

  Homothecy_repC3() {}
  Homothecy_repC3(const FT &s) : _scalefactor(s) {}
  virtual ~Homothecy_repC3() {}

  virtual Point_d      transform(const Point_d &p) const
  {
    return Point_d(_scalefactor * p.x(),
                   _scalefactor * p.y(),
                   _scalefactor * p.z());
  }

  virtual Vector_d     transform(const Vector_d &v) const
  {
    return Vector_d(_scalefactor * v.x(), _scalefactor * v.y(),
                    _scalefactor * v.z());
  }

  virtual Direction_d  transform(const Direction_d &d) const
  {
    return d;
  }

  virtual Aff_transformation_d operator*(const Transformation_base_d &t) const
  {
    return t.compose(*this);
  }

  virtual Aff_transformation_d compose(const Transformation_d &t) const
  {
    return Aff_transformation_d(_scalefactor * t.t11,
                                _scalefactor * t.t12,
                                _scalefactor * t.t13,
                                t.t14,
				
                                _scalefactor * t.t21,
                                _scalefactor * t.t22,
                                _scalefactor * t.t23,
                                t.t24,
				
                                _scalefactor * t.t31,
                                _scalefactor * t.t32,
                                _scalefactor * t.t33,
                                t.t34);
  }

  virtual Aff_transformation_d compose(const Translation_d &t) const
  {
    FT ft0(0);
    return Aff_transformation_d(_scalefactor,
                                ft0,
                                ft0,
				t._translationvector.x(),
				
                                ft0,
				_scalefactor,
                                ft0,
				t._translationvector.y(),
				
                                ft0,
                                ft0,
				_scalefactor,
				t._translationvector.z());
  }

  virtual Aff_transformation_d compose(const Homothecy_d &t) const
  {
    return Aff_transformation_d(HOMOTHECY, _scalefactor*t._scalefactor);
  }

  virtual Aff_transformation_d inverse() const
  {
    return Aff_transformation_d(HOMOTHECY, FT(1)/_scalefactor);
  }

  virtual Aff_transformation_d transpose() const
  {
    return Aff_transformation_d(HOMOTHECY, _scalefactor);
  }

  virtual bool            is_even() const
  {
    return true;
  }

  virtual FT cartesian(int i, int j) const
  {
    if (i!=j) return FT(0);
    if (i==3) return FT(1);
    return _scalefactor;
  }

  virtual std::ostream &print(std::ostream &os) const
  {
    FT ft0(0);
    os << "Aff_transformationC3(" << _scalefactor << ")";
    return os;
  }

private:
  FT   _scalefactor;
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_HOMOTHECY_REP_D_H
