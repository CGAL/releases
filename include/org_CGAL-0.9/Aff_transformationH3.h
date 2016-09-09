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

// Source: Aff_transformationH3.h
// Author: Stefan Schirra

#ifndef CGAL_AFF_TRANSFORMATIONH3_H
#define CGAL_AFF_TRANSFORMATIONH3_H

#include <CGAL/determinant.h>

// #ifdef CGAL_WORKAROUND_015    line removed by Wieger
#define CGAL_NO_PLANE_TRANSFORM_IN_AT
// #endif // CGAL_WORKAROUND_015    line removed by Wieger

template <class FT, class RT>
class CGAL__Aff_transformation_repH3;

template <class FT, class RT>
class CGAL__Aff_transformation_rep_baseH3 : public CGAL_Rep
{
public:

    virtual                 ~CGAL__Aff_transformation_rep_baseH3(){}

    virtual  CGAL_PointH3<FT,RT>
                            transform(const CGAL_PointH3<FT,RT>&) const = 0;

    virtual  CGAL_VectorH3<FT,RT>
                            transform(const CGAL_VectorH3<FT,RT>&) const = 0;

    virtual  CGAL_DirectionH3<FT,RT>
                            transform(const CGAL_DirectionH3<FT,RT>&) const = 0;

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
    virtual  CGAL_PlaneH3<FT,RT>
                            transform(const CGAL_PlaneH3<FT,RT>&) const = 0;
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

    virtual  CGAL_Aff_transformationH3<FT,RT>
                            inverse() const = 0;

    virtual  CGAL_Aff_transformationH3<FT,RT>
                            transpose() const = 0;

    virtual  CGAL__Aff_transformation_repH3<FT,RT>
                            general_form() const = 0;

    virtual  bool           is_even() const = 0;

};
template < class FT, class RT >
class CGAL__Aff_transformation_repH3 :
                       public CGAL__Aff_transformation_rep_baseH3<FT,RT>
{

public:

                  CGAL__Aff_transformation_repH3();

                  CGAL__Aff_transformation_repH3(
                    const RT& m00, const RT& m01, const RT& m02, const RT& m03,
                    const RT& m10, const RT& m11, const RT& m12, const RT& m13,
                    const RT& m20, const RT& m21, const RT& m22, const RT& m23,
                                                                 const RT& m33);

  virtual       ~CGAL__Aff_transformation_repH3();

  virtual   CGAL_PointH3<FT,RT>
                transform(const CGAL_PointH3<FT,RT>& p) const;

  virtual   CGAL_VectorH3<FT,RT>
                transform(const CGAL_VectorH3<FT,RT>& v) const;

  virtual   CGAL_DirectionH3<FT,RT>
                transform(const CGAL_DirectionH3<FT,RT>& dir) const;

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
  virtual   CGAL_PlaneH3<FT,RT>
                transform(const CGAL_PlaneH3<FT,RT>& pl) const;
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

  virtual   CGAL_Aff_transformationH3<FT,RT>
                inverse() const;

  virtual   CGAL__Aff_transformation_repH3<FT,RT>
                general_form() const;

  virtual   CGAL_Aff_transformationH3<FT,RT>
                transpose() const;

  virtual   bool  is_even() const;

  friend class CGAL_Aff_transformationH3<FT,RT>;

  friend   CGAL_Aff_transformationH3<FT,RT>
    CGAL__general_transformation_composition(
                          CGAL__Aff_transformation_repH3<FT,RT> l,
                          CGAL__Aff_transformation_repH3<FT,RT> r );

  friend   ostream &
    operator<< ( ostream & out, const CGAL_Aff_transformationH3<FT,RT>& t);

private:

    RT   t11, t12, t13, t14;
    RT   t21, t22, t23, t24;
    RT   t31, t32, t33, t34;
    RT                  t44;
};
template < class FT, class RT >
class
CGAL__Translation_repH3 : public CGAL__Aff_transformation_rep_baseH3<FT,RT>
{

public:
            CGAL__Translation_repH3();

            CGAL__Translation_repH3( const CGAL_VectorH3<FT,RT>& v);

            ~CGAL__Translation_repH3();

  virtual   CGAL_PointH3<FT,RT>
                transform(const CGAL_PointH3<FT,RT>& p) const;

  virtual   CGAL_VectorH3<FT,RT>
                transform(const CGAL_VectorH3<FT,RT>& v) const;

  virtual   CGAL_DirectionH3<FT,RT>
                transform(const CGAL_DirectionH3<FT,RT>& dir) const;

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
  virtual   CGAL_PlaneH3<FT,RT>
                transform(const CGAL_PlaneH3<FT,RT>& pl) const;
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

  virtual   CGAL_Aff_transformationH3<FT,RT>
                inverse() const;

  virtual   CGAL__Aff_transformation_repH3<FT,RT>
                general_form() const;

  virtual   CGAL_Aff_transformationH3<FT,RT>
                transpose() const;

  virtual   bool  is_even() const;

 friend class CGAL_Aff_transformationH3<FT,RT>;

private:
    CGAL_VectorH3<FT,RT>   tv;
};

