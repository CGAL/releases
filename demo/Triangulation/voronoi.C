#include <CGAL/basic.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <strstream.h>

#include <CGAL/Cartesian.h>

#include <CGAL/squared_distance_2.h>   // to avoid a g++ problem
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Segment_2.h>

#include <CGAL/Triangulation_euclidean_traits_2.h>

#include <CGAL/Delaunay_triangulation_2.h>

#include "parse.h"

//typedef leda_integer  coord_type;
typedef double coord_type;
//typedef CGAL_Fixed coord_type;

typedef CGAL_Cartesian<coord_type>  Rep;
//typedef CGAL_Homogeneous<coord_type>  Rep;

typedef CGAL_Point_2<Rep>  Point;
typedef CGAL_Segment_2<Rep>  Segment;
typedef CGAL_Ray_2<Rep>  Ray;
typedef CGAL_Line_2<Rep>  Line;
typedef CGAL_Triangle_2<Rep>  Triangle;

typedef CGAL_Triangulation_euclidean_traits_2<Rep> Traits;
typedef CGAL_Delaunay_triangulation_2<Traits>  Triangulation_2;

typedef Triangulation_2::Face  Face;
typedef Triangulation_2::Vertex Vertex;
typedef Triangulation_2::Face_handle  Face_handle;
typedef Triangulation_2::Vertex_handle Vertex_handle;

typedef Triangulation_2::Face_circulator  Face_circulator;
typedef Triangulation_2::Vertex_circulator  Vertex_circulator;

typedef Triangulation_2::Locate_type Locate_type;

typedef Triangulation_2::Face_iterator  Face_iterator;
typedef Triangulation_2::Vertex_iterator  Vertex_iterator;
typedef Triangulation_2::Edge_iterator  Edge_iterator;
typedef Triangulation_2::Line_face_circulator  Line_face_circulator;


#include <CGAL/IO/Window_stream.h>

typedef CGAL_Window_stream Window_stream;

int
main(int argc, char* argv[])
{
    Options opt;
    parse(argc, argv, opt);

    Triangulation_2 T;

    Window_stream W(opt.winx, opt.winy); // physical window size
    W.init(opt.min, opt.max, opt.min);   // logical window size
    //  W.set_show_coordinates(true);
    W << CGAL_BLUE;
    W.set_mode(leda_src_mode);
    W.set_node_width(3);
    W.display();

    
    cout << "Enter points with left button" << endl;
    cout << "Finish by clicking right button" << endl;
    while (1) {
      double x, y;
      if (W.read_mouse(x,y)==MOUSE_BUTTON(3))
          break;
      T.insert(Point(x,y));
      W.clear();
      W << T;
    }

    W << CGAL_RED;
    Face_iterator fit, fbegin=T.faces_begin(), fend=T.faces_end(); 
    for (fit=fbegin; fit != fend; ++fit)
	W << T.dual(fit);

    Edge_iterator eit, ebegin=T.edges_begin(), eend=T.edges_end(); 
    for (eit=ebegin; eit != eend; ++eit)
    {
        CGAL_Object o = T.dual(eit);
	Triangulation_2::Ray r;
	Triangulation_2::Segment s;
	if (CGAL_assign(s,o)) W << s;
	if (CGAL_assign(r,o)) W << r;
    }

    cout << "The Voronoi diagram is displayed in red" << endl;
    double x,y; W.read_mouse(x,y);
    return 0;
}
