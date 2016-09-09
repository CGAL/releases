#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <iostream>

int main()
{
    Point p1(1.0, -1.0), p2(4.0, 3.0), p3;
    Vector v1(-1, 10);
    Vector v2(p2-p1);
    v1 = v1 + v2;
    p3 = p2 + v1*2;
    std::cout << "Vector v2 has coordinates: ("
         << v2.x() <<", "<<v2.y() <<")\n";
    std::cout << "Point p3 has coordinates: ("
         << p3.x() <<", "<<p3.y() <<")\n";
    return 0;
}
