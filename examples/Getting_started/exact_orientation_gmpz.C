#include <CGAL/Homogeneous.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <iostream>

using std::cout;

typedef CGAL::Homogeneous<CGAL::Gmpz> Rep_class;
typedef CGAL::Point_2<Rep_class> Point;

main()
{
    Point p1(0, 0), p2(3, 17, 10), p3(9, 51, 10);
    switch (CGAL::orientation(p1,p2,p3)) {
      case CGAL::LEFTTURN:
        cout << "Left turn.";
        break;
      case CGAL::RIGHTTURN:
        cout << "Right turn.";
        break;
      case CGAL::COLLINEAR:
        cout << "The three points lie on a line.";
        break;
    }
    cout << "\n";
}
