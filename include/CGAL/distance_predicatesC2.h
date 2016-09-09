// ============================================================================
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/distance_predicatesC2.h
// author(s)     : Stefan Schirra
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_DISTANCE_PREDICATESC2_H
#define CGAL_DISTANCE_PREDICATESC2_H

#include <CGAL/determinant.h>

template <class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_cmp_dist_to_point(const CGAL_PointC2<FT>& p,
                       const CGAL_PointC2<FT>& q,
                       const CGAL_PointC2<FT>& r)
{
  const FT& px = p.x();
  const FT& py = p.y();
  const FT& qx = q.x();
  const FT& qy = q.y();
  const FT& rx = r.x();
  const FT& ry = r.y();
  const FT FT0 = FT(0);

  FT dosd   // difference of squared distances
    =  (px - qx)*(px - qx) + (py - qy)*(py - qy)
    -( (px - rx)*(px - rx) + (py - ry)*(py - ry) );


  if ( dosd > FT0 )
  {
      return CGAL_LARGER;
  }
  else
  {
      return (dosd == FT0 ) ? CGAL_EQUAL : CGAL_SMALLER;
  }
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_larger_dist_to_point(const CGAL_PointC2<FT>& p,
                              const CGAL_PointC2<FT>& q,
                              const CGAL_PointC2<FT>& r)
{
  const FT& px = p.x();
  const FT& py = p.y();
  const FT& qx = q.x();
  const FT& qy = q.y();
  const FT& rx = r.x();
  const FT& ry = r.y();
  const FT FT0 = FT(0);

  FT dosd   // difference of squared distances
    =  (px - qx)*(px - qx) + (py - qy)*(py - qy)
    -( (px - rx)*(px - rx) + (py - ry)*(py - ry) );


  return ( dosd > FT0 );
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_smaller_dist_to_point(const CGAL_PointC2<FT>& p,
                               const CGAL_PointC2<FT>& q,
                               const CGAL_PointC2<FT>& r)
{
  const FT& px = p.x();
  const FT& py = p.y();
  const FT& qx = q.x();
  const FT& qy = q.y();
  const FT& rx = r.x();
  const FT& ry = r.y();
  const FT FT0 = FT(0);

  FT dosd   // difference of squared distances
    =  (px - qx)*(px - qx) + (py - qy)*(py - qy)
    -( (px - rx)*(px - rx) + (py - ry)*(py - ry) );


  return ( dosd < FT0 );
}
template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_line(const CGAL_LineC2<FT>&  l,
                             const CGAL_PointC2<FT>& p,
                             const CGAL_PointC2<FT>& q)
{
  const FT& la = l.a();
  const FT& lb = l.b();
  const FT& px = p.x();
  const FT& py = p.y();
  const FT& qx = q.x();
  const FT& qy = q.y();
  FT scaled_dist_p = la*px + lb*py ;
  FT scaled_dist_q = la*qx + lb*qy ;

  if ( scaled_dist_p < scaled_dist_q )
  {
      return CGAL_SMALLER;
  }
  else
  {
      return (scaled_dist_p > scaled_dist_q) ? CGAL_LARGER : CGAL_EQUAL;
  }
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_larger_signed_dist_to_line(const CGAL_LineC2<FT>&  l,
                                    const CGAL_PointC2<FT>& p,
                                    const CGAL_PointC2<FT>& q)
{
  const FT& la = l.a();
  const FT& lb = l.b();
  const FT& px = p.x();
  const FT& py = p.y();
  const FT& qx = q.x();
  const FT& qy = q.y();
  return (  la*px + lb*py > la*qx + lb*qy );
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_smaller_signed_dist_to_line(const CGAL_LineC2<FT>&  l,
                                     const CGAL_PointC2<FT>& p,
                                     const CGAL_PointC2<FT>& q)
{
  const FT& la = l.a();
  const FT& lb = l.b();
  const FT& px = p.x();
  const FT& py = p.y();
  const FT& qx = q.x();
  const FT& qy = q.y();
  return (  la*px + lb*py < la*qx + lb*qy );
}
template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_line(const CGAL_PointC2<FT>& p,
                             const CGAL_PointC2<FT>& q,
                             const CGAL_PointC2<FT>& r,
                             const CGAL_PointC2<FT>& s)
{
  const FT& px = p.x();
  const FT& py = p.y();
  const FT& qx = q.x();
  const FT& qy = q.y();
  const FT& rx = r.x();
  const FT& ry = r.y();
  const FT& sx = s.x();
  const FT& sy = s.y();
  FT scaled_dist_r = (px-rx)*(qy-ry) - (py-ry)*(qx-rx);
  FT scaled_dist_s = (px-sx)*(qy-sy) - (py-sy)*(qx-sx);


  if ( scaled_dist_r < scaled_dist_s )
  {
      return CGAL_SMALLER;
  }
  else
  {
      return (scaled_dist_r > scaled_dist_s) ? CGAL_LARGER : CGAL_EQUAL;
  }
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_smaller_signed_dist_to_line(const CGAL_PointC2<FT>& p,
                                     const CGAL_PointC2<FT>& q,
                                     const CGAL_PointC2<FT>& r,
                                     const CGAL_PointC2<FT>& s)
{
  const FT& px = p.x();
  const FT& py = p.y();
  const FT& qx = q.x();
  const FT& qy = q.y();
  const FT& rx = r.x();
  const FT& ry = r.y();
  const FT& sx = s.x();
  const FT& sy = s.y();
  FT scaled_dist_r = (px-rx)*(qy-ry) - (py-ry)*(qx-rx);
  FT scaled_dist_s = (px-sx)*(qy-sy) - (py-sy)*(qx-sx);


  return ( scaled_dist_r < scaled_dist_s );
}

template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_has_larger_signed_dist_to_line(const CGAL_PointC2<FT>& p,
                                    const CGAL_PointC2<FT>& q,
                                    const CGAL_PointC2<FT>& r,
                                    const CGAL_PointC2<FT>& s)
{
  const FT& px = p.x();
  const FT& py = p.y();
  const FT& qx = q.x();
  const FT& qy = q.y();
  const FT& rx = r.x();
  const FT& ry = r.y();
  const FT& sx = s.x();
  const FT& sy = s.y();
  FT scaled_dist_r = (px-rx)*(qy-ry) - (py-ry)*(qx-rx);
  FT scaled_dist_s = (px-sx)*(qy-sy) - (py-sy)*(qx-sx);


  return ( scaled_dist_r > scaled_dist_s );
}


#endif //CGAL_DISTANCE_PREDICATESC2_H
