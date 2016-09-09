//#define USE_NAIVE_POINT_LOCATION  //for naive strategy
//#define USE_RATIONAL              //for rational coordinates
//#define CGAL_PM_DEBUG				// internal debug flag
//#define CGAL_PM_TIMER				// internal timing flag

#include <CGAL/basic.h>
#include <iostream.h>
#include <fstream.h>


#ifdef USE_NAIVE_POINT_LOCATION
#include <CGAL/Pm_naive_point_location.h>
#endif

#include "draw_map.h"  

typedef CGAL_Point_2<Rep>  Point;
typedef CGAL_Segment_2<Rep>  Segment;

typedef CGAL_Window_stream  Window_stream;


void redraw(leda_window* wp, double x0, double y0, double x1, double y1) 
{ wp->flush_buffer(x0,y0,x1,y1); }



#ifdef CGAL_PM_TIMER
CGAL_Timer t_total,t_construction,t_insert,t_remove,t_locate,t_vertical;
int n_total=0,n_insert=0,n_remove=0,n_locate=0,n_vertical=0;
#endif

int main(int argc, char* argv[])
{
#ifdef CGAL_PM_TIMER
	t_total.reset();
	t_total.start();
	t_construction.reset();
	t_insert.reset();
	t_remove.reset();
	t_locate.reset();
	t_vertical.reset();
#endif
	
#ifndef USE_NAIVE_POINT_LOCATION
	Planar_map M;
#else
	CGAL_Pm_naive_point_location<Planar_map> naive_pl;
	Planar_map M(&naive_pl);
#endif
	
	Window_stream W(400, 400);
	
	
	W.button("finish",10);
	W.set_redraw(redraw);
	double x0=-1.1,x1=1.1 ,y0=-1.1; 
	W.init(x0,x1,y0);   // logical window size 
	
	W.set_mode(leda_src_mode);
	W.set_node_width(3);
	W.display(leda_window::center,leda_window::center);
	
	if (argc>1) 
    {
#ifdef CGAL_PM_TIMER
		t_construction.start();
#endif
		if (!Init(argv[1],M)) {cerr << "\nBad input file";return 1;}
#ifdef CGAL_PM_TIMER
		t_construction.stop();
#endif
		win_border(x0,x1,y0,M); //rescale window 
                  W.init(x0,x1,y0);
		if (argc>2)
		{
			Planar_map::Locate_type lt;
			CGAL_STD_IO_ ifstream in(argv[2]);
			if (in.bad()) {cerr << "\nBad locate input file";return false;}
			int n; in >> n;
			while (n--) {
				double x,y;
				in >> x >> y ; 
				Point p(x,y);
#ifdef CGAL_PM_TIMER
				t_locate.start();
#endif
				M.locate(p,lt);
#ifdef CGAL_PM_TIMER
				t_locate.stop();
				n_locate++;
#endif
			}
			if (argc>3)
			{
				Planar_map::Locate_type lt;
				Planar_map::Halfedge_handle e;
				CGAL_STD_IO_ ifstream in(argv[3]);
				if (in.bad()) {cerr << "\nBad remove input file";return false;}
				int n; in >> n;
				while (n--) {
					double x,y;
					in >> x >> y ; 
					Point p(x,y);
#ifdef CGAL_PM_TIMER
					t_locate.start();
#endif
					e=M.locate(p,lt);
#ifdef CGAL_PM_TIMER
					t_locate.stop();
					n_locate++;
					t_remove.start();
#endif
					M.remove_edge(e);
#ifdef CGAL_PM_TIMER
					t_remove.stop();
					n_remove++;
#endif
				}
			}
        }
        else
			draw_pm(M,W);		
    }
	else
    {
		W << CGAL_GREEN;
		window_input(M,W);      
		Window_stream W2(400, 400);
		W2.init(x0,x1,y0); 
		W2.set_mode(leda_src_mode);
		W2.set_node_width(3);
		W2.button("quit",10);
		W2.display(leda_window::max,leda_window::center);
		draw_pm(M,W2);    
    }
#ifdef CGAL_PM_TIMER
	t_total.stop(); // currently t_total is not displayed
        if (argc>3)
          {
            cout << "\n" << t_construction.time() << " " << 
              t_insert.time()/n_insert << " " << 
              t_locate.time()/n_locate << " " << 
              t_remove.time()/n_remove << "\n";
          }
        else if (argc>2)
          {
            cout << "\n" << t_construction.time() << " " << 
              t_insert.time()/n_insert << " " << 
              t_locate.time()/n_locate << "\n";
          }
	else
	{
		cout << "\nTotal construction time: " << t_construction.time();
                if (n_insert) cout << "\ninsert average time: " << t_insert.time()/n_insert;
                if (n_remove) cout << "\nremove time: " << t_remove.time()/n_remove;
                if (n_locate) cout << "\nlocate average time: " << t_locate.time()/n_locate;
                if (n_vertical) cout << "\nvertical ray shoot time: " << t_vertical.time()/n_vertical;
	cout << endl;
        }
#endif
	return 0;
}




