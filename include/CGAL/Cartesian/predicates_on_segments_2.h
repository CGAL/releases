// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Cartesian/predicates_on_segments_2.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2002/01/23 17:59:17 $
// author(s)     : Susan Hert
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_PREDICATES_ON_SEGMENTS_2_H
#define CGAL_CARTESIAN_PREDICATES_ON_SEGMENTS_2_H

#include <CGAL/Cartesian/Point_2.h>
#include <CGAL/Cartesian/Segment_2.h>
#include <CGAL/predicates/kernel_ftC2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
Comparison_result
compare_slopes(const SegmentC2<R> &s1,
               const SegmentC2<R> &s2)
{
   return compare_slopesC2(s1.source().x(), s1.source().y(),
                           s1.target().x(), s1.target().y(),
                           s2.source().x(), s2.source().y(),
                           s2.target().x(), s2.target().y());
}

template < class R >
Comparison_result
compare_y_at_x(const PointC2<R> &p,
               const SegmentC2<R> &s)
{
    return compare_y_at_xC2(p.x(), p.y(),
	                    s.source().x(), s.source().y(),
	                    s.target().x(), s.target().y());
}

template < class R >
Comparison_result
compare_y_at_x(const PointC2<R> &p,
               const SegmentC2<R> &s1,
               const SegmentC2<R> &s2)
{
    return compare_y_at_x_segment_C2(p.x(),
	                    s1.source().x(), s1.source().y(),
	                    s1.target().x(), s1.target().y(),
	                    s2.source().x(), s2.source().y(),
	                    s2.target().x(), s2.target().y());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_PREDICATES_ON_SEGMENTS_2_H
