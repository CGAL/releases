#include "tutorial.h"
#include <CGAL/convex_hull_2.h>
#include <list>
#include <iterator>
#include <iostream>


typedef std::list<Point> pointlist;

const int IN_COUNT = 6;

static Point in[IN_COUNT] = {
    Point(0, 0),
    Point(3, 4),
    Point(0, 10),
    Point(11, 12),
    Point(7, 1),
    Point(6, 5),
};

template <class iterator>
void write(iterator cur, iterator beyond)
{
    for (; cur != beyond; ++cur)
        std::cout << *cur << '\n';
}

void list_version()
{
    pointlist out;
    CGAL::convex_hull_points_2(in, in+IN_COUNT, std::back_inserter(out));
    write(out.begin(), out.end());
}

void array_version()
{
    Point out[IN_COUNT], *beyond;
    beyond = CGAL::convex_hull_points_2(in, in+IN_COUNT, out);
    write(out, beyond);
}

main()
{
    list_version();
    std::cout<<'\n';
    array_version();
}
