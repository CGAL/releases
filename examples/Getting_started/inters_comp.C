#include "tutorial.h"
#include <CGAL/intersections.h>

main()
{
  Triangle t1(Point(2,6), Point(-6,5), Point(-2,-7));
  Triangle t2(Point(6,0), Point(-3,0), Point(2,-5));

  cout << "The intersection of triangle 1:\n" << t1;
  cout << "\nand triangle 2:\n" << t2 << "\nis ";

  if ( ! CGAL::do_intersect(t1,t2) ) {
    cout << "empty" << endl;
  }
  else {
    CGAL::Object result = CGAL::intersection(t1,t2);
    Point point;
    Segment segment;
    Triangle triangle;
    std::vector<Point> polypoint;                   // not a Polygon !

    if (CGAL::assign(point, result)) {
      cout << "point." << endl;
    } else
    if (CGAL::assign(segment, result)) {
      cout << "segment." << endl;
    } else
    if (CGAL::assign(triangle, result)) {
      cout << "triangle." << endl;
    } else
    if (CGAL::assign(polypoint, result)) {
      cout << "a polygon." << endl;
    } else
    cout << "unknown!" << endl;
  }
}
