/*
 * 2D Triangle Point intersection.
 */

#include <iostream.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Object.h>
#include <CGAL/test_types.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Point_2_Triangle_2_intersection.h>
#include "tst.h"

typedef CGAL_TestfieldC testfield;
typedef CGAL_Cartesian<testfield> myR;
typedef CGAL_Point_2< myR > point_t;
typedef CGAL_Triangle_2< myR > trian_t;

template <class R>
void print(const CGAL_Point_2<R> &pt)
{
    cout << CGAL_to_double(pt.x()) <<' '<<CGAL_to_double(pt.y());
}



void one_pair(point_t const & pt, trian_t const & trian)
{
    typedef CGAL_Point_2_Triangle_2_pair<myR> Is_type;
    point_t point;
    Is_type pair(&pt, &trian);
    switch (pair.intersection_type()) {
    case Is_type::POINT:
	cout<<"Point intersection.\n";
	pair.intersection(point);
	print(point);
	cout<<'\n';
	break;
    case Is_type::NO:
	cout<<"No intersection.\n";
	break;
    }

    if (CGAL_do_intersect(point, trian))
	;

    CGAL_Object result = CGAL_intersection(point, trian);
    if (CGAL_assign(point, result)) {
	cout << "Point intersection.\n";
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
	cin >> x1 >> y1;
	if (!cin)
	    return 1;
	point_t pt(to_nt(x1), to_nt(y1));
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	if (!cin)
	    return 1;
	trian_t trian(point_t(to_nt(x1), to_nt(y1)),
		       point_t(to_nt(x2), to_nt(y2)),
		       point_t(to_nt(x3), to_nt(y3)));
	one_pair(pt, trian);
    }
}
