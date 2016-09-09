/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/

// Source: Aff_transformationC2.h
// Author: Andreas Fabri, Lutz Kettner

#ifndef CGAL_AFF_TRANSFORMATIONC2_H
#define CGAL_AFF_TRANSFORMATIONC2_H
#include <math.h>
#include <CGAL/rational_rotation.h>
#include <CGAL/bool.h>
#include <CGAL/Handle.h>
#include <CGAL/cartesian_classes.h>
#include <CGAL/determinant.h>

#ifdef CGAL_WORKAROUND_015
#define CGAL_NO_LINE_TRANSFORM_IN_AT
#endif // CGAL_WORKAROUND_015


template < class FT >
class CGAL__Translation_repC2;

template < class FT >
class CGAL__Rotation_repC2;

template < class FT >
class CGAL__Scaling_repC2;

template < class FT >
class CGAL__Aff_transformation_repC2;


template < class FT >
  class CGAL__Aff_transformation_rep_baseC2 : public CGAL_Rep
{
public:
  virtual                       ~CGAL__Aff_transformation_rep_baseC2() {}

  virtual CGAL_PointC2<FT>     transform(const CGAL_PointC2<FT> &p) const  = 0;
  virtual CGAL_VectorC2<FT>    transform(const CGAL_VectorC2<FT> &v) const = 0;
  virtual CGAL_DirectionC2<FT> transform(const CGAL_DirectionC2<FT> &d) const=0;
#ifdef CGAL_WORKAROUND_004

  virtual CGAL_Aff_transformationC2<FT> general_form() const  = 0;
#else
  virtual CGAL_Aff_transformationC2<FT> operator*(
                       const CGAL__Aff_transformation_rep_baseC2<FT> &t)  = 0;

  virtual CGAL_Aff_transformationC2<FT> compose(
                       const CGAL__Translation_repC2<FT> &t) const  = 0;

  virtual CGAL_Aff_transformationC2<FT> compose(
                       const CGAL__Rotation_repC2<FT> &t) const  = 0;

  virtual CGAL_Aff_transformationC2<FT> compose(
                       const CGAL__Scaling_repC2<FT> &t) const  = 0;

  virtual CGAL_Aff_transformationC2<FT> compose(
                       const CGAL__Aff_transformation_repC2<FT> &t) const  = 0;
#endif // GAL_WORKAROUND_004
  virtual CGAL_Aff_transformationC2<FT> inverse() const  = 0;

  virtual bool                 is_even() const  = 0;

  virtual ostream              &print(ostream &os) const
    {
      os << "virtual fct called";
      return os;
    }

};




