// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Cartesian/Rotation_rep_2.h
// package       : C2 (4.4)
// revision      : $Revision: 1.12 $
// revision_date : $Date: 2000/06/26 15:00:24 $
// author(s)     : Andreas Fabri, Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_ROTATION_REP_2_H
#define CGAL_CARTESIAN_ROTATION_REP_2_H

#include <CGAL/rational_rotation.h>

CGAL_BEGIN_NAMESPACE

template < class R >
class Rotation_repC2: public Aff_transformation_rep_baseC2<R>
{
friend class Aff_transformation_repC2<R>;
friend class Translation_repC2<R>;
friend class Scaling_repC2<R>;

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

  Rotation_repC2() {}

  Rotation_repC2(const FT &sinus, const FT &cosinus)
    : _sinus(sinus), _cosinus(cosinus) {}

  Rotation_repC2(const Direction_2 &d,
                 const FT &eps_num,
                 const FT &eps_den = FT(1))
  {
    FT sin_num;
    FT cos_num;
    FT denom;

    rational_rotation_approximation(d.to_vector().x(),
                                    d.to_vector().y(),
                                    sin_num,
                                    cos_num,
                                    denom,
                                    eps_num,
                                    eps_den);
    _sinus   = sin_num/denom;
    _cosinus = cos_num/denom;
  }

  Point_2      transform(const Point_2 &p) const
  {
    return Point_2(_cosinus * p.x() - _sinus * p.y(),
                   _sinus * p.x() + _cosinus * p.y());
  }

  Vector_2     transform(const Vector_2 &v) const
  {
    return Vector_2(_cosinus * v.x() - _sinus * v.y(),
                    _sinus * v.x() + _cosinus * v.y());
  }

  Direction_2  transform(const Direction_2 &d) const
  {
    Vector_2  v = d.to_vector();
    return Direction_2(_cosinus * v.x() - _sinus * v.y(),
                       _sinus * v.x() + _cosinus * v.y());
  }

  Aff_transformation_2 inverse() const
  {
    return Aff_transformation_2(ROTATION, - _sinus, _cosinus, FT(1));
  }

  Aff_transformation_2 operator*(const Aff_t_base &t) const
  {
    return t.compose(*this);
  }

  Aff_transformation_2 compose(const Translation &t) const
  {
    return Aff_transformation_2(_cosinus,
                                    -_sinus,
                                    t._translationvector.x(),

                                    _sinus,
                                    _cosinus,
                                    t._translationvector.y());
  }

  Aff_transformation_2 compose(const Rotation &t) const
  {
    return Aff_transformation_2(ROTATION,
                                    t._sinus*_cosinus + t._cosinus*_sinus,
                                    t._cosinus*_cosinus-t._sinus*_sinus );
  }

  Aff_transformation_2 compose(const Scaling &t) const
  {
    return Aff_transformation_2(t._scalefactor*_cosinus,
                                t._scalefactor*-_sinus,

                                t._scalefactor*_sinus,
                                t._scalefactor*_cosinus);
  }

  Aff_transformation_2 compose(const Transformation &t) const
  {
    return Aff_transformation_2(_cosinus*t.t11  + _sinus*t.t12,
                                -_sinus*t.t11  + _cosinus*t.t12,
                                t.t13,

                                _cosinus*t.t21 + _sinus*t.t22,
                                -_sinus*t.t21 + _cosinus*t.t22,
                                t.t23);
  }

  bool is_even() const
  {
    return true;
  }

  FT cartesian(int i, int j) const
  {
    switch (i)
    {
    case 0: switch (j)
            {
              case 0: return _cosinus;
              case 1: return -_sinus;
              case 2: return FT(0);
            }
    case 1: switch (j)
            {
              case 0: return _sinus;
              case 1: return _cosinus;
              case 2: return FT(0);
            }
    case 2: switch (j)
            {
              case 0: return FT(0);
              case 1: return FT(0);
              case 2: return FT(1);
            }
    }
    return FT(0);
  }

  std::ostream &print(std::ostream &os) const
  {
    os << "Aff_transformationC2(" << _sinus << ", " << _cosinus <<  ")";
    return os;
  }

private:
  FT _sinus;
  FT _cosinus;
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_ROTATION_REP_2_H
