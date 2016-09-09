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
// file          : demo/BooleanOperations/tutorial_example.C
// source        : demo/BooleanOperations/tutorial_example.C
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:29:06 MET 1998  $
// author(s)     :                   Remco Veltkamp
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Polygon_2.h>

#include <list>
#include <iostream>
#include <fstream>
//#include <CGAL/IO/Window_stream.h>
#include <CGAL/basic.h>

//#define CGAL__BOPS_DEBUG_ON
//#define  CGAL__DCEL_DEBUG_ON
//#define _DCEL__V2E_DEBUG_ON
#include <CGAL/boolean_operations_2.h>

typedef Cartesian<double> TutorialR;
typedef Point_2<TutorialR> Point_2;
typedef Segment_2<TutorialR> Segment_2;
typedef Polygon_traits_2<TutorialR> Polygon_traits_2;
typedef list< Point_2 > Polygon_Container_2;
typedef Polygon_2< Polygon_traits_2, Polygon_Container_2 >  Polygon_2;
typedef Polygon_2::Vertex_iterator Vertex_iterator;
typedef Polygon_2::Vertex_circulator Vertex_circulator;
typedef Polygon_2::Edge_const_iterator Edge_iterator;

template< class ForwardIterator >
double area_result( ForwardIterator first, ForwardIterator last )
{
  Point_2 point;
  Segment_2 segment;
  Polygon_2 polygon;
  double area=0;

  for( ForwardIterator it= first; it != last; it++) {
    if( assign( polygon, *it) ) {
      cout << "Intersection polygon: " << polygon << endl;
      area = area + polygon.area();
    }
    else if( assign( segment, *it) ) {
      cout << "Intersection segment: " << segment << endl;
    }
    else if( assign( point, *it) )  {
      cout << "Intersection point: " << point << endl;
    }
    else {
      /* unknown intersection type */
      cout << "Unknown intersection result type." << endl;
    }
  }
  return area;
}

//-----------------------------------------------------------------------//
//                          main
//-----------------------------------------------------------------------//

#define WORLD_MIN_X -10
#define WORLD_MAX_X 10
#define WORLD_MIN_Y -10

int main(int argc, char *argv[])
{ bool fromFile = (argc>1);

  Polygon_2 polygA;
  Polygon_2 polygB;

  if (fromFile) {
    ifstream from(argv[1]);

    set_ascii_mode(from);
    from >> polygA >> polygB;
  }
  else {
    cout << "Give filename as argument."<< endl;
    exit (0);
  }

  // check simplicity
  if ( !polygA.is_simple() ) {
    cout << "Polygon A is not simple, exiting program." << endl;
    exit (0);
  }

  // check counterclockwise orientation
  if (polygA.orientation() == CLOCKWISE) {
    cout << "Polygon A is entered clockwise.";
    polygA.reverse_orientation();
    cout << "Its orientation has been reversed." << endl;
  }
  else {
    cout << "Polygon A is entered counterclockwise." << endl;
  }

  // compute area of polygon A
  cout << "Area of polygon A is " << polygA.area() << "." << endl;

  if (polygB.is_empty()) {
    cout << "Polygon B is empty, exiting program." << endl;
    exit (0);
  }

  // check simplicity
  if ( !polygB.is_simple() ) {
    cout << "Polygon B is not simple, exiting program." << endl;
    exit (0);
  }

  // check counterclockwise orientation
  if (polygB.orientation() == CLOCKWISE) {
    cout << "Polygon B is entered clockwise.";
    polygB.reverse_orientation();
    cout << "Its orientation has been reversed." << endl;
  }
  else {
    cout << "Polygon B is entered counterclockwise." << endl;
  }

  // compute area of polygon B
  cout << "Area of polygon B is " << polygB.area() << "." << endl;

  // compute the intersection of A and B
  { list<Object> result;
    double area;
    cout << "Computing intersection of A and B ..." << endl;
    intersection (polygA, polygB, back_inserter(result) );
    cout << "Done." << endl;
    area = area_result( result.begin(), result.end() );
    cout << "Area of intersection of A and B is " << area << endl;
  }

  // compute the differences A - B and B - A
  { list<Object> result;
    double area1, area2;
    cout << "Computing difference A-B ..." << endl;
    difference (polygA, polygB, back_inserter(result) );
    cout << "Done." << endl;
    area1 = area_result( result.begin(), result.end() );
    cout << "Area of A-B is " << area1 << endl;
    cout << "Computing difference B-A ..." << endl;
    difference (polygA, polygB, back_inserter(result) );
    cout << "Done." << endl;
    area2 = area_result( result.begin(), result.end() );
    cout << "Area of B-A is " << area2 << endl;
    cout << "Area of symmetric difference is " << area1+area2 << endl;
  }

  return 0;
}
