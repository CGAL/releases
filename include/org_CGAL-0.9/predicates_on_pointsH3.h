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


// Source: predicates_on_pointsH3.h
// Author: Stefan Schirra

#ifndef PREDICATES_ON_POINTSH3_H
#define PREDICATES_ON_POINTSH3_H

#include <CGAL/PVDH3.h>

template < class FT, class RT >
inline
bool 
CGAL_x_equal(const CGAL_PointH3<FT,RT> &p,
             const CGAL_PointH3<FT,RT> &q)
{
  return p.x()*q.hw() == q.x()*p.hw();
}

template < class FT, class RT >
inline
bool 
CGAL_y_equal(const CGAL_PointH3<FT,RT> &p,
             const CGAL_PointH3<FT,RT> &q)
{
  return p.y()*q.hw() == q.y()*p.hw();
}

template < class FT, class RT >
inline
bool 
CGAL_z_equal(const CGAL_PointH3<FT,RT> &p,
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

template < class FT, class RT >
inline
CGAL_Comparison_result 
CGAL_compare_x(const CGAL_PointH3<FT,RT> &p, const CGAL_PointH3<FT,RT> &q)
{
  return CGAL_compare(p.hx() * q.hw(), q.hx() * p.hw() );
}


template < class FT, class RT >
inline
CGAL_Comparison_result 
CGAL_compare_y(const CGAL_PointH3<FT,RT> &p, const CGAL_PointH3<FT,RT> &q)
{
  return CGAL_compare(p.hy() * q.hw(), q.hy() * p.hw() );
}


template < class FT, class RT >
inline
CGAL_Comparison_result 
CGAL_compare_z(const CGAL_PointH3<FT,RT> &p, const CGAL_PointH3<FT,RT> &q)
{
  return CGAL_compare(p.hz() * q.hw(), q.hz() * p.hw() );
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
inline
bool
CGAL_collinear_are_ordered_along_line(const CGAL_PointH3<FT,RT> &p,
                       const CGAL_PointH3<FT,RT> &q,
                       const CGAL_PointH3<FT,RT> &r)
{
 CGAL_exactness_precondition( CGAL_collinear(p, q, r) );
 CGAL_DirectionH3<FT,RT> dir_pr = (p - r).direction();
 CGAL_DirectionH3<FT,RT> dir_qr = (q - r).direction();

 return (dir_pr == -dir_qr);
}


#endif // PREDICATES_ON_POINTSH3_H
