#include "draw_map.h"
#include <fstream.h>
#include "read_inp.h"


/*=========================================================================
 * Start of Code
\*=========================================================================*/

//enumerates the map info  (needed for coloring could be done differently)
void enumerate_all (pmmap &pm)
{
    int k;
    typename pmmap::Vertex_iterator vi;
    typename pmmap::Face_iterator fi;
    typename pmmap::Halfedge_iterator ei;
    
    for (k = 0, vi = pm.vertices_begin (); vi != pm.vertices_end (); vi++, k++)
        (*vi).set_info (k);

    for (k = 0, fi = pm.faces_begin (); fi != pm.faces_end (); fi++, k++)
        (*fi).set_info (k);

    for (k = 0, ei = pm.halfedges_begin (); ei != pm.halfedges_end (); ei++, k++)
        (*ei).set_info (k);
}



void MarkCcb (const pmccbcirc & b)
{
    pmccbcirc first = b, iter = b;
    int j;

    do
    {
        j = (*iter).info () | 0x00010000;
        (*iter).set_info (j);
        iter++;
    }
    while (iter != first);
}



void draw_arrow (pmpoint p1, pmpoint p2, bool black , CGAL_Window_stream & W )
{
    if (black)
	W << CGAL_BLACK;
    else
	W << CGAL_WHITE;

    float ar_size=(W.xmax()-W.xmin())/20 ;

    W << pmcurve (p1, p2);
    W << pmcurve (p2, pmpoint (p2.x () - ar_size , p2.y () - ar_size));
    W << pmcurve (p2, pmpoint (p2.x () + ar_size , p2.y () - ar_size));
}




void Draw (CGAL_Window_stream & W , pmmap & pm )
{
    W.set_flush( 0 );
    
    //printf( "displaying vertices\n" );
    typename pmmap::Vertex_iterator vi;
    for (vi = pm.vertices_begin (); vi != pm.vertices_end (); vi++)
    {
                W << CGAL_GREEN;
                W << (*vi).point();
    }

    //printf( "displaying curves\n" );
    typename pmmap::Halfedge_iterator ei;
    for (ei = pm.halfedges_begin (); ei != pm.halfedges_end (); ei++)
    {
                if ((((*ei).info () & 0xffff0000) != 0) ||
                        (((*ei).twin ().info () & 0xffff0000) != 0))
                        W << CGAL_RED;
                else
                        W << CGAL_BLUE;

                W << ((*ei).curve());

    }

    //printf( "flushing\n" );

    W.set_flush( 1 );
    W.flush();

    //printf( "done\n" );
}




bool VerticalRayShoot (pmpoint p, pmpoint & q, bool up , pmmap &pm)
{
    pmedge e;
    typename pmmap::Locate_type lt;
    number_type y_min, y_max, y_arrow_tip;

    e=pm.vertical_ray_shoot (p,lt, up);
    //    if (!e.is_null())
    if (lt!=pmmap::UNBOUNDED_FACE)
    {
                pmpoint p1 = e.source().point();
                pmpoint p2 = e.target().point();
                // make the arrow point upwards and touch the found segment:
                if (p1.x() == p2.x())
                {  
                  // the found segment is vertical
                  y_min = min (p1.y(), p2.y());
                  y_max = max (p1.y(), p2.y());
                  y_arrow_tip = (p.y() < y_min) ? y_min : y_max;
                  q = pmpoint(p.x(), y_arrow_tip); 
                }
                else
                {
                  y_arrow_tip = p2.y()-
                              ((p2.x()-p.x())*(p2.y()-p1.y()))/(p2.x()-p1.x());
                  q = pmpoint(p.x(), y_arrow_tip);
                }
                return true;
    }
    else
    {
                return false;
    }

}



