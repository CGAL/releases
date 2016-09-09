// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.3
// release_date  : 2001, August 13
// 
// file          : include/CGAL/distance_predicatesH3.h
// package       : H3 (2.34)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/07/23 17:35:22 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_DISTANCE_PREDICATESH3_H
#define CGAL_DISTANCE_PREDICATESH3_H

CGAL_BEGIN_NAMESPACE

template <class R>
Comparison_result
compare_distance_to_point(const PointH3<R>& ,
                          const PointH3<R>& ,
                          const PointH3<R>& );

template <class R>
bool
has_larger_distance_to_point(const PointH3<R>& ,
                             const PointH3<R>& ,
                             const PointH3<R>& );

template <class R>
bool
has_smaller_distance_to_point(const PointH3<R>& ,
                              const PointH3<R>& ,
                              const PointH3<R>& );

template <class R>
Comparison_result
compare_signed_distance_to_plane(const PlaneH3<R>& ,
                                 const PointH3<R>& ,
                                 const PointH3<R>& );

template <class R>
bool
has_larger_signed_distance_to_plane(const PlaneH3<R>& ,
                                    const PointH3<R>& ,
                                    const PointH3<R>& );

template <class R>
bool
has_smaller_signed_distance_to_plane(const PlaneH3<R>&,
                                     const PointH3<R>& ,
                                     const PointH3<R>& );

template <class R>
Comparison_result
compare_signed_distance_to_plane(const PointH3<R>& ,
                                 const PointH3<R>& ,
                                 const PointH3<R>& ,
                                 const PointH3<R>& ,
                                 const PointH3<R>& );

template <class R>
bool
has_larger_signed_distance_to_plane(const PointH3<R>& ,
                                    const PointH3<R>& ,
                                    const PointH3<R>& ,
                                    const PointH3<R>& ,
                                    const PointH3<R>& );

