// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : Aff_transformationH3.fw
// file          : include/CGAL/Aff_transformationH3.h
// package       : H3 (1.3.1)
// revision      : 1.3.1
// revision_date : 30 Jun 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_AFF_TRANSFORMATIONH3_H
#define CGAL_AFF_TRANSFORMATIONH3_H

#if defined(CGAL_CFG_INCOMPLETE_TYPE_BUG_1) && \
   !defined(CGAL_NO_PLANE_TRANSFORM_IN_AT)
#define CGAL_NO_PLANE_TRANSFORM_IN_AT
#endif // CGAL_CFG_INCOMPLETE_TYPE_BUG_1

#ifndef CGAL_DETERMINANT_H
#include <CGAL/determinant.h>
#endif // CGAL_DETERMINANT_H

// forward declaration
template < class FT, class RT >
class CGAL__Aff_transformationH3;

template < class FT, class RT >
class CGAL__Aff_transformation_repH3;

template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>
CGAL__general_transformation_composition (
                           CGAL__Aff_transformation_repH3<FT,RT> l,
                           CGAL__Aff_transformation_repH3<FT,RT> r
                                         );

template <class _FT, class _RT >
class CGAL__Aff_transformation_rep_baseH3 : public CGAL_Rep
// abstract base class of aff transformation representations
{
public:
  typedef _FT           FT;
  typedef _RT           RT;

  virtual  ~CGAL__Aff_transformation_rep_baseH3(){}

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
  virtual  bool         is_even() const = 0;
  virtual  RT           homogeneous(int i, int j) const = 0;
  virtual  FT           cartesian(int i, int j) const = 0;
};

template < class _FT, class _RT >
class CGAL__Aff_transformation_repH3 :
  public CGAL__Aff_transformation_rep_baseH3<_FT,_RT>
{
public:
  typedef _FT           FT;
  typedef _RT           RT;

  CGAL__Aff_transformation_repH3();
  CGAL__Aff_transformation_repH3(
                    const RT& m00, const RT& m01, const RT& m02, const RT& m03,
                    const RT& m10, const RT& m11, const RT& m12, const RT& m13,
                    const RT& m20, const RT& m21, const RT& m22, const RT& m23,
                                                                 const RT& m33);
  virtual  ~CGAL__Aff_transformation_repH3() {}

  virtual  CGAL_PointH3<FT,RT>
                       transform(const CGAL_PointH3<FT,RT>& p) const;
  virtual  CGAL_VectorH3<FT,RT>
                       transform(const CGAL_VectorH3<FT,RT>& v) const;
  virtual  CGAL_DirectionH3<FT,RT>
                       transform(const CGAL_DirectionH3<FT,RT>& dir) const;
#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
  virtual  CGAL_PlaneH3<FT,RT>
                       transform(const CGAL_PlaneH3<FT,RT>& pl) const;
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT
  virtual  CGAL_Aff_transformationH3<FT,RT>
                       inverse() const;
  virtual  CGAL__Aff_transformation_repH3<FT,RT>
                       general_form() const;
  virtual  CGAL_Aff_transformationH3<FT,RT>
                       transpose() const;
  virtual  bool        is_even() const;
  virtual  RT          homogeneous(int i, int j) const ;
  virtual  FT          cartesian(int i, int j) const ;

friend class CGAL_Aff_transformationH3<FT,RT>;

friend
CGAL_Aff_transformationH3<FT,RT>
CGAL__general_transformation_composition CGAL_NULL_TMPL_ARGS (
                           CGAL__Aff_transformation_repH3<FT,RT> l,
                           CGAL__Aff_transformation_repH3<FT,RT> r
                                                             );

friend
ostream &
operator<< CGAL_NULL_TMPL_ARGS (ostream & out,
                                const CGAL_Aff_transformationH3<FT,RT>& t);

private:
    RT   t00, t01, t02, t03;
    RT   t10, t11, t12, t13;
    RT   t20, t21, t22, t23;
    RT                  t33;
};

