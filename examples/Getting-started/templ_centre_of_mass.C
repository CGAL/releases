#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <iostream.h>
#include <vector.h>
#include <list.h>

typedef CGAL_Cartesian<double> Rep_class;
typedef CGAL_Point_2<Rep_class> Point_2;
typedef CGAL_Vector_2<Rep_class> Vector_2;

struct Point_mass {
    Point_2 pos;
    double mass;
    Point_mass(const Point_2 & p, double m): pos(p), mass(m) {}
    Point_mass() {}
};

template <class Iterator>
Point_2 centre_of_mass(Iterator cur, Iterator beyond)
{
    Vector_2 sumv(0.0, 0.0);
    double sumw = 0.0;
    for ( ; cur != beyond; ++cur) {
       // sumv = sumv + (cur->pos - CGAL_ORIGIN) * cur->mass;
       // sumw += cur->mass;
        sumv = sumv + ((*cur).pos - CGAL_ORIGIN) * (*cur).mass;
        sumw += (*cur).mass;
    }
    return CGAL_ORIGIN + sumv/sumw;
}

void write(const Point_2 &centre)
{
    cout << "The centre of mass is: ("
         << centre.x() <<", "<< centre.y() <<")\n";
}

void main()
{
    const int N = 4;
    Point_mass points1[N] = {
            Point_mass(Point_2(3,4), 1),
            Point_mass(Point_2(-3,5), 1),
            Point_mass(Point_2(2.1,0), 10),
            Point_mass(Point_2(7,-12), 1)
            };
    write(centre_of_mass(points1, points1+N));

    vector<Point_mass> points2(points1, points1+N);
    write(centre_of_mass(points2.begin(), points2.end()));

    list<Point_mass> points3(points1, points1+N);
    write(centre_of_mass(points3.begin(), points3.end()));
}
