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


// Source: distance_predicatesH2.h
// Author: Stefan Schirra

#ifndef CGAL_DISTANCE_PREDICATESH2_H
#define CGAL_DISTANCE_PREDICATESH2_H

#include <CGAL/determinant.h>

template < class FT, class RT>
CGAL_Comparison_result
CGAL_cmp_dist_to_point(const CGAL_PointH2<FT,RT>& p,
                       const CGAL_PointH2<FT,RT>& q,
                       const CGAL_PointH2<FT,RT>& r)
{
  const RT & phx = p.hx();
  const RT & phy = p.hy();
  const RT & phw = p.hw();
  const RT & qhx = q.hx();
  const RT & qhy = q.hy();
  const RT & qhw = q.hw();
  const RT & rhx = r.hx();
  const RT & rhy = r.hy();
  const RT & rhw = r.hw();
  const RT RT0   = RT(0);
  const RT RT2   = RT(2);

  RT dosd =   // difference of squared distances

  //            phx * phx   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phx * qhx   *   phw * qhw * rhw * rhw
  //   +        qhx * qhx   *   phw * phw * rhw * rhw
  //
  //   +        phy * phy   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phy * qhy   *   phw * qhw * rhw * rhw
  //   +        qhy * qhy   *   phw * phw * rhw * rhw
  //
  // - (        phx * phx   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phx * rhx   *   phw * qhw * qhw * rhw
  //   +        rhx * rhx   *   phw * phw * qhw * qhw
  //
  //   +        phy * phy   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phy * rhy   *   phw * qhw * qhw * rhw
  //   +        rhy * rhy   *   phw * phw * qhw * qhw

    rhw*rhw * (         phw * ( qhx*qhx + qhy*qhy ) 
                - RT2 * qhw * ( phx*qhx + phy*qhy ) 
              ) 
  - qhw*qhw * (         phw * ( rhx*rhx + rhy*rhy ) 
                - RT2 * rhw * ( phx*rhx + phy*rhy ) 
              );


  if ( dosd > RT0 )
  {
      return CGAL_LARGER;
  }
  else
  {
      return (dosd == RT0) ? CGAL_EQUAL : CGAL_SMALLER;
  }
}

template < class FT, class RT>
bool
CGAL_has_larger_dist_to_point(const CGAL_PointH2<FT,RT>& p,
                              const CGAL_PointH2<FT,RT>& q,
                              const CGAL_PointH2<FT,RT>& r)
{
  const RT & phx = p.hx();
  const RT & phy = p.hy();
  const RT & phw = p.hw();
  const RT & qhx = q.hx();
  const RT & qhy = q.hy();
  const RT & qhw = q.hw();
  const RT & rhx = r.hx();
  const RT & rhy = r.hy();
  const RT & rhw = r.hw();
  const RT RT0   = RT(0);
  const RT RT2   = RT(2);

  RT dosd =   // difference of squared distances

  //            phx * phx   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phx * qhx   *   phw * qhw * rhw * rhw
  //   +        qhx * qhx   *   phw * phw * rhw * rhw
  //
  //   +        phy * phy   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phy * qhy   *   phw * qhw * rhw * rhw
  //   +        qhy * qhy   *   phw * phw * rhw * rhw
  //
  // - (        phx * phx   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phx * rhx   *   phw * qhw * qhw * rhw
  //   +        rhx * rhx   *   phw * phw * qhw * qhw
  //
  //   +        phy * phy   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phy * rhy   *   phw * qhw * qhw * rhw
  //   +        rhy * rhy   *   phw * phw * qhw * qhw

    rhw*rhw * (         phw * ( qhx*qhx + qhy*qhy ) 
                - RT2 * qhw * ( phx*qhx + phy*qhy ) 
              ) 
  - qhw*qhw * (         phw * ( rhx*rhx + rhy*rhy ) 
                - RT2 * rhw * ( phx*rhx + phy*rhy ) 
              );


  return ( dosd > RT0 );
}

