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
// release       : CGAL-2.1
// release_date  : 2000, January 11
// 
// source        : distance_predicatesH3.fw
// file          : include/CGAL/distance_predicatesH3.h
// package       : H3 (2.3.7)
// revision      : 2.3.7
// revision_date : 03 Dec 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_DISTANCE_PREDICATESH3_H
#define CGAL_DISTANCE_PREDICATESH3_H

CGAL_BEGIN_NAMESPACE

template <class FT, class RT>
Comparison_result
cmp_dist_to_point(const PointH3<FT,RT>& ,
                  const PointH3<FT,RT>& ,
                  const PointH3<FT,RT>& );

template <class FT, class RT>
bool
has_larger_dist_to_point(const PointH3<FT,RT>& ,
                         const PointH3<FT,RT>& ,
                         const PointH3<FT,RT>& );

template <class FT, class RT>
bool
has_smaller_dist_to_point(const PointH3<FT,RT>& ,
                          const PointH3<FT,RT>& ,
                          const PointH3<FT,RT>& );

template <class FT, class RT>
Comparison_result
cmp_signed_dist_to_plane(const PlaneH3<FT,RT>& ,
                         const PointH3<FT,RT>& ,
                         const PointH3<FT,RT>& );

template <class FT, class RT>
bool
has_larger_signed_dist_to_plane(const PlaneH3<FT,RT>& ,
                                const PointH3<FT,RT>& ,
                                const PointH3<FT,RT>& );

template <class FT, class RT>
bool
has_smaller_signed_dist_to_plane(const PlaneH3<FT,RT>&,
                                 const PointH3<FT,RT>& ,
                                 const PointH3<FT,RT>& );

template <class FT, class RT>
Comparison_result
cmp_signed_dist_to_plane(const PointH3<FT,RT>& ,
                         const PointH3<FT,RT>& ,
                         const PointH3<FT,RT>& ,
                         const PointH3<FT,RT>& ,
                         const PointH3<FT,RT>& );

template <class FT, class RT>
bool
has_larger_signed_dist_to_plane(const PointH3<FT,RT>& ,
                                const PointH3<FT,RT>& ,
                                const PointH3<FT,RT>& ,
                                const PointH3<FT,RT>& ,
                                const PointH3<FT,RT>& );

template <class FT, class RT>
bool
has_smaller_signed_dist_to_plane(const PointH3<FT,RT>& ,
                                 const PointH3<FT,RT>& ,
                                 const PointH3<FT,RT>& ,
                                 const PointH3<FT,RT>& ,
                                 const PointH3<FT,RT>& );

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
cmp_dist_to_point(const PointH3<FT,RT>& p,
                  const PointH3<FT,RT>& q,
                  const PointH3<FT,RT>& r)
{
  const RT phx = p.hx();
  const RT phy = p.hy();
  const RT phz = p.hz();
  const RT phw = p.hw();
  const RT qhx = q.hx();
  const RT qhy = q.hy();
  const RT qhz = q.hz();
  const RT qhw = q.hw();
  const RT rhx = r.hx();
  const RT rhy = r.hy();
  const RT rhz = r.hz();
  const RT rhw = r.hw();
  const RT RT0 = RT(0);
  const RT RT2 = RT(2);

  RT dosd =   // difference of squared distances

    rhw*rhw * (         phw * ( qhx*qhx + qhy*qhy + qhz*qhz )
                - RT2 * qhw * ( phx*qhx + phy*qhy + phz*qhz )
              )
  - qhw*qhw * (         phw * ( rhx*rhx + rhy*rhy + rhz*rhz )
                - RT2 * rhw * ( phx*rhx + phy*rhy + phz*rhz )
              );

  if ( RT0 < dosd )
  { return LARGER; }
  else
  { return (dosd < RT0) ? SMALLER : EQUAL; }
}

template < class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
has_larger_dist_to_point(const PointH3<FT,RT>& p,
                         const PointH3<FT,RT>& q,
                         const PointH3<FT,RT>& r)
{
  const RT phx = p.hx();
  const RT phy = p.hy();
  const RT phz = p.hz();
  const RT phw = p.hw();
  const RT qhx = q.hx();
  const RT qhy = q.hy();
  const RT qhz = q.hz();
  const RT qhw = q.hw();
  const RT rhx = r.hx();
  const RT rhy = r.hy();
  const RT rhz = r.hz();
  const RT rhw = r.hw();
  const RT RT0 = RT(0);
  const RT RT2 = RT(2);

  RT dosd =   // difference of squared distances

    rhw*rhw * (         phw * ( qhx*qhx + qhy*qhy + qhz*qhz )
                - RT2 * qhw * ( phx*qhx + phy*qhy + phz*qhz )
              )
  - qhw*qhw * (         phw * ( rhx*rhx + rhy*rhy + rhz*rhz )
                - RT2 * rhw * ( phx*rhx + phy*rhy + phz*rhz )
              );

  return ( RT0 < dosd );
}

