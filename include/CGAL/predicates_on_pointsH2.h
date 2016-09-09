 


// Source: predicates_on_pointsH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_PREDICATES_ON_POINTSH2_H
#define CGAL_PREDICATES_ON_POINTSH2_H

#include <CGAL/PVDH2.h>

 
template < class FT, class RT>
CGAL_Comparison_result
CGAL_compare_lexicographically_xy(const CGAL_PointH2<FT,RT>& p,
                                  const CGAL_PointH2<FT,RT>& q)
{
 CGAL_kernel_precondition(p.is_defined() && q.is_defined() );
 RT pV = p.hx()*q.hw();
 RT qV = q.hx()*p.hw();
 if ( pV == qV )
 {
 pV = p.hy()*q.hw();
 qV = q.hy()*p.hw();
 }
 if ( pV < qV )
 {
 return CGAL_SMALLER;
 }
 else
 {
 return (pV > qV) ? CGAL_LARGER : CGAL_EQUAL;
 }
}


template < class FT, class RT>
bool
CGAL_lexicographically_xy_smaller_or_equal(const CGAL_PointH2<FT,RT>& p,
                                           const CGAL_PointH2<FT,RT>& q)
{
 CGAL_kernel_precondition(p.is_defined() && q.is_defined() );
 return ( !( CGAL_compare_lexicographically_xy(p,q) == CGAL_LARGER ) );
}
 

template < class FT, class RT>
CGAL_Ordertype
CGAL_ordertype( const CGAL_PointH2<FT,RT>& p,
                const CGAL_PointH2<FT,RT>& q,
                const CGAL_PointH2<FT,RT>& r)
{
 CGAL_kernel_precondition(p.is_defined() && q.is_defined() && r.is_defined() );
 RT det =    p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
           + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
           + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );
 if (det == RT(0)  )
 {
 return CGAL_COLLINEAR;
 }
 else
 {
 return det < RT(0)   ? CGAL_CLOCKWISE : CGAL_COUNTERCLOCKWISE;
 }
}


template < class FT, class RT>
bool
CGAL_leftturn( const CGAL_PointH2<FT,RT>& p,
               const CGAL_PointH2<FT,RT>& q,
               const CGAL_PointH2<FT,RT>& r)
{
 return (CGAL_ordertype(p,q,r) == CGAL_COUNTERCLOCKWISE);
}


template < class FT, class RT>
bool
CGAL_rightturn( const CGAL_PointH2<FT,RT>& p,
                const CGAL_PointH2<FT,RT>& q,
                const CGAL_PointH2<FT,RT>& r)
{
 return (CGAL_ordertype(p,q,r) == CGAL_CLOCKWISE);
}


template < class FT, class RT>
bool
CGAL_collinear( const CGAL_PointH2<FT,RT>& p,
                const CGAL_PointH2<FT,RT>& q,
                const CGAL_PointH2<FT,RT>& r)
{
 return (CGAL_ordertype(p,q,r) == CGAL_COLLINEAR);
}
 
template <class FT, class RT>
CGAL_Side
CGAL_in_circle( const CGAL_PointH2<FT,RT>& q,
                const CGAL_PointH2<FT,RT>& r,
                const CGAL_PointH2<FT,RT>& s,
                const CGAL_PointH2<FT,RT>& t)
{
 
 CGAL_kernel_precondition(   q.is_defined() && r.is_defined()
                          && s.is_defined() && t.is_defined() );
 CGAL_nondegeneracy_precondition( ! CGAL_collinear(q,r,s) );

 // compute sign of      |qx  qy  qx^2+qy^2  1 |   | a b c d |
 //                      |      --  r  --      | = | e f g h |
 //     determinant      |      --  s  --      | = | i j k l |
 //                      |      --  t  --      |   | m n o p |
 //           where

 RT a = q.hx()*q.hw();
 RT b = q.hy()*q.hw();
 RT c = q.hx()*q.hx() + q.hy()*q.hy();
 RT d = q.hw()*q.hw();

 RT e = r.hx()*r.hw();
 RT f = r.hy()*r.hw();
 RT g = r.hx()*r.hx() + r.hy()*r.hy();
 RT h = r.hw()*r.hw();

 RT i = s.hx()*s.hw();
 RT j = s.hy()*s.hw();
 RT k = s.hx()*s.hx() + s.hy()*s.hy();
 RT l = s.hw()*s.hw();

 RT m = t.hx()*t.hw();
 RT n = t.hy()*t.hw();
 RT o = t.hx()*t.hx() + t.hy()*t.hy();
 RT p = t.hw()*t.hw();

 RT det =   a * ( f*(k*p - l*o) + j*(h*o - g*p) + n*(g*l - h*k) )
          - e * ( b*(k*p - l*o) + j*(d*o - c*p) + n*(c*l - d*k) )
          + i * ( b*(g*p - h*o) + f*(d*o - c*p) + n*(c*h - d*g) )
          - m * ( b*(g*l - h*k) + f*(d*k - c*l) + j*(c*h - d*g) );

 // CGAL_kernel_check( det == CGAL_det4x4_by_formula( a, b, c, d,
 //                                                   e, f, g, h,
 //                                                   i, j, k, l,
 //                                                   m, n, o, p ) );
 


 if ( det == RT(0)   )
 {
    return CGAL_ON;
 }
 else
 {
    if (CGAL_ordertype(q,r,s) == CGAL_CLOCKWISE)
    {
        det = -det;
    }
    return (det > RT(0)   ) ? CGAL_INSIDE : CGAL_OUTSIDE;
 }
}

