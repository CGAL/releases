// fstream should appear first
//(otherwise ifstream is not added into the global std)
#include <fstream.h>
#include "draw_map.h"
#include "read_inp.h"


/*=========================================================================
 * Start of Code
\*=========================================================================*/


void MarkCcb (const Ccb_halfedge_circulator & b, list<Pm_curve>& l)
{
    Ccb_halfedge_circulator first = b, iter = b;
    do
    {
      l.push_back(iter->curve());
        iter++;
    }
    while (iter != first);
}



void draw_arrow (Pm_point p1, Pm_point p2, bool black , CGAL_Window_stream & W )
{
    if (black)
	W << CGAL_BLACK;
    else
	W << CGAL_WHITE;

    float ar_size=(W.xmax()-W.xmin())/20 ;

    W << Pm_curve (p1, p2);
    W << Pm_curve (p2, Pm_point (p2.x () - ar_size , p2.y () - ar_size));
    W << Pm_curve (p2, Pm_point (p2.x () + ar_size , p2.y () - ar_size));
}




void Draw (CGAL_Window_stream & W , Planar_map & pm )
{
    W.set_flush( 0 );
    
    Vertex_iterator vi;
    for (vi = pm.vertices_begin (); vi != pm.vertices_end (); vi++)
    {
                W << CGAL_GREEN;
                W << (*vi).point();
    }

    Halfedge_iterator ei;
    for (ei = pm.halfedges_begin (); ei != pm.halfedges_end (); ei++)
    {
      W << CGAL_BLUE;
      W << ((*ei).curve());
    }

    W.set_flush( 1 );
    W.flush();

}




bool VerticalRayShoot (Pm_point p, Pm_point & q, bool up , Planar_map &pm)
{
    Halfedge_handle e;
    Planar_map::Locate_type lt;
    number_type y_min, y_max, y_arrow_tip;

#ifdef CGAL_PM_TIMER
    t_vertical.start();
#endif
    e=pm.vertical_ray_shoot (p,lt, up);
#ifdef CGAL_PM_TIMER
    t_vertical.stop();
    n_vertical++;
#endif
    if (lt!=Planar_map::UNBOUNDED_FACE)
    {
      Pm_point p1 = e->source()->point();
      Pm_point p2 = e->target()->point();
      // make the arrow point upwards and touch the found segment:
      if (p1.x() == p2.x())
        {  
          // the found segment is vertical
          y_min = CGAL_min (p1.y(), p2.y());
          y_max = CGAL_max (p1.y(), p2.y());
          y_arrow_tip = (p.y() < y_min) ? y_min : y_max;
          q = Pm_point(p.x(), y_arrow_tip); 
        }
      else
        {
          y_arrow_tip = p2.y()-
            ((p2.x()-p.x())*(p2.y()-p1.y()))/(p2.x()-p1.x());
          q = Pm_point(p.x(), y_arrow_tip);
        }
      return true;
    }
    else
      {
        return false;
      }
    
}



void FindFace (const Pm_point& p , Planar_map &pm, list<Pm_curve>& l)
{
  Planar_map::Locate_type lt;
#ifdef CGAL_PM_TIMER
  t_vertical.start();
#endif
  Halfedge_handle e = pm.vertical_ray_shoot (p, lt, true);
#ifdef CGAL_PM_TIMER
  t_vertical.stop();
  n_vertical++;
#endif
  Face_handle f;
  
  if (lt!=Planar_map::UNBOUNDED_FACE)
    {
      f = e->face ();
    }
  else
    {
      f = pm.unbounded_face ();
    }
  
  Ccb_halfedge_circulator ccb_circ;
  
  if (f->does_outer_ccb_exist ())
    {
      ccb_circ = f->halfedge_on_outer_ccb()->ccb();  
      MarkCcb (ccb_circ,l);
    }
  
  Planar_map::Holes_iterator iccbit;
  for (iccbit = f->holes_begin (); iccbit != f->holes_end (); ++iccbit)
    {
      MarkCcb (*iccbit,l);
    }
  
}