template < class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
has_smaller_dist_to_point(const PointH3<FT,RT>& p,
                          const PointH3<FT,RT>& q,
                          const PointH3<FT,RT>& r)
{
  const RT phx = p.hx();
  const RT phy = p.hy();
  const RT phz = p.hz();
  const RT phw = p.hw();
  const RT qhx = q.hx();
  const RT qhy = q.hy();
  const RT qhz = q.hz();
  const RT qhw = q.hw();
  const RT rhx = r.hx();
  const RT rhy = r.hy();
  const RT rhz = r.hz();
  const RT rhw = r.hw();
  const RT RT0 = RT(0);
  const RT RT2 = RT(2);

  RT dosd =   // difference of squared distances

    rhw*rhw * (         phw * ( qhx*qhx + qhy*qhy + qhz*qhz )
                - RT2 * qhw * ( phx*qhx + phy*qhy + phz*qhz )
              )
  - qhw*qhw * (         phw * ( rhx*rhx + rhy*rhy + rhz*rhz )
                - RT2 * rhw * ( phx*rhx + phy*rhy + phz*rhz )
              );

  return ( dosd < RT0 );
}

template < class FT, class RT>
CGAL_KERNEL_INLINE
Comparison_result
cmp_signed_dist_to_plane(const PlaneH3<FT,RT>& pl,
                         const PointH3<FT,RT>& p,
                         const PointH3<FT,RT>& q)
{
  const RT pla = pl.a();
  const RT plb = pl.b();
  const RT plc = pl.c();
  const RT phx = p.hx();
  const RT phy = p.hy();
  const RT phz = p.hz();
  const RT phw = p.hw();
  const RT qhx = q.hx();
  const RT qhy = q.hy();
  const RT qhz = q.hz();
  const RT qhw = q.hw();
  const RT RT0 = RT(0);

  RT scaled_dist_p_minus_scaled_dist_q =
      pla*( phx*qhw - qhx*phw )
    + plb*( phy*qhw - qhy*phw )
    + plc*( phz*qhw - qhz*phw );



  if ( scaled_dist_p_minus_scaled_dist_q < RT0 )
  { return SMALLER; }
  else
  { return (RT0 < scaled_dist_p_minus_scaled_dist_q ) ?  LARGER : EQUAL;}
}

template <class FT, class RT>
bool
has_larger_signed_dist_to_plane(const PlaneH3<FT,RT>& pl,
                                const PointH3<FT,RT>& p,
                                const PointH3<FT,RT>& q )
{
  const RT pla = pl.a();
  const RT plb = pl.b();
  const RT plc = pl.c();
  const RT phx = p.hx();
  const RT phy = p.hy();
  const RT phz = p.hz();
  const RT phw = p.hw();
  const RT qhx = q.hx();
  const RT qhy = q.hy();
  const RT qhz = q.hz();
  const RT qhw = q.hw();
  const RT RT0 = RT(0);

  RT scaled_dist_p_minus_scaled_dist_q =
      pla*( phx*qhw - qhx*phw )
    + plb*( phy*qhw - qhy*phw )
    + plc*( phz*qhw - qhz*phw );


  return ( RT0 < scaled_dist_p_minus_scaled_dist_q );
}

template <class FT, class RT>
bool
has_smaller_signed_dist_to_plane(const PlaneH3<FT,RT>& pl,
                                 const PointH3<FT,RT>& p,
                                 const PointH3<FT,RT>& q )
{
  const RT pla = pl.a();
  const RT plb = pl.b();
  const RT plc = pl.c();
  const RT phx = p.hx();
  const RT phy = p.hy();
  const RT phz = p.hz();
  const RT phw = p.hw();
  const RT qhx = q.hx();
  const RT qhy = q.hy();
  const RT qhz = q.hz();
  const RT qhw = q.hw();
  const RT RT0 = RT(0);

  RT scaled_dist_p_minus_scaled_dist_q =
      pla*( phx*qhw - qhx*phw )
    + plb*( phy*qhw - qhy*phw )
    + plc*( phz*qhw - qhz*phw );


  return ( scaled_dist_p_minus_scaled_dist_q < RT0 );
}

template <class FT, class RT>
Comparison_result
cmp_signed_dist_to_plane(const PointH3<FT,RT>& p,
                         const PointH3<FT,RT>& q,
                         const PointH3<FT,RT>& r,
                         const PointH3<FT,RT>& s,
                         const PointH3<FT,RT>& t)
{
  CGAL_kernel_precondition( !collinear(p,q,r) );
  PlaneH3<FT,RT> P(p,q,r);
  return cmp_signed_dist_to_plane( P, s, t);
}

template <class FT, class RT>
bool
has_larger_signed_dist_to_plane(const PointH3<FT,RT>& p,
                                const PointH3<FT,RT>& q,
                                const PointH3<FT,RT>& r,
                                const PointH3<FT,RT>& s,
                                const PointH3<FT,RT>& t)
{ return cmp_signed_dist_to_plane(p,q,r,s,t) == LARGER; }


template <class FT, class RT>
bool
has_smaller_signed_dist_to_plane(const PointH3<FT,RT>& p,
                                 const PointH3<FT,RT>& q,
                                 const PointH3<FT,RT>& r,
                                 const PointH3<FT,RT>& s,
                                 const PointH3<FT,RT>& t)
{ return cmp_signed_dist_to_plane(p,q,r,s,t) == SMALLER; }


CGAL_END_NAMESPACE


#endif //CGAL_DISTANCE_PREDICATESH3_H
