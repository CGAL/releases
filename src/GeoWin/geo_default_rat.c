// ============================================================================
//
// Copyright (c) 2000 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       :
// release_date  :
//
// file          : src/GeoWin/geo_default_rat.c
// package       : GeoWin (1.1.9)
// revision      : 1.1.9
// revision_date : 27 September 2000 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken@informatik.uni-trier.de>)
// ============================================================================


#include <LEDA/geowin.h>
#include <LEDA/geowin_init.h>

GEOWIN_BEGIN_NAMESPACE

// post window default input handler ...

void d3_rat_point_window_handler(GeoWin& gw, d3_rat_point& p)
{
   double zv = gw.get_d3_z_value();
   p = d3_rat_point(p.xcoord(),p.ycoord(),rational(zv));
}

// edit functions

void edit_rat_gen_polygon(GeoWin& gw, rat_gen_polygon& gp, int i)
{
  list<rat_point> LP = gp.vertices();
  list<rat_segment> LS = gp.edges();

  window& w = gw.get_window();
  gw.message("Left button - delete vertex/insert vertex near edge, right - quit edit");  
  double d  = w.pix_to_real(1)*gw.get_mfct();
  int but;
  unsigned long t;
  double x,y;
  int event;
  
  do {
   do event = w.read_event(but, x, y, t);   
   while (event != button_release_event);

   double x1=x-d, x2=x+d, y1=y-d, y2=y+d;
   list_item iter,found=NULL;
   int cnt=0,number=0;
   
   if (but == MOUSE_BUTTON(1)){ // left ...
      forall_items(iter,LP){
        double xw = LP[iter].to_float().xcoord(), yw = LP[iter].to_float().ycoord();
        if ((xw>=x1) && (xw<=x2) && (yw>=y1) && (yw<=y2)) found=iter;
      }
      if (found != NULL) { // delete a vertex ...
         LP.del_item(found);
	 gp = rat_gen_polygon(LP);
	 LP = gp.vertices(); LS = gp.edges();
	 gw.get_active_scene()->update_and_redraw();
      }
      else {
       forall_items(iter,LS) {
        if (geowin_IntersectsBox(LS[iter],x1,y1,x2,y2,true)) { found=iter; number=cnt; }
	cnt++;
       }
       if (found != NULL) { // insert vertex ...
         list_item it = LP.get_item(number);
	 LP.insert(rat_point(point(x,y)),it);
	 gp = rat_gen_polygon(LP);
	 LP = gp.vertices(); LS = gp.edges();
	 gw.get_active_scene()->update_and_redraw();         
       }
      }
   }
  } while (but != MOUSE_BUTTON(3));
  
  gw.message("");
}


void edit_rat_polygon(GeoWin& gw, rat_polygon& gp, int i)
{
  list<rat_point> LP = gp.vertices();
  list<rat_segment> LS = gp.edges();

  window& w = gw.get_window();
  gw.message("Left button - delete vertex/insert vertex near edge, right - quit edit");
  double d  = w.pix_to_real(1)*gw.get_mfct();
  int but;
  unsigned long t;
  double x,y;
  int event;
  
  do {
   do event = w.read_event(but, x, y, t);   
   while (event != button_release_event);

   double x1=x-d, x2=x+d, y1=y-d, y2=y+d;
   list_item iter,found=NULL;
   int cnt=0,number=0;

   if (but == MOUSE_BUTTON(1)){ // left ...
      forall_items(iter,LP){
        double xw = LP[iter].to_float().xcoord(), yw = LP[iter].to_float().ycoord();
        if ((xw>=x1) && (xw<=x2) && (yw>=y1) && (yw<=y2)) found=iter;
      }
      if (found != NULL) { // delete a vertex ...
         LP.del_item(found);
	 gp = rat_polygon(LP);
	 LP = gp.vertices(); LS = gp.edges();
	 gw.get_active_scene()->update_and_redraw();
      }
      else {
       forall_items(iter,LS) {
        if (geowin_IntersectsBox(LS[iter],x1,y1,x2,y2,true)) { found=iter; number=cnt; }
	cnt++;
       }
       if (found != NULL) { // insert vertex ...
         list_item it = LP.get_item(number);
	 LP.insert(rat_point(point(x,y)),it);
	 gp = rat_polygon(LP);
	 LP = gp.vertices(); LS = gp.edges();
	 gw.get_active_scene()->update_and_redraw();         
       }
      }
   }
  } while (but != MOUSE_BUTTON(3));
  
  gw.message("");
}


