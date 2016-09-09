//  -*- Mode: c++ -*-
// ============================================================================
// 
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-0.9-I-06 $
// release_date  : $CGAL_Date: 1998/09/02 $
//
// file          : ./examples/BooleanOperations/BooleanOperations_example.C
// source        : ./examples/BooleanOperations/BooleanOperations_example.C
// revision      : $Revision: 0.9.29h $
// revision_date : $Date: Mon Feb  9 16:00:44 MET 1998  $
// author(s)     :         Wolfgang Freiseisen <Wolfgang.Freiseisen@risc.uni-linz.ac.at>
//
// coordinator   : RISC Linz
//           (Wolfgang Freiseisen <wfreisei@risc.uni-linz.ac.at>)
//
// 
// ============================================================================

/*
  This is an example program for the usage of boolean opertations:
  

  The number type it uses is a non-exact one:    CGAL_Quotient<int>
                               ---------
  The coordinates are usually cartesian and if one wants to use
  homogeneous coordinates the compiler option -DCGAL_BOPS_HOMOGENEOUS
  has to be added.




  

*/

#include <CGAL/Cartesian.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/basic.h>
#include <CGAL/boolean_operations_2.h>

typedef CGAL_Quotient<long int>       TestNum;  // exact, but very finite

#ifdef CGAL_BOPS_HOMOGENEOUS
  typedef CGAL_Homogeneous<TestNum>   R_type;
#else
  typedef CGAL_Cartesian<TestNum>     R_type;
#endif

typedef CGAL_Point_2<R_type>          Point_2;
typedef CGAL_Segment_2<R_type>        Segment_2;
                                    // Polygon_2
typedef list< Point_2 >               Container;
typedef CGAL_Polygon_traits_2<R_type> Polygon_traits_2;
typedef CGAL_Polygon_2< Polygon_traits_2, Container >  Polygon_2;


/*--------------------------------------------------------------*/
/* test data are inserted:                                      */
/* Polygon 1: (2,4) (0,3) (1,1) (2,3) (3,1) (4,3)               */
/* Polygon 2: (0,2) (0,0) (5,0) (5,2)                           */
void test_input(vector<Point_2>& vA, vector<Point_2>& vB) {
  vA[0]= Point_2(2,4);
  vA[1]= Point_2(0,3);
  vA[2]= Point_2(1,1);
  vA[3]= Point_2(2,3);
  vA[4]= Point_2(3,1);
  vA[5]= Point_2(4,3);
  vB[0]= Point_2(0,2);
  vB[1]= Point_2(0,0);
  vB[2]= Point_2(5,0);
  vB[3]= Point_2(5,2);
}
/*--------------------------------------------------------------*/


/*--------------------------------------------------------------*/
/* do something with the test result                            */
template< class ForwardIterator >
int test_result_output( ForwardIterator first, ForwardIterator last ) {
  Point_2 point;
  Segment_2 segment;
  Polygon_2 polygon;

  for( ForwardIterator it= first; it != last; it++) {
    if( CGAL_assign( polygon, *it) ) {
       /* do something with the polygon */
    }
    else if( CGAL_assign( segment, *it) ) {
       /* do something with the segment */
    }
    else if( CGAL_assign( point, *it) )  {
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
  vector<Point_2> vA(6), vB(4);
  test_input( vA, vB);
  Polygon_2 A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  list<CGAL_Object> result;
  CGAL_intersection(A,B, back_inserter(result));
  test_result_output( result.begin(), result.end() );
  
  return 0;
}
/*--------------------------------------------------------------*/



/*--------------------------------------------------------------*/
/* Difference test of two simple polygons                       */
/* --------------------------------------                       */
/* result:                                                      */
int test_difference(void) {
  vector<Point_2> vA(6), vB(4);
  test_input( vA, vB);
  Polygon_2 A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  list<CGAL_Object> result;
  CGAL_difference(A,B, back_inserter(result) );

  return 0;
}
/*--------------------------------------------------------------*/



/*--------------------------------------------------------------*/
/* Union test of two simple polygons                            */
/* ---------------------------------                            */
/* result:                                                      */
int test_union(void) {
  vector<Point_2> vA(6), vB(4);
  test_input( vA, vB);
  Polygon_2 A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  list<CGAL_Object> result;
  CGAL_union(A,B, back_inserter(result) );

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
