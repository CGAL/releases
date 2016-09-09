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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : determinant.fw
// file          : include/CGAL/determinant.h
// package       : Kernel_basic (1.2)
// revision      : 1.2
// revision_date : 12 Jun 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_DETERMINANT_H
#define CGAL_DETERMINANT_H

template <class FT>
inline
FT
CGAL_det2x2_by_formula( const FT& a, const FT& b,
                        const FT& c, const FT& d)
{ return (   a*d - b*c ); }


template <class FT>
CGAL_KERNEL_MEDIUM_INLINE
FT
CGAL_det3x3_by_formula( const FT& a, const FT& b, const FT& c,
                        const FT& d, const FT& e, const FT& f,
                        const FT& g, const FT& h, const FT& i )
{
  return (   a*(e*i - f*h)
           - d*(b*i - c*h)
           + g*(b*f - c*e) );
}


template <class FT>
CGAL_KERNEL_LARGE_INLINE
FT
CGAL_det4x4_by_formula( const FT& a, const FT& b, const FT& c, const FT& d,
                        const FT& e, const FT& f, const FT& g, const FT& h,
                        const FT& i, const FT& j, const FT& k, const FT& l,
                        const FT& m, const FT& n, const FT& o, const FT& p )
{
  return (  a * CGAL_det3x3_by_formula( f, g, h,
                                        j, k, l,
                                        n, o, p )
          - e * CGAL_det3x3_by_formula( b, c, d,
                                        j, k, l,
                                        n, o, p )
          + i * CGAL_det3x3_by_formula( b, c, d,
                                        f, g, h,
                                        n, o, p )
          - m * CGAL_det3x3_by_formula( b, c, d,
                                        f, g, h,
                                        j, k, l ) );
}

template <class FT>
CGAL_KERNEL_LARGE_INLINE
FT
CGAL_det5x5_by_formula(
         const FT& a, const FT& b, const FT& c, const FT& d, const FT e,
         const FT& f, const FT& g, const FT& h, const FT& i, const FT j,
         const FT& k, const FT& l, const FT& m, const FT& n, const FT o,
         const FT& p, const FT& q, const FT& r, const FT& s, const FT t,
         const FT& u, const FT& v, const FT& w, const FT& x, const FT y )
{
  return  a * CGAL_det4x4_by_formula( g, h, i, j,
                                      l, m, n, o,
                                      q, r, s, t,
                                      v, w, x, y  )
        - f * CGAL_det4x4_by_formula( b, c, d, e,
                                      l, m, n, o,
                                      q, r, s, t,
                                      v, w, x, y  )
        + k * CGAL_det4x4_by_formula( b, c, d, e,
                                      g, h, i, j,
                                      q, r, s, t,
                                      v, w, x, y  )
        - p * CGAL_det4x4_by_formula( b, c, d, e,
                                      g, h, i, j,
                                      l, m, n, o,
                                      v, w, x, y  )
        + u * CGAL_det4x4_by_formula( b, c, d, e,
                                      g, h, i, j,
                                      l, m, n, o,
                                      q, r, s, t  );
}



#endif // CGAL_DETERMINANT_H
