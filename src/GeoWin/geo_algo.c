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
// file          : src/GeoWin/geo_algo.c
// package       : GeoWin (1.1.9)
// revision      : 1.1.9
// revision_date : 27 September 2000 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken@informatik.uni-trier.de>)
// ============================================================================

#include <LEDA/geowin.h>
#include <LEDA/rat_geo_alg.h>
#include <LEDA/float_geo_alg.h>

GEOWIN_BEGIN_NAMESPACE

void insert_new_segment_scene(GeoWin& gw, const list<segment>& LPol);
void insert_new_rat_segment_scene(GeoWin& gw, const list<rat_segment>& LPol);
void insert_new_circle_scene(GeoWin& gw, const list<circle>& LPol);
void insert_new_rat_circle_scene(GeoWin& gw, const list<rat_circle>& LPol);

//void insert_new_gen_polygon_scene(GeoWin& gw, const list<gen_polygon>& LPol);
//void insert_new_rat_gen_polygon_scene(GeoWin& gw, const list<rat_gen_polygon>& LPol);


// Convex Hulls 
void chull_float(GeoWin& gw, list<point>& L)
{
  list<point> Pl = CONVEX_HULL(L);
  list<segment> Lseg;
  list_item it, prev, fst;
  
  prev = Pl.first();
  fst = prev;
  if (prev != NULL) {
    it = Pl.succ(prev);
    while (it != NULL){
      Lseg.append(segment(Pl[prev],Pl[it]));
      prev = it;
      it = Pl.succ(prev);
    }
    if (Pl.size()>1) Lseg.append(segment(Pl[prev],Pl[fst]));
  }  
  
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  
  segment siter;
  forall(siter,Lseg) win << siter;
  
  win.set_color(cold);
  
  insert_new_segment_scene(gw,Lseg);
}

void chull_rat(GeoWin& gw, list<rat_point>& L)
{
  list<rat_point> Pl = CONVEX_HULL(L);
  list<rat_segment> Lseg;
  list_item it, prev, fst;
  
  prev = Pl.first();
  fst = prev;
  if (prev != NULL) {
    it = Pl.succ(prev);
    while (it != NULL){
      Lseg.append(rat_segment(Pl[prev],Pl[it]));
      prev = it;
      it = Pl.succ(prev);
    }
    if (Pl.size()>1) Lseg.append(rat_segment(Pl[prev],Pl[fst]));
  }  
    
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  
  rat_segment siter;
  forall(siter,Lseg) win << siter;
    
  win.set_color(cold);

  insert_new_rat_segment_scene(gw,Lseg);  
}

// Triangulations
void triang_float(GeoWin& gw, list<point>& L)
{
  GRAPH<point,int> G;
  TRIANGULATE_POINTS(L,G); 
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  edge e;
  list<segment> LPol;  
  forall_edges(e,G) {
   win << segment(G[source(e)],G[target(e)]);
   LPol.append(segment(G[source(e)],G[target(e)]));
  }
  win.set_color(cold);  
  
  insert_new_segment_scene(gw,LPol);
}

void triang_rat(GeoWin& gw, list<rat_point>& L)
{
  GRAPH<rat_point,int> G;
  TRIANGULATE_POINTS(L,G); 
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  edge e;
  list<rat_segment> LPol;  
  forall_edges(e,G) {
   win << rat_segment(G[source(e)],G[target(e)]);
   LPol.append(rat_segment(G[source(e)],G[target(e)]));
  }
  win.set_color(cold);  

  insert_new_rat_segment_scene(gw,LPol);  
}

// WIDTH
void width_float(GeoWin& gw, list<point>& L)
{
  line l1,l2;
  WIDTH(L,l1,l2);
  window& win = gw.get_window();
  color cold= win.set_color(blue); 
  win << l1 << l2;
  win.set_color(cold);  
}

void width_rat(GeoWin& gw, list<rat_point>& L)
{
  rat_line l1,l2;
  WIDTH(L,l1,l2);
  window& win = gw.get_window();
  color cold= win.set_color(blue); 
  win << l1 << l2;
  win.set_color(cold);  
}
 
// Delaunay triangulation

void dt_float(GeoWin& gw, list<point>& L)
{
  GRAPH<point,int> G;
  DELAUNAY_TRIANG(L,G); 
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  edge e;
  list<segment> LPol;
  forall_edges(e,G) {
   win << segment(G[source(e)],G[target(e)]);   
   LPol.append(segment(G[source(e)],G[target(e)]));
  }
  win.set_color(cold);  
  
  insert_new_segment_scene(gw,LPol);
}

