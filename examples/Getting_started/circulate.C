#include "tutorial.h"
#include <CGAL/Polygon_2.h>
#include <fstream.h>

typedef Polygon_2::Edge_const_circulator Edge_circulator;

void main()
{
  Polygon_2 polyg;

  ifstream from("polygon.dat");              // input file stream
  CGAL_set_ascii_mode(from);                 // file contains ascii
  from >> polyg;                            // read polygon

  Edge_circulator start = polyg.edges_circulator();
  double perimeter=0;

  if (start != NULL) { // polygon not empty
    Edge_circulator cur = start;
    do {
      Segment_2 edge = *cur;
      double l2 = edge.squared_length();
      perimeter += sqrt(l2);
      ++cur;
    } while (cur != start);
  }

  cout << "Perimeter of the polygon is " << perimeter << endl;
}
