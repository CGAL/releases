#include "tutorial.h"
#include <assert.h>
#include <list>
#include <iterator>
#include <fstream>
#include <iostream>
#include <CGAL/boolean_operations_2.h>

using std::back_inserter;
using std::cout;
using std::endl;

typedef Polygon::Edge_const_circulator Polygon_edge_circulator;
typedef Polygon::Vertex_circulator Polygon_vertex_circulator;
typedef Polygon::Vertex_iterator Polygon_vertex_iterator;

Point centroid (Polygon &polyg)
{
  Polygon_vertex_circulator start = polyg.vertices_circulator();

  // check if the polygon is empty
  assert (start != 0);

  Polygon_vertex_circulator cur = start;
  Polygon_vertex_circulator next = cur;
  ++next;

  // check if the polygon has only one point
  if (next == cur) {
   cout << "next == cur" << endl;
   return *cur;
  }

  // check if polygon has only two points
  if (polyg.size()==2)
    return CGAL::ORIGIN + ((*cur-CGAL::ORIGIN) + (*next-CGAL::ORIGIN))/2;

  Vector cent(0,0);
  Vector aux(0,0);
  double a=0, atot=0;
  do {
    a = ((*cur).x()) * ((*next).y()) - ((*next).x()) * ((*cur).y());
    atot = atot + a;
    cent = cent + ((*cur - CGAL::ORIGIN) + (*next - CGAL::ORIGIN)) * a;
    cur = next;
    ++next;
  } while (cur != start);
  atot = 3*atot;
  cent = cent/atot;
  return CGAL::ORIGIN + cent;
}

template< class ForwardIterator >
double sum_area( ForwardIterator start, ForwardIterator beyond )
{
  Point point;
  Segment segment;
  Polygon polygon;
  double area=0;

  for( ForwardIterator it= start; it != beyond; it++) {
    if( CGAL::assign( polygon, *it) ) {
      area = area + polygon.area();
    }
  }
  return area;
}

double area_overlap(Polygon &polyg1, Polygon &polyg2)
{
  std::list<CGAL::Object> result;

  CGAL::intersection (polyg1, polyg2, back_inserter(result) );
  return sum_area( result.begin(), result.end() );
}

double area_difference (Polygon &polyg1, Polygon &polyg2)
{
  std::list<CGAL::Object> result;
  double area1, area2;

  CGAL::difference (polyg1, polyg2, back_inserter(result) );
  area1 = sum_area( result.begin(), result.end() );

  result.erase( result.begin(), result.end() );
  CGAL::difference (polyg2, polyg1, back_inserter(result) );
  area2 = sum_area( result.begin(), result.end() );

  return area1+area2;
}

//-----------------------------------------------------------------------//
//                          main
//-----------------------------------------------------------------------//

main(int argc, char *argv[])
{
  Polygon polygA;
  Polygon polygB;

  std::ifstream from("polygon_match.dat");
  CGAL::set_ascii_mode(from);
  from >> polygA >> polygB;

  if (polygA.is_empty() || polygB.is_empty()) {
    cout << "Polygons must be non-empty, exiting program." << endl;
    exit (1);
  }

  // check simplicity
  if ( !polygA.is_simple() || !polygB.is_simple()) {
    cout << "Polygons must be simple, exiting program." << endl;
    exit (1);
  }

  // check counterclockwise orientation
  if (polygA.orientation() == CGAL::CLOCKWISE) {
    cout << "Polygon A is entered clockwise.";
    polygA.reverse_orientation();
    cout << " Its orientation has been reversed." << endl;
  }
  else
    cout << "Polygon A is entered counterclockwise." << endl;

  // check counterclockwise orientation
  if (polygB.orientation() == CGAL::CLOCKWISE) {
    cout << "Polygon B is entered clockwise.";
    polygB.reverse_orientation();
    cout << " Its orientation has been reversed." << endl;
  }
  else
    cout << "Polygon B is entered counterclockwise." << endl;

  cout << "Area of intersection: " << area_overlap(polygA, polygB) << endl;
  cout << "Area of symmetric difference: "
       << area_difference(polygA, polygB) << endl;

  // transform B to put centroid B over centroid A
  Point centA = centroid(polygA);
  Point centB = centroid(polygB);
  Vector vec = centA - centB;
  Transformation transl(CGAL::TRANSLATION, vec);

  polygB = CGAL::transform (transl, polygB);
  cout << "Polygon B translated over " << vec << endl;

  cout << "New area of intersection: "
       << area_overlap(polygA, polygB) << endl;
  cout << "New area of symmetric difference: "
       << area_difference(polygA, polygB) << endl;

  // check convexity
  if ( polygA.is_convex() && polygB.is_convex() )
    cout << "Polygons A and B are both convex." << endl;
  else
    cout << "Polygons A and B are not both convex." << endl;
}
