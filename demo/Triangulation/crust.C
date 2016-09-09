#include <assert.h>
#include <iostream.h>
#include <set.h>

#include <CGAL/basic.h>
#include <CGAL/double.h>
#include <CGAL/Cartesian.h>
#include <CGAL/predicate_objects_on_points_2.h>

#include <CGAL/Triangulation_euclidean_traits_2.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef double testnt;
typedef CGAL_Cartesian<testnt> TestR;

typedef CGAL_Line_2< TestR > Line;
typedef CGAL_Triangulation_euclidean_traits_2< TestR > Traits;
typedef CGAL_Triangulation_2<Traits>  Triangulation_2;
typedef CGAL_Delaunay_triangulation_2<Traits>  Delaunay_2;

typedef Traits::Point  Point;
typedef Traits::Point  Point;
typedef Triangulation_2::Face  Face;
typedef Triangulation_2::Vertex Vertex;
typedef Triangulation_2::Face_handle   Face_handle;
typedef Triangulation_2::Vertex_handle Vertex_handle;

typedef CGAL_p_Less_xy<Point> Point_compare;

typedef Triangulation_2::Face_circulator  Face_circulator;
typedef Triangulation_2::Face_iterator  Face_iterator;
typedef Triangulation_2::Edge_iterator  Edge_iterator;

#include <CGAL/IO/Window_stream.h>

typedef CGAL_Window_stream  Window_stream;

Delaunay_2 T;
Window_stream W(400,400);

char*
db_pretty_print(const Vertex *v,
                int ,
                char *)
{
    if (v == &(*T.infinite_vertex())) return "infinity";
    W << CGAL_ORANGE << v->point();
    return "Pretty print in CGAL Window (in Orange)";
}
char*
db_pretty_print(const Face *f,
                int ,
                char *)
{
    if (T.is_infinite(Face_handle(f))) return "infinity";
    W << CGAL_ORANGE << T.triangle(Face_handle(f));
    return "Pretty print in CGAL Window (in Orange)";
}

void pause()
{
  double x, y;
  cerr << "Press any button to continue" << endl;
  W.read_mouse(x,y);
}

int main(int argc, char *argv[])
{
  int n; 

  CGAL_set_pretty_mode(cout);
  W.init(0.0,5.0,0.0);
  W.set_node_width(3);
  W.display();
  W << CGAL_BLUE;

  cout << "Enter points with left button" << endl;
  cout << "Finish by clicking right button" << endl;
  while (1) {
    TestR::RT x, y;
    if (W.read_mouse(x,y)==MOUSE_BUTTON(3))
    	break;
    T.insert(Point(x,y));
    W.clear();
    W << T;
  }

  assert(T.is_valid());
  W.clear();
  W << CGAL_BLUE << T;
  pause();
  
  Face_iterator f;
  set<Point,Point_compare> s;
  for (f=T.faces_begin(); f!=T.faces_end(); ++f)
    s.insert( T.dual(f) );
  set<Point,Point_compare>::iterator p;
  for (p=s.begin(); p!=s.end(); ++p)
    T.insert(*p);

  assert(T.is_valid());
  W << CGAL_GREEN << T;
  cout << "All the Voronoi vertices have been inserted in the Delaunay triangulation" << endl;
  cout << "Click on any button to continue" << endl;
  pause();

  W.clear();
  Edge_iterator e;
  for (e=T.edges_begin(); e!=T.edges_end(); ++e) {
    Face_handle f=(*e).first; int i=(*e).second;
    bool s1=s.find(f->vertex(f->ccw(i))->point())==s.end();
    bool s2=s.find(f->vertex(f->cw(i))->point())==s.end();
    if (!s1&&!s2)  { W << CGAL_VIOLET << T.segment(e); }
    if (s1&&s2)  { W << CGAL_RED << T.segment(e); }
  }
  cout << "The crust is displayed in red" << endl;
  cout << "A superset of the median axis is displayed in purple" << endl;
  pause();

  return 0;
}
