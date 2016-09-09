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
// file          : include/CGAL/Cartesian/Scaling_rep_d.h
// package       : Cd (1.14)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/20 21:55:01 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_SCALING_REP_D_H
#define CGAL_CARTESIAN_SCALING_REP_D_H

#include <CGAL/Cartesian/redefine_names_d.h>

#ifdef _MSC_VER
#define typename
#endif

CGAL_BEGIN_NAMESPACE

template < class R >
class Scaling_repCd : public Aff_transformation_rep_baseCd<R>
{
  friend class Aff_transformation_repCd<R>;
  friend class Translation_repCd<R>;

public:
  typedef typename R::FT                                FT;
  typedef typename R::RT                                RT;
  typedef Aff_transformation_rep_baseCd<R>              Transformation_base_d;
  typedef Aff_transformation_repCd<R>                   Transformation_d;
  typedef Translation_repCd<R>                          Translation_d;
  typedef Scaling_repCd<R>                              Scaling_d;
  typedef typename Transformation_base_d::Point_d       Point_d;
  typedef typename Transformation_base_d::Vector_d      Vector_d;
  typedef typename Transformation_base_d::Direction_d   Direction_d;
  typedef typename Transformation_base_d::Aff_transformation_d
	                                                Aff_transformation_d;

  Scaling_repCd() {}
  Scaling_repCd(const FT &s) : _scalefactor(s) {}
  virtual ~Scaling_repCd() {}

  virtual Point_d      transform(const Point_d &p) const
  {
  }

  virtual Vector_d     transform(const Vector_d &v) const
  {
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
  }

  virtual Aff_transformation_d compose(const Translation_d &t) const
  {
  }

  virtual Aff_transformation_d compose(const Scaling_d &t) const
  {
    return Aff_transformation_d(SCALING, _scalefactor*t._scalefactor);
  }

  virtual Aff_transformation_d inverse() const
  {
    return Aff_transformation_d(SCALING, FT(1)/_scalefactor);
  }

  virtual Aff_transformation_d transpose() const
  {
    return Aff_transformation_d(SCALING, _scalefactor);
  }

  virtual bool            is_even() const
  {
    return true;
  }

  virtual FT cartesian(int i, int j) const
  {
    if (i!=j) return FT(0);
    if (i==dimension()) return FT(1);
    return _scalefactor;
  }

  virtual std::ostream &print(std::ostream &os) const
  {
    FT ft0(0);
    os << "Aff_transformationCd(" << _scalefactor << ")";
    return os;
  }

private:
  FT   _scalefactor;
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_SCALING_REP_D_H
