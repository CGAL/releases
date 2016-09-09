#include <CGAL/Cartesian.h>
#include <CGAL/Pm_segment_epsilon_traits.h>
#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Planar_map_2.h>

#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Circle_2.h>
#include <CGAL/Vector_2.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_2_algorithms.h>
#include<list>

#include <CGAL/geowin_support.h>
#include <CGAL/distance_predicates_2.h>

CGALPointlist L;
CGALSegmentlist Lseg;
CGALPointlist Loc;

typedef double                                          number_type;
typedef CGAL::Cartesian<number_type>                      coord_t;
typedef CGAL::Pm_segment_epsilon_traits<coord_t>          pmtraits;
typedef pmtraits::Point                                   point;
typedef pmtraits::X_curve                                 curve;
typedef CGAL::Pm_default_dcel<pmtraits>                   pmdcel;

typedef CGAL::Planar_map_2<pmdcel, pmtraits>	          planar_map;
typedef planar_map::Locate_type                           loc_type;


bool snap_to_points(CGALSegment& seg)
{
 if (L.size() < 2) return false;
 CGALPoint ps = seg.source();
 CGALPoint pt = seg.target();

 std::list<CGALPoint>::const_iterator it = L.begin();
 CGALPoint psnew=*it, ptnew=*it;

 for(; it != L.end(); ++it) {
  CGALPoint pakt= *it;
  if (CGAL::has_smaller_dist_to_point(ps,pakt,psnew)) psnew=pakt;
 }
 it=L.begin();
 for(; it != L.end(); ++it) {
  CGALPoint pakt= *it;
  if (CGAL::has_smaller_dist_to_point(pt,pakt,ptnew)) ptnew=pakt;
 }
 
 seg=CGALSegment(psnew,ptnew);
 if (seg.is_degenerate()) return false; 
 else return true;
}


bool segment_add_changer(GeoWin& gw, const CGALSegment& segold, CGALSegment& segnew)
{
 segnew=segold;
 bool b = snap_to_points(segnew);
 return b;
}

bool segment_start_change(GeoWin& gw, const CGALSegment& segold)
{ return false; }
bool point_start_change(GeoWin& gw, const CGALPoint& p)
{ return false; }


class geo_plmap : public geowin_redraw, public geowin_update<CGALSegmentlist, CGALPointlist >
{
public:

  CGALPolygonlist CPL;
  CGALPointlist  red;    //for location...
  CGALPointlist  green;
  CGALPointlist  white;

  virtual ~geo_plmap() {}

  virtual void draw(leda_window& W, leda_color c1, leda_color c2,double x1,double y1,double x2,double y2)
  {     
    CGALPolygonlist::const_iterator it = CPL.begin();
    int cnt = 0;
    for(; it != CPL.end(); ++it, cnt ++) {    
       W.set_fill_color(cnt % 7 + 6);
       CGALPolygon pol= *it;
       if (pol.is_simple()) W << convert_to_leda(pol); 
    }
    // output the lists for location ...
    std::list<CGALPoint>::const_iterator rt;

    W.set_color(leda_red);
    for (rt=red.begin(); rt != red.end(); rt++) W.draw_disc((*rt).x(),(*rt).y(),5);
    W.set_color(leda_green);
    for (rt=green.begin(); rt != green.end(); rt++) W.draw_disc((*rt).x(),(*rt).y(),5);
    W.set_color(leda_white);
    for (rt=white.begin(); rt != white.end(); rt++) W.draw_disc((*rt).x(),(*rt).y(),5);
  }
  
  virtual bool write_postscript(ps_file& PS, leda_color c1, leda_color c2)
  {     
    CGALPolygonlist::const_iterator it = CPL.begin();
    int cnt = 0;
    for(; it != CPL.end(); ++it, cnt ++) {    
       PS.set_fill_color(cnt % 7 + 6);
       CGALPolygon pol= *it;
       if (pol.is_simple()) PS << convert_to_leda(pol); 
    }
    // output the lists for location ...
    std::list<CGALPoint>::const_iterator rt;

    PS.set_color(leda_red);
    for (rt=red.begin(); rt != red.end(); rt++) PS.draw_disc((*rt).x(),(*rt).y(),5);
    PS.set_color(leda_green);
    for (rt=green.begin(); rt != green.end(); rt++) PS.draw_disc((*rt).x(),(*rt).y(),5);
    PS.set_color(leda_white);
    for (rt=white.begin(); rt != white.end(); rt++) PS.draw_disc((*rt).x(),(*rt).y(),5);
    return false;
  }