template < class FT >
class CGAL__Aff_transformation_repC2 :
                              public CGAL__Aff_transformation_rep_baseC2<FT>
{
friend class CGAL__Translation_repC2<FT>;
friend class CGAL__Rotation_repC2<FT>;
friend class CGAL__Scaling_repC2<FT>;
friend class CGAL_Aff_transformationC2<FT>;
public:

  CGAL__Aff_transformation_repC2()
  {}

  CGAL__Aff_transformation_repC2( const FT& m11, const FT& m12,
                                  const FT& m21, const FT& m22)
    : t11(m11), t12(m12), t13(0),
      t21(m21), t22(m22), t23(0)
  {}

  CGAL__Aff_transformation_repC2( const FT& m11, const FT& m12, const FT& m13,
                                  const FT& m21, const FT& m22, const FT& m23)
    : t11(m11), t12(m12), t13(m13),
      t21(m21), t22(m22), t23(m23)
  {}

  ~CGAL__Aff_transformation_repC2()
  {}

  CGAL_PointC2<FT> transform(const CGAL_PointC2<FT>& p) const
  {
    return CGAL_PointC2<FT>(t11 * p.x() + t12 * p.y() + t13,
                            t21 * p.x() + t22 * p.y() + t23);
  }


  // note that a vector is not translated
  CGAL_VectorC2<FT> transform(const CGAL_VectorC2<FT>& v) const
  {
    return CGAL_VectorC2<FT>(t11 * v.x() + t12 * v.y(),
                             t21 * v.x() + t22 * v.y());
  }


  // note that a direction is not translated
  CGAL_DirectionC2<FT> transform(const CGAL_DirectionC2<FT>& dir) const
  {
    CGAL_VectorC2<FT> v = dir.vector();
    return CGAL_DirectionC2<FT>(t11 * v.x() + t12 * v.y(),
                                t21 * v.x() + t22 * v.y());
  }

  CGAL_Aff_transformationC2<FT> inverse() const
  {
    FT det = FT(1) / (t11 * t22 - t12 * t21);

    return CGAL_Aff_transformationC2<FT>(
      det * t22,    det * (-t12), det * (t12*t23-t13*t22),
      det * (-t21), det * t11 ,   det * (t13*t21-t11*t23));
  }

#ifdef CGAL_WORKAROUND_004

  CGAL_Aff_transformationC2<FT> general_form() const
  {
    return CGAL_Aff_transformationC2<FT>(t11, t12, t13,
                                         t21, t22, t23);
  }

#else
  CGAL_Aff_transformationC2<FT> operator*(
                          const CGAL__Aff_transformation_rep_baseC2<FT> &t)
  {
    return t.compose(*this);
  }

  CGAL_Aff_transformationC2<FT> compose(
                                const CGAL__Translation_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(t11,
                                         t12,
                                         t13 + t._translationvector.x(),

                                         t21,
                                         t22,
                                         t23 + t._translationvector.y());
  }

  virtual CGAL_Aff_transformationC2<FT> compose(
                                  const CGAL__Rotation_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(t._cosinus*t11 - t._sinus*t21,
                                         t._cosinus*t12 - t._sinus*t22,
                                         t._cosinus*t13 - t._sinus*t23,

                                         t._sinus*t11 + t._cosinus*t21,
                                         t._sinus*t12 + t._cosinus*t22,
                                         t._sinus*t13 + t._cosinus*t23);
  }

  virtual CGAL_Aff_transformationC2<FT> compose(
                                     const CGAL__Scaling_repC2<FT> &t) const
  {
     return CGAL_Aff_transformationC2<FT>(t._scalefactor * t11,
                                          t._scalefactor * t12,
                                          t._scalefactor * t13,

                                          t._scalefactor * t21,
                                          t._scalefactor * t22,
                                          t._scalefactor * t23);
  }

  virtual CGAL_Aff_transformationC2<FT> compose(
                            const CGAL__Aff_transformation_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(
            t.t11*t11 + t.t12*t21,
            t.t11*t12 + t.t12*t22,
            t.t11*t13 + t.t12*t23 + t.t13,

            t.t21*t11 + t.t22*t21,
            t.t21*t12 + t.t22*t22,
            t.t21*t13 + t.t22*t23 + t.t23 );
  }
#endif // CGAL_WORKAROUND_004

 virtual bool is_even() const
  {
    return ( CGAL_sign(t11 * t22 - t12 * t21) == 1 );
  }

 virtual ostream &print(ostream &os) const
  {
    os << "Aff_transformationC2(" << t11 << " " << t12 << " " << t13 << endl;
    os << "                     " << t21 << " " << t22 << " " << t23 << ")";
    return os;
  }

private:

    FT   t11, t12, t13;
    FT   t21, t22, t23;

};

template < class FT >
class CGAL__Translation_repC2 : public CGAL__Aff_transformation_rep_baseC2<FT>
{
friend class CGAL__Aff_transformation_repC2<FT>;
friend class CGAL__Rotation_repC2<FT>;
friend class CGAL__Scaling_repC2<FT>;
public:
  CGAL__Translation_repC2()
  {}

  CGAL__Translation_repC2(const CGAL_VectorC2<FT> &tv) :
    _translationvector(tv)
  {}

  ~CGAL__Translation_repC2()
  {}

  CGAL_PointC2<FT>        transform(const CGAL_PointC2<FT> &p) const
  {
    return p + _translationvector;
  }

  CGAL_VectorC2<FT>        transform(const CGAL_VectorC2<FT> &v) const
  {
    return v;
  }

