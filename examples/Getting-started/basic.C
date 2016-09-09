// ---------------------------------------
// Example program from Getting Started with CGAL
// Chapter: Elementaries
// Author: Geert-Jan Giezeman
// June 1997
// ---------------------------------------

#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <iostream.h>

main()
{
    Point_2 p1(1.0, -1.0), p2(4.0, 3.0), p3;
    Vector_2 v1(-1, 10);
    Vector_2 v2(p2-p1);
    v1 = v1 + v2;
    p3 = p2 + v1*2;
    cout << "Vector v2 has coordinates: ("
         << v2.x() <<", "<<v2.y() <<")\n";
    cout << "Point p3 has coordinates: ("
         << p3.x() <<", "<<p3.y() <<")\n";
}