void insert_new_rat_segment_scene(GeoWin& gw, const list<rat_segment>& LPol)
{
 if (gw.get_algo_create_scenes()) {
  geo_scene sc = GeoScene::new_scene(string("RationalSegments"));
  gw.insert_scene(sc);
  ((GeoEditScene<list<rat_segment> >*)sc)->set_objects(LPol);
  gw.init_and_set_visible(sc);
 }
}

void insert_new_rat_circle_scene(GeoWin& gw, const list<rat_circle>& LPol)
{
 if (gw.get_algo_create_scenes()) {
  geo_scene sc = GeoScene::new_scene(string("RationalCircles"));
  gw.insert_scene(sc);
  ((GeoEditScene<list<rat_circle> >*)sc)->set_objects(LPol);
  gw.init_and_set_visible(sc);
 } 
}

/*
void insert_new_rat_gen_polygon_scene(GeoWin& gw, const list<rat_gen_polygon>& LPol)
{
 if (gw.get_algo_create_scenes()) {
  geo_scene sc = GeoScene::new_scene(string("RationalGeneralizedPolygons"));
  gw.insert_scene(sc);
  ((GeoEditScene<list<rat_gen_polygon> >*)sc)->set_objects(LPol);
  gw.init_and_set_visible(sc);
 } 
}*/

// get defining points functions ...
void rat_segment_defining_points(const rat_segment& s, list<point>& lp)
{ lp.append(s.source().to_float()); lp.append(s.target().to_float()); }

void rat_circle_defining_points(const rat_circle& c, list<point>& lp)
{ lp.append(c.point1().to_float()); lp.append(c.point2().to_float()); lp.append(c.point3().to_float()); }

void rat_ray_defining_points(const rat_ray& r, list<point>& lp)
{ lp.append(r.point1().to_float()); lp.append(r.point2().to_float()); }

void rat_line_defining_points(const rat_line& l, list<point>& lp)
{ lp.append(l.point1().to_float()); lp.append(l.point2().to_float()); }

void rat_polygon_defining_points(const rat_polygon& p, list<point>& lp)
{ list<rat_point> lpr=p.vertices(); 
  rat_point iter;
  forall(iter,lpr){ lp.append(iter.to_float()); }
}

void rat_gen_polygon_defining_points(const rat_gen_polygon& gp, list<point>& lp)
{ list<rat_point> lpr=gp.vertices(); 
  rat_point iter;
  forall(iter,lpr){ lp.append(iter.to_float()); }
}

// algorithms ...
void chull_rat(GeoWin& gw, list<rat_point>& L);
void triang_rat(GeoWin& gw, list<rat_point>& L);
void width_rat(GeoWin& gw, list<rat_point>& L);
void dt_rat(GeoWin& gw, list<rat_point>& L);
void f_dt_rat(GeoWin& gw, list<rat_point>& L);
void mst_rat(GeoWin& gw, list<rat_point>& L);
void lec_rat(GeoWin& gw, list<rat_point>& L);
void sec_rat(GeoWin& gw, list<rat_point>& L);
void all_empty_rat(GeoWin& gw, list<rat_point>& L);
void all_encl_rat(GeoWin& gw, list<rat_point>& L);
void point_fcn_two_rat(GeoWin& gw, list<rat_point>& L);
void point_fcn_three_rat(GeoWin& gw, list<rat_point>& L);
void point_fcn_four_rat(GeoWin& gw, list<rat_point>& L);
void seg_inter_rat(GeoWin& gw, list<rat_segment>& L);
//void check_gen_pol_rat(GeoWin& gw, list<rat_gen_polygon>& L);
//void union_gen_pol_rat(GeoWin& gw, list<rat_gen_polygon>& L);
//void inter_gen_pol_rat(GeoWin& gw, list<rat_gen_polygon>& L);

// input functions

void rat_segment_points( list<rat_point>& L, rat_segment s, int n);

void circle_points(list<rat_point>& L, circle C, int n);

class alt_input_segment_rat : public GeoInputObject<rat_point> {
int pt_number;
public:
 alt_input_segment_rat() { pt_number=20; }

 virtual void operator()(GeoWin& gw, list<rat_point>& LPR)
 {
  window& w = gw.get_window();
  rat_segment s;
  w >> s;
  rat_segment_points(LPR,s,pt_number); 
 }
 
