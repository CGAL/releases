#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/intersections.h>

main()
{
  Triangle t1(Point(-5.2,1.7), Point(-7.1,-6.3), Point(-0.9,-2.3));
  Triangle t2(Point(-4.8,-4.5), Point(4.5,-1.1), Point(2.4,-7.6));

  cout << "Triangle 1:\n" << t1 << "\nand triangle 2:\n" << t2 << endl;
  if ( ! CGAL::do_intersect(t1,t2))
    cout << "do not intersect" << endl;
  else
    cout << "do intersect" << endl;
}
