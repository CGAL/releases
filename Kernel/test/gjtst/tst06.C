/*
 * Line Bbox intersectie.
 */
#include <CGAL/Cartesian.h>
#include <CGAL/Line_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Bbox_2_Line_2_intersection.h>
#include "tst.h"

typedef CGAL_TestfieldC testfield;
typedef CGAL_Cartesian<testfield> myR;
typedef CGAL_Point_2< myR > point_t;
typedef CGAL_Line_2< myR > line_t;
typedef CGAL_Segment_2< myR > segment_t;

template <class R>
void print(const CGAL_Point_2<R> &pt)
{
    cout << CGAL_to_double(pt.x()) <<' '<<CGAL_to_double(pt.y());
}

int main()
{
    double x1, x2, y1, y2;
    int i, n;
    cin >> n;
    if (!cin)
	return 1;
    for (i=0; i<n; i++) {
	cin >> x1 >> x2 >> y1 >> y2;
	if (!cin)
	    return 1;
        CGAL_Bbox_2 box(x1, x2, y1, y2);
	cin >> x1 >> y1 >> x2 >> y2;
	if (!cin)
	    return 1;
	line_t l1(point_t(to_nt(x1), to_nt(y1)), point_t(to_nt(x2), to_nt(y2)));
	CGAL_Bbox_2_Line_2_pair<myR> pair(&box, &l1);
	switch (pair.intersection_type()) {
	case CGAL_Bbox_2_Line_2_pair<myR>::NO:
	    cout << "No intersection.\n";
	    break;
	case CGAL_Bbox_2_Line_2_pair<myR>::SEGMENT: {
	    cout << "Segment intersection.\n";
	    CGAL_Segment_2< CGAL_Cartesian<double> > seg;
	    pair.intersection(seg);
	    print(seg.source());
	    cout<<' ';
	    print(seg.target());
	    cout<<'\n';
	    break; }
	case CGAL_Bbox_2_Line_2_pair<myR>::POINT: {
	    CGAL_Point_2< CGAL_Cartesian<double> > pt;
	    cout << "Point intersection.\n";
	    pair.intersection(pt);
	    print(pt);
	    cout <<'\n';
	    break;}
	}
    }
    return 0;
}
