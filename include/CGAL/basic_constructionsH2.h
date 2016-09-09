// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// source        : basic_constructionsH2.fw
// file          : include/CGAL/basic_constructionsH2.h
// package       : H2 (2.12)
// revision      : 2.12
// revision_date : 03 Aug 2000 
// author(s)     : Sven Schoenherr
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_BASIC_CONSTRUCTIONSH2_H
#define CGAL_BASIC_CONSTRUCTIONSH2_H

#include <CGAL/PointH2.h>
#include <CGAL/LineH2.h>
#include <CGAL/TriangleH2.h>

CGAL_BEGIN_NAMESPACE

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
PointH2<FT,RT>
gp_linear_intersection(const LineH2<FT,RT>& l1, const LineH2<FT,RT>& l2)
{
  return PointH2<FT,RT>( l1.b()*l2.c() - l2.b()*l1.c(),
                         l2.a()*l1.c() - l1.a()*l2.c(),
                         l1.a()*l2.b() - l2.a()*l1.b() );
}

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
LineH2<FT,RT>
bisector( const PointH2<FT,RT>& p, const PointH2<FT,RT>& q )
{
 // Bisector equation is based on equation
 // ( X - p.x())^2 + (Y - p.y())^2 == ( X - q.x())^2 + (Y - q.y())
 // and x() = hx()/hw() ...

  RT phx = p.hx();
  RT phy = p.hy();
  RT phw = p.hw();
  RT qhx = q.hx();
  RT qhy = q.hy();
  RT qhw = q.hw();

  RT a = RT(2) * ( qhx*qhw*phw*phw - phx*phw*qhw*qhw );
  RT b = RT(2) * ( qhy*qhw*phw*phw - phy*phw*qhw*qhw );
  RT c = phx*phx*qhw*qhw + phy*phy*qhw*qhw - qhx*qhx*phw*phw - qhy*qhy*phw*phw;

  return LineH2<FT,RT>( a, b, c );
}

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
FT
squared_distance( const PointH2<FT,RT>& p, const PointH2<FT,RT>& q )
{
  const RT phx = p.hx();
  const RT phy = p.hy();
  const RT phw = p.hw();
  const RT qhx = q.hx();
  const RT qhy = q.hy();
  const RT qhw = q.hw();

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

template < class FT, class RT >
CGAL_KERNEL_MEDIUM_INLINE
PointH2<FT,RT>
midpoint( PointH2<FT,RT> const& p, PointH2<FT,RT> const& q )
{
    const RT phw( p.hw());
    const RT qhw( q.hw());

    RT hx( p.hx()*qhw + q.hx()*phw);
    RT hy( p.hy()*qhw + q.hy()*phw);
    RT hw( phw * qhw * RT( 2));

    return( PointH2<FT,RT>( hx, hy, hw));
}


template <class FT, class RT>
CGAL_KERNEL_LARGE_INLINE
PointH2<FT,RT>
circumcenter( const PointH2<FT,RT>& p,
              const PointH2<FT,RT>& q,
              const PointH2<FT,RT>& r )
{
  RT phx = p.hx();
  RT phy = p.hy();
  RT phw = p.hw();
  RT qhx = q.hx();
  RT qhy = q.hy();
  RT qhw = q.hw();
  RT rhx = r.hx();
  RT rhy = r.hy();
  RT rhw = r.hw();

#ifdef EXPANDED_CIRCUMCENTER_COMPUTATION   /* strange flag -- XXX */
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
#endif // EXPANDED_CIRCUMCENTER_COMPUTATION

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

  return PointH2<FT,RT>( vvx, vvy, vvw );
}

template <class FT, class RT>
FT
area(const TriangleH2<FT,RT>& t)
{
  RT num = determinant_3x3_by_formula(
               t.vertex(0).hx(), t.vertex(0).hy(), t.vertex(0).hw(),
               t.vertex(1).hx(), t.vertex(1).hy(), t.vertex(1).hw(),
               t.vertex(2).hx(), t.vertex(2).hy(), t.vertex(2).hw() );
  RT den = t.vertex(0).hw() * t.vertex(1).hw() * t.vertex(2).hw();
  return FT(num) / FT(den);
}

CGAL_END_NAMESPACE


#endif // CGAL_BASIC_CONSTRUCTIONSH2_H
