// Copyright (c) 1999  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/H2/include/CGAL/Homogeneous/basic_constructionsH2.h,v $
// $Revision: 1.7 $ $Date: 2003/10/28 17:57:11 $
// $Name: current_submission $
//
// Author(s)     : Sven Schoenherr
//                 Stefan Schirra
 

#ifndef CGAL_BASIC_CONSTRUCTIONSH2_H
#define CGAL_BASIC_CONSTRUCTIONSH2_H

#include <CGAL/Homogeneous/PointH2.h>
#include <CGAL/Homogeneous/LineH2.h>
#include <CGAL/Homogeneous/TriangleH2.h>

CGAL_BEGIN_NAMESPACE

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
PointH2<R>
gp_linear_intersection(const LineH2<R>& l1, const LineH2<R>& l2)
{
  return PointH2<R>( l1.b()*l2.c() - l2.b()*l1.c(),
                     l2.a()*l1.c() - l1.a()*l2.c(),
                     l1.a()*l2.b() - l2.a()*l1.b() );
}

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
LineH2<R>
bisector( const PointH2<R>& p, const PointH2<R>& q )
{
  typedef typename R::RT RT;

 // Bisector equation is based on equation
 // ( X - p.x())^2 + (Y - p.y())^2 == ( X - q.x())^2 + (Y - q.y())
 // and x() = hx()/hw() ...

  const RT & phx = p.hx();
  const RT & phy = p.hy();
  const RT & phw = p.hw();
  const RT & qhx = q.hx();
  const RT & qhy = q.hy();
  const RT & qhw = q.hw();

  RT a = RT(2) * ( phx*phw*qhw*qhw - qhx*qhw*phw*phw );
  RT b = RT(2) * ( phy*phw*qhw*qhw - qhy*qhw*phw*phw );
  RT c = qhx*qhx*phw*phw + qhy*qhy*phw*phw - phx*phx*qhw*qhw - phy*phy*qhw*qhw;

  return LineH2<R>( a, b, c );
}

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
typename R::FT
squared_distance( const PointH2<R>& p, const PointH2<R>& q )
{
  typedef typename R::RT RT;
  typedef typename R::FT FT;

  const RT & phx = p.hx();
  const RT & phy = p.hy();
  const RT & phw = p.hw();
  const RT & qhx = q.hx();
  const RT & qhy = q.hy();
  const RT & qhw = q.hw();

  RT sq_dist_numerator =
          phx * phx * qhw * qhw
    - RT(2) * phx * qhx * phw * qhw
    +     qhx * qhx * phw * phw

    +     phy * phy * qhw * qhw
    - RT(2) * phy * qhy * phw * qhw
    +     qhy * qhy * phw * phw ;

  RT sq_dist_denominator = qhw * qhw * phw * phw ;

  return FT( sq_dist_numerator ) / FT( sq_dist_denominator );
}

template < class R >
CGAL_KERNEL_MEDIUM_INLINE
PointH2<R>
midpoint( PointH2<R> const& p, PointH2<R> const& q )
{
    typedef typename R::RT RT;
    const RT phw( p.hw());
    const RT qhw( q.hw());

    RT hx( p.hx()*qhw + q.hx()*phw);
    RT hy( p.hy()*qhw + q.hy()*phw);
    RT hw( phw * qhw * RT( 2));

    return( PointH2<R>( hx, hy, hw));
}

template < class R >
CGAL_KERNEL_MEDIUM_INLINE
PointH2<R>
centroid( const PointH2<R>& p,
          const PointH2<R>& q,
          const PointH2<R>& r )
{
   typedef typename R::RT  RT;
   const RT phw(p.hw());
   const RT qhw(q.hw());
   const RT rhw(r.hw());
   RT hx(p.hx()*qhw*rhw + q.hx()*phw*rhw + r.hx()*phw*qhw);
   RT hy(p.hy()*qhw*rhw + q.hy()*phw*rhw + r.hy()*phw*qhw);
   RT hw( phw*qhw*rhw * 3);
   return PointH2<R>(hx, hy, hw);
}

template < class R >
CGAL_KERNEL_MEDIUM_INLINE
PointH2<R>
centroid( const PointH2<R>& p,
          const PointH2<R>& q,
          const PointH2<R>& r,
          const PointH2<R>& s )
{
   typedef typename R::RT  RT;
   const RT phw(p.hw());
   const RT qhw(q.hw());
   const RT rhw(r.hw());
   const RT shw(s.hw());
   RT hx(p.hx()*qhw*rhw*shw + q.hx()*phw*rhw*shw + r.hx()*phw*qhw*shw 
         + s.hx()*phw*qhw*rhw);
   RT hy(p.hy()*qhw*rhw*shw + q.hy()*phw*rhw*shw + r.hy()*phw*qhw*shw
         + s.hy()*phw*qhw*rhw);
   RT hw( phw*qhw*rhw*shw * 4);
   return PointH2<R>(hx, hy, hw);
}

