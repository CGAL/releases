#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <iostream>

struct Point_mass {
    Point pos;
    double mass;
    Point_mass(const Point & p, double m): pos(p), mass(m) {}
};


Point centre_of_mass(Point_mass *cur, Point_mass *beyond)
{
    Vector sumv(0.0, 0.0);
    double sumw = 0.0;
    for ( ; cur != beyond; ++cur) {
        sumv = sumv + ((*cur).pos - CGAL::ORIGIN) * (*cur).mass;
        sumw += (*cur).mass;
    }
    return CGAL::ORIGIN + sumv/sumw;
}

int main()
{
    const int N = 4;
    Point_mass points[N] = {
            Point_mass(Point(3,4), 1),
            Point_mass(Point(-3,5), 1),
            Point_mass(Point(2.1,0), 10),
            Point_mass(Point(7,-12), 1)
            };
    Point centre = centre_of_mass(points, points+N);
    std::cout << "The centre of mass is: ("
         << centre.x() <<", "<< centre.y() <<")\n";
    return 0;
}
