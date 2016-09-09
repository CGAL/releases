// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : predicates_on_pointsH3.fw
// file          : include/CGAL/orientation_predicatesH3.h
// package       : H3 (2.12)
// revision      : 2.12
// revision_date : 16 Aug 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_ORIENTATION_PREDICATESH3_H
#define CGAL_ORIENTATION_PREDICATESH3_H

#ifndef CGAL_PVDH3_H
#include <CGAL/PVDH3.h>
#endif // CGAL_PVDH3_H

#include <CGAL/predicates_on_rtH2.h>

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


template <class FT, class RT>
Orientation
coplanar_orientation(const PointH3<FT,RT>& p,
                     const PointH3<FT,RT>& q,
                     const PointH3<FT,RT>& r,
                     const PointH3<FT,RT>& s)
// p,q,r,s supposed to be coplanar
// p, q, r supposed to be non collinear
// tests whether s is on the same side of p,q as r
// returns :
// COLLINEAR if pqs collinear
// POSITIVE if pqr and pqs have the same orientation
// NEGATIVE if pqr and pqs have opposite orientations
{
  CGAL_kernel_precondition( coplanar( p, q, r, s));
  // p, q, r define a plane P:
  CGAL_kernel_precondition( !collinear( p, q, r));
  // compute orientation of p,q,s in this plane P:
  Orientation save;
  if ( (save = orientationH2( p.hy(), p.hz(), p.hw(),
                              q.hy(), q.hz(), q.hw(),
                              r.hy(), r.hz(), r.hw())) != COLLINEAR)
  { return
      static_cast<Orientation>(
        static_cast<int>( save)
      * static_cast<int>( orientationH2( p.hy(), p.hz(), p.hw(),
                                         q.hy(), q.hz(), q.hw(),
                                         s.hy(), s.hz(), s.hw())) );
  }
  if ( (save = orientationH2( p.hx(), p.hz(), p.hw(),
                              q.hx(), q.hz(), q.hw(),
                              r.hx(), r.hz(), r.hw())) != COLLINEAR)
  { return
      static_cast<Orientation>(
        static_cast<int>( save)
      * static_cast<int>( orientationH2( p.hx(), p.hz(), p.hw(),
                                         q.hx(), q.hz(), q.hw(),
                                         s.hx(), s.hz(), s.hw())) );
  }
  if ( (save = orientationH2( p.hx(), p.hy(), p.hw(),
                              q.hx(), q.hy(), q.hw(),
                              r.hx(), r.hy(), r.hw())) != COLLINEAR)
  { return
      static_cast<Orientation>(
        static_cast<int>( save)
      * static_cast<int>( orientationH2( p.hx(), p.hy(), p.hw(),
                                         q.hx(), q.hy(), q.hw(),
                                         s.hx(), s.hy(), s.hw())) );
  }
  CGAL_kernel_assertion( false);
  return COLLINEAR;
}

CGAL_END_NAMESPACE


#endif // ORIENTATION_PREDICATESH3_H
