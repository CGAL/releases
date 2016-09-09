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

// Source: Aff_transformationC3.h
// Author: Andreas Fabri

#ifndef CGAL_AFF_TRANSFORMATIONC3_H
#define CGAL_AFF_TRANSFORMATIONC3_H
#include <math.h>
#include <CGAL/bool.h>
#include <CGAL/Handle.h>
#include <CGAL/cartesian_classes.h>
#include <CGAL/determinant.h>

#ifdef CGAL_WORKAROUND_015
#define CGAL_NO_PLANE_TRANSFORM_IN_AT
#endif // CGAL_WORKAROUND_015

template < class FT >
class CGAL__Aff_transformation_rep_baseC3 : public CGAL_Rep
{
public:
  virtual                      ~CGAL__Aff_transformation_rep_baseC3(){}

  virtual CGAL_PointC3<FT>     transform(const CGAL_PointC3<FT> &p) const = 0;
  virtual CGAL_VectorC3<FT>    transform(const CGAL_VectorC3<FT> &v) const = 0;
  virtual CGAL_DirectionC3<FT> transform(const CGAL_DirectionC3<FT> &d)
                                                                    const = 0;

  virtual CGAL_Aff_transformationC3<FT> inverse() const = 0;

  virtual CGAL_Aff_transformationC3<FT> transpose() const = 0;

  virtual bool                 is_even() const = 0;
  virtual ostream              &print(ostream &os) const = 0;
  virtual CGAL_Aff_transformationC3<FT> general_form() const = 0;
};