template < class FT, class RT>
bool
CGAL_has_smaller_dist_to_point(const CGAL_PointH2<FT,RT>& p,
                               const CGAL_PointH2<FT,RT>& q,
                               const CGAL_PointH2<FT,RT>& r)
{
  const RT & phx = p.hx();
  const RT & phy = p.hy();
  const RT & phw = p.hw();
  const RT & qhx = q.hx();
  const RT & qhy = q.hy();
  const RT & qhw = q.hw();
  const RT & rhx = r.hx();
  const RT & rhy = r.hy();
  const RT & rhw = r.hw();
  const RT RT0   = RT(0);
  const RT RT2   = RT(2);

  RT dosd =   // difference of squared distances

  //            phx * phx   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phx * qhx   *   phw * qhw * rhw * rhw
  //   +        qhx * qhx   *   phw * phw * rhw * rhw
  //
  //   +        phy * phy   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phy * qhy   *   phw * qhw * rhw * rhw
  //   +        qhy * qhy   *   phw * phw * rhw * rhw
  //
  // - (        phx * phx   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phx * rhx   *   phw * qhw * qhw * rhw
  //   +        rhx * rhx   *   phw * phw * qhw * qhw
  //
  //   +        phy * phy   *   qhw * qhw * rhw * rhw
  //   -RT(2) * phy * rhy   *   phw * qhw * qhw * rhw
  //   +        rhy * rhy   *   phw * phw * qhw * qhw

    rhw*rhw * (         phw * ( qhx*qhx + qhy*qhy ) 
                - RT2 * qhw * ( phx*qhx + phy*qhy ) 
              ) 
  - qhw*qhw * (         phw * ( rhx*rhx + rhy*rhy ) 
                - RT2 * rhw * ( phx*rhx + phy*rhy ) 
              );


  return ( dosd < RT0 );
}
template < class FT, class RT>
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_line(const CGAL_LineH2<FT,RT>&  l,
                             const CGAL_PointH2<FT,RT>& p,
                             const CGAL_PointH2<FT,RT>& q)
{
  const RT & la = l.a();
  const RT & lb = l.b();
  const RT & lc = l.c();
  const RT & phx= p.hx();
  const RT & phy= p.hy();
  const RT & phw= p.hw();
  const RT & qhx= q.hx();
  const RT & qhy= q.hy();
  const RT & qhw= q.hw();
  const RT  RT0 = RT(0);
  
  RT scaled_dist_p_minus_scaled_dist_q = 
      la*( phx*qhw - qhx*phw ) 
    + lb*( phy*qhw - qhy*phw );



  if ( scaled_dist_p_minus_scaled_dist_q < RT0 )
  {
      return CGAL_SMALLER;
  }
  else
  {
      return (scaled_dist_p_minus_scaled_dist_q > RT0) ? 
             CGAL_LARGER : CGAL_EQUAL;
  }
}

template < class FT, class RT>
bool
CGAL_has_larger_signed_dist_to_line(const CGAL_LineH2<FT,RT>&  l,
                                    const CGAL_PointH2<FT,RT>& p,
                                    const CGAL_PointH2<FT,RT>& q)
{
  const RT & la = l.a();
  const RT & lb = l.b();
  const RT & lc = l.c();
  const RT & phx= p.hx();
  const RT & phy= p.hy();
  const RT & phw= p.hw();
  const RT & qhx= q.hx();
  const RT & qhy= q.hy();
  const RT & qhw= q.hw();
  const RT  RT0 = RT(0);
  
  RT scaled_dist_p_minus_scaled_dist_q = 
      la*( phx*qhw - qhx*phw ) 
    + lb*( phy*qhw - qhy*phw );



  return ( scaled_dist_p_minus_scaled_dist_q > RT0 );
}