 virtual void options(GeoWin& gw) 
 {
   panel P;
   P.text_item("\\bf\\blue Number of points on segment:");
   P.int_item("number", pt_number, 10, 200);
   P.button(" DONE ", 0);
   gw.open_panel(P);
 }
};

class alt_input_d3_rat_point : public GeoInputObject<d3_rat_point>
{
 void operator()(GeoWin& gw, list<d3_rat_point>& LP)
 {
  window& w = gw.get_window();
  rat_point p;
  w >> p;
  double x0 = p.to_float().xcoord();
  double y0 = p.to_float().ycoord();
  double x1, y1;
  w.read_mouse_seg(x0, y0, x1, y1);
  
  LP.append(d3_rat_point(p.xcoord(),rational(y1),rational(x1-x0)));
 }
};

class alt_input_circle_rat : public GeoInputObject<rat_point> {
int pt_number;
public:
 alt_input_circle_rat() { pt_number=20; }

 virtual void operator()(GeoWin& gw, list<rat_point>& LP)
 {
  window& w = gw.get_window();
  circle c;
  w >> c;
  circle_points(LP,c,pt_number); 
 }

 virtual void options(GeoWin& gw) 
 {
   panel P;
   P.text_item("\\bf\\blue Number of points on circle:"); 
   P.int_item("number", pt_number, 10, 200);
   P.button(" DONE ", 0);
   gw.open_panel(P);
 }
};

class alt_input_poly_rat : public GeoInputObject<rat_gen_polygon> {
public:
 virtual void operator()(GeoWin& gw, list<rat_gen_polygon>& LG)
 {
  window& w = gw.get_window();
  gw.message("Middle mouse button - abort gen_polygon input");
  
  rat_polygon in;
  rat_gen_polygon GP;

  int but;
  unsigned long t;
  double x,y;
  int event;
  
  do {
    event = w.read_event(but, x, y, t);
   
   if (but != MOUSE_BUTTON(2)) {
    w >> in; w << in;
    if (! in.empty() || in.orientation()==0) {
       if (in.orientation()==1) GP = GP.unite(rat_gen_polygon(in));
       else GP = GP.diff(rat_gen_polygon(in.complement()));
    }
   }
  } while (but != MOUSE_BUTTON(2));

  gw.message("");  
  if (! GP.empty())  LG.append(GP);
 }
};

static alt_input_segment_rat altseg_rat;
static alt_input_circle_rat  altcirc_rat;
static alt_input_poly_rat    altpoly_rat;
static alt_input_d3_rat_point altd3point_rat;

// ----------------------------------------------
// d3 output functions ...
// ----------------------------------------------

void rat_points_d3(const list<rat_point>& L,d3_window& W, GRAPH<d3_point,int>& H)
{
 GRAPH<d3_point,int> G;
 rat_point iter;
 forall(iter,L) G.new_node(d3_point(iter.to_float().xcoord(),iter.to_float().ycoord(),0));
 H.join(G);
}

void d3_rat_points_d3(const list<d3_rat_point>& L,d3_window& W, GRAPH<d3_point,int>& H)
{
 GRAPH<d3_point,int> G;
 d3_rat_point iter;
 forall(iter,L) G.new_node(iter.to_float());
 H.join(G);
}

void rat_segments_d3(const list<rat_segment>& L,d3_window& W, GRAPH<d3_point,int>& H)
{
 GRAPH<d3_point,int> G;
 rat_segment iter;
 forall(iter,L) {
   node v1 = G.new_node(d3_point(iter.source().to_float().xcoord(),iter.source().to_float().ycoord(),0));
   node v2 = G.new_node(d3_point(iter.target().to_float().xcoord(),iter.target().to_float().ycoord(),0));   
   edge e1 = G.new_edge(v1,v2);
   edge e2 = G.new_edge(v2,v1);
   G.set_reversal(e1,e2);
 }
 H.join(G);
}

void circle_segments(list<segment>&, circle, int);

void rat_circles_d3(const list<rat_circle>& L,d3_window& W, GRAPH<d3_point,int>& H)
{
 list<segment> LS;
 list<rat_segment> LSR;
 rat_circle C;
 forall(C,L) {
  LS.clear(); LSR.clear();
  circle_segments(LS,C.to_float(),30);
  segment iter;
  forall(iter,LS) LSR.append(rat_segment(iter));
  rat_segments_d3(LSR,W,H);
 }
}

