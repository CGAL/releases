#include <CGAL/Cartesian.h>
#include <CGAL/utils.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/squared_distance_2.h>
#include "tst.h"
typedef CGAL_TestfieldC testfield;

typedef CGAL_Point_2< CGAL_Cartesian<testfield> > point_t;
typedef CGAL_Ray_2< CGAL_Cartesian<testfield> > ray_t;



int main()
{
    double x1, x2, y1, y2;
    int i, n;
    testfield d;
    cin >> n;
    if (!cin)
	return 1;
    for (i=0; i<n; i++) {
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	ray_t ray1(point_t(to_nt(x1), to_nt(y1)), point_t(to_nt(x2), to_nt(y2)));
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	ray_t ray2(point_t(to_nt(x1), to_nt(y1)), point_t(to_nt(x2), to_nt(y2)));
	d = CGAL_squared_distance(ray1, ray2);
	cout << CGAL_to_double(d) << '\n';
    }
    return 0;
}
