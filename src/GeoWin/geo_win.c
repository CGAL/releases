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
// file          : src/GeoWin/geo_win.c
// package       : GeoWin (1.0.8)
// revision      : 1.0.8
// revision_date : 17 December 1999 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken@informatik.uni-halle.de>)
// ============================================================================

#include <LEDA/geowin.h>
#include <LEDA/stream.h>
#include <LEDA/file_panel.h>
#include <LEDA/file.h>
#include <LEDA/pixmaps/texture.h>

#include "geo_localdefs.h"


GEOWIN_BEGIN_NAMESPACE

void init_leda_float_default_types();
void init_leda_rat_default_types();


void update_gw(GeoWin *gw)
{
  if(gw){
	gw->redraw();
	gw->update_status_line();
  }
}

void gw_save_grid_paras(window* w,double& gdist, int& gmode, grid_style& gstyle)
{
  gdist= w->get_grid_dist();
  gmode= w->get_grid_mode();
  gstyle=w->get_grid_style();
}

void gw_restore_grid_paras(window* w,double gdist, int gmode, grid_style gstyle)
{
  w->set_grid_dist(gdist);
  w->set_grid_mode(gmode);
  w->set_grid_style(gstyle);
}

void mouse_pos(long& MASK,GeoWin* gw, bool b)
{
     if (b)
      {
	MASK |= A_OBJECT;
	gw->set_cursor(60);
      }
    else
      {
	MASK = 0;
	gw->set_cursor();
      }
}

void setup_font(window& w, double size)
{     
  int sz = w.real_to_pix(size);

  if (sz<8) sz=8;

  string font_name;
  font_name = string("F%d",sz);
                
  w.set_font(font_name);
}



void setup_focus_dialog(panel& p,color& c1,color& c2,int& lw,line_style& ls,string& label,bool  fredraw)
{
    p.text_item("\\bf\\blue Colors");
    p.color_item("interior", c2);   
    p.color_item("boundary", c1);   
    p.text_item("");
	
    p.text_item("\\bf\\blue Line Style");
    p.lstyle_item("line style", ls);
    p.lwidth_item("line width", lw);
    p.text_item("");  
	

    p.string_item("Object Label",label );
	
    p.fbutton("apply",   APPLY_BUTTON);
    p.button("default",  DEFAULTS_BUTTON);
    p.button("cancel",   CANCEL_BUTTON);
}

bool show_options(GeoScene* scn,panel* p,GeoWin *gw,color& filling_color,bool fredraw)
{  
  //cout << "show_options!\n";

  panel* P = p;

  int own_but;
    
  if( !p ) {
	P = new panel("Scene Options");
  }
  P->set_inf(&own_but);
 
  scn->GeoScene::options(P);

  if( own_but == CANCEL_BUTTON ) return false;
    
  if(!p) gw->redraw();
  return true;
}

bool show_options2(GeoScene* scn,panel* p,GeoWin *gw,color& filling_color,bool& high_light,bool fredraw)
{
    panel* P = p;

    int own_but;
    
    if( !p )
      {
	P = new panel("Scene Options");
	P->set_inf(&own_but);
      }
    
    bool hl = high_light;
    P->text_item("\\bf\\blue Focus");
    P->bool_item("highlight ?", hl);
    
    bool val=show_options(scn,P,gw,filling_color,fredraw);
    
    if( ! val ) return false;

    high_light = hl;
    
    if(!p) gw->redraw();
    return true;
}



#define FCN_COUNT        100

void GeoWin::set_quit_handler(bool (*f)(const GeoWin& gw))
{
 quit_handler=f;
}
  
void GeoWin::set_done_handler(bool (*f)(const GeoWin& gw)) 
{
 done_handler=f;
}

bool GeoWin::done_button_was_pressed()
{ 
 if (! (button_info[GEO_CM_OK] == 2)) return false;
  
 if (done_handler != NULL){
       bool flag=done_handler(*this);
       if (! flag) return false;
 }
 
 return true; 
} 

bool GeoWin::quit_button_was_pressed() 
{ 
 int def_choice = 0;
 if (button_info[GEO_CM_QUIT] != 2) return false;
 else { // really quit ??
    if (quit_handler != NULL){
       bool flag=quit_handler(*this);
       if (! flag) return false;
    }
 
    panel P;

    P.text_item("");
    P.text_item("\\bf\\blue Really quit ?");
    P.text_item("");
    P.choice_item("Options ~/.geowinrc",def_choice,"keep","write","reset");
    P.button("yes");
    P.button("no");

    int w= open_panel(P);

    if (w==0) {
      if (def_choice != 0) 
      { if (def_choice == 2) reset_defaults();
        save_defaults();
      }   
      return true;
    }  
    else { quit_button_reset(); return false; }
 } 
} 

GeoWin::GeoWin(const char* label)
 : mouse_actions(0) , scene_name_map(0)
{
  Wp = new window(560,630,label);
  construct();  
  editables = GeoScenePrototypes::get_all_editables();
}

GeoWin::GeoWin(double x, double y, const char* label)
  : mouse_actions(0) , scene_name_map(0)
{
  Wp = new window(x,y,label);
  construct();  
  editables = GeoScenePrototypes::get_all_editables(); 
}


GeoWin::~GeoWin()
{  
  //cout << "Destruktor GeoWin!\n"; cout.flush();

  geo_scene sc;
  forall(sc,scenes) { 
    sc->set_visible(false);
    sc->del_objref();
  }

  is_locked = true;
  while( cur )  destroy(cur);
  
  for( int i = 0; i <  menu_fcn_count; i++ )  delete menu_fcn[i];
  
  menu_fcn_count = 0;
  if (menu_fcn) delete[] menu_fcn;
  
  for( int j = 0; j <  last_menu; j++ )  delete menus[j];
  delete[] menus;

#if !defined(__win32__)
  delete Wp;
  delete msg_win; 
#endif
 
  if( pin_point ) delete pin_point;

}

// *************************** Help *************************************

void GeoWin::help_user()
{ window* wp = window::get_call_window();
  int b = window::get_call_button();
  string label = wp->get_button_label(b);
  wp->display_help_text(label);
}

void GeoWin::help_about()
{
  string naeher = string("S. N\344her");
  string baesken = string("M. B\344sken");
  panel P;

P.text_item(string("\\bf GeoWin (Version %f)",version()));
P.text_item("");
P.text_item("");
P.text_item("by U. Bartuschka, " + baesken + " and " + naeher + " (1998-99)");
P.text_item("");
P.text_item("");
P.text_item("");
P.text_item("\
GeoWin is a LEDA data type for constructing, displaying \
and manipulating geometrical objects and visualizing \
geometrical algorithms. \
Please see the LEDA User Manual for a detailed description.");
P.text_item("");
P.text_item("");
P.text_item(string("The design and implementation of GeoWin was \
supported in part by the GALIA project."));

P.text_item("");
P.button("ok");

 open_panel(P);
}

void GeoWin::help_news()
{
 panel P;
 P.text_item(string("\\bf New in Version %f",version()));
 P.text_item("");
 P.text_item("- First released version");
 P.text_item("");
 P.button("ok");
 open_panel(P);

}

void GeoWin::help_buttons()
{
  panel P;


P.text_item("\
Left Mouse Button: \
Input an object or scroll the scene by holding the button \
and moving the mouse.");
P.text_item("");
P.text_item("Middle Mouse Button: \
Select an object by clicking on it or a group of objects \
by holding the button and moving the mouse.");
P.text_item("");
P.text_item("Right Mouse Button: \
Open a menu by clicking on an object. The menu contains \
the options setup (for the object), select ((de)select \
the object), delete and object (change the object).\
By clicking on the background you can access the setup \
menu of the whole scene.");
P.text_item("");
P.text_item("");

P.text_item("");
P.button("ok");

open_panel(P);
}