  CGAL_DirectionC2<FT>    transform(const CGAL_DirectionC2<FT> &d) const
  {
    return d;
  }

#ifdef CGAL_WORKAROUND_004

  CGAL_Aff_transformationC2<FT> general_form() const
  {
    return CGAL_Aff_transformationC2<FT>
                                    (FT(1), FT(0), _translationvector.x(),
                                    FT(0), FT(1), _translationvector.y());
  }

#else
  CGAL_Aff_transformationC2<FT> operator*(
                            const CGAL__Aff_transformation_rep_baseC2<FT> &t)
  {
    return t.compose(*this);
  }

  CGAL_Aff_transformationC2<FT> compose(
                            const CGAL__Translation_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(CGAL_TRANSLATION,
                                         _translationvector +
                                         t._translationvector);
  }

  virtual CGAL_Aff_transformationC2<FT> compose(
                                   const CGAL__Rotation_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(t._cosinus,
                                         -t._sinus,
                                         t._cosinus*_translationvector.x() -
                                         t._sinus*_translationvector.y(),

                                         t._sinus,
                                         t._cosinus,
                                         t._sinus*_translationvector.x() +
                                         t._cosinus*_translationvector.y());
  }

  virtual CGAL_Aff_transformationC2<FT> compose(
                                     const CGAL__Scaling_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(t._scalefactor,
                                         FT(0),
                                         t._scalefactor*_translationvector.x(),

                                         FT(0),
                                         t._scalefactor,
                                         t._scalefactor*_translationvector.y());
  }

  virtual CGAL_Aff_transformationC2<FT> compose(
                            const CGAL__Aff_transformation_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(t.t11,
                                         t.t12,
                                         t.t11 * _translationvector.x()
                                         + t.t12 * _translationvector.y()
                                         + t.t13,

                                         t.t21,
                                         t.t22,
                                         t.t21 * _translationvector.x()
                                         + t.t22*_translationvector.y()
                                         + t.t23);
  }
#endif // CGAL_WORKAROUND_004

  CGAL_Aff_transformationC2<FT>  inverse() const
  {
    return CGAL_Aff_transformationC2<FT>(CGAL_TRANSLATION,
                                         - _translationvector);
  }

  virtual bool                 is_even() const
  {
    return true;
  }


 virtual ostream &print(ostream &os) const
  {
    os << "Aff_transformationC2(VectorC2(" << _translationvector.x() << ", "
       << _translationvector.y()  <<  "))";
    return os;
  }

private:
  CGAL_VectorC2<FT>   _translationvector;
};

template < class FT >
class CGAL__Rotation_repC2: public CGAL__Aff_transformation_rep_baseC2<FT>
{
friend class CGAL__Aff_transformation_repC2<FT>;
friend class CGAL__Translation_repC2<FT>;
friend class CGAL__Scaling_repC2<FT>;
public:
  CGAL__Rotation_repC2()
  {}

  CGAL__Rotation_repC2(const FT &sinus, const FT &cosinus)
    : _sinus(sinus), _cosinus(cosinus)
  {}

  CGAL__Rotation_repC2(const CGAL_DirectionC2<FT> &d,
                       const FT &eps_num,
                       const FT &eps_den = FT(1))
  {
    FT sin_num;
    FT cos_num;
    FT denom;

    CGAL_rational_rotation_approximation(d.vector().x(),
                                         d.vector().y(),
                                         sin_num,
                                         cos_num,
                                         denom,
                                         eps_num,
                                         eps_den);
    _sinus   = sin_num/denom;
    _cosinus = cos_num/denom;
  }

  ~CGAL__Rotation_repC2()
  {}

  CGAL_PointC2<FT>      transform(const CGAL_PointC2<FT> &p) const
  {
    return CGAL_PointC2<FT>(_cosinus * p.x() - _sinus * p.y(),
                            _sinus * p.x() + _cosinus * p.y());
  }

  CGAL_VectorC2<FT>  transform(const CGAL_VectorC2<FT> &v) const
  {
    return CGAL_VectorC2<FT>(_cosinus * v.x() - _sinus * v.y(),
                             _sinus * v.x() + _cosinus * v.y());
  }