void dt_rat(GeoWin& gw, list<rat_point>& L)
{
  GRAPH<rat_point,int> G;
  DELAUNAY_TRIANG(L,G); 
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  edge e;
  list<rat_segment> LPol;
  forall_edges(e,G) {
   win << rat_segment(G[source(e)],G[target(e)]);
   LPol.append(rat_segment(G[source(e)],G[target(e)]));
  }
  win.set_color(cold);  

  insert_new_rat_segment_scene(gw,LPol);  
}

// Furthest point Delaunay Triangulation

void f_dt_float(GeoWin& gw, list<point>& L)
{
  GRAPH<point,int> G;
  F_DELAUNAY_TRIANG(L,G); 
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  edge e;
  list<segment> LPol;
  forall_edges(e,G) {
   win << segment(G[source(e)],G[target(e)]);
   LPol.append(segment(G[source(e)],G[target(e)]));
  }
  win.set_color(cold);  

  insert_new_segment_scene(gw,LPol);    
}

void f_dt_rat(GeoWin& gw, list<rat_point>& L)
{
  GRAPH<rat_point,int> G;
  F_DELAUNAY_TRIANG(L,G); 
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  edge e;
  list<rat_segment> LPol;
  forall_edges(e,G) {
   win << rat_segment(G[source(e)],G[target(e)]);
   LPol.append(rat_segment(G[source(e)],G[target(e)]));   
  }
  win.set_color(cold);  

  insert_new_rat_segment_scene(gw,LPol);      
}

// MST

void mst_float(GeoWin& gw, list<point>& L)
{
  GRAPH<point,int> G;
  MIN_SPANNING_TREE(L,G); 
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  edge e;
  list<segment> LPol;
  forall_edges(e,G) {
   win << segment(G[source(e)],G[target(e)]);
   LPol.append(segment(G[source(e)],G[target(e)]));
  }
  win.set_color(cold); 
  
  insert_new_segment_scene(gw,LPol);        
}

void mst_rat(GeoWin& gw, list<rat_point>& L)
{
  GRAPH<rat_point,int> G;
  MIN_SPANNING_TREE(L,G); 
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  edge e;
  list<rat_segment> LPol;
  forall_edges(e,G) {
   win << rat_segment(G[source(e)],G[target(e)]);
   LPol.append(rat_segment(G[source(e)],G[target(e)]));
  }
  win.set_color(cold); 
  
  insert_new_rat_segment_scene(gw,LPol);      
}

// LEC

void lec_float(GeoWin& gw, list<point>& L)
{
  circle C = LARGEST_EMPTY_CIRCLE(L);
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  win << C;
  win.set_color(cold);   
  
  list<circle> LPol;
  LPol.append(C);
  insert_new_circle_scene(gw,LPol);    
}

void lec_rat(GeoWin& gw, list<rat_point>& L)
{
  rat_circle C = LARGEST_EMPTY_CIRCLE(L);
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  win << C;
  win.set_color(cold);   
  
  list<rat_circle> LPol;
  LPol.append(C);
  insert_new_rat_circle_scene(gw,LPol);   
}

// SEC

void sec_float(GeoWin& gw, list<point>& L)
{
  circle C = SMALLEST_ENCLOSING_CIRCLE(L);
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  win << C;
  win.set_color(cold);   

  list<circle> LPol;
  LPol.append(C);
  insert_new_circle_scene(gw,LPol);      
}

void sec_rat(GeoWin& gw, list<rat_point>& L)
{
  rat_circle C = SMALLEST_ENCLOSING_CIRCLE(L);
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  win << C;
  win.set_color(cold);   

  list<rat_circle> LPol;
  LPol.append(C);
  insert_new_rat_circle_scene(gw,LPol);   
}

// all empty circles

void all_empty_float(GeoWin& gw, list<point>& L)
{
  list<circle> LC;
  circle C;
  ALL_EMPTY_CIRCLES(L,LC);
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  forall(C,LC) win << C;
  win.set_color(cold);   

  insert_new_circle_scene(gw,LC);   
}

void all_empty_rat(GeoWin& gw, list<rat_point>& L)
{
  list<rat_circle> LC;
  rat_circle C;
  ALL_EMPTY_CIRCLES(L,LC);
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  forall(C,LC) win << C;
  win.set_color(cold);  

  insert_new_rat_circle_scene(gw,LC);   
}

