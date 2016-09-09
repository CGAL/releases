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
// file          : include/CGAL/predicates_on_pointsH3.h
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


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
  CGAL_exactness_precondition( CGAL_collinear(p, q, r) );
  CGAL_DirectionH3<FT,RT> dir_pr = (p - r).direction();
  CGAL_DirectionH3<FT,RT> dir_qr = (q - r).direction();
  return (dir_pr == -dir_qr);
}


#endif // PREDICATES_ON_POINTSH3_H