  CGAL_DirectionC2<FT>  transform(const CGAL_DirectionC2<FT> &d) const
  {
    CGAL_VectorC2<FT>  v = d.vector();
    return CGAL_DirectionC2<FT>(_cosinus * v.x() - _sinus * v.y(),
                                _sinus * v.x() + _cosinus * v.y());
  }

  CGAL_Aff_transformationC2<FT> inverse() const
  {
    return CGAL_Aff_transformationC2<FT>(CGAL_ROTATION,
                                         - _sinus, _cosinus, FT(1));
  }
#ifdef CGAL_WORKAROUND_004

  CGAL_Aff_transformationC2<FT> general_form() const
  {
    return CGAL_Aff_transformationC2<FT>(_cosinus, - _sinus, FT(0),
                                         _sinus,   _cosinus, FT(0));
  }

#else

  CGAL_Aff_transformationC2<FT> operator*(
                            const CGAL__Aff_transformation_rep_baseC2<FT> &t)
  {
    return t.compose(*this);
  }

  CGAL_Aff_transformationC2<FT> compose(
                                const CGAL__Translation_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(_cosinus,
                                         -_sinus,
                                         t._translationvector.x(),

                                         _sinus,
                                         _cosinus,
                                         t._translationvector.y());
  }


  virtual CGAL_Aff_transformationC2<FT> compose(
                                     const CGAL__Rotation_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(CGAL_ROTATION,
                                         t._sinus*_cosinus + t._cosinus*_sinus,
                                         t._cosinus*_cosinus-t._sinus*_sinus );
  }

  virtual CGAL_Aff_transformationC2<FT> compose(
                                     const CGAL__Scaling_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(t._scalefactor*_cosinus,
                                         t._scalefactor*-_sinus,

                                         t._scalefactor*_sinus,
                                         t._scalefactor*_cosinus);
  }

  virtual CGAL_Aff_transformationC2<FT> compose(
                           const CGAL__Aff_transformation_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(_cosinus*t.t11  + _sinus*t.t12,
                                         -_sinus*t.t11  + _cosinus*t.t12,
                                         t.t13,

                                         _cosinus*t.t21 + _sinus*t.t22,
                                         -_sinus*t.t21 + _cosinus*t.t22,
                                          t.t23);
  }
#endif // CGAL_WORKAROUND_004

  virtual bool                 is_even() const
  {
    return true;
  }


 virtual ostream &print(ostream &os) const
  {
    os << "Aff_transformationC2(" << _sinus << ", " << _cosinus <<  ")";
    return os;
  }

private:
  FT _sinus;
  FT _cosinus;
};

template < class FT >
class CGAL__Scaling_repC2: public CGAL__Aff_transformation_rep_baseC2<FT>
{
friend class CGAL__Aff_transformation_repC2<FT>;
friend class CGAL__Rotation_repC2<FT>;
friend class CGAL__Translation_repC2<FT>;

public:
  CGAL__Scaling_repC2()
  {}

  CGAL__Scaling_repC2(const FT &scalefactor) :
    _scalefactor(scalefactor)
  {}

  ~CGAL__Scaling_repC2()
  {}

  CGAL_PointC2<FT>      transform(const CGAL_PointC2<FT> &p) const
  {
    return CGAL_PointC2<FT>(_scalefactor * p.x(), _scalefactor * p.y());
  }

  CGAL_VectorC2<FT>      transform(const CGAL_VectorC2<FT> &p) const
  {
    return CGAL_VectorC2<FT>(_scalefactor * p.x(), _scalefactor * p.y());
  }

  CGAL_DirectionC2<FT>  transform(const CGAL_DirectionC2<FT> &d) const
  {
    return d;
  }

#ifdef CGAL_WORKAROUND_004

  CGAL_Aff_transformationC2<FT> general_form() const
  {
    return CGAL_Aff_transformationC2<FT>(_scalefactor, FT(0), FT(0),
                                         FT(0), _scalefactor, FT(0));
  }

#else
  CGAL_Aff_transformationC2<FT> operator*(
                           const CGAL__Aff_transformation_rep_baseC2<FT> &t)
  {
   return t.compose(*this);
  }

