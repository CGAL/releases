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


// Author: Geert-Jan Giezeman

#ifndef CGAL_SQUARED_DISTANCE_2_2_H
#define CGAL_SQUARED_DISTANCE_2_2_H

#include <CGAL/user_classes.h>
#include <CGAL/workaround_010.h>



template <class R>
extern void
CGAL_distance_index(
    int &ind1,
    int &ind2,
    const CGAL_Point_2<R> &pt,
    const CGAL_Triangle_2<R> &triangle);

template <class R>
extern R_FT_return(R)
CGAL_squared_distance_indexed(const CGAL_Point_2<R> &pt,
    const CGAL_Triangle_2<R> &triangle, int ind1, int ind2);
template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Point_2<R> &pt,
    const CGAL_Triangle_2<R> &triangle);


template <class R>
inline R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> & triangle,
    const CGAL_Point_2<R> & pt)
{
    return CGAL_squared_distance(pt, triangle);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Line_2<R> &line,
    const CGAL_Triangle_2<R> &triangle);


template <class R>
inline R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> & triangle,
    const CGAL_Line_2<R> & line)
{
    return CGAL_squared_distance(line, triangle);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Ray_2<R> &ray,
    const CGAL_Triangle_2<R> &triangle);


template <class R>
inline R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> & triangle,
    const CGAL_Ray_2<R> & ray)
{
    return CGAL_squared_distance(ray, triangle);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Triangle_2<R> &triangle);


template <class R>
inline R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> & triangle,
    const CGAL_Segment_2<R> & seg)
{
    return CGAL_squared_distance(seg, triangle);
}

template <class R>
extern R_FT_return(R)
CGAL_squared_distance(
    const CGAL_Triangle_2<R> &triangle1,
    const CGAL_Triangle_2<R> &triangle2);



#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/squared_distance_2_2.C>
#endif


#endif
