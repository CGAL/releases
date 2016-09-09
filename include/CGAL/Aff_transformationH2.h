

//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: Aff_transformationH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_AFF_TRANSFORMATIONH2_H
#define CGAL_AFF_TRANSFORMATIONH2_H

#include <CGAL/rational_rotation.h>

#ifdef CGAL_WORKAROUND_015
#define CGAL_NO_LINE_TRANSFORM_IN_AT
#endif // CGAL_WORKAROUND_015

template <class FT, class RT>
class CGAL__Aff_transformation_repH2;

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
               if ( g > 0 )
               {
                   return CGAL_DirectionH2<FT,RT>( a * dir.x() + b * dir.y(),
                                                   d * dir.x() + e * dir.y() );
               }
               else if ( g < 0 )
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

    RT    a;           //    |  a  b  c  |   | x |   | xn |
    RT    b;           //    |  d  e  f  | * | y | = | yn |
    RT    c;           //    |  0  0  g  |   | w |   | wn |
    RT    d;
    RT    e;
    RT    f;
    RT    g;

  friend   CGAL_Aff_transformationH2<FT,RT>
    CGAL__general_transformation_composition(
                                   CGAL__Aff_transformation_repH2<FT,RT> l,
                                   CGAL__Aff_transformation_repH2<FT,RT> r );

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

private:

    RT  _sf_num;
    RT  _sf_den;
};




template < class FT, class RT >
class CGAL_Aff_transformationH2 : public CGAL_Handle
{
public:
          CGAL_Aff_transformationH2();
          CGAL_Aff_transformationH2(const CGAL_Aff_transformationH2& tbc);

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

#ifdef CGAL_WORKAROUND_008
          CGAL_Aff_transformationH2(
                                CGAL__Aff_transformation_repH2<FT,RT>* ptr);
#endif // CGAL_WORKAROUND_008


          ~CGAL_Aff_transformationH2();


    CGAL_PointH2<FT,RT>     transform(const CGAL_PointH2<FT,RT>& p) const;
    CGAL_VectorH2<FT,RT>    transform(const CGAL_VectorH2<FT,RT>& v) const;
    CGAL_DirectionH2<FT,RT> transform(const CGAL_DirectionH2<FT,RT>& d) const;
#ifndef CGAL_NO_LINE_TRANSFORM_IN_AT
    CGAL_LineH2<FT,RT>      transform(const CGAL_LineH2<FT,RT>& l) const;
#endif // CGAL_NO_LINE_TRANSFORM_IN_AT

