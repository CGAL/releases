// ============================================================================
//
// Copyright (c) 1999 The CGAL Consortium
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
// package       : GeoWin (1.0.8)
// revision      : 1.0.8
// revision_date : 17 December 1999 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken@informatik.uni-halle.de>)
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
 back_line_width=gw->DEFAULT_line_width;       
 active_line_width=gw->DEFAULT_active_line_width;  
 l_style=gw->DEFAULT_line_style;        
 p_style=gw->DEFAULT_point_style;        
}


GeoScene::GeoScene(GeoWin* win) : gw(win) 
{
  set_name(string(""));
  pos               = 0;
  col1              = black;        
  col2              = red;   
  filling_color     = ivory;       
  back_line_width   = 1;     
  active_line_width = 1;      
  l_style           = solid;      
  p_style           = cross_point;      
  visible           = false;
  active            = false;
  edit_menu_type    = -1;
  while_dragging    = false;
  mouse_changing    = false;
  redraw_pt         = NULL;
  
  for(int i = 0; i<geo_max_ids; i++) ids[i] = -1;
  
  labels[geo_col0_label] = "interior";
  labels[geo_col1_label] = "boundary";
  labels[geo_col2_label] = "selected";

  init_d3_window = NULL;
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


bool GeoScene::IsMyKindOfScene(geo_scene sc)
{
  return sc->IsSuperOrEqual(this);
}

void GeoScene::init_from_prototype(geo_scene proto)
{
  set_base_name(proto->get_base_name());
}
 

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
  forall( sc, results )
    if( !while_dragging || sc->is_visible() )  sc->update();
}

string GeoScene::information()
{
  return string("\\blue \\bf ~~%s~: ~~~\\black \\tt ", get_name());
}

void GeoScene::mouse_at_pos(double, double, long& MASK)
{
  gw->set_cursor(-1);
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
    Ls.append(h(posakt,act-1));
    posakt=act+1;
    act=h.pos(sh,posakt);
  }
  
  Ls.append(h(posakt,posmax));
  LedaFileViewer(Ls);
}

void GeoScene::options(panel* p)
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
  bool vis = visible;

  int aw = active_line_width, bw = back_line_width;
  line_style lst = l_style;
  point_style pst= p_style;
  
  P->text_item("\\bf\\blue Colors");
  P->color_item(labels[geo_col0_label], c0);
  P->color_item(labels[geo_col1_label], c1);
  P->color_item(labels[geo_col2_label], c2);
  P->text_item("");

  P->text_item("\\bf\\blue Points"); 
  P->pstyle_item("point style", pst);
  
  P->text_item("\\bf\\blue Lines");
  P->lstyle_item("line style", lst);
  P->lwidth_item("line width", bw);
  P->lwidth_item("active width", aw);
  
  
  P->text_item("\\bf\\blue Visibility");
  P->bool_item("always visible", vis);
  P->text_item("");
  
  P->fbutton("apply",   APPLY_BUTTON);
  P->button("cancel",   CANCEL_BUTTON);
  
  int& but = *((int*)(P->get_inf()));
 
  but = gw->open_panel(*P);
 
  //but = P->open(w);
  
  if( but == CANCEL_BUTTON ) return;
  
  filling_color = c0;
  col1 = c1;
  col2 = c2;
  active_line_width = aw;
  back_line_width = bw;
  l_style = lst;
  p_style = pst;
  visible = vis;
}
 
GEOWIN_END_NAMESPACE