  CGAL_Aff_transformationC2<FT> compose(
                              const CGAL__Translation_repC2<FT> &t) const
  {
    FT ft0(0);

    return CGAL_Aff_transformationC2<FT>(_scalefactor,
                                         ft0,
                                         t._translationvector.x(),

                                         ft0,
                                         _scalefactor,
                                         t._translationvector.y());
  }

  virtual CGAL_Aff_transformationC2<FT> compose(
                                     const CGAL__Rotation_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(_scalefactor * t._cosinus,
                                         _scalefactor * -t._sinus,

                                         _scalefactor * t._sinus,
                                         _scalefactor * t._cosinus);
  }

  virtual CGAL_Aff_transformationC2<FT> compose(
                                    const CGAL__Scaling_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(CGAL_SCALING,
                                         _scalefactor*t._scalefactor);
  }

  virtual CGAL_Aff_transformationC2<FT> compose(
                            const CGAL__Aff_transformation_repC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(_scalefactor * t.t11,
                                         _scalefactor * t.t12,
                                          t.t13,

                                         _scalefactor * t.t21,
                                         _scalefactor * t.t22,
                                          t.t23);
  }
#endif // CGAL_WORKAROUND_004

  CGAL_Aff_transformationC2<FT>  inverse() const
  {
    return CGAL_Aff_transformationC2<FT>(CGAL_SCALING, FT(1)/_scalefactor);
  }

  virtual bool                 is_even() const
  {
    return true;
  }


 virtual ostream &print(ostream &os) const
  {
    os << "Aff_transformationC2(" << _scalefactor <<  ")";
    return os;
  }

private:
  FT _scalefactor;
};



template < class FT >
class CGAL_Aff_transformationC2 : public CGAL_Handle
{


public:
                      CGAL_Aff_transformationC2();
                      CGAL_Aff_transformationC2(
                                    const CGAL_Aff_transformationC2<FT> &t);

                      // Translation:
                      CGAL_Aff_transformationC2(const CGAL_Translation,
                                                const CGAL_VectorC2<FT> &v);

                      // Rational Rotation:
                      CGAL_Aff_transformationC2(const CGAL_Rotation,
                                                const CGAL_DirectionC2<FT> &d,
                             const FT &num,
                             const FT &den = FT(1));

                      CGAL_Aff_transformationC2(const CGAL_Rotation,
                                                const FT &sine_rho,
                                                const FT &cosine_rho,
                                                const FT &hw = FT(1));

                      // Scaling:
                      CGAL_Aff_transformationC2(const CGAL_Scaling,
                                                const FT &s,
                                                const FT &w = FT(1));

                      // The general case:
                      CGAL_Aff_transformationC2(const FT & m11,
                                                const FT & m12,
                                                const FT & m13,
                                                const FT & m21,
                                                const FT & m22,
                                                const FT & m23,
                                                const FT &w = FT(1));

                      CGAL_Aff_transformationC2(const FT & m11, const FT & m12,
                                                const FT & m21, const FT & m22,
                                                const FT &w = FT(1));

                      ~CGAL_Aff_transformationC2();

  CGAL_Aff_transformationC2<FT> &operator=(
                                      const CGAL_Aff_transformationC2<FT> &t);

  CGAL_PointC2<FT>     transform(const CGAL_PointC2<FT> &p) const;
  CGAL_PointC2<FT>     operator()(const CGAL_PointC2<FT> &p) const;

  CGAL_VectorC2<FT>    transform(const CGAL_VectorC2<FT> &p) const;
  CGAL_VectorC2<FT>    operator()(const CGAL_VectorC2<FT> &p) const;

  CGAL_DirectionC2<FT> transform(const CGAL_DirectionC2<FT> &d) const;
  CGAL_DirectionC2<FT> operator()(const CGAL_DirectionC2<FT> &d) const;

#ifndef CGAL_NO_LINE_TRANSFORM_IN_AT
  CGAL_LineC2<FT> transform(const CGAL_LineC2<FT> &l) const;
  CGAL_LineC2<FT> operator()(const CGAL_LineC2<FT> &l) const;
#endif // CGAL_NO_LINE_TRANSFORM_IN_AT

