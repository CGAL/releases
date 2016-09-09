/*  stream_iterator.C              */
/*  ------------------------------ */
/*  CGAL example program for the CGAL stream iterator adaptor. */

#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/copy_n.h>
#include <CGAL/IO/Istream_iterator.h>
#include <CGAL/IO/Ostream_iterator.h>
#include <CGAL/IO/Window_stream.h>
#include <algo.h>

typedef CGAL_Cartesian<double>                     TutorialR;
typedef CGAL_Point_2<TutorialR>                    Point_2;
typedef CGAL_Random_points_in_disc_2<Point_2>      Random_points_in_disc_2;

int main()
{
    Point_2  points[100];

    /* Create 100 random points uniform distributed in a disc of radius 250. */
    /* Use deterministic initialization for the random number generator.     */
    CGAL_Random rnd(1);
    Random_points_in_disc_2  rnd_points( 250.0, rnd);
    CGAL_copy_n( rnd_points, 100, points);

    /* Display points in a 512x512 pixel window. */
    CGAL_Window_stream W(512, 512);
    W.init(-256.0, 255.0, -256.0);
    copy( points, points+100, 
	  CGAL_Ostream_iterator<Point_2,CGAL_Window_stream>(W));

    /*  Wait for mouse click in window. */
    CGAL_Istream_iterator<Point_2,CGAL_Window_stream>  si(W);
    Point_2 q = *si;  // W >> q;

    return 0;
}