// ***********************************************************************
// **************** Operations for handling default values ************

bool GeoWin::save_defaults(string fname)
{
 ofstream out(fname);
 if (out.fail()) return false;

 out << "color              " << DEFAULT_color       << endl;
 out << "color2             " << DEFAULT_color2      << endl;
 out << "fill_color         " << DEFAULT_fill_color  << endl;
 out << "line_width         " << DEFAULT_line_width  << endl;
 out << "active_line_width  " << DEFAULT_active_line_width << endl;
 out << "line_style         " << (int)DEFAULT_line_style  << endl;
 out << "point_style        " << (int)DEFAULT_point_style << endl;

 out << "show_coords        " << show_coords << endl;
 out << "time_meas          " << time_meas   << endl;
 out << "gw_elim            " << gw_elim    << endl;
 out << "gw_solid           " << gw_solid    << endl;
 out << "gw_anim_speed      " << gw_anim_speed  << endl;
 out << "anim_steps         " << gw_anim_steps  << endl;
 out << "time_out1          " << time_out1   << endl;
 out << "time_out2          " << time_out2   << endl;
 
 return true;
}

bool GeoWin::read_defaults(string fname)
{
  if (! is_file(fname)) return false;
    
  ifstream in(fname);
  if (! in.good()) return false;
  
  string key;
  int w;
  color cl;
  bool b;
  
  while (in >> key)
  { if (key == "color") {in >> cl; DEFAULT_color=cl; }
    if (key == "color2"){in >> cl; DEFAULT_color2=cl; }  
    if (key == "fill_color") {in >> cl; DEFAULT_fill_color=cl; }  
    if (key == "line_width") {in >> w; DEFAULT_line_width=w; }
    if (key == "active_line_width") {in >> w; DEFAULT_active_line_width=w; }
    if (key == "line_style") {in >> w; DEFAULT_line_style=(line_style)w; }
    if (key == "point_style"){in >> w; DEFAULT_point_style=(point_style)w; }
    if (key == "show_coords"){in >> b; DEFAULT_show_coords=b; }  
    if (key == "time_meas") {in >> b; DEFAULT_time_meas=b; }    
    if (key == "gw_elim") {in >> b; DEFAULT_gw_elim=b; }    
    if (key == "gw_solid") {in >> b; DEFAULT_gw_solid=b; }     
    if (key == "gw_anim_speed") {in >> w; DEFAULT_gw_anim_speed=w; }    
    if (key == "anim_steps") {in >> w; DEFAULT_anim_steps=w; }        
    if (key == "time_out1") {in >> w; DEFAULT_time_out1=w; }
    if (key == "time_out2") {in >> w; DEFAULT_time_out2=w; }   
   }
  return in.good();
}

bool GeoWin::save_defaults()
{ char* home = getenv("HOME");
  string fname;
  if (home) fname = string("%s/",home);
  return save_defaults(fname + ".geowinrc");
}

bool GeoWin::read_defaults()
{ 
  reset_defaults();
  char* home = getenv("HOME");
  string fname;
  if (home) fname = string("%s/",home); else return false;
  return read_defaults(fname + ".geowinrc");
}


void GeoWin::reset_defaults()
{
 // scene defaults
 DEFAULT_color=black;
 DEFAULT_color2=red;
 DEFAULT_fill_color=ivory;
 DEFAULT_line_width=1;
 DEFAULT_active_line_width=1;
 DEFAULT_line_style=solid;
 DEFAULT_point_style=cross_point;
 
 // geowin defaults
 DEFAULT_show_coords=true;
 DEFAULT_time_meas=false;
 DEFAULT_gw_elim=false;
 DEFAULT_gw_solid=false;
 DEFAULT_gw_anim_speed=10;
 DEFAULT_anim_steps=10;
 DEFAULT_time_out1=300;
 DEFAULT_time_out2=300;
 
 show_coords=true;
 time_meas=false;
 gw_elim=false;
 gw_solid=false;
 gw_anim_speed=10;
 gw_anim_steps=10;
 time_out1=300;
 time_out2=300;
}

// ***********************************************************************
// ***************************  Main  Operations *************************

void GeoWin::construct()
{  
  read_defaults();
  
  init_leda_rat_default_types();
  init_leda_float_default_types();

  menu_init=false;
  quit_handler=NULL;
  done_handler=NULL;

  Wp->init(-50,450,-50);
  START_XMIN=-50;
  START_XMAX=450;
  START_YMIN=-50;
  START_YMAX=get_ymax();

  Wp->set_inf(this);
  Wp->set_redraw(GeoWin::redraw_geowin);
  show_coords = DEFAULT_show_coords;        //true;
  time_meas   = DEFAULT_time_meas;          //false;
  Wp->set_show_coord_handler(GeoWin::coord_handler);
  scribble_mode=false;
  is_open   = false;
  is_locked = false;

  gw_elim = DEFAULT_gw_elim;                //false;
  gw_solid = DEFAULT_gw_solid;              //false;
  gw_anim_speed = DEFAULT_gw_anim_speed;    //10
  
  gw_anim_steps = DEFAULT_anim_steps;       //10;
  
  msg_win = new window(500, 200, "Messages");
  msg_win->set_inf(this);

  cur_info = string("");

  menus = new menu*[last_menu];
  for( int i = 0; i < last_menu; i++ )  
    {
      menus[i] = new menu;
      menus[i]->set_inf(this);
    }
  menu_fcn = new GeoFunctions*[FCN_COUNT];
  menu_fcn_count = 0;
  user_fcn_count = 0;
  
  Wp->set_node_width(1);
  
  show_grid = false;
  grid = 0.0;
  
  cur = edit_scene = 0;  
  reset_actions();

  time_out1 = DEFAULT_time_out1;            //300
  time_out2 = DEFAULT_time_out2;            //300

  d3_win = NULL;
  Whelpd3= NULL;

  bg_pixmap = "none";
  pin_point = 0;
  mouse_fct = 4;
} 

double GeoWin::get_xmin() const
{
  return Wp->xmin();
}
  
double GeoWin::get_ymin() const
{
  return Wp->ymin();
}
  
double GeoWin::get_xmax() const
{
  return Wp->xmax();
}
    
double GeoWin::get_ymax() const
{
  return Wp->ymax();
}
  
void GeoWin::display(int xc, int yc)
{
  if( is_open ) return;
  
  if (!menu_init) init_menu();

  Wp->set_clear_on_resize(0);
  Wp->geowin_ptr = this;
 
  Wp->open(xc,yc);
  Wp->open_status_window();
  is_open = true;
  grid = 10/Wp->scale();
  if( !scenes.empty() ) 
    {
      activate(scenes.head());
      no_scene_off();
    }
  else no_scene_on();
  make_scene_menu();
  redraw();
}

int GeoWin::open_panel(panel& P)
{ window& W = get_window();
  W.disable_panel();
  int but = P.open(W);
  W.enable_panel(); 
  return but;
}

int GeoWin::open_panel(file_panel& P)
{ window& W = get_window();
  W.disable_panel();
  P.open();
  W.enable_panel(); 
  return 0;
}



