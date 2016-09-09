#include <assert.h>
#include <iostream.h>

#include <CGAL/basic.h>
#include <iostream.h>
#include <CGAL/double.h>
#include <CGAL/Cartesian.h>

#include <CGAL/Line_2.h>
#include <CGAL/Triangulation_euclidean_traits_2.h>
#include <CGAL/Triangulation_2.h>

typedef double testnt;
typedef CGAL_Cartesian<testnt> TestR;

typedef CGAL_Line_2< TestR > Line;
typedef CGAL_Triangulation_euclidean_traits_2< TestR > Traits;
typedef CGAL_Triangulation_2<Traits>  Triangulation_2;

typedef Traits::Point  Point;
typedef Triangulation_2::Face  Face;
typedef Triangulation_2::Vertex Vertex;
typedef Triangulation_2::Face_handle   Face_handle;
typedef Triangulation_2::Vertex_handle Vertex_handle;

typedef Triangulation_2::Face_circulator  Face_circulator;
typedef Triangulation_2::Face_iterator  Face_iterator;
typedef Triangulation_2::Line_face_circulator  Line_face_circulator;

#include <CGAL/IO/Window_stream.h>

typedef CGAL_Window_stream  Window_stream;

Window_stream W(400,400);

void pause()
{
  double x, y;
  cerr << "Press any button to continue" << endl;
  W.read_mouse(x,y);
}

int main(int argc, char *argv[])
{
  Triangulation_2 T;
  Vertex_handle v;  
  int n; 

  CGAL_set_pretty_mode(cout);
  W.init(-1.1,1.1,-1.1);
  W.set_mode(leda_src_mode);
  W.set_node_width(3);
  W.display();
  W << CGAL_BLUE;

  cout << "Enter points with left button" << endl;
  cout << "Finish by clicking right button" << endl;
  while (1) {
    TestR::RT x, y;
    if (W.read_mouse(x,y)==MOUSE_BUTTON(3))
    	break;
    v = T.insert(Point(x,y));
    cout << "Inserted Point("<<x<<","<<y<<")"<<endl;
    W << v->point();
    W << T;
  }

  assert(T.is_valid());
  W << T;
  pause();
  
  while (1) {  
    cout << "Enter two points with left button" << endl;
    cout << "Finish by clicking right button" << endl;
    TestR::RT x, y;    
    if (W.read_mouse(x,y)==MOUSE_BUTTON(3)) break; Point p(x,y);
    if (W.read_mouse(x,y)==MOUSE_BUTTON(3)) break; Point q(x,y);
    cout << "Faces crossed by line joining " << p << "," << q << endl;
    W << CGAL_RED << Line(p,q) << CGAL_BLUE;
    Line_face_circulator lfcirc=T.line_walk(p,q), done(lfcirc);
    if (lfcirc==NULL) 
      cout << "No such face" << endl;
    else do {
      cout << T.triangle(lfcirc) << endl;
      W << CGAL_RED;
      W << T.triangle(lfcirc);
      pause();
      W << CGAL_BLUE;
      W << T.triangle(lfcirc);
      ++lfcirc;
      // The following corrects a bug of triangulation
      // normally ++lfcirc skips infinite triangles, but since it is used in insert
      // we need the infinite triangles
      while (T.is_infinite(lfcirc)) { cout << "Triangle infini" << endl; ++lfcirc; }
    } while (lfcirc != done);
  }

  return 0;
}
