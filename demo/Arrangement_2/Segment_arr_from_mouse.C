//constructs a segment arrangement from CGAL window.
// We use the leda traits (therefore we are using leda functions).

#include <CGAL/basic.h>

#include <CGAL/Arr_leda_segment_exact_traits.h>
#include <CGAL/Arr_2_bases.h>
#include <CGAL/Arr_2_default_dcel.h>
#include <CGAL/Arrangement_2.h>

#include <CGAL/IO/Window_stream.h>

#include <vector>

typedef CGAL::Arr_leda_segment_exact_traits         Traits;

typedef Traits::Point                                  Point;
typedef Traits::X_curve                                X_curve;

typedef CGAL::Arr_base_node<X_curve>   Base_node;
typedef CGAL::Arr_2_default_dcel<Traits> Dcel;

typedef CGAL::Arrangement_2<Dcel,Traits,Base_node > Arr_2;


CGAL_BEGIN_NAMESPACE
Window_stream& operator<<(Window_stream& os,
                          Arr_2 &A)
{
   Arr_2::Halfedge_iterator it = A.halfedges_begin();

   os << BLUE;

    while(it != A.halfedges_end()){

      os << (*it).curve();
      ++it; ++it;

    }

    os << GREEN;
    Arr_2::Vertex_iterator vit = A.vertices_begin();
    while(vit!=A.vertices_end()) {
      os << (*vit).point();
      ++vit;
    }

    os.set_flush( 1 );
    os.flush();

    return os;
}
CGAL_END_NAMESPACE

//I had to add these in global namespace for the program to compile
CGAL::Window_stream& operator<<(CGAL::Window_stream& os,
                          const Point& p);
/*
{
  //return os << leda_point(p.xcoordD(),p.ycoordD());
  return os << p.to_point();
}
*/
CGAL::Window_stream& operator<<(CGAL::Window_stream& os,
                          const X_curve &c);
/*
{
  //  return os << leda_segment(c.xcoord1D(),c.ycoord1D(),c.xcoord2D(),c.ycoord2D());
  return os << c.to_segment();
}
*/
int main()
{
  Arr_2 pm; //confusing with the names but easier work

 //for now
  CGAL::Window_stream W(400, 400);
  double x0=-400,x1=400,y0=-400;

  W.init(x0,x1,y0);
  W.set_mode(leda_src_mode);
  W.set_node_width(3);
  W.button("finish",10);
  W.display();

  //read input from window
  std::cout << "left button to start and end the segment\n";
  std::cout << "clicking close to a vertex, assumes the location is at the vertex"
       << std::endl;

  std::vector<Point> cv1;

  Point pnt;
  bool begin=true;

  for (;;) {
    double x, y;
    int b = W.get_mouse(x,y);
    if (b==10) break;
    pnt = Point(x,y);
  
    if (b == MOUSE_BUTTON(1))
      {
        
        for(Arr_2::Vertex_iterator vi = pm.vertices_begin();
            vi != pm.vertices_end(); ++vi) {
          //we are using the leda sqr_dist func
          if ( pnt.sqr_dist(vi->point()) < ((x1-x0)/50)*((x1-x0)/50) )
            pnt=vi->point();
        }
        
        cv1.push_back(pnt);
        W << CGAL::BLACK;
        W << pnt;
        W << CGAL::GREEN;
        
        if (!begin) {
          pm.insert(X_curve(cv1[0],cv1[1]));
          cv1.clear();
          W << pm;
        }
        begin=!begin;
      }

  }

  
  W << pm;
   
  //LOCATION
  std::cout << "\nEnter a point with left button." << std::endl;
  W << CGAL::RED;

  Point p;

  Arr_2::Halfedge_handle e;
  
  for (; ; ) {

    double x,y;
    int b=W.read_mouse(x,y);
    if (b==10) break;
    else
      p=Point(x,y);

    W << pm;
    
    Arr_2::Locate_type lt;
    e = pm.locate(p,lt);

    //color the face on the screen
    Arr_2::Face_handle f=e->face();
    if (f->does_outer_ccb_exist()) {
      Arr_2::Ccb_halfedge_circulator cc=f->outer_ccb();
      do {
        W << cc->curve();
      } while (++cc != f->outer_ccb());
      
    }
    
    Arr_2::Holes_iterator hit=f->holes_begin(),eit=f->holes_end();
    for (;hit!=eit; ++hit) {
      Arr_2::Ccb_halfedge_circulator cc=*hit; 
      do {
        W << cc->curve();
      } while (++cc != *hit);

    }      
  }


  return 0;  
}







 