template < class FT, class RT >
class CGAL_Aff_transformationH3 : public CGAL_Handle
{
public:
          CGAL_Aff_transformationH3();

          CGAL_Aff_transformationH3(
                                  const CGAL_Aff_transformationH3<FT,RT>& tbc);

          // Translation

          CGAL_Aff_transformationH3(const CGAL_Translation& ,
                                    const CGAL_VectorH3<FT,RT>& v);

          //  Scaling

          CGAL_Aff_transformationH3(const CGAL_Scaling&,
                                    const RT& num, const RT& den);

          //  General form

          CGAL_Aff_transformationH3(
                  const RT& m00, const RT& m01, const RT& m02, const RT& m03,
                  const RT& m10, const RT& m11, const RT& m12, const RT& m13,
                  const RT& m20, const RT& m21, const RT& m22, const RT& m23,
                                                               const RT& m33);

          CGAL_Aff_transformationH3(
                  const RT& m00, const RT& m01, const RT& m02,
                  const RT& m10, const RT& m11, const RT& m12,
                  const RT& m20, const RT& m21, const RT& m22,
                                                               const RT& m33);

#ifdef CGAL_WORKAROUND_008
          CGAL_Aff_transformationH3(
                                CGAL__Aff_transformation_repH3<FT,RT>* ptr);
#endif // CGAL_WORKAROUND_008


          ~CGAL_Aff_transformationH3();


    CGAL_PointH3<FT,RT>
          transform(const CGAL_PointH3<FT,RT>& p) const;
    CGAL_VectorH3<FT,RT>
          transform(const CGAL_VectorH3<FT,RT>& v) const;
    CGAL_DirectionH3<FT,RT>
          transform(const CGAL_DirectionH3<FT,RT>& d) const;
#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
    CGAL_PlaneH3<FT,RT>
          transform(const CGAL_PlaneH3<FT,RT>& pl) const;
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT
    CGAL_Aff_transformationH3<FT,RT>
          inverse()   const;
    CGAL_Aff_transformationH3<FT,RT>
          transpose() const;
    bool  is_even()   const;
    bool  is_odd()    const;

    CGAL__Aff_transformation_rep_baseH3<FT,RT>*   ptr() const;

};

template < class FT, class RT >
CGAL__Aff_transformation_repH3<FT,RT>::CGAL__Aff_transformation_repH3()
{
}

template < class FT, class RT >
CGAL__Aff_transformation_repH3<FT,RT>::CGAL__Aff_transformation_repH3(
                   const RT& m00, const RT& m01, const RT& m02, const RT& m03,
                   const RT& m10, const RT& m11, const RT& m12, const RT& m13,
                   const RT& m20, const RT& m21, const RT& m22, const RT& m23,
                                                                const RT& m33)
  :  t11(m00), t12(m01), t13(m02), t14(m03),
     t21(m10), t22(m11), t23(m12), t24(m13),
     t31(m20), t32(m21), t33(m22), t34(m23),
                                   t44(m33)
{
}

