// ---------------------------------------
// Example program from Getting Started with CGAL
// Chapter: Elementaries
// Author: Geert-Jan Giezeman
// June 1997
// ---------------------------------------

#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <iostream.h>

main()
{
    double x1, x2, x3, y1, y2, y3;
    do {
	cout << "Give three points (6 coordinates, separated by spaces).\n";
	cout << ">> " << flush;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	if (!cin)
    	    break;
	Point_2 p1(x1,y1), p2(x2,y2), p3(x3,y3);
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
	cout << "\n\n";
    } while (1);
}
