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
// file          : src/GeoWin/geo_scene.c
// package       : GeoWin (1.1.9)
// revision      : 1.1.9
// revision_date : 27 September 2000 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken@informatik.uni-trier.de>)
// ============================================================================


#include<LEDA/geowin.h>
#include "geo_localdefs.h"

GEOWIN_BEGIN_NAMESPACE

// ***************************************************************
// ************* GeoScenePrototypes ******************************

int GeoScenePrototypes::SceneCount = 0;

bool GeoScenePrototypes::st_alloc = false; 

static GeoScenePrototypes* tname_map_ptr = 0;

GeoScenePrototypes::GeoScenePrototypes() 
  : allscenes(MAXIMUM_SCENETYPES)
{
  st_alloc=false;
  allscenes.init((GeoScene*)0);
}

GeoScenePrototypes::~GeoScenePrototypes()
{
  st_alloc=false; 
  for( int i = 0; i < SceneCount; i++ )
    delete allscenes[i];
}


int GeoScenePrototypes::RegisterScene(geo_scene sc)
{
  if (tname_map_ptr == 0) { 
                            tname_map_ptr = new GeoScenePrototypes; 
                            st_alloc=true; }

  if( SceneCount < MAXIMUM_SCENETYPES )
    {
      tname_map_ptr->allscenes[SceneCount] = sc;
      string str("Type%dScene", SceneCount+1);
      sc->set_base_name(str);

      return SceneCount++;
    }
  else error_handler(0, "Maximum scene count reached");
  
  return -1;
}

void GeoScenePrototypes::FreeMem()
{
  if (st_alloc) delete tname_map_ptr;
}

geo_scene GeoScenePrototypes::get_prototype(int id) 
{ 
  if (tname_map_ptr && id >= 0 && id < SceneCount) 
     return tname_map_ptr->allscenes[id];
  return 0;
}

geo_scene GeoScenePrototypes::get_prototype(string str) 
{ 
  if (tname_map_ptr == 0) return 0;

  list<string> choice;
  string tmp;
  
  for( int i = 0; i < SceneCount; i++ )
    {
      tmp = GeoScenePrototypes::get_type_name(i);
      if( tmp == str ) return  tname_map_ptr->allscenes[i];
      choice.append(tmp);
    }
  
  cout << "There is no prototype for a scene of type " << str << " known. ";
  cout << endl << "Possible types are : " << endl;
  forall(tmp, choice) cout << tmp << endl;
  
  return 0;
}

void GeoScenePrototypes::set_type_name(int id, string str)
{ 
  if(tname_map_ptr && id>=0 && id<SceneCount) 
      tname_map_ptr->allscenes[id]->set_base_name(str);
}

string GeoScenePrototypes::get_type_name(int id) 
{ 
  if(tname_map_ptr && id>=0 && id<SceneCount) 
    return tname_map_ptr->allscenes[id]->get_base_name();
  return string("");
}

list<string> GeoScenePrototypes::get_all_editables()
{
  list<string> L;
  if (tname_map_ptr == 0) return L;
  for( int i = 0; i < SceneCount; i++ )
    { geo_scene  sc = tname_map_ptr->allscenes[i];
      geo_editor ed = sc->type_editor();
      if( ed ) L.append(sc->get_base_name());
    }
  return L;
}

// ***************************************************************
// ****************** GeoScene ***********************************

  
void GeoScene::init_default_values()
{
 col1=gw->DEFAULT_color;
 col2=gw->DEFAULT_color2; 
 filling_color=gw->DEFAULT_fill_color; 
 text_color=gw->DEFAULT_color;     
 back_line_width=gw->DEFAULT_line_width;       
 active_line_width=gw->DEFAULT_active_line_width;  
 l_style=gw->DEFAULT_line_style;        
 p_style=gw->DEFAULT_point_style;        
}


GeoScene::GeoScene(GeoWin* win) : gw(win) 
{
  set_name(string(""));
  pos               = 0;
  edit_mode         = 0;
  z                 = 0;
  fcn_state         = 0;
  draw_mode_number  = 0;
  col1              = black;        
  col2              = red;   
  filling_color     = ivory;
  cyclic_colors     = false;         
  back_line_width   = 1;     
  active_line_width = 1;      
  l_style           = solid;      
  p_style           = cross_point;  
  copy_attr         = false;    
  visible           = false;
  active            = false;
  edit_menu_type    = -1;
  while_dragging    = false;
  mouse_changing    = false;
  redraw_pt         = NULL;
  debug_mode        = false;
  debug_file_name   = string("debug.geo");
  
  for(int i = 0; i<geo_max_ids; i++) ids[i] = -1;
  
  labels[geo_col0_label] = "interior";
  labels[geo_col1_label] = "boundary";
  labels[geo_col2_label] = "selected";

  init_d3_window = NULL;
  
  // removed from GeoBaseScene / GeoEditScene
   myobjs        = true;
   base_mode     = true;
   change_mode   = -1;			   
   high_light = false;
   mouse_obj_exist = false;
   base_mode = false;  
}

