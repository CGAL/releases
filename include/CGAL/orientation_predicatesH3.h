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
// file          : include/CGAL/orientation_predicatesH3.h
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef ORIENTATION_PREDICATESH3_H
#define ORIENTATION_PREDICATESH3_H

#ifndef CGAL_PVDH3_H
#include <CGAL/PVDH3.h>
#endif // CGAL_PVDH3_H

template < class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_Orientation
CGAL_orientation( const CGAL_PointH3<FT,RT>& p,
                  const CGAL_PointH3<FT,RT>& q,
                  const CGAL_PointH3<FT,RT>& r,
                  const CGAL_PointH3<FT,RT>& s)
{
  RT det = CGAL_det4x4_by_formula(
               p.hx(), p.hy(), p.hz(), p.hw(),
               q.hx(), q.hy(), q.hz(), q.hw(),
               r.hx(), r.hy(), r.hz(), r.hw(),
               s.hx(), s.hy(), s.hz(), s.hw() );
/*
  RT det= - p.hw()*(  q.hx()*( r.hy()*s.hz() - r.hz()*s.hy() )
                    - r.hx()*( q.hy()*s.hz() - q.hz()*s.hy() )
                    + s.hx()*( q.hy()*r.hz() - q.hz()*r.hy() ) )
          + q.hw()*(  p.hx()*( r.hy()*s.hz() - r.hz()*s.hy() )
                    - r.hx()*( p.hy()*s.hz() - p.hz()*s.hy() )
                   + s.hx()*( p.hy()*r.hz() - p.hz()*r.hy() ) )
          - r.hw()*(  p.hx()*( q.hy()*s.hz() - q.hz()*s.hy() )
                    - q.hx()*( p.hy()*s.hz() - p.hz()*s.hy() )
                    + s.hx()*( p.hy()*q.hz() - p.hz()*q.hy() ) )
          + s.hw()*(  p.hx()*( q.hy()*r.hz() - q.hz()*r.hy() )
                    - q.hx()*( p.hy()*r.hz() - p.hz()*r.hy() )
                    + r.hx()*( p.hy()*q.hz() - p.hz()*q.hy() ) ) ;
*/
  if (det == RT(0))
  {
      return CGAL_COPLANAR;
  }
  else
  {
      return det < RT(0) ? CGAL_POSITIVE : CGAL_NEGATIVE;
      // switched, because the determinant above has the 1-row at the end
  }
}

template < class FT, class RT>
inline
bool
CGAL_are_positive_oriented( const CGAL_PointH3<FT,RT>& p,
                            const CGAL_PointH3<FT,RT>& q,
                            const CGAL_PointH3<FT,RT>& r,
                            const CGAL_PointH3<FT,RT>& s)
{ return (CGAL_orientation(p,q,r,s) == CGAL_POSITIVE); }

template < class FT, class RT>
inline
bool
CGAL_are_negative_oriented( const CGAL_PointH3<FT,RT>& p,
                            const CGAL_PointH3<FT,RT>& q,
                            const CGAL_PointH3<FT,RT>& r,
                            const CGAL_PointH3<FT,RT>& s)
{ return (CGAL_orientation(p,q,r,s) == CGAL_NEGATIVE); }

template < class FT, class RT>
inline
bool
CGAL_coplanar( const CGAL_PointH3<FT,RT>& p,
               const CGAL_PointH3<FT,RT>& q,
               const CGAL_PointH3<FT,RT>& r,
               const CGAL_PointH3<FT,RT>& s)
{ return (CGAL_orientation(p,q,r,s) == CGAL_COPLANAR); }

#endif // ORIENTATION_PREDICATESH3_H
