/*  generators_example2.C           */
/*  ------------------------------- */
/*  CGAL example program for point generators creating integer points. */
/*  Derived from generators_prog2.C, without visualization.            */
/*  12.06.1997  V1.0   Lutz Kettner   */ 

#include <CGAL/basic.h>
#include <assert.h>
#include <vector.h>
#include <algo.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>

typedef CGAL_Cartesian<int>  R;
typedef CGAL_Point_2<R>      Point;

/* Provide your own CGAL_build_point function. */
inline
Point& CGAL_build_point( double x, double y, Point& p) {
    p = Point( int(x), int(y));
    return p;
}

#include <CGAL/point_generators_2.h>
#include <CGAL/ncopy.h>


int main()
{
    /* Create test point set. Prepare a vector for 400 points. */
    vector<Point> points;
    points.reserve(400);

    /* Create 250 points from a 16 x 16 grid. Note that the double */
    /* arithmetic _is_ sufficient to produce exact integer grid points. */
    /* The distance between neighbors is 34 pixel = 510 / 15. */
    CGAL_points_on_square_grid_2( 510.0, 250, back_inserter(points),(Point*)0);

    /* Lower, left corner. */
    assert( points[0].x() == -255);
    assert( points[0].y() == -255);

    /* Upper, right corner. Note that 6 points are missing to fill the grid. */
    assert( points[249].x() == 255 - 6 * 34);
    assert( points[249].y() == 255);

    /* Create 250 points within a disc of radius 150. */
    CGAL_Random_points_in_disc_2<Point> g( 150.0);
    CGAL_ncopy( g, 250, back_inserter( points));

    /* Check that we have really created 500 points. */
    assert( points.size() == 500);

    return 0;
}
