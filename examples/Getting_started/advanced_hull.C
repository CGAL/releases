#include <CGAL/Homogeneous.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/predicate_objects_on_points_2.h>
#include <vector>
#include <iterator>
#include <iostream>

typedef CGAL::Homogeneous<long> Rep_class;


const int IN_COUNT = 6;

struct Special_point {
    Special_point() {}
    Special_point(int x, int y) : pt(x, y), next_on_hull(0) {}
    CGAL::Point_2<Rep_class> pt;
    Special_point *next_on_hull;
};

struct Special_less_xy {
    bool operator()(Special_point *p, Special_point *q) const
        { return CGAL::lexicographically_xy_smaller(p->pt, q->pt); }
};

struct Special_less_yx {
    bool operator()(Special_point *p, Special_point *q) const
        { return CGAL::lexicographically_yx_smaller(p->pt, q->pt); }
};

struct Special_right_of_line {
    Special_right_of_line(Special_point *p, Special_point *q)
                    :rol(p->pt, q->pt) {}
    bool operator()(Special_point *r) const
                    { return rol(r->pt);}
private:
    CGAL::r_Right_of_line<Rep_class> rol;
};

struct Special_leftturn {
    bool operator()(Special_point *p, Special_point *q, Special_point *r)const
        { return CGAL::leftturn(p->pt, q->pt, r->pt); }
};

struct Special_point_traits {
    typedef Special_point * Point_2;
    typedef Special_less_xy Less_xy;
    typedef Special_less_yx Less_yx;
    typedef Special_right_of_line Right_of_line;
    typedef Special_leftturn Leftturn;
    Less_xy get_less_xy_object() const
      { return Less_xy(); }
    Less_yx get_less_yx_object() const
      { return Less_yx(); }
    Right_of_line get_right_of_line_object(
                      const Point_2& p, const Point_2& q) const
      { return Right_of_line( p, q); }
    Leftturn get_leftturn_object() const
      { return Leftturn(); }
    Special_point_traits() {}
};

static Special_point in[IN_COUNT] = {
    Special_point(0, 0),
    Special_point(3, 4),
    Special_point(0, 10),
    Special_point(11, 12),
    Special_point(7, 1),
    Special_point(6, 5),
};

typedef std::vector<Special_point *> Pointer_collection;

// Link the points of the convex hull together, given a vector of pointers
// to the points on the convex hull.
Special_point *
link(Pointer_collection &c)
{
    Pointer_collection::iterator cur, prev;
    cur = c.begin();
// return NULL if there are no points.
    if (cur == c.end())
        return 0;
// prev and cur iterate over all CH points. prev lags one behind.
// Every time we set the next pointer in prev to cur.
    prev = cur;
    ++ cur;
    while (cur != c.end()) {
        (*prev)->next_on_hull = *cur;
        prev = cur;
        ++cur;
    }
// Close the chain.
    (*prev)->next_on_hull = c.front();
    return *prev;
}

main()
{
// Initialise a vector with pointers to the input points.
    Pointer_collection pointers(IN_COUNT), out;
    for (int i=0; i<IN_COUNT; i++)
        pointers[i] = in+i;

// Compute the convex hull of the pointers.
    CGAL::convex_hull_points_2(
                pointers.begin(),
                pointers.end(),
                std::back_inserter(out),
                Special_point_traits());

// Link the points of the convex hull together.
    Special_point *first, *cur;
    cur = first = link(out);

// Print all points of the convex hull.
    if (first != 0)
        do {
            std::cout << cur->pt << '\n';
            cur = cur->next_on_hull;
        } while (cur != first);
}
