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
// source        : basic_constructionsH3.fw
// file          : include/CGAL/basic_constructionsH3.h
// package       : H3 (2.12)
// revision      : 2.12
// revision_date : 16 Aug 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_BASIC_CONSTRUCTIONSH3_H
#define CGAL_BASIC_CONSTRUCTIONSH3_H

CGAL_BEGIN_NAMESPACE

template <class FT, class RT>
PointH3<FT,RT>
_projection(const PointH3<FT,RT>& p, const PlaneH3<FT,RT>& pl)
{
  if ( pl.has_on(p) ) return p;

  RT A = pl.a();
  RT B = pl.b();
  RT C = pl.c();
  RT D = pl.d();
  RT phx = p.hx();
  RT phy = p.hy();
  RT phz = p.hz();
  RT phw = p.hw();

  RT num = A * phx  +  B * phy  +  C * phz  +  D * phw;
  RT den = A * A    +  B * B    +  C * C;

  return PointH3<FT,RT>( num * A  -  den * phx,
                              num * B  -  den * phy,
                              num * C  -  den * phz,
                             -den );
}

template <class FT, class RT>
PointH3<FT,RT>
midpoint( const PointH3<FT,RT>& p,
               const PointH3<FT,RT>& q )
{
  RT phw = p.hw();
  RT qhw = q.hw();
  return PointH3<FT,RT>( p.hx()*qhw + q.hx()*phw,
                              p.hy()*qhw + q.hy()*phw,
                              p.hz()*qhw + q.hz()*phw,
                              RT(2) * phw * qhw );
}


template <class FT, class RT>
PointH3<FT,RT>
gp_linear_intersection(const PlaneH3<FT,RT> &f,
                       const PlaneH3<FT,RT> &g,
                       const PlaneH3<FT,RT> &h)
{
  return PointH3<FT,RT>(
                      det3x3_by_formula(-f.d(), f.b(), f.c(),
                                        -g.d(), g.b(), g.c(),
                                        -h.d(), h.b(), h.c()),
                      det3x3_by_formula( f.a(),-f.d(), f.c(),
                                         g.a(),-g.d(), g.c(),
                                         h.a(),-h.d(), h.c()),
                      det3x3_by_formula( f.a(), f.b(),-f.d(),
                                         g.a(), g.b(),-g.d(),
                                         h.a(), h.b(),-h.d()),
                      det3x3_by_formula( f.a(), f.b(), f.c(),
                                         g.a(), g.b(), g.c(),
                                         h.a(), h.b(), h.c()));
}


template <class FT, class RT>
CGAL_KERNEL_INLINE
FT
squared_distance( PointH3<FT,RT> const& p, PointH3<FT,RT> const& q)
{ return (p-q)*(p-q); }


template <class FT, class RT>
inline
PlaneH3<FT,RT>
bisector( PointH3<FT,RT> const& p,
          PointH3<FT,RT> const& q)
{ return PlaneH3<FT,RT>( midpoint(p,q), q-p); }

template <class FT, class RT>
PointH3<FT,RT>
circumcenter( PointH3<FT,RT> const& p,
              PointH3<FT,RT> const& q,
              PointH3<FT,RT> const& r,
              PointH3<FT,RT> const& s)
{
  RT phw( p.hw() );
  RT qhw( q.hw() );
  RT rhw( r.hw() );
  RT shw( s.hw() );

  RT phx( p.hx() );
  RT phy( p.hy() );
  RT phz( p.hz() );
  RT qhx( q.hx() );
  RT qhy( q.hy() );
  RT qhz( q.hz() );
  RT rhx( r.hx() );
  RT rhy( r.hy() );
  RT rhz( r.hz() );
  RT shx( s.hx() );
  RT shy( s.hy() );
  RT shz( s.hz() );

  RT pssq( phx*phx + phy*phy + phz*phz );
  RT qssq( qhx*qhx + qhy*qhy + qhz*qhz );
  RT rssq( rhx*rhx + rhy*rhy + rhz*rhz );
  RT sssq( shx*shx + shy*shy + shz*shz );

  phx *= phw;
  phy *= phw;
  phz *= phw;
  phw *= phw;
  qhx *= qhw;
  qhy *= qhw;
  qhz *= qhw;
  qhw *= qhw;
  rhx *= rhw;
  rhy *= rhw;
  rhz *= rhw;
  rhw *= rhw;
  shx *= shw;
  shy *= shw;
  shz *= shw;
  shw *= shw;

  RT chx =  det4x4_by_formula(phy, phz, pssq, phw,
                                   qhy, qhz, qssq, qhw,
                                   rhy, rhz, rssq, rhw,
                                   shy, shz, sssq, shw );
  RT chy =  det4x4_by_formula(phx, phz, pssq, phw,
                                   qhx, qhz, qssq, qhw,
                                   rhx, rhz, rssq, rhw,
                                   shx, shz, sssq, shw );
  RT chz =  det4x4_by_formula(phx, phy, pssq, phw,
                                   qhx, qhy, qssq, qhw,
                                   rhx, rhy, rssq, rhw,
                                   shx, shy, sssq, shw );
  RT chw =  det4x4_by_formula(phx, phy, phz, phw,
                                   qhx, qhy, qhz, qhw,
                                   rhx, rhy, rhz, rhw,
                                   shx, shy, shz, shw );

 return PointH3<FT,RT>( chx, -chy, chz, RT(2)*chw);
}
template <class FT, class RT>
CGAL_KERNEL_INLINE
PointH3<FT,RT>
circumcenter( PointH3<FT,RT> const& p,
              PointH3<FT,RT> const& q,
              PointH3<FT,RT> const& r)
{
  return gp_linear_intersection( PlaneH3<FT,RT>(p,q,r),
                                 bisector(p,q),
                                 bisector(p,r));
}

CGAL_END_NAMESPACE


#endif // CGAL_BASIC_CONSTRUCTIONSH3_H