int FindFace (pmpoint point , pmmap &pm)
{
    pmpoint p (point.x (), point.y ());
    typename pmmap::Locate_type lt;
    pmedge e = pm.vertical_ray_shoot (p, lt, true);
    pmface f;
    //CString s;
    
        
    //    if (!e.is_null())
    if (lt!=pmmap::UNBOUNDED_FACE)
    {
                f = e.face ();
    }
    else
    {
                f = pm.unbounded_face ();
    }
        
    pmccbcirc ccb_circ;
        
    if (f.is_outer_ccb_exist ())
    {
      ccb_circ = f.halfedge_on_outer_ccb().ccb();  //maybe outer_ccb() ?
                MarkCcb (ccb_circ);
    }
        
    typename pmmap::Holes_iterator iccbit;
    for (iccbit = f.holes_begin (); iccbit != f.holes_end (); iccbit++)
    {
                MarkCcb (*iccbit);
    }
        
    return (f.info () & 0x0000ffff);
}




int draw_pm (pmmap & pm , CGAL_Window_stream & W)
{    


    pmpoint pnt (20, 20);
    pmpoint ar1, ar2;
    int button = 0;
    double x, y;

    cout << "Drawing the map:" << endl;
    Draw (W,pm);

    cout << "1.Click left mouse button for vertical ray shooting." << endl;
    cout << "  the arrow will point to the middle of the edge." << endl;
    cout << "2.Middle mouse button for point location." << endl;
    cout << "3.Right mouse button to exit" << endl;

    while (button != 3)
    {
	button = -1 * W.read_mouse (x, y);
	pnt = pmpoint (x, y);

	draw_arrow (ar1, ar2, false,W);
	if (button == 1)
	{
	    ar1 = pnt;
	    if (VerticalRayShoot (ar1, ar2, true,pm))
		draw_arrow (ar1, ar2, true,W);
	    enumerate_all (pm);
	}

	if (button == 2)
	{
	    enumerate_all (pm);
	    FindFace (pnt,pm);
	}

	if (button != 0)
	{
	    Draw (W,pm);
	}
    }


    return 0;
}


//-------------------------------------------------------------------

bool ReadFile(char *filename, int &num_points, pmpoint* &pnts, 
                             int &num_curves, pmcurve* &cvs )
{
  int j, k;

  ifstream is(filename);
  PM_input<coord_t> inp;
  is >> inp;
  is.close();

  num_points = inp.get_num_pnts();
  num_curves = inp.get_num_cvs();
  pnts = new pmpoint[num_points];
  cvs = new pmcurve[num_curves];

  int i;
  for(i = 0; i < num_points; i++)
  {
      inp.get(i, pnts[i]);
  }

  for(i = 0; i < inp.get_num_cvs(); i++)
  {
      inp.get(i, k, j);
      cvs[i] = pmcurve(pnts[k], pnts[j]);
  }

  return true;
  
}

//----------------------------------------------------------------

void win_border( double &x0 , double &x1 , double &y0 ,const pmmap &pm)
{
  typename pmmap::Vertex_iterator vit = pm.vertices_begin();
  x0=x1=( (*vit).point() ).x();
  y0=( (*vit).point() ).y();

  while (vit!=pm.vertices_end())
    {
      if ( ((*vit).point() ).x() < x0 )
        x0 = ( (*vit).point() ).x() ;
      if ( ( (*vit).point() ).x() > x1 )
        x1 = ( (*vit).point() ).x() ;
      if ( ( (*vit).point() ).y() < y0 )
        y0 = ( (*vit).point() ).y() ;
      vit++;
    }

  //  x0=x0-1;
  x0=x0-(x1-x0)/4;
  //x1=x1+1;
  x1=x1+(x1-x0)/4;

  y0=y0-(x1-x0)/4;
}




bool Init (char *filename , pmmap & pm)
{
    int num_points, num_curves, i;
    pmpoint *pnts;
    pmcurve *cvs;


    if (!ReadFile (filename, num_points, pnts, num_curves, cvs ))
        return false;

    for (i = 0; i < num_curves; i++)
    {
      //        printf( "inserting curve: %d\n", i );
      pm.insert (cvs[i]);
    }

    delete[]  cvs;
    delete[]  pnts;

    enumerate_all (pm);

    return true;

}











