// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// source        : Aff_transformationH2.fw
// file          : include/CGAL/Aff_transformationH2.h
// package       : H2 (1.2.1)
// revision      : 1.2.1
// revision_date : 15 Jan 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_AFF_TRANSFORMATIONH2_H
#define CGAL_AFF_TRANSFORMATIONH2_H

#ifndef CGAL_RATIONAL_ROTATION_H
#include <CGAL/rational_rotation.h>
#endif // CGAL_RATIONAL_ROTATION_H

#if defined(CGAL_CFG_INCOMPLETE_TYPE_BUG_1) && \
   !defined(CGAL_NO_LINE_TRANSFORM_IN_AT)
#define CGAL_NO_LINE_TRANSFORM_IN_AT
#endif // CGAL_CFG_INCOMPLETE_TYPE_BUG_1

template <class FT, class RT>
class CGAL__Aff_transformationH2;

template <class FT, class RT>
class CGAL__Aff_transformation_repH2;

template <class FT, class RT>
CGAL_Aff_transformationH2<FT,RT>
CGAL__general_transformation_composition (
                                   CGAL__Aff_transformation_repH2<FT,RT> l,
                                   CGAL__Aff_transformation_repH2<FT,RT> r);

template <class FT, class RT>
class CGAL__Aff_transformation_rep_baseH2 : public CGAL_Rep
{
public:

    virtual             ~CGAL__Aff_transformation_rep_baseH2(){}

    virtual  CGAL_PointH2<FT,RT>
                        transform(const CGAL_PointH2<FT,RT>& p) const = 0;
    virtual  CGAL_VectorH2<FT,RT>
                        transform(const CGAL_VectorH2<FT,RT>& v) const = 0;
    virtual  CGAL_DirectionH2<FT,RT>
                        transform(const CGAL_DirectionH2<FT,RT>& d) const = 0;
    virtual  CGAL_Aff_transformationH2<FT,RT>
                        inverse() const = 0;
    virtual  CGAL__Aff_transformation_repH2<FT,RT>
                        general_form() const = 0;
    virtual  bool       is_even() const = 0;

    virtual  RT         homogeneous(int i, int j) const = 0;
    virtual  FT         cartesian(int i, int j) const = 0;


};

template < class FT, class RT >
class CGAL__Aff_transformation_repH2 :
                            public CGAL__Aff_transformation_rep_baseH2<FT,RT>
{
public:

        CGAL__Aff_transformation_repH2()
        {
        }
        CGAL__Aff_transformation_repH2(
                                 const RT& m00, const RT& m01, const RT& m02,
                                 const RT& m10, const RT& m11, const RT& m12,
                                 const RT& m22) :
          a(m00), b(m01), c(m02), d(m10), e(m11), f(m12), g(m22)
        {
        }
        ~CGAL__Aff_transformation_repH2()
        {
        }

    virtual  CGAL_PointH2<FT,RT>
             transform(const CGAL_PointH2<FT,RT>& p) const
             {
               return CGAL_PointH2<FT,RT>( a * p.hx() + b * p.hy() + c * p.hw(),
                                           d * p.hx() + e * p.hy() + f * p.hw(),
                                           g * p.hw()
                                          );
             }

    virtual  CGAL_VectorH2<FT,RT>
             transform(const CGAL_VectorH2<FT,RT>& v) const
             {
               return CGAL_VectorH2<FT,RT>( a * v.hx() + b * v.hy(),
                                            d * v.hx() + e * v.hy(),
                                            g * v.hw()
                                          );
             }

    virtual  CGAL_DirectionH2<FT,RT>
             transform(const CGAL_DirectionH2<FT,RT>& dir) const
             {
               RT RT0(0);
               if ( g > RT0 )
               {
                   return CGAL_DirectionH2<FT,RT>( a * dir.x() + b * dir.y(),
                                                   d * dir.x() + e * dir.y() );
               }
               else if ( g < RT0 )
               {
                   return - CGAL_DirectionH2<FT,RT>(a * dir.x() + b * dir.y(),
                                                    d * dir.x() + e * dir.y() );
               }
               return CGAL_DirectionH2<FT,RT>( a * dir.x() + b * dir.y(),
                                               d * dir.x() + e * dir.y(),
                                               g );

             }

    virtual  CGAL_Aff_transformationH2<FT,RT>
             inverse() const
             {
                RT  ai =   e*g;
                RT  bi = - b*g;
                RT  ci =   b*f - e*c;
                RT  di = - d*g;
                RT  ei =   a*g;
                RT  fi =   d*c - a*f;
                RT  gi =   a*e - b*d;
                return CGAL_Aff_transformationH2<FT,RT>( ai, bi, ci,
                                                         di, ei, fi,
                                                                 gi) ;
             }


    virtual   CGAL__Aff_transformation_repH2<FT,RT>
              general_form() const
              {
                return *this;
              }

    virtual   bool
              is_even() const
              {
                return CGAL_sign( (a*e - b*d)*g )== 1;
              }

    virtual   RT   homogeneous(int i, int j) const;
    virtual   FT   cartesian(int i, int j) const;

    RT    a;           //    |  a  b  c  |   | x |   | xn |
    RT    b;           //    |  d  e  f  | * | y | = | yn |
    RT    c;           //    |  0  0  g  |   | w |   | wn |
    RT    d;
    RT    e;
    RT    f;
    RT    g;

  friend CGAL_Aff_transformationH2<FT,RT>
         CGAL__general_transformation_composition CGAL_NULL_TMPL_ARGS (
                                   CGAL__Aff_transformation_repH2<FT,RT> l,
                                   CGAL__Aff_transformation_repH2<FT,RT> r
                                                                      );
};

