// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/min_sqr_distance.h
// package       : bops (2.4)
// source        : include/CGAL/min_sqr_distance.h
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1999/10/11 13:50:32 $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_MIN_SQR_DISTANCE_H
#define CGAL_MIN_SQR_DISTANCE_H

CGAL_BEGIN_NAMESPACE

template <class ForwardIterator, class I>
double minimal_square_distance2(ForwardIterator first,
			        ForwardIterator last,
			        I& T)
/*
   ----------------------------------------------------------
   Calculates the minimal square distance of a set of points
   in O(n^2) time and returns the (double) result;
   ----------------------------------------------------------
*/
;
 


template <class ForwardIterator, class I>
double minimal_square_distance(ForwardIterator first,
			       ForwardIterator last,
			       I& T)
/*
   ----------------------------------------------------------
   Calculates the minimal square distance of a set of points
   in O(n log(n)) time by doing a sweep-line algorithm and
   returns the (double) result;

   See:
     K.Hinrichs, J.Nievergelt, P.Schorn,
     "Plane-sweep solves the closest pair problem elegantly",
     Inform. Process. Lett., 26, 1988, p. 255-261.
   or
     Rolf Klein: "Algorithmische Geometrie", chapter 2.3.1
   ----------------------------------------------------------
*/
;

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/min_sqr_distance.C>
#endif

#endif // CGAL_MIN_SQR_DISTANCE_H
