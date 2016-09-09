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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/leda_in_CGAL_2.h
// package       : Convex_hull (3.3)
// source        : convex_hull_2.lw
// revision      : 3.3
// revision_date : 03 Aug 2000
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef LEDA_IN_CGAL_H
#define LEDA_IN_CGAL_H

#include <CGAL/enum.h>
#include <LEDA/point.h>
#include <LEDA/segment.h>
#include <LEDA/line.h>

CGAL_BEGIN_NAMESPACE
inline
bool
leftturn( const leda_point & p, 
          const leda_point & q, 
          const leda_point & r)
{ return  left_turn(p,q,r); }

inline
bool
rightturn( const leda_point & p, 
           const leda_point & q, 
           const leda_point & r)
{ return  right_turn(p,q,r); }

#ifndef CGAL_CFG_NO_NAMESPACE
inline
Orientation
orientation( const leda_point & p, 
             const leda_point & q, 
             const leda_point & r)
{ return (Orientation)::orientation(p,q,r); }
#endif // CGAL_CFG_NO_NAMESPACE

inline
bool
lexicographically_xy_smaller( const leda_point & p, 
                              const leda_point & q)
{ return ( leda_point::cmp_xy(p,q)  <  0 ); }

inline
bool
lexicographically_yx_smaller( const leda_point & p, 
                              const leda_point & q)
{ return ( leda_point::cmp_yx(p,q)  <  0 ); }

inline
bool
lexicographically_xy_larger( const leda_point & p, 
                             const leda_point & q)
{ return ( leda_point::cmp_xy(p,q)  >  0 ); }

inline
bool
lexicographically_yx_larger( const leda_point & p, 
                             const leda_point & q)
{ return ( leda_point::cmp_yx(p,q)  >  0 ); }

inline
bool
collinear_are_ordered_along_line( const leda_point & p, 
                                  const leda_point & q, 
                                  const leda_point & r)
{ 
  return 
  (  (( leda_point::cmp_xy(p,q)<=0 )&&( leda_point::cmp_xy(q,r)<=0 )) 
   ||(( leda_point::cmp_xy(r,q)<=0 )&&( leda_point::cmp_xy(q,p)<=0 )) );
}

inline
Comparison_result 
cmp_signed_dist_to_line( const leda_point & p, const leda_point & q,
                         const leda_point & r, const leda_point & s )
{
#if ( __LEDA__ >= 360 )
  return (Comparison_result)::cmp_signed_dist(p,q,r,s);
#else
  leda_line  l(p,q);
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
CGAL_END_NAMESPACE

#endif // LEDA_IN_CGAL_H
