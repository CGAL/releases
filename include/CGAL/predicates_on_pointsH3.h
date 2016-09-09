// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.2
// release_date  : 1999, January 18
// 
// source        : predicates_on_pointsH3.fw
// file          : include/CGAL/predicates_on_pointsH3.h
// package       : H3 (1.5)
// revision      : 1.5
// revision_date : 15 Dec 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef PREDICATES_ON_POINTSH3_H
#define PREDICATES_ON_POINTSH3_H

#ifndef CGAL_PVDH3_H
#include <CGAL/PVDH3.h>
#endif // CGAL_PVDH3_H

template < class FT, class RT >
inline
bool
CGAL_x_equal(const CGAL_PointH3<FT,RT> &p,
             const CGAL_PointH3<FT,RT> &q)
{ return p.x()*q.hw() == q.x()*p.hw(); }

template < class FT, class RT >
inline
bool
CGAL_y_equal(const CGAL_PointH3<FT,RT> &p,
             const CGAL_PointH3<FT,RT> &q)
{ return p.y()*q.hw() == q.y()*p.hw(); }

template < class FT, class RT >
inline
bool
CGAL_z_equal(const CGAL_PointH3<FT,RT> &p,
             const CGAL_PointH3<FT,RT> &q)
{ return p.z()*q.hw() == q.z()*p.hw(); }

template < class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_compare_lexicographically_xyz(const CGAL_PointH3<FT,RT>& p,
                                   const CGAL_PointH3<FT,RT>& q)
{
  RT pV = p.hx()*q.hw();
  RT qV = q.hx()*p.hw();
  if ( pV < qV )
  {
      return CGAL_SMALLER;
  }
  if ( qV < pV )    //   ( pV > qV )
  {
      return CGAL_LARGER;
  }
  // same x
  pV = p.hy()*q.hw();
  qV = q.hy()*p.hw();
  if ( pV < qV )
  {
      return CGAL_SMALLER;
  }
  if ( qV < pV )    //   ( pV > qV )
  {
      return CGAL_LARGER;
  }
  // same x and y
  pV = p.hz()*q.hw();
  qV = q.hz()*p.hw();
  if ( pV < qV )
  {
      return CGAL_SMALLER;
  }
  else
  {
      return (qV < pV) ? CGAL_LARGER : CGAL_EQUAL;
  }
}

template < class FT, class RT >
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_lexicographically_xyz_smaller_or_equal(const CGAL_PointH3<FT,RT> &p,
                                            const CGAL_PointH3<FT,RT> &q)
{
  RT pV = p.hx()*q.hw();
  RT qV = q.hx()*p.hw();
  if ( qV < pV )    //   ( pV > qV )
  {
      return false;
  }
  if ( !(pV == qV) )
  {
      return true;
  }
  // same x
  pV = p.hy()*q.hw();
  qV = q.hy()*p.hw();
  if ( qV < pV )    //   ( pV > qV )
  {
      return false;
  }
  if ( !(pV == qV) )
  {
      return true;
  }
  // same x and y
  pV = p.hz()*q.hw();
  qV = q.hz()*p.hw();
  if ( qV < pV )    //   ( pV > qV )
  {
      return false;
  }
  return true;
}

template < class FT, class RT >
CGAL_KERNEL_MEDIUM_INLINE
bool CGAL_lexicographically_xyz_smaller(const CGAL_PointH3<FT,RT> &p,
                                        const CGAL_PointH3<FT,RT> &q)
{
  RT pV = p.hx()*q.hw();
  RT qV = q.hx()*p.hw();
  if ( pV < qV )
  {
      return true;
  }
  if ( qV < pV )
  {
      return false;
  }
  // same x
  pV = p.hy()*q.hw();
  qV = q.hy()*p.hw();
  if ( pV < qV )
  {
      return true;
  }
  if ( qV < pV )
  {
      return false;
  }
  // same x and y
  pV = p.hz()*q.hw();
  qV = q.hz()*p.hw();
  if ( pV < qV )
  {
      return true;
  }
  return false;
}

template < class FT, class RT >
inline
CGAL_Comparison_result
CGAL_compare_x(const CGAL_PointH3<FT,RT> &p, const CGAL_PointH3<FT,RT> &q)
{ return CGAL_compare(p.hx() * q.hw(), q.hx() * p.hw() ); }