GeoScene::~GeoScene() 
{  
  additional_objects.clear();
  
  geo_scene scn;
  forall(scn,owner) {
     scn->del_dependence(this);
  }

  if( gw )    gw->remove(this);
  while( !results.empty() ) 
    {
      geo_scene sc = results.pop();
      // sc already deleted ?
      //(sc->owner) = 0;
      list_item del=0,lit;
      forall_items(lit,sc->owner)
        if ((sc->owner)[lit] == this) { del = lit; break; }
      if (del) (sc->owner).del(del);
      if ((sc->owner).empty()) delete sc;
    }
}

geo_scene GeoScene::new_scene(string str)
{
  geo_scene proto = GeoScenePrototypes::get_prototype(str);
  return proto->clone();
}

geo_scene GeoScene::new_scene(int id)
{
  geo_scene proto = GeoScenePrototypes::get_prototype(id);
  return proto->clone();
}

void GeoScene::set_name(string nm)
{
 name=nm;
}

string GeoScene::get_name() const { return name; }

void GeoScene::set_base_name(string nm) { base_name = nm; }

string GeoScene::get_base_name() const { return base_name; }

void GeoScene::set_type_name(string str)
{
  int id = GeoSceneId();
  GeoScenePrototypes::set_type_name(id, str);
}

string GeoScene::get_type_name() const
{
  int id = GeoSceneId();
  return GeoScenePrototypes::get_type_name(id);
}

color GeoScene::get_default_color1()          
{ 
 return col1; 
}

color GeoScene::get_sel_color()               
{ 
  return col2;
}

color GeoScene::get_default_color2()          
{
 return filling_color; 
}

point_style GeoScene::get_default_point_style() 
{ return p_style; }

color GeoScene::get_default_text_color()        
{ return text_color; }

line_style GeoScene::get_default_line_style() 
{ return l_style; }

int  GeoScene::get_default_line_width()       
{ return get_line_width(); }


bool GeoScene::IsMyKindOfScene(geo_scene sc)
{
  return sc->IsSuperOrEqual(this);
}

void GeoScene::init_from_prototype(geo_scene proto)
{
  set_base_name(proto->get_base_name());
  draw_object_parameters = proto->draw_object_parameters;
}

void GeoScene::init_data()
{
  update();
  if (gw){
    gw->redraw();
    gw->update_status_line();
  }
}

void GeoScene::edit()
{ if ( gw) gw->redraw(); }

list_item GeoScene::add_remark(double x,double y,string rem)
{
 GeoRemark gr(x,y);
 gr.set_remark(rem);
 GeoWin_GeoObj gakt(gr);
 
 list_item it= additional_objects.append(gakt);
 return it;
}

list_item GeoScene::add_remark(double x,double y,double wd,string rem)
{
 GeoRemark gr(x,y,wd);
 gr.set_remark(rem);
 GeoWin_GeoObj gakt(gr);
 
 list_item it= additional_objects.append(gakt);
 return it;
}

void GeoScene::add_dependence(GeoScene* sc)
{
  results.append(sc);
  (sc->owner).append(this);
}

void GeoScene::del_dependence(GeoScene* sc)
{
  //cout << "remove " << sc->get_name() << " from " << this->get_name() << "\n";
  list_item lit, del=0;
  forall_items( lit, results )
    if( results[lit] == sc ) { del = lit; break; }
  if( del )
    {
      results.del_item(del);
      del=0;
      forall_items(lit,sc->owner)
        if ((sc->owner)[lit] == this) { del = lit; break; }
      if (del) (sc->owner).del(del);
      if ((sc->owner).empty()) delete sc;
    }
  else 
    {
      cout << "error in remove " << sc->get_name() << " from " << this->get_name() << "\n";
    }
}

void GeoScene::redraw(window* w, double x1, double y1, double x2, double y2)
{
  geo_scene sc;

  list_item it;
  forall_items(it,additional_objects) {
   GeoWin_GeoObj& gr = additional_objects[it];
   gr.draw(*w); 
 }

  forall( sc, results )
    {
      if( sc->is_visible() && sc->gw != gw )   sc->gw->redraw();
      if( sc->get_active() )  sc->gw->update_status_line();
    }

  // reset point style , line style, line width
  w->set_point_style(oldpstl);
  w->set_line_style(oldstl);
  w->set_line_width(oldwl);  
}

