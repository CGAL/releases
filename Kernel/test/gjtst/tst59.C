/*
 * 2D Iso_rectangle Segment intersection.
 */

#include <iostream.h>
//#include <CGAL/Homogeneous.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Object.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Iso_rectangle_2_Iso_rectangle_2_intersection.h>
#include "tst.h"

typedef CGAL_TestfieldC testfield;
//typedef CGAL_Homogeneous<testfield> myR;
typedef CGAL_Cartesian<testfield> myR;
typedef CGAL_Point_2< myR > point_t;
typedef CGAL_Iso_rectangle_2< myR > rect_t;

template <class R>
void print(const CGAL_Point_2<R> &pt)
{
    cout << CGAL_to_double(pt.x()) <<' '<<CGAL_to_double(pt.y());
}



void one_pair(rect_t const & irect1, rect_t const & irect2)
{
    rect_t irect;
    CGAL_Object result = CGAL_intersection(irect1, irect2);
    if (CGAL_assign(irect, result)) {
	cout << "Intersection.\n";
	print(irect.min());
	cout << ' ';
	print(irect.max());
	cout << '\n';
    }
    if (!CGAL_assign(irect, result)) {
	cout << "No intersection.\n";
    }
}

main()
{
    double x1, x2, y1, y2;
    int i, n;
    cin >> n;
    if (!cin)
	return 1;
    for (i=0; i<n; i++) {
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	rect_t irect1(point_t(to_nt(x1), to_nt(y1)),
		       point_t(to_nt(x2), to_nt(y2)));
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	rect_t irect2(point_t(to_nt(x1), to_nt(y1)),
		       point_t(to_nt(x2), to_nt(y2)));
	one_pair(irect1, irect2);
    }
}
