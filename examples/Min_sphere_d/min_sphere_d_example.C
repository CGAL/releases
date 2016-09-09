#include<iostream.h>
#include<stdlib.h>
#include<CGAL/Cartesian.h>
#include<CGAL/Min_sphere_d.h>

typedef CGAL_Cartesian<double> 		 R;
typedef CGAL_Min_sphere_d_traits_d<R> 	 Traits;              
typedef CGAL_Min_sphere_d<Traits>	 Min_sphere;
typedef CGAL_Point_d<R>			 Point;

const int n = 10;			 // number of points
const int d = 5;			 // dimension of points

int main ()
{
    Point         P[n];    		 // n points
    double	  coord[d];		 // d coordinates

    for (int i=0; i<n; ++i) {
        for (int j=0; j<d; ++j)
            coord[j] = drand48(); 	
        P[i] = Point(d, coord, coord+d); // random point
    } 

    Min_sphere  ms (P, P+n); 		 // smallest enclosing sphere

    CGAL_set_pretty_mode (cout);
    cout << ms;				 // output the sphere

    return 0;
}
