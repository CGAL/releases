//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL basic library.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//
 
// Source: BooleanOperations_example.C
// Author: Wolfgang Freiseisen
 

/*
  This is an example program for the usage of boolean opertations:
  

  The number type it uses is a non-exact one:    CGAL_Quotient<int>
                               ---------
  The coordinates are usually cartesian and if one wants to use
  homogeneous coordinates the compiler option -DCGAL_BOPS_HOMOGENEOUS
  has to be added.




  

*/

#ifdef __GNUC__
#include <typeinfo>
#endif

//#define __BUILTIN_BOOL__
#include <CGAL/Cartesian.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/basic.h>
#include <CGAL/Rational.h>

#include <list.h>
#include <CGAL/boolean_operations_2.h>
#include <iostream.h>

//typedef CGAL_Rational TestNum;  // only with Leda usage
typedef CGAL_Quotient<int> TestNum;

#ifdef CGAL_BOPS_HOMOGENEOUS
  typedef CGAL_Homogeneous<TestNum>  R_type;
#else
  typedef CGAL_Cartesian<TestNum>    R_type;
#endif

typedef CGAL_Point_2<R_type>           Point_2;
typedef CGAL_Segment_2<R_type>         Segment_2;
typedef list< Point_2 >              Container;
typedef CGAL_Polygon_2< R_type, Container >  Polygon_2;

#include "example_io.h"  /* I/O to cin/cout */



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