// all enclosing circles

void all_encl_float(GeoWin& gw, list<point>& L)
{
  list<circle> LC;
  circle C;
  ALL_ENCLOSING_CIRCLES((const list<point>&)L,LC);
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  forall(C,LC) win << C;
  win.set_color(cold);   

  insert_new_circle_scene(gw,LC);   
}

void all_encl_rat(GeoWin& gw, list<rat_point>& L)
{
  list<rat_circle> LC;
  rat_circle C;
  ALL_ENCLOSING_CIRCLES((const list<rat_point>&)L,LC);
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  forall(C,LC) win << C;
  win.set_color(cold);   

  insert_new_rat_circle_scene(gw,LC);   
}

// point fcns

void point_fcn_two_float(GeoWin& gw, list<point>& L)
{
 if ( L.size() != 2) return;
 point p1 = L.head();
 point p2 = L[L.succ(L.first())]; 
 string str_p1,str_p2;
 string str_sqrdist, str_xdist, str_ydist;
 string_ostream O1,O2,O3,O4,O5;
 O1 << p1 << ends; str_p1=O1.str();
 O2 << p2 << ends; str_p2=O2.str();
 O3 << p1.sqr_dist(p2) << ends; str_sqrdist=O3.str();
 O4 << p1.xdist(p2) << ends; str_xdist=O4.str();
 O5 << p1.ydist(p2) << ends; str_ydist=O5.str(); 
 panel P;
 P.text_item("point p1:" + str_p1);
 P.text_item("");
 P.text_item("point p2:" + str_p2);
 P.text_item("");
 P.text_item("squared distance:" + str_sqrdist);
 P.text_item("");
 P.text_item("x distance:" + str_xdist);
 P.text_item("");
 P.text_item("y distance:" + str_ydist);
 P.text_item("");
   
 P.button("OK");
 gw.open_panel(P);
}
 
void point_fcn_two_rat(GeoWin& gw, list<rat_point>& L)
{
 if ( L.size() != 2) return;
 rat_point p1 = L.head();
 rat_point p2 = L[L.succ(L.first())];  
 string str_p1,str_p2;
 string str_sqrdist, str_xdist, str_ydist;
 string_ostream O1,O2,O3,O4,O5;
 O1 << p1 << ends; str_p1=O1.str();
 O2 << p2 << ends; str_p2=O2.str();
 O3 << p1.sqr_dist(p2) << ends; str_sqrdist=O3.str();
 O4 << p1.xdist(p2) << ends; str_xdist=O4.str();
 O5 << p1.ydist(p2) << ends; str_ydist=O5.str(); 
 panel P;
 P.text_item("point p1:" + str_p1);
 P.text_item("");
 P.text_item("point p2:" + str_p2);
 P.text_item("");
 P.text_item("squared distance:" + str_sqrdist);
 P.text_item("");
 P.text_item("x distance:" + str_xdist);
 P.text_item("");
 P.text_item("y distance:" + str_ydist);
 P.text_item(""); 
 P.button("OK");
 gw.open_panel(P);
}

void point_fcn_three_float(GeoWin& gw, list<point>& L)
{
 if ( L.size() != 3) return;
 point p1 = L.head();
 point p2 = L[L.succ(L.first())]; 
 point p3 = L[L.get_item(2)];
 string str_p1, str_p2, str_p3;
 string str_ori, str_area;
 string_ostream O1,O2,O3,O4,O5;
 O1 << p1 << ends; str_p1=O1.str();
 O2 << p2 << ends; str_p2=O2.str();
 O3 << p3 << ends; str_p3=O3.str();
 O4 << orientation(p1,p2,p3) << ends; str_ori=O4.str();
 O5 << area(p1,p2,p3) << ends; str_area=O5.str(); 
 panel P;
 P.text_item("point p1:" + str_p1);
 P.text_item("");
 P.text_item("point p2:" + str_p2);
 P.text_item("");
 P.text_item("point p3:" + str_p3);
 P.text_item("");
 P.text_item("orientation(p1,p2,p3):" + str_ori);
 P.text_item("");
 P.text_item("area(p1,p2,p3):" + str_area);
 P.text_item(""); 
 P.button("OK");
 gw.open_panel(P);
}

