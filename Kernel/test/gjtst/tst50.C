#include <CGAL/Cartesian.h>
#include <iostream.h>
#include <CGAL/test_types.h>
#include <CGAL/Object.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Triangle_2_Triangle_2_intersection.h>
#include "tst.h"

typedef CGAL_TestfieldC testfield;
typedef CGAL_Cartesian<testfield> myR;
typedef CGAL_Point_2< myR > point_t;
typedef CGAL_Segment_2< myR > segment_t;
typedef CGAL_Triangle_2< myR > trian_t;

template <class R>
void print(const CGAL_Point_2<R> &pt)
{
    cout << CGAL_to_double(pt.x()) <<' '<<CGAL_to_double(pt.y());
}



void one_pair(trian_t const & trian1, trian_t const & trian2)
{
    segment_t seg;
    trian_t trian3;
    point_t point;
    CGAL_Triangle_2_Triangle_2_pair<myR> pair(&trian1, &trian2);
    switch (pair.intersection_type()) {
    case CGAL_Triangle_2_Triangle_2_pair<myR>::POLYGON:
	cout<<"Polygon intersection.\n";
	pair.intersection();
	break;
    case CGAL_Triangle_2_Triangle_2_pair<myR>::TRIANGLE:
	cout<<"Triangle intersection.\n";
	pair.intersection(trian3);
	break;
    case CGAL_Triangle_2_Triangle_2_pair<myR>::SEGMENT:
	cout<<"Segment intersection.\n";
	pair.intersection(seg);
	break;
    case CGAL_Triangle_2_Triangle_2_pair<myR>::POINT:
	cout<<"Point intersection.\n";
	pair.intersection(point);
	break;
    case CGAL_Triangle_2_Triangle_2_pair<myR>::NO:
	cout<<"No intersection.\n";
	break;
    }

    if (CGAL_do_intersect(trian1, trian2))
	;

    CGAL_Object result = CGAL_intersection(trian1, trian2);
    if (CGAL_assign(point, result)) {
	cout << "Point intersection.\n";
    }
    if (CGAL_assign(seg, result)) {
	cout << "Segment intersection.\n";
    }
    if (CGAL_assign(trian3, result)) {
	cout << "Triangle intersection.\n";
    }
}

main()
{
    double x1, x2, x3, y1, y2, y3;
    int i, n;
    cin >> n;
    if (!cin)
	return 1;
    for (i=0; i<n; i++) {
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	if (!cin)
	    return 1;
	trian_t trian1(point_t(to_nt(x1), to_nt(y1)),
		       point_t(to_nt(x2), to_nt(y2)),
		       point_t(to_nt(x3), to_nt(y3)));
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	if (!cin)
	    return 1;
	trian_t trian2(point_t(to_nt(x1), to_nt(y1)),
		       point_t(to_nt(x2), to_nt(y2)),
		       point_t(to_nt(x3), to_nt(y3)));
	one_pair(trian1, trian2);
    }
}
