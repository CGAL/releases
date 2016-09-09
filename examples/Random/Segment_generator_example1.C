/*  Segment_generator_example1.C    */
/*  ------------------------------- */
/*  CGAL example program for the generic segment generator.        */
/*  Derived from Segment_generator_prog1.C, without visualization. */
/*  31.10.1997  V1.1   Lutz Kettner   kettner@acm.org              */

#include <CGAL/basic.h>
#include <assert.h>
#include <vector.h>
#include <algo.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/function_objects.h>
#include <CGAL/Join_input_iterator.h>
#include <CGAL/copy_n.h>

typedef CGAL_Cartesian<double>                R;
typedef CGAL_Point_2<R>                       Point;
typedef CGAL_Creator_uniform_2<double,Point>  Pt_creator;
typedef CGAL_Segment_2<R>                     Segment;

int main()
{
    /* Create test segment set. Prepare a vector for 200 segments. */
    vector<Segment> segs;
    segs.reserve(200);

    /* Prepare point generator for the horizontal segment, length 200. */
    typedef  CGAL_Random_points_on_segment_2<Point,Pt_creator>  P1;
    P1 p1( Point(-100,0), Point(100,0));
    
    /* Prepare point generator for random points on circle, radius 250. */
    typedef  CGAL_Random_points_on_circle_2<Point,Pt_creator>  P2;
    P2 p2( 250);
    
    /* Create 200 segments. */
    typedef CGAL_Creator_uniform_2< Point, Segment> Seg_creator;
    typedef CGAL_Join_input_iterator_2< P1, P2, Seg_creator> Seg_iterator;
    Seg_iterator g( p1, p2);
    CGAL_copy_n( g, 200, back_inserter( segs));

    assert( segs.size() == 200);
    for ( vector<Segment>::iterator i = segs.begin(); i != segs.end(); i++){
	assert( (*i).source().x() <=  100);
	assert( (*i).source().x() >= -100);
	assert( (*i).source().y() ==   0);
	assert( (*i).target().x() * (*i).target().x() +
		(*i).target().y() * (*i).target().y()
		<=  251*251);
	assert( (*i).target().x() * (*i).target().x() +
		(*i).target().y() * (*i).target().y()
		>=  249*249);
    }
    return 0;
}
