#include "tutorial.h"
#include <assert.h>
#include <fstream.h>
#include <iostream.h>
#include <CGAL/boolean_operations_2.h>

typedef Polygon_2::Edge_const_circulator Polygon_edge_circulator;
typedef Polygon_2::Vertex_circulator Polygon_vertex_circulator;
typedef Polygon_2::Vertex_iterator Polygon_vertex_iterator;

Point_2 centroid (Polygon_2 &polyg)
{
  Polygon_vertex_circulator start = polyg.vertices_circulator();

  // check if the polygon is empty
  assert (start != NULL);

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
    return CGAL_ORIGIN + ((*cur-CGAL_ORIGIN) + (*next-CGAL_ORIGIN))/2;

  Vector_2 cent(0,0);
  Vector_2 aux(0,0);
  double a=0, atot=0;
  do {
    a = ((*cur).x()) * ((*next).y()) - ((*next).x()) * ((*cur).y());
    atot = atot + a;
    cent = cent + ((*cur - CGAL_ORIGIN) + (*next - CGAL_ORIGIN)) * a;
    cur = next;
    ++next;
  } while (cur != start);
  atot = 3*atot;
  cent = cent/atot;
  return CGAL_ORIGIN + cent;
}

template< class ForwardIterator >
double sum_area( ForwardIterator start, ForwardIterator beyond )
{
  Point_2 point;
  Segment_2 segment;
  Polygon_2 polygon;
  double area=0;

  for( ForwardIterator it= start; it != beyond; it++) {
    if( CGAL_assign( polygon, *it) ) {
      area = area + polygon.area();
    }
  }
  return area;
}

double area_overlap(Polygon_2 &polyg1, Polygon_2 &polyg2)
{
  list<CGAL_Object> result;

  CGAL_intersection (polyg1, polyg2, back_inserter(result) );
  return sum_area( result.begin(), result.end() );
}

double area_difference (Polygon_2 &polyg1, Polygon_2 &polyg2)
{
  list<CGAL_Object> result;
  double area1, area2;

  CGAL_difference (polyg1, polyg2, back_inserter(result) );
  area1 = sum_area( result.begin(), result.end() );

  result.erase( result.begin(), result.end() );
  CGAL_difference (polyg2, polyg1, back_inserter(result) );
  area2 = sum_area( result.begin(), result.end() );

  return area1+area2;
}

//-----------------------------------------------------------------------//
//                          main
//-----------------------------------------------------------------------//

void main(int argc, char *argv[])
{
  Polygon_2 polygA;
  Polygon_2 polygB;

  ifstream from("polygon_match.dat");
  CGAL_set_ascii_mode(from);
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
  if (polygA.orientation() == CGAL_CLOCKWISE) {
    cout << "Polygon A is entered clockwise.";
    polygA.reverse_orientation();
    cout << " Its orientation has been reversed." << endl;
  }
  else
    cout << "Polygon A is entered counterclockwise." << endl;

  // check counterclockwise orientation
  if (polygB.orientation() == CGAL_CLOCKWISE) {
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
  Point_2 centA = centroid(polygA);
  Point_2 centB = centroid(polygB);
  Vector_2 vec = centA - centB;
  Transformation_2 transl(CGAL_TRANSLATION, vec);

  polygB = transform (transl, polygB);
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