template <class R>
bool
has_smaller_signed_distance_to_plane(const PointH3<R>& ,
                                     const PointH3<R>& ,
                                     const PointH3<R>& ,
                                     const PointH3<R>& ,
                                     const PointH3<R>& );

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_distance_to_point(const PointH3<R>& p,
                          const PointH3<R>& q,
                          const PointH3<R>& r)
{
  typedef typename R::RT RT;

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

template < class R>
CGAL_KERNEL_MEDIUM_INLINE
bool
has_larger_distance_to_point(const PointH3<R>& p,
                             const PointH3<R>& q,
                             const PointH3<R>& r)
{
  typedef typename R::RT RT;

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

template < class R>
CGAL_KERNEL_MEDIUM_INLINE
bool
has_smaller_distance_to_point(const PointH3<R>& p,
                              const PointH3<R>& q,
                              const PointH3<R>& r)
{
  typedef typename R::RT RT;

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

template < class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_signed_distance_to_plane(const PlaneH3<R>& pl,
                                 const PointH3<R>& p,
                                 const PointH3<R>& q)
{
  typedef typename R::RT RT;

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

template <class R>
bool
has_larger_signed_distance_to_plane(const PlaneH3<R>& pl,
                                    const PointH3<R>& p,
                                    const PointH3<R>& q )
{
  typedef typename R::RT RT;

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

template <class R>
bool
has_smaller_signed_distance_to_plane(const PlaneH3<R>& pl,
                                     const PointH3<R>& p,
                                     const PointH3<R>& q )
{
  typedef typename R::RT RT;

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

template <class R>
inline
Comparison_result
compare_signed_distance_to_plane(const PointH3<R>& p,
                                 const PointH3<R>& q,
                                 const PointH3<R>& r,
                                 const PointH3<R>& s,
                                 const PointH3<R>& t)
{
  CGAL_kernel_precondition( !collinear(p,q,r) );
  PlaneH3<R> P(p,q,r);
  return cmp_signed_dist_to_plane( P, s, t);
}

template <class R>
inline
bool
has_larger_signed_distance_to_plane(const PointH3<R>& p,
                                    const PointH3<R>& q,
                                    const PointH3<R>& r,
                                    const PointH3<R>& s,
                                    const PointH3<R>& t)
{ return cmp_signed_dist_to_plane(p,q,r,s,t) == LARGER; }


template <class R>
inline
bool
has_smaller_signed_distance_to_plane(const PointH3<R>& p,
                                     const PointH3<R>& q,
                                     const PointH3<R>& r,
                                     const PointH3<R>& s,
                                     const PointH3<R>& t)
{ return cmp_signed_dist_to_plane(p,q,r,s,t) == SMALLER; }


#ifndef CGAL_NO_DEPRECATED_CODE
template <class R>
Comparison_result
cmp_dist_to_point(const PointH3<R>& ,
                  const PointH3<R>& ,
                  const PointH3<R>& );

template <class R>
bool
has_larger_dist_to_point(const PointH3<R>& ,
                         const PointH3<R>& ,
                         const PointH3<R>& );

template <class R>
bool
has_smaller_dist_to_point(const PointH3<R>& ,
                          const PointH3<R>& ,
                          const PointH3<R>& );

template <class R>
Comparison_result
cmp_signed_dist_to_plane(const PlaneH3<R>& ,
                         const PointH3<R>& ,
                         const PointH3<R>& );

template <class R>
bool
has_larger_signed_dist_to_plane(const PlaneH3<R>& ,
                                const PointH3<R>& ,
                                const PointH3<R>& );

template <class R>
bool
has_smaller_signed_dist_to_plane(const PlaneH3<R>&,
                                 const PointH3<R>& ,
                                 const PointH3<R>& );

template <class R>
Comparison_result
cmp_signed_dist_to_plane(const PointH3<R>& ,
                         const PointH3<R>& ,
                         const PointH3<R>& ,
                         const PointH3<R>& ,
                         const PointH3<R>& );

template <class R>
bool
has_larger_signed_dist_to_plane(const PointH3<R>& ,
                                const PointH3<R>& ,
                                const PointH3<R>& ,
                                const PointH3<R>& ,
                                const PointH3<R>& );

template <class R>
bool
has_smaller_signed_dist_to_plane(const PointH3<R>& ,
                                 const PointH3<R>& ,
                                 const PointH3<R>& ,
                                 const PointH3<R>& ,
                                 const PointH3<R>& );

template <class R>
inline
Comparison_result
cmp_dist_to_point(const PointH3<R>& p,
                  const PointH3<R>& q,
                  const PointH3<R>& r)
{
  return compare_distance_to_point(p, q, r);
}

template < class R>
inline
bool
has_larger_dist_to_point(const PointH3<R>& p,
                         const PointH3<R>& q,
                         const PointH3<R>& r)
{
  return has_larger_distance_to_point(p, q, r);
}

template < class R>
inline
bool
has_smaller_dist_to_point(const PointH3<R>& p,
                          const PointH3<R>& q,
                          const PointH3<R>& r)
{
  return has_smaller_distance_to_point(p, q, r);
}

template < class R>
inline
Comparison_result
cmp_signed_dist_to_plane(const PlaneH3<R>& pl,
                         const PointH3<R>& p,
                         const PointH3<R>& q)
{
  return compare_signed_distance_to_plane(pl, p, q);
}

template <class R>
inline
bool
has_larger_signed_dist_to_plane(const PlaneH3<R>& pl,
                                const PointH3<R>& p,
                                const PointH3<R>& q )
{
  return has_larger_signed_distance_to_plane(pl, p, q);
}

template <class R>
inline
bool
has_smaller_signed_dist_to_plane(const PlaneH3<R>& pl,
                                 const PointH3<R>& p,
                                 const PointH3<R>& q )
{
  return has_smaller_signed_distance_to_plane(pl, p, q);
}

template <class R>
Comparison_result
cmp_signed_dist_to_plane(const PointH3<R>& p,
                         const PointH3<R>& q,
                         const PointH3<R>& r,
                         const PointH3<R>& s,
                         const PointH3<R>& t)
{
  return compare_signed_distance_to_plane(p, q, r, s, t);
}

template <class R>
inline
bool
has_larger_signed_dist_to_plane(const PointH3<R>& p,
                                const PointH3<R>& q,
                                const PointH3<R>& r,
                                const PointH3<R>& s,
                                const PointH3<R>& t)
{ return cmp_signed_dist_to_plane(p,q,r,s,t) == LARGER; }


template <class R>
inline
bool
has_smaller_signed_dist_to_plane(const PointH3<R>& p,
                                 const PointH3<R>& q,
                                 const PointH3<R>& r,
                                 const PointH3<R>& s,
                                 const PointH3<R>& t)
{ return cmp_signed_dist_to_plane(p,q,r,s,t) == SMALLER; }
#endif

CGAL_END_NAMESPACE


#endif //CGAL_DISTANCE_PREDICATESH3_H