void GeoScene::show_points(const list<point>& L)
{
  window& w = gw->get_window();
  point_style pold=w.set_point_style(rect_point);
  color cold = w.set_fill_color(ivory);
    
  point piter;
  forall(piter,L) w << piter;
     
  w.set_point_style(pold);
  w.set_fill_color(cold);  
}

void GeoScene::write_postscript(ps_file& f)
{
  list_item it;
  forall_items(it,additional_objects) {
   GeoWin_GeoObj& gr = additional_objects[it];
   gr.write_ps(f); 
 }  
}

void GeoScene::update()
{
  geo_scene sc;
  forall( sc, results ) {
    if( !while_dragging || sc->is_visible() || (! (sc->results).empty()))  sc->update();
  }
    
  // clean up lists of added/ deleted objects ...
  clear_op_objs();
}

void GeoScene::update_and_redraw()
{
  update();
  gw->redraw_and_update_status_line();
}

string GeoScene::information()
{
  return string("\\blue \\bf ~~%s~: ~~~\\black \\tt ", get_name());
}

void GeoScene::mouse_at_pos(double, double, long& MASK)
{
  gw->set_cursor(-1);
}

void GeoScene::split_and_append(string s, list<string>& LS, int cnt)
{
  int posact=0, posmax= s.length()-1, pos2=0;
  
  for(;posact< posmax+1;posact=posact+cnt){
    pos2 = posact+cnt-1;
    if (pos2 > posmax) pos2=posmax;
    LS.append(s(posact,pos2)); 
  }  
  LS.append(string(" "));
}

void GeoScene::contents()
{
  list<string> Ls;
  string_ostream str_bf;
  write(str_bf,"\n");
  str_bf << ends;
  string h = str_bf.str();
  string sh("\n");
  int posakt=0, posmax= h.length()-1,act;
  act=h.pos(sh,posakt);
  
  while(act != -1){
    split_and_append(h(posakt,act-1),Ls,77);
    posakt=act+1;
    act=h.pos(sh,posakt);
  }
  
  split_and_append(h(posakt,posmax),Ls,77);
  LedaFileViewer(Ls);
}

bool GeoScene::options(panel* p)
{ 
  panel* P = p;
  int own_but;
  
  if( !p )
    {
      P = new panel("Scene Options");
      P->set_inf(&own_but);
    }
   
  color c0 = filling_color; 
  color c1 = col1; 
  color c2 = col2;
  bool enum_col = cyclic_colors;
  bool dbg = debug_mode;
  string dbs = debug_file_name;
  string xstr("");

  int aw = active_line_width, bw = back_line_width;
  line_style lst = l_style;
  point_style pst= p_style;
  
  P->text_item("\\bf\\blue Colors");
  P->color_item(labels[geo_col0_label], c0);
  P->color_item(labels[geo_col1_label], c1);
  P->color_item(labels[geo_col2_label], c2);
  P->bool_item("enum colors",enum_col);
  P->text_item("");

  P->text_item("\\bf\\blue Points"); 
  P->pstyle_item("point style", pst);
  
  P->text_item("\\bf\\blue Lines");
  P->lstyle_item("line style", lst);
  P->lwidth_item("line width", bw);
  P->lwidth_item("active width", aw);
  P->text_item("");
  
  if (! draw_object_parameters.empty()) {
   xstr = draw_object_parameters[draw_object_parameters.get_item(draw_mode_number)];
   P->text_item("\\bf\\blue Draw function");
   P->string_item("Drawing mode:", xstr, draw_object_parameters, 8);
   P->text_item("");
  }
  
  P->text_item("\\bf\\blue Debug");      
  P->bool_item("Output input scene", dbg);
  P->string_item("File name:", dbs);
  P->text_item("");  
  
  P->fbutton("apply",   APPLY_BUTTON);
  P->button("cancel",   CANCEL_BUTTON);
  
  int& butt = *((int*)(P->get_inf()));
 
  butt = gw->open_panel(*P);
  
  if( butt == CANCEL_BUTTON ) return false;
  
  filling_color = c0;
  col1 = c1;
  col2 = c2;
  active_line_width = aw;
  back_line_width = bw;
  l_style = lst;
  p_style = pst;
  debug_mode = dbg;
  cyclic_colors = enum_col;
  debug_file_name = dbs;
  
  if (! draw_object_parameters.empty()) {
   if (xstr.length() > 0){ // a new draw mode was choosen
    string iter; 
    int nb=0, counter=0;
    forall(iter, draw_object_parameters){
      if (iter == xstr) nb=counter; counter++;
    }
    draw_mode_number = nb;
   }
  }

  if(!p) gw->redraw();  
  return true;
}
 
GEOWIN_END_NAMESPACE
