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
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : src/Bbox_2_intersections.C
// package       : Intersections_2 (2.1.2)
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
    _dir = ray->direction().vector();
    _min = 0;
}

CGAL_END_NAMESPACE