void rat_lines_d3(const list<rat_line>& L,d3_window& W, GRAPH<d3_point,int>& H)
{
 GRAPH<d3_point,int> G;
 rat_line r_iter;
 forall(r_iter,L) {
   line iter = r_iter.to_float();
   point pm((iter.point1().xcoord()+iter.point2().xcoord())/2,(iter.point1().ycoord()+iter.point2().ycoord())/2);
   vector v = iter.point1() - iter.point2();
   v= v * 100;
   point p1=pm+v, p2=pm-v;
   node v1 = G.new_node(d3_point(p1.xcoord(),p1.ycoord(),0));
   node v2 = G.new_node(d3_point(p2.xcoord(),p2.ycoord(),0));   
   edge e1 = G.new_edge(v1,v2);
   edge e2 = G.new_edge(v2,v1);
   G.set_reversal(e1,e2);   
 }
 H.join(G);
}

void rat_rays_d3(const list<rat_ray>& L,d3_window& W, GRAPH<d3_point,int>& H)
{
 GRAPH<d3_point,int> G;
 rat_ray r_iter;
 forall(r_iter,L) {
   ray iter = r_iter.to_float();
   vector v = iter.point2() - iter.point1();
   v= v * 100;
   point p1=iter.source(), p2=p1 + v;
   node v1 = G.new_node(d3_point(p1.xcoord(),p1.ycoord(),0));
   node v2 = G.new_node(d3_point(p2.xcoord(),p2.ycoord(),0));   
   edge e1 = G.new_edge(v1,v2);
   edge e2 = G.new_edge(v2,v1);
   G.set_reversal(e1,e2);   
 } 
 H.join(G);
}

void rat_poly_d3(const list<rat_polygon>& L,d3_window& W, GRAPH<d3_point,int>& H)
{
 GRAPH<d3_point,int> G;
 rat_polygon piter;
 list<rat_segment> LS;
 forall(piter,L) {
   LS = piter.segments();
   rat_segment siter;
   forall(siter,LS) {
    node v1 = G.new_node(d3_point(siter.source().to_float().xcoord(),siter.source().to_float().ycoord(),0));
    node v2 = G.new_node(d3_point(siter.target().to_float().xcoord(),siter.target().to_float().ycoord(),0));   
    edge e1 = G.new_edge(v1,v2);
    edge e2 = G.new_edge(v2,v1);
    G.set_reversal(e1,e2);
   }   
 }
 H.join(G); 
}

void rat_gen_poly_d3(const list<rat_gen_polygon>& L,d3_window& W, GRAPH<d3_point,int>& H)
{
 GRAPH<d3_point,int> G;
 rat_gen_polygon piter;
 list<rat_segment> LS;
 forall(piter,L) {
   LS = piter.edges();
   rat_segment siter;
   forall(siter,LS) {
    node v1 = G.new_node(d3_point(siter.source().to_float().xcoord(),siter.source().to_float().ycoord(),0));
    node v2 = G.new_node(d3_point(siter.target().to_float().xcoord(),siter.target().to_float().ycoord(),0));   
    edge e1 = G.new_edge(v1,v2);
    edge e2 = G.new_edge(v2,v1);
    G.set_reversal(e1,e2);
   }   
 }
 H.join(G); 
}

window& d3_rat_point_draw(window& w, const d3_rat_point& p,int val)
{
  //cout << val << "\n";
  val = GeoWin::get_projection_mode();
  
  switch(val){
    case 0:  //xy
    { w << rat_point(p.xcoord(),p.ycoord()); break; }
    case 1:  //xz
    { w << rat_point(p.xcoord(),p.zcoord()); break; }    
    case 2:  //yz
    { w << rat_point(p.ycoord(),p.zcoord()); break; }
  }
  return w;
}

#if defined(__KCC)

