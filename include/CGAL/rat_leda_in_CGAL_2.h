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

#ifndef RAT_LEDA_IN_CGAL_H
#define RAT_LEDA_IN_CGAL_H

#include <CGAL/enum.h>
#include <LEDA/rat_point.h>
#include <LEDA/rat_segment.h>

inline
bool
CGAL_leftturn( const rat_point & p, const rat_point & q, const rat_point & r)
{
  return  left_turn(p,q,r);
}

inline
bool
CGAL_rightturn( const rat_point & p, const rat_point & q, const rat_point & r)
{
  return  right_turn(p,q,r);
}

inline
CGAL_Orientation
CGAL_orientation( const rat_point & p, const rat_point & q, const rat_point & r)
{
  return (CGAL_Orientation)orientation(p,q,r);
}


inline
bool
CGAL_lexicographically_xy_smaller( const rat_point & p, const rat_point & q)
{
  return ( rat_point::cmp_xy(p,q) == -1 );
}

inline
bool
CGAL_lexicographically_yx_smaller( const rat_point & p, const rat_point & q)
{
  return ( rat_point::cmp_yx(p,q) == -1 );
}

inline
bool
CGAL_lexicographically_xy_larger( const rat_point & p, const rat_point & q)
{
  return ( rat_point::cmp_xy(p,q) ==  1 );
}

inline
bool
CGAL_lexicographically_yx_larger( const rat_point & p, const rat_point & q)
{
  return ( rat_point::cmp_yx(p,q) ==  1 );
}

inline
bool
CGAL_collinear_are_ordered_along_line( const rat_point & p, 
                                       const rat_point & q, 
                                       const rat_point & r)
{
  return (rat_segment(p,r).contains(q) && ( q != p ) && ( q != r ));
}  


#endif // RAT_LEDA_IN_CGAL_H

