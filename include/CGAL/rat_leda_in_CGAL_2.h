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
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/rat_leda_in_CGAL_2.h
// package       : Convex_hull (2.0.8)
// source        : convex_hull_2.lw
// revision      : 2.0.8
// revision_date : 06 May 1999
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef RAT_LEDA_IN_CGAL_H
#define RAT_LEDA_IN_CGAL_H

#include <CGAL/enum.h>
#include <LEDA/rat_point.h>
#include <LEDA/rat_segment.h>
#include <LEDA/rat_line.h>

CGAL_BEGIN_NAMESPACE
inline
bool
leftturn( const leda_rat_point & p, 
          const leda_rat_point & q, 
          const leda_rat_point & r)
{ return ::left_turn(p,q,r); }

inline
bool
rightturn( const leda_rat_point & p, 
                const leda_rat_point & q, 
                const leda_rat_point & r)
{ return ::right_turn(p,q,r); }

/*
#ifndef CGAL_CFG_NO_NAMESPACE
inline
bool
collinear( const leda_rat_point & p, 
           const leda_rat_point & q, 
           const leda_rat_point & r)
{ return ::collinear(p,q,r); }
#endif // CGAL_CFG_NO_NAMESPACE
*/


#ifndef CGAL_CFG_NO_NAMESPACE
inline
Orientation
orientation( const leda_rat_point & p, 
             const leda_rat_point & q, 
             const leda_rat_point & r)
{ return (Orientation)::orientation(p,q,r); }
#endif // CGAL_CFG_NO_NAMESPACE


inline
bool
lexicographically_xy_smaller( const leda_rat_point & p, 
                              const leda_rat_point & q)
{ return ( leda_rat_point::cmp_xy(p,q)  <  0 ); }

inline
bool
lexicographically_yx_smaller( const leda_rat_point & p, 
                              const leda_rat_point & q)
{ return ( leda_rat_point::cmp_yx(p,q)  <  0 ); }

inline
bool
lexicographically_xy_larger( const leda_rat_point & p, 
                             const leda_rat_point & q)
{ return ( leda_rat_point::cmp_xy(p,q)  >  0 ); }

inline
bool
lexicographically_yx_larger( const leda_rat_point & p, 
                             const leda_rat_point & q)
{ return ( leda_rat_point::cmp_yx(p,q)  >  0 ); }

inline
bool
lexicographically_xy_smaller_or_equal( const leda_rat_point & p, 
                                       const leda_rat_point & q)
{ return ( leda_rat_point::cmp_xy(p,q)  <=  0 ); }

inline
bool
lexicographically_yx_smaller_or_equal( const leda_rat_point & p, 
                                       const leda_rat_point & q)
{ return ( leda_rat_point::cmp_yx(p,q)  <=  0 ); }

inline 
Comparison_result
compare_lexicographically_xy(const leda_rat_point & p, 
                             const leda_rat_point & q)
{ return (Comparison_result)leda_rat_point::cmp_xy(p,q); }

inline 
Comparison_result
compare_lexicographically_yx(const leda_rat_point & p, 
                             const leda_rat_point & q)
{ return (Comparison_result)leda_rat_point::cmp_yx(p,q); }

inline
bool
collinear_are_ordered_along_line( const leda_rat_point & p, 
                                  const leda_rat_point & q, 
                                  const leda_rat_point & r)
{ return leda_rat_segment(p,r).contains(q); }  

inline
bool
collinear_are_strictly_ordered_along_line( const leda_rat_point & p, 
                                           const leda_rat_point & q, 
                                           const leda_rat_point & r)
{ return (leda_rat_segment(p,r).contains(q) && ( q != p ) && ( q != r )); }  

inline
bool
are_ordered_along_line( const leda_rat_point & p, 
                        const leda_rat_point & q, 
                        const leda_rat_point & r)
{ return ( collinear(p,q,r) &&  collinear_are_ordered_along_line(p,q,r)); }  

inline
bool
are_strictly_ordered_along_line( const leda_rat_point & p, 
                                 const leda_rat_point & q, 
                                 const leda_rat_point & r)
{ 
  return (    collinear(p,q,r) 
           && collinear_are_strictly_ordered_along_line(p,q,r)
         ); 
}  

inline
Comparison_result 
cmp_signed_dist_to_line(const leda_rat_point& p, const leda_rat_point& q,
                        const leda_rat_point& r, const leda_rat_point& s)
{
#if ( __LEDA__ >= 360 )
  return (Comparison_result)::cmp_signed_dist(p,q,r,s);
#else
  leda_rat_line  l(p,q);
  int  r_or = ::orientation( l, r );
  int  s_or = ::orientation( l, s );
  if ( r_or != s_or )
  {
      return (Comparison_result)( r_or < s_or );
  }
  else
  {
      return 
        (Comparison_result)(r_or *( CGAL::sign(l.sqr_dist(r) - l.sqr_dist(s) )));
  }
#endif  // __LEDA__ >= 360
}

inline
bool
has_smaller_signed_dist_to_line(const leda_rat_point& p, const leda_rat_point& q,
                                const leda_rat_point& r, const leda_rat_point& s)
{ return ( cmp_signed_dist_to_line(p,q,r,s) == SMALLER ); }

inline
bool
has_larger_signed_dist_to_line(const leda_rat_point& p, const leda_rat_point& q,
                               const leda_rat_point& r, const leda_rat_point& s)
{ return ( cmp_signed_dist_to_line(p,q,r,s) == LARGER ); }

CGAL_END_NAMESPACE

#endif // RAT_LEDA_IN_CGAL_H