void GeoWin::edit()
{
  if (!is_open) display();
  
  while( !quit_button_was_pressed() && !done_button_was_pressed() )
  { 
    long MASK = 0;

    int but;
    window* w;
    double x,y,xval;
    int event = read_event(w, but, x, y);
    
    xval = Wp->pix_to_real(1);

    if( xval >= 1 ) 
      set_rational_precision(1);
    else
      set_rational_precision((int)(1/xval)); 
      
    //cout << "    " << x << "/" << y << "  event:" << event << " window:" << w << "\n";

    while ( event != button_press_event || w != Wp ) 
    {
      event = read_event(w,but,x,y);
      
      //cout << "  " << x << "  " << y << "\n";

      if (w != Wp || event == no_event) continue;
          
      if (cur)  
         cur->mouse_at_pos(x, y, MASK);
      else 
         Wp->set_cursor(-1);
     }
      

    switch (but) 
    { case MOUSE_BUTTON(1) : MASK |= A_LEFT;   break;
      case MOUSE_BUTTON(2) : MASK |= A_MIDDLE; break;
      case MOUSE_BUTTON(3) : MASK |= A_RIGHT;  break;
      default : continue;
     } 


    if (scribble_mode) 
    { if (but==MOUSE_BUTTON(1))
      { do { if (scribble_first) 
              { Wp->draw_pixel(x,y, black); 
                scribble_first = false; 
               }
             else 
               Wp->draw_segment(x,y,scribble_x,scribble_y, black);
             scribble_x = x; 
             scribble_y = y;
             event = Wp->get_event(but,x,y);
        } while (event != button_release_event);

        scribble_first=true;
      }
      continue;
    } 


    if (Wp->shift_key_down()) MASK |= A_SHIFT; 
    if (Wp->ctrl_key_down())  MASK |= A_CTRL;
    if (Wp->alt_key_down())   MASK |= A_ALT;
    
    point p = point(x, y);
   
    geo_action func = mouse_actions[MASK|A_IMMEDIATE];

    if (func)
       MASK |= A_IMMEDIATE;
    else
      { bool dclick = false;
        bool drag = false;
  
        if ( but == MOUSE_BUTTON(1) ||
             but == MOUSE_BUTTON(2) ||
             but == MOUSE_BUTTON(3) )
          Wp->read_mouse(x,y,300,300,dclick,drag);
  
        if (drag)   MASK |= A_DRAG;
        if (dclick) MASK |= A_DOUBLE;
  
        func = mouse_actions[MASK];
      }

    if (func) func(*this, p);
  }
}


bool GeoWin::edit(geo_scene sc)
{
  if( !sc ) return false;
  if( sc->gw != this )
    error_handler(1, "edit : Scene does not belong to this GeoWin!");
  
  if( !is_open) display(); 
  
  geo_scene old_edit = edit_scene;
  edit_scene = sc;
  enable_done_button();
  disable_new_button();
  disable_close_button();
  
  activate(edit_scene);
  edit();

  bool ret = (button_info[GEO_CM_QUIT] == 2) ? false : true;
    
  if( old_edit && ret ) 
    {
      activate(old_edit);  
      enable_done_button();
    }
  else 
    {
      disable_done_button();
      enable_new_button();
      enable_close_button();
    }
  edit_scene = old_edit;

  return ret;
}

// **********************************************************************
// *************************** Window Operations ************************

void GeoWin::init(double x1, double x2, double y1)
{
  if (x2<x1){
   double tm;
   tm=x1; x1=x2; x2=tm;
  }
  if (x1==x2) x2=x2+1; 

  double new_scale = Wp->width()/(x2-x1);
  int g = (int)grid;
  if( show_grid && g*new_scale < 4 ) { g = (int)(6/new_scale); if (g>0) g=-g; }
  if( show_grid )  Wp->init(x1, x2, y1, g, false);
  else             Wp->init(x1, x2, y1, 0, false);
}

void GeoWin::init(double x1, double x2, double y1, double y2, int rand)
{
  double x_min, x_max, y_min, y_max;
  
  if( x2 < x1 ) { x_min = x2; x_max = x1; }
  else          { x_min = x1; x_max = x2; }
  if( y2 < y1 ) { y_min = y2; y_max = y1; }
  else          { y_min = y1; y_max = y2; }
  
  double dx = x_max-x_min;
  double dy = y_max-y_min;
  
  double w = (Wp->xmax()-Wp->xmin())*Wp->scale();
  double h = (Wp->ymax()-Wp->ymin())*Wp->scale();
  
  double weff = w - 2*rand;
  double heff = h - 16 - 2*rand;
  
  double new_scale = dx ? weff/dx : Wp->scale();
  
  if( (!dx && dy) ||  (dy &&  heff/dy < weff/dx ) )
    {
      new_scale = heff/dy;
      x_min -=  (w/new_scale - dx)/2;
      x_max +=  (w/new_scale - dx)/2;
      y_min -=  (18+rand)/new_scale; 
    }
  else
    {
      x_min -= rand/new_scale;
      x_max += rand/new_scale;
      y_min -= (h/new_scale - 16/new_scale - dy)/2;
    }
  
  int g = (int)grid;
  if( show_grid && g*new_scale < 4 ) { g = (int)(6/new_scale); if (g>0) g=-g; }
  
  if( show_grid )  Wp->init(x_min, x_max, y_min, g);
  else             Wp->init(x_min, x_max, y_min, 0);
}


void GeoWin::redraw_geowin(window* wp, double x0, double y0, 
                              double x1, double y1)
{
  ((GeoWin*)(wp->get_inf()))->redraw(x0, y0, x1, y1);
}

void GeoWin::coord_handler(window* win, double x, double y)
{
  BASE_WINDOW* swin = win->get_status_window();

  if( !swin || !swin->is_open()) return;
  
  double y0 = swin->ymin();
  double x1 = swin->xmax();
  double y1 = swin->ymax();
  
  string coord_str("%8.2f %8.2f", x, y);
  double dy = swin->text_width(coord_str) + 2;

  double cy = y1 - swin->pix_to_real(1);
  double cx = x1 - dy;
  swin->draw_filled_rectangle(cx,y0,x1,y1,ivory);
  swin->draw_text(cx,cy,coord_str);
}

void GeoWin::redraw() 
{
  if( is_open && !is_locked && !scribble_mode)
    redraw(Wp->xmin(), Wp->ymin(), Wp->xmax(), Wp->ymax());
}

void GeoWin::redraw(double x0, double y0, double x1, double y1) 
{ 

  if( !is_open || is_locked || scribble_mode) return;
  
  drawing_mode old_mode = Wp->set_mode(src_mode);
  Wp->start_buffering();
  
  Wp->clear(x0, y0, x1, y1);
  
  geo_scene sc;
  forall( sc, scenes ) 
    if( sc->visible && sc != cur ) sc->redraw(Wp, x0, y0, x1, y1);

  if(cur) { cur->redraw(Wp, x0, y0, x1, y1); }
  
  draw_pin();
  draw_info();
  
  Wp->flush_buffer();
  Wp->stop_buffering();
  Wp->set_mode(old_mode);

}

void GeoWin::update_status_line()
{
  if( is_open )
    {
      string str;
      if( cur )  str = cur->information();
      Wp->set_status_string(str);
    }
}


// ***********************************************************************
// *************************** Scene Operations **************************

void GeoWin::insert(geo_scene sc)
{
  if (!sc) error_handler(1, "Can not insert (geo_scene)0 into a GeoWin!");
  
  string tmp = sc->get_name();
  if( tmp == string("") || scene_name_map[tmp] )
    set_name(sc, sc->get_base_name());
  
  if( sc->pos )
    error_handler(1,"insert : Scene is already inserted into a GeoWindow.");
  sc->gw  = this;
  
  sc->pos = scenes.append(sc);
  
  if( scenes.length() == 1 ) 
    {
      activate(sc);
      no_scene_off();
      update_status_line();
    }
  make_scene_menu();
  redraw();
}

void GeoWin::remove(geo_scene sc)
{
  if (!sc) error_handler(1, "remove : Can not remove (geo_scene)0 !");
  
  scenes.del_item(sc->pos);
  bool rd = sc->is_visible();
  sc->pos = 0;
  sc->gw  = 0;
  
  string tmp1 = sc->get_name();
  string tmp2 = sc->get_base_name();
  
  scene_name_map[tmp2]--;
  if( tmp1 == tmp2 ) tmp1 = string("%s-%d", tmp2, 1);
  scene_name_map[tmp1]=0;
  
  if ( cur == sc )
    {
      if( !scenes.empty() )  activate(scenes.head());
      else                  { cur = 0; no_scene_on(); }
      update_status_line();
    }
  
  make_scene_menu();  
  if( rd ) redraw();
}

