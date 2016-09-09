/*  triangulation_basic_example.C */
/*--------------------------------*/
#include <CGAL/Object.h>
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

typedef CGAL_Window_stream                            Window_stream;

typedef CGAL_Cartesian<double>                        Rep;

typedef CGAL_Triangulation_euclidean_traits_2<Rep>    Traits;
typedef CGAL_Delaunay_triangulation_2<Traits>         Triangulation;

typedef Traits::Point                                 Point;
typedef Traits::Line                                  Line;
typedef Traits::Ray                                   Ray;
typedef Traits::Segment                               Segment;

typedef CGAL_Vector_2<Rep>                            Vector;
typedef CGAL_Creator_uniform_2<double,Point>          Creator;

typedef Triangulation::Face::Face_handle              Face_handle;
typedef Triangulation::Face_iterator                  Face_iterator;
typedef Triangulation::Edge_iterator                  Edge_iterator;
typedef Triangulation::Vertex_circulator              Vertex_circulator;
typedef Triangulation::Line_face_circulator           Line_face_circulator;

void draw_faces_along_line(Triangulation &T, Window_stream &W);
void draw_convex_hull(Triangulation &T, Window_stream &W);
void draw_dual( Triangulation& T, Window_stream &W );

int main(int argc, char* argv[])
{
    Triangulation T;

    CGAL_Window_stream W(400,400);
    W.init(-1.1, 1.1, -1.1);
    W.set_node_width(3);
    W.display();

    cout << "Entering 100 random points" << endl;
    CGAL_Random_points_in_disc_2<Point,Creator> r(1.0);
    CGAL_copy_n( r, 100, back_inserter(T));
    W << CGAL_BLUE << T;

    draw_faces_along_line(T, W);
    draw_convex_hull(T, W);
    draw_dual(T, W);
    double x,y; W.read_mouse(x,y); return 0;
}

void draw_faces_along_line(Triangulation &T, Window_stream &W)
{
    Point p, q;
    cerr << "Enter two points" << endl;
    W >> p >> q;
    W << p << q << Line(p,q) << CGAL_RED;

    Face_handle          f   = T.locate(p);
    Line_face_circulator lfc = T.line_walk(p, q, f),
                         done(lfc);
    if (lfc == NULL)
        cerr << "Line does not intersect convex hull" << endl;
    else
        do {
            W << CGAL_RED << T.triangle( lfc );
        } while (++lfc != done);
}

void draw_convex_hull(Triangulation &T, Window_stream &W)
{
    Vertex_circulator chc = T.infinite_vertex()->incident_vertices(),
                      done(chc);
    Point p = chc->point();
    do {
         --chc;
         Point q = chc->point();
         W << Segment(p, q);
         p = q;
    } while(chc != done);
}

void draw_dual( Triangulation& T, Window_stream &W )
{
    Face_iterator fit, fbegin=T.faces_begin(), fend=T.faces_end();
    /* Display the Voronoi vertices */
    for (fit=fbegin; fit != fend; ++fit)
        W << CGAL_RED << T.dual(fit);

    Edge_iterator eit, ebegin=T.edges_begin(), eend=T.edges_end();
    /* Display the Voronoi edges */
    for (eit=ebegin; eit != eend; ++eit)
    {
        Ray r;
        Segment s;
        CGAL_Object o = T.dual(eit);
        if (CGAL_assign(s,o)) W << CGAL_RED << s;
        if (CGAL_assign(r,o)) W << CGAL_RED << r;
    }
}

