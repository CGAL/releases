/*  Segment_generator_example2.C    */
/*  ------------------------------- */
/*  CGAL example program for the generic segment generator         */
/*  using precomputed point locations.                             */
/*  Derived from Segment_generator_prog2.C, without visualization. */
/*  12.06.1997  V1.0   Lutz Kettner   				   */

#include <CGAL/basic.h>
#include <assert.h>
#include <vector.h>
#include <algo.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/Segment_generator.h>
#include <CGAL/copy_n.h>

typedef CGAL_Cartesian<double>  R;
typedef CGAL_Point_2<R>         Point;
typedef CGAL_Segment_2<R>       Segment;

int main()
{
    /* Prepare two point vectors for the precomputed points. */
    vector<Point> p1, p2;
    p1.reserve(100);
    p2.reserve(100);

    /* Create points for a horizontal like fan. */
    CGAL_points_on_segment_2( Point(-250, -50), Point(-250, 50),
			      50, back_inserter( p1));
    CGAL_points_on_segment_2( Point( 250,-250), Point( 250,250),
			      50, back_inserter( p2));
    
    /* Create points for a vertical like fan. */
    CGAL_points_on_segment_2( Point( -50,-250), Point(  50,-250),
			      50, back_inserter( p1));
    CGAL_points_on_segment_2( Point(-250, 250), Point( 250, 250),
			      50, back_inserter( p2));
    
    /* Create test segment set. Prepare a vector for 100 segments. */
    vector<Segment> segs;
    segs.reserve(100);

    /* Create both fans at once from the precomputed points. */
    typedef  vector<Point>::iterator  I;
    I i1 = p1.begin();
    I i2 = p2.begin();
    CGAL_Segment_generator<Segment,I,I> g( i1, i2);
    CGAL_copy_n( g, 100, back_inserter( segs));

    assert( segs.size() == 100);
    for (vector<Segment>::iterator i = segs.begin(); i!=segs.end(); i++){
	assert( (*i).source().x() <=  250);
	assert( (*i).source().x() >= -250);
	assert( (*i).source().y() <=  250);
	assert( (*i).source().y() >= -250);
	assert( (*i).target().x() <=  250);
	assert( (*i).target().x() >= -250);
	assert( (*i).target().y() <=  250);
	assert( (*i).target().y() >= -250);
    }
    return 0;
}