void GeoWin::destroy(geo_scene sc)
{
  if (!sc) error_handler(1, "destroy : Can not destroy (geo_scene)0 !");
  //sc->clear();
  //cout << "delete scene!\n"; cout.flush();
  delete sc;
  //cout << "after deleting scene!\n"; cout.flush();  
}

geo_scene GeoWin::get_scene_with_name(string nm) const
{
  geo_scene sc;
  forall(sc, scenes) if( sc->get_name() == nm ) return sc;
  return 0;
}

string GeoWin::set_name(geo_scene sc, string nm)
{
  if( nm != string("") )
    {
      string tmp = sc->get_name();
      if( tmp != string("") ) scene_name_map[tmp]--;
      
      sc->set_base_name(nm);
      int i, c = 0;
      
      if( scene_name_map.defined(nm) )  c = scene_name_map[nm];
      
      for( i = 0; i <= c; i++)
        {
          tmp = string("%s-%d", nm, i+1);
          
          if( !scene_name_map[tmp] )  
            {
              scene_name_map[tmp] = 1;
              if( i==0 ) tmp = nm;
              scene_name_map[nm]  = c+1;
              sc->set_name(tmp);
              break;
            }
        }  
      make_scene_menu();
    }
  return sc->get_name();
}

void GeoWin::activate(geo_scene sc)
{
  if( !is_open || !sc )  return;
  
  if( cur && cur != sc ) cur->set_active(false);
    
  cur = sc;
  cur->set_active(true);
  
  if( cur->edit_menu_type != -1)
    {
      Wp->set_window(menu_const + edit_menu1, menus[cur->edit_menu_type]);
      Wp->enable_button(menu_const + edit_menu1); 
      edit_scene =sc;
    }
  else   Wp->disable_button(menu_const + edit_menu1);
  
  redraw();
  update_status_line();
  
  return;
}

geo_scene GeoWin::get_active_scene() const { return cur; }

color GeoWin::get_color(geo_scene sc) const { return sc->get_color(); }

color GeoWin::set_color(geo_scene sc, color c) { 
  color cold=sc->get_color(); sc->set_color(c); return cold; 
}
  
color GeoWin::get_color2(geo_scene sc) const { return sc->get_color2(); }

color GeoWin::set_color2(geo_scene sc, color c) { 
  color cold=sc->get_color2(); sc->set_color2(c); return cold;
}

color GeoWin::set_fill_color(geo_scene sc,color c) { 
  color cold=sc->filling_color; sc->filling_color=c; 
  return cold; 
}

color GeoWin::get_fill_color(geo_scene sc) const { return sc->filling_color; }

bool GeoWin::get_visible(geo_scene sc) const { return sc->get_visible(); }

bool GeoWin::set_visible(geo_scene sc, bool v) { 
 bool bold=sc->get_visible(); sc->set_visible(v); return bold; }
 
void GeoWin::set_all_visible(bool v){
 geo_scene sc;
 forall(sc,scenes) sc->set_visible(v);                                                                                                                                              
}

geowin_redraw* GeoWin::get_redraw_pt(geo_scene sc) { return sc->redraw_pt; }

GEOWIN_END_NAMESPACE

// ***********************************************************************
// *******************  Input and Output Operations  *********************

// put it into a namespace ??

#if defined GEOWIN_USE_NAMESPACE
static GEOWIN_NAMESPACE_NAME::GeoWin* GeoWp = 0;
#else
static GeoWin* GeoWp =0;
#endif

static void geo_read_scene(string fn)
{ GeoWp->read_scene(fn); }

void geo_write_scene(string fn)
{ GeoWp->write_scene(fn); }

void geo_write_ps(string fn)
{ GeoWp->write_ps(fn); }

void geo_write_ps_vis(string fn)
{ GeoWp->write_ps_vis(fn); }

void geo_write_scene_woh(string fn)
{ GeoWp->write_scene_woh(fn); }

static bool s_full_color = true;

void geo_write_screen(string fn)
{ GeoWp->redraw();
  GeoWp->get_window().screenshot(fn,s_full_color); 
}

void geo_dummy(string fn)
{}

static bool read_without_header = false;

GEOWIN_BEGIN_NAMESPACE

void GeoWin::read_scene(string filename)
{
  ifstream is(filename);
  if( !is )  {  error_handler(0, "No such file or directory");  return; }
  
  string type_name;
  string sc_name;
  string identifier;
  double version;

  geo_scene sc;
  
  is >> identifier >> version;
  
  if( !(identifier == string("GEOWIN")) )
    {
      is.close();
      
      if( edit_scene && read_without_header ) 
        {
          ifstream is2(filename);
          edit_scene->read(is2);
        }
      else error_handler(0, "Incorrect Fileheader.");
      return;
    }
  
  is >> type_name >> sc_name;

  
  if( edit_scene )
    if( type_name == edit_scene->get_type_name() )  sc = edit_scene;
    else  
      {
        type_name = string("read : File contains data for type \n \t") + 
          type_name;
        type_name += string(",\n \t but the edited scene contains data ");
        type_name += string("of type \n \t");
        type_name += edit_scene->get_type_name();
        error_handler(0, type_name.cstring());
        return;
      }
  else
    {
      sc = GeoScene::new_scene(type_name);
      sc->set_base_name(sc_name);
      insert(sc);
      activate(sc);
    }
  sc->read(is);
  redraw();
  update_status_line();
}


// new function - save without header
void GeoWin::file_save_woh()
{
  string str1;
  if(cur) str1 = string(cur->get_name()) + string(".geo");
  string str2(".");
  
  GeoWp = this;
  file_panel P(get_window(),str1, str2);
  P.set_save_handler(::geo_write_scene_woh);
  P.set_cancel_handler(::geo_dummy); 
  P.set_pattern("*.geo");
  open_panel(P);  
  GeoWp = 0; 
}

void GeoWin::file_save()
{
  string str1;
  if(cur) str1 = string(cur->get_name()) + string(".geo"); else return;
  string str2(".");
  
  GeoWp = this;
  file_panel P(get_window(),str1, str2);
  P.set_save_handler(::geo_write_scene);
  P.set_cancel_handler(::geo_dummy);
  P.set_pattern("*.geo");
  open_panel(P);  
  GeoWp = 0;
}

void GeoWin::save_ps()
{
  string str1;
  if(cur) str1 = string(cur->get_name()) + string(".ps"); else return;
  string str2(".");
  
  GeoWp = this;
  file_panel P(get_window(),str1, str2);
  P.set_save_handler(::geo_write_ps);
  P.set_cancel_handler(::geo_dummy);
  P.set_pattern("*.ps");
  open_panel(P);  
  GeoWp = 0;
}

void GeoWin::save_ps_vis()
{
  string str1("ps_output.ps");
  if(! cur) return;
  string str2(".");
  
  GeoWp = this;
  file_panel P(get_window(),str1, str2);
  P.set_save_handler(::geo_write_ps_vis);
  P.set_cancel_handler(::geo_dummy);
  P.set_pattern("*.ps");
  open_panel(P);  
  GeoWp = 0;
}

void GeoWin::write_scene(string filename)
{
  if (!cur) return;
  ofstream os(filename);
  if( !os )  { error_handler(0, "Can not save");  return;   }
  string str("GEOWIN ");
  os << str << version() << endl;
  os << cur->get_type_name() << endl;
  os << cur->get_base_name() << endl;
  cur->write(os,"");
  os.close();
}