typedef void (*POINT_D3)(const list<rat_point>&, d3_window&, GRAPH<d3_point,int>&);
typedef void (*SEGMENT_D3)(const list<rat_segment>&, d3_window&, GRAPH<d3_point,int>&);
typedef void (*RAY_D3)(const list<rat_ray>&, d3_window&, GRAPH<d3_point,int>&);
typedef void (*LINE_D3)(const list<rat_line>&, d3_window&, GRAPH<d3_point,int>&);
typedef void (*CIRCLE_D3)(const list<rat_circle>&, d3_window&, GRAPH<d3_point,int>&);
typedef void (*POLYGON_D3)(const list<rat_polygon>&, d3_window&, GRAPH<d3_point,int>&);
typedef void (*GENPOLYGON_D3)(const list<rat_gen_polygon>&, d3_window&, GRAPH<d3_point,int>&);
typedef void (*D3POINT_D3)(const list<d3_rat_point>&, d3_window&, GRAPH<d3_point,int>&);

template class GeoEditScene<list<rat_point> >;
template class GeoBaseScene<list<rat_point> >;
template string geowin_info_fcn(const list<rat_point>&);
template GeoEditScene<list<rat_point> >* make_edit_prototype(list<rat_point>*, string);
template GeoBaseScene<list<rat_point> >* make_base_prototype(list<rat_point>*, string);
template GeoEditScene<list<rat_point> >* geowin_init_default_type(list<rat_point>*, string, POINT_D3); 

template class GeoEditScene<list<rat_segment> >;
template class GeoBaseScene<list<rat_segment> >;
template string geowin_info_fcn(const list<rat_segment>&);
template GeoEditScene<list<rat_segment> >* make_edit_prototype(list<rat_segment>*, string);
template GeoBaseScene<list<rat_segment> >* make_base_prototype(list<rat_segment>*, string);
template GeoEditScene<list<rat_segment> >* geowin_init_default_type(list<rat_segment>*, string, SEGMENT_D3); 

template class GeoEditScene<list<rat_line> >;
template class GeoBaseScene<list<rat_line> >;
template string geowin_info_fcn(const list<rat_line>&);
template GeoEditScene<list<rat_line> >* make_edit_prototype(list<rat_line>*, string);
template GeoBaseScene<list<rat_line> >* make_base_prototype(list<rat_line>*, string);
template GeoEditScene<list<rat_line> >* geowin_init_default_type(list<rat_line>*, string, LINE_D3); 

template class GeoEditScene<list<rat_circle> >;
template class GeoBaseScene<list<rat_circle> >;
template string geowin_info_fcn(const list<rat_circle>&);
template GeoEditScene<list<rat_circle> >* make_edit_prototype(list<rat_circle>*, string);
template GeoBaseScene<list<rat_circle> >* make_base_prototype(list<rat_circle>*, string);
template GeoEditScene<list<rat_circle> >* geowin_init_default_type(list<rat_circle>*, string, CIRCLE_D3); 

template class GeoEditScene<list<rat_polygon> >;
template class GeoBaseScene<list<rat_polygon> >;
template string geowin_info_fcn(const list<rat_polygon>&);
template GeoEditScene<list<rat_polygon> >* make_edit_prototype(list<rat_polygon>*, string);
template GeoBaseScene<list<rat_polygon> >* make_base_prototype(list<rat_polygon>*, string);
template GeoEditScene<list<rat_polygon> >* geowin_init_default_type(list<rat_polygon>*, string, POLYGON_D3); 

template class GeoEditScene<list<rat_gen_polygon> >;
template class GeoBaseScene<list<rat_gen_polygon> >;
template string geowin_info_fcn(const list<rat_gen_polygon>&);
template GeoEditScene<list<rat_gen_polygon> >* make_edit_prototype(list<rat_gen_polygon>*, string);
template GeoBaseScene<list<rat_gen_polygon> >* make_base_prototype(list<rat_gen_polygon>*, string);
template GeoEditScene<list<rat_gen_polygon> >* geowin_init_default_type(list<rat_gen_polygon>*, string, GENPOLYGON_D3); 

template class GeoEditScene<list<d3_rat_point> >;
template class GeoBaseScene<list<d3_rat_point> >;
template string geowin_info_fcn(const list<d3_rat_point>&);
template GeoEditScene<list<d3_rat_point> >* make_edit_prototype(list<d3_rat_point>*, string);
template GeoBaseScene<list<d3_rat_point> >* make_base_prototype(list<d3_rat_point>*, string);
template GeoEditScene<list<d3_rat_point> >* geowin_init_default_type(list<d3_rat_point>*, string, D3POINT_D3); 

#endif

