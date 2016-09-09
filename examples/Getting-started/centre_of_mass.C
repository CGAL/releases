#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <iostream.h>

struct Point_mass {
    Point_2 pos;
    double mass;
    Point_mass(const Point_2 & p, double m): pos(p), mass(m) {}
};


Point_2 centre_of_mass(Point_mass *cur, Point_mass *beyond)
{
    Vector_2 sumv(0.0, 0.0);
    double sumw = 0.0;
    for ( ; cur != beyond; ++cur) {
        sumv = sumv + ((*cur).pos - CGAL_ORIGIN) * (*cur).mass;
        sumw += (*cur).mass;
    }
    return CGAL_ORIGIN + sumv/sumw;
}

void main()
{
    const int N = 4;
    Point_mass points[N] = {
            Point_mass(Point_2(3,4), 1),
            Point_mass(Point_2(-3,5), 1),
            Point_mass(Point_2(2.1,0), 10),
            Point_mass(Point_2(7,-12), 1)
            };
    Point_2 centre = centre_of_mass(points, points+N);
    cout << "The centre of mass is: ("
         << centre.x() <<", "<< centre.y() <<")\n";
}