  CGAL_Aff_transformationC2<FT>  inverse() const;

  bool                 is_even() const {return ptr()->is_even();}
  bool                 is_odd() const;
#ifdef CGAL_WORKAROUND_004

CGAL_Aff_transformationC2<FT>  general_form() const
{
  return ptr()->general_form();
}


CGAL_Aff_transformationC2<FT> operator*(
                                 const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_Aff_transformationC2<FT> tt1 = general_form(),
                                tt2 = t.general_form();
  CGAL__Aff_transformation_repC2<FT> *t1 =
                                (CGAL__Aff_transformation_repC2<FT>*)tt1.ptr();

  CGAL__Aff_transformation_repC2<FT> *t2 =
                                (CGAL__Aff_transformation_repC2<FT>*)tt2.ptr();

  return CGAL_Aff_transformationC2<FT>(
            t1->t11*t2->t11 + t1->t12*t2->t21,
            t1->t11*t2->t12 + t1->t12*t2->t22,
            t1->t11*t2->t13 + t1->t12*t2->t23 + t1->t13,

            t1->t21*t2->t11 + t1->t22*t2->t21,
            t1->t21*t2->t12 + t1->t22*t2->t22,
            t1->t21*t2->t13 + t1->t22*t2->t23 + t1->t23 );
}

#else

CGAL_Aff_transformationC2<FT> operator*(
                                 const CGAL_Aff_transformationC2<FT> &t) const
{
  return (*ptr()) * (*t.ptr());
}

#endif // CGAL_WORKAROUND_004


  ostream              &print(ostream &os) const;



private:
    CGAL__Aff_transformation_rep_baseC2<FT>* ptr() const
    {
      return  (CGAL__Aff_transformation_rep_baseC2<FT>*)PTR;
    }

};



template < class FT >
CGAL_Aff_transformationC2<FT>::CGAL_Aff_transformationC2()
{
  PTR = new CGAL__Aff_transformation_repC2<FT>(FT(1), FT(0),
                                               FT(0), FT(1));
}

template < class FT >
CGAL_Aff_transformationC2<FT>::CGAL_Aff_transformationC2(
                                     const CGAL_Aff_transformationC2<FT> &t)
  : CGAL_Handle(t)
{}


template < class FT >
CGAL_Aff_transformationC2<FT>::CGAL_Aff_transformationC2(const FT & m11,
                                                         const FT & m12,
                                                         const FT & m21,
                                                         const FT & m22,
                                                         const FT &w)
{
  if (w != FT(1)){
    PTR = new CGAL__Aff_transformation_repC2<FT>(m11/w, m12/w, m21/w, m22/w);
  }else{
    PTR = new CGAL__Aff_transformation_repC2<FT>(m11, m12, m21, m22);
  }
}

template < class FT >
CGAL_Aff_transformationC2<FT>::CGAL_Aff_transformationC2(
                                                  const CGAL_Translation,
                                                  const CGAL_VectorC2<FT> &v)
{
  PTR = new CGAL__Translation_repC2<FT>(v);
}

template < class FT >
CGAL_Aff_transformationC2<FT>::CGAL_Aff_transformationC2(
                                  const CGAL_Rotation,
                                  const CGAL_DirectionC2<FT> &d,
                                  const FT &num,
                                  const FT &den)
{
  PTR = new CGAL__Rotation_repC2<FT>(d, num, den);
}


template < class FT >
CGAL_Aff_transformationC2<FT>::CGAL_Aff_transformationC2(const CGAL_Rotation,
                              const FT &sine, const FT &cosine, const FT &w)
{
  if (w != FT(1)){
    PTR = new CGAL__Rotation_repC2<FT>(sine/w, cosine/w);
  }else{
    PTR = new CGAL__Rotation_repC2<FT>(sine, cosine);
  }
}

