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
// file          : demo/BooleanOperations/include/CGAL/test_bops_cin.C
// source        : demo/BooleanOperations/include/CGAL/test_bops_cin.C
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:29:02 MET 1998  $
// author(s)     :                        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

int test_intersection(const Polygon_2& A, const Polygon_2& B) {
  list<CGAL_Object> result;
  CGAL_intersection(A,B, back_inserter(result));
  test_result_output(result);
  return 0;
}


int test_difference(const Polygon_2& A, const Polygon_2& B) {
  list<CGAL_Object> result;
  CGAL_difference(A,B, back_inserter(result));
  test_result_output(result);
  return 0;
}


int test_union(const Polygon_2& A, const Polygon_2& B) {
  list<CGAL_Object> result;
  CGAL_union(A,B, back_inserter(result));
  test_result_output(result);
  return 0;
}


int main( int argc, char *argv[] )
{
  int arg= 0;
  if( argc > 1 ) {
    arg= atoi(argv[1]);
  }

  Polygon_2 A,B;

  if (!read_pgn(A)) {
	cerr << "Polygon A is wrong!" << endl;
	return 1;
  }
  // check counterclockwise orientation
  if ( A.orientation() == CGAL_CLOCKWISE) {
    A.reverse_orientation();
    cout << "orientation reversed" << endl;
  }
  cout << "polygon A: " << A << endl;

  if (!read_pgn(B)) {
	cerr << "Polygon B is wrong!" << endl;
	return 1;
  }
  // check counterclockwise orientation
  if ( B.orientation() == CGAL_CLOCKWISE) {
    B.reverse_orientation();
    cout << "orientation reversed" << endl;
  }
  cout << "polygon B: " << B << endl;

  switch( arg ) {
  case 1:
    cout << "INTERSECTION: " << endl;
    test_intersection(A,B);
    break;
  case 2:
    cout << "UNION: A + B " << endl;
    test_union(A, B);
    break;
  case 3:
    cout << "DIFFERENCE:  A - B" << endl;
    test_difference(A, B);
    break;
  case 4:
    cout << "DIFFERENCE:  B - A" << endl;
    test_difference(B, A);
    break;
  default:

    cout << "INTERSECTION: " << endl;
    test_intersection(A,B);

    cout << "UNION: A + B " << endl;
    test_union(A, B);

    cout << "DIFFERENCE:  A - B" << endl;
    test_difference(A, B);

    cout << "DIFFERENCE:  B - A" << endl;
    test_difference(B, A);
  }
  return 0;
}

