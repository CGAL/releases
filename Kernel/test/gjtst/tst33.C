#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/squared_distance_2_2.h>

#include "tst.h"
typedef CGAL_TestfieldC testfield;

typedef CGAL_Point_2< CGAL_Cartesian<testfield> > point_t;
typedef CGAL_Segment_2< CGAL_Cartesian<testfield> > segment_t;
typedef CGAL_Triangle_2< CGAL_Cartesian<testfield> > triangle_t;


int main()
{
    double x1, x2, x3, y1, y2, y3;
    int i, n;
    testfield d;
    cin >> n;
    if (!cin)
	return 1;
    for (i=0; i<n; i++) {
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	segment_t seg(point_t(to_nt(x1), to_nt(y1)),
		      point_t(to_nt(x2), to_nt(y2)));
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	if (!cin)
	    return 1;
	triangle_t tr(point_t(to_nt(x1), to_nt(y1)),
		      point_t(to_nt(x2), to_nt(y2)),
		      point_t(to_nt(x3), to_nt(y3)));
	d = CGAL_squared_distance(seg, tr);
	cout << CGAL_to_double(d) << '\n';
    }
    return 0;
}