template < class FT >
class CGAL__Aff_transformation_repC3 :
                              public CGAL__Aff_transformation_rep_baseC3<FT>
{
  friend class CGAL_Aff_transformationC3<FT>;

  friend   CGAL_Aff_transformationC3<FT>
  CGAL__general_transformation_composition(
                                   CGAL__Aff_transformation_repC3<FT> &l,
                                   CGAL__Aff_transformation_repC3<FT> &r );
  friend CGAL_Aff_transformationC3<FT> operator*
                                (const CGAL_Aff_transformationC3<FT> &a,
                                 const CGAL_Aff_transformationC3<FT> &b);

public:

  CGAL__Aff_transformation_repC3()
  {}

  CGAL__Aff_transformation_repC3( const FT& m11, const FT& m12, const FT& m13,
                                  const FT& m21, const FT& m22, const FT& m23,
                                  const FT& m31, const FT& m32, const FT& m33)
    : t11(m11), t12(m12), t13(m13), t14(0),
      t21(m21), t22(m22), t23(m23), t24(0),
      t31(m31), t32(m32), t33(m33), t34(0)
  {}

  CGAL__Aff_transformation_repC3( const FT& m11, const FT& m12,
                                  const FT& m13,const FT& m14,

                                  const FT& m21, const FT& m22,
                                  const FT& m23, const FT& m24,

                                  const FT& m31, const FT& m32,
                                  const FT& m33, const FT& m34)
    : t11(m11), t12(m12), t13(m13), t14(m14),
      t21(m21), t22(m22), t23(m23), t24(m24),
      t31(m31), t32(m32), t33(m33), t34(m34)
  {}

  ~CGAL__Aff_transformation_repC3()
  {}

  CGAL_PointC3<FT> transform(const CGAL_PointC3<FT>& p) const
  {
    return CGAL_PointC3<FT>(t11 * p.x() + t12 * p.y() + t13 * p.z() + t14,
                            t21 * p.x() + t22 * p.y() + t23 * p.z() + t24,
                            t31 * p.x() + t32 * p.y() + t33 * p.z() + t34);
  }


  // note that a vector is not translated
  CGAL_VectorC3<FT> transform(const CGAL_VectorC3<FT>& v) const
  {
    return CGAL_VectorC3<FT>(t11 * v.x() + t12 * v.y() + t13 * v.z(),
                             t21 * v.x() + t22 * v.y() + t23 * v.z(),
                             t31 * v.x() + t32 * v.y() + t33 * v.z());
  }


  // note that a direction is not translated
  CGAL_DirectionC3<FT> transform(const CGAL_DirectionC3<FT>& dir) const
  {
    CGAL_VectorC3<FT> v = dir.vector();
    return CGAL_DirectionC3<FT>(t11 * v.x() + t12 * v.y() + t13 * v.z(),
                                t21 * v.x() + t22 * v.y() + t23 * v.z(),
                                t31 * v.x() + t32 * v.y() + t33 * v.z());
  }

  CGAL_Aff_transformationC3<FT> inverse() const
  {
 FT  RT0(0);
 FT  RT1(1);
 return CGAL_Aff_transformationC3<FT>(
                           CGAL_det3x3_by_formula( t22, t23, t24,
                                                   t32, t33, t34,     // i 11
                                                   RT0, RT0, RT1 ),

                        -  CGAL_det3x3_by_formula( t12, t13, t14,
                                                   t32, t33, t34,     // i 12
                                                   RT0, RT0, RT1 ),

                           CGAL_det3x3_by_formula( t12, t13, t14,
                                                   t22, t23, t24,     // i 13
                                                   RT0, RT0, RT1 ),

                        -  CGAL_det3x3_by_formula( t12, t13, t14,
                                                   t22, t23, t24,     // i 14
                                                   t32, t33, t34 ),

                        -  CGAL_det3x3_by_formula( t21, t23, t24,
                                                   t31, t33, t34,     // i 21
                                                   RT0, RT0, RT1 ),

                           CGAL_det3x3_by_formula( t11, t13, t14,
                                                   t31, t33, t34,     // i 22
                                                   RT0, RT0, RT1 ),

                        -  CGAL_det3x3_by_formula( t11, t13, t14,
                                                   t21, t23, t24,     // i 23
                                                   RT0, RT0, RT1 ),

                           CGAL_det3x3_by_formula( t11, t13, t14,
                                                   t21, t23, t24,     // i 24
                                                   t31, t33, t34 ),

                           CGAL_det3x3_by_formula( t21, t22, t24,
                                                   t31, t32, t34,     // i 31
                                                   RT0, RT0, RT1 ),

                        -  CGAL_det3x3_by_formula( t11, t12, t14,
                                                   t31, t32, t34,     // i 32
                                                   RT0, RT0, RT1 ),

                           CGAL_det3x3_by_formula( t11, t12, t14,
                                                   t21, t22, t24,     // i 33
                                                   RT0, RT0, RT1 ),

                        -  CGAL_det3x3_by_formula( t11, t12, t14,
                                                   t21, t22, t24,     // i 34
                                                   t31, t32, t34 ),

                           CGAL_det3x3_by_formula( t11, t12, t13,
                                                   t21, t22, t23,     // i 44
                                                   t31, t32, t33 )
                                                       ) ;

    /*
    FT xx = t22 * t33 - t23 * t32,
       yy = t12*t33 - t13*t32,
       zz = t12*t23-t13*t22;

    FT det = FT(1) / ( t11 * xx - t21 * yy + t31 * zz -
                     CGAL_det3x3_by_formula(t12, t13, t14,
                                            t22, t23, t24,
                                            t32, t33, t34) );

    return CGAL_Aff_transformationC3<FT>(
      det * xx,    det * (t13*t32-t12*t33), det * zz,
      -CGAL_det3x3_by_formula(t12, t13, t14,
                              t22, t23, t24,
                              t32, t33, t34),

      det * (t23*t31-t21*t33), det * (t11 * t33 - t13 * t31) ,
      det * (t13*t21-t11*t23),

      CGAL_det3x3_by_formula(t11, t13, t14,
                              t21, t23, t24,
                              t31, t33, t34),

      det * (t21*t32-t22*t31), det * (t12*t31-t11*t32),
      det * (t11 * t22 - t12 * t21),

      -CGAL_det3x3_by_formula(t11, t12, t14,
                              t21, t22, t24,
                              t31, t32, t34));
                              */
  }


  virtual CGAL_Aff_transformationC3<FT> general_form() const
  {
    return CGAL_Aff_transformationC3<FT>(t11, t12, t13, t14,
                                         t21, t22, t23, t24,
                                         t31, t32, t33, t34);
  }

  virtual CGAL_Aff_transformationC3<FT> transpose() const
  {
    FT ft0(0);
    return CGAL_Aff_transformationC3<FT>( t11, t21, t31, ft0,
                                          t12, t22, t32, ft0,
                                          t13, t23, t33, ft0);
  }

 virtual bool is_even() const
  {
    return ( CGAL_sign(CGAL_det3x3_by_formula(t11, t12, t13,
                                              t21, t22, t23,
                                              t31, t32, t33)) == 1 );
  }

  ostream &print(ostream &os) const
  {
    os <<"                   "<< t11 <<' '<< t12 <<' '<< t13 <<' '<< t14 <<"\n";
    os <<"                   "<< t21 <<' '<< t22 <<' '<< t23 <<' '<< t24 <<"\n";
    os <<"                   "<< t31<<' '<< t32 <<' '<< t33 <<' '<< t34 <<")\n";

    return os;
  }
private:

    FT   t11, t12, t13, t14;
    FT   t21, t22, t23, t24;
    FT   t31, t32, t33, t34;

};