template < class FT, class RT >
inline
CGAL_Comparison_result
CGAL_compare_y(const CGAL_PointH3<FT,RT> &p, const CGAL_PointH3<FT,RT> &q)
{ return CGAL_compare(p.hy() * q.hw(), q.hy() * p.hw() ); }

template < class FT, class RT >
inline
CGAL_Comparison_result
CGAL_compare_z(const CGAL_PointH3<FT,RT> &p, const CGAL_PointH3<FT,RT> &q)
{ return CGAL_compare(p.hz() * q.hw(), q.hz() * p.hw() ); }

#ifndef CGAL_ORIENTATION_PREDICATESH3_H
#include <CGAL/orientation_predicatesH3.h>
#endif // CGAL_ORIENTATION_PREDICATESH3_H
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_collinear(const CGAL_PointH3<FT,RT> &p,
               const CGAL_PointH3<FT,RT> &q,
               const CGAL_PointH3<FT,RT> &r)
{
  CGAL_DirectionH3<FT,RT> dir_pq = (p - q).direction();
  CGAL_DirectionH3<FT,RT> dir_rq = (r - q).direction();

  return    ( dir_pq == dir_rq ) || (dir_pq == -dir_rq)
         || ( p == q ) || ( p == r ) || ( q == r ) ;
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_are_ordered_along_line(const CGAL_PointH3<FT,RT> &p,
                            const CGAL_PointH3<FT,RT> &q,
                            const CGAL_PointH3<FT,RT> &r)
{
  if (!CGAL_collinear(p, q, r))
  {
       return false;
  }
  return CGAL_collinear_are_ordered_along_line(p, q, r);
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_collinear_are_ordered_along_line(const CGAL_PointH3<FT,RT> &p,
                                      const CGAL_PointH3<FT,RT> &q,
                                      const CGAL_PointH3<FT,RT> &r)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );
  const RT phx = p.hx();
  const RT phw = p.hw();
  const RT qhx = q.hx();
  const RT qhw = q.hw();
  const RT rhx = r.hx();
  const RT rhw = r.hw();

  const RT pqx = phx*qhw;
  const RT qpx = qhx*phw;
  const RT prx = phx*rhw;
  const RT qrx = qhx*rhw;
  const RT rqx = rhx*qhw;
  const RT rpx = rhx*phw;

  if ( prx != rpx )   // px != rx
  {
                //    (px <= qx)&&(qx <= rx) || (px >= qx)&&(qx >= rx)
                // !(((qx <  px)||(rx <  qx))&&((px <  qx)||(qx <  rx)))
      return ! (   ((qpx < pqx) || (rqx < qrx))
                && ((pqx < qpx) || (qrx < rqx))  );
  }

  const RT phy = p.hy();
  const RT qhy = q.hy();
  const RT rhy = r.hy();

  const RT pqy = phy*qhw;
  const RT qpy = qhy*phw;
  const RT pry = phy*rhw;
  const RT qry = qhy*rhw;
  const RT rqy = rhy*qhw;
  const RT rpy = rhy*phw;

  if ( pry != rpy )
  {
      return ! (   ((qpy < pqy) || (rqy < qry))
                && ((pqy < qpy) || (qry < rqy))  );
  }

  const RT phz = p.hz();
  const RT qhz = q.hz();
  const RT rhz = r.hz();

  const RT pqz = phz*qhw;
  const RT qpz = qhz*phw;
  const RT prz = phz*rhw;
  const RT qrz = qhz*rhw;
  const RT rqz = rhz*qhw;
  const RT rpz = rhz*phw;

  if ( prz != rpz )
  {
      return ! (   ((qpz < pqz) || (rqz < qrz))
                && ((pqz < qpz) || (qrz < rqz))  );
  }
  // p == r
  return  ((rqx == qrx) && (rqy == qry) && (rqz == qrz));
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_are_strictly_ordered_along_line(const CGAL_PointH3<FT,RT> &p,
                                     const CGAL_PointH3<FT,RT> &q,
                                     const CGAL_PointH3<FT,RT> &r)
{
  if ( ! CGAL_collinear(p, q, r) ) return false;
  return CGAL_collinear_are_strictly_ordered_along_line( p, q, r);
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_collinear_are_strictly_ordered_along_line(const CGAL_PointH3<FT,RT> &p,
                                               const CGAL_PointH3<FT,RT> &q,
                                               const CGAL_PointH3<FT,RT> &r)
{
  CGAL_kernel_exactness_precondition( CGAL_collinear(p, q, r) );
  if ( p == r) return false;
  CGAL_DirectionH3<FT,RT> dir_pq = (p - q).direction();
  CGAL_DirectionH3<FT,RT> dir_rq = (r - q).direction();
  return (dir_pq == -dir_rq);
}



template < class FT, class RT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Oriented_side
CGAL_side_of_oriented_sphere(const CGAL_PointH3<FT,RT> &p,
                             const CGAL_PointH3<FT,RT> &q,
                             const CGAL_PointH3<FT,RT> &r,
                             const CGAL_PointH3<FT,RT> &s,
                             const CGAL_PointH3<FT,RT> &t)
{
  CGAL_kernel_precondition( !CGAL_coplanar(p,q,r,s) );
  const RT phx = p.hx();
  const RT phy = p.hy();
  const RT phz = p.hz();
  const RT phw = p.hw();
  const RT phw2 = phw*phw;

  const RT qhx = q.hx();
  const RT qhy = q.hy();
  const RT qhz = q.hz();
  const RT qhw = q.hw();
  const RT qhw2 = qhw*qhw;

  const RT rhx = r.hx();
  const RT rhy = r.hy();
  const RT rhz = r.hz();
  const RT rhw = r.hw();
  const RT rhw2 = rhw*rhw;

  const RT shx = s.hx();
  const RT shy = s.hy();
  const RT shz = s.hz();
  const RT shw = s.hw();
  const RT shw2 = shw*shw;

  const RT thx = t.hx();
  const RT thy = t.hy();
  const RT thz = t.hz();
  const RT thw = t.hw();
  const RT thw2 = thw*thw;

  const RT det = CGAL_det5x5_by_formula(
        phx*phw, phy*phw, phz*phw, phx*phx + phy*phy + phz*phz, phw2,
        qhx*qhw, qhy*qhw, qhz*qhw, qhx*qhx + qhy*qhy + qhz*qhz, qhw2,
        rhx*rhw, rhy*rhw, rhz*rhw, rhx*rhx + rhy*rhy + rhz*rhz, rhw2,
        shx*shw, shy*shw, shz*shw, shx*shx + shy*shy + shz*shz, shw2,
        thx*thw, thy*thw, thz*thw, thx*thx + thy*thy + thz*thz, thw2);
  if (det < RT(0))
  {
      return CGAL_ON_POSITIVE_SIDE;
  }
  else
  {
      return (RT(0) < det) ? CGAL_ON_NEGATIVE_SIDE : CGAL_ON_ORIENTED_BOUNDARY;
  }
}

template < class FT, class RT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Bounded_side
CGAL_side_of_bounded_sphere(const CGAL_PointH3<FT,RT> &p,
                            const CGAL_PointH3<FT,RT> &q,
                            const CGAL_PointH3<FT,RT> &r,
                            const CGAL_PointH3<FT,RT> &s,
                            const CGAL_PointH3<FT,RT> &test)
{
  CGAL_Oriented_side  oside = CGAL_side_of_oriented_sphere(p,q,r,s,test);
  if ( CGAL_are_positive_oriented( p,q,r,s) )
  {
    switch (oside)
    {
        case CGAL_ON_POSITIVE_SIDE    :   return CGAL_ON_BOUNDED_SIDE;
        case CGAL_ON_ORIENTED_BOUNDARY:   return CGAL_ON_BOUNDARY;
        case CGAL_ON_NEGATIVE_SIDE    :   return CGAL_ON_UNBOUNDED_SIDE;
    }
  }
  else
  {
    switch (oside)
    {
        case CGAL_ON_POSITIVE_SIDE    :   return CGAL_ON_UNBOUNDED_SIDE;
        case CGAL_ON_ORIENTED_BOUNDARY:   return CGAL_ON_BOUNDARY;
        case CGAL_ON_NEGATIVE_SIDE    :   return CGAL_ON_BOUNDED_SIDE;
    }
  }
  return CGAL_ON_BOUNDARY;  // Pls, no warnings anylonger
}



#endif // PREDICATES_ON_POINTSH3_H
