//constructs a segment arrangement from file.
// We use a homogeneous representation with the cached traits.

//File format is (coordinates should be between [-400,400] to be in window):
//#number_of_segments
//#x1 y1 x2 y2
// ....
 
// Define shorter names to please linker (g++/egcs)
#define Homogeneous Ho
#define Quotient Qu
#define _In_place_list_iterator IPLI
#define Arrangement_2 Ar
#define Arr_segment_exact_traits ASET
#define bidirectional_iterator_tag BIT
#define Arr_base_node ABN
#define Arr_2_default_dcel A2DD


#include <CGAL/basic.h>
#include <CGAL/Homogeneous.h>
//#include <CGAL/Cartesian.h>

#include <CGAL/Arrangement_2.h>
#include <CGAL/Timer.h>

#include <vector>
#include <fstream>

#include <CGAL/leda_integer.h>
//#include <CGAL/leda_real.h>
//#include <CGAL/leda_rational.h>
//#include <CGAL/Double_eps.h>

#include <CGAL/Arr_2_default_dcel.h>
//#include <CGAL/Arr_segment_exact_cached_traits.h>
#include <CGAL/Arr_segment_exact_traits.h>

#include <CGAL/Pm_walk_along_line_point_location.h>

#include <CGAL/IO/Window_stream.h>

typedef leda_integer NT;
//typedef double                                           NT;
//typedef leda_real                                           NT;
//typedef leda_rational NT;
//typedef CGAL::Double_eps NT;

typedef CGAL::Homogeneous<NT>                      Rep;
//typedef CGAL::Cartesian<NT>                      Rep;

//typedef CGAL::Arr_segment_exact_cached_traits<Rep>          Traits;
typedef CGAL::Arr_segment_exact_traits<Rep>          Traits;

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

void color_face(CGAL::Window_stream& W, Arr_2::Halfedge_handle e,
                CGAL::Color color) {
  //color the face on the screen
  W << color;
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

int main(int argc, char* argv[])
{
  //for Double_eps
  //CGAL::set_eps(0.0001); 

  if (argc != 2) {
    std::cout << "usage: Segment_arr_from_file filename\n";
    exit(1);
  }

  CGAL::Timer insrt_t;

  Arr_2 arr(new CGAL::Pm_walk_along_line_point_location<Arr_2::Planar_map>);

  CGAL::Window_stream W(400, 400);
  double x0=-200,x1=200,y0=-200;

  W.init(x0,x1,y0);
  W.set_mode(leda_src_mode);
  W.set_node_width(3);
  W.button("finish",10);
  W.display();

  std::ifstream file(argv[1]);
  int num_curves;
  file >> num_curves;
  while (num_curves--) {
    //NT x,y;
    double x,y; //(actually int)
    file >> x >> y;
    NT nx(x),ny(y);
    Point s(nx,ny);
    file >> x >> y;
    NT mx(x),my(y);
    Point t(mx,my);
    
    insrt_t.start();
    arr.insert(X_curve(s,t));
    insrt_t.stop();
  }
  
  W << arr;
  
  std::cout << "Total insertion time: " <<  insrt_t.time() << std::endl;

  
  //POINT LOCATION
  std::cout << "\nEnter a point with left button." << std::endl;
  Point p;
  
  Arr_2::Halfedge_handle e=arr.halfedges_begin();
  
  for (; ; ) {
    
    //instead of before
    double x,y;
    int b=W.read_mouse(x,y);
    if (b==10) break;
    else
      p=Point(x,y);

    color_face(W,e,CGAL::BLUE);


    //W << arr;
    
    Arr_2::Locate_type lt;
    e = arr.locate(p,lt);

    //color the face on the screen
    color_face(W,e,CGAL::GREEN);
  }

  return 0;  
}





