template <class FT, class RT>
CGAL_Side
CGAL_in_oriented_circle( const CGAL_PointH2<FT,RT>& q,
                         const CGAL_PointH2<FT,RT>& r,
                         const CGAL_PointH2<FT,RT>& s,
                         const CGAL_PointH2<FT,RT>& t)
{
 
 CGAL_kernel_precondition(   q.is_defined() && r.is_defined()
                          && s.is_defined() && t.is_defined() );
 CGAL_nondegeneracy_precondition( ! CGAL_collinear(q,r,s) );

 // compute sign of      |qx  qy  qx^2+qy^2  1 |   | a b c d |
 //                      |      --  r  --      | = | e f g h |
 //     determinant      |      --  s  --      | = | i j k l |
 //                      |      --  t  --      |   | m n o p |
 //           where

 RT a = q.hx()*q.hw();
 RT b = q.hy()*q.hw();
 RT c = q.hx()*q.hx() + q.hy()*q.hy();
 RT d = q.hw()*q.hw();

 RT e = r.hx()*r.hw();
 RT f = r.hy()*r.hw();
 RT g = r.hx()*r.hx() + r.hy()*r.hy();
 RT h = r.hw()*r.hw();

 RT i = s.hx()*s.hw();
 RT j = s.hy()*s.hw();
 RT k = s.hx()*s.hx() + s.hy()*s.hy();
 RT l = s.hw()*s.hw();

 RT m = t.hx()*t.hw();
 RT n = t.hy()*t.hw();
 RT o = t.hx()*t.hx() + t.hy()*t.hy();
 RT p = t.hw()*t.hw();

 RT det =   a * ( f*(k*p - l*o) + j*(h*o - g*p) + n*(g*l - h*k) )
          - e * ( b*(k*p - l*o) + j*(d*o - c*p) + n*(c*l - d*k) )
          + i * ( b*(g*p - h*o) + f*(d*o - c*p) + n*(c*h - d*g) )
          - m * ( b*(g*l - h*k) + f*(d*k - c*l) + j*(c*h - d*g) );

 // CGAL_kernel_check( det == CGAL_det4x4_by_formula( a, b, c, d,
 //                                                   e, f, g, h,
 //                                                   i, j, k, l,
 //                                                   m, n, o, p ) );
 


 if ( det == RT(0)   )
 {
    return CGAL_ON;
 }
 else
 {
    return (det > RT(0)   ) ? CGAL_INSIDE : CGAL_OUTSIDE;
 }
}
 
template <class FT, class RT>
bool
CGAL_collinear_between( const CGAL_PointH2<FT,RT>& p,
                        const CGAL_PointH2<FT,RT>& q,
                        const CGAL_PointH2<FT,RT>& r )
{
 CGAL_kernel_precondition( p.is_defined() && q.is_defined() && r.is_defined() );
 return (  CGAL_lexicographically_xy_smaller_or_equal(p, q )
        && CGAL_lexicographically_xy_smaller_or_equal(q, r ) );
}

template <class FT, class RT>
bool
CGAL_between( const CGAL_PointH2<FT,RT>& p,
              const CGAL_PointH2<FT,RT>& q,
              const CGAL_PointH2<FT,RT>& r )
{
 CGAL_kernel_precondition( p.is_defined() && q.is_defined() && r.is_defined() );
 if ( CGAL_collinear(p,q,r) )
 {
    return CGAL_collinear_between(p,q,r);
 }
 else
 {
    return false;
 }
}
 
template <class FT, class RT>
bool
CGAL_x_equal( const CGAL_PointH2<FT,RT>& p,
              const CGAL_PointH2<FT,RT>& q )
{
 CGAL_kernel_precondition( p.is_defined() && q.is_defined() );
 return ( p.hx()*q.hw() == q.hx()*p.hw() );
}

template <class FT, class RT>
bool
CGAL_y_equal( const CGAL_PointH2<FT,RT>& p,
              const CGAL_PointH2<FT,RT>& q )
{
 CGAL_kernel_precondition( p.is_defined() && q.is_defined() );
 return ( p.hy()*q.hw() == q.hy()*p.hw() );
}
 
template <class FT, class RT>
CGAL_Side
CGAL__where_wrt_L_wedge( const CGAL_PointH2<FT,RT>& p,
                         const CGAL_PointH2<FT,RT>& q )
{
 CGAL_kernel_precondition( p.is_defined() && q.is_defined() );
 int xs = CGAL_sign( q.hx()*p.hw() - p.hx()*q.hw() );  // sign( qx - px )
 int ys = CGAL_sign( q.hy()*p.hw() - p.hy()*q.hw() );  // sign( qy - py )

 if (( xs == -1 ) || ( ys == -1 ))
 {
    return CGAL_OUTSIDE;
 }
 if (( xs ==  1 ) && ( ys ==  1 ))
 {
    return CGAL_INSIDE;
 }
 return CGAL_ON;
}
 


#endif // CGAL_PREDICATES_ON_POINTSH2_H