template < class FT, class RT>
bool
CGAL_has_smaller_signed_dist_to_line(const CGAL_LineH2<FT,RT>&  l,
                                     const CGAL_PointH2<FT,RT>& p,
                                     const CGAL_PointH2<FT,RT>& q)
{
  const RT & la = l.a();
  const RT & lb = l.b();
  const RT & lc = l.c();
  const RT & phx= p.hx();
  const RT & phy= p.hy();
  const RT & phw= p.hw();
  const RT & qhx= q.hx();
  const RT & qhy= q.hy();
  const RT & qhw= q.hw();
  const RT  RT0 = RT(0);
  
  RT scaled_dist_p_minus_scaled_dist_q = 
      la*( phx*qhw - qhx*phw ) 
    + lb*( phy*qhw - qhy*phw );



  return ( scaled_dist_p_minus_scaled_dist_q < RT0 );
}
template < class FT, class RT>
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_line(const CGAL_PointH2<FT,RT>& p,
                             const CGAL_PointH2<FT,RT>& q,
                             const CGAL_PointH2<FT,RT>& r,
                             const CGAL_PointH2<FT,RT>& s)
{
  const RT & phx= p.hx();
  const RT & phy= p.hy();
  const RT & phw= p.hw();
  const RT & qhx= q.hx();
  const RT & qhy= q.hy();
  const RT & qhw= q.hw();
  const RT & rhx= r.hx();
  const RT & rhy= r.hy();
  const RT & rhw= r.hw();
  const RT & shx= s.hx();
  const RT & shy= s.hy();
  const RT & shw= s.hw();
  const RT RT0  = RT(0);

  RT  scaled_dist_r_minus_scaled_dist_s =
         ( rhx*shw - shx*rhw ) * (phy*qhw - qhy*phw)
       - ( rhy*shw - shy*rhw ) * (phx*qhw - qhx*phw);


  if ( scaled_dist_r_minus_scaled_dist_s < RT0 )
  {
      return CGAL_SMALLER;
  }
  else
  {
      return (scaled_dist_r_minus_scaled_dist_s > RT0 ) ? 
             CGAL_LARGER : CGAL_EQUAL;
  }
}

template < class FT, class RT>
bool
CGAL_has_smaller_signed_dist_to_line(const CGAL_PointH2<FT,RT>& p,
                                     const CGAL_PointH2<FT,RT>& q,
                                     const CGAL_PointH2<FT,RT>& r,
                                     const CGAL_PointH2<FT,RT>& s)
{
  const RT & phx= p.hx();
  const RT & phy= p.hy();
  const RT & phw= p.hw();
  const RT & qhx= q.hx();
  const RT & qhy= q.hy();
  const RT & qhw= q.hw();
  const RT & rhx= r.hx();
  const RT & rhy= r.hy();
  const RT & rhw= r.hw();
  const RT & shx= s.hx();
  const RT & shy= s.hy();
  const RT & shw= s.hw();
  const RT RT0  = RT(0);

  RT  scaled_dist_r_minus_scaled_dist_s =
         ( rhx*shw - shx*rhw ) * (phy*qhw - qhy*phw)
       - ( rhy*shw - shy*rhw ) * (phx*qhw - qhx*phw);


  return ( scaled_dist_r_minus_scaled_dist_s < RT0 );
}

template < class FT, class RT>
bool
CGAL_has_larger_signed_dist_to_line(const CGAL_PointH2<FT,RT>& p,
                                    const CGAL_PointH2<FT,RT>& q,
                                    const CGAL_PointH2<FT,RT>& r,
                                    const CGAL_PointH2<FT,RT>& s)
{
  const RT & phx= p.hx();
  const RT & phy= p.hy();
  const RT & phw= p.hw();
  const RT & qhx= q.hx();
  const RT & qhy= q.hy();
  const RT & qhw= q.hw();
  const RT & rhx= r.hx();
  const RT & rhy= r.hy();
  const RT & rhw= r.hw();
  const RT & shx= s.hx();
  const RT & shy= s.hy();
  const RT & shw= s.hw();
  const RT RT0  = RT(0);

  RT  scaled_dist_r_minus_scaled_dist_s =
         ( rhx*shw - shx*rhw ) * (phy*qhw - qhy*phw)
       - ( rhy*shw - shy*rhw ) * (phx*qhw - qhx*phw);


  return ( scaled_dist_r_minus_scaled_dist_s > RT0 );
}


#endif //CGAL_DISTANCE_PREDICATESH2_H
