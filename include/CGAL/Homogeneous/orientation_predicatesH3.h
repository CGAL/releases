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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.4
// release_date  : 2002, May 16
// 
// file          : include/CGAL/Homogeneous/orientation_predicatesH3.h
// package       : H3 (2.49)
// revision      : $Revision: 1.1 $
// revision_date : $Date: 2001/10/16 16:01:39 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_ORIENTATION_PREDICATESH3_H
#define CGAL_ORIENTATION_PREDICATESH3_H

#include <CGAL/Homogeneous/PointH3.h>
#include <CGAL/Homogeneous/predicates_on_rtH2.h>
#include <CGAL/predicates/sign_of_determinant.h>

CGAL_BEGIN_NAMESPACE

template < class R>
CGAL_KERNEL_INLINE
Orientation
orientation( const PointH3<R>& p,
             const PointH3<R>& q,
             const PointH3<R>& r,
             const PointH3<R>& s)
{
  // Two rows are switched, because of the homogeneous column.
  return (Orientation) sign_of_determinant4x4( p.hx(), p.hy(), p.hz(), p.hw(),
                                               r.hx(), r.hy(), r.hz(), r.hw(),
                                               q.hx(), q.hy(), q.hz(), q.hw(),
                                               s.hx(), s.hy(), s.hz(), s.hw());
}

template < class R>
inline
bool
are_positive_oriented( const PointH3<R>& p,
                       const PointH3<R>& q,
                       const PointH3<R>& r,
                       const PointH3<R>& s)
{ return (orientation(p,q,r,s) == POSITIVE); }

template < class R>
inline
bool
are_negative_oriented( const PointH3<R>& p,
                       const PointH3<R>& q,
                       const PointH3<R>& r,
                       const PointH3<R>& s)
{ return (orientation(p,q,r,s) == NEGATIVE); }

template < class R>
inline
bool
coplanar( const PointH3<R>& p,
          const PointH3<R>& q,
          const PointH3<R>& r,
          const PointH3<R>& s)
{ return (orientation(p,q,r,s) == COPLANAR); }


template <class R>
Orientation
coplanar_orientation(const PointH3<R>& p,
                     const PointH3<R>& q,
                     const PointH3<R>& r,
                     const PointH3<R>& s)
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

template <class R>
CGAL_KERNEL_LARGE_INLINE
Orientation
coplanar_orientation(const PointH3<R>& p,
                     const PointH3<R>& q,
                     const PointH3<R>& r)
// Returns an Orientation which is coherent for all (p,q,r) chosen in a same
// plane.
{
  Orientation oxy_pqr = orientationH2(p.hx(), p.hy(), p.hw(),
	                              q.hx(), q.hy(), q.hw(),
				      r.hx(), r.hy(), r.hw());
  if (oxy_pqr != COLLINEAR)
      return oxy_pqr;

  Orientation oyz_pqr = orientationH2(p.hy(), p.hz(), p.hw(),
	                              q.hy(), q.hz(), q.hw(),
				      r.hy(), r.hz(), r.hw());
  if (oyz_pqr != COLLINEAR)
      return oyz_pqr;

  return orientationH2(p.hx(), p.hz(), p.hw(),
	               q.hx(), q.hz(), q.hw(),
		       r.hx(), r.hz(), r.hw());
}

CGAL_END_NAMESPACE

#endif // CGAL_ORIENTATION_PREDICATESH3_H
