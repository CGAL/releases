#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <assert.h>

main()
{
    Point p1(0, -5), p2(3, -4), p3(4, 3), in(-1, 4), out(5, -1), on(0, 5);
    CGAL::Bounded_side inside, onside, outside;
    inside = CGAL::side_of_bounded_circle(p1, p2, p3, in);
    outside = CGAL::side_of_bounded_circle(p1, p2, p3, out);
    onside = CGAL::side_of_bounded_circle(p1, p2, p3, on);
    assert(inside == CGAL::ON_BOUNDED_SIDE);
    assert(outside == CGAL::ON_UNBOUNDED_SIDE);
    assert(onside == CGAL::ON_BOUNDARY);
}
