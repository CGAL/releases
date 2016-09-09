//  -*- Mode: c++ -*-
// ============================================================================
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
// file          : examples/BooleanOperations/BooleanOperations_example.C
// source        : examples/BooleanOperations/BooleanOperations_example.C
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1999/10/11 13:50:31 $
// author(s)     :                  Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

/*
  This is an example program for the usage of boolean operations:
  

  The number type it uses is a unsafe one:    Quotient<int>
                               ----------
  The coordinates are usually cartesian and if one wants to use
  homogeneous coordinates the compiler option -DCGAL_BOPS_HOMOGENEOUS
  has to be added.

*/

#include <CGAL/Cartesian.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/basic.h>
#include <CGAL/boolean_operations_2.h>
#include <vector>
#include <list>
#include <iterator>

using CGAL::Object;
using CGAL::assign;
using std::vector;
using std::list;
using std::back_inserter;

typedef CGAL::Quotient<long int>       TestNum;  // exact, but very finite

#ifdef BOPS_HOMOGENEOUS
  typedef CGAL::Homogeneous<TestNum>   R_type;
#else
  typedef CGAL::Cartesian<TestNum>     R_type;
#endif

typedef CGAL::Point_2<R_type>          Point;
typedef CGAL::Segment_2<R_type>        Segment;
typedef list< Point >                Container;
typedef CGAL::Polygon_traits_2<R_type> Polygon_traits;
typedef CGAL::Polygon_2< Polygon_traits, Container >  Polygon;


/*--------------------------------------------------------------*/
/* test data are inserted:                                      */
/* Polygon 1: (2,4) (0,3) (1,1) (2,3) (3,1) (4,3)               */
/* Polygon 2: (0,2) (0,0) (5,0) (5,2)                           */
void test_input(vector<Point>& vA, vector<Point>& vB) {
  vA[0]= Point(2,4);
  vA[1]= Point(0,3);
  vA[2]= Point(1,1);
  vA[3]= Point(2,3);
  vA[4]= Point(3,1);
  vA[5]= Point(4,3);
  vB[0]= Point(0,2);
  vB[1]= Point(0,0);
  vB[2]= Point(5,0);
  vB[3]= Point(5,2);
}
/*--------------------------------------------------------------*/


/*--------------------------------------------------------------*/
/* do something with the test result                            */
template< class ForwardIterator >
int test_result_output( ForwardIterator first, ForwardIterator last ) {
  Point point;
  Segment segment;
  Polygon polygon;

  for( ForwardIterator it= first; it != last; it++) {
    if( assign( polygon, *it) ) {
       /* do something with the polygon */
    }
    else if( assign( segment, *it) ) {
       /* do something with the segment */
    }
    else if( assign( point, *it) )  {
       /* do something with the point */
    }
    else {
       /* unknown type, nothing to do */
    }
  }
  return 0;
}
/*--------------------------------------------------------------*/


/*--------------------------------------------------------------*/
/* Intersection test of two simple polygons                     */
/* ----------------------------------------                     */
/* result:                                                      */
int test_intersection(void) {
  vector<Point> vA(6), vB(4);
  test_input( vA, vB);
  Polygon A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  list<Object> result;
  CGAL::intersection(A,B, back_inserter(result));
  test_result_output( result.begin(), result.end() );
  
  return 0;
}
/*--------------------------------------------------------------*/



/*--------------------------------------------------------------*/
/* Difference test of two simple polygons                       */
/* --------------------------------------                       */
/* result:                                                      */
int test_difference(void) {
  vector<Point> vA(6), vB(4);
  test_input( vA, vB);
  Polygon A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  list<Object> result;
  CGAL::difference(A,B, back_inserter(result) );

  return 0;
}
/*--------------------------------------------------------------*/



/*--------------------------------------------------------------*/
/* Union test of two simple polygons                            */
/* ---------------------------------                            */
/* result:                                                      */
int test_union(void) {
  vector<Point> vA(6), vB(4);
  test_input( vA, vB);
  Polygon A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  list<Object> result;
  CGAL::Union(A,B, back_inserter(result) );

  return 0;
}
/*--------------------------------------------------------------*/


/*--------------------------------------------------------------*/
/* main program                                                 */
int main(int argc, char *argv[])
{
  return 
      test_intersection() && test_difference() && test_union(); 
}
/*--------------------------------------------------------------*/