void GeoWin::write_ps(string filename)
{
  if (!cur) return;
  window& win=get_window();

  ps_file F(filename);
  F.init(win.xmin(),win.xmax(),win.ymin());
  F.set_output_mode(colored_mode);
  F.set_point_style(cur->p_style);  
  cur->write_postscript(F);
  F.close();
}

void GeoWin::write_ps_vis(string filename)
{
  if (!cur) return;
  geo_scene sc;
  window& win=get_window();

  ps_file F(filename);
  F.init(win.xmin(),win.xmax(),win.ymin());
  F.set_output_mode(colored_mode); 

  // iterate through scenes...
  forall(sc,scenes) {
    F.set_point_style(sc->p_style);
    if (sc->visible && sc != cur) sc->write_postscript(F); 
  }  
  if(cur) {
    F.set_point_style(cur->p_style); 
    cur->write_postscript(F);
  }
  
  F.close();
}


void GeoWin::write_scene_woh(string filename)
// write to file without header
{
  if (!cur) return;
  ofstream os(filename);
  if( !os )  { error_handler(0, "Can not save");  return;   }
  cur->write(os,"");
  os.close(); 
}

void GeoWin::file_open()
{
  string str1;
  if(cur) str1 = string(cur->get_name()) + string(".geo");
  else str1 = string("no name");
  
  string str2(".");
  
  GeoWp = this;
  file_panel P(get_window(),str1, str2);
  P.set_load_handler(::geo_read_scene);
  P.set_cancel_handler(::geo_dummy);
  P.set_pattern("*.geo");
  
  panel& pan = P.get_panel();
  P.init_panel();
  pan.bool_item("Read without Header : ", read_without_header);

  open_panel(P); 
  GeoWp = 0;
}

void GeoWin::save_screen()
{
  string fname,dname(".");
 
#if defined(__win32__)
                 fname = "gw_screenshot.wmf";
#else
                 fname = "gw_screenshot.ps";
#endif

  GeoWp = this;
  file_panel P(get_window(),fname, dname);
  P.set_save_handler(::geo_write_screen);
#if defined(__win32__)
                 P.set_save_string("Write Metafile Screenshot");
#else
                 P.set_save_string("Write Postscript Screenshot");
#endif
  P.set_cancel_handler(::geo_dummy);
  P.set_pattern(".");
         
  panel& pan = P.get_panel();
  P.init_panel();
  pan.bool_item("full color",s_full_color);

  open_panel(P);  
  GeoWp = 0;
}


// ******************************************************************
// *****************  View Operations  ******************************

void GeoWin::zoom_up()   {  
 int gmode;
 double gdist;
 grid_style gstyle;
 gw_save_grid_paras(Wp,gdist,gmode,gstyle);
 Wp->zoom(2.0,gw_anim_steps); 
 gw_restore_grid_paras(Wp,gdist,gmode,gstyle); 
}

void GeoWin::zoom_down() {  
 int gmode;
 double gdist;
 grid_style gstyle;
 gw_save_grid_paras(Wp,gdist,gmode,gstyle);
 Wp->zoom(0.5,gw_anim_steps); 
 gw_restore_grid_paras(Wp,gdist,gmode,gstyle); 
}


void GeoWin::zoom_area()
{
  if (!cur) return;

  point p1,p2;
  if (Wp->read_zoom_rect(p1,p2)){
     Wp->zoom_area(p1.xcoord(),p1.ycoord(),p2.xcoord(),p2.ycoord(),gw_anim_steps);
     Wp->set_show_coord_handler(GeoWin::coord_handler);
     update_status_line();
     redraw();
  }
  else 
     Wp->redraw();
}

void GeoWin::reset_window()
{
     Wp->zoom_area(START_XMIN,START_YMIN,START_XMAX,START_YMAX,gw_anim_steps);
}

void GeoWin::fill_window()
{ 
  double x_min =  MAXINT;
  double y_min =  MAXINT;
  double x_max = -MAXINT;
  double y_max = -MAXINT;


  geo_scene sc;
  forall( sc, scenes ) 
  { geo_editor ed = sc->type_editor();
    if (ed && sc->is_visible()) 
    { double x_min_akt, x_max_akt, y_min_akt, y_max_akt;
      if (ed->fill_rect(x_min_akt, x_max_akt, y_min_akt, y_max_akt))
      { if (x_min_akt < x_min) x_min = x_min_akt;
        if (x_max_akt > x_max) x_max = x_max_akt;
        if (y_min_akt < y_min) y_min = y_min_akt;
        if (y_max_akt > y_max) y_max = y_max_akt;
       }
     }
   }

  if (x_min < MAXINT) 
    Wp->zoom_area(x_min, y_min, x_max, y_max, gw_anim_steps);
}


string GeoWin::set_bg_pixmap(string pix_name)
{
  string old = bg_pixmap;
  color bg_col = Wp->get_bg_color();
  color fg_col = Wp->get_fg_color();

  list<string> pm_list;

  int i;
  for(i=0; i < num_texture; i++) pm_list.append( name_texture[i] );
  pm_list.append("none");
  
  i=0;
  string str;
  forall(str, pm_list) 
    if( str == pix_name ) break;
    else i++;
  
  char* pr = 0;
  if( i >= 0 && i < num_texture)
    pr = Wp->create_pixrect(xpm_texture[i]);
  else return old;
  
  pr = Wp->set_bg_pixmap(pr);
  if( pr ) Wp->del_pixrect(pr);
  bg_pixmap = pix_name;
  
  Wp->set_fg_color(fg_col);
  Wp->set_bg_color(bg_col);
  
  return old;
}


void GeoWin::visible_scenes()
{
  if( !cur ) return;
  
  bool *vis= new bool[scenes.length()];

  int i=0;
  geo_scene sc;
  
  panel P("Visible Scenes");
  P.buttons_per_line(2);
  
  P.text_item("\\bf\\blue Visible Scenes");
  P.text_item("");
  P.text_item("");
  
  forall(sc , scenes)  
    { 
      vis[i] = sc->get_visible();  
      if (sc != cur) P.bool_item( sc->get_name(), vis[i] );
      else {
        string strh = sc->get_name();
        P.text_item("\\red "+strh);
      }
      i++;
    }
  P.text_item("");
  P.fbutton("Apply", APPLY_BUTTON);
  P.button("Cancel", CANCEL_BUTTON);

  window& W = get_window();
  W.disable_panel();
  int but = P.open();
  W.enable_panel();
  
  if (but)
    {
      i = 0;
      forall(sc , scenes)  { sc->set_visible(vis[i++]);
         if (sc->is_visible()) sc->update(); 
      }
      redraw();
    }

  delete vis;
}

// ******************************************************************
// *****************  protected members  ****************************

void GeoWin::scene_defaults()
{
  int own_but;
 
  panel P("Scene Defaults");
  P.set_inf(&own_but);
   
  color c0 = DEFAULT_fill_color; 
  color c1 = DEFAULT_color; 
  color c2 = DEFAULT_color2;
  int aw = DEFAULT_active_line_width;
  int bw = DEFAULT_line_width;
  line_style lst = DEFAULT_line_style;
  point_style pst= DEFAULT_point_style;
  
  P.text_item("\\bf\\blue Colors");
  P.color_item(string("default interior"), c0);
  P.color_item(string("default boundary"), c1);
  P.color_item(string("default selected"), c2);
  P.text_item("");

  P.text_item("\\bf\\blue Points"); 
  P.pstyle_item("default point style", pst);
  
  P.text_item("\\bf\\blue Lines");
  P.lstyle_item("default line style", lst);
  P.lwidth_item("default line width", bw);
  P.lwidth_item("default active width", aw);
  
  P.fbutton("apply",   APPLY_BUTTON);
  P.button("cancel",   CANCEL_BUTTON);
  
  int& but = *((int*)(P.get_inf()));
  but = open_panel(P);

  if( but == CANCEL_BUTTON ) return;
  
  DEFAULT_fill_color = c0;
  DEFAULT_color = c1;
  DEFAULT_color2 = c2;
  DEFAULT_active_line_width = aw;
  DEFAULT_line_width = bw;
  DEFAULT_line_style = lst;
  DEFAULT_point_style = pst;
}


