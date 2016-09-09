#include <iostream.h>
//#include <CGAL/Homogeneous.h>
//#include <CGAL/Quotient.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Object.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Line_2_Iso_rectangle_2_intersection.h>
#include "tst.h"

//typedef CGAL_Homogeneous<CGAL_TestrepH> myR;
typedef CGAL_Cartesian<CGAL_TestfieldC> myR;
typedef CGAL_Point_2< myR > point_t;
typedef CGAL_Line_2< myR > line_t;
typedef CGAL_Segment_2< myR > segment_t;
typedef CGAL_Iso_rectangle_2< myR > rect_t;

template <class R>
void print(const CGAL_Point_2<R> &pt)
{
    cout << CGAL_to_double(pt.x()) <<' '<<CGAL_to_double(pt.y());
}



void one_pair(line_t const & line, rect_t const & rect)
{
    segment_t seg;
    point_t point;
    CGAL_Line_2_Iso_rectangle_2_pair<myR> pair(&line, &rect);
    switch (pair.intersection_type()) {
    case CGAL_Line_2_Iso_rectangle_2_pair<myR>::SEGMENT:
	cout<<"Segment intersection.\n";
	pair.intersection(seg);
	print(seg.source());
	cout<<' ';
	print(seg.target());
	cout<<'\n';
	break;
    case CGAL_Line_2_Iso_rectangle_2_pair<myR>::POINT:
	cout<<"Point intersection.\n";
	pair.intersection(point);
	print(point);
	cout<<'\n';
	break;
    case CGAL_Line_2_Iso_rectangle_2_pair<myR>::NO:
	cout<<"No intersection.\n";
	break;
    }
    CGAL_Object result = CGAL_intersection(line, rect);
    if (CGAL_assign(point, result)) {
	cout << "Point intersection.\n";
    }
    if (CGAL_assign(seg, result)) {
	cout << "Segment intersection.\n";
    }
    if (!CGAL_assign(point, result) && !CGAL_assign(seg, result)) {
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
	line_t line(point_t(to_nt(x1), to_nt(y1)),
		       point_t(to_nt(x2), to_nt(y2)));
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	rect_t rect(point_t(to_nt(x1), to_nt(y1)),
		       point_t(to_nt(x2), to_nt(y2)));
	one_pair(line, rect);
    }
}
