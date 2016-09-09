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

// Source: distance_predicatesH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_DISTANCE_PREDICATESH2_H
#define CGAL_DISTANCE_PREDICATESH2_H

#include <CGAL/determinant.h>

template < class FT, class RT>
CGAL_Comparison_result
CGAL_cmp_dist_to_point(const CGAL_PointH2<FT,RT>& p,
                       const CGAL_PointH2<FT,RT>& q,
                       const CGAL_PointH2<FT,RT>& r)
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

 RT dosd   // difference of squared distances
    =
         phx * phx   *   qhw * qhw * rhw * rhw
   - 2 * phx * qhx   *   phw * qhw * rhw * rhw
   +     qhx * qhx   *   phw * phw * rhw * rhw

   +     phy * phy   *   qhw * qhw * rhw * rhw
   - 2 * phy * qhy   *   phw * qhw * rhw * rhw
   +     qhy * qhy   *   phw * phw * rhw * rhw

 - (     phx * phx   *   qhw * qhw * rhw * rhw
   - 2 * phx * rhx   *   phw * qhw * qhw * rhw
   +     rhx * rhx   *   phw * phw * qhw * qhw

   +     phy * phy   *   qhw * qhw * rhw * rhw
   - 2 * phy * rhy   *   phw * qhw * qhw * rhw
   +     rhy * rhy   *   phw * phw * qhw * qhw
   );


 if ( dosd > 0 )
 {
    return CGAL_LARGER;
 }
 else
 {
    return (dosd == 0) ? CGAL_EQUAL : CGAL_SMALLER;
 }
}

template < class FT, class RT>
bool
CGAL_has_larger_dist_to_point(const CGAL_PointH2<FT,RT>& p,
                              const CGAL_PointH2<FT,RT>& q,
                              const CGAL_PointH2<FT,RT>& r)
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

 RT dosd   // difference of squared distances
    =
         phx * phx   *   qhw * qhw * rhw * rhw
   - 2 * phx * qhx   *   phw * qhw * rhw * rhw
   +     qhx * qhx   *   phw * phw * rhw * rhw

   +     phy * phy   *   qhw * qhw * rhw * rhw
   - 2 * phy * qhy   *   phw * qhw * rhw * rhw
   +     qhy * qhy   *   phw * phw * rhw * rhw

 - (     phx * phx   *   qhw * qhw * rhw * rhw
   - 2 * phx * rhx   *   phw * qhw * qhw * rhw
   +     rhx * rhx   *   phw * phw * qhw * qhw

   +     phy * phy   *   qhw * qhw * rhw * rhw
   - 2 * phy * rhy   *   phw * qhw * qhw * rhw
   +     rhy * rhy   *   phw * phw * qhw * qhw
   );


return ( dosd > 0 );
}

template < class FT, class RT>
bool
CGAL_has_smaller_dist_to_point(const CGAL_PointH2<FT,RT>& p,
                               const CGAL_PointH2<FT,RT>& q,
                               const CGAL_PointH2<FT,RT>& r)
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

 RT dosd   // difference of squared distances
    =
         phx * phx   *   qhw * qhw * rhw * rhw
   - 2 * phx * qhx   *   phw * qhw * rhw * rhw
   +     qhx * qhx   *   phw * phw * rhw * rhw

   +     phy * phy   *   qhw * qhw * rhw * rhw
   - 2 * phy * qhy   *   phw * qhw * rhw * rhw
   +     qhy * qhy   *   phw * phw * rhw * rhw

 - (     phx * phx   *   qhw * qhw * rhw * rhw
   - 2 * phx * rhx   *   phw * qhw * qhw * rhw
   +     rhx * rhx   *   phw * phw * qhw * qhw

   +     phy * phy   *   qhw * qhw * rhw * rhw
   - 2 * phy * rhy   *   phw * qhw * qhw * rhw
   +     rhy * rhy   *   phw * phw * qhw * qhw
   );


