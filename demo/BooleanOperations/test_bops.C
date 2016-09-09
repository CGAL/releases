//  -*- Mode: c++ -*-
// ============================================================================
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
// file          : demo/BooleanOperations/test_bops.C
// source        : demo/BooleanOperations/test_bops.C
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:29:03 MET 1998  $
// author(s)     :                        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/test_bops.h>

using namespace CGAL;
using namespace std;

int test_iso_rectangles(void) {
  Iso_rectangle_2 A(Point_2(0,5), Point_2(6,2));
  Iso_rectangle_2 B(Point_2(4,3), Point_2(7,0));
  list<Object> result;
  cout << "iso_rectangle A: " << A << endl;
  cout << "iso_rectangle B: " << B << endl;
  cout << "INTERSECTION(A,B)" << " - ";
  intersection(A, B, back_inserter(result));
  test_result_output(result);
  result= list<Object>();
  cout << "UNION(A,B)" << " - ";
  Union(A, B, back_inserter(result));
  test_result_output(result);
  result= list<Object>();
  cout << "DIFFERENCE(A,B)" << " - ";
  difference(A, B, back_inserter(result));
  test_result_output(result);
  result= list<Object>();
  cout << "DIFFERENCE(B,A)" << " - ";
  difference(B, A, back_inserter(result));
  test_result_output(result);
  return 0;
}

int test_triangles(void) {
  Triangle_2 A(Point_2(0,3), Point_2(2,0), Point_2(4,1));
  Triangle_2 B(Point_2(-1,1), Point_2(1,0), Point_2(3,3));
  list<Object> result;
  cout << "triangle A: " << A << endl;
  cout << "triangle B: " << B << endl;
  cout << "INTERSECTION" << endl;
  //intersection(A, B, back_inserter(result));
  //test_result_output(result);
  cout << "UNION" << endl;
  union(A, B, back_inserter(result));
  test_result_output(result);
  result= list<Object>();
  cout << "DIFFERENCE" << endl;
  difference(A, B, back_inserter(result));
  test_result_output(result);
  return 0;
}

int test_intersection(void) {
  vector<Point_2> vA(6), vB(4);
  test_input( vA, vB);
  Polygon_2 A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  cout << "INTERSECTION" << endl;
  cout << "============" << endl;
  cout << "polygon A: " << A << endl;
  cout << "polygon B: " << B << endl;

  list<Object> result;
  /*
  insert_iterator< list<Object> > result_iterator(result, result.begin());
  intersection(A,B, result_iterator);
  */
  intersection(A,B, back_inserter(result));
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

  list<Object> result;
  difference(A,B, back_inserter(result) );
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

  list<Object> result;
  union(A,B, back_inserter(result) );
  test_result_output(result);

  return 0;
}


int main(int argc, char *argv[])
{
  int s= -1;
  if( argc>1 ) s= atoi(argv[1]);

  switch(s) {
    case 0: 
      cout << "usage: test_bops [number]" << endl;
      cout << "   - tests boolean operations on two simple polygons," << endl;
      cout << "   - where 'number' can be one of the following:" << endl;
      cout << "                  1 ... intersection" << endl;
      cout << "                  2 ... difference" << endl;
      cout << "                  3 ... union " << endl;
      cout << "                  4 ... iso_rectangles" << endl;
      cout << "                  5 ... triangles" << endl;
      cout << "            default ... all tests" << endl;
      break;
    case 1: test_intersection(); break;
    case 2: test_difference(); break;
    case 3: test_union(); break;
    case 4: test_iso_rectangles(); break;
    case 5: test_triangles(); break;
    default:
      test_iso_rectangles();
      test_triangles();
      test_intersection();
      test_difference(); 
      test_union(); 
  }
 
  return 0;
}
