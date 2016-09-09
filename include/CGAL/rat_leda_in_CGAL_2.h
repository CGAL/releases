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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/rat_leda_in_CGAL_2.h
// package       : Convex_hull (1.3.2)
// source        : convex_hull_2.lw
// revision      : 1.3.2
// revision_date : 09 Dec 1998
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef RAT_LEDA_IN_CGAL_H
#define RAT_LEDA_IN_CGAL_H

#include <CGAL/enum.h>
#include <LEDA/rat_point.h>
#include <LEDA/rat_segment.h>
#include <LEDA/rat_line.h>

inline
bool
CGAL_leftturn( const leda_rat_point & p, 
               const leda_rat_point & q, 
               const leda_rat_point & r)
{ return  left_turn(p,q,r); }

inline
bool
CGAL_rightturn( const leda_rat_point & p, 
                const leda_rat_point & q, 
                const leda_rat_point & r)
{ return  right_turn(p,q,r); }

inline
bool
CGAL_collinear( const leda_rat_point & p, 
                const leda_rat_point & q, 
                const leda_rat_point & r)
{ return  collinear(p,q,r); }

inline
CGAL_Orientation
CGAL_orientation( const leda_rat_point & p, 
                  const leda_rat_point & q, 
                  const leda_rat_point & r)
{ return (CGAL_Orientation)orientation(p,q,r); }

inline
bool
CGAL_lexicographically_xy_smaller( const leda_rat_point & p, 
                                   const leda_rat_point & q)
{ return ( leda_rat_point::cmp_xy(p,q)  <  0 ); }

inline
bool
CGAL_lexicographically_yx_smaller( const leda_rat_point & p, 
                                   const leda_rat_point & q)
{ return ( leda_rat_point::cmp_yx(p,q)  <  0 ); }

inline
bool
CGAL_lexicographically_xy_larger( const leda_rat_point & p, 
                                  const leda_rat_point & q)
{ return ( leda_rat_point::cmp_xy(p,q)  >  0 ); }

inline
bool
CGAL_lexicographically_yx_larger( const leda_rat_point & p, 
                                  const leda_rat_point & q)
{ return ( leda_rat_point::cmp_yx(p,q)  >  0 ); }

inline
bool
CGAL_lexicographically_xy_smaller_or_equal( const leda_rat_point & p, 
                                            const leda_rat_point & q)
{ return ( leda_rat_point::cmp_xy(p,q)  <=  0 ); }

inline
bool
CGAL_lexicographically_yx_smaller_or_equal( const leda_rat_point & p, 
                                            const leda_rat_point & q)
{ return ( leda_rat_point::cmp_yx(p,q)  <=  0 ); }

inline 
CGAL_Comparison_result
CGAL_compare_lexicographically_xy(const leda_rat_point & p, 
                                  const leda_rat_point & q)
{ return (CGAL_Comparison_result)leda_rat_point::cmp_xy(p,q); }

inline 
CGAL_Comparison_result
CGAL_compare_lexicographically_yx(const leda_rat_point & p, 
                                  const leda_rat_point & q)
{ return (CGAL_Comparison_result)leda_rat_point::cmp_yx(p,q); }

inline
bool
CGAL_collinear_are_ordered_along_line( const leda_rat_point & p, 
                                       const leda_rat_point & q, 
                                       const leda_rat_point & r)
{ return leda_rat_segment(p,r).contains(q); }  

inline
bool
CGAL_collinear_are_strictly_ordered_along_line( const leda_rat_point & p, 
                                                const leda_rat_point & q, 
                                                const leda_rat_point & r)
{ return (leda_rat_segment(p,r).contains(q) && ( q != p ) && ( q != r )); }  

inline
bool
CGAL_are_ordered_along_line( const leda_rat_point & p, 
                             const leda_rat_point & q, 
                             const leda_rat_point & r)
{ return ( CGAL_collinear(p,q,r) &&  CGAL_collinear_are_ordered_along_line(p,q,r)); }  

inline
bool
CGAL_are_strictly_ordered_along_line( const leda_rat_point & p, 
                                      const leda_rat_point & q, 
                                      const leda_rat_point & r)
{ 
  return (    CGAL_collinear(p,q,r) 
           && CGAL_collinear_are_strictly_ordered_along_line(p,q,r)
         ); 
}  

inline
CGAL_Comparison_result 
CGAL_cmp_signed_dist_to_line(const leda_rat_point& p, const leda_rat_point& q,
                             const leda_rat_point& r, const leda_rat_point& s)
{
#if ( __LEDA__ >= 360 )
  return (CGAL_Comparison_result)cmp_signed_dist(p,q,r,s);
#else
  leda_rat_line  l(p,q);
  int  r_or = orientation( l, r );
  int  s_or = orientation( l, s );
  if ( r_or != s_or )
  {
      return (CGAL_Comparison_result)( r_or < s_or );
  }
  else
  {
      return 
        (CGAL_Comparison_result)(r_or *( sign(l.sqr_dist(r) - l.sqr_dist(s) )));
  }
#endif  // __LEDA__ >= 360
}

inline
bool
CGAL_has_smaller_signed_dist_to_line(const leda_rat_point& p, const leda_rat_point& q,
                                     const leda_rat_point& r, const leda_rat_point& s)
{ return ( CGAL_cmp_signed_dist_to_line(p,q,r,s) == CGAL_SMALLER ); }

inline
bool
CGAL_has_larger_signed_dist_to_line(const leda_rat_point& p, const leda_rat_point& q,
                                    const leda_rat_point& r, const leda_rat_point& s)
{ return ( CGAL_cmp_signed_dist_to_line(p,q,r,s) == CGAL_LARGER ); }


#endif // RAT_LEDA_IN_CGAL_H
