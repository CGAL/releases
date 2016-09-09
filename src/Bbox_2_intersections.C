// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

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
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : src/Bbox_2_intersections.C
// package       : Intersections_2 (2.2.2)
// source        : intersection_2_1.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CARTESIAN_H
#include <CGAL/Cartesian.h>
#endif // CGAL_CARTESIAN_H
#ifndef CGAL_BBOX_2_LINE_2_INTERSECTION_H
#include <CGAL/Bbox_2_Line_2_intersection.h>
#endif // CGAL_BBOX_2_LINE_2_INTERSECTION_H
#ifndef CGAL_RAY_2_BBOX_2_INTERSECTION_H
#include <CGAL/Ray_2_Bbox_2_intersection.h>
#endif // CGAL_RAY_2_BBOX_2_INTERSECTION_H


CGAL_BEGIN_NAMESPACE

template <>
Bbox_2_Line_2_pair< Cartesian<double> >::Bbox_2_Line_2_pair(
    Bbox_2 const *bbox, Line_2< Cartesian<double> > const *line)
{
    _bbox = bbox;
    _line = *line;
    _known = false;
}

CGAL_END_NAMESPACE




CGAL_BEGIN_NAMESPACE

template <>
Ray_2_Bbox_2_pair< Cartesian<double> >::
Ray_2_Bbox_2_pair(
            Ray_2< Cartesian<double> > const *ray,
            Bbox_2 const *box)
{
    _known = false;
    _box = box;
    _ref_point = ray->start();
    _dir = ray->direction().to_vector();
    _min = 0;
}

CGAL_END_NAMESPACE