void GeoWin::global_options()
{
  bool sh_grid     = show_grid;
  double new_scale = Wp->scale();
  int  grid_dist = (int)grid;
  int  max_dist  = (int)((Wp->xmax()-Wp->xmin())/4);
  int  min_dist  = (int)(new_scale/4);
  int  gr_style     = (int)Wp->get_grid_style();
  
  if (grid_dist > max_dist) max_dist = grid_dist;
  if (grid_dist < min_dist) min_dist = grid_dist;
  
  color bg_col = Wp->get_bg_color();
  
  string pm_name   = bg_pixmap;
  list<string> pm_list;
  
  int i;
  for(i=0; i < num_texture; i++) pm_list.append( name_texture[i] );
  pm_list.append("none");

  bool coords = show_coords;
  bool scribble = scribble_mode;
  bool tme= time_meas;
  
  int  t1   = time_out1;
  int  t2   = time_out2;
  int  prec = rat_point::default_precision;
  bool  fi   = rat_point::use_filter;
  int  mfct = (int) mouse_fct;
  
  int an_steps = gw_anim_steps;
  
  panel P;
  P.set_inf(this);  
  P.text_item("\\bf\\blue Grid Settings");
  P.bool_item("show grid", sh_grid);
  P.int_item("grid dist", grid_dist, min_dist, max_dist);
  P.choice_item("grid style",gr_style,"invisible", "points", "lines");
  P.text_item("");
  
  P.text_item("\\bf\\blue Window Options");
  P.string_item("bg texture", pm_name, pm_list, 5);
  P.color_item("bg color",bg_col);
  P.int_item("animation", an_steps,1,30);
  P.bool_item("show position", coords);
  P.text_item("");


  P.text_item("\\bf\\blue Mouse Options"); 
  P.int_item("capture width", mfct, 1, 15);
  P.int_item("timeout1", t1, 100, 1000);
  P.int_item("timeout2", t2, 10, 1000);
  P.text_item("");  

  P.text_item("\\bf\\blue Rational Kernel Options"); 
  P.int_item("precision", prec, 0, 53);
  P.bool_item("use filter",fi);
  P.text_item("");  


  P.text_item("\\bf\\blue Miscellaneous");   
  P.bool_item("measure time", tme);
  P.bool_item("scribble mode", scribble);
  P.text_item("");
  
  P.fbutton("apply",   APPLY_BUTTON);
  P.button("defaults", DEFAULTS_BUTTON);
  P.button("cancel",   CANCEL_BUTTON);
  
  int but;
  
  while ((but=open_panel(P)) == DEFAULTS_BUTTON )
    { 
      grid_dist = (int)(10/Wp->scale());
      sh_grid   = false;
      gr_style  = point_grid;
      
      bg_col    = white;
      pm_name   = "none";
      
      coords    = DEFAULT_show_coords;
      prec      = 10;
      fi        = true;

      mfct      = 1;
      
      an_steps  = DEFAULT_anim_steps;
      
      time_out1 = DEFAULT_time_out1;
      time_out2 = DEFAULT_time_out2;
      tme       = DEFAULT_time_meas;
    }
  
  if( but == CANCEL_BUTTON ) return;
  
  Wp->set_flush(false);
  
  if( sh_grid ) { grid = grid_dist; show_grid = true; }
  else          show_grid = false;
  double g = grid;
  if( show_grid && g*new_scale < 4 ) g = 6/new_scale;
  if( show_grid ) { if (g>0) g=-g;  Wp->set_grid_dist(-g); }
  else            Wp->set_grid_mode(0);
  Wp->set_grid_style((grid_style)gr_style);
  
  Wp->set_bg_color(bg_col);
  i=0;
  string str;
  forall(str, pm_list) 
    if( str == pm_name ) break;
    else i++;
  
  char* pr = 0;
  if( i >= 0 && i < num_texture)
    pr = Wp->create_pixrect(xpm_texture[i]);
  
  pr = Wp->set_bg_pixmap(pr);
  if( pr ) Wp->del_pixrect(pr);
  bg_pixmap = pm_name;
  
  if( !show_coords && coords ) 
    Wp->set_show_coord_handler(GeoWin::coord_handler);
  if( show_coords && !coords )  Wp->set_show_coord_handler(0);
  
  gw_anim_steps = an_steps;
  
  show_coords = coords;
  scribble_mode=scribble;

  if (scribble_mode)  scribble_first=true;

  rat_point::default_precision=prec;
  rat_point::use_filter=fi;

  mouse_fct = mfct;

  time_out1 = t1;
  time_out2 = t2;
  
  time_meas = tme;

  Wp->set_flush(true);
  
  redraw();      
  update_status_line();
}


void GeoWin::scaling_options()
{
  panel P;  

  P.text_item("\\bf\\blue Window Coordinates");

  double  x0  = Wp->xmin();
  double  x1  = Wp->xmax();
  double  y0  = Wp->ymin();
  double ox0=x0, ox1=x1, oy0=y0;
  
  P.double_item("minimal xcoord", x0);
  P.double_item("maximal xcoord", x1);
  P.double_item("minimal ycoord", y0);

  P.fbutton("apply",   APPLY_BUTTON);
  P.button("defaults", DEFAULTS_BUTTON);
  P.button("cancel",   CANCEL_BUTTON);
  
  int but;
  
  while ((but=open_panel(P)) == DEFAULTS_BUTTON  )
    {
      x0 =   0;
      x1 = 100;
      y0 =   0;
    }
  
  if( but == CANCEL_BUTTON ) return;
  
  if( but && ( x0!=ox0 || x1!=ox1 || y0!=oy0) )
    {
      init(x0, x1, y0);
      redraw();
    }
}

void GeoWin::d3_options()
{
  panel P;  
  bool elim= gw_elim, solid= gw_solid;
  int sp= gw_anim_speed;

  P.text_item("\\bf\\blue Options for 3d Output");

  P.text_item("\\bf\\blue Elimination"); 
  P.bool_item("Elinimate ?", elim);
  P.text_item("");

  P.text_item("\\bf\\blue Solid Output"); 
  P.bool_item("Solid ?", solid);
  P.text_item("");

  P.text_item("\\bf\\blue Animation Speed"); 
  P.int_item("Speed", sp, 1, 32);
  P.text_item("");

  P.fbutton("apply",   APPLY_BUTTON);
  P.button("defaults", DEFAULTS_BUTTON);
  P.button("cancel",   CANCEL_BUTTON);
  
  int but;
  
  while ((but=open_panel(P)) == DEFAULTS_BUTTON  ) {
    elim= DEFAULT_gw_elim; solid= DEFAULT_gw_solid;
    sp= DEFAULT_gw_anim_speed;
  }
  if( but == CANCEL_BUTTON ) return;

  gw_elim= elim; gw_solid= solid; 
  gw_anim_speed= sp;
}

// --------------- additonal objects to scenes --------------------

list_item GeoWin::add_point(geo_scene sc, point p)
{
 GeoWin_GeoObj gakt(p);
 list_item it= sc->additional_objects.append(gakt);
 return it;
}

list_item GeoWin::add_segment(geo_scene sc, segment s)
{
 GeoWin_GeoObj gakt(s);
 //cout << "created GeoObj! \n";
 list_item it= sc->additional_objects.append(gakt);
 return it;
}

list_item GeoWin::add_ray(geo_scene sc, ray r)
{
 GeoWin_GeoObj gakt(r);
 list_item it= sc->additional_objects.append(gakt);
 return it;
}