template < class FT >
CGAL_Aff_transformationC2<FT>::CGAL_Aff_transformationC2(const CGAL_Scaling,
                                                         const FT &s,
                                                         const FT &w)
{
  if (w != FT(1)){
    PTR = new CGAL__Scaling_repC2<FT>(s/w);
  }else{
    PTR = new CGAL__Scaling_repC2<FT>(s);
  }
}



// and a 3x2 matrix for the operations combining rotation, scaling, translation
template < class FT >
CGAL_Aff_transformationC2<FT>::CGAL_Aff_transformationC2(
                                const FT & m11, const FT & m12, const FT & m13,
                                const FT & m21, const FT & m22, const FT & m23,
                                const FT &w)
{
  if (w != FT(1)){
    PTR = new CGAL__Aff_transformation_repC2<FT>(m11/w, m12/w, m13/w,
                                                 m21/w, m22/w, m23/w);
  } else {
    PTR = new CGAL__Aff_transformation_repC2<FT>(m11, m12, m13,
                                                 m21, m22, m23);
  }
}

template < class FT >
CGAL_Aff_transformationC2<FT>::~CGAL_Aff_transformationC2()
{}

template < class FT >
CGAL_Aff_transformationC2<FT> &CGAL_Aff_transformationC2<FT>::operator=(
                                        const CGAL_Aff_transformationC2<FT> &t)
{
  CGAL_Handle::operator=(t);
  return *this;
}



template < class FT >
CGAL_PointC2<FT> CGAL_Aff_transformationC2<FT>::transform(
                                           const CGAL_PointC2<FT> &p) const
{
  return ptr()->transform(p);
}

template < class FT >
inline CGAL_PointC2<FT> CGAL_Aff_transformationC2<FT>::operator()(
                                           const CGAL_PointC2<FT> &p) const
{
  return transform(p);
}

template < class FT >
CGAL_VectorC2<FT> CGAL_Aff_transformationC2<FT>::transform(
                                            const CGAL_VectorC2<FT> &p) const
{
  return ptr()->transform(p);
}

template < class FT >
inline CGAL_VectorC2<FT> CGAL_Aff_transformationC2<FT>::operator()(
                                            const CGAL_VectorC2<FT> &p) const
{
  return transform(p);
}
template < class FT >
CGAL_DirectionC2<FT> CGAL_Aff_transformationC2<FT>::transform(
                                           const CGAL_DirectionC2<FT> &d) const
{
  return ptr()->transform(d);
}

template < class FT >
inline CGAL_DirectionC2<FT> CGAL_Aff_transformationC2<FT>::operator()(
                                           const CGAL_DirectionC2<FT> &d) const
{
  return transform(d);
}

#ifndef CGAL_NO_LINE_TRANSFORM_IN_AT
template < class FT >
inline CGAL_LineC2<FT> CGAL_Aff_transformationC2<FT>::transform(
                                           const CGAL_LineC2<FT> &l) const
{
  return CGAL_LineC2<FT>(ptr()->transform(l.point(0)),
                         ptr()->transform(l.direction()));
}

template < class FT >
inline CGAL_LineC2<FT> CGAL_Aff_transformationC2<FT>::operator()(
                                           const CGAL_LineC2<FT> &l) const
{
  return transform(l);
}
#endif // CGAL_NO_LINE_TRANSFORM_IN_AT

template < class FT >
CGAL_Aff_transformationC2<FT>  CGAL_Aff_transformationC2<FT>::inverse() const
{
  return ptr()->inverse();
}


template < class FT >
bool  CGAL_Aff_transformationC2<FT>::is_odd() const
{
  return ! (ptr()->is_even());
}




template < class FT >
ostream& CGAL_Aff_transformationC2<FT>::print(ostream &os) const
{
  ptr()->print(os);
  return os;
}



#ifndef CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATIONC2
template < class FT >
ostream& operator<<(ostream& os, const CGAL_Aff_transformationC2<FT>& t)
{
    t.print(os);
    return os;
}
#endif // CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATIONC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATIONC2
#endif // CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATIONC2



#endif // CGAL_AFF_TRANSFORMATIONC2_H
