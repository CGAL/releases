#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <iostream>
#include <vector>
#include <list>

typedef CGAL::Cartesian<double> Rep_class;
typedef CGAL::Point_2<Rep_class> Point;
typedef CGAL::Vector_2<Rep_class> Vector;

struct Point_mass {
    Point pos;
    double mass;
    Point_mass(const Point & p, double m): pos(p), mass(m) {}
    Point_mass() {}
};

template <class Iterator>
Point centre_of_mass(Iterator cur, Iterator beyond)
{
    Vector sumv(0.0, 0.0);
    double sumw = 0.0;
    for ( ; cur != beyond; ++cur) {
       // sumv = sumv + (cur->pos - CGAL::ORIGIN) * cur->mass;
       // sumw += cur->mass;
        sumv = sumv + ((*cur).pos - CGAL::ORIGIN) * (*cur).mass;
        sumw += (*cur).mass;
    }
    return CGAL::ORIGIN + sumv/sumw;
}

void write(const Point &centre)
{
    std::cout << "The centre of mass is: ("
         << centre.x() <<", "<< centre.y() <<")\n";
}

main()
{
    const int N = 4;
    Point_mass points1[N] = {
            Point_mass(Point(3,4), 1),
            Point_mass(Point(-3,5), 1),
            Point_mass(Point(2.1,0), 10),
            Point_mass(Point(7,-12), 1)
            };
    write(centre_of_mass(points1, points1+N));

    std::vector<Point_mass> points2(points1, points1+N);
    write(centre_of_mass(points2.begin(), points2.end()));

    std::list<Point_mass> points3(points1, points1+N);
    write(centre_of_mass(points3.begin(), points3.end()));
}