return ( dosd < 0 );
}
template < class FT, class RT>
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_line(const CGAL_LineH2<FT,RT>&  l,
                             const CGAL_PointH2<FT,RT>& p,
                             const CGAL_PointH2<FT,RT>& q)
{
 RT scaled_dist_p = l.a()*p.hx() + l.b()*p.hy() + l.c()*p.hw();
 RT scaled_dist_q = l.a()*q.hx() + l.b()*q.hy() + l.c()*q.hw();
 if ( scaled_dist_p < scaled_dist_q )
 {
 return CGAL_SMALLER;
 }
 else
 {
 return (scaled_dist_p > scaled_dist_q) ? CGAL_LARGER : CGAL_EQUAL;
 }
}

template < class FT, class RT>
bool
CGAL_has_larger_signed_dist_to_line(const CGAL_LineH2<FT,RT>&  l,
                                    const CGAL_PointH2<FT,RT>& p,
                                    const CGAL_PointH2<FT,RT>& q)
{
 return (  l.a()*p.hx() + l.b()*p.hy() + l.c()*p.hw()
         < l.a()*q.hx() + l.b()*q.hy() + l.c()*q.hw() );
}

template < class FT, class RT>
bool
CGAL_has_smaller_signed_dist_to_line(const CGAL_LineH2<FT,RT>&  l,
                                     const CGAL_PointH2<FT,RT>& p,
                                     const CGAL_PointH2<FT,RT>& q)
{
 return (  l.a()*p.hx() + l.b()*p.hy() + l.c()*p.hw()
         > l.a()*q.hx() + l.b()*q.hy() + l.c()*q.hw() );
}

template < class FT, class RT>
CGAL_Comparison_result
CGAL_cmp_signed_dist_to_line(const CGAL_PointH2<FT,RT>& p,
                             const CGAL_PointH2<FT,RT>& q,
                             const CGAL_PointH2<FT,RT>& r,
                             const CGAL_PointH2<FT,RT>& s)
{
 RT scaled_dist_r = CGAL_det3x3_by_formula( p.hx(),  p.hy(),  p.hw(),
                                            q.hx(),  q.hy(),  q.hw(),
                                            r.hx(),  r.hy(),  r.hw()  );
 RT scaled_dist_s = CGAL_det3x3_by_formula( p.hx(),  p.hy(),  p.hw(),
                                            q.hx(),  q.hy(),  q.hw(),
                                            s.hx(),  s.hy(),  s.hw()  );
 if ( scaled_dist_r < scaled_dist_s )
 {
 return CGAL_SMALLER;
 }
 else
 {
 return (scaled_dist_r > scaled_dist_s) ? CGAL_LARGER : CGAL_EQUAL;
 }
}
template < class FT, class RT>
bool
CGAL_has_smaller_signed_dist_to_line(const CGAL_PointH2<FT,RT>& p,
                                     const CGAL_PointH2<FT,RT>& q,
                                     const CGAL_PointH2<FT,RT>& r,
                                     const CGAL_PointH2<FT,RT>& s)
{
 RT scaled_dist_r = CGAL_det3x3_by_formula( p.hx(),  p.hy(),  p.hw(),
                                            q.hx(),  q.hy(),  q.hw(),
                                            r.hx(),  r.hy(),  r.hw()  );
 RT scaled_dist_s = CGAL_det3x3_by_formula( p.hx(),  p.hy(),  p.hw(),
                                            q.hx(),  q.hy(),  q.hw(),
                                            s.hx(),  s.hy(),  s.hw()  );
 return ( scaled_dist_r < scaled_dist_s );
}

template < class FT, class RT>
bool
CGAL_has_larger_signed_dist_to_line(const CGAL_PointH2<FT,RT>& p,
                                    const CGAL_PointH2<FT,RT>& q,
                                    const CGAL_PointH2<FT,RT>& r,
                                    const CGAL_PointH2<FT,RT>& s)
{
 RT scaled_dist_r = CGAL_det3x3_by_formula( p.hx(),  p.hy(),  p.hw(),
                                            q.hx(),  q.hy(),  q.hw(),
                                            r.hx(),  r.hy(),  r.hw()  );
 RT scaled_dist_s = CGAL_det3x3_by_formula( p.hx(),  p.hy(),  p.hw(),
                                            q.hx(),  q.hy(),  q.hw(),
                                            s.hx(),  s.hy(),  s.hw()  );
 return ( scaled_dist_r > scaled_dist_s );
}


#endif //CGAL_DISTANCE_PREDICATESH2_H