list_item GeoWin::add_line(geo_scene sc, line l)
{
 GeoWin_GeoObj gakt(l);
 list_item it= sc->additional_objects.append(gakt);
 return it;
}

list_item GeoWin::add_circle(geo_scene sc, circle c)
{
 GeoWin_GeoObj gakt(c);
 list_item it= sc->additional_objects.append(gakt);
 return it;
}

list_item GeoWin::add_gen_polygon(geo_scene sc, gen_polygon g)
{
 GeoWin_GeoObj gakt(g);
 list_item it= sc->additional_objects.append(gakt);
 return it;
}

list_item GeoWin::add_remark(geo_scene sc,double x,double y,string rem)
{ return sc->add_remark(x,y,rem); }

list_item GeoWin::add_remark(geo_scene sc,double x,double y,double wd,string rem)
{ return sc->add_remark(x,y,wd,rem); }
  
color GeoWin::additional_object_get_color(geo_scene sc, list_item it) const
{
  GeoWin_GeoObj& gakt = sc->additional_objects[it];
  return gakt.get_color();
}

color GeoWin::additional_object_set_color(geo_scene sc, list_item it, color c)
{
  GeoWin_GeoObj& gakt = sc->additional_objects[it];
  return gakt.set_color(c);
}

color GeoWin::additional_object_get_fill_color(geo_scene sc, list_item it) const
{
  GeoWin_GeoObj& gakt = sc->additional_objects[it];
  return gakt.get_fill_color();
}

color GeoWin::additional_object_set_fill_color(geo_scene sc, list_item it, color c)
{
  GeoWin_GeoObj& gakt = sc->additional_objects[it];
  return gakt.set_fill_color(c);
}

line_style GeoWin::additional_object_get_line_style(geo_scene sc, list_item it) const
{
  GeoWin_GeoObj& gakt = sc->additional_objects[it];
  return gakt.get_line_style();
}

line_style GeoWin::additional_object_set_line_style(geo_scene sc, list_item it,line_style l)
{
  GeoWin_GeoObj& gakt = sc->additional_objects[it];
  return gakt.set_line_style(l);
}

int GeoWin::additional_object_get_line_width(geo_scene sc, list_item it) const
{
  GeoWin_GeoObj& gakt = sc->additional_objects[it];
  return gakt.get_line_width();
}

int GeoWin::additional_object_set_line_width(geo_scene sc, list_item it,int l)
{
  GeoWin_GeoObj& gakt = sc->additional_objects[it];
  return gakt.set_line_width(l);
}

void GeoWin::delete_additional_object(geo_scene sc, list_item it)
{
  sc->additional_objects.del_item(it);
}

void GeoWin::delete_additional_objects(geo_scene sc) 
{ sc->delete_additional_objects(); }
  

void GeoWin::msg_open(string str)
{
  if( !msg_win->is_open() )  msg_win->open(0, 0);
  msg_win->message(str);
}

void GeoWin::message(string str)
{
  if (str==string("")){
   double x0, x1, y0, y1;
   cur_info = string("");
  
   x0 = Wp->xmin();
   x1 = Wp->xmax(); 
   y0 = Wp->ymin();
   y1 = Wp->ymax();
  
   redraw(x0, y0, x1, y1);  
  }
  else {
   if( !(cur_info == string("")) ) message("");
   cur_info = str;
   draw_info();
  }
}


void GeoWin::draw_info()
{
  double x0, x1, y;
  x0 = Wp->xmin() + Wp->pix_to_real(12);
  x1 = Wp->xmax() - Wp->pix_to_real(12);
  y  = Wp->ymax() - Wp->pix_to_real(2);
  
  Wp->text_box(x0, x1, y, cur_info );    
}

bool GeoWin::get_pin_point( point& p ) const
{
  if (pin_point) 
    {
      p = *pin_point;
      return true;
    }
  return false;
}

void GeoWin::set_pin_point( point p )
{
  if (pin_point)  delete pin_point;
  pin_point = new point(p); 
}

void GeoWin::del_pin_point( )
{
  if (pin_point)  delete pin_point;
  pin_point = 0; 
}

void GeoWin::draw_pin()
{
  if( pin_point )
    {
      int oldw = Wp->set_line_width(1);

      double r = Wp->pix_to_real(4);
      double d = Wp->pix_to_real(3);
      double x = pin_point->xcoord();
      double y = pin_point->ycoord();
      Wp->draw_segment(x-d, y-d, x+d, y+d, black);
      Wp->draw_segment(x-d, y+d, x+d, y-d, black);
      Wp->draw_circle(x, y, r, black);
      
      Wp->set_line_width(oldw);
    }
}


void GeoWin::rotate()
{
  geo_editor ed = cur ? cur->type_editor() : 0;
  if( !ed ) return;

  point p1;
  if( get_pin_point(p1) ) rotate(p1);
  else
    {
      string str("\\bf \\blue ROTATE : \\black click the rotation center.");
      message(str);

      Wp->read_mouse(p1);
      set_pin_point(p1);
      draw_pin();
      rotate(p1);
      del_pin_point();
      redraw();
    }
}

void GeoWin::rotate(const point& p1)
{
  geo_editor ed = cur ? cur->type_editor() : 0;
  if( !ed ) return;
  
  string str("\\bf \\blue ROTATE : \\black select a second point and drag.");
  message(str);
  
  point p2, p3;
  Wp->read_mouse(p2);
  rotate(p1, p2);

  message("");
}

void GeoWin::rotate(const point& p1, const point& p)
{
  geo_editor ed = cur ? cur->type_editor() : 0;
  if( !ed ) return;
  if( !ed->start_changing() )
    error_handler(0, "Changing selected objects is not allowed !");

  point p2 = p;
  point p3;
  segment s1, s2;
  double x1,y1;
  unsigned long t = Wp->button_press_time();
  int event;
  
  do 
    { 
      int val;
      unsigned long t1;
      event = Wp->read_event(val,x1,y1,t1);
      if (event == motion_event) if (t1 - t < 50) continue;
      p3 = point(x1, y1);
      s1 = segment(p1, p2);
      s2 = segment(p1, p3);
      ed->rotate_sel(p1.xcoord(), p1.ycoord(), s1.angle(s2));
      t = t1;      
      p2 = p3;
    }
  while( event != button_release_event);
  
  p3 = point(x1, y1);
  s1 = segment(p1, p2);
  s2 = segment(p1, p3);
  ed->rotate_sel(p1.xcoord(), p1.ycoord(), s1.angle(s2));
  
  ed->stop_changing();
}

void GeoWin::move()
{
  geo_editor ed = cur ? cur->type_editor() : 0;
  if( !ed ) return;
  
  string str("\\bf \\blue MOVE : \\black determine a point and drag.");
  message(str);

  point p1;
  Wp->read_mouse(p1);
  move(p1);
  
  message("");
}


void GeoWin::move(const point& p)
{
  geo_editor ed = cur ? cur->type_editor() : 0;
  if( !ed ) return;
  if( !ed->start_changing() )
    error_handler(0, "Changing selected objects is not allowed !");

  double x = p.xcoord();
  double y = p.ycoord();

  double dx, dy, x1,y1;
  unsigned long t = Wp->button_press_time();
  int event;
     
  do 
  { 
    int val;
    unsigned long t1;
    event = Wp->read_event(val,x1,y1,t1);
    if (event == motion_event) if (t1 - t < 50) continue;
    dx = x1-x; 
    dy = y1-y;
    ed->move_sel(dx, dy);
    t = t1;
    x = x1;
    y = y1;
  }
  while( event != button_release_event);

  // get_window().get_mouse(x1,y1);

  dx = x1-x; 
  dy = y1-y;
  ed->move_sel(dx, dy);
  
  ed->stop_changing();
}

