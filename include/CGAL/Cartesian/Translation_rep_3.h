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
// file          : include/CGAL/Cartesian/Translation_rep_3.h
// package       : C3 (4.0.3)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1999/11/05 22:29:45 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
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

  Translation_repC3() {}
  Translation_repC3(const Vector_3 &tv) : _translationvector(tv) {}
  virtual ~Translation_repC3() {}

  virtual Point_3     transform(const Point_3 &p) const
  {
    return p + _translationvector;
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
				t.t11 * _translationvector.x()
				+ t.t12 * _translationvector.y()
				+ t.t13 * _translationvector.z() + t.t14,
				
				t.t21,
                                t.t22,
				t.t23,
				t.t21 * _translationvector.x()
				+ t.t22 * _translationvector.y()
				+ t.t23 * _translationvector.z() + t.t24,
				
				t.t31,
                                t.t32,
				t.t33,
				t.t31 * _translationvector.x()
				+ t.t32 * _translationvector.y()
				+ t.t33 * _translationvector.z() + t.t34);
  }

  virtual Aff_transformation_3 compose(const Translation_3 &t) const
  {
    return Aff_transformation_3(TRANSLATION,
                                _translationvector + t._translationvector);
  }

  virtual Aff_transformation_3 compose(const Scaling_3 &t) const
  {
    FT ft0(0);
    return Aff_transformation_3(t._scalefactor,
                                ft0,
				ft0,
				t._scalefactor * _translationvector.x(),
				
				ft0,
                                t._scalefactor,
				ft0,
				t._scalefactor * _translationvector.y(),
				
				ft0,
                                ft0,
				t._scalefactor,
				t._scalefactor * _translationvector.z());
  }

  virtual Aff_transformation_3 inverse() const
  {
    return Aff_transformation_3(TRANSLATION, - _translationvector);
  }

  virtual Aff_transformation_3 transpose() const
  {
    FT ft1(1), ft0(0);
    return Aff_transformation_3(TRANSLATION, _translationvector);
  }
  
  virtual bool is_even() const
  {
    return true;
  }

  virtual FT cartesian(int i, int j) const
  {
    if (j==i) return FT(1);
    if (j==3) return _translationvector[i];
    return FT(0);
  }

  virtual std::ostream &print(std::ostream &os) const
  {
    FT ft0(0), ft1(1);
    os << "Aff_transformationC3(VectorC3("<< _translationvector.x() << ","
       << _translationvector.y() << ","
       << _translationvector.z() << "))\n";
    return os;
  }

private:
  Vector_3   _translationvector;
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_TRANSLATION_REP_3_H
