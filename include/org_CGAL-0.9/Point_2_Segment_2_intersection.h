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

#ifndef CGAL_POINT_2_SEGMENT_2_INTERSECTION_H
#define CGAL_POINT_2_SEGMENT_2_INTERSECTION_H

#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>


template <class R>
inline bool
CGAL_do_intersect(const CGAL_Point_2<R> &pt, const CGAL_Segment_2<R> &seg)
{
    return seg.has_on(pt);
}

#include <CGAL/Object.h>

template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Point_2<R> &pt, const CGAL_Segment_2<R> &seg)
{
    if (CGAL_do_intersect(pt,seg)) {
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(pt));
    }
    return CGAL_Object();
}


template <class R>
inline bool
CGAL_do_intersect(const CGAL_Segment_2<R> &seg, const CGAL_Point_2<R> &pt)
{
    return seg.has_on(pt);
}


template <class R>
inline CGAL_Object
CGAL_intersection(const CGAL_Segment_2<R> &seg, const CGAL_Point_2<R> &pt)
{
    if (CGAL_do_intersect(pt,seg)) {
        return CGAL_Object(new CGAL_Wrapper< CGAL_Point_2<R> >(pt));
    }
    return CGAL_Object();
}

#endif