int draw_pm (Planar_map & pm , CGAL_Window_stream & W)
{    

  list<Pm_curve> l;
  Pm_point pnt (20, 20);
  Pm_point ar1, ar2;
  int button = 0;
  double x, y;

  cerr << "Drawing the map:" << endl;
  Draw (W,pm);
  
  cerr << "1.Left button: vertical ray shooting." << endl;
  cerr << "2.Middle button: point location." << endl;
  cerr << "3.Right button: exit" << endl;
  
  while (button != 3)
    {
      int b=W.read_mouse(x,y);
      if (b==10) return 0;
      
      button = -b;
      pnt = Pm_point (x, y);
      
      draw_arrow (ar1, ar2, false,W);
      if (button == 1)
	{
          ar1 = pnt;
          if (VerticalRayShoot (ar1, ar2, true,pm))
            draw_arrow (ar1, ar2, true,W);
	}
      
      if (button == 2)
	{
          FindFace (pnt,pm,l);
	}
      
      if (button != 0)
	{
          Draw (W,pm);
          W << CGAL_RED;
          for (list<Pm_curve>::iterator lit=l.begin(); lit!=l.end(); ++lit)
            W << *lit;
          l.erase(l.begin(),l.end());
	}
    }
  
  
  return 0;
}


//-------------------------------------------------------------------
bool ReadFile(char *filename, int &num_points, Pm_point* &pnts, 
                             int &num_curves, Pm_curve* &cvs )
{
  int j, k;

  CGAL_STD_IO_ ifstream is(filename);
  if (is.bad()) return false;
  PM_input<Rep> inp;
  is >> inp;
  is.close();

  num_points = inp.get_num_pnts();
  num_curves = inp.get_num_cvs();
  pnts = new Pm_point[num_points];
  cvs = new Pm_curve[num_curves];

  int i;
  for(i = 0; i < num_points; i++)
  {
      inp.get(i, pnts[i]);
  }

  for(i = 0; i < inp.get_num_cvs(); i++)
  {
      inp.get(i, k, j);
      cvs[i] = Pm_curve(pnts[k], pnts[j]);
  }

  return true;
  
}
//----------------------------------------------------------------

void win_border( double &x0 , double &x1 , double &y0 ,Planar_map &pm)
{
  Vertex_iterator vit = pm.vertices_begin();
  x0=x1=CGAL_to_double(( (*vit).point() ).x());
  y0=CGAL_to_double(( (*vit).point() ).y());

  while (vit!=pm.vertices_end())
    {
      if ( ((*vit).point() ).x() < x0 )
        x0 = CGAL_to_double(( (*vit).point() ).x()) ;
      if ( ( (*vit).point() ).x() > x1 )
        x1 = CGAL_to_double(( (*vit).point() ).x()) ;
      if ( ( (*vit).point() ).y() < y0 )
        y0 = CGAL_to_double(( (*vit).point() ).y()) ;
      vit++;
    }

  x0=x0-(x1-x0)/2;
  x1=x1+(x1-x0)/2;

  y0=y0-(x1-x0)/4;
}

//DEBUG
//bool Init (char *filename , Planar_map & pm, CGAL_Window_stream& W)
bool Init (char *filename , Planar_map & pm)
{
    int num_points, num_curves, i;
    Pm_point *pnts;
    Pm_curve *cvs;

#ifdef CGAL_PM_TIMER
    t_construction.stop();// ReadFile shouldn't be included in construction time.
#endif
    if (!ReadFile (filename, num_points, pnts, num_curves, cvs ))
        return false;

#ifdef CGAL_PM_TIMER
    t_construction.start();
#endif

    for (i = 0; i < num_curves; i++)
    {
      //printf( "inserting curve: %d\n", i );
      //DEBUG
      //cout << cvs[i] << endl;
      //W << cvs[i] ;
#ifdef CGAL_PM_TIMER
      t_insert.start();
#endif
      Halfedge_handle  h=pm.insert (cvs[i]);
#ifdef CGAL_PM_TIMER
      t_insert.stop();
      n_insert++;
#endif
    }

    delete[]  cvs;
    delete[]  pnts;

    return true;

}

///////////////////////////////////////////////////////////////////////