template < class FT, class RT >
class CGAL__Translation_repH2 :
                          public CGAL__Aff_transformation_rep_baseH2<FT,RT>
{
public:
             CGAL__Translation_repH2()
             {
             }
             CGAL__Translation_repH2(const CGAL_VectorH2<FT,RT> & tv) :
               _tv(tv)
             {
             }
             ~CGAL__Translation_repH2()
             {
             }

    virtual  CGAL_PointH2<FT,RT>
             transform(const CGAL_PointH2<FT,RT> & p) const
             {
               return (p + _tv);
             }
    virtual  CGAL_VectorH2<FT,RT>
             transform(const CGAL_VectorH2<FT,RT> & v) const
             {
               return (v);
             }
    virtual  CGAL_DirectionH2<FT,RT>
             transform(const CGAL_DirectionH2<FT,RT> & d) const
             {
               return (d);
             }
    virtual  CGAL_Aff_transformationH2<FT,RT>
             inverse() const
             {
               return CGAL_Aff_transformationH2<FT,RT>(CGAL_TRANSLATION, - _tv);
             }
    virtual  bool
             is_even() const
             {
               return true;
             }
    virtual  CGAL__Aff_transformation_repH2<FT,RT>
             general_form() const
             {
               return CGAL__Aff_transformation_repH2<FT,RT>(
                                _tv.hw(),  RT(0)  ,   _tv.hx(),
                                RT(0)  ,   _tv.hw(),  _tv.hy(),
                                                      _tv.hw() );
             }

    virtual  RT   homogeneous(int i, int j) const;
    virtual  FT   cartesian(int i, int j) const;


private:

    CGAL_VectorH2<FT,RT> _tv;
};
template < class FT, class RT >
class CGAL__Rotation_repH2 : public CGAL__Aff_transformation_rep_baseH2<FT,RT>
{
public:
             CGAL__Rotation_repH2()
             {
             }
             CGAL__Rotation_repH2(const RT& sin, const RT& cos, const RT& den) :
               _sin(sin), _cos(cos), _den(den)
             {
               if ( den < RT(0)   )
               {
                 _sin = - _sin;
                 _cos = - _cos;
                 _den = - _den;
               };
             }
             ~CGAL__Rotation_repH2()
             {
             }

