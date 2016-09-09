#include "tutorial.h"
#include <CGAL/intersections.h>

void main()
{
  Triangle_2 t1(Point_2(2,6), Point_2(-6,5), Point_2(-2,-7));
  Triangle_2 t2(Point_2(6,0), Point_2(-3,0), Point_2(2,-5));

  cout << "The intersection of triangle 1:\n" << t1;
  cout << "\nand triangle 2:\n" << t2 << "\nis ";

  if ( ! CGAL_do_intersect(t1,t2) ) {
    cout << "empty" << endl;
  }
  else {
    CGAL_Object result = CGAL_intersection(t1,t2);
    Point_2 point;
    Segment_2 segment;
    Triangle_2 triangle;
    vector<Point_2> polygon;

    if (CGAL_assign(point, result)) {
      cout << "point " << point << endl;
    } else
    if (CGAL_assign(segment, result)) {
      cout << "segment " << segment << endl;
    } else
    if (CGAL_assign(triangle, result)) {
      cout << "triangle " << triangle << endl;
    } else
    if (CGAL_assign(polygon, result)) {
      cout << "a polygon. " << endl;
    } else
    cout << "unknown!" << endl;
  }
}
