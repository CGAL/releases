#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <iostream>

using std::cout;
using std::cin;

int main()
{
    double x1, x2, x3, y1, y2, y3;
    do {
        cout << "Give three points (6 coordinates, separated by spaces).\n";
        cout << ">> " << std::flush;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        if (!cin)
            break;
        Point p1(x1,y1), p2(x2,y2), p3(x3,y3);
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
        cout << "\n\n";
    } while (1);
    return 0;
}
