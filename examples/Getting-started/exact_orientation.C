// ---------------------------------------
// Example program from Getting Started with CGAL
// Chapter: Arithmetics
// Author: Geert-Jan Giezeman
// June 1997
// ---------------------------------------

#include <CGAL/Homogeneous.h>
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <iostream.h>

typedef CGAL_Homogeneous<long> RepType;
typedef CGAL_Point_2<RepType> Point_2;

main()
{
    Point_2 p1(0, 0), p2(3, 17, 10), p3(9, 51, 10);
    switch (CGAL_orientation(p1,p2,p3)) {
      case CGAL_LEFTTURN:
	cout << "left turn.";
	break;
      case CGAL_RIGHTTURN:
	cout << "right turn.";
	break;
      case CGAL_COLLINEAR:
	cout << "The three points lie on a line.";
	break;
    }
    cout << "\n";
}
