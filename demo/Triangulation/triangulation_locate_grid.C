/* triangulation_locate_grid.C */
/* ----------------------------*/
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Segment_2.h>

#include <CGAL/point_generators_2.h>
#include <CGAL/copy_n.h>
#include <CGAL/predicates_on_points_2.h>

#include <CGAL/Triangulation_euclidean_traits_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/IO/Window_stream.h>

typedef double                                        coord_type;
typedef CGAL_Cartesian<coord_type>                    Rep;

typedef CGAL_Point_2<Rep>                             Point;
typedef CGAL_Vector_2<Rep>                            Vector;
typedef CGAL_Segment_2<Rep>                           Segment;

typedef CGAL_Triangulation_euclidean_traits_2<Rep>    Traits;
typedef CGAL_Delaunay_triangulation_2<Traits>         Triangulation_2;
typedef Triangulation_2::Face_handle                  Face_handle;

int main(int argc, char* argv[])
{
    Triangulation_2 T;

    CGAL_Window_stream W(400,400);
    W.init(-1.1, 1.1, -1.1);
    W.set_node_width(3);
    W.display();

    cout << "Entering 500 random points" << endl;
    typedef CGAL_Creator_uniform_2<double,Point> Creator;
    CGAL_Random_points_in_square_2<Point,Creator> r(1.0);
    CGAL_copy_n( r, 500, back_inserter(T));
    W << CGAL_BLUE << T;

    cout << "Locating a 5x5 grid vertices by walking in the triangulation" << endl;
    Point p0(-0.75,-0.75), p, q;
    Vector up(0.0,0.2), right(0.3,0.0);
    int index_up[25]    = {0,1,2,3,4,4,3,2,1,0,0,1,2,3,4,4,3,2,1,0,0,1,2,3,4};
    int index_right[25] = {0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4};
    int k;
    
    Face_handle f = T.locate(p0);
    W << CGAL_RED << p0 << T.triangle(f);
    for (k=0; k<24; k++) {
        p = p0 + up * index_up[k] + right * index_right[k];
        q = p0 + up * index_up[k+1] + right * index_right[k+1];
        W << CGAL_GREEN << Segment(p,q);
        f = T.locate(q,f);
        W << CGAL_RED << q << T.triangle(f);
    }

    cout << "The triangles containing the grid vertices are displayed in red" << endl;
    cout << "The traversal of the grid is displayed in green" << endl;
    cout << "Only the triangles intersecting the green lines have been explored" << endl;
    double x,y; W.read_mouse(x,y); return 0;
}
