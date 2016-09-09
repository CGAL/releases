// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : predicates_on_pointsH3.fw
// file          : include/CGAL/orientation_predicatesH3.h
// package       : H3 (2.2.1)
// revision      : 2.2.1
// revision_date : 26 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef ORIENTATION_PREDICATESH3_H
#define ORIENTATION_PREDICATESH3_H

#ifndef CGAL_PVDH3_H
#include <CGAL/PVDH3.h>
#endif // CGAL_PVDH3_H

CGAL_BEGIN_NAMESPACE

template < class FT, class RT>
CGAL_KERNEL_INLINE
Orientation
orientation( const PointH3<FT,RT>& p,
                  const PointH3<FT,RT>& q,
                  const PointH3<FT,RT>& r,
                  const PointH3<FT,RT>& s)
{
  RT det = det4x4_by_formula(
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
      return COPLANAR;
  }
  else
  {
      return det < RT(0) ? POSITIVE : NEGATIVE;
      // switched, because the determinant above has the 1-row at the end
  }
}

template < class FT, class RT>
inline
bool
are_positive_oriented( const PointH3<FT,RT>& p,
                            const PointH3<FT,RT>& q,
                            const PointH3<FT,RT>& r,
                            const PointH3<FT,RT>& s)
{ return (orientation(p,q,r,s) == POSITIVE); }

template < class FT, class RT>
inline
bool
are_negative_oriented( const PointH3<FT,RT>& p,
                            const PointH3<FT,RT>& q,
                            const PointH3<FT,RT>& r,
                            const PointH3<FT,RT>& s)
{ return (orientation(p,q,r,s) == NEGATIVE); }

template < class FT, class RT>
inline
bool
coplanar( const PointH3<FT,RT>& p,
               const PointH3<FT,RT>& q,
               const PointH3<FT,RT>& r,
               const PointH3<FT,RT>& s)
{ return (orientation(p,q,r,s) == COPLANAR); }

CGAL_END_NAMESPACE


#endif // ORIENTATION_PREDICATESH3_H
