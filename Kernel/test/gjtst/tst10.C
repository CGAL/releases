/*
 * Line Ray intersection.
 */

#include <CGAL/Cartesian.h>
#include <CGAL/Object.h>
#include <CGAL/number_utils.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Line_2_Ray_2_intersection.h>
#include "tst.h"

typedef CGAL_TestfieldC testfield;
typedef CGAL_Cartesian<testfield> myR;
typedef CGAL_Point_2< myR > point_t;
typedef CGAL_Line_2< myR > line_t;
typedef CGAL_Ray_2< myR > ray_t;
typedef CGAL_Segment_2< myR > segment_t;

void print(const point_t &pt)
{
    cout << CGAL_to_double(pt.x()) <<' '<<CGAL_to_double(pt.y());
}


void treat_intersection(const line_t &line, const ray_t &ray)
{
    point_t ipt;
    ray_t iray;
    CGAL_Line_2_Ray_2_pair<myR> pair(&line, &ray);
    switch (pair.intersection_type()) {
    case CGAL_Line_2_Ray_2_pair<myR>::NO:
	cout << "No intersection.\n";
	break;
    case CGAL_Line_2_Ray_2_pair<myR>::RAY:
	cout << "Ray intersection.\n";
	pair.intersection(iray);
	print(iray.source());
	cout << ' ';
	print(CGAL_ORIGIN + iray.direction().vector());
	cout<<'\n';
	break;
    case CGAL_Line_2_Ray_2_pair<myR>::POINT:
	cout << "Point intersection.\n";
	pair.intersection(ipt);
	print(ipt);
	cout<<'\n';
	break;
    default:
	cout << "Unexpected result.\n";
    }

    CGAL_Object result = CGAL_intersection(line, ray);
    if (CGAL_assign(ipt, result)) {
	cout << "Point intersection.\n";
	print(ipt);
	cout<<'\n';
    }
    if (CGAL_assign(iray, result)) {
	cout << "Ray intersection.\n";
	print(iray.source());
	cout << ' ';
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
	line_t line(point_t(to_nt(x1), to_nt(y1)), point_t(to_nt(x2), to_nt(y2)));
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	ray_t ray(point_t(to_nt(x1), to_nt(y1)), point_t(to_nt(x2), to_nt(y2)));
	treat_intersection(line, ray);
    }
    return 0;
}