template < class FT >
class CGAL__Translation_repC3 : public CGAL__Aff_transformation_rep_baseC3<FT>
{
  friend ostream &operator<<(ostream &os, CGAL__Translation_repC3<FT> &t);
  friend CGAL_Aff_transformationC3<FT> operator*
                                (const CGAL_Aff_transformationC3<FT> &a,
                                 const CGAL_Aff_transformationC3<FT> &b);

public:
  CGAL__Translation_repC3()
  {}

  CGAL__Translation_repC3(const CGAL_VectorC3<FT> &tv) :
    translationvector(tv)
  {}

  ~CGAL__Translation_repC3()
  {}

  CGAL_PointC3<FT>        transform(const CGAL_PointC3<FT> &p) const
  {
    return p + translationvector;
  }

  CGAL_VectorC3<FT>        transform(const CGAL_VectorC3<FT> &v) const
  {
    return v;
  }

  CGAL_DirectionC3<FT>    transform(const CGAL_DirectionC3<FT> &d) const
  {
    return d;
  }

  CGAL_Aff_transformationC3<FT> inverse() const
  {
    return CGAL_Aff_transformationC3<FT>(CGAL_TRANSLATION,
                                         - translationvector);
  }

  CGAL_Aff_transformationC3<FT> transpose() const
  {
    FT ft0(0), ft1(1);

    return CGAL_Aff_transformationC3<FT>(ft1, ft0, ft0, ft0,
                                         ft0, ft1, ft0, ft0,
                                         ft0, ft0, ft1, ft0);
  }

  CGAL_Aff_transformationC3<FT> general_form() const
  {
    FT ft0(0), ft1(1);

    return CGAL_Aff_transformationC3<FT>(ft1, ft0, ft0, translationvector.x(),
                                         ft0, ft1, ft0, translationvector.y(),
                                         ft0, ft0, ft1, translationvector.z());
  }


  virtual bool                 is_even() const
  {
    return true;
  }

  ostream &print(ostream &os) const
  {
    FT ft0(0), ft1(1);
    os << "                   "<< ft1 <<' '<< ft0 <<' '<< ft0 <<' '
       << translationvector.x() << "\n";

    os << "                   "<< ft0 <<' '<< ft1 <<' '<< ft0 <<' '
       << translationvector.y() << "\n";

    os << "                   "<< ft0 <<' '<< ft0 <<' '<< ft1 <<' '
       << translationvector.z() << ")\n";

    return os;
  }

private:
  CGAL_VectorC3<FT>   translationvector;
};

template < class FT >
class CGAL__Scaling_repC3: public CGAL__Aff_transformation_rep_baseC3<FT>
{
  friend ostream &operator<<(ostream &os, CGAL__Scaling_repC3<FT> &t);
  friend CGAL_Aff_transformationC3<FT> operator*
                                (const CGAL_Aff_transformationC3<FT> &a,
                                 const CGAL_Aff_transformationC3<FT> &b);

public:
  CGAL__Scaling_repC3()
  {}

  CGAL__Scaling_repC3(const FT &s) :
    scalefactor(s)
  {}

  ~CGAL__Scaling_repC3()
  {}

  CGAL_PointC3<FT>      transform(const CGAL_PointC3<FT> &p) const
  {
    return CGAL_PointC3<FT>(scalefactor * p.x(), scalefactor * p.y(),
                            scalefactor * p.z());
  }

  CGAL_VectorC3<FT>      transform(const CGAL_VectorC3<FT> &v) const
  {
    return CGAL_VectorC3<FT>(scalefactor * v.x(), scalefactor * v.y(),
                             scalefactor * v.z());
  }

