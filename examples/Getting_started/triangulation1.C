#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Triangulation_2.h>
#include <vector>


int main()
{
  const int numPoints1 = 4;

  static Point points1[numPoints1] = {
    Point(0.4, 1),
    Point(1, 0.3),
    Point(0.0, -0.9),
    Point(-1, 0)
    };

  Point point2(0.0, 0.0);
  Point point3(-1,1);

  std::vector<Point> points4(3);
  points4[0] = Point(1, 0.9);
  points4[1] = Point(1.4, -0.3);
  points4[2] = Point(0.6, 0);

  Triangulation tr;                           // create an empty triangulation

  tr.insert(points1, points1+numPoints1);       // insert array of Point-s
  tr.insert(point2);                            // insert interior Point
  tr.insert(point3);                            // insert exterior Point
  tr.insert(points4.begin(),points4.end());     // insert vector of Point-s

  std::cout << tr;
  return 0;
}
