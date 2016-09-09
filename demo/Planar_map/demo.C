#include <CGAL/basic.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <strstream.h>

#include <CGAL/Cartesian.h>

#include <CGAL/squared_distance_2.h>   // to avoid a g++ problem
#include <CGAL/Point_2.h>
//#include <CGAL/predicates_on_points_2.h>
#include <CGAL/Segment_2.h>

#include <CGAL/Pm_segment_epsilon_traits.h>
#include <CGAL/Pm_default_dcel.h>

#ifndef  CGAL_PLANAR_MAP_2_H
#include <CGAL/Planar_map_2.h>
#endif

#include <CGAL/IO/Window_stream.h>

#include "draw_map.h"


//general typedefs

typedef double coord_type;
typedef CGAL_Cartesian<coord_type>  Rep;
typedef CGAL_Point_2<Rep>  Point;
typedef CGAL_Segment_2<Rep>  Segment;

typedef CGAL_Window_stream  Window_stream;


//planar_map typedefs

typedef CGAL_Pm_segment_epsilon_traits<Rep>  pmtraits;
typedef CGAL_Pm_default_dcel<pmtraits>       pmdcel;
typedef CGAL_Planar_map_2< pmdcel, pmtraits > pmmap;

typedef typename pmtraits::X_curve curve;

typedef typename pmmap::Vertex Vertex;
typedef typename pmmap::Halfedge Halfedge;
typedef typename pmmap::Face Face;

typedef typename pmmap::Vertex_iterator  Vertex_iterator;
typedef typename pmmap::Halfedge_iterator  Halfedge_iterator;


#ifdef __GNU__
template < class R >
bool operator<(const CGAL_Point_2<R>& p, const CGAL_Point_2<R>& q)
{
    return CGAL_compare_lexicographically_xy (p, q) == CGAL_SMALLER;
}
#endif // __GNU__

Window_stream *W_global;

void
any_button(CGAL_Window_stream &W)
{
    double x, y;
    cerr << "Press any button to continue" << endl;
    W.read_mouse(x,y);
}



Window_stream& operator<<(Window_stream& os,
                          const pmmap &M)
{
   Halfedge_iterator it = M.halfedges_begin();

    while(it != M.halfedges_end()){
      os << (*it).curve();
      ++it;
    }

    return os;
}


Vertex
closest_vertex(const pmmap &M,
               const Point& p)
{
    Vertex v;
    Vertex_iterator vi = M.vertices_begin();
    if (vi==M.vertices_end()) 
      return v; //returns NULL if no vertices
    else v=(*vi);
    typename Rep::FT d  = CGAL_squared_distance(p, (*vi).point());

    for (; vi!=M.vertices_end(); ++vi)
    {
      typename Rep::FT d2 = CGAL_squared_distance(p, (*vi).point());
      if(d2 < d){
        d = d2;
        v = (*vi);
      }
    }
    return v;
    
}

void
window_input(pmmap & M,
             Window_stream &W )
{
    cerr << "1.Left button: edge from last vertex to current position"<< endl;
    cerr << "  at start - first vertex is set to current position"<< endl; 
    cerr << "2.Middle button: edge from last vertex to closest vertex from current position" << endl;
    cerr <<    "at start - first vertex is set to closest vertex from cirrent position" << endl;
    cerr << "3.Right button terminates input of points" << endl;

    Point p;
    Point first_point;
    Vertex last_vertex;

    bool start_flag = true;
    bool one_after_start = false;

    while(1) {
        double x, y;
        int b = W.get_mouse(x,y);
        bool button_pressed = (b == MOUSE_BUTTON(1)) ||
                              (b == MOUSE_BUTTON(2)) ||
                              (b == MOUSE_BUTTON(3));
        p = Point(coord_type(x),
                  coord_type(y));

        if(b == MOUSE_BUTTON(1))
          {
                if (start_flag)
                {
                  first_point=p;
                  start_flag=false;
                  one_after_start=true;
                 }
                 else
                 if (one_after_start)
                 {
                   one_after_start=false;
                   Halfedge e=M.insert(curve(first_point,p));
                   last_vertex=e.target();
                 }
                 else
                 {
                 Halfedge e=M.insert_from_vertex(curve(last_vertex.point(),p),
                                                 last_vertex,true);
                 last_vertex=e.target(); 
                                                
                 }

                W.clear();
                W << M;
          }
        
        else if(b == MOUSE_BUTTON(2))
          {
            Vertex v=closest_vertex(M,p);
            if (!start_flag)  // if at beginning do nothing
              {
                start_flag=true;
              
                if (one_after_start)  //insert fromfirst_point to nearest
                  {
                    M.insert(curve(first_point,v.point()));
                    one_after_start=false;
                  }
                else
                {
                  M.insert_at_vertices(curve(last_vertex.point(),v.point()),
                                       last_vertex,v);
                }
                
                
                if (M.is_valid())
                {
                  W.clear();
                  W << M;
                }
                else
                  cerr << "map not valid - operation canceled" << endl;
              }
            else  //want to start from existing vertex 
              {
                //                if (!v.is_null())
                if (M.number_of_vertices() > 0)
                  {
                    first_point=v.point(); 
                    start_flag=false;
                    one_after_start=true;
                  }
                //else -  no vertex exists do nothing
              }
          }
        else if(b == MOUSE_BUTTON(3))
          {
            // we are done
            break;
          }
        
    }
}



int
main(int argc, char* argv[])
{
       
  pmmap M;  

  Window_stream W(400, 400);
  
  double x0=-1.1,x1=1.1 ,y0=-1.1; 

  W.init(x0,x1,y0);   // logical window size 

  if (argc>1) 
    {
      Init(argv[1],M);
      win_border(x0,x1,y0,M); //rescale window 
      W.init(x0,x1,y0);      
    }
  else
    {

    W.set_show_coordinates(true);
    W << CGAL_GREEN;
    window_input(M,W);
    //    any_button(W);

    }

  draw_pm(M,W);

  return 0;
}