    virtual  CGAL_PointH2<FT,RT>
             transform(const CGAL_PointH2<FT,RT> & p) const
             {
               return CGAL_PointH2<FT,RT>( p.hx()*_cos  - p.hy()*_sin,
                                           p.hx()*_sin  + p.hy()*_cos,
                                           p.hw()*_den );
             }
    virtual  CGAL_VectorH2<FT,RT>
             transform(const CGAL_VectorH2<FT,RT> & v) const
             {
               return CGAL_VectorH2<FT,RT>( v.hx()*_cos  - v.hy()*_sin,
                                            v.hx()*_sin  + v.hy()*_cos,
                                            v.hw()*_den );
             }
    virtual  CGAL_DirectionH2<FT,RT>
             transform(const CGAL_DirectionH2<FT,RT> & d) const
             {
               return CGAL_DirectionH2<FT,RT>( d.x()*_cos  - d.y()*_sin,
                                               d.x()*_sin  + d.y()*_cos);
             }
    virtual  CGAL_Aff_transformationH2<FT,RT>
             inverse() const
             {
               return CGAL_Aff_transformationH2<FT,RT>(CGAL_ROTATION,
                                                       - _sin, _cos, _den);
             }
    virtual  bool
             is_even() const
             {
               return true;
             }
    virtual  CGAL__Aff_transformation_repH2<FT,RT>
             general_form() const
             {
               return CGAL__Aff_transformation_repH2<FT,RT>(
                           _cos,  - _sin,  RT(0)  ,
                           _sin,    _cos,  RT(0)  ,
                                           _den );
             }

    virtual  RT   homogeneous(int i, int j) const;
    virtual  FT   cartesian(int i, int j) const;


private:
    RT  _sin;
    RT  _cos;
    RT  _den;
};

template < class FT, class RT >
class CGAL__Scaling_repH2 : public CGAL__Aff_transformation_rep_baseH2<FT,RT>
{
public:
             CGAL__Scaling_repH2()
             {
             }
             CGAL__Scaling_repH2(const RT& scaling_numerator,
                                 const RT& scaling_denominator) :
               _sf_num(scaling_numerator), _sf_den(scaling_denominator)
             {
               if ( scaling_denominator < RT(0)   )
               {
                 _sf_num = - _sf_num;
                 _sf_den = - _sf_den;
               };
             }
             ~CGAL__Scaling_repH2()
             {
             }

    virtual  CGAL_PointH2<FT,RT>
             transform(const CGAL_PointH2<FT,RT> & p) const
             {
               return CGAL_PointH2<FT,RT>( p.hx() * _sf_num,
                                           p.hy() * _sf_num,
                                           p.hw() * _sf_den );
             }
    virtual  CGAL_VectorH2<FT,RT>
             transform(const CGAL_VectorH2<FT,RT> & v) const
             {
               return CGAL_VectorH2<FT,RT>( v.hx() * _sf_num,
                                            v.hy() * _sf_num,
                                            v.hw() * _sf_den );
             }
    virtual  CGAL_DirectionH2<FT,RT>
             transform(const CGAL_DirectionH2<FT,RT> & d) const
             {
               return (d);
             }
    virtual  CGAL_Aff_transformationH2<FT,RT>
             inverse() const
             {
               return CGAL_Aff_transformationH2<FT,RT>(CGAL_SCALING,
                                                        _sf_den, _sf_num);
             }
    virtual  bool
             is_even() const
             {
               return true;
             }
    virtual  CGAL__Aff_transformation_repH2<FT,RT>
             general_form() const
             {
               return CGAL__Aff_transformation_repH2<FT,RT>(
                              _sf_num,  RT(0)  ,  RT(0)  ,
                              RT(0)  ,  _sf_num,  RT(0)  ,
                                                  _sf_den );
             }

    virtual  RT   homogeneous(int i, int j) const;
    virtual  FT   cartesian(int i, int j) const;


private:

    RT  _sf_num;
    RT  _sf_den;
};




template < class FT, class RT >
class CGAL_Aff_transformationH2 : public CGAL_Handle
{
public:
          CGAL_Aff_transformationH2();
          CGAL_Aff_transformationH2(
                                 const CGAL_Aff_transformationH2<FT,RT>& tbc);

