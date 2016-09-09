#include "tutorial.h"
#include <CGAL/convex_hull_2.h>
#include <list.h>
#include <iostream.h>


typedef list<Point_2> pointlist;

const int IN_COUNT = 6;

static Point_2 in[IN_COUNT] = {
    Point_2(0, 0),
    Point_2(3, 4),
    Point_2(0, 10),
    Point_2(11, 12),
    Point_2(7, 1),
    Point_2(6, 5),
};

template <class iterator>
void write(iterator cur, iterator beyond)
{
    for (; cur != beyond; ++cur)
        cout << *cur << '\n';
}

void list_version()
{
    pointlist out;
    CGAL_convex_hull_points_2(in, in+IN_COUNT, back_inserter(out));
    write(out.begin(), out.end());
}

void array_version()
{
    Point_2 out[IN_COUNT], *beyond;
    beyond = CGAL_convex_hull_points_2(in, in+IN_COUNT, out);
    write(out, beyond);
}

void main()
{
    list_version();
    cout<<'\n';
    array_version();
}
