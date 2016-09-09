
#include<CGAL/Cartesian.h>
#include<iostream>
#include<cstdlib>
#include<CGAL/Random.h>
#include<CGAL/Min_sphere_d.h>

using namespace CGAL;
using namespace std;

typedef Cartesian<double>                R;
typedef Min_sphere_d_traits_d<R>         Traits;
typedef Min_sphere_d<Traits>             Min_sphere;
typedef Point_d<R>                       Point;

const int n = 10;                        // number of points
const int d = 5;                         // dimension of points

int main ()
{
    Point         P[n];                  // n points
    double        coord[d];              // d coordinates
    Random        r;                     // random number generator

    for (int i=0; i<n; ++i) {
        for (int j=0; j<d; ++j)
            coord[j] = r.get_double();
        P[i] = Point(d, coord, coord+d); // random point
    }

    Min_sphere  ms (P, P+n);             // smallest enclosing sphere

    set_pretty_mode (cout);
    cout << ms;                          // output the sphere

    return 0;
}