    CGAL_Aff_transformationH2
                            inverse() const;
    bool                    is_even() const;
    bool                    is_odd()  const;
    CGAL__Aff_transformation_repH2<FT,RT>
                            general_form() const;

//  friend   CGAL_Aff_transformationH2<FT,RT>
//    operator*(const CGAL_Aff_transformationH2<FT,RT>& left_argument,
//              const CGAL_Aff_transformationH2<FT,RT>& right_argument );

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
CGAL_Aff_transformationH2<FT,RT>::CGAL_Aff_transformationH2(
                                     const CGAL_Aff_transformationH2<FT,RT>& t)
 : CGAL_Handle(t)
{
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::CGAL_Aff_transformationH2(
                                               const CGAL_Translation,
                                               const CGAL_VectorH2<FT,RT>& v)
{
 PTR = new CGAL__Translation_repH2<FT,RT>( v );
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::CGAL_Aff_transformationH2(
                                               const CGAL_Scaling,
                                               const RT& a, const RT& b)
{
 PTR = new CGAL__Scaling_repH2<FT,RT>( a, b);
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::CGAL_Aff_transformationH2(
                                               const CGAL_Scaling,
                                               const RT& xa, const RT& xb,
                                               const RT& ya, const RT& yb)
{
 PTR = new CGAL__Aff_transformation_repH2<FT,RT>(
                    xa * yb,    RT(0)  ,    RT(0)  ,
                    RT(0)  ,    ya * xb,    RT(0)  ,
                                            xb * yb  );
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::CGAL_Aff_transformationH2(
                                               const CGAL_Rotation,
                                               const RT& sine,
                                               const RT& cosine,
                                               const RT& denominator)
{
 PTR = new CGAL__Rotation_repH2<FT,RT>(sine, cosine, denominator);
}
template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::CGAL_Aff_transformationH2(
                                           const CGAL_Rotation,
                                           const CGAL_DirectionH2<FT,RT>& dir,
                                           const RT& n,
                                           const RT& d)
{

 const RT   RTzero = RT(0)  ;
 const RT   RTone  = RT(1)  ;
 CGAL_kernel_precondition( n > RTzero );
 CGAL_kernel_precondition( d > RTzero );
 RT   sin;
 RT   cos;
 RT   den;

 CGAL_rational_rotation_approximation(dir.x(), dir.y(), sin, cos, den, n, d);
#ifdef HUMBUG
 RT   dx = abs(dir.x() );
 RT   dy = abs(dir.y() );
 RT   sq_hypotenuse = dx*dx + dy*dy;
 RT   common_part;
 RT   diff_part;
 RT   rhs;
 bool lower_ok;
 bool upper_ok;

 if (dy > dx)
 {
    CGAL_swap (dx,dy);
 }
 // approximate sin = dy / sqrt(sq_hypotenuse)
 // if ( dy / sqrt(sq_hypotenuse) < n/d )
 if (dy * dy * d * d < sq_hypotenuse * n * n)
 {
    cos = RTone;
    sin = RTzero;
    den = RTone;
 }
 else
 {
    RT  p;
    RT  q;
    RT  p0 = RTzero;
    RT  q0 = RTone;
    RT  p1 = RTone;
    RT  q1 = RTone;

    for(;;)
    {
        p = p0 + p1;
        q = q0 + q1;
        sin = RT(2)*p*q;
        den = p*p + q*q;

        // sanity check for approximation
        //        sin/den < dy/sqrt(hypotenuse) + n/d
        //    &&  sin/den > dy/sqrt(hypotenuse) - n/d
        // ===    sin/den - n/d  <   dy/sqrt(sq_hypotenuse)
        //    &&  sin/den + n/d  >   dy/sqrt(sq_hypotenuse)
        // ===    (sin^2 d^2 + n^2 den^2)sq_hypotenuse - 2... < dy^2 d^2 den^2
        //    &&  (sin^2 d^2 + n^2 den^2)sq_hypotenuse + 2... > dy^2 d^2 den^2

        common_part = (sin*sin*d*d + n*n*den*den)*sq_hypotenuse;
        diff_part   = RT(2)*n*sin*d*den*sq_hypotenuse;
        rhs         = dy*dy*d*d*den*den;

        upper_ok    = (common_part - diff_part < rhs);
        lower_ok    = (common_part + diff_part > rhs);

        if ( lower_ok && upper_ok )
        {
           // if ( (p*p)%2 + (q*q)%2 > RTone)
           // {
           //     sin = p*q;
           //     cos = (q*q - p*p)/2;    // exact division
           //     den = (p*p + q*q)/2;    // exact division
           // }
           // else
           // {
                  cos = q*q - p*p;
           // }

           break;
        }
        else
        {
            // if ( dy/sqrt(sq_hypotenuse) < sin/den )
            if ( dy*dy*den*den < sin*sin*sq_hypotenuse )
            {
                p1 = p;
                q1 = q;
            }
            else
            {
                p0 = p;
                q0 = q;
            }
        }
    } // for(;;)
 }
 dx = dir.x();
 dy = dir.y();
 if (dy > dx )
 {
     CGAL_swap (sin,cos);
 }
 if (dy < RTzero)
 {
     sin = - sin;
 }
 if (dx < RTzero)
 {
     cos = - cos;
 }
#endif // 0

 PTR = new CGAL__Rotation_repH2<FT,RT>( sin, cos, den );
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::CGAL_Aff_transformationH2(
                                 const CGAL_VectorH2<FT,RT>& v,
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
CGAL_Aff_transformationH2<FT,RT>::CGAL_Aff_transformationH2(
                                   const RT& a, const RT& b, const RT& c,
                                   const RT& d, const RT& e, const RT& f,
                                   const RT& g)
{
 PTR = new CGAL__Aff_transformation_repH2<FT,RT>( a,   b,   c,
                                                  d,   e,   f,
                                                            g  );
}

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>::CGAL_Aff_transformationH2(
                                   const RT& a, const RT& b,
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
CGAL_Aff_transformationH2<FT,RT>::transform(const CGAL_PointH2<FT,RT>& p) const
{
 return ptr()->transform(p);
}


template < class FT, class RT >
CGAL_VectorH2<FT,RT>
CGAL_Aff_transformationH2<FT,RT>::transform(
                                      const CGAL_VectorH2<FT,RT>& v) const
{
 return ptr()->transform(v);
}

template < class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_Aff_transformationH2<FT,RT>::transform(
                                      const CGAL_DirectionH2<FT,RT>& d) const
{
 return ptr()->transform(d);
}

#ifndef CGAL_NO_LINE_TRANSFORM_IN_AT
template < class FT, class RT >
CGAL_LineH2<FT,RT>
CGAL_Aff_transformationH2<FT,RT>::transform(const CGAL_LineH2<FT,RT>& l) const
{
 return CGAL_LineH2<FT,RT>( transform( l.start()), transform( l.end()) );
}
#endif // CGAL_NO_LINE_TRANSFORM_IN_AT

template < class FT, class RT >
CGAL_Aff_transformationH2<FT,RT>
CGAL_Aff_transformationH2<FT,RT>::inverse() const
{
 return ptr()->inverse();
}

template < class FT, class RT >
bool
CGAL_Aff_transformationH2<FT,RT>::is_even() const
{
 return ptr()->is_even();
}

template < class FT, class RT >
bool
CGAL_Aff_transformationH2<FT,RT>::is_odd() const
{
 return !( ptr()->is_even() );
}

template < class FT, class RT >
CGAL__Aff_transformation_repH2<FT,RT>
CGAL_Aff_transformationH2<FT,RT>::general_form() const
{
 return ptr()->general_form();
}

template <class FT, class RT>
CGAL_Aff_transformationH2<FT,RT>
//operator*(const CGAL_Aff_transformationH2<FT,RT>& left_argument,
//          const CGAL_Aff_transformationH2<FT,RT>& right_argument )
CGAL_Aff_transformationH2<FT,RT>::operator*(
                const CGAL_Aff_transformationH2<FT,RT>& right_argument) const
{
return CGAL__general_transformation_composition(
//                  left_argument.ptr()->general_form(),
                  ptr()->general_form(),
                  right_argument.ptr()->general_form() );
}

template < class FT, class RT >
CGAL__Aff_transformation_rep_baseH2<FT,RT>*
CGAL_Aff_transformationH2<FT,RT>::ptr() const
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


#endif // CGAL_AFF_TRANSFORMATIONH2_H
