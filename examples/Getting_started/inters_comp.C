#include "tutorial.h"
#include <CGAL/intersections.h>

int main()
{
  Triangle t1(Point(2,6), Point(-6,5), Point(-2,-7));
  Triangle t2(Point(6,0), Point(-3,0), Point(2,-5));

  std::cout << "The intersection of triangle 1:\n" << t1;
  std::cout << "\nand triangle 2:\n" << t2 << "\nis ";

  if ( ! CGAL::do_intersect(t1,t2) ) {
    std::cout << "empty" << std::endl;
  }
  else {
    CGAL::Object result = CGAL::intersection(t1,t2);
    Point point;
    Segment segment;
    Triangle triangle;
    std::vector<Point> polypoint;                   // not a Polygon !

    if (CGAL::assign(point, result)) {
      std::cout << "point." << std::endl;
    } else
    if (CGAL::assign(segment, result)) {
      std::cout << "segment." << std::endl;
    } else
    if (CGAL::assign(triangle, result)) {
      std::cout << "triangle." << std::endl;
    } else
    if (CGAL::assign(polypoint, result)) {
      std::cout << "a polygon." << std::endl;
    } else
    std::cout << "unknown!" << std::endl;
  }
  return 0;
}