template <class R>
CGAL_KERNEL_LARGE_INLINE
PointH2<R>
circumcenter( const PointH2<R>& p,
              const PointH2<R>& q,
              const PointH2<R>& r )
{
  typedef typename R::RT RT;
  RT phx = p.hx();
  RT phy = p.hy();
  RT phw = p.hw();
  RT qhx = q.hx();
  RT qhy = q.hy();
  RT qhw = q.hw();
  RT rhx = r.hx();
  RT rhy = r.hy();
  RT rhw = r.hw();

#ifdef CGAL_EXPANDED_CIRCUMCENTER_COMPUTATION
  RT vvx =
     ( qhy*qhw*phw*phw - phy*phw*qhw*qhw )
    *( phx*phx*rhw*rhw + phy*phy*rhw*rhw - rhx*rhx*phw*phw - rhy*rhy*phw*phw )
  -  ( rhy*rhw*phw*phw - phy*phw*rhw*rhw )
    *( phx*phx*qhw*qhw + phy*phy*qhw*qhw - qhx*qhx*phw*phw - qhy*qhy*phw*phw );

  RT vvy =
  -  ( qhx*qhw*phw*phw - phx*phw*qhw*qhw )
    *( phx*phx*rhw*rhw + phy*phy*rhw*rhw - rhx*rhx*phw*phw - rhy*rhy*phw*phw )
  +  ( rhx*rhw*phw*phw - phx*phw*rhw*rhw )
    *( phx*phx*qhw*qhw + phy*phy*qhw*qhw - qhx*qhx*phw*phw - qhy*qhy*phw*phw );

  RT vvw = RT(2) *
   (  ( qhx*qhw*phw*phw - phx*phw*qhw*qhw )
     *( rhy*rhw*phw*phw - phy*phw*rhw*rhw )
   -  ( rhx*rhw*phw*phw - phx*phw*rhw*rhw )
     *( qhy*qhw*phw*phw - phy*phw*qhw*qhw ) );
#endif // CGAL_EXPANDED_CIRCUMCENTER_COMPUTATION

  RT qy_py = ( qhy*qhw*phw*phw - phy*phw*qhw*qhw );
  RT qx_px = ( qhx*qhw*phw*phw - phx*phw*qhw*qhw );
  RT rx_px = ( rhx*rhw*phw*phw - phx*phw*rhw*rhw );
  RT ry_py = ( rhy*rhw*phw*phw - phy*phw*rhw*rhw );

  RT px2_py2_rx2_ry_2 =
     phx*phx*rhw*rhw + phy*phy*rhw*rhw - rhx*rhx*phw*phw - rhy*rhy*phw*phw ;
  RT px2_py2_qx2_qy_2 =
     phx*phx*qhw*qhw + phy*phy*qhw*qhw - qhx*qhx*phw*phw - qhy*qhy*phw*phw ;

  RT vvx = qy_py * px2_py2_rx2_ry_2 - ry_py * px2_py2_qx2_qy_2;
  RT vvy = rx_px * px2_py2_qx2_qy_2 - qx_px * px2_py2_rx2_ry_2;
  RT vvw = RT(2) * ( qx_px * ry_py - rx_px * qy_py );

  return PointH2<R>( vvx, vvy, vvw );
}

template <class R>
CGAL_KERNEL_INLINE
typename R::FT
squared_radius( const PointH2<R>& p,
                const PointH2<R>& q,
                const PointH2<R>& r )
{
  return squared_distance(p, circumcenter(p, q, r));
}

template <class R>
CGAL_KERNEL_INLINE
typename R::FT
squared_radius( const PointH2<R>& p,
                const PointH2<R>& q )
{
  typedef typename R::FT FT;
  return squared_distance(p, q)/FT(4);
}

template <class R>
CGAL_KERNEL_LARGE_INLINE
typename R::FT
area(const PointH2<R>& p, const PointH2<R>& q, const PointH2<R>& r)
{
    typedef typename R::Vector_2  Vector_2;
    typedef typename R::RT        RT;
    typedef typename R::FT        FT;

    Vector_2 v1 = q - p;
    Vector_2 v2 = r - p;

    RT num = v1.hx()*v2.hy() - v2.hx()*v1.hy();
    RT den = RT(2) * v1.hw() * v2.hw();
    return FT(num)/FT(den);
}

/*  I believe it's undocumented, so I comment it.
template <class R>
inline
typename R::FT
area(const TriangleH2<R>& t)
{
    return area(t.vertex(0), t.vertex(1), t.vertex(2));
}
*/

CGAL_END_NAMESPACE

#endif // CGAL_BASIC_CONSTRUCTIONSH2_H
