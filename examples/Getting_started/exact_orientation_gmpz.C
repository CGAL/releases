#include <CGAL/Homogeneous.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <iostream.h>

typedef CGAL_Homogeneous<CGAL_Gmpz> Rep_class;
typedef CGAL_Point_2<Rep_class> Point_2;

void main()
{
    Point_2 p1(0, 0), p2(3, 17, 10), p3(9, 51, 10);
    switch (CGAL_orientation(p1,p2,p3)) {
      case CGAL_LEFTTURN:
        cout << "Left turn.";
        break;
      case CGAL_RIGHTTURN:
        cout << "Right turn.";
        break;
      case CGAL_COLLINEAR:
        cout << "The three points lie on a line.";
        break;
    }
    cout << "\n";
}