void GeoWin::select()
{
  geo_editor ed = cur ? cur->type_editor() : 0;
  if( !ed ) return;
  
  string str("\\bf \\blue SELECT : \\black determine a corner and drag.");
  message(str);
  
  point p;
  if ( Wp->read_mouse(p) != MOUSE_BUTTON(1) ) return;
  select(p);

  message("");
}


void GeoWin::select_all()
{
  geo_editor ed = cur ? cur->type_editor() : 0;
  if( !ed ) return; 

  ed->select_all();
}

void GeoWin::select(const point& p0)
{
  geo_editor ed = cur ? cur->type_editor() : 0;
  if( !ed ) return;
  
  double x0 = p0.xcoord();
  double y0 = p0.ycoord();
  //unsigned long t = Wp->button_press_time();
  int event;
  double x1,y1;
  
  char* buf = Wp->get_window_pixrect();
  Wp->start_buffering();
  Wp->set_line_width(1);
  
  do
    { 
      
      int val;
      unsigned long t1;
      event = Wp->read_event(val,x1,y1,t1);
      
      Wp->put_pixrect(buf);
      Wp->draw_rectangle(x0, y0, x1, y1); 
      Wp->flush_buffer();
    }
  while(event != button_release_event);
  
  Wp->put_pixrect(buf);  
  Wp->flush_buffer();
  
  Wp->del_pixrect(buf); 
  Wp->stop_buffering();
  
  double tmp;
  if( x1 < x0 ) { tmp = x0; x0 = x1; x1 = tmp; }
  if( y1 < y0 ) { tmp = y0; y0 = y1; y1 = tmp; }
  
  ed->select_in_rect(x0, y0, x1, y1); 
}

void GeoWin::unselect()
{ 
  geo_editor ed = cur ? cur->type_editor() : 0;
  if( ed ) ed->unselect();
}

// d3 - support in GeoWin using d3_window ...

void GeoWin::show_d3()
{
  // init window
  // cout << "show d3!\n"; cout.flush();

  window& W = get_window();
  GRAPH<d3_point,int> H;
  
  d3_win = new d3_window(W,H);
  
  d3_win->set_node_width(4);
  d3_win->set_elim(gw_elim);
  d3_win->set_solid(gw_solid);
  d3_win->set_speed(gw_anim_speed);
  d3_win->set_message("");
  
  geo_scene scn;
  int but; 
    
  forall(scn,scenes){
    if (scn->init_d3_window){
       scn->init_d3_window(scn, (*d3_win), H);
    }
  }
  
  W.disable_panel();

  string msg("\\bf\\blue ~~~~~left:  \\black zoom up \
              \\bf\\blue ~~~~~middle:\\black zoom down \
              \\bf\\blue ~~~~~right: \\black return to geowin");

  W.set_show_coord_handler(nil);
  W.set_status_string(msg);

  //node_array<vector> pos(H);
  //node v;
  //forall_nodes(v,H) pos[v] = H[v].to_vector();
  //d3_win->init(pos);
  
  d3_win->draw();
  
  do {
     but = d3_win->move();
  }
  while (but != MOUSE_BUTTON(3));
  
  delete d3_win;
  d3_win = NULL;

  W.set_show_coord_handler(GeoWin::coord_handler);
  W.enable_panel();
  update_status_line();
  redraw();
}


void GeoWin::hide_d3()
{
  if (d3_win != NULL) 
  { delete d3_win; 
    (*Whelpd3).close(); 
    delete Whelpd3; 
    d3_win=NULL; 
    Whelpd3=NULL; 
  }
}

// GeoProp-class 

color GeoProp::get_obj_color(void* o) 
{
  color c = get_default_color1();
  void* obj = (original && original->defined(o)) ? (*original)[o] : o;
  if( color1_map && color1_map->defined(obj)) c = (*color1_map)[obj];
  return c; 
}

color GeoProp::set_obj_color(void* obj, color c) 
{
  color cold = get_obj_color(obj);
  if( !color1_map ) color1_map = new map<void*, color>;
  (*color1_map)[obj] = c;
  return cold;
}

color GeoProp::get_obj_fill_color(void* o) 
{
  color c = get_default_color2();
  void* obj = (original && original->defined(o)) ? (*original)[o] : o;
  if( color2_map && color2_map->defined(obj)) { c = (*color2_map)[obj]; }

  return c; 
}

color GeoProp::set_obj_fill_color(void* obj, color c) 
{
  color cold = get_obj_fill_color(obj);
  if( !color2_map ) color2_map = new map<void*, color>;
  (*color2_map)[obj] = c;
  return cold;
}

  
line_style GeoProp::get_obj_line_style(void* o)   
{
  line_style lst = get_default_line_style();
  void* obj = (original && original->defined(o)) ? (*original)[o] : o;
  if( lst_map && lst_map->defined(obj)) lst = (*lst_map)[obj];
  return lst;
}

line_style GeoProp::set_obj_line_style(void* obj, line_style lst)
{
  line_style lold = get_obj_line_style(obj);
  if(!lst_map) lst_map = new map<void*,line_style>;
  (*lst_map)[obj] = lst;
  return lold;
}

int GeoProp::get_obj_line_width(void* o)
{ 
  int lw = get_default_line_width();
  void* obj = (original && original->defined(o)) ? (*original)[o] : o;
  if ( lw_map && lw_map->defined(obj) ) lw = (*lw_map)[obj];
  return  lw;
}

int GeoProp::set_obj_line_width(void* obj, int w)
{
  int lold = get_obj_line_width(obj);
  if(!lw_map) lw_map = new map<void*, int >;
  (*lw_map)[obj] = w;
  return lold;
}

bool GeoProp::get_obj_label(void* o,string& label)
{ 
  if (! label_map) return false;
  void* obj = (original && original->defined(o)) ? (*original)[o] : o;
  if ( label_map && label_map->defined(obj) )  { label=  (*label_map)[obj]; return true; }
  return false;
}

void GeoProp::set_obj_label(void* obj, string label)
{
  if(!label_map) label_map = new map<void*, string >;
  (*label_map)[obj] = label;
}  

void GeoProp::set_original_properties(void* o, void* obj)
{
    if( color1_map && color1_map->defined(obj) )
      (*color1_map)[o] = (*color1_map)[obj];
    if( color2_map && color2_map->defined(obj) )
      (*color2_map)[o] = (*color2_map)[obj];
    if( lst_map && lst_map->defined(obj) )
      (*lst_map)[o] = (*lst_map)[obj];
    if( lw_map && lw_map->defined(obj) )
      (*lw_map)[o] = (*lw_map)[obj];
    if( label_map && label_map->defined(obj) )
      (*label_map)[o] = (*label_map)[obj];
}

void GeoProp::set_def_properties(void* o)
{
    if( color1_map && color1_map->defined(o) )
      (*color1_map)[o] = get_default_color1();
    if( color2_map && color2_map->defined(o) )
      (*color2_map)[o] = get_default_color2();
    if( lst_map && lst_map->defined(o) )
      (*lst_map)[o] = get_default_line_style();
    if( lw_map && lw_map->defined(o) )
      (*lw_map)[o] = get_default_line_width();
    if( label_map && label_map->defined(o) )
      (*label_map)[o] = string("");
}

void GeoProp::original_properties(void* o)
{
    void* obj = original ? (*original)[o] : o;
    if(o==obj )  return; //was identical...

    set_original_properties(o,obj);
}
  
void GeoProp::set_default_properties(void* o)
{
    set_def_properties(o);
    if( original && original->defined(o))  (*original)[o] = o;
}

void GeoProp::undefine_all()
{
    undefine_colors1();
    undefine_colors2();
    undefine_line_styles();
    undefine_line_width();
    undefine_labels();
}

GEOWIN_END_NAMESPACE