void point_fcn_three_rat(GeoWin& gw, list<rat_point>& L)
{
 if ( L.size() != 3) return;
 rat_point p1 = L.head();
 rat_point p2 = L[L.succ(L.first())]; 
 rat_point p3 = L[L.get_item(2)];
 string str_p1, str_p2, str_p3;
 string str_ori, str_area;
 string_ostream O1,O2,O3,O4,O5;
 O1 << p1 << ends; str_p1=O1.str();
 O2 << p2 << ends; str_p2=O2.str();
 O3 << p3 << ends; str_p3=O3.str();
 O4 << orientation(p1,p2,p3) << ends; str_ori=O4.str();
 O5 << area(p1,p2,p3) << ends; str_area=O5.str(); 
 panel P;
 P.text_item("point p1:" + str_p1);
 P.text_item("");
 P.text_item("point p2:" + str_p2);
 P.text_item("");
 P.text_item("point p3:" + str_p3);
 P.text_item("");
 P.text_item("orientation(p1,p2,p3):" + str_ori);
 P.text_item("");
 P.text_item("area(p1,p2,p3):" + str_area);
 P.text_item(""); 
 P.button("OK");
 gw.open_panel(P);
}

void point_fcn_four_float(GeoWin& gw, list<point>& L)
{
 if ( L.size() != 4) return;
 point p1 = L.head();
 point p2 = L[L.succ(L.first())]; 
 point p3 = L[L.get_item(2)];
 point p4 = L[L.get_item(3)];
 string str_p1, str_p2, str_p3, str_p4;
 string str_sos;
 string_ostream O1,O2,O3,O4,O5;
 O1 << p1 << ends; str_p1=O1.str();
 O2 << p2 << ends; str_p2=O2.str();
 O3 << p3 << ends; str_p3=O3.str();
 O4 << p4 << ends; str_p4=O4.str();
 O5 << side_of_circle(p1,p2,p3,p4) << ends; str_sos=O5.str(); 
 panel P;
 P.text_item("point p1:" + str_p1);
 P.text_item("");
 P.text_item("point p2:" + str_p2);
 P.text_item("");
 P.text_item("point p3:" + str_p3);
 P.text_item("");
 P.text_item("point p4:" + str_p4);
 P.text_item(""); 
 P.text_item("side of circle(p1,p2,p3,p4):" + str_sos);
 P.text_item("");
 P.button("OK");
 gw.open_panel(P);
}

void point_fcn_four_rat(GeoWin& gw, list<rat_point>& L)
{
 if ( L.size() != 4) return;
 rat_point p1 = L.head();
 rat_point p2 = L[L.succ(L.first())]; 
 rat_point p3 = L[L.get_item(2)];
 rat_point p4 = L[L.get_item(3)];
 string str_p1, str_p2, str_p3, str_p4;
 string str_sos;
 string_ostream O1,O2,O3,O4,O5;
 O1 << p1 << ends; str_p1=O1.str();
 O2 << p2 << ends; str_p2=O2.str();
 O3 << p3 << ends; str_p3=O3.str();
 O4 << p4 << ends; str_p4=O4.str();
 O5 << side_of_circle(p1,p2,p3,p4) << ends; str_sos=O5.str(); 
 panel P;
 P.text_item("point p1:" + str_p1);
 P.text_item("");
 P.text_item("point p2:" + str_p2);
 P.text_item("");
 P.text_item("point p3:" + str_p3);
 P.text_item("");
 P.text_item("point p4:" + str_p4);
 P.text_item(""); 
 P.text_item("side of circle(p1,p2,p3,p4):" + str_sos);
 P.text_item("");
 P.button("OK");
 gw.open_panel(P);
}

// segment intersection

void seg_inter_float(GeoWin& gw, list<segment>& S)
{
  //cout << "seg inter float!\n";
  list<point> LI;
  SEGMENT_INTERSECTION(S,LI);
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  point_style pold = win.set_point_style(disc_point);
  point iter;
  forall(iter,LI) win << iter;
  win.set_color(cold);
  win.set_point_style(pold);
}

void seg_inter_rat(GeoWin& gw, list<rat_segment>& S)
{
  //cout << "seg inter rat!\n";
  list<rat_point> LI;
  SEGMENT_INTERSECTION(S,LI);
  window& win = gw.get_window();
  color cold= win.set_color(blue);
  point_style pold = win.set_point_style(disc_point);
  rat_point iter;
  forall(iter,LI) win << iter;
  win.set_color(cold);
  win.set_point_style(pold);
}


GEOWIN_END_NAMESPACE










