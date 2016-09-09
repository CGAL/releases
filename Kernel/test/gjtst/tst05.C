/*
 * Intersection of two segments.
 */

#include <CGAL/Cartesian.h>
#include <CGAL/Object.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2_Segment_2_intersection.h>
#include <CGAL/test_types.h>
#include <CGAL/number_utils.h>

#include "tst.h"

typedef CGAL_TestfieldC testfield;
typedef CGAL_Cartesian<testfield> myR;
typedef CGAL_TestfieldC nt;


typedef CGAL_Cartesian<nt> myR;
typedef CGAL_Point_2< myR > point_t;
typedef CGAL_Segment_2< myR > segment_t;


ostream & operator<<(ostream & os, const CGAL_TestfieldC &)
{
  return os;
}


void print(const point_t &pt)
{
    cout << CGAL_to_double(pt.x()) <<' '<<CGAL_to_double(pt.y());
}


void treat_intersection(const segment_t &seg1, const segment_t &seg2)
{
    point_t pt1;
    segment_t iseg;
    CGAL_Segment_2_Segment_2_pair<myR> pair(&seg1, &seg2);
    switch (pair.intersection_type()) {
    case CGAL_Segment_2_Segment_2_pair<myR>::NO:
	cout << "No intersection.\n";
	break;
    case CGAL_Segment_2_Segment_2_pair<myR>::SEGMENT:
	cout << "Segment intersection.\n";
	pair.intersection(iseg);
	pt1 = iseg.source();
	print(pt1);
	cout<<'\n';
	pt1 = iseg.target();
	print(pt1);
	cout<<'\n';
	break;
    case CGAL_Segment_2_Segment_2_pair<myR>::POINT:
	cout << "Point intersection.\n";
	pair.intersection(pt1);
	print(pt1);
	cout<<'\n';
	break;
    }

    CGAL_Object result = CGAL_intersection(seg1, seg2);
    if (CGAL_assign(pt1, result)) {
	cout << "Point intersection.\n";
	print(pt1);
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
	segment_t seg1(point_t(to_nt(x1), to_nt(y1)),
			point_t(to_nt(x2), to_nt(y2)));
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	segment_t seg2(point_t(to_nt(x1), to_nt(y1)),
		    point_t(to_nt(x2), to_nt(y2)));
	treat_intersection(seg1, seg2);
    }
    return 0;
}