          // Translation:

          CGAL_Aff_transformationH2(const CGAL_Translation,
                                    const CGAL_VectorH2<FT,RT>& v);

          // Scaling:

          CGAL_Aff_transformationH2(const CGAL_Scaling,
                                    const RT& a,  const RT& b = RT(1)  );
          CGAL_Aff_transformationH2(const CGAL_Scaling,
                                    const RT& xa, const RT& xb,
                                    const RT& ya, const RT& yb);

          // Rational Rotation:

          CGAL_Aff_transformationH2(const CGAL_Rotation,
                                    const RT& sine,
                                    const RT& cosine,
                                    const RT& denominator);

          CGAL_Aff_transformationH2(const CGAL_Rotation,
                                    const CGAL_DirectionH2<FT,RT>& dir,
                                    const RT& n,
                                    const RT& d = RT(1)   );

          // Orthogonal Transformation:

          CGAL_Aff_transformationH2(const CGAL_VectorH2<FT,RT>& v,
                                    const RT& sine,
                                    const RT& cosine,
                                    const RT& denominator,
                                    const RT& scaling_numerator = RT(1)  ,
                                    const RT& scaling_denominator = RT(1)   );

          // General affine transformation
          //    | a b c |   |x|
          //    | d e f | * |y|
          //    | 0 0 g |   |w|

          CGAL_Aff_transformationH2(const RT& a, const RT& b, const RT& c,
                                    const RT& d, const RT& e, const RT& f,
                                                              const RT& g
                                                                    = RT(1)  );

          CGAL_Aff_transformationH2(const RT& a, const RT& b,
                                    const RT& d, const RT& e,
                                                              const RT& g
                                                                    = RT(1)  );

#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_1
          CGAL_Aff_transformationH2(
                                CGAL__Aff_transformation_repH2<FT,RT>* ptr);
#endif // CGAL_CFG_INCOMPLETE_TYPE_BUG_1


          ~CGAL_Aff_transformationH2();


    CGAL_PointH2<FT,RT>     transform(const CGAL_PointH2<FT,RT>& p) const;
    CGAL_VectorH2<FT,RT>    transform(const CGAL_VectorH2<FT,RT>& v) const;
    CGAL_DirectionH2<FT,RT> transform(const CGAL_DirectionH2<FT,RT>& d) const;
#ifndef CGAL_NO_LINE_TRANSFORM_IN_AT
    CGAL_LineH2<FT,RT>      transform(const CGAL_LineH2<FT,RT>& l) const;
#endif // CGAL_NO_LINE_TRANSFORM_IN_AT

    CGAL_Aff_transformationH2<FT,RT>
                            inverse() const;
    bool                    is_even() const;
    bool                    is_odd()  const;

                            // Access functions for matrix form
    FT                      cartesian(int i, int j) const;
    RT                      homogeneous(int i, int j) const;
    FT                      m(int i, int j) const
                            { return cartesian(i,j); }
    RT                      hm(int i, int j) const
                            { return homogeneous(i,j); }

    CGAL__Aff_transformation_repH2<FT,RT>
                            general_form() const;

//  friend   CGAL_Aff_transformationH2<FT,RT>
//    operator* CGAL_NULL_TMPL_ARGS
//              (const CGAL_Aff_transformationH2<FT,RT>& left_argument,
//               const CGAL_Aff_transformationH2<FT,RT>& right_argument );

    CGAL_Aff_transformationH2<FT,RT> operator*(
              const CGAL_Aff_transformationH2<FT,RT>& right_argument ) const;

private:

