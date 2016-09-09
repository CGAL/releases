/*
 * Squared distance between two segments.
 */
//#include <CGAL/Cartesian.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/utils.h>
#include <CGAL/Point_2.h>
#include <sqd.h>
#include <CGAL/squared_distance_2.h>
#include "tst.h"
typedef CGAL_TestrepH testring;
typedef CGAL_TestfieldH testfield;

typedef CGAL_Homogeneous<testfield, testring> R;

typedef CGAL_Point_2< R > point_t;
typedef CGAL_Segment_2< R > segment_t;


int main()
{
    const int C1 = 2;
    const int C2 = 25;
    const int C3 = 86;
    const int C4 = 7;
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
	segment_t seg1(point_t(to_rt(C1*x1), to_rt(C1*y1), to_rt(C1)),
		       point_t(to_rt(C2*x2), to_rt(C2*y2), to_rt(C2)));
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	segment_t seg2(point_t(to_rt(C3*x1), to_rt(C3*y1), to_rt(C3)),
		       point_t(to_rt(C4*x2), to_rt(C4*y2), to_rt(C4)));
	d = GJG_squared_distance(seg1, seg2);
	cout << CGAL_to_double(d) << '\n';
    }
    return 0;
}
