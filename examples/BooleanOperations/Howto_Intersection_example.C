//  -*- Mode: c++ -*-
// ============================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : examples/BooleanOperations/Howto_Intersection_example.C
// source        : examples/BooleanOperations/Howto_Intersection_example.C
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:29:08 MET 1998  $
// author(s)     :                  Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

/*
  This is an example program for the usage of the boolean operation
  Intersection with cartesian coordiantes.

  The number type it uses is a non-exact one:    CGAL_Quotient<int>
                               ---------
*/

#include <CGAL/Homogeneous.h>
#include <CGAL/Cartesian.h>
#include <CGAL/basic.h>

#include <list.h>
#include <CGAL/boolean_operations_2.h>


typedef CGAL_Quotient<long int>          TestNum;
typedef CGAL_Homogeneous<TestNum>        R_type;

typedef CGAL_Point_2<R_type>             Point_2;
typedef CGAL_Segment_2<R_type>           Segment_2;

typedef list< Point_2 >                  Container;
typedef CGAL_Polygon_traits_2<R_type>    Polygon_traits_2;
typedef CGAL_Polygon_2< Polygon_traits_2, Container >  Polygon_2;

typedef vector<Point_2>                  Input_container;


int example_intersection(
  const Input_container& container_A,
  const Input_container& container_B
) {
  /* possible results */
  Point_2   point;
  Segment_2 segment;
  Polygon_2 polygon;

  /* instantiate Polygon A and B with containers */
  Polygon_2 A(container_A.begin(), container_A.end());
  Polygon_2 B(container_B.begin(), container_B.end());

  /* declaration of the result container */
  list<CGAL_Object> result;

  /* performing intersection of A and B */
  CGAL_intersection(A, B, back_inserter(result));
  
  /* do something with the result */

  /* declaration of an iterator on the result container */
  list<CGAL_Object>::const_iterator it;
  for( it= result.begin(); it != result.end(); it++) {
    if( CGAL_assign( polygon, *it) ) {
        /* polygon detected */
    }
    else if( CGAL_assign( segment, *it) ) {
        /* segment detected */
    }
    else if( CGAL_assign( point, *it) )  {  
        /* point detected */
    }
    else {
        /* nothing detected */
    }
  }
  
  /* return size of result */
  return result.size();
}



int main(void)
{
  Input_container container_A(6), container_B(4);

  container_A[0]= Point_2(2,4);
  container_A[1]= Point_2(0,3);
  container_A[2]= Point_2(1,1);
  container_A[3]= Point_2(2,3);
  container_A[4]= Point_2(3,1);
  container_A[5]= Point_2(4,3);
  container_B[0]= Point_2(0,2);
  container_B[1]= Point_2(0,0);
  container_B[2]= Point_2(5,0);
  container_B[3]= Point_2(5,2);

  example_intersection( container_A, container_B);
  return 0;
}
