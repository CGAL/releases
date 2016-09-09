
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
// file          : include/CGAL/Circle_2_Circle_2_intersection.C
// package       : Intersections_2 (2.11.3)
// source        : intersection_2_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================



#include <CGAL/Circle_2.h>
#include <CGAL/squared_distance_2_1.h>
CGAL_BEGIN_NAMESPACE

template <class R>
bool
do_intersect(const Circle_2<R> & circ1, const Circle_2<R>& circ2)
{
    typedef typename R::FT FT;
    FT sr1 = circ1.squared_radius();
    FT sr2 = circ2.squared_radius();
    FT squared_dist = squared_distance(circ1.center(), circ2.center());
    FT temp = sr1+sr2-squared_dist;
    return !(FT(4)*sr1*sr2 < temp*temp);
}

CGAL_END_NAMESPACE

