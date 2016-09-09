// ---------------------------------------
// Example program from Getting Started with CGAL
// Chapter: Traits classes in CGAL (alternative implementation)
// Author: Geert-Jan Giezeman
// June 1997
// ---------------------------------------

#include <CGAL/Homogeneous.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/predicate_objects_on_points_2.h>
#include <vector.h>
#include <iostream.h>

typedef CGAL_Homogeneous<long> Rep;

typedef CGAL_Point_2<Rep> Point_2;

const int IN_COUNT = 6;

struct Special_point: public CGAL_Point_2<Rep> {
    Special_point() {}
    Special_point(int x, int y) : CGAL_Point_2<Rep>(x, y), next_on_hull(0) {}
//    CGAL_Point_2<Rep> pt;
    Special_point *next_on_hull;
};

struct Special_less_xy {
    bool operator()(Special_point *p, Special_point *q) const
	{ return CGAL_lexicographically_xy_smaller(*p, *q); }
};

struct Special_less_yx {
    bool operator()(Special_point *p, Special_point *q) const
	{ return CGAL_lexicographically_yx_smaller(*p, *q); }
};

struct Special_greater_xy {
    bool operator()(Special_point *p, Special_point *q) const
	{ return CGAL_lexicographically_xy_larger(*p, *q); }
};

struct Special_greater_yx {
    bool operator()(Special_point *p, Special_point *q) const
	{ return CGAL_lexicographically_yx_larger(*p, *q); }
};

struct Special_right_of_line {
    Special_right_of_line(Special_point *p, Special_point *q)
		    :rol(*p, *q) {}
    bool operator()(Special_point *r) const
		    { return rol(*r);}
private:
    CGAL_r_Right_of_line<Rep> rol;
};

struct Special_point_traits {
    typedef Special_point * Point_2;
    typedef Special_less_xy Less_xy;
    typedef Special_greater_xy Greater_xy;
    typedef Special_less_yx Less_yx;
    typedef Special_greater_yx Greater_yx;
    typedef Special_right_of_line Right_of_line;
    Special_point_traits() {}
    bool    leftturn(Point_2, Point_2, Point_2) const;
};

bool
Special_point_traits::leftturn(
    Point_2 p,
    Point_2 q,
    Point_2 r) const
{
    return CGAL_leftturn(*p, *q, *r);
}

static Special_point in[IN_COUNT] = {
    Special_point(0, 0),
    Special_point(3, 4),
    Special_point(0, 10),
    Special_point(11, 12),
    Special_point(7, 1),
    Special_point(6, 5),
};

typedef vector<Special_point *> Pointer_collection;

Special_point * link(Pointer_collection &c)
{
    Pointer_collection::iterator cur, prev;
    cur = c.begin();
    if (cur == c.end())
	return 0;
    prev = cur;
    ++ cur;
    while (cur != c.end()) {
	(*prev)->next_on_hull = *cur;
	prev = cur;
	++cur;
    }
    (*prev)->next_on_hull = c.front();
    return c.front();
}

void main()
{
// Initialise a vector with pointers to the input points.
    Pointer_collection pointers(IN_COUNT), out;
    for (int i=0; i<IN_COUNT; i++)
	pointers[i] = in+i;

// Compute the convex hull of the pointers.
    CGAL_convex_hull_points_2(
		pointers.begin(),
		pointers.end(),
		back_inserter(out),
		Special_point_traits());

// Link the points of the convex hull together.
    Special_point *first, *cur;
    cur = first = link(out);

// Print all points of the convex hull.
    if (first != 0)
	do {
	    cout << *((CGAL_Point_2<Rep> *) cur) << '\n';
	    cur = cur->next_on_hull;
	} while (cur != first);
}