  CGAL_DirectionC3<FT>  transform(const CGAL_DirectionC3<FT> &d) const
  {
    return d;
  }

  CGAL_Aff_transformationC3<FT> inverse() const
  {
    return CGAL_Aff_transformationC3<FT>(CGAL_SCALING, FT(1)/scalefactor);
  }

  CGAL_Aff_transformationC3<FT> general_form() const
  {
    FT ft0(0);

    return CGAL_Aff_transformationC3<FT>(scalefactor, ft0,        ft0,
                                         ft0,         scalefactor,ft0,
                                         ft0,         ft0,        scalefactor);
  }

  CGAL_Aff_transformationC3<FT> transpose() const
  {
    return general_form();
  }

  virtual bool                 is_even() const
  {
    return true;
  }

  virtual ostream &print(ostream &os) const
  {
    FT ft0(0);
    os << "                   "<< scalefactor <<' '<< ft0 <<' '<< ft0 << ' '
       << ft0 << "\n";
    os << "                   "<< ft0 <<' '<< scalefactor <<' '<< ft0 << ' '
       << ft0 << "\n";
    os << "                   "<< ft0 <<' '<<  ft0 <<' '<< scalefactor <<' '
       << ft0 << ")\n";

    return os;
  }

private:
  FT   scalefactor;
};


template < class FT >
class CGAL_Aff_transformationC3 : public CGAL_Handle
{
  friend   ostream &
    operator<< ( ostream &os, const CGAL_Aff_transformationC3<FT> &t);

  friend   CGAL_Aff_transformationC3<FT>
  CGAL__general_transformation_composition(
                                   CGAL__Aff_transformation_repC3<FT> &l,
                                   CGAL__Aff_transformation_repC3<FT> &r );
  friend CGAL_Aff_transformationC3<FT> operator*
                                (const CGAL_Aff_transformationC3<FT> &a,
                                 const CGAL_Aff_transformationC3<FT> &b);


public:
                       // default cosntructor:
                       CGAL_Aff_transformationC3();

                       // Translation:
                       CGAL_Aff_transformationC3(const CGAL_Translation,
                                                 const CGAL_VectorC3<FT> &v);

                       // Scaling:
                       CGAL_Aff_transformationC3(const CGAL_Scaling,
                                                 const FT &s,
                                                 const FT &w = FT(1));

                       // General form:
                       CGAL_Aff_transformationC3(const FT& m11, const FT& m12,
                                                 const FT& m13,
                                                 const FT& m21,
                                                 const FT& m22,
                                                 const FT& m23,
                                                 const FT& m31,
                                                 const FT& m32,
                                                 const FT& m33,
                                                 const FT& w= FT(1));

                       CGAL_Aff_transformationC3(const FT& m11, const FT& m12,
                                                 const FT& m13, const FT& m14,
                                                 const FT& m21, const FT& m22,
                                                 const FT& m23, const FT& m24,
                                                 const FT& m31, const FT& m32,
                                                 const FT& m33, const FT& m34,
                                                 const FT& w = FT(1));

                       ~CGAL_Aff_transformationC3();

  CGAL_PointC3<FT>     transform(const CGAL_PointC3<FT> &p) const;
  CGAL_PointC3<FT>     operator()(const CGAL_PointC3<FT> &p) const;

  CGAL_VectorC3<FT>    transform(const CGAL_VectorC3<FT> &v) const;
  CGAL_VectorC3<FT>    operator()(const CGAL_VectorC3<FT> &v) const;

  CGAL_DirectionC3<FT> transform(const CGAL_DirectionC3<FT> &d) const;
  CGAL_DirectionC3<FT> operator()(const CGAL_DirectionC3<FT> &d) const;


#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
  CGAL_PlaneC3<FT>     transform(const CGAL_PlaneC3<FT>& p) const;
  CGAL_PlaneC3<FT>     operator()(const CGAL_PlaneC3<FT>& p) const;
#endif //  CGAL_NO_PLANE_TRANSFORM_IN_AT

  CGAL_Aff_transformationC3<FT>  inverse() const;
  CGAL_Aff_transformationC3<FT>  transpose() const;
  CGAL_Aff_transformationC3<FT>  general_form() const;
  bool                 is_even() const;
  bool                 is_odd() const;

private:
  CGAL__Aff_transformation_rep_baseC3<FT>*   ptr() const
    {
      return  (CGAL__Aff_transformation_rep_baseC3<FT>*)PTR;
    }
};