void init_leda_rat_default_types()
{
#if defined INIT_GEOWIN_LEDA_DEFAULT_TYPES

  GeoEditScene<list<rat_point> >* esc = geowin_init_default_type((list<rat_point>*)0, string("RationalPoints"), rat_points_d3);
  esc->add_alternative_input_object(altseg_rat, string("Segments"));
  esc->add_alternative_input_object(altcirc_rat, string("Circles"));    
  esc->add_buffer_fcn(chull_rat, "Convex hull");
  esc->add_buffer_fcn(triang_rat, "Triangulation");
  esc->add_buffer_fcn(width_rat, "Width");
  esc->add_buffer_fcn(dt_rat, "Delaunay triangulation");
  esc->add_buffer_fcn(f_dt_rat, "Furthest point DT");
  esc->add_buffer_fcn(mst_rat, "MST");
  esc->add_buffer_fcn(lec_rat, "Largest empty circle");
  esc->add_buffer_fcn(sec_rat, "Smallest enclosing circle");
  esc->add_buffer_fcn(all_empty_rat, "All empty circles");
  esc->add_buffer_fcn(all_encl_rat, "All enclosing circles");
  esc->add_buffer_fcn(point_fcn_two_rat, "Check (2)");
  esc->add_buffer_fcn(point_fcn_three_rat, "Check (3)");
  esc->add_buffer_fcn(point_fcn_four_rat, "Check (4)");  
   
  GeoEditScene<list<rat_segment> >* esc2 = geowin_init_default_type((list<rat_segment>*)0, string("RationalSegments"), rat_segments_d3);
  esc2->set_defining_points_fcn(rat_segment_defining_points);
  esc2->move_point_fcn = geowin_Translatepoint;
  esc2->add_buffer_fcn(seg_inter_rat, "Segment intersection");  

/*     
  GeoEditScene<list<rat_ray> >* esc3 = geowin_init_default_type((list<rat_ray>*)0,     string("RationalRays"), rat_rays_d3);
  esc3->set_defining_points_fcn(rat_ray_defining_points);
  esc3->move_point_fcn = geowin_Translatepoint;
*/
   
  GeoEditScene<list<rat_line> >* esc4 = geowin_init_default_type((list<rat_line>*)0,    string("RationalLines"), rat_lines_d3);
  esc4->set_defining_points_fcn(rat_line_defining_points);
  esc4->move_point_fcn = geowin_Translatepoint;
   
  GeoEditScene<list<rat_circle> >* esc5 = geowin_init_default_type((list<rat_circle>*)0,  string("RationalCircles"), rat_circles_d3);
  esc5->set_defining_points_fcn(rat_circle_defining_points);
  esc5->move_point_fcn = geowin_Translatepoint;
  
  GeoEditScene<list<rat_polygon> >* esc6 = geowin_init_default_type((list<rat_polygon>*)0, string("RationalSimplePolygons"), rat_poly_d3);
  esc6->set_defining_points_fcn(rat_polygon_defining_points);
  esc6->move_point_fcn = geowin_Translatepoint;
  esc6->edit_obj_fcn=edit_rat_polygon;
   
  GeoEditScene<list<rat_gen_polygon> >* esc7 =geowin_init_default_type((list<rat_gen_polygon>*)0, \
  string("RationalGeneralizedPolygons"),rat_gen_poly_d3);
  esc7->add_alternative_input_object(altpoly_rat, string("Construction")); 
  esc7->set_defining_points_fcn(rat_gen_polygon_defining_points);
  esc7->move_point_fcn = geowin_Translatepoint;
  //esc7->add_buffer_fcn(check_gen_pol_rat, string("Check (1)"));
  //esc7->add_buffer_fcn(union_gen_pol_rat, string("Union (2)"));
  //esc7->add_buffer_fcn(inter_gen_pol_rat, string("Intersection (2)"));  
  esc7->edit_obj_fcn=edit_rat_gen_polygon;  
  
#if defined LEDA_RECTANGLES
  geowin_init_default_type((list<rat_rectangle>*)0,   string("RationalRectangles"));
#endif

  GeoEditScene<list<d3_rat_point> >* esc8 = geowin_init_default_type((list<d3_rat_point>*)0, \
  string("D3-RationalPoints"),d3_rat_points_d3);
  esc8->add_alternative_input_object(altd3point_rat,  string("xyz - Input"));
  esc8->draw_fcn = d3_rat_point_draw;  
  esc8->post_window_default_input_handler = d3_rat_point_window_handler;
  
#endif
}

GEOWIN_END_NAMESPACE


