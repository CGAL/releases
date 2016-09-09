/*  stream_iterator.C              */
/*  ------------------------------ */
/*  CGAL example program for the CGAL stream iterator adaptor. */

#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/copy_n.h>
#include <CGAL/IO/Istream_iterator.h>
#include <CGAL/IO/Ostream_iterator.h>
#include <CGAL/IO/leda_window.h>
#include <algo.h>

typedef CGAL_Cartesian<double>                         TutorialR;
typedef CGAL_Point_2<TutorialR>                        Point_2;
typedef CGAL_Creator_uniform_2<double,Point_2>         Creator;
typedef CGAL_Random_points_in_disc_2<Point_2,Creator>  Random_points_in_disc_2;

void init_window( leda_window& W) {
    CGAL_cgalize( W);
    W.set_fg_color( leda_green);
    W.display();
    W.init(-1.0, 1.0, -1.0);
}

int main()
{
    Point_2  points[100];

    /* Create 100 random points uniform distributed in a disc of radius 1. */
    /* Use deterministic initialization for the random number generator.   */
    CGAL_Random rnd(1);
    Random_points_in_disc_2  rnd_points( 1.0, rnd);
    CGAL_copy_n( rnd_points, 100, points);

    /* Display points in a 512x512 pixel window. */
    leda_window W(512, 512);
    init_window( W);
    copy( points, points+100, 
	  CGAL_Ostream_iterator<Point_2, CGAL_Window_stream>(W));

    /*  Wait for mouse click in window. */
    CGAL_Istream_iterator<Point_2, CGAL_Window_stream>  si(W);
    Point_2 q = *si;  // W >> q;

    return 0;
}

