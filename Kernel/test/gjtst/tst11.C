/*
 * Segment Line intersection.
 */

#include <CGAL/Cartesian.h>
#include <CGAL/Object.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Segment_2_Line_2_intersection.h>
#include "tst.h"

typedef CGAL_TestfieldC testfield;
typedef CGAL_Cartesian<testfield> myR;
typedef CGAL_Point_2< myR > point_t;
typedef CGAL_Line_2< myR > line_t;
typedef CGAL_Segment_2< myR > segment_t;

void print(const point_t &pt)
{
    cout << CGAL_to_double(pt.x()) <<' '<<CGAL_to_double(pt.y());
}


void treat_intersection(const segment_t &seg, const line_t &line)
{
    point_t ipt;
    segment_t iseg;
    CGAL_Segment_2_Line_2_pair<myR> pair(&seg, &line);
    switch (pair.intersection_type()) {
    case CGAL_Segment_2_Line_2_pair<myR>::NO:
	cout << "No intersection.\n";
	break;
    case CGAL_Segment_2_Line_2_pair<myR>::SEGMENT:
	cout << "Segment intersection.\n";
	pair.intersection(iseg);
	print(iseg.source());
	cout << ' ';
	print(iseg.target());
	cout<<'\n';
	break;
    case CGAL_Segment_2_Line_2_pair<myR>::POINT:
	cout << "Point intersection.\n";
	pair.intersection(ipt);
	print(ipt);
	cout<<'\n';
	break;
    default:
	cout << "Unexpected result.\n";
    }

    CGAL_Object result = CGAL_intersection(seg, line);
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
	segment_t seg(point_t(to_nt(x1), to_nt(y1)), point_t(to_nt(x2), to_nt(y2)));
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	line_t line(point_t(to_nt(x1), to_nt(y1)), point_t(to_nt(x2), to_nt(y2)));
	treat_intersection(seg, line);
    }
    return 0;
}
