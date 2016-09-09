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


// Source: boolean_operations_2.h
// Author: Wolfgang Freiseisen
 
#ifndef CGAL_BOOLEAN_OPERATIONS_2_H
#define CGAL_BOOLEAN_OPERATIONS_2_H


#include <CGAL/basic.h>
#include <CGAL/Object.h>
//#include <CGAL/gnu_istream_iterator_value_type_fix.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <list.h>

#include <CGAL/Polygon_2.h>
#include <CGAL/intersection_2.h>
#include <CGAL/bops_2.h>

/***********************************/ 
/* For Polygons with traits class: */
/***********************************/ 

template < class InputIterator, class I >
bool CGAL_do_intersect( InputIterator Afirst, InputIterator Alast,
		        InputIterator Bfirst, InputIterator Blast,
		        I &);

template < class InputIterator, class OutputIterator, class I >
OutputIterator
CGAL_intersection( InputIterator Afirst, InputIterator Alast,
     	           InputIterator Bfirst, InputIterator Blast,
                   I &, OutputIterator list_of_objects_it);

template < class InputIterator, class OutputIterator, class I >
OutputIterator
CGAL_union(        InputIterator Afirst, InputIterator Alast,
                   InputIterator Bfirst, InputIterator Blast,
		   I &, OutputIterator list_of_objects_it);

template < class InputIterator, class OutputIterator, class I >
OutputIterator
CGAL_difference(   InputIterator Afirst, InputIterator Alast,
		   InputIterator Bfirst, InputIterator Blast,
		   I &, OutputIterator list_of_objects_it);

 
/**************************/ 
/* For CGAL Objects only: */
/**************************/ 

template < class R, class Container >
bool CGAL_do_intersect( const CGAL_Polygon_2<R, Container>& A,
                        const CGAL_Polygon_2<R, Container>& B);

template < class R, class Container, class OutputIterator >
OutputIterator
CGAL_intersection( const CGAL_Polygon_2<R, Container>& A,
                   const CGAL_Polygon_2<R, Container>& B,
                   OutputIterator list_of_objects_it);

/*
#include <CGAL/Triangle_2_Triangle_2_intersection.h>
bool 
CGAL_do_intersect( const CGAL_Triangle_2<R>& A,
                   const CGAL_Triangle_2<R>& B);
OutputIterator
CGAL_intersection( const CGAL_Triangle_2<R>& A,
                   const CGAL_Triangle_2<R>& B,
                   OutputIterator object_it);
NOT IMPLEMENTED YET*/

/*
#include <CGAL/Iso_rectangle_2_Iso_rectangle_2_intersection.h>
bool 
CGAL_do_intersect( const CGAL_Iso_rectangle_2<R>& A,
                   const CGAL_Iso_rectangle_2<R>& B);
OutputIterator
CGAL_intersection( const CGAL_Iso_rectangle_2<R>& A,
                   const CGAL_Iso_rectangle_2<R>& B,
                   OutputIterator object_it);
NOT IMPLEMENTED YET*/


template < class R, class OutputIterator >
OutputIterator
CGAL_union(        const CGAL_Triangle_2<R>& A,
                   const CGAL_Triangle_2<R>& B,
                   OutputIterator object_it);
 
 
template < class R, class OutputIterator >
OutputIterator
CGAL_union(        const CGAL_Iso_rectangle_2<R>& A,
                   const CGAL_Iso_rectangle_2<R>& B,
                   OutputIterator object_it);
 
template < class R, class Container, class OutputIterator >
OutputIterator
CGAL_union(        const CGAL_Polygon_2<R, Container>& A,
                   const CGAL_Polygon_2<R, Container>& B,
                   OutputIterator list_of_objects_it);
 
template < class R, class OutputIterator >
OutputIterator
CGAL_difference(   const CGAL_Triangle_2<R>& A,
                   const CGAL_Triangle_2<R>& B,
                   OutputIterator list_of_objects_it);
 
 
template < class R, class OutputIterator >
OutputIterator
CGAL_difference(   const CGAL_Iso_rectangle_2<R>& A,
                   const CGAL_Iso_rectangle_2<R>& B,
                   OutputIterator object_it);
 
 
template < class R, class Container, class OutputIterator >
OutputIterator
CGAL_difference(   const CGAL_Polygon_2<R, Container>& A,
                   const CGAL_Polygon_2<R, Container>& B,
                   OutputIterator list_of_objects_it);
 
#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/boolean_operations_2.C>
#endif

#endif // CGAL_BOOLEAN_OPERATIONS_2_H
