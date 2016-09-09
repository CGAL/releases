//  -*- Mode: c++ -*-
// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/bops_Container_Polygon_2.h
// package       : bops (1.0.5)
// source        : include/CGAL/bops_Container_Polygon_2.h
// revision      : $Revision: 1.0.5 $
// revision_date : $Date: Tue Jun 30 19:04:24 MET DST 1998  $
// author(s)     :         Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BOPS_CONTAINER_POLYGON_2_H
#define CGAL_BOPS_CONTAINER_POLYGON_2_H


/***********************************/ 
/* For Polygons with traits class: */
/***********************************/ 


template < class ForwardIterator, class Traits >
bool CGAL_do_intersect( ForwardIterator Afirst, ForwardIterator Alast,
		        ForwardIterator Bfirst, ForwardIterator Blast,
		        Traits &);


template < class ForwardIterator, class OutputIterator, class Traits >
OutputIterator
CGAL_intersection( ForwardIterator Afirst, ForwardIterator Alast,
     	           ForwardIterator Bfirst, ForwardIterator Blast,
                   Traits &, OutputIterator list_of_objects_it);


template < class ForwardIterator, class OutputIterator, class Traits >
OutputIterator
CGAL_union(        ForwardIterator Afirst, ForwardIterator Alast,
                   ForwardIterator Bfirst, ForwardIterator Blast,
		   Traits &, OutputIterator list_of_objects_it);


template < class ForwardIterator, class OutputIterator, class Traits >
OutputIterator
CGAL_difference(   ForwardIterator Afirst, ForwardIterator Alast,
		   ForwardIterator Bfirst, ForwardIterator Blast,
		   Traits &, OutputIterator list_of_objects_it);

 
 
#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/bops_Container_Polygon_2.C>
#endif

#endif // CGAL_BOPS_CONTAINER_POLYGON_2_H
