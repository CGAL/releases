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


// Source: predicates_on_pointsH3.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef PREDICATES_ON_POINTSH3_H
#define PREDICATES_ON_POINTSH3_H

#include <CGAL/PVDH3.h>

template < class FT, class RT >
bool CGAL_x_equal(const CGAL_PointH3<FT,RT> &p,
                  const CGAL_PointH3<FT,RT> &q)
{
  return p.x()*q.hw() == q.x()*p.hw();
}

template < class FT, class RT >
bool CGAL_y_equal(const CGAL_PointH3<FT,RT> &p,
                  const CGAL_PointH3<FT,RT> &q)
{
  return p.y()*q.hw() == q.y()*p.hw();
}

template < class FT, class RT >
bool CGAL_z_equal(const CGAL_PointH3<FT,RT> &p,
                  const CGAL_PointH3<FT,RT> &q)
{
  return p.z()*q.hw() == q.z()*p.hw();
}

template < class FT, class RT>
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
 if ( pV > qV )
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
 if ( pV > qV )
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
    return (pV > qV) ? CGAL_LARGER : CGAL_EQUAL;
 }
}

template < class FT, class RT >
bool CGAL_lexicographically_xyz_smaller_or_equal(const CGAL_PointH3<FT,RT> &p,
                                                 const CGAL_PointH3<FT,RT> &q)
{
  return ( !( CGAL_compare_lexicographically_xyz(p,q) == CGAL_LARGER ) );
}

template < class FT, class RT >
bool CGAL_lexicographically_xyz_smaller(const CGAL_PointH3<FT,RT> &p,
                                        const CGAL_PointH3<FT,RT> &q)
{
  return CGAL_compare_lexicographically_xyz(p,q) == CGAL_SMALLER ;
}

#include <CGAL/orientation_predicatesH3.h>
template < class FT, class RT >
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
inline
bool
CGAL_between(const CGAL_PointH3<FT,RT> &p,
             const CGAL_PointH3<FT,RT> &q,
             const CGAL_PointH3<FT,RT> &r)
{
 if (!CGAL_collinear(p, q, r))
 {
     return false;
 }
 return CGAL_collinear_between(p, q, r);
}

template < class FT, class RT >
inline
bool
CGAL_collinear_between(const CGAL_PointH3<FT,RT> &p,
                       const CGAL_PointH3<FT,RT> &q,
                       const CGAL_PointH3<FT,RT> &r)
{
 CGAL_exactness_precondition( CGAL_collinear(p, q, r) );
 CGAL_DirectionH3<FT,RT> dir_pr = (p - r).direction();
 CGAL_DirectionH3<FT,RT> dir_qr = (q - r).direction();

 return (dir_pr == -dir_qr);
}

template < class FT, class RT >
CGAL_Bounded_side
CGAL_side_of_bounded_sphere(const CGAL_PointH3<FT,RT> &p,
                            const CGAL_PointH3<FT,RT> &q,
                            const CGAL_PointH3<FT,RT> &r,
                            const CGAL_PointH3<FT,RT> &s,
                            const CGAL_PointH3<FT,RT> &test)
{
 CGAL_Oriented_side  oside = CGAL_side_of_oriented_sphere(p,q,r,s,test);
 if ( CGAL_positive_oriented( p,q,r,s) )
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

template < class FT, class RT >
CGAL_Oriented_side
CGAL_side_of_oriented_sphere(const CGAL_PointH3<FT,RT> &p,
                             const CGAL_PointH3<FT,RT> &q,
                             const CGAL_PointH3<FT,RT> &r,
                             const CGAL_PointH3<FT,RT> &s,
                             const CGAL_PointH3<FT,RT> &test)
{
 CGAL_kernel_precondition( !CGAL_coplanar(p,q,r,s) );
 assert(0); // not implemented
}


#endif // PREDICATES_ON_POINTSH3_H
