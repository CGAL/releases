/*
 * Intersection of two rays.
 */

#include <CGAL/Cartesian.h>
#include <CGAL/Object.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Ray_2_Ray_2_intersection.h>
#include <CGAL/test_types.h>
#include "tst.h"

typedef CGAL_TestfieldC testfield;
typedef CGAL_Cartesian<testfield> myR;



typedef CGAL_Point_2< myR > point_t;
typedef CGAL_Ray_2< myR > ray_t;
typedef CGAL_Segment_2< myR > segment_t;

void print(const point_t &pt)
{
    cout << CGAL_to_double(pt.x()) <<' '<<CGAL_to_double(pt.y());
}


void treat_intersection(const ray_t &ray1, const ray_t &ray2)
{
    typedef CGAL_Ray_2_Ray_2_pair<myR> is_t;
    point_t ipt;
    ray_t iray;
    segment_t iseg;
    is_t pair(&ray1, &ray2);
    switch (pair.intersection_type()) {
    case is_t::NO:
	cout << "No intersection.\n";
	break;
    case is_t::RAY:
	cout << "Ray intersection.\nsource: ";
	pair.intersection(iray);
	print(iray.source());
	cout<<" direction: ";
	print(CGAL_ORIGIN + iray.direction().vector());
	cout<<'\n';
	break;
    case is_t::SEGMENT:
	cout << "Segment intersection.\n";
	pair.intersection(iseg);
	print(iseg.source());
	cout << ' ';
	print(iseg.target());
	cout<<'\n';
	break;
    case is_t::POINT:
	cout << "Point intersection.\n";
	pair.intersection(ipt);
	print(ipt);
	cout<<'\n';
	break;
    default:
	cout << "Unexpected result.\n";
    }

    CGAL_Object result = CGAL_intersection(ray1, ray2);
    if (CGAL_assign(ipt, result)) {
	cout << "Point intersection.\n";
	print(ipt);
	cout<<'\n';
    }
    if (CGAL_assign(iseg, result)) {
	cout << "Segment intersection.\n";
	print(iseg.source());
	cout << ' ';
	print(iseg.target());
	cout<<'\n';
    }
    if (CGAL_assign(iray, result)) {
	cout << "Ray intersection.\n";
	print(iray.source());
	cout<<" direction: ";
	print(CGAL_ORIGIN + iray.direction().vector());
	cout<<'\n';
    }
}

int main()
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
	ray_t ray1(point_t(to_nt(x1), to_nt(y1)), point_t(to_nt(x2), to_nt(y2)));
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	ray_t ray2(point_t(to_nt(x1), to_nt(y1)), point_t(to_nt(x2), to_nt(y2)));
	treat_intersection(ray1, ray2);
    }
    return 0;
}
