// ---------------------------------------
// Example program from Getting Started with CGAL
// Chapter: Triangulations
// Author: Remco Veltkamp
// June 1997
// ---------------------------------------

#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Triangulation_2.h>
#include <vector.h>

void main ()
{
  const int numPoints1 = 4;

  static Point_2 points1[numPoints1] = {
    Point_2(0.4, 1), 
    Point_2(1, 0.3), 
    Point_2(0.0, -0.9), 
    Point_2(-1, 0)
    };

  Point_2 point2(0.0, 0.0);
  Point_2 point3(-1,1);

  vector<Point_2> points4(3);
  points4[0] = Point_2(1, 0.9);
  points4[1] = Point_2(1.4, -0.3);
  points4[2] = Point_2(0.6, 0);

  Triangulation_2 tr;                                   // create an empty triangulation

  tr.insert(points1, points1+numPoints1);        // insert array of Point-s
  tr.insert(point2);                                   // insert interior Point
  tr.insert(point3);                                   // insert exterior Point
  tr.insert(points4.begin(),points4.end());     // insert vector of Point-s

  typedef Triangulation_2::Vertex Vertex;
  typedef Triangulation_2::Vertex_iterator Vertex_iterator;

  Vertex *v;
  Vertex_iterator it = tr.vertices_begin(),
       	               beyond = tr.vertices_end();

  while(it != beyond) {
     v = *it;                                              // access vertex
     ++it;                                                 // forward the iterator
     cout << v->point() << endl;                     // print vertex point
  }


}
 