CGAL_Window_stream& operator<<(CGAL_Window_stream& os,
                          Planar_map &M)
{
  Halfedge_iterator it = M.halfedges_begin();
  
  while(it != M.halfedges_end()){
    os << (*it).curve();
    ++it;
  }
	
  return os;
}


//function needed for window input
Vertex_handle closest_vertex(Planar_map &M, const Pm_point& p)
{
  Vertex_handle v;
  Vertex_iterator vi = M.vertices_begin();
  if (vi==M.vertices_end()) 
    return vi; 
  else v=vi;
  Rep::FT d  = CGAL_squared_distance(p, (*vi).point());
  
  for (; vi!=M.vertices_end(); ++vi)
    {
      Rep::FT d2 = CGAL_squared_distance(p, (*vi).point());
      if(d2 < d){
        d = d2;
        v = vi;
      }
    }
  return v;
  
} 



void window_input(Planar_map & M,
             CGAL_Window_stream &W )
{
  cerr << "1.Left button: start or end edge at mouse position."<< endl;
  cerr << "2.Middle button: start or end edge at closest vertex from mouse position" << endl;
  cerr << "3.Right button: remove the edge directly above the mouse position" << endl;

  Pm_point p;
  Pm_point first_point;
  Vertex_handle last_vertex;
	
  bool start_flag = true;
  
  while(1) {
    double x, y;
    int b = W.get_mouse(x,y);
    if (b==10) break;
    p = Pm_point(Rep::FT(x),
                 Rep::FT(y));

		
    if (b == MOUSE_BUTTON(1))
      {
        if (start_flag)
          {
            first_point=p;
            start_flag=false;
          }
        else 
          {
            start_flag=true;
#ifdef CGAL_PM_TIMER
            t_insert.start();
#endif
            Halfedge_handle e=M.insert(Pm_curve(first_point,p));
#ifdef CGAL_PM_TIMER
            t_insert.stop();
            n_insert++;
#endif
#ifdef CGAL_PM_DEBUG
            CGAL_postcondition(M.traits.point_is_same(e->source()->point(),first_point));
            CGAL_postcondition(M.traits.point_is_same(e->target()->point(),p));
#endif
          }

        W << M;
      }

    else
      if (b==MOUSE_BUTTON(2))
        {
          if (M.number_of_vertices()==0) { //an empty map do nothing
            start_flag=true;
          }
          else {  
          Vertex_handle v=closest_vertex(M,p);
          
          if (start_flag)  { 
            first_point=v->point();
            start_flag=false;
          }
          else //insert fromfirst_point to nearest
            {
#ifdef CGAL_PM_TIMER
              t_insert.start();
#endif
              Halfedge_handle e=M.insert(Pm_curve(first_point,v->point()));
#ifdef CGAL_PM_TIMER
              t_insert.stop();
              n_insert++;
#endif
#ifdef CGAL_PM_DEBUG
              CGAL_postcondition(M.traits.point_is_same(e->source()->point(),first_point));
              CGAL_postcondition(M.traits.point_is_same(e->target()->point(),v->point()));
#endif
              start_flag=true;
            }
          }

          W << M;
        }

      else if(b == MOUSE_BUTTON(3))
        {
          start_flag=true;
          Planar_map::Locate_type l;
          Halfedge_handle e;
#ifdef CGAL_PM_TIMER
          t_vertical.start();
#endif
          e=M.vertical_ray_shoot(p,l,true);
#ifdef CGAL_PM_TIMER
          t_vertical.stop();
          n_vertical++;
#endif
          if (l!=Planar_map::UNBOUNDED_FACE)
            {
#ifdef CGAL_PM_TIMER
              t_remove.start();
#endif
              M.remove_edge(e);
#ifdef CGAL_PM_TIMER
              t_remove.stop();
              n_remove++;
#endif
              W.clear();
              W << M;
              
#ifdef CGAL_PM_DEBUG
              cout << "\nremove()" << flush;
              M.debug();
#endif
            }
          
        }
    
    if (!M.is_valid()) {
      cerr << "map is not valid - aborting" << endl;
      exit(1);
    }

  }
        
}