template < class FT >
CGAL_Aff_transformationC3<FT>::CGAL_Aff_transformationC3()
{
  FT ft1(1), ft0(0);
  PTR = new CGAL__Aff_transformation_repC3<FT>(ft1, ft0, ft0,
                                               ft0, ft1, ft0,
                                               ft0, ft0, ft1);
}

template < class FT >
CGAL_Aff_transformationC3<FT>::CGAL_Aff_transformationC3(
                                               const CGAL_Translation,
                                               const CGAL_VectorC3<FT> &v)
{
  PTR = new CGAL__Translation_repC3<FT>(v);
}

template < class FT >
CGAL_Aff_transformationC3<FT>::CGAL_Aff_transformationC3(const CGAL_Scaling,
                                                         const FT &s,
                                                         const FT &w)
{
  if (w != FT(1)){
    PTR = new CGAL__Scaling_repC3<FT>(s/w);
  } else {
    PTR = new CGAL__Scaling_repC3<FT>(s);
  }
}


template < class FT >
CGAL_Aff_transformationC3<FT>::CGAL_Aff_transformationC3(
                                   const FT& m11, const FT& m12,
                                   const FT& m13, const FT& m14,
                                   const FT& m21, const FT& m22,
                                   const FT& m23, const FT& m24,
                                   const FT& m31, const FT& m32,
                                   const FT& m33, const FT& m34,
                                   const FT &w)
{
  if (w != FT(1)){
  PTR = new CGAL__Aff_transformation_repC3<FT>(m11/w, m12/w, m13/w, m14/w,
                                               m21/w, m22/w, m23/w, m24/w,
                                               m31/w, m32/w, m33/w, m34/w);
  } else {
    PTR = new CGAL__Aff_transformation_repC3<FT>(m11, m12, m13, m14,
                                                 m21, m22, m23, m24,
                                                 m31, m32, m33, m34);
  }
}

template < class FT >
CGAL_Aff_transformationC3<FT>::CGAL_Aff_transformationC3(
                                   const FT& m11, const FT& m12, const FT& m13,
                                   const FT& m21, const FT& m22, const FT& m23,
                                   const FT& m31, const FT& m32, const FT& m33,
                                   const FT &w)
{
  if (w != FT(1)){
  PTR = new CGAL__Aff_transformation_repC3<FT>(m11/w, m12/w, m13/w,
                                               m21/w, m22/w, m23/w,
                                               m31/w, m32/w, m33/w);
  } else {
    PTR = new CGAL__Aff_transformation_repC3<FT>(m11, m12, m13,
                                                 m21, m22, m23,
                                                 m31, m32, m33);
  }
}

template < class FT >
CGAL_Aff_transformationC3<FT>::~CGAL_Aff_transformationC3()
{}
template < class FT >
CGAL_PointC3<FT> CGAL_Aff_transformationC3<FT>::transform(
                                              const CGAL_PointC3<FT> &p) const
{
  return ptr()->transform(p);
}

template < class FT >
inline CGAL_PointC3<FT> CGAL_Aff_transformationC3<FT>::operator()(
                                              const CGAL_PointC3<FT> &p) const
{
  return transform(p);
}

template < class FT >
CGAL_VectorC3<FT> CGAL_Aff_transformationC3<FT>::transform(
                                              const CGAL_VectorC3<FT> &v) const
{
  return ptr()->transform(v);
}

template < class FT >
inline CGAL_VectorC3<FT> CGAL_Aff_transformationC3<FT>::operator()(
                                             const CGAL_VectorC3<FT> &v) const
{
  return transform(v);
}

template < class FT >
CGAL_DirectionC3<FT> CGAL_Aff_transformationC3<FT>::transform(
                                         const CGAL_DirectionC3<FT> &d) const
{
  return ptr()->transform(d);
}

template < class FT >
inline CGAL_DirectionC3<FT> CGAL_Aff_transformationC3<FT>::operator()(
                                           const CGAL_DirectionC3<FT>& d) const
{
  return transform(d);
}

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
template < class FT >
inline CGAL_PlaneC3<FT> CGAL_Aff_transformationC3<FT>::transform(
                                             const CGAL_PlaneC3<FT>& p) const
{
  return p.transform(*this);
}

