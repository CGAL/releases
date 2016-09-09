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
// file          : demo/BooleanOperations/BooleanOperations_demo.C
// source        : demo/BooleanOperations/BooleanOperations_demo.C
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:28:58 MET 1998  $
// author(s)     :                        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

/*
  This is an example program for the usage of boolean opertations:
  

  The number type it uses is a non-exact one:    Quotient<int>
                               ---------
  The coordinates are usually cartesian and if one wants to use
  homogeneous coordinates the compiler option -DCGAL_BOPS_HOMOGENEOUS
  has to be added.




  

*/

#include <CGAL/Cartesian.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/basic.h>

#include <list>
#include <CGAL/boolean_operations_2.h>
#include <iostream>

using CGAL::Object;
using std::list;
using std::vector;
using std::cout;
using std::endl;

//#include <CGAL/Rational.h>
//typedef Rational TestNum;  // only with Leda usage
//typedef double TestNum;         // non exact
typedef CGAL::Quotient<long int>       TestNum;  // exact, but very finite

#ifdef BOPS_HOMOGENEOUS
  typedef CGAL::Homogeneous<TestNum>   R_type;
#else
  typedef CGAL::Cartesian<TestNum>     R_type;
#endif

typedef CGAL::Point_2<R_type>          Point_2;
typedef CGAL::Segment_2<R_type>        Segment_2;
                                    // Polygon_2
typedef list< Point_2 >               Container;
typedef CGAL::Polygon_traits_2<R_type> Polygon_traits_2;
typedef CGAL::Polygon_2< Polygon_traits_2, Container >  Polygon_2;

#include "CGAL/example_io.h"  /* I/O to cin/cout */



int test_intersection(void) {
  vector<Point_2> vA(6), vB(4);
  test_input( vA, vB);
  Polygon_2 A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  cout << "INTERSECTION" << endl;
  cout << "============" << endl;
  cout << "polygon A: " << A << endl;
  cout << "polygon B: " << B << endl;

  list<Object> result;
  CGAL::intersection(A,B, back_inserter(result));
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
  CGAL::difference(A,B, back_inserter(result) );
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
  CGAL::Union(A,B, back_inserter(result) );
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
