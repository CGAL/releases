
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
 RT phx = p.hx();
 RT phw = p.hw();
 RT qhx = q.hx();
 RT qhw = q.hw();

 RT pV = phx * qhw;
 RT qV = qhx * phw;
 if ( pV > qV )
 {
    return false;
 }
 else if ( pV < qV )
 {
    return true;
 }
 RT phy = p.hy();
 RT qhy = q.hy();

 pV = phy * qhw;
 qV = qhy * phw;
 return ( pV <= qV );
}


template < class FT, class RT>
bool
CGAL_lexicographically_xy_smaller(const CGAL_PointH2<FT,RT>& p,
                                  const CGAL_PointH2<FT,RT>& q)
{
 RT phx = p.hx();
 RT phw = p.hw();
 RT qhx = q.hx();
 RT qhw = q.hw();

 RT pV = phx * qhw;
 RT qV = qhx * phw;
 if ( pV > qV )
 {
    return false;
 }
 else if ( pV < qV )
 {
    return true;
 }
 RT phy = p.hy();
 RT qhy = q.hy();

 pV = phy * qhw;
 qV = qhy * phw;
 return ( pV < qV );
}

template < class FT, class RT>
CGAL_Comparison_result
CGAL_compare_x(const CGAL_PointH2<FT,RT>& p,
               const CGAL_PointH2<FT,RT>& q)
{
 RT phx = p.hx();
 RT phw = p.hw();
 RT qhx = q.hx();
 RT qhw = q.hw();
 RT com = phx * qhw - qhx * phw;
 if ( com < RT(0) )
 {
    return CGAL_SMALLER;
 }
 else if ( com > RT(0) )
 {
    return CGAL_LARGER;
 }
 return CGAL_EQUAL;
}


template < class FT, class RT>
CGAL_Comparison_result
CGAL_compare_y(const CGAL_PointH2<FT,RT>& p,
               const CGAL_PointH2<FT,RT>& q)
{
 RT phy = p.hy();
 RT phw = p.hw();
 RT qhy = q.hy();
 RT qhw = q.hw();
 RT com = phy * qhw - qhy * phw;
 if ( com < RT(0) )
 {
    return CGAL_SMALLER;
 }
 else if ( com > RT(0) )
 {
    return CGAL_LARGER;
 }
 return CGAL_EQUAL;
}


template < class FT, class RT>
CGAL_Orientation
CGAL_orientation( const CGAL_PointH2<FT,RT>& p,
                const CGAL_PointH2<FT,RT>& q,
                const CGAL_PointH2<FT,RT>& r)
{
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
 return (CGAL_orientation(p,q,r) == CGAL_COUNTERCLOCKWISE);
}


template < class FT, class RT>
bool
CGAL_rightturn( const CGAL_PointH2<FT,RT>& p,
                const CGAL_PointH2<FT,RT>& q,
                const CGAL_PointH2<FT,RT>& r)
{
 return (CGAL_orientation(p,q,r) == CGAL_CLOCKWISE);
}


template < class FT, class RT>
bool
CGAL_collinear( const CGAL_PointH2<FT,RT>& p,
                const CGAL_PointH2<FT,RT>& q,
                const CGAL_PointH2<FT,RT>& r)
{
 return (CGAL_orientation(p,q,r) == CGAL_COLLINEAR);
}
template <class FT, class RT>
CGAL_Bounded_side
CGAL_side_of_bounded_circle( const CGAL_PointH2<FT,RT>& q,
                             const CGAL_PointH2<FT,RT>& r,
                             const CGAL_PointH2<FT,RT>& s,
                             const CGAL_PointH2<FT,RT>& t)
{
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
    return CGAL_ON_BOUNDARY;
 }
 else
 {
    if (CGAL_orientation(q,r,s) == CGAL_CLOCKWISE)
    {
        det = -det;
    }
    return (det > RT(0)   ) ? CGAL_ON_BOUNDED_SIDE : CGAL_ON_UNBOUNDED_SIDE;
 }
}

template <class FT, class RT>
CGAL_Oriented_side
CGAL_side_of_oriented_circle( const CGAL_PointH2<FT,RT>& q,
                              const CGAL_PointH2<FT,RT>& r,
                              const CGAL_PointH2<FT,RT>& s,
                              const CGAL_PointH2<FT,RT>& t)
{
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
    return CGAL_ON_ORIENTED_BOUNDARY;
 }
 else
 {
    return (det > RT(0)   ) ? CGAL_ON_POSITIVE_SIDE : CGAL_ON_NEGATIVE_SIDE;
 }
}
template <class FT, class RT>
bool
CGAL_collinear_between( const CGAL_PointH2<FT,RT>& p,
                        const CGAL_PointH2<FT,RT>& q,
                        const CGAL_PointH2<FT,RT>& r )
{
 RT phx = p.hx();
 RT phw = p.hw();
 RT qhx = q.hx();
 RT qhw = q.hw();
 RT rhx = r.hx();
 RT rhw = r.hw();

 if ( phx * rhw != rhx * phw )
 {
    return (   ( phx * qhw < qhx * phw)
            &&( qhx * rhw < rhx * qhw))
         ||(   ( phx * qhw > qhx * phw)
            &&( qhx * rhw > rhx * qhw));
 }
 else
 {
    RT phy = p.hy();
    RT qhy = q.hy();
    RT rhy = r.hy();
    return (   ( phy * qhw < qhy * phw)
            &&( qhy * rhw < rhy * qhw))
         ||(   ( phy * qhw > qhy * phw)
            &&( qhy * rhw > rhy * qhw));
 }
}


template <class FT, class RT>
bool
CGAL_between( const CGAL_PointH2<FT,RT>& p,
              const CGAL_PointH2<FT,RT>& q,
              const CGAL_PointH2<FT,RT>& r )
{
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
 return ( p.hx()*q.hw() == q.hx()*p.hw() );
}

template <class FT, class RT>
bool
CGAL_y_equal( const CGAL_PointH2<FT,RT>& p,
              const CGAL_PointH2<FT,RT>& q )
{
 return ( p.hy()*q.hw() == q.hy()*p.hw() );
}
template <class FT, class RT>
CGAL_Oriented_side
CGAL__where_wrt_L_wedge( const CGAL_PointH2<FT,RT>& p,
                         const CGAL_PointH2<FT,RT>& q )
{
 int xs = CGAL_sign( q.hx()*p.hw() - p.hx()*q.hw() );  // sign( qx - px )
 int ys = CGAL_sign( q.hy()*p.hw() - p.hy()*q.hw() );  // sign( qy - py )

 if (( xs == -1 ) || ( ys == -1 ))
 {
    return CGAL_ON_NEGATIVE_SIDE;
 }
 if (( xs ==  1 ) && ( ys ==  1 ))
 {
    return CGAL_ON_POSITIVE_SIDE;
 }
 return CGAL_ON_ORIENTED_BOUNDARY;
}


#endif // CGAL_PREDICATES_ON_POINTSH2_H
