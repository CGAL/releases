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
// release_date  : $CGAL_Date: 1998/10/03 $
//
// file          : demo/BooleanOperations/BooleanOperations_demo.C
// source        : demo/BooleanOperations/BooleanOperations_demo.C
// revision      : $Revision: 0.9.30b $
// revision_date : $Date: Tue Mar 10 12:54:02 MET 1998  $
// author(s)     :            Wolfgang Freiseisen <Wolfgang.Freiseisen@risc.uni-linz.ac.at>
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

#include <list.h>
#include <CGAL/boolean_operations_2.h>
#include <iostream.h>

//#include <CGAL/Rational.h>
//typedef CGAL_Rational TestNum;  // only with Leda usage
//typedef double TestNum;         // non exact
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

#include "CGAL/example_io.h"  /* I/O to cin/cout */



int test_intersection(void) {
  vector<Point_2> vA(6), vB(4);
  test_input( vA, vB);
  Polygon_2 A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  cout << "INTERSECTION" << endl;
  cout << "============" << endl;
  cout << "polygon A: " << A << endl;
  cout << "polygon B: " << B << endl;

  list<CGAL_Object> result;
  CGAL_intersection(A,B, back_inserter(result));
  test_result_output(result);
  
  return 0;
}



int test_difference(void) {
  vector<Point_2> vA(6), vB(4);
  test_input( vA, vB);
  Polygon_2 A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  cout << "DIFFERENCE" << endl;
  cout << "==========" << endl;
  cout << "polygon A: " << A << endl;
  cout << "polygon B: " << B << endl;

  list<CGAL_Object> result;
  CGAL_difference(A,B, back_inserter(result) );
  test_result_output(result);

  return 0;
}



int test_union(void) {
  vector<Point_2> vA(6), vB(4);
  test_input( vA, vB);
  Polygon_2 A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  cout << "UNION" << endl;
  cout << "=====" << endl;
  cout << "polygon A: " << A << endl;
  cout << "polygon B: " << B << endl;

  list<CGAL_Object> result;
  CGAL_union(A,B, back_inserter(result) );
  test_result_output(result);

  return 0;
}


int main(int argc, char *argv[])
{
  int s= -1;
  if( argc>1 ) s= atoi(argv[1]);

  switch(s) {
    case 1: test_intersection(); break;
    case 2: test_difference(); break;
    case 3: test_union(); break;
    default:
      test_intersection();
      test_difference(); 
      test_union(); 
  }
 
  return 0;
}