template < class FT, class RT >
CGAL__Aff_transformation_repH3<FT,RT>::~CGAL__Aff_transformation_repH3()
{
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::transform(const CGAL_PointH3<FT,RT>& p)
                                                                          const
{
 return
  CGAL_PointH3<FT,RT>(t11 * p.hx() + t12 * p.hy() + t13 * p.hz() + t14 * p.hw(),
                      t21 * p.hx() + t22 * p.hy() + t23 * p.hz() + t24 * p.hw(),
                      t31 * p.hx() + t32 * p.hy() + t33 * p.hz() + t34 * p.hw(),
                                                                   t44 * p.hw()
                     );
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::transform(const CGAL_VectorH3<FT,RT>& v)
                                                                          const
{
  return
   CGAL_VectorH3<FT,RT>(t11 * v.hx() + t12 * v.hy() + t13 * v.hz(),
                        t21 * v.hx() + t22 * v.hy() + t23 * v.hz(),
                        t31 * v.hx() + t32 * v.hy() + t33 * v.hz(),
                                                      t44 * v.hw() );
}

template < class FT, class RT >
CGAL_DirectionH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::
                            transform(const CGAL_DirectionH3<FT,RT>& dir) const
{
 CGAL_VectorH3<FT,RT> v = dir.vector();
 return CGAL_DirectionH3<FT,RT>( t11 * v.hx() + t12 * v.hy() + t13 * v.hz(),
                                 t21 * v.hx() + t22 * v.hy() + t23 * v.hz(),
                                 t31 * v.hx() + t32 * v.hy() + t33 * v.hz(),
                                                               t44 * v.hw() );
}

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
template < class FT, class RT >
CGAL_PlaneH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::transform(const CGAL_PlaneH3<FT,RT>& pl)
                                                                          const
{
 if ( is_even() )
 {
    return CGAL_PlaneH3<FT,RT>(
              transform(pl.point() ),
              transpose().inverse().transform(pl.orthogonal_direction() ));
 }
 else
 {
    return CGAL_PlaneH3<FT,RT>(
              transform(pl.point() ),
            - transpose().inverse().transform(pl.orthogonal_direction() ));
 }
}
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::inverse() const
{
 RT  RT0(0);
 return CGAL_Aff_transformationH3<FT,RT>(
                           CGAL_det3x3_by_formula( t22, t23, t24,
                                                   t32, t33, t34,     // i 11
                                                   RT0, RT0, t44 ),

                        -  CGAL_det3x3_by_formula( t12, t13, t14,
                                                   t32, t33, t34,     // i 12
                                                   RT0, RT0, t44 ),

                           CGAL_det3x3_by_formula( t12, t13, t14,
                                                   t22, t23, t24,     // i 13
                                                   RT0, RT0, t44 ),

                        -  CGAL_det3x3_by_formula( t12, t13, t14,
                                                   t22, t23, t24,     // i 14
                                                   t32, t33, t34 ),

                        -  CGAL_det3x3_by_formula( t21, t23, t24,
                                                   t31, t33, t34,     // i 21
                                                   RT0, RT0, t44 ),

                           CGAL_det3x3_by_formula( t11, t13, t14,
                                                   t31, t33, t34,     // i 22
                                                   RT0, RT0, t44 ),

                        -  CGAL_det3x3_by_formula( t11, t13, t14,
                                                   t21, t23, t24,     // i 23
                                                   RT0, RT0, t44 ),

                           CGAL_det3x3_by_formula( t11, t13, t14,
                                                   t21, t23, t24,     // i 24
                                                   t31, t33, t34 ),

                           CGAL_det3x3_by_formula( t21, t22, t24,
                                                   t31, t32, t34,     // i 31
                                                   RT0, RT0, t44 ),

                        -  CGAL_det3x3_by_formula( t11, t12, t14,
                                                   t31, t32, t34,     // i 32
                                                   RT0, RT0, t44 ),

                           CGAL_det3x3_by_formula( t11, t12, t14,
                                                   t21, t22, t24,     // i 33
                                                   RT0, RT0, t44 ),

                        -  CGAL_det3x3_by_formula( t11, t12, t14,
                                                   t21, t22, t24,     // i 34
                                                   t31, t32, t34 ),

                           CGAL_det3x3_by_formula( t11, t12, t13,
                                                   t21, t22, t23,     // i 44
                                                   t31, t32, t33 )
                                                       ) ;
}

template <class FT, class RT>
CGAL__Aff_transformation_repH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::general_form() const
{
 return *this;
}

template <class FT, class RT>
CGAL_Aff_transformationH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::transpose() const
{
   RT  RT0(0);
   return CGAL_Aff_transformationH3<FT,RT>( t11,    t21,    t31,    RT0,
                                            t12,    t22,    t32,    RT0,
                                            t13,    t23,    t33,    RT0,
                                                                    t44);
}

template <class FT, class RT>
bool
CGAL__Aff_transformation_repH3<FT,RT>::is_even() const
{
  return (CGAL_sign( t44 * CGAL_det3x3_by_formula(t11, t12, t13,
                                                  t21, t22, t23,
                                                  t31, t32, t33 ) ) == 1 );
}
template < class FT, class RT >
CGAL__Translation_repH3<FT,RT>::CGAL__Translation_repH3()
{}

template < class FT, class RT >
CGAL__Translation_repH3<FT,RT>::
                        CGAL__Translation_repH3( const CGAL_VectorH3<FT,RT>& v)
 : tv(v)
{}

template < class FT, class RT >
CGAL__Translation_repH3<FT,RT>::~CGAL__Translation_repH3()
{}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::transform(const CGAL_PointH3<FT,RT>& p) const
{
 return CGAL_PointH3<FT,RT>( tv.hw() * p.hx() + tv.hx() * p.hw(),
                             tv.hw() * p.hy() + tv.hy() * p.hw(),
                             tv.hw() * p.hz() + tv.hz() * p.hw(),
                             tv.hw() * p.hw() );
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::transform(const CGAL_VectorH3<FT,RT>& v) const
{
 return v;
}

template < class FT, class RT >
CGAL_DirectionH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::transform(const CGAL_DirectionH3<FT,RT>& dir)
                                                                         const
{
 return dir;
}

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
template < class FT, class RT >
CGAL_PlaneH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::transform(const CGAL_PlaneH3<FT,RT>& pl) const
{
  return CGAL_PlaneH3<FT,RT>( transform( pl.point() ),
                              transform( pl.orthogonal_vector() ) );
}
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::inverse() const
{
 return CGAL_Aff_transformationH3<FT,RT>(CGAL_TRANSLATION,  - tv );
}

template < class FT, class RT >
CGAL__Aff_transformation_repH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::general_form() const
{
 RT  RT0(0);
 return CGAL__Aff_transformation_repH3<FT,RT>(tv.hw(), RT0,  RT0,  tv.hx(),
                                              RT0,  tv.hw(), RT0,  tv.hy(),
                                              RT0,  RT0,  tv.hw(), tv.hz(),
                                                                   tv.hw() );
}

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::transpose() const
{
 RT  RT0(0);
 RT  RT1(1);
 return CGAL_Aff_transformationH3<FT,RT>( RT1,  RT0,  RT0,  RT0,
                                          RT0,  RT1,  RT0,  RT0,
                                          RT0,  RT0,  RT1,  RT0,
                                                            RT1 );
}

template < class FT, class RT >
bool
CGAL__Translation_repH3<FT,RT>::is_even() const
{
 return true;
}

template <class FT, class RT>
CGAL_Aff_transformationH3<FT,RT>
CGAL__general_transformation_composition(
        CGAL__Aff_transformation_repH3<FT,RT> l,
        CGAL__Aff_transformation_repH3<FT,RT> r )
{
 return CGAL_Aff_transformationH3<FT,RT>(
            l.t11*r.t11 + l.t12*r.t21 + l.t13*r.t31,
            l.t11*r.t12 + l.t12*r.t22 + l.t13*r.t32,
            l.t11*r.t13 + l.t12*r.t23 + l.t13*r.t33,
            l.t11*r.t14 + l.t12*r.t24 + l.t13*r.t34 + l.t14*r.t44,

            l.t21*r.t11 + l.t22*r.t21 + l.t23*r.t31,
            l.t21*r.t12 + l.t22*r.t22 + l.t23*r.t32,
            l.t21*r.t13 + l.t22*r.t23 + l.t23*r.t33,
            l.t21*r.t14 + l.t22*r.t24 + l.t23*r.t34 + l.t24*r.t44,

            l.t31*r.t11 + l.t32*r.t21 + l.t33*r.t31,
            l.t31*r.t12 + l.t32*r.t22 + l.t33*r.t32,
            l.t31*r.t13 + l.t32*r.t23 + l.t33*r.t33,
            l.t31*r.t14 + l.t32*r.t24 + l.t33*r.t34 + l.t34*r.t44,

            l.t44*r.t44 );
}

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>::CGAL_Aff_transformationH3()
{
 PTR = new CGAL__Aff_transformation_repH3<FT,RT>();
}

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>::CGAL_Aff_transformationH3(
                                    const CGAL_Aff_transformationH3<FT,RT>& tbc)
 : CGAL_Handle(tbc)
{}

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>::CGAL_Aff_transformationH3(
                                              const CGAL_Translation&,
                                              const CGAL_VectorH3<FT,RT>& v)
{
 PTR = new CGAL__Translation_repH3<FT,RT>( v );
}

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>::CGAL_Aff_transformationH3(const CGAL_Scaling&,
                                                            const RT& num,
                                                            const RT& den)
{
 RT RT0 = 0;
 PTR = new CGAL__Aff_transformation_repH3<FT,RT>(num, RT0, RT0, RT0,
                                                 RT0, num, RT0, RT0,
                                                 RT0, RT0, num, RT0,
                                                                den );
}

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>::CGAL_Aff_transformationH3(
                  const RT& m00, const RT& m01, const RT& m02, const RT& m03,
                  const RT& m10, const RT& m11, const RT& m12, const RT& m13,
                  const RT& m20, const RT& m21, const RT& m22, const RT& m23,
                                                               const RT& m33)
{
 PTR = new CGAL__Aff_transformation_repH3<FT,RT>(m00, m01, m02, m03,
                                                 m10, m11, m12, m13,
                                                 m20, m21, m22, m23,
                                                                m33 );
}

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>::CGAL_Aff_transformationH3(
                  const RT& m00, const RT& m01, const RT& m02,
                  const RT& m10, const RT& m11, const RT& m12,
                  const RT& m20, const RT& m21, const RT& m22,
                                                               const RT& m33)
{
 const RT RT0 = RT(0);
 PTR = new CGAL__Aff_transformation_repH3<FT,RT>(m00, m01, m02, RT0,
                                                 m10, m11, m12, RT0,
                                                 m20, m21, m22, RT0,
                                                                m33 );
}

template < class FT, class RT >
CGAL__Aff_transformation_rep_baseH3<FT,RT>*
CGAL_Aff_transformationH3<FT,RT>::ptr() const
{
 return (CGAL__Aff_transformation_rep_baseH3<FT,RT>*)PTR;
}

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>::~CGAL_Aff_transformationH3()
{}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::transform(const CGAL_PointH3<FT,RT>& p) const
{
 return ptr()->transform(p);
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::transform(const CGAL_VectorH3<FT,RT>& v) const
{
 return ptr()->transform(v);
}

template < class FT, class RT >
CGAL_DirectionH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::transform(const CGAL_DirectionH3<FT,RT>& d)
                                                                          const
{
 return ptr()->transform(d);
}

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
template < class FT, class RT >
CGAL_PlaneH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::transform(const CGAL_PlaneH3<FT,RT>& p) const
{
 return p.transform(*this);
}
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::inverse() const
{
 return ptr()->inverse();
}

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::transpose() const
{
 return ptr()->transpose();
}

template < class FT, class RT >
bool
CGAL_Aff_transformationH3<FT,RT>::is_even() const
{
 return ptr()->is_even();
}

template < class FT, class RT >
bool
CGAL_Aff_transformationH3<FT,RT>::is_odd() const
{
 return ( ! (ptr()->is_even() ));
}

template <class FT, class RT>
CGAL_Aff_transformationH3<FT,RT>
operator*(const CGAL_Aff_transformationH3<FT,RT>& left_argument,
          const CGAL_Aff_transformationH3<FT,RT>& right_argument )
{
 return CGAL__general_transformation_composition(
              left_argument.ptr() ->general_form(),
              right_argument.ptr()->general_form() );
}


template <class FT, class RT>
ostream &
operator<< ( ostream & out,
             const CGAL_Aff_transformationH3<FT,RT>& t)
{
 RT RT0(0);
 CGAL__Aff_transformation_repH3<FT,RT> r = t.ptr()->general_form();
 return  out
 << "| "<< r.t11 <<' '<< r.t12 <<' '<< r.t13 <<' '<< r.t14 << " |\n"
 << "| "<< r.t21 <<' '<< r.t22 <<' '<< r.t23 <<' '<< r.t24 << " |\n"
 << "| "<< r.t31 <<' '<< r.t32 <<' '<< r.t33 <<' '<< r.t34 << " |\n"
 << "| "<< RT0   <<' '<< RT0   <<' '<< RT0   <<' '<< r.t44 << " |\n";
}



#endif // CGAL_AFF_TRANSFORMATIONH3_H