    CGAL__Aff_transformation_rep_baseH2<FT,RT>*
                            ptr() const;
};

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::CGAL_Aff_transformationH2()
{
  PTR = new CGAL__Aff_transformation_repH2<FT,RT>();
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::
CGAL_Aff_transformationH2(const CGAL_Aff_transformationH2<FT,RT>& t)
 : CGAL_Handle(t)
{
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::
CGAL_Aff_transformationH2(const CGAL_Translation,const CGAL_VectorH2<FT,RT>& v)
{
  PTR = new CGAL__Translation_repH2<FT,RT>( v );
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::
CGAL_Aff_transformationH2(const CGAL_Scaling, const RT& a, const RT& b)
{
  PTR = new CGAL__Scaling_repH2<FT,RT>( a, b);
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::
CGAL_Aff_transformationH2( const CGAL_Scaling, const RT& xa, const RT& xb,
                                               const RT& ya, const RT& yb)
{
  PTR = new CGAL__Aff_transformation_repH2<FT,RT>(
                     xa * yb,    RT(0)  ,    RT(0)  ,
                     RT(0)  ,    ya * xb,    RT(0)  ,
                                             xb * yb  );
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::
CGAL_Aff_transformationH2(const CGAL_Rotation,
                          const RT& sine,
                          const RT& cosine,
                          const RT& denominator)
{
  PTR = new CGAL__Rotation_repH2<FT,RT>(sine, cosine, denominator);
}
template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::
CGAL_Aff_transformationH2( const CGAL_Rotation,
                           const CGAL_DirectionH2<FT,RT>& dir,
                           const RT& n,
                           const RT& d)
{

 const RT   RTzero = RT(0)  ;
 CGAL_kernel_precondition( n > RTzero );
 CGAL_kernel_precondition( d > RTzero );
 RT   sin;
 RT   cos;
 RT   den;

 CGAL_rational_rotation_approximation(dir.x(), dir.y(), sin, cos, den, n, d);

 PTR = new CGAL__Rotation_repH2<FT,RT>( sin, cos, den );
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::
CGAL_Aff_transformationH2( const CGAL_VectorH2<FT,RT>& v,
                           const RT& sine,
                           const RT& cosine,
                           const RT& denominator,
                           const RT& scaling_numerator,
                           const RT& scaling_denominator )
{
  CGAL_Aff_transformationH2<FT,RT>
        scaling(CGAL_SCALING,scaling_numerator,scaling_denominator);
  CGAL_Aff_transformationH2<FT,RT>
        combination =
        CGAL_Aff_transformationH2<FT,RT>(CGAL_TRANSLATION,
                                         scaling.inverse().transform(-v) )
      * scaling
      * CGAL_Aff_transformationH2<FT,RT>(CGAL_ROTATION,
                                         sine, cosine, denominator)
      * CGAL_Aff_transformationH2<FT,RT>(CGAL_TRANSLATION,
                                         v ) ;

  //  PTR is still 0
  //  currently LEDA (3.3) checks PTR in assignment before deletion
  *this = combination;

}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::
CGAL_Aff_transformationH2( const RT& a, const RT& b, const RT& c,
                           const RT& d, const RT& e, const RT& f,
                                                     const RT& g)
{
  PTR = new CGAL__Aff_transformation_repH2<FT,RT>( a,   b,   c,
                                                   d,   e,   f,
                                                             g  );
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::
CGAL_Aff_transformationH2( const RT& a, const RT& b,
                           const RT& d, const RT& e,
                                                     const RT& g)
{
  PTR = new CGAL__Aff_transformation_repH2<FT,RT>( a,   b,   RT(0),
                                                   d,   e,   RT(0),
                                                             g  );
}

//template < class FT, class RT >
//CGAL_Aff_transformationH2<FT,RT>::CGAL_Aff_transformationH2(
//                               CGAL__Aff_transformation_repH2<FT,RT>* rep_ptr)
//{
// PTR = rep_ptr;
//}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::~CGAL_Aff_transformationH2()
{
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_Aff_transformationH2<FT,RT>::
transform(const CGAL_PointH2<FT,RT>& p) const
{
  return ptr()->transform(p);
}


template < class FT, class RT >
CGAL_VectorH2<FT,RT>
CGAL_Aff_transformationH2<FT,RT>::
transform( const CGAL_VectorH2<FT,RT>& v) const
{
  return ptr()->transform(v);
}

template < class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_Aff_transformationH2<FT,RT>::
transform( const CGAL_DirectionH2<FT,RT>& d) const
{
  return ptr()->transform(d);
}

#ifndef CGAL_NO_LINE_TRANSFORM_IN_AT
template < class FT, class RT >
CGAL_LineH2<FT,RT>
CGAL_Aff_transformationH2<FT,RT>::
transform(const CGAL_LineH2<FT,RT>& l) const
{
  return CGAL_LineH2<FT,RT>( transform( l.point(0)), transform( l.point(1)) );
}
#endif // CGAL_NO_LINE_TRANSFORM_IN_AT

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>
CGAL_Aff_transformationH2<FT,RT>::
inverse() const
{
  return ptr()->inverse();
}

template < class FT, class RT >
bool
CGAL_Aff_transformationH2<FT,RT>::
is_even() const
{
  return ptr()->is_even();
}

template < class FT, class RT >
bool
CGAL_Aff_transformationH2<FT,RT>::
is_odd() const
{
  return !( ptr()->is_even() );
}

template < class FT, class RT >
inline
FT
CGAL_Aff_transformationH2<FT,RT>::
cartesian(int i, int j) const
{
  return ptr()->cartesian(i,j);
}

template < class FT, class RT >
inline
RT
CGAL_Aff_transformationH2<FT,RT>::
homogeneous(int i, int j) const
{
  return ptr()->homogeneous(i,j);
}

template < class FT, class RT >
CGAL__Aff_transformation_repH2<FT,RT>
CGAL_Aff_transformationH2<FT,RT>::
general_form() const
{
  return ptr()->general_form();
}

template <class FT, class RT>
CGAL_Aff_transformationH2<FT,RT>
//operator*(const CGAL_Aff_transformationH2<FT,RT>& left_argument,
//          const CGAL_Aff_transformationH2<FT,RT>& right_argument )
CGAL_Aff_transformationH2<FT,RT>::
operator*(const CGAL_Aff_transformationH2<FT,RT>& right_argument) const
{
  return CGAL__general_transformation_composition(
                  ptr()->general_form(),
                  right_argument.ptr()->general_form() );
}

template < class FT, class RT >
CGAL__Aff_transformation_rep_baseH2<FT,RT>*
CGAL_Aff_transformationH2<FT,RT>::
ptr() const
{
  return (CGAL__Aff_transformation_rep_baseH2<FT,RT>*)PTR;
}

template <class FT, class RT>
CGAL_Aff_transformationH2<FT,RT>
CGAL__general_transformation_composition(
        CGAL__Aff_transformation_repH2<FT,RT> l,
        CGAL__Aff_transformation_repH2<FT,RT> r )
{
return CGAL_Aff_transformationH2<FT,RT>(
       l.a*r.a + l.b*r.d,   l.a*r.b + l.b*r.e,   l.a*r.c + l.b*r.f + l.c*r.g,
       l.d*r.a + l.e*r.d,   l.d*r.b + l.e*r.e,   l.d*r.c + l.e*r.f + l.f*r.g,
                                                 l.g*r.g                     );
}

template < class FT, class RT >
RT
CGAL__Aff_transformation_repH2<FT,RT>::
homogeneous(int i, int j) const
{
  CGAL_kernel_precondition( (i >= 0) && (i <= 2) && (j >= 0) && (j <= 2) );
  switch (i)
  {
    case 0: switch (j)
            {
              case 0: return a;
              case 1: return b;
              case 2: return c;
            }
    case 1: switch (j)
            {
              case 0: return d;
              case 1: return e;
              case 2: return f;
            }
    case 2: switch (j)
            {
              case 0: return RT(0);
              case 1: return RT(0);
              case 2: return g;
            }
  }
  return RT(0);
}

template < class FT, class RT >
FT
CGAL__Aff_transformation_repH2<FT,RT>::
cartesian(int i, int j) const
{
  CGAL_kernel_precondition( (i >= 0) && (i <= 2) && (j >= 0) && (j <= 2) );
  if ( (i == 2) && (j == 2) )  return FT(1);
  return FT(homogeneous(i,j)) / FT(g);
}


template < class FT, class RT >
RT
CGAL__Translation_repH2<FT,RT>::
homogeneous(int i, int j) const
{
  CGAL_kernel_precondition( (i >= 0) && (i <= 2) && (j >= 0) && (j <= 2) );
  switch (i)
  {
    case 0: switch (j)
            {
              case 0: return _tv.hw();
              case 1: return RT(0);
              case 2: return _tv.hx();
            }
    case 1: switch (j)
            {
              case 0: return RT(0);
              case 1: return _tv.hw();
              case 2: return _tv.hy();
            }
    case 2: switch (j)
            {
              case 0: return RT(0);
              case 1: return RT(0);
              case 2: return _tv.hw();
            }
  }
  return RT(0);
}

template < class FT, class RT >
FT
CGAL__Translation_repH2<FT,RT>::
cartesian(int i, int j) const
{
  CGAL_kernel_precondition( (i >= 0) && (i <= 2) && (j >= 0) && (j <= 2) );
  switch (i)
  {
    case 0: switch (j)
            {
              case 0: return FT(1);
              case 1: return FT(0);
              case 2: return _tv.x();
            }
    case 1: switch (j)
            {
              case 0: return FT(0);
              case 1: return FT(1);
              case 2: return _tv.y();
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


template < class FT, class RT >
RT
CGAL__Rotation_repH2<FT,RT>::
homogeneous(int i, int j) const
{
  CGAL_kernel_precondition( (i >= 0) && (i <= 2) && (j >= 0) && (j <= 2) );
  switch (i)
  {
    case 0: switch (j)
            {
              case 0: return _cos;
              case 1: return - _sin;
              case 2: return RT(0);
            }
    case 1: switch (j)
            {
              case 0: return _sin;
              case 1: return _cos;
              case 2: return RT(0);
            }
    case 2: switch (j)
            {
              case 0: return RT(0);
              case 1: return RT(0);
              case 2: return _den;
            }
  }
  return RT(0);
}

template < class FT, class RT >
FT
CGAL__Rotation_repH2<FT,RT>::
cartesian(int i, int j) const
{
  CGAL_kernel_precondition( (i >= 0) && (i <= 2) && (j >= 0) && (j <= 2) );
  switch (i)
  {
    case 0: switch (j)
            {
              case 0: return FT(_cos) / FT(_den);
              case 1: return - FT(_sin) / FT(_den);
              case 2: return RT(0);
            }
    case 1: switch (j)
            {
              case 0: return FT(_sin) / FT(_den);
              case 1: return FT(_cos) / FT(_den);
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


template < class FT, class RT >
RT
CGAL__Scaling_repH2<FT,RT>::
homogeneous(int i, int j) const
{
  CGAL_kernel_precondition( (i >= 0) && (i <= 2) && (j >= 0) && (j <= 2) );
  switch (i)
  {
    case 0: switch (j)
            {
              case 0: return _sf_num;
              case 1: return RT(0);
              case 2: return RT(0);
            }
    case 1: switch (j)
            {
              case 0: return RT(0);
              case 1: return _sf_num;
              case 2: return RT(0);
            }
    case 2: switch (j)
            {
              case 0: return RT(0);
              case 1: return RT(0);
              case 2: return _sf_den;
            }
  }
  return RT(0);
}

template <class FT, class RT>
FT
CGAL__Scaling_repH2<FT,RT>::
cartesian(int i, int j) const
{
  CGAL_kernel_precondition( (i >= 0) && (i <= 2) && (j >= 0) && (j <= 2) );
  switch (i)
  {
    case 0: switch (j)
            {
              case 0: return FT(_sf_num) / FT(_sf_den);
              case 1: return FT(0);
              case 2: return FT(0);
            }
    case 1: switch (j)
            {
              case 0: return FT(0);
              case 1: return FT(_sf_num) / FT(_sf_den);
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


#endif // CGAL_AFF_TRANSFORMATIONH2_H