template < class _FT, class _RT >
class CGAL__Translation_repH3 :
  public CGAL__Aff_transformation_rep_baseH3<_FT,_RT>
{
public:
  typedef _FT           FT;
  typedef _RT           RT;

  CGAL__Translation_repH3();
  CGAL__Translation_repH3( const CGAL_VectorH3<FT,RT>& v);
  virtual  ~CGAL__Translation_repH3() {}

  virtual  CGAL_PointH3<FT,RT>
                        transform(const CGAL_PointH3<FT,RT>& p) const;
  virtual  CGAL_VectorH3<FT,RT>
                        transform(const CGAL_VectorH3<FT,RT>& v) const;
  virtual  CGAL_DirectionH3<FT,RT>
                        transform(const CGAL_DirectionH3<FT,RT>& dir) const;
#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
  virtual  CGAL_PlaneH3<FT,RT>
                        transform(const CGAL_PlaneH3<FT,RT>& pl) const;
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT
  virtual  CGAL_Aff_transformationH3<FT,RT>
                        inverse() const;
  virtual  CGAL__Aff_transformation_repH3<FT,RT>
                        general_form() const;
  virtual  CGAL_Aff_transformationH3<FT,RT>
                        transpose() const;
  virtual  bool         is_even() const;
  virtual  RT           homogeneous(int i, int j) const ;
  virtual  FT           cartesian(int i, int j) const ;

friend class CGAL_Aff_transformationH3<FT,RT>;

private:
  CGAL_VectorH3<FT,RT>  tv;
};


template < class _FT, class _RT >
class CGAL_Aff_transformationH3 : public CGAL_Handle
{
public:
  typedef _FT           FT;
  typedef _RT           RT;

  CGAL_Aff_transformationH3();
  CGAL_Aff_transformationH3(const CGAL_Aff_transformationH3<FT,RT>& tbc);
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
#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_1
  CGAL_Aff_transformationH3(CGAL__Aff_transformation_repH3<FT,RT>* ptr);
#endif // CGAL_CFG_INCOMPLETE_TYPE_BUG_1
  ~CGAL_Aff_transformationH3();


  CGAL_PointH3<FT,RT>   transform(const CGAL_PointH3<FT,RT>& p) const;
  CGAL_VectorH3<FT,RT>  transform(const CGAL_VectorH3<FT,RT>& v) const;
  CGAL_DirectionH3<FT,RT>
                        transform(const CGAL_DirectionH3<FT,RT>& d) const;
#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
    CGAL_PlaneH3<FT,RT> transform(const CGAL_PlaneH3<FT,RT>& pl) const;
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT
    CGAL_Aff_transformationH3<FT,RT>
                        inverse()   const;
    CGAL_Aff_transformationH3<FT,RT>
                        transpose() const;
    bool                is_even()   const;
    bool                is_odd()    const;
    FT                  cartesian(int i, int j) const
                        { return ptr()->cartesian(i,j); }
    RT                  homogeneous(int i, int j) const
                        { return ptr()->homogeneous(i,j); }
    FT                  m(int i, int j) const
                        { return ptr()->cartesian(i,j); }
    RT                  hm(int i, int j) const
                        { return ptr()->homogeneous(i,j); }

// protected:
    CGAL__Aff_transformation_rep_baseH3<FT,RT>*   ptr() const;
};


template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL__Aff_transformation_repH3<FT,RT>::CGAL__Aff_transformation_repH3()
#ifdef CGAL_INITIALIZE_AFF_TRANSFORMATIONS
  :  t00(RT(1)), t01(RT(0)), t02(RT(0)), t03(RT(0)),
     t10(RT(0)), t11(RT(1)), t12(RT(0)), t13(RT(0)),
     t20(RT(0)), t21(RT(0)), t22(RT(1)), t23(RT(0)),
                                         t33(RT(1))
#endif // CGAL_INITIALIZE_AFF_TRANSFORMATIONS
{}