  virtual void update(const CGALSegmentlist& L, CGALPointlist&)
  {
     CPL.clear();
 
     CGAL::Planar_map_2<pmdcel, pmtraits> pm;    
     std::list<CGALSegment>::const_iterator it = L.begin();

     for(; it != L.end(); ++it) {
        CGALSegment sakt= *it;
        pm.insert(curve(sakt.source(),sakt.target()));
     }

     if (! pm.is_valid()) std::cout << "not a valid map!\n";

     int cnt = 0;
     CGAL::Planar_map_2<pmdcel, pmtraits>::Face_iterator fit= pm.faces_begin();
     for(; fit != pm.faces_end(); ++fit) {  
        CGAL::Planar_map_2<pmdcel, pmtraits>::Face fc = *fit;

        // now lets do something with the face ...
        if (! fc.is_unbounded()) {

           CGAL::Planar_map_2<pmdcel, pmtraits>::Halfedge_handle he, he_next;
           he= fc.halfedge_on_outer_ccb();
	   he_next = he;
	   std::list<CGALPoint> pcon;

	   do {
             point pt = (*he_next).source()->point();
             pcon.push_back(pt);
	     he_next = (*he_next).next_halfedge();
             
	   } while (he!=he_next);
           
           CGALPolygon poly(pcon.begin(), pcon.end());
           CPL.push_back(poly);
        }

        cnt++;
     }      

     green.clear(); red.clear(); white.clear();

     std::list<CGALPoint>::const_iterator loc_it = Loc.begin();
     loc_type lt;

     for(; loc_it != Loc.end(); ++loc_it) {
           pm.locate(*loc_it,lt);        
           if (lt==4) green.push_back(*loc_it);
           if (lt==3) red.push_back(*loc_it);
           if (lt==1 || lt==2) white.push_back(*loc_it);
     }  
  }
};


int main()
{
  geowin_init_default_type((CGALPointlist*)0, leda_string("CGALPointList"));
  geowin_init_default_type((CGALSegmentlist*)0, leda_string("CGALSegmentList"));
 
  GeoWin GW("CGAL - Planar map demo");
  GW.add_help_text(leda_string("Plmap"));

  geo_scene point_scene   = GW.new_scene(L);  
  GW.set_visible(point_scene,true);


  GeoEditScene<std::list<CGAL::Point_2<CGAL::Cartesian<double> > > >* PTR1 =
       (GeoEditScene<std::list<CGAL::Point_2<CGAL::Cartesian<double> > > >*)point_scene;

  GW.set_start_change_handler(PTR1, point_start_change);
 
  geo_scene segment_scene = GW.new_scene(Lseg); 
  GW.set_visible(segment_scene,true);

  GeoEditScene<std::list<CGAL::Segment_2<CGAL::Cartesian<double> > > >* PTR2 =
       (GeoEditScene<std::list<CGAL::Segment_2<CGAL::Cartesian<double> > > >*)segment_scene;

  GW.set_pre_add_change_handler(PTR2,segment_add_changer);
  GW.set_start_change_handler(PTR2,segment_start_change);

  // second point scene for locating ...
  
  geo_scene ploc_scene   = GW.new_scene(Loc);  
  GW.set_color(ploc_scene,leda_black);
  GW.set_visible(ploc_scene,true);
  

  geo_plmap PM;
 
  // Result Scene ...
  geo_scene sc1 = GW.new_scene( PM, PM, segment_scene, "Planar Map"); 
  GW.set_color(sc1, leda_blue);
  GW.set_visible(sc1,true);

  GW.add_dependence(ploc_scene,sc1);
  GW.edit(point_scene);
  
  return 0;  
}