template < class FT >
inline CGAL_PlaneC3<FT> CGAL_Aff_transformationC3<FT>::operator()(
                                             const CGAL_PlaneC3<FT>& p) const
{
  return transform(p);
}
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

template < class FT >
CGAL_Aff_transformationC3<FT> CGAL_Aff_transformationC3<FT>::inverse() const
{
  return ptr()->inverse();
}


template < class FT >
CGAL_Aff_transformationC3<FT>  CGAL_Aff_transformationC3<FT>::general_form()
                                                                    const
{
  return ptr()->general_form();
}

template < class FT >
CGAL_Aff_transformationC3<FT>  CGAL_Aff_transformationC3<FT>::transpose() const
{
  return ptr()->transpose();
}

template < class FT >
bool  CGAL_Aff_transformationC3<FT>::is_even() const
{
  return ptr()->is_even();
}

template < class FT >
bool  CGAL_Aff_transformationC3<FT>::is_odd() const
{
  return ! (ptr()->is_even());
}




template < class FT >
CGAL_Aff_transformationC3<FT> CGAL__general_transformation_composition(
                                      CGAL__Aff_transformation_repC3<FT> &l,
                                      CGAL__Aff_transformation_repC3<FT> &r )
{
return CGAL_Aff_transformationC3<FT>(
            l.t11*r.t11 + l.t12*r.t21 + l.t13*r.t31,
            l.t11*r.t12 + l.t12*r.t22 + l.t13*r.t32,
            l.t11*r.t13 + l.t12*r.t23 + l.t13*r.t33,
            l.t11*r.t14 + l.t12*r.t24 + l.t13*r.t34 + l.t14,

            l.t21*r.t11 + l.t22*r.t21 + l.t23*r.t31,
            l.t21*r.t12 + l.t22*r.t22 + l.t23*r.t32,
            l.t21*r.t13 + l.t22*r.t23 + l.t23*r.t33,
            l.t21*r.t14 + l.t22*r.t24 + l.t23*r.t34 + l.t24,

            l.t31*r.t11 + l.t32*r.t21 + l.t33*r.t31,
            l.t31*r.t12 + l.t32*r.t22 + l.t33*r.t32,
            l.t31*r.t13 + l.t32*r.t23 + l.t33*r.t33,
            l.t31*r.t14 + l.t32*r.t24 + l.t33*r.t34 + l.t34);

/*
return CGAL_Aff_transformationC3<FT>(
            l.t11*r.t11 + l.t12*r.t21 + l.t13*r.t31,
            l.t11*r.t12 + l.t12*r.t22 + l.t13*r.t32,
            l.t11*r.t13 + l.t12*r.t23 + l.t13*r.t33 + l.t14,

            l.t21*r.t11 + l.t22*r.t21 + l.t23*r.t31,
            l.t21*r.t12 + l.t22*r.t22 + l.t23*r.t32,
            l.t21*r.t13 + l.t22*r.t23 + l.t23*r.t33 + l.t24,

            l.t31*r.t11 + l.t32*r.t21 + l.t33*r.t31,
            l.t31*r.t12 + l.t32*r.t22 + l.t33*r.t32,
            l.t31*r.t13 + l.t32*r.t23 + l.t33*r.t33 + l.t34  );
*/
}


// this is really quick and dirty.  As in the 2D case the composition of
// translations or scalings should be a translation or a scaling
template < class FT >
CGAL_Aff_transformationC3<FT> operator*
                                (const CGAL_Aff_transformationC3<FT> &a,
                                 const CGAL_Aff_transformationC3<FT> &b)
{
  return CGAL__general_transformation_composition(
         *(CGAL__Aff_transformation_repC3<FT>*)(a.general_form().ptr()),
         *(CGAL__Aff_transformation_repC3<FT>*)(b.general_form().ptr()));
}



/*
template < class FT >
ostream &operator<<(ostream &os, const CGAL_Aff_transformationC3<FT> &t)
{
  return t.ptr()->print(os);
}
*/


#ifndef CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATIONC3
template < class FT >
ostream &operator<<(ostream &os, const CGAL_Aff_transformationC3<FT> &t)
{
    t.print(os);
    return os;
}
#endif // CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATIONC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATIONC3
#endif // CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATIONC3



#endif // CGAL_AFF_TRANSFORMATIONC3_H