template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL__Aff_transformation_repH3<FT,RT>::
CGAL__Aff_transformation_repH3(
                   const RT& m00, const RT& m01, const RT& m02, const RT& m03,
                   const RT& m10, const RT& m11, const RT& m12, const RT& m13,
                   const RT& m20, const RT& m21, const RT& m22, const RT& m23,
                                                                const RT& m33)
  :  t00(m00), t01(m01), t02(m02), t03(m03),
     t10(m10), t11(m11), t12(m12), t13(m13),
     t20(m20), t21(m21), t22(m22), t23(m23),
                                   t33(m33)
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::
transform(const CGAL_PointH3<FT,RT>& p) const
{
  return
  CGAL_PointH3<FT,RT>(t00 * p.hx() + t01 * p.hy() + t02 * p.hz() + t03 * p.hw(),
                      t10 * p.hx() + t11 * p.hy() + t12 * p.hz() + t13 * p.hw(),
                      t20 * p.hx() + t21 * p.hy() + t22 * p.hz() + t23 * p.hw(),
                                                                   t33 * p.hw()
                     );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_VectorH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::
transform(const CGAL_VectorH3<FT,RT>& v) const
{
  return
  CGAL_VectorH3<FT,RT>(t00 * v.hx() + t01 * v.hy() + t02 * v.hz(),
                       t10 * v.hx() + t11 * v.hy() + t12 * v.hz(),
                       t20 * v.hx() + t21 * v.hy() + t22 * v.hz(),
                                                     t33 * v.hw() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_DirectionH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::
transform(const CGAL_DirectionH3<FT,RT>& dir) const
{
  CGAL_VectorH3<FT,RT> v( dir.vector() );
  return CGAL_DirectionH3<FT,RT>( t00 * v.hx() + t01 * v.hy() + t02 * v.hz(),
                                  t10 * v.hx() + t11 * v.hy() + t12 * v.hz(),
                                  t20 * v.hx() + t21 * v.hy() + t22 * v.hz(),
                                                                t33 * v.hw() );
}

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PlaneH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::
transform(const CGAL_PlaneH3<FT,RT>& pl) const
{
  if ( is_even() )
  {
      return
        CGAL_PlaneH3<FT,RT>(
               transform(pl.point() ),
               transpose().inverse().transform(pl.orthogonal_direction() )
                           );
  }
  else
  {
     return
       CGAL_PlaneH3<FT,RT>(
               transform(pl.point() ),
               -(transpose().inverse().transform(pl.orthogonal_direction() ))
                          );
  }
}
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_Aff_transformationH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::inverse() const
{
  const RT  RT0(0);
  return CGAL_Aff_transformationH3<FT,RT>(
                           CGAL_det3x3_by_formula( t11, t12, t13,
                                                   t21, t22, t23,     // i 00
                                                   RT0, RT0, t33 ),

                        -  CGAL_det3x3_by_formula( t01, t02, t03,
                                                   t21, t22, t23,     // i 01
                                                   RT0, RT0, t33 ),

                           CGAL_det3x3_by_formula( t01, t02, t03,
                                                   t11, t12, t13,     // i 02
                                                   RT0, RT0, t33 ),

                        -  CGAL_det3x3_by_formula( t01, t02, t03,
                                                   t11, t12, t13,     // i 03
                                                   t21, t22, t23 ),


                        -  CGAL_det3x3_by_formula( t10, t12, t13,
                                                   t20, t22, t23,     // i 10
                                                   RT0, RT0, t33 ),

                           CGAL_det3x3_by_formula( t00, t02, t03,
                                                   t20, t22, t23,     // i 11
                                                   RT0, RT0, t33 ),

                        -  CGAL_det3x3_by_formula( t00, t02, t03,
                                                   t10, t12, t13,     // i 12
                                                   RT0, RT0, t33 ),

                           CGAL_det3x3_by_formula( t00, t02, t03,
                                                   t10, t12, t13,     // i 13
                                                   t20, t22, t23 ),


                           CGAL_det3x3_by_formula( t10, t11, t13,
                                                   t20, t21, t23,     // i 20
                                                   RT0, RT0, t33 ),

                        -  CGAL_det3x3_by_formula( t00, t01, t03,
                                                   t20, t21, t23,     // i 21
                                                   RT0, RT0, t33 ),

                           CGAL_det3x3_by_formula( t00, t01, t03,
                                                   t10, t11, t13,     // i 22
                                                   RT0, RT0, t33 ),

                        -  CGAL_det3x3_by_formula( t00, t01, t03,
                                                   t10, t11, t13,     // i 23
                                                   t20, t21, t23 ),


                           CGAL_det3x3_by_formula( t00, t01, t02,
                                                   t10, t11, t12,     // i 33
                                                   t20, t21, t22 )
                                                       ) ;
}

template < class FT, class RT >
inline
CGAL__Aff_transformation_repH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::general_form() const
{ return *this; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_Aff_transformationH3<FT,RT>
CGAL__Aff_transformation_repH3<FT,RT>::transpose() const
{
  const RT  RT0(0);
  return CGAL_Aff_transformationH3<FT,RT>( t00,    t10,    t20,    RT0,
                                           t01,    t11,    t21,    RT0,
                                           t02,    t12,    t22,    RT0,
                                                                   t33);
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL__Aff_transformation_repH3<FT,RT>::is_even() const
{
  return (CGAL_sign( t33 * CGAL_det3x3_by_formula(t00, t01, t02,
                                                  t10, t11, t12,
                                                  t20, t21, t22 ) ) == 1 );
}

template < class FT, class RT >
CGAL_KERNEL_LARGE_INLINE
RT
CGAL__Aff_transformation_repH3<FT,RT>::
homogeneous(int i, int j) const
{
  CGAL_kernel_precondition( (i >= 0) && (i <= 3) && (j >= 0) && (j <= 3) );
  const RT  RT0(0);
  switch (i)
  {
    case 0: switch (j)
            {
              case 0: return t00;
              case 1: return t01;
              case 2: return t02;
              case 3: return t03;
            }
    case 1: switch (j)
            {
              case 0: return t10;
              case 1: return t11;
              case 2: return t12;
              case 3: return t13;
            }
    case 2: switch (j)
            {
              case 0: return t20;
              case 1: return t21;
              case 2: return t22;
              case 3: return t23;
            }
    case 3: switch (j)
            {
              case 0: return RT0;
              case 1: return RT0;
              case 2: return RT0;
              case 3: return t33;
            }
  }
  return RT0;
}

template < class FT, class RT >
inline
FT
CGAL__Aff_transformation_repH3<FT,RT>::
cartesian(int i, int j) const
{
  return  FT(homogeneous(i,j)) / FT(t33);
}
// not used (default ctor in CGAL_Aff_transformationH3
// calls default ctor of CGAL__Aff_transformation_repH3 )
template < class FT, class RT >
inline
CGAL__Translation_repH3<FT,RT>::CGAL__Translation_repH3()
#ifdef CGAL_INITIALIZE_AFF_TRANSFORMATIONS
  : tv( CGAL_VectorH3<FT,RT>( RT(0), RT(0) ))
#endif // CGAL_INITIALIZE_AFF_TRANSFORMATIONS
{}

template < class FT, class RT >
inline
CGAL__Translation_repH3<FT,RT>::
CGAL__Translation_repH3( const CGAL_VectorH3<FT,RT>& v) : tv(v)
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::transform(const CGAL_PointH3<FT,RT>& p) const
{
  return CGAL_PointH3<FT,RT>( tv.hw() * p.hx() + tv.hx() * p.hw(),
                              tv.hw() * p.hy() + tv.hy() * p.hw(),
                              tv.hw() * p.hz() + tv.hz() * p.hw(),
                              tv.hw() * p.hw() );
}

template < class FT, class RT >
inline
CGAL_VectorH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::
transform(const CGAL_VectorH3<FT,RT>& v) const
{ return v; }

template < class FT, class RT >
inline
CGAL_DirectionH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::
transform(const CGAL_DirectionH3<FT,RT>& dir) const
{ return dir; }

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
template < class FT, class RT >
inline
CGAL_PlaneH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::
transform(const CGAL_PlaneH3<FT,RT>& pl) const
{
  return CGAL_PlaneH3<FT,RT>( transform( pl.point() ),
                              pl.orthogonal_vector()  );
}
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

template < class FT, class RT >
inline
CGAL_Aff_transformationH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::inverse() const
{ return CGAL_Aff_transformationH3<FT,RT>(CGAL_TRANSLATION,  - tv ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL__Aff_transformation_repH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::general_form() const
{
  const RT  RT0(0);
  return CGAL__Aff_transformation_repH3<FT,RT>(tv.hw(), RT0,  RT0,  tv.hx(),
                                               RT0,  tv.hw(), RT0,  tv.hy(),
                                               RT0,  RT0,  tv.hw(), tv.hz(),
                                                                    tv.hw() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_Aff_transformationH3<FT,RT>
CGAL__Translation_repH3<FT,RT>::transpose() const
{
 const RT  RT0(0);
 const RT  RT1(1);
 return CGAL_Aff_transformationH3<FT,RT>( RT1,  RT0,  RT0,  RT0,
                                          RT0,  RT1,  RT0,  RT0,
                                          RT0,  RT0,  RT1,  RT0,
                                                            RT1 );
}

template < class FT, class RT >
inline
bool
CGAL__Translation_repH3<FT,RT>::is_even() const
{ return true; }

template < class FT, class RT >
CGAL_KERNEL_LARGE_INLINE
RT
CGAL__Translation_repH3<FT,RT>::
homogeneous(int i, int j) const
{
  CGAL_kernel_precondition( (i >= 0) && (i <= 3) && (j >= 0) && (j <= 3) );
  const RT  RT0(0);
  switch (i)
  {
    case 0: switch (j)
            {
              case 0: return tv.hw();
              case 1: return RT0;
              case 2: return RT0;
              case 3: return tv.hx();
            }
    case 1: switch (j)
            {
              case 0: return RT0;
              case 1: return tv.hw();
              case 2: return RT0;
              case 3: return tv.hy();
            }
    case 2: switch (j)
            {
              case 0: return RT0;
              case 1: return RT0;
              case 2: return tv.hw();
              case 3: return tv.hz();
            }
    case 3: switch (j)
            {
              case 0: return RT0;
              case 1: return RT0;
              case 2: return RT0;
              case 3: return tv.hw();
            }
  }
  return RT0;
}

template < class FT, class RT >
inline
FT
CGAL__Translation_repH3<FT,RT>::
cartesian(int i, int j) const
{
  return FT(homogeneous(i,j)) / FT(tv.hw());
}


template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_Aff_transformationH3<FT,RT>
CGAL__general_transformation_composition(
    CGAL__Aff_transformation_repH3<FT,RT> l,
    CGAL__Aff_transformation_repH3<FT,RT> r )
{
  return CGAL_Aff_transformationH3<FT,RT>(
            l.t00*r.t00 + l.t01*r.t10 + l.t02*r.t20,
            l.t00*r.t01 + l.t01*r.t11 + l.t02*r.t21,
            l.t00*r.t02 + l.t01*r.t12 + l.t02*r.t22,
            l.t00*r.t03 + l.t01*r.t13 + l.t02*r.t23 + l.t03*r.t33,

            l.t10*r.t00 + l.t11*r.t10 + l.t12*r.t20,
            l.t10*r.t01 + l.t11*r.t11 + l.t12*r.t21,
            l.t10*r.t02 + l.t11*r.t12 + l.t12*r.t22,
            l.t10*r.t03 + l.t11*r.t13 + l.t12*r.t23 + l.t13*r.t33,

            l.t20*r.t00 + l.t21*r.t10 + l.t22*r.t20,
            l.t20*r.t01 + l.t21*r.t11 + l.t22*r.t21,
            l.t20*r.t02 + l.t21*r.t12 + l.t22*r.t22,
            l.t20*r.t03 + l.t21*r.t13 + l.t22*r.t23 + l.t23*r.t33,

            l.t33*r.t33 );
}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_Aff_transformationH3<FT,RT>::CGAL_Aff_transformationH3()
{ PTR = new CGAL__Aff_transformation_repH3<FT,RT>(); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_Aff_transformationH3<FT,RT>::
CGAL_Aff_transformationH3( const CGAL_Aff_transformationH3<FT,RT>& tbc)
 : CGAL_Handle(tbc)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_Aff_transformationH3<FT,RT>::
CGAL_Aff_transformationH3(const CGAL_Translation&,
                          const CGAL_VectorH3<FT,RT>& v)
{ PTR = new CGAL__Translation_repH3<FT,RT>( v ); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_Aff_transformationH3<FT,RT>::
CGAL_Aff_transformationH3(const CGAL_Scaling&, const RT& num, const RT& den)
{
  const RT RT0(0);
  PTR = new CGAL__Aff_transformation_repH3<FT,RT>(num, RT0, RT0, RT0,
                                                  RT0, num, RT0, RT0,
                                                  RT0, RT0, num, RT0,
                                                                 den );
}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_Aff_transformationH3<FT,RT>::
CGAL_Aff_transformationH3(
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
CGAL_KERNEL_CTOR_INLINE
CGAL_Aff_transformationH3<FT,RT>::
CGAL_Aff_transformationH3(
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
inline
CGAL__Aff_transformation_rep_baseH3<FT,RT>*
CGAL_Aff_transformationH3<FT,RT>::ptr() const
// static_cast
{ return (CGAL__Aff_transformation_rep_baseH3<FT,RT>*) PTR; }

template < class FT, class RT >
inline
CGAL_Aff_transformationH3<FT,RT>::~CGAL_Aff_transformationH3()
{}

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::transform(const CGAL_PointH3<FT,RT>& p) const
{ return ptr()->transform(p); }

template < class FT, class RT >
inline
CGAL_VectorH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::transform(const CGAL_VectorH3<FT,RT>& v) const
{ return ptr()->transform(v); }

template < class FT, class RT >
inline
CGAL_DirectionH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::
transform(const CGAL_DirectionH3<FT,RT>& d) const
{ return ptr()->transform(d); }

#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
template < class FT, class RT >
inline
CGAL_PlaneH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::
transform(const CGAL_PlaneH3<FT,RT>& pl) const
{ return ptr()->transform(pl); }
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT

template < class FT, class RT >
inline
CGAL_Aff_transformationH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::inverse() const
{ return ptr()->inverse(); }

template < class FT, class RT >
inline
CGAL_Aff_transformationH3<FT,RT>
CGAL_Aff_transformationH3<FT,RT>::transpose() const
{ return ptr()->transpose(); }

template < class FT, class RT >
inline
bool
CGAL_Aff_transformationH3<FT,RT>::is_even() const
{ return ptr()->is_even(); }

template < class FT, class RT >
inline
bool
CGAL_Aff_transformationH3<FT,RT>::is_odd() const
{ return ( ! (ptr()->is_even() )); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_Aff_transformationH3<FT,RT>
operator*(const CGAL_Aff_transformationH3<FT,RT>& left_argument,
          const CGAL_Aff_transformationH3<FT,RT>& right_argument )
{
 return CGAL__general_transformation_composition(
              left_argument.ptr() ->general_form(),
              right_argument.ptr()->general_form() );
}


template < class FT, class RT >
ostream &
operator<< ( ostream & out,
             const CGAL_Aff_transformationH3<FT,RT>& t)
{
 RT RT0(0);
 CGAL__Aff_transformation_repH3<FT,RT> r = t.ptr()->general_form();
 return  out
 << "| "<< r.t00 <<' '<< r.t01 <<' '<< r.t02 <<' '<< r.t03 << " |\n"
 << "| "<< r.t10 <<' '<< r.t11 <<' '<< r.t12 <<' '<< r.t13 << " |\n"
 << "| "<< r.t20 <<' '<< r.t21 <<' '<< r.t22 <<' '<< r.t23 << " |\n"
 << "| "<< RT0   <<' '<< RT0   <<' '<< RT0   <<' '<< r.t33 << " |\n";
}

#endif // CGAL_AFF_TRANSFORMATIONH3_H
