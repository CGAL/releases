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
// file          : include/CGAL/Cartesian/Scaling_rep_2.h
// package       : C2 (3.3.11)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1999/11/05 22:29:49 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
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
  typedef typename Aff_t_base::RT                RT;
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
    _scalefactor(scalefactor)
  {}

  ~Scaling_repC2()
  {}

  Point_2      transform(const Point_2 &p) const
  {
    return Point_2(_scalefactor * p.x(), _scalefactor * p.y());
  }

  Vector_2      transform(const Vector_2 &p) const
  {
    return Vector_2(_scalefactor * p.x(), _scalefactor * p.y());
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
    return Aff_transformation_2(_scalefactor,
                                ft0,
                                t._translationvector.x(),

                                ft0,
                                _scalefactor,
                                t._translationvector.y());
  }

  Aff_transformation_2 compose(const Rotation &t) const
  {
    return Aff_transformation_2(_scalefactor * t._cosinus,
                                _scalefactor * -t._sinus,

                                _scalefactor * t._sinus,
                                _scalefactor * t._cosinus);
  }

  Aff_transformation_2 compose(const Scaling &t) const
  {
    return Aff_transformation_2(SCALING, _scalefactor*t._scalefactor);
  }

  Aff_transformation_2 compose(const Transformation &t) const
  {
    return Aff_transformation_2(_scalefactor * t.t11,
                                _scalefactor * t.t12,
                                 t.t13,

                                _scalefactor * t.t21,
                                _scalefactor * t.t22,
                                 t.t23);
  }

  Aff_transformation_2  inverse() const
  {
    return Aff_transformation_2(SCALING, FT(1)/_scalefactor);
  }

  bool is_even() const
  {
    return true;
  }

  FT cartesian(int i, int j) const
  {
    if (i!=j) return FT(0);
    return (i==2) ? FT(1) : _scalefactor;
  }

  std::ostream &print(std::ostream &os) const
  {
    os << "Aff_transformationC2(" << _scalefactor <<  ")";
    return os;
  }

private:
  FT _scalefactor;
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_ROTATION_REP_2_H
