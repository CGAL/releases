// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : src/GeoWin/LEDA/geowin.h
// package       : GeoWin (1.1.9)
// revision      : 1.1.9
// revision_date : 27 September 2000 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef LEDA_GEOWIN_H
#define LEDA_GEOWIN_H

#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 410096
#include <LEDA/REDEFINE_NAMES.h>
#endif

#include<LEDA/std/ctype.h>
#include<LEDA/list.h>
#include<LEDA/array.h>
#include<LEDA/d_array.h>
#include<LEDA/map.h>
#include<LEDA/window.h>
#include<LEDA/color.h>
#include<LEDA/rat_window.h>
#include<LEDA/string.h>
#include<LEDA/graph.h>
#include<LEDA/ps_file.h>
#include<LEDA/d3_window.h>
#include<LEDA/d3_point.h>
#include<LEDA/d3_rat_point.h>
#include<LEDA/geo_graph.h>


#if (__LEDA__ >= 420)
#include<LEDA/triangle.h>
#include<LEDA/rat_triangle.h>
#endif

#if defined(_MSC_VER) || defined(NO_STATIC_DATA_MEMBER)
#define NO_STATIC_DATA_MEMBER2
#endif


#if defined(LEDA_INSTALL)
#define INIT_GEOWIN_LEDA_DEFAULT_TYPES
#endif


#if defined GEOWIN_USE_NAMESPACE

#if !defined GEOWIN_NAMESPACE_NAME
#define GEOWIN_NAMESPACE_NAME CGAL
#endif

#define GEOWIN_BEGIN_NAMESPACE namespace GEOWIN_NAMESPACE_NAME {
#define GEOWIN_END_NAMESPACE }
#else
#  define GEOWIN_BEGIN_NAMESPACE
#  define GEOWIN_END_NAMESPACE
#endif

// ps_file output operator for the (rat_)triangle
#if (__LEDA__ >= 420)

inline ps_file& operator<<(ps_file& F,const triangle& t) 
{
  F.draw_filled_triangle(t.point1(),t.point2(),t.point3(),F.get_fill_color());
  F.draw_triangle(t.point1(),t.point2(),t.point3()); 
  return F; 
}

inline ps_file& operator<<(ps_file& F,const rat_triangle& t) 
{ F << t.to_float(); return F; }

#endif

// for d3_points/d3_rat_points in GeoWin...
inline window& operator<<(window& w,const d3_point& p)
{ point p2d(p.xcoord(), p.ycoord());
  w << p2d; return w;
}

inline window& operator<<(window& w,const d3_rat_point& p)
{ rat_point p2d(p.xcoord(), p.ycoord());
  w << p2d;  return w;
}


inline ps_file& operator<<(ps_file& F,const d3_point& p) 
{ F << point(p.xcoord(),p.ycoord()); return F; }

inline ps_file& operator<<(ps_file& F,const d3_rat_point& p) 
{ F << point(p.xcoordD(),p.ycoordD()); return F; }

inline window& operator >> (window& w, d3_point& p)
{ point p1;
  if( w >> p1 ) p = d3_point(p1.xcoord(), p1.ycoord(),0);
  return w;
}

inline window& operator >> (window& w, d3_rat_point& p)
{ rat_point p1;
  if( w >> p1 ) p = d3_rat_point(p1.xcoord(), p1.ycoord(),0);
  return w;
}

// for list<iterator> ...
#if defined(_MSC_VER)
template<class T>
inline istream& operator>>(istream& i,list<T>::iterator&)
{ return i; }

template<class T>
inline ostream& operator<<(ostream& o, const list<T>::iterator&)
{ return o; }
#endif


GEOWIN_BEGIN_NAMESPACE

class _exportC geowin_redraw
{
public:

 virtual void draw(window& W,color c1,color c2,double x1,double y1,double x2,double y2) 
 { }
 
 virtual bool draw_container()
 { return false; }
  
 virtual bool write_postscript(ps_file& PS,color c1,color c2) { return false; }
  
 virtual bool operator() (window& W,color c1,color c2,double x1,double y1,double x2,double y2 ) 
 { draw(W,c1,c2,x1,y1,x2,y2);
   return draw_container(); 
 }
};

// templated variant of geowin redraw redraw class
template<class T>
class _exportC geowin_redraw_container
{
public:

 virtual bool draw(const T&, window& W,color c1,color c2,double,double,double,double) 
 { return false; }
  
 virtual bool write_postscript(const T&, ps_file& PS,color c1,color c2) { return false; }
  
 virtual bool operator() (const T& cnt, window& W,color c1,color c2,double x1,double y1,double x2,double y2 ) 
 { return draw(cnt,W,c1,c2,x1,y1,x2,y2);
   //return draw_container(); 
 }
};

template<class S,class R> class geowin_update
{
 typedef __typename S::value_type InpObject;
 typedef __typename R::value_type ResObject;
 typedef __typename R::iterator   iterator;

 void (*ptr0)(const S& in,R& out);
 void (*ptr1)(const S& in, ResObject& obj);
 ResObject (*ptr2)(const S& in);
 
 void clear_result(R& out)
 {
    iterator it1 = out.begin();
    iterator it2 = out.end();
    out.erase(it1,it2);    
 }
  
public:

  virtual bool insert(const InpObject& new_in)
  // new_in: new inserted object
  {
    return false;
  }
 
  virtual bool del(const InpObject& new_out)
  // new_out: deleted object 
  {
    return false;
  }
 
  // change: move/rotate
  virtual bool change(const InpObject& old_obj, const InpObject& new_obj)
  // old   : object before change ...
  // new   : object after change ...  
  {
    return false;
  }

  virtual void update(const S& in,R& out) 
  {
    operator()(in,out);
  }
   
  virtual void operator() (const S& in,R& out)
  {
    if (ptr0 != NULL) 
    { ptr0(in,out);
      return;
     }

    if (ptr1 != NULL) 
    { clear_result(out);
      ResObject obj;
      ptr1(in,obj);
      out.push_back(obj);
      return;
     }

    if (ptr2 != NULL) 
    { clear_result(out);
      out.push_back(ptr2(in));
      return;
     }  
  }
  
  geowin_update() { ptr0 = NULL; ptr1= NULL; ptr2=NULL; }
  
  geowin_update(void (*fpt)(const S& in,R& out)) { ptr0 = fpt; ptr1= NULL; ptr2=NULL; }
  
  geowin_update(void (*fpt)(const S& in,ResObject& obj)) 
  { ptr0 = NULL; ptr1 = fpt; ptr2 = NULL; }

  geowin_update(ResObject (*fpt)(const S& in))           
  { ptr0 = NULL; ptr1 = NULL; ptr2 = fpt; }
  
};

template <class S, class graph_t>
class geowin_graph_update : public geowin_update<S, list<geo_graph> > {

void (*func)(const S& in, graph_t& G);

public:

void update(const S& in, list<geo_graph>& out)
{ graph_t G;
  func(in,G);
  out.clear();
  out.append(G);
}

geowin_graph_update(void (*alg)(const S&, graph_t& G))
{ func = alg; }

};

template<class GeoObj>
class _exportC GeoInputObject {
  public:
  void (*ptr)(GeoWin&, list<GeoObj>&);

  virtual void operator()(GeoWin& gw, list<GeoObj>& L)
  { 
    //cout << "operator!\n"; cout.flush();
    if (ptr != NULL) ptr(gw,L);
  }
  
  virtual void options(GeoWin& gw) { }
  
  GeoInputObject() { ptr = NULL; }
  GeoInputObject(void (*f)(GeoWin&, list<GeoObj>&)){ ptr=f; }
};


#define GEOWIN_UPDATE_SIZE 10

#define GEOWIN_MARGIN  16        

#define APPLY_BUTTON    2
#define DEFAULTS_BUTTON 1
#define CANCEL_BUTTON   0

// Menuconstants
#define menu_const       400
#define io_menu          0
#define edit_menu1       io_menu + 1
#define mark_menu        edit_menu1 + 1
#define operate_menu     mark_menu + 1
#define readobject_menu  operate_menu + 1
#define clear_menu       readobject_menu + 1
#define input_menu       clear_menu + 1
#define edit_menu2       input_menu + 1
#define scene_menu       edit_menu2 + 1

#define view_menu        scene_menu + 1
#define zoom_menu        view_menu + 1
#define algo_menu        zoom_menu + 1
#define option_menu      algo_menu+ 1
#define scene_opt_menu   option_menu + 1
#define run_menu         scene_opt_menu + 1

#define algo_algorithm_menu run_menu + 1
#define algo_options_menu algo_algorithm_menu + 1
#define scene_list_menu  algo_options_menu + 1
#define scene_groups_menu scene_list_menu + 1
#define scene_cont_menu  scene_groups_menu + 1
#define scene_type_menu  scene_cont_menu + 1
#define help_menu        scene_type_menu + 1
#define sub_menu         help_menu + 1

#define last_menu        sub_menu + 1
// last_menu only counter

// constants for GeoScene::id
#define geo_max_ids          3
#define geo_activ_id         0
#define geo_opt_id           1
#define geo_cont_id          2


// constants for GeoScene::labels
#define geo_max_labels       3
#define geo_col0_label       0
#define geo_col1_label       1
#define geo_col2_label       2

// disabled/enabled menu entries
#define GEO_CM_NEW           0
#define GEO_CM_WRITE         1
#define GEO_CM_EXPORT        6
#define GEO_CM_POST          7
#define GEO_CM_POSTVIS       8

#define GEO_CM_CLOSE         2
#define GEO_CM_CLOSE_ALL     12
#define GEO_CM_OK            3
#define GEO_CM_QUIT          4
#define GEO_CM_ACTIVE_OPT    5

#define GEO_CM_CLEAR         9
#define GEO_CM_VISIBLE       10
#define GEO_CM_Z             11
#define GEO_CM_BUTTONS       13

// as defined in GraphWin
#define A_LEFT	    (1 << 0)
#define A_MIDDLE    (1 << 1)
#define A_RIGHT	    (1 << 2)
#define A_SHIFT	    (1 << 3)
#define A_CTRL	    (1 << 4)
#define A_ALT	    (1 << 5)
#define A_DOUBLE    (1 << 6)
#define A_DRAG      (1 << 7)
#define A_OBJECT    (1 << 8)

#define A_IMMEDIATE (1 << 12)


enum PresentationType {geowin_normal, geowin_selected, geowin_focus};
// we have to draw an object normal, selected, ...

enum geowin_defining_points {geowin_show, geowin_hide, geowin_highlight};

extern _exportF void setup_font(window &w, double sz);

class _exportC GeoScene;

template<class T> class GeoBaseScene;
template<class T> class GeoEditScene;
template<class S,class R> class GeoResultScene;

class _exportC GeoSceneBuilder;
class _exportC GeoEditor;


class _exportC GeoRemark {
  double posx; // x and y - position of the remark
  double posy;
  double sizex; // size
  string remark;// text of the remark

  friend class _exportC GeoWin;

  public:
  GeoRemark(double x,double y) { posx=x; posy=y; sizex=20; }
  GeoRemark(double x,double y,double sx) { posx=x; posy=y; sizex=sx;  } 
  GeoRemark(){}

  string set_remark(string st);
  string get_remark() const;
  double get_size() const { return sizex; }
  double xcoord() const { return posx; }
  double ycoord() const { return posy; }

  friend _exportF ostream& operator<<(ostream& o,const GeoRemark& g);
  friend _exportF istream& operator>>(istream& i,GeoRemark& g);
  
};

inline window& operator << (window& w,const GeoRemark& g)
{
  double wert;
  double sx = g.get_size();
  if (sx >0) wert=sx; else wert=-sx;

  setup_font(w,3);
  w.text_box(g.xcoord(),g.ycoord()+wert,g.ycoord(),g.get_remark());
  return w; 
}

inline ps_file& operator << (ps_file& p,const GeoRemark& g)
{ return p; }

typedef GeoRemark* geo_remark;


class _exportC GeoWin_GeoObj {
 GeoScene* my_scene;
 int mode;
 // =0 ... no object allocated
 // =7 ... GeoRemark
 
 void* object_ptr; // pointer to the object...
 
 //attributes of the GeoWin_GeoObj
 color interior;
 color boundary;
 line_style l_style;
 int l_width;
 
 public:
   GeoWin_GeoObj() {mode =0; }
   GeoWin_GeoObj(const GeoRemark&);
   GeoWin_GeoObj(const GeoWin_GeoObj&);
   
   ~GeoWin_GeoObj();
   int get_mode() const;
   void* get_ptr();
   void draw(window& w) const;
   void write_ps(ps_file& ps) const;
   void init();
   
   color get_color() const;
   color set_color(color c);
   color get_fill_color() const;
   color set_fill_color(color c);
   line_style get_line_style() const;
   line_style set_line_style(line_style l);
   int get_line_width() const;
   int set_line_width(int l);
};

inline int compare(const GeoWin_GeoObj& o1,const GeoWin_GeoObj& o2){ return 0;}
inline ostream& operator<<(ostream& o, const GeoWin_GeoObj& obj) { return o; }
inline istream& operator>>(istream& i, GeoWin_GeoObj& obj) { return i; }


// ------------------------------------------------


// Class that maps all known GeoScenes
class _exportC GeoScenePrototypes 
// saves all prototypes and names for known scenes 
{   
  friend class _exportC GeoSceneBuilder;

  //number of known scenes
  static int       SceneCount;
  
  //array of pointers to prototypes of all known scenes
  array<GeoScene*> allscenes;
  
  // array of typenames for all known scenes
  array<string>    scenenames;  

  static int       RegisterScene(GeoScene* sc); 
  //inserts sc into allscenes and gives it a unique name,returns array position
  static bool st_alloc;   // has a call to RegisterScenes allocated memory  ?
 
  public :
  
  GeoScenePrototypes();
  ~GeoScenePrototypes();

  static void      FreeMem();
  static GeoScene* get_prototype(int id); // id-array position
  static GeoScene* get_prototype(string str);
  
  static void      set_type_name(int id, string str); 
  //sets the name of scene  allscenes[id]
  static string     get_type_name(int id);

  static list<string> get_all_editables(); 
  //returns the names of all (editable) GeoEditScenes<T>

  friend class _exportC GeoScene;
};


class _exportC GeoWin;


class _exportC GeoEditor
// contains all functions for editing
{
  protected :
  
  int id;
  
  GeoEditor(int d = 0) : id(d) {}
  
  public :
  
  
  int operator() () { return id; }
  
  virtual void scene_read_object(int n) { }    // reads in a geoobject (n=0: mouse, else keyboard)
  virtual void generate() { }             // generates objects
  
  virtual void toggle_selection() { }     // changes the selectionstate of the object with focus
  virtual void select_in_rect(bool uflag,double x1, double y1, double x2, double y2, bool b) { }
  virtual bool fill_rect(double&, double&, double&, double&) { return true; }  
  virtual void copy()  { }
  virtual void paste() { }
  virtual void del_sel()   { }
  virtual void del_focus() { }
  virtual void setup_focus_or_raise(bool b) { }
  virtual void obj_focus()   { }
  virtual void obj_edit()    { }
  virtual void clear()       { }

  virtual bool start_changing() { return true; } // called, when the position of an object is changed
  virtual void move_or_rotate_sel(double, double, double, bool, bool) { }
  virtual void stop_changing() { }
 
};


typedef GeoEditor* geo_editor;

class _exportC GeoScene
{
  
  friend class _exportC GeoWin;  
  friend class _exportC GeoScenePrototypes;
  friend class _exportC GeoSceneBuilder;
  friend class _exportC GeoRemark;
  
  // Each scene has an unique |name| 
  // the name is constructed by gw

  string name; 
  string base_name;
  
  protected :
  
  GeoWin* gw;       // pointer to the scene's |GeoWin|  

  list_item  pos;   // position in the list of scenes which are managed by |gw|
  
  bool debug_mode;  // debugging mode ...
  string debug_file_name;
  
  // copy object attributes in result scenes ... 
  bool copy_attr;
  
  int fcn_state;   // number of input function (0...default input)
    
  // drawing parameters :
  color      col1;  //color for normal drawing  
  color      col2;  //color for selected drawing
  color      filling_color; // color for filled objects
  color      text_color;    // color for drawing text 

  int        back_line_width;   // for objects, if the scene is not active
  int        active_line_width; // for objects in the currently active scene
  line_style  l_style;
  point_style p_style;
  
  // cyclic colors in this scene
  bool        cyclic_colors;
  int        cyclic_fill_colors_counter;
  int        cyclic_colors_counter;
  

  geowin_redraw* redraw_pt;

  list<GeoWin_GeoObj> additional_objects; //additional objects of the scene ...
  
  // flag used by |GeoWin| for marking the scene with input focus
  bool active;
  // flag used by |GeoWin| for marking if this scene is visible or hidden
  bool visible;
  // defines the type of the edit-menu used by |GeoWin| 
  int edit_menu_type;

  // The objects of each scene can be the input for a function whose results
  // builds a new scene. Such a result scene is stored in list |results|.
  list<GeoScene*>    owner;     //is empty if it isn't a result scene
  list<GeoScene*>    results;

  virtual GeoScene* clone() = 0; // creates an empty  clone of this scene.
  
  virtual bool IsSuperOrEqual( GeoScene* sc ) { return false; }
  // Returns true if this scene is of the same class as |sc| or if its
  // class is a super class of the class of |sc|. Returns false otherwise.
  
  // internal used integers
  // geo_activ_id ... button number in "activate" submenu of the "Scenes" menu
  // geo_opt_id ... button number in "options" submenu of the "Scenes" menu
  // geo_cont_id ... button number in "contents" submenu of the "Scenes" menu
  int    ids[geo_max_ids];

  // internal used labels
  // geo_col0_label ... dialog label name for fill color
  // geo_col1_label ... dialog label name for col1
  // geo_col2_label ... dialog label name for col2
  string labels[geo_max_labels];

  // is set to true, while dragging 
  bool while_dragging;

  bool mouse_changing;
  
  public :
  
  int edit_mode; // parameter for edit_obj fucntion in edit scenes ...
  
  list<string> draw_object_parameters; // names of different drawing modes ...
  int draw_mode_number;
 
  int z;           // z - coordinate of the scene ...
  
  // removed from BaseScene/ EditScene ...
  bool     myobjs;  //true,if the memory for the data object was allocated by this Geoscene
  bool     high_light;
  bool     mouse_obj_exist;
  bool     base_mode;
  int     change_mode; // 0 ... added, 1 ... deleted, 2 ... changed; negative: call update, not 
                        // insert/del or change ...  
  int     but;
  string   nval;
  int oldwl;
  line_style oldstl;
  point_style oldpstl; 
  
  void (*init_d3_window)(GeoScene* sc, d3_window& W, GRAPH<d3_point,int>& H);  
  virtual void compute_d3_output(GeoScene* sc, d3_window& W, GRAPH<d3_point,int>& H)
  { if (init_d3_window!=NULL) init_d3_window(sc,W,H); }
  
  virtual list<string> get_fcn_names(int&, bool flag) 
  { list<string> LS; return LS; }
  virtual void set_alternative_input_fcn(int i)  { }
  virtual void call_buffer_fcn(int w, bool flag) { }
  
  GeoScene(GeoWin* win);
  
  virtual ~GeoScene();

  static GeoScene* new_scene(string str); // parameter: prototype name or -id
  static GeoScene* new_scene(int id);
  
  void init_default_values();
  // set colors and other parameters ...
 
  void show_points(const list<point>&);

  geowin_redraw* get_redraw_pt() { return redraw_pt; } 
  GeoWin*          get_geowin()  { return gw; }
   
  virtual geo_editor type_editor()  { return 0; }
  
  bool IsMyKindOfScene( GeoScene* sc );
  virtual int GeoSceneId() const = 0;
  void split_and_append(string s, list<string>& LS, int cnt);
  
  void set_name(string nm);
  string get_name() const;
  void set_base_name(string nm);
  string get_base_name() const;
  void set_type_name(string str);
  string get_type_name() const;
  
  color get_color() const { return col1; }
  void  set_color(color c) { col1 = c ; }
  color get_color2() const { return col2; }
  void  set_color2(color c) { col2 = c; }

  int   get_back_line_width() const { return back_line_width; }
  void  set_back_line_width(int lw) { back_line_width = lw; }
  int   get_active_line_width() const { return active_line_width; }
  void  set_active_line_width(int lw) { active_line_width = lw; }
  int   get_line_width() const 
  {return active ? active_line_width : back_line_width;}
  
  virtual color get_default_color1();
  virtual color get_sel_color();
  virtual color get_default_color2();
  virtual point_style get_default_point_style();
  virtual color get_default_text_color();
  virtual line_style get_default_line_style();
  virtual int  get_default_line_width();    

  bool get_visible() const { return visible; }
  void set_visible(bool v) { visible = v; if (v) update(); }
  bool get_active() const { return active; }
  void set_active(bool ac) {  active = ac; }
  bool is_visible() const { return (gw && (visible || active)); }
  
  list_item add_remark(double x,double y,string rem);
  list_item add_remark(double x,double y,double wd,string rem);
  
  void delete_additional_objects() { additional_objects.clear(); }

  void add_dependence(GeoScene* sc); 
  void del_dependence(GeoScene* sc); 
  
  virtual void init_from_prototype(GeoScene* proto);

  virtual void init_data();

  virtual void redraw(window* w, double x1, double y1, double x2, double y2); 
  
  virtual void mouse_at_pos(double, double, long& MASK);
  /* informs this scene about current mouse position. |MASK| will
     be checked for userdefined actions  */ 

  virtual void update();
  
  void update_and_redraw();
  
  virtual void clear_op_objs() {}
  
  void    scene_options()  { options((panel*)0); }
  virtual void scene_input_options() { }
  virtual void clear() { }
  virtual void del_objref() {}

  virtual bool options(panel* p = 0);
  virtual void contents();

  virtual string information();
  virtual void edit(); 
 
  virtual void read(istream& is, bool) = 0;
  virtual void write(ostream& os, string tr) = 0;
  virtual void write_postscript(ps_file& f);  
};

typedef GeoScene* geo_scene;


class _exportC GeoSceneGroup 
{
  friend class _exportC GeoScene;
  friend class _exportC GeoWin;

  string name;
  int id; // menu id ...
  list<geo_scene> group_members;
  list<geo_scene> dependent_scenes;
  
  GeoSceneGroup(const string& s) : id(-1){ name = s; }
  GeoSceneGroup(const string& s,geo_scene sc) : id(-1) { name = s; group_members.append(sc); }
  GeoSceneGroup(const string& s, const list<geo_scene>& Ls) : id(-1)
  { name = s; group_members = Ls; }

};

typedef GeoSceneGroup* geo_scenegroup;

class _exportC GeoSceneBuilder
// helper class for building scenes
{ 
  protected :
  
  friend class _exportC GeoScene; 

  int prototypeid;

  GeoSceneBuilder() : prototypeid(-1) {}
  
  GeoSceneBuilder(geo_scene proto) 
  { 
    //cout << "  Konstruktor GeoSceneBuilder!\n";
    prototypeid = GeoScenePrototypes::RegisterScene(proto);
  }

  ~GeoSceneBuilder(){ GeoScenePrototypes::FreeMem(); }
  
  public :
  
  int get_id() { return prototypeid; }
  
  geo_scene new_scene()
  {
    geo_scene proto = GeoScenePrototypes::get_prototype(prototypeid);
    return proto->clone();
  }
};


void set_rational_precision(int prec); 

class _exportC GeoFunctions
// helper class for adding functions to a menu
{ 
  protected :
  
  string label;
  
  public : 
  
  GeoFunctions(string s) : label(s) {}
  virtual ~GeoFunctions() {}
  virtual void call(GeoWin&) = 0; 
};


class _exportC GeowinMember : public GeoFunctions
{
  void (GeoWin::*f)(void);
  
  public : 
  
  GeowinMember(void (GeoWin::*g)(), string l)  : GeoFunctions(l), f(g)   {}
  GeowinMember(void (GeoWin::*g)()) : GeoFunctions(""), f(g)  {}
  virtual ~GeowinMember() {}
  virtual inline void call(GeoWin& gw);
};


template<class F>
class _exportC GeoFunction : public GeoFunctions
{ 
  F      f;
  
  public :
  
  GeoFunction(F g, string l) : GeoFunctions(l), f(g) {}
  virtual ~GeoFunction() {}
  virtual void call(GeoWin& gw) {  geo_call(gw, f, label); }
};


typedef void (*geo_action)(GeoWin&, const point&);


/*{\Manpage {GeoWin} {} {Geometry Windows}}*/

class _exportC GeoWin 
{
  /*{\Mdefinition
    An instance of data type |\Mname| is an editor 
    for sets of geometric objects. It can be used for the visualization of 
    result and progression of geometric algorithms.
    
    |\Mname| manages the geometric objects in so called scenes.
    A scene contains a container storing geometric objects (the contents of the
    scene) and provides all operations that |\Mname| needs to edit it. 
    Every scene maintains a set of parameters:
    
    \begin{itemize}
    \item |name| is the name of the scene 
          (type |string|)
    \item |color| is the color for drawing the boundaries of the objects
          (type |color|)
    \item |color2| is the color for drawing the selected boundaries of the objects
          (type |color|)
    \item |fill_color| is the color for drawing the interior of the objects
          (type |color|)
    \item |text_color| is the color for drawing text labels
    \item |line_width| is the line width used for drawing the objects
          (type |int|)
    \item |active_line_width| is the line width used for drawing the objects if the
          scene is active (type |int|)
    \item |line_style| is the line style used for drawing the objects
          (type |line_style|)
    \item |point_style| is the point style used for drawing points
          (type |point_style|)	  
    \item |active| is |true| if the scene has input focus (is currently edited) in
          its |GeoWin|, |false| otherwise (type |bool|)	   
    \item |visible| is |true| if the scene is visible in its |GeoWin|, |false| otherwise;
          note that the |active| scene will always be displayed, whether or not the
	  |visible| flag is set for this scene
          (type |bool|)
    \end{itemize}
    
    There are three kinds of scenes:
    \begin{enumerate}
    
    \item {\em Basic Scenes}
    
    The basic scene  type |GeoBaseScene<CONTAINER>| works on  every 
    container type  that provides an interface as the list of the STL library. 
    More precisely, |CONTAINER| has to support the following type definitions 
    and operations:
    \begin{itemize}
    \item |value_type| - the type |T| of values the container holds
    \item |iterator| 
    \item operations |begin()| and |end()| returning an iterator that can be used
          for begining (ending) the traversal of the container
    \item |void push_back(const T&)| for inserting an element at the end of the container
    \item |iterator insert(iterator, const T&)| for inserting an element
    \item |void erase(iterator it)| for erasing an element at position |it|
    \item operation |bool empty()| returning |true| if the container is empty, false
          otherwise
    \end{itemize}
    
    That means, that LEDA lists can be used as well as containers.

    \item {\em Edit Scenes}
    
    A scene of type |GeoEditScene<CONTAINER>| is a user editable scene.
    |\Mname| is an editor for this kind of scenes.
    
    
    \item {\em Result Scenes}
    
    A scene of type |GeoResultScene<I,R>| is not independently 
    editable. Instead its contents (a container of type |R|) is computed by a user
    defined update
    function or update object with an update function. The update function computes
    the contents of the result scene every time when another scene (the input scene for
    the result scene) changes. The update function
      |void (*f_update)(const I& input, R& result)|
    gets the contents of this input scene (a container |input| of type |I|) and computes
    the contents |result| of the result scene.
    We say that the result scene |depends| on its input scene.
   \end{enumerate}    
   
    Both Edit and Result scenes are derived from Basic scenes.
    The objects stored in the containers of the scenes have to support input and
    output operators for streams and the LEDA window and the output operator
    to the |ps_file|.
    
    Please note that the type |geo_scene| is the scene item type used in |\Mname|.
    You can interpret them as pointers to scenes.
}*/

  friend class _exportC GeoScene;
  
  typedef void (*D3_FCN)(geo_scene, d3_window&, GRAPH<d3_point,int>&);
  
  // window member parameters :
  // **************************
  window* Wp;
  window* msg_win;
  d3_window* d3_win;
  window* Whelpd3;
  
  // input mode ...
  int input_mode;
  
  string cur_info;
  void draw_info();

  // is |true| iff the window was opened
  bool   is_open;
  
  // if |is_locked| is true, no redraws take place  (flag to avoid multiple 
  // redraws)
  bool   is_locked;
  
  //create scenes when build in algor. are called
  bool  algo_create_scenes;
  
  // like window::grid but it is not set to 0 if the grid distance is to small
  // or if no grid display is wished
  double grid;
  bool   show_grid;    // |true| if no grid is displayed, false otherwise
  bool   show_coords;  // |true| if coordinates are displayed, false otherwise

  bool   time_meas;    // |true| if time measurement is on

  bool   scribble_mode;// |true| if scribble-mode is on
  bool   scribble_first;// first point scribbled
  double scribble_x,scribble_y; // last scribbled x and y coordinate ...

  string bg_pixmap;    // name of the window background pixmap 

  // parameter for 3d output
  bool   gw_elim;      // elimination in the 3d window ?
  bool   gw_solid;     // solid output ?
  int   gw_anim_speed;// animation speed for 3d
  bool   gw_d3edges;   // show or hide edges in d3 output
  bool   gw_d3_cs;     // show or hide coord. system ...
  double gw_d3_zvalue; // z -value for input of 3d objects ...
  
  // true : update result scenes while moving/rotating objects ...
  bool update_while_object_dragging;
  
  // animation steps for zooming
  int gw_anim_steps;

  // parameter for size of the isorect. around mousepointer
  // (used when finding objects)
  double mouse_fct;
  
  // call mouse_at_pos for current scene (or not)
  bool mouse_pos_check;

  // menu member parameters :
  // ************************
  
  // array of all menus : 
  menu**  menus;  
  
  // array of associated menu functions :
  GeoFunctions** menu_fcn;
  int            menu_fcn_count;  // number of all menu items
  int            user_fcn_count;  // number of user defined menu items
  
  // values for the NEW, WRITE, CLOSE, DONE and QUIT buttons
  public:
  int     buttons[GEO_CM_BUTTONS];
  int     button_info[GEO_CM_BUTTONS];  // and infos about their status
                         // 0 = inactive, 1 = active, 2 = button depend

  private:
  // mouse handling parameter :
  // **************************
  
  // actions for certain mouse or key events
  map<long, geo_action> mouse_actions;
  
  // double click timeout
  int time_out1;
  // time after which for a motion event is tested
  int time_out2;
  
  list<string> help_list;
  
  // scene member parameters :
  // *************************

  // list of all scenes :
  list<geo_scene> scenes;
  
  // list of all scene groups :
  list<geo_scenegroup> scene_groups;

  // currently active scene :
  geo_scene       cur;

  // if a special scene should be edited, |edit_scene| points 
  // to this scene 
  geo_scene       edit_scene;

  // list of names of scene types that can be edited by this |\Mname|
  list<string> editables;

  // maps scene names to its number to avoid duplicates
  d_array<string, int>    scene_name_map;
  
  // node colors / edge colors for d3 output window ...
  map<node,color> node_color_map;
  map<edge,color> edge_color_map; 


  // geometrical parameters :
  // ************************

  // If |pin\_point| is not |0| |\Mname| is pined at this point. In this
  // case by default moves of geometrical object will be rotations around 
  // |pin\_point|
  point* pin_point;
  bool   menu_init;
  
  // handling of defaults (~/.geowinrc):
  // ***********************************
  color DEFAULT_color;
  color DEFAULT_color2;
  color DEFAULT_fill_color;
  int  DEFAULT_line_width, DEFAULT_active_line_width;
  line_style  DEFAULT_line_style;
  point_style DEFAULT_point_style;
  bool DEFAULT_show_coords;
  bool DEFAULT_time_meas;
  bool DEFAULT_gw_elim;
  bool DEFAULT_gw_solid;
  int DEFAULT_gw_anim_speed;
  int DEFAULT_anim_steps;
  int DEFAULT_time_out1;
  int DEFAULT_time_out2;
  
  //visible range when the GeoWin is constructed...
  double START_XMIN,START_YMIN,START_XMAX,START_YMAX;
  
  //z-order for redraw ?
  bool redraw_z_order;
  
  bool save_defaults(string fname); //save the current default values 
  bool save_defaults();             //write them to ~/.geowinrc
  bool read_defaults(string fname); //read the current default values 
  bool read_defaults();             //read them from ~/.geowinrc 
  void reset_defaults();            //reset the default values ...

  // Methods :
  // *********
  // common part of all constructors
  void construct();

  // menu handling :
  // ---------------
  void call_handler(int n);  // n - position of the function to be called
  friend void geo_call_handler(int n);
  
  bool (*quit_handler)(const GeoWin& gw);
  bool (*done_handler)(const GeoWin& gw);

  void done_button_pressed()     { button_info[GEO_CM_OK] = 2; }
  bool done_button_was_pressed();  

  void quit_button_pressed()     { button_info[GEO_CM_QUIT] = 2; }
  void quit_button_reset()       { button_info[GEO_CM_QUIT] = 1; }  
  bool quit_button_was_pressed();
  
  void   make_scene_menu(); // updates scene menu
  void   make_algo_menu(geo_scene sc);
  
  void   call_keyboard_read_object();
  void   call_mouse_read_object();

  // calls |activate| for the scene, for which |ids[geo_active_id] == id|
  void activate(int id);
  friend void geo_activate(int n);
  
  // calls member |options| for the scene, for which |ids[geo_opt_id] == id|
  void scene_options(int id);
  void scene_group_menu(int id);

 // calls member |contents| for the scene, for which |ids[geo_cont_id] == id|  
  void scene_contents(int id);
  void active_scene_options();
  
  friend void geo_scene_option(int n);
  friend void geo_scene_algo(int n);
  friend void geo_scene_contents(int n);
  friend void geo_scene_groups(int n);

  // create a new scene of type editables[n] :
  void new_scene(int n);
  friend void geo_new_scene_handler(int n);
  
  // close the currently active scene :
  void destroy() { if( cur ) destroy(cur); }
  
  // manipulate menu items:
  // ---------------------
  void enable_done_button();
  void disable_done_button();
  void enable_new_button();
  void disable_new_button();
  void enable_close_button();
  void disable_close_button();
  // disables all buttons useless with no scene
  void no_scene_on();
  // enables them again
  void no_scene_off();


  // options :
  // ---------

  // Panel for setting the scene defaults (stored in .geowinrc)
  void scene_defaults(); 
  // panel for the setting of grid distance and style, background color,
  // show_coordinates and time outs for double click and dragging
  void global_options();
  void advanced_global_options();
  // panel for the setting of minimal and Maximal coordinates
  void scaling_options();
  // panel for setting d3 output options
  void d3_options();

  // handling :
  // ----------

  friend _exportF void geo_move(GeoWin& gw, const point& p);
  friend _exportF void geo_rotate(GeoWin& gw, const point& p);
  friend _exportF void geo_object_dragging(GeoWin& gw, const point& p);

  friend _exportF void geo_scroll_scene(GeoWin& gw, const point& p);

  // rotate selected object around pin point :
  void   rotate();
  void   rotate(const point& p);
  void   rotate(const point& p1, const point& p2);

  // move selected object with mouse cursor
  void   move();
  void   move(const point& p);
  
  void   show_sel();
 
  void rotate_menu() { rotate(); }
  void move_menu()   { move();   }
  void select_menu() { select(); }
  void redraw_menu() { redraw(); }
  void destroy_menu(){ destroy();}
  void destroy_all();

  void help_about();
  void help_news ();
  
  void help_user();  

 
  // visibility :
  // ------------
  
  void visible_scenes();
  void z_scenes();
  void scenegroup_dialog(geo_scenegroup gsg);

  public :
  
  // visibility/activate buttons ...
  bool vis_buttons;
  bool activate_buttons;
  
  // true ... show visibility buttons/ show activate buttons
  
  list<geo_scene> VAR_1;  // visibility of these scenes will be shown (string buttons)...
  list<geo_scene> VAR_2;  // visibility of these scenes will be shown (bitmap buttons)...
  list<string> VLABEL;    // button labels ...
  list<unsigned char*> VPIC_LIST;  // bitmap pictures ....
  int VWIDTH, VHEIGHT;    // width and height of the buttons ...
  unsigned char** VPICS;  // bitmaps for buttons ...
  
  list<geo_scene> ACT_SCN; 
  list<unsigned char*>    APIC_LIST;
  unsigned char**         APICS;
  
  panel_item pnit1;
  panel_item pnit2;
  panel_item acit;
  panel_item inpit;
  
  int VIS_STATE; // state of visibility for scenes in VAR ...
  int ACT_STATE;
  int INP_STATE;
  
  // file operations...
  void save_ps();
  void save_ps_vis(); // writes all visible scenes in ps - format...
  bool test_file_exists(string);
  void file_open();
  void write_ps(string filename);
  void write_ps_vis(string filename);
  void write_scene_woh(string filename);
  void file_save();
  void file_save_woh();
  void save_screen(); 
  void round_to_grid(double&,double&);
  void init_and_set_visible(geo_scene sc);
  void redraw_inp_panel();
  
  //operations for getting scenes and GeoWin in update and result scenes ...
  static GeoWin* call_win;
  static geo_scene call_scene; 
  static geo_scene call_inp_scene;
  
  static GeoWin* get_call_geowin() { return call_win; }
  static geo_scene get_call_scene() { return call_scene; }
  static geo_scene get_call_input_scene() { return call_inp_scene; }

  bool get_copy_attr(geo_scene sc) { return sc->copy_attr; }  
  bool set_copy_attr(geo_scene sc, bool b) { bool old = sc->copy_attr; sc->copy_attr = b; return old; }
  
  //drawing mode for 3d objects 0 - xy, 1-xz, other - yz
  static int projection_mode;
  static int get_projection_mode() { return projection_mode; }

  /*{\Mcreation GW}*/

  GeoWin(const char* label = "GEOWIN"); 
  /*{\Mcreate creates a GeoWin $GW$. |\Mvar| is constructed with 
              frame label $label$}*/ 

  GeoWin(int w, int h, const char* label = "GEOWIN"); 
  /*{\Mcreate creates a GeoWin $GW$ with frame label $label$ and 
              window size $w\times h$ pixels. }*/  
  
  ~GeoWin();

  /*{\Moperations }*/
  
  /*{\Mtext
    \medskip
    {\bf a) Main Operations} }*/
#ifdef __HAS_MEMBER_TEMPLATES__

  /*{\Mtext
    \medskip
    The |new_scene| and |get_objects| operations use member templates. If your 
    compiler does not support member templates, you should use instead
    the templated functions |geowin_new_scene| and |geowin_get_objects| with
    |\Mvar| as an additional first parameter.\\
    
    All |new_scene| operations can get as an optional last parameter a 
    pointer to a function that is used to compute the
    three-dimensional output of the scene.
    The type of such a function pointer |f| is 
    
    |void (*f)(const T&, d3_window&, GRAPH<d3_point,int>&))|
    
    where |T| is the type of the container used in the scene (for instance |list<point>|).
    The function gets a reference to the container of it's scene, a reference to the
    output |d3_window| and to the parametrized graph describing the three-dimensional
    output. The function usually adds new nodes and edges to this graph. Note that
    every edge in the graph must have a reversal edge ( and the reversal information
    has to be set). \\
    Example:
\begin{verbatim}
void segments_d3(const list<segment>& L,d3_window& W, 
                 GRAPH<d3_point,int>& H)
{
 GRAPH<d3_point,int> G;
 segment iter;
 forall(iter,L) {
   node v1 = G.new_node(d3_point(iter.source().xcoord(),
                                 iter.source().ycoord(),0));
   node v2 = G.new_node(d3_point(iter.target().xcoord(),
                                 iter.target().ycoord(),0));   
   edge e1 = G.new_edge(v1,v2);
   edge e2 = G.new_edge(v2,v1);
   G.set_reversal(e1,e2);
 }
 H.join(G);
}
\end{verbatim}    
    In this simple example the function gets a list of segments.
    For every segment in the list two new nodes and two new edges are created.
    The reversal information is set for the two edges. At the end the local graph 
    |G| is merged into |H|.

    The following templated |new_scene| operation can be used to create 
    edit scenes.
    The |CONTAINER| has to be a |list<T>| , where T is one of the following
    2d LEDA kernel type
\begin{itemize}
\item |(rat_)point|
\item |(rat_)segment|
\item |(rat_)line|
\item |(rat_)circle|
\item |(rat_)polygon|
\item |(rat_)gen_polygon|
\end{itemize}    
    or a |d3_point| or a |d3_rat_point|.
    If you want to use the other 2d LEDA kernel types, you have to include
    |geowin_init.h| and to initialize them for usage in |GeoWin| by calling
    the |geowin_init_default_type| function at the beginning of |main| (before an
    object of data type |\Mvar| is constructed).
    If you want to use the other 3d LEDA kernel types, you have to include
    |geowin_init_d3.h| and to initialize them for usage in |GeoWin| by calling
    the |geowin_init_default_type| function at the beginning of |main| (before an
    object of data type |\Mvar| is constructed).    
    }*/ 
    

  template<class CONTAINER> GeoEditScene<CONTAINER>* new_scene(CONTAINER& c, D3_FCN f = NULL) 
    /*{\Mopl creates a new edit scene for |c|. |c| will be edited by |\Mvar|.}*/
  {
    return geowin_new_scene(*this, c, f);
  }
  
  /*{\Mtext
    \medskip
    The following |new_scene| operations can be used to create result scenes.
    Result scenes use the contents of another scene (the input scene) 
    as the input for a function (the update function). 
    This function computes the contents of the result scene. The update function 
    is called every time when the contents of the input scene changes.
    Instead of using an update function you can use an update object that encapsulates
    an update function.
    The type of this update object has to be |geowin_update<I,R>| 
    (|I| - type of the container in the input scene, |R| - type of the container 
    in the result scene) or a class derived from it. 
    A derived class should overwrite the virtual update function

     |void update(const I& in,R& out)| 
     
    of the base class to provide a user defined update function.
    The class |geowin_update<I,R>| has 3 constructors getting function pointers
    as arguments:
    
     |geowin_update(void (*f)(const I& in, R& res)|
     
     |geowin_update(void (*f)(const I& in, R::value_type& obj)|
     
     |geowin_update(R::value_type (*f)(const I& in)|
    
    These functions |(*f)| will be called in the update function of the update object.
    The first is the normal update function that gets the contents |in| of the input 
    scene and computes the contents |res| of the output scene. 
    In the second variant the contents of the result scene will first be cleared, then the
    update function will be called and |obj| will be inserted in the result scene.
    In the third variant the contents of the result scene will be cleared, and then
    the object returned by |(*f)| will be inserted in the result scene.
    The class |geowin_update| has also the following virtual functions:
    
     |bool insert(const InpObject& new)|
 
     |bool del(const InpObject& new)|
 
     |bool change(const InpObject& old_obj, 
                  const InpObject& new_obj)|
		  
    where 
    |new| is a new inserted or deleted object and |old_obj| and |new_obj| are 
    objects before and after a change.
    |InpObject| is the value type of the container of the input scene.
    With these functions it is possible to support incremental algorithms. The functions will
    be called, when in the input scene new objects are added ($insert$), deleted ($del$) or 
    changed when performing a move or rotate operation ($change$).
    In the base class these functions return |false|. That means, that the standard update-function
    of the update object should be used. But in derived classes it is possible to overwrite
    these functions and provide user-defined update operations for these three incremental
    operations. Then the function has to return
    |true|. That means, that the standard update function of the update object should not be used.
    
    It is also possible to provide user defined redraw for a scene.
    For this purpose we use redraw objects derived from |geowin_redraw|.
    The derived class has to overwrite the virtual redraw function

     |void draw(window& W,color c1,color c2,double x1,double y1,double x2,double y2)|
     
    of the base class to provide a user defined redraw function. The first 3 parameters
    of this function are the redraw window and the first and second drawing color (|color| 
    and |color2|) of the scene.
    The class |geowin_redraw| has also a virtual method 
    
     |bool draw_container()|
     
    that returns |false| in the base class. If you want the user defined redraw of the scene
    (provided by the redraw function |draw|) and the normal redraw of the scene as well
    (output of the objects stored in the container of the scene), you have to overwrite
    |draw_container| in a derived class by a function returning |true|. 
    
    In update- and redraw- functions and objects the following static member functions 
    of the |GeoWin| class can be used:
    
    |GeoWin*    GeoWin::get_call_geowin()|
    \\
    |geo_scene  GeoWin::get_call_scene()|
    \\
    |geo_scene  GeoWin::get_call_input_scene()|   
    
    The first function returns a pointer to the |GeoWin| of the calling scene,
    the second returns the calling scene and the third (only usable in update functions/
    objects) returns the input scene of the calling scene.
    
    Note that |S| and |R| in the following operations are template parameters.
    |S| and |R| have to be a |list<T>|, where T is a 2d LEDA kernel type,
    a |d3_point| or a |d3_rat_point|.
    |S| is the type of the contents of the input scene, |R| the type of the contents
    of the created result scene.
    
 }*/

  template<class S, class R> 
  GeoResultScene<S,R>* new_scene(void (*f_update)(const S&, R&), geo_scene sc, string str, D3_FCN f = NULL)
    /*{\Mopl  creates a new result scene with name |str|.
             The input scene for this new result scene will be |sc|.
             The update function will be |f_update|. }*/
  { return geowin_new_scene(*this, f_update, sc, str,f );  }

  //result scene for update objects...
  template<class S,class R>
  GeoResultScene<S,R>* new_scene(geowin_update<S,R>& up, geo_scene sc_input, string str, D3_FCN f = NULL)
    /*{\Mopl  creates a new result scene with name |str|.
             The input scene for this new result scene will be |sc_input|.
             The update object will be |up|. }*/
  { return geowin_new_scene(*this,up,sc_input,str,f); }
  
  template<class S,class R>
  void set_update(geo_scene res, geowin_update<S,R>& up)
  /*{\Mopl    makes |up| the update object of |res|.\precond |res| points to a scene of type
              |GeoResultScene<S,R>| .}*/
  { geowin_set_update(res,up); }
  
  template<class S,class R>
  void set_update(geo_scene res, void (*f_update)(const S&, R&))
  /*{\Mopl    makes |f_update| the update function of |res|.\precond |res| points to a scene of type
              |GeoResultScene<S,R>| .}*/
  { geowin_set_update(res,f_update); }  
     
  template<class S,class R>
  GeoResultScene<S,R>* new_scene(geowin_update<S,R>& up, geowin_redraw& rd, geo_scene sc_input, string str, D3_FCN f = NULL)
    /*{\Mopl  creates a new result scene with name |str|.
             The input scene for this new result scene will be |sc_input|.    
             The update object will be |ub|.  
	     The redraw object will be |rd|. }*/
  { return geowin_new_scene(*this,up,rd,sc_input,str,f); }
  
  template<class S,class R>
  GeoResultScene<S,R>* new_scene(geowin_update<S,R>& up, geowin_redraw_container<R>& rd, geo_scene sc_input, string str, D3_FCN f = NULL)
    /*{\Mopl  creates a new result scene with name |str|.
             The input scene for this new result scene will be |sc_input|.    
             The update object will be |ub|.  
	     The redraw container object will be |rd|. }*/
  { return geowin_new_scene(*this,up,rd,sc_input,str,f); }

  template<class CONTAINER> bool get_objects(CONTAINER& c)
    /*{\Mopl  If the contents of the current edit scene matches type |CONTAINER|, 
             then the contents of this scene is copied to |c|. }*/
  {
    return get_objects(get_active_scene(), c);
  }
  
  template<class CONTAINER> bool get_objects(geo_scene sc, CONTAINER& c)
    /*{\Mopl  If the contents of scene |sc| matches type |CONTAINER|, 
             then the contents of scene |sc| is copied to |c|. }*/
  {
    if( sc ) return geowin_get_objects(*this, sc, c);
    else return false;
  }
  
  template <class CONTAINER>
  void get_selected_objects(GeoEditScene<CONTAINER>* sc, CONTAINER& cnt)
    /*{\Mopl  returns the selected objects of scene |sc| in container |cnt|.}*/  
  {
    geowin_get_selected_objects(*this, sc, cnt);
  }
#endif

  void edit();
  /*{\Mop starts the interactive mode of |\Mvar|. The operation returns 
         if either the $DONE$ or $Quit$ button was pressed. }*/

  bool edit(geo_scene sc);
  /*{\Mop  edits scene $sc$. Returns |false| if the Quit-Button was pressed,
          |true| otherwise. }*/
  

  /*{\Mtext
    \medskip
    {\bf b) Window Operations} }*/

  void init_menu();
  
  static void redraw_geowin(window* w, double x0, double y0, 
			    double x1, double y1);
  static void coord_handler(window*,double,double); 
  bool get_time_meas() { return time_meas; }

  void lock() { is_locked = true;}
  void unlock() { is_locked = false;}  
  
  void close() { Wp->close(); }
  /*{\Mop closes |\Mvar| .}*/
  
  double get_xmin() const;
  /*{\Mopl returns the minimal x-coordinate of the drawing area.}*/
  
  double get_ymin() const;
  /*{\Mopl returns the minimal y-coordinate of the drawing area.}*/  
  
  double get_xmax() const;
  /*{\Mopl returns the maximal x-coordinate of the drawing area.}*/
    
  double get_ymax() const;
  /*{\Mopl returns the maximal y-coordinate of the drawing area.}*/  

  void display(int x = window::center ,int y = window::center);
  /*{\Mop opens |\Mvar| at |(x,y)|. }*/
  
  window& get_window() const { return *Wp; }
  /*{\Mopl returns a reference to the drawing window. }*/
  
  void init(double xmin, double xmax, double ymin);
  /*{\Mopl     same as $window$::init($xmin$, $xmax$, $ymin$, $g$).}*/
  
  void init(double x1, double x2, double y1, double y2, int r=GEOWIN_MARGIN);
  /*{\Mopl inializes the window so that the rectangle with lower 
           left corner $(x1-r,y1-r)$ and upper right corner $(x2+r,y2+r)$
	   is visible. The window must be open. $GEOWIN\_MARGIN$ is a
	   default value provided by |\Mname|. }*/

  void redraw();
  /*{\Mopl redraws the contents of |\Mvar| (all visible scenes).}*/
  
  void redraw(double x0, double y0, double x1, double y1);
  /*{\Xopl redraws objects in the rectangle with lower 
           left corner $(x0,y0)$ and upper right corner $(x1,y1)$.}*/

  void update_status_line();
  
  void redraw_and_update_status_line();
  
  int  set_cursor(int cursor_id = -1) { return Wp->set_cursor(cursor_id); }
  /*{\Mopl sets the mouse cursor to $cursor\_id$. }*/


  /*{\Mtext
    \medskip
    {\bf c) Scene and scene group Operations} }*/

  void insert_scene(geo_scene sc);
  void remove(geo_scene sc);
  // removes scene |sc| from $GW$. Contents of |sc| will not be destroyed.
  
  void destroy(geo_scene sc);
  /*{\Mopl removes scene |sc| from $GW$ and destroys it. }*/

  geo_scene get_scene_with_name(string nm) const;
  /*{\Mopl returns the scene with name |nm| or nil if there is no scene
           with name |nm|.}*/
	   
  void   activate(geo_scene sc);
  /*{\Mopl  makes scene |sc| the active scene of |\Mvar|. }*/ 
  
  // operations for setting/ getting z - values for scenes
  
  bool get_redraw_z_order() const;
  
  bool set_redraw_z_order(bool b);
  
  int get_z(geo_scene sc) const;
  
  int set_z(geo_scene sc,int n);
  
  geo_scene get_active_scene() const;
  /*{\Mopl  returns the active scene of |\Mvar|. }*/ 
  
  bool is_active(geo_scene sc) const { return sc->get_active(); }
  /*{\Mopl returns true if |sc| is an active scene in a |\Mname|. }*/

  /*{\Mtext
    \medskip
    The following $get$ and $set$ operations can be used for retrieving and
    changing scene parameters. All $set$ operations return the previous 
    value. }*/
  
  bool get_algo_create_scenes() { return algo_create_scenes; }
  
  bool set_algo_create_scenes(bool b) { bool v = algo_create_scenes; algo_create_scenes = b; return v; }

  string get_name(geo_scene sc) const { return sc->get_name(); }
  /*{\Mopl returns the |name| of scene |sc|. }*/ 
  
  string get_name(geo_scenegroup gs) const { return gs->name; }
  /*{\Mopl returns the |name| of scene group |gs|. }*/   
    
  string set_name(geo_scene sc, string nm);
  /*{\Mopl  gives scene |sc| the name |nm|. If there is already
           a scene with name |nm|, another name is constructed
	   based on |nm| and is given to |sc|. The operation 
	   will return the given name.
 }*/ 
  
  color get_color(geo_scene sc) const;
  /*{\Mopl returns the boundary drawing color of scene |sc|. }*/

  color set_color(geo_scene sc, color c);
  /*{\Mopl sets the boundary drawing color of scene |sc| to |c|. }*/
  
  void set_color(geo_scenegroup gs, color c);
  /*{\Mopl sets the boundary drawing color of all scenes in group |gs| to |c|.}*/

  color get_selection_color(geo_scene sc) const { return get_color2(sc); }
  /*{\Mopl returns the boundary drawing color for selected objects
          of scene |sc|. }*/

  color set_selection_color(geo_scene sc, color c){ return set_color2(sc,c); }
  /*{\Mopl sets the boundary drawing color for selected objects
          of scene |sc| to |c|. }*/
	
  void set_selection_color(geo_scenegroup gs, color c);
  /*{\Mopl sets the boundary drawing color for selected objects
          of all scenes in |gs| to |c|. }*/  

  color get_color2(geo_scene sc) const;
  color set_color2(geo_scene sc, color c);

  color get_fill_color(geo_scene sc) const;
  /*{\Mopl returns the fill color of |sc|.}*/  
 
  color set_fill_color(geo_scene sc,color c);
  /*{\Mopl sets the fill color of |sc| to |c|. Use color $invisible$ 
           to disable filling.}*/ 

  void set_fill_color(geo_scenegroup gs, color c);
  /*{\Mopl sets the fill color of all scenes in |gs| to |c|. 
          Use color $invisible$ to disable filling.}*/   
	  
  color get_text_color(geo_scene sc) const;
  /*{\Mopl returns the text color of |sc|.}*/  
 
  color set_text_color(geo_scene sc,color c);
  /*{\Mopl sets the text color of |sc| to |c|.}*/ 

  void set_text_color(geo_scenegroup gs, color c);
  /*{\Mopl sets the text color of all scenes in |gs| to |c|.}*/	   

  int get_line_width(geo_scene sc) const { return sc->back_line_width; }
  /*{\Mopl returns the line width of scene |sc| .}*/

  int get_active_line_width(geo_scene sc) const 
  /*{\Mopl returns the active line width of |sc| .}*/
  { return sc->active_line_width; }
  
  int set_line_width(geo_scene sc,int w) 
  /*{\Mopl sets the line width for scene |sc| to |w|.}*/
  { int val=sc->back_line_width; sc->back_line_width=w; return val;}
  
  void set_line_width(geo_scenegroup gs,int w);
  /*{\Mopl sets the line width for all scenes in |gs| to |w|.}*/
  
  int set_active_line_width(geo_scene sc,int w) 
  /*{\Mopl sets the active line width of scene |sc| to |w|.}*/
  { int val=sc->active_line_width; sc->active_line_width=w; return val; }
  
  void set_active_line_width(geo_scenegroup gs,int w);
  /*{\Mopl sets the active line width for all scenes in |gs| to |w|.}*/  

  line_style get_line_style(geo_scene sc) const { return sc->l_style; }
  /*{\Mopl returns the line style of |sc|.}*/
  
  line_style set_line_style(geo_scene sc, line_style l) 
  /*{\Mopl sets the line style of scene |sc| to |l|.}*/
  { line_style val=sc->l_style; sc->l_style=l; return val; }
  
  void set_line_style(geo_scenegroup gs, line_style l);
  /*{\Mopl sets the line style of all scenes in |gs| to |l|.}*/  
  
  bool get_visible(geo_scene sc) const;
  /*{\Mopl returns the visible flag of scene |sc|. }*/
  
  bool set_visible(geo_scene sc, bool v);
  /*{\Mopl sets the visible flag of scene |sc| to |v|. }*/
  
  void set_visible(geo_scenegroup gs, bool v);
  /*{\Mopl sets the visible flag of all scenes in |gs| to |v|. }*/  
  
  void set_all_visible(bool v);
  /*{\Mopl sets the visible flag of all scenes that are 
          currently in |\Mvar| to |v|.}*/
  
  point_style get_point_style(geo_scene sc) const { return sc->p_style; }
  /*{\Mopl returns the point style of |sc|.}*/
  
  point_style set_point_style(geo_scene sc, point_style p) 
  /*{\Mopl sets the point style of |sc| to |p|}*/ 
  { point_style pold= sc->p_style; sc->p_style=p; return pold; }
  
  void set_point_style(geo_scenegroup gs, point_style p);
  /*{\Mopl sets the point style of all scenes in |gs| to |p|}*/   
  
  bool get_cyclic_colors(geo_scene sc) const { return sc->cyclic_colors; }  
  /*{\Mopl returns the cyclic colors flag for editable scene |sc|. }*/
  
  bool set_cyclic_colors(geo_scene sc, bool b) { bool old = sc->cyclic_colors; sc->cyclic_colors = b; return old; }  
  /*{\Mopl sets the cyclic colors flag for editable scene |sc|. If the cyclic colors
  flag is set, the new inserted objects of the scene get color |counter%16|, where
  counter is the object counter of the scene.}*/
  
  void set_cyclic_colors_counter(geo_scene sc, int c) 
  {sc->cyclic_colors_counter = c; }  
  
#ifdef __HAS_MEMBER_TEMPLATES__
  template<class T>    
  void set_handle_defining_points(GeoEditScene<T>* sc, geowin_defining_points gdp)
  { geowin_set_handle_defining_points(sc,gdp); } 
#endif

  /*{\Mtext
    \medskip
    The following operations can be used to set/get 
    individual attributes of objects in scenes.
    All set operations return the previous value.
    The first parameter is the scene, where the object belongs to.
    The second parameter is a generic pointer to the object.
    Precondition: the object belongs to the scene (is in the container
    of the scene).
  }*/
  
#ifdef __HAS_MEMBER_TEMPLATES__
  
  template<class T>
  color get_obj_color(GeoBaseScene<T>* sc, void* adr)
  /*{\Mopl returns the boundary color of the object at |(*adr)|.}*/
  { return sc->get_obj_color(adr); }

  template<class T>    
  color set_obj_color(GeoBaseScene<T>* sc, void* adr, color c)
  /*{\Mopl sets the boundary color of the object at |(*adr)| to |c|.}*/  
  { return sc->set_obj_color(adr,c); } 

  // -------------- new --------------
  template<class T>
  bool get_obj_color(GeoBaseScene<T>* sc, const __typename T::value_type& obj, color& c)
  /*{\Mopl if there is an object $o$ in the container of scene $sc$ with
  $o==obj$ the boundary color of $o$ is assigned to $c$ and $true$ is returned.
  Otherwise false is returned.
  }*/
  { 
    T& cnt = sc->get_objref();
    __typename T::iterator it;
    
    for(it=cnt.begin();it != cnt.end(); it++){
       if ((*it) == obj){
          __typename T::value_type& of = *it;
          c = sc->get_obj_color((void*)(&of));
	  return true;
       }
    }
    return false;
  }

  template<class T>    
  bool set_obj_color(GeoBaseScene<T>* sc, const __typename T::value_type& obj, color c)
  /*{\Mopl if there is an object $o$ in the container of scene $sc$ with
  $o==obj$ the boundary color of $o$ is set to $c$ and true will be
  returned. Otherwise false will be returned.}*/
  { 
    T& cnt = sc->get_objref();
    __typename T::iterator it;
    
    for(it=cnt.begin();it != cnt.end(); it++){
       if ((*it) == obj){
          __typename T::value_type& of = *it;
          sc->set_obj_color((void*)(&of),c);
	  return true;
       }
    }
    return false;  
  }
  // ---------------------------------

  template<class T>  
  color get_obj_fill_color(GeoBaseScene<T>* sc, void* adr)
  /*{\Mopl returns the interior color of the object at |(*adr)|.}*/ 
  { return sc->get_obj_fill_color(adr); }

  template<class T>  
  color set_obj_fill_color(GeoBaseScene<T>* sc, void* adr, color c)
  /*{\Mopl sets the interior color of the object at |(*adr)| to |c|.}*/    
  { return sc->set_obj_fill_color(adr,c); }  

  // -------------- new --------------
  template<class T>
  bool get_obj_fill_color(GeoBaseScene<T>* sc, const __typename T::value_type& obj, color& c)
  /*{\Mopl if there is an object $o$ in the container of scene $sc$ with
  $o==obj$ the interior color of $o$ is assigned to $c$ and $true$ is returned.
  Otherwise false is returned.
  }*/
  { 
    T& cnt = sc->get_objref();
    __typename T::iterator it;
    
    for(it=cnt.begin();it != cnt.end(); it++){
       if ((*it) == obj){
          __typename T::value_type& of = *it;
          c = sc->get_obj_fill_color((void*)(&of));
	  return true;
       }
    }
    return false;
  }

  template<class T>    
  bool set_obj_fill_color(GeoBaseScene<T>* sc, const __typename T::value_type& obj, color c)
  /*{\Mopl if there is an object $o$ in the container of scene $sc$ with
  $o==obj$ the interior color of $o$ is set to $c$ and true will be
  returned. Otherwise false will be returned.}*/
  { 
    T& cnt = sc->get_objref();
    __typename T::iterator it;
    
    for(it=cnt.begin();it != cnt.end(); it++){
       if ((*it) == obj){
          __typename T::value_type& of = *it;
          sc->set_obj_fill_color((void*)(&of),c);
	  return true;
       }
    }
    return false;  
  }
  // ---------------------------------
  
  template<class T>
  line_style get_obj_line_style(GeoBaseScene<T>* sc, void* adr)
  /*{\Mopl returns the line style of the object at |(*adr)|.}*/
  { return sc->get_obj_line_style(adr); }    

  template<class T>    
  line_style set_obj_line_style(GeoBaseScene<T>* sc, void* adr, line_style l)
  /*{\Mopl sets the line style of the object at |(*adr)| to |l|.}*/
  { return sc->set_obj_line_style(adr,l); }  
  
  // -------------- new --------------
  template<class T>
  bool get_obj_line_style(GeoBaseScene<T>* sc, const __typename T::value_type& obj, line_style& l)
  /*{\Mopl if there is an object $o$ in the container of scene $sc$ with
  $o==obj$ the line style of $o$ is assigned to $l$ and $true$ is returned.
  Otherwise false is returned.
  }*/
  { 
    T& cnt = sc->get_objref();
    __typename T::iterator it;
    
    for(it=cnt.begin();it != cnt.end(); it++){
       if ((*it) == obj){
          __typename T::value_type& of = *it;
          l = sc->get_obj_line_style((void*)(&of));
	  return true;
       }
    }
    return false;
  }

  template<class T>    
  bool set_obj_line_style(GeoBaseScene<T>* sc, const __typename T::value_type& obj, line_style l)
  /*{\Mopl if there is an object $o$ in the container of scene $sc$ with
  $o==obj$ the line style of $o$ is set to $l$ and true will be
  returned. Otherwise false will be returned.}*/
  { 
    T& cnt = sc->get_objref();
    __typename T::iterator it;
    
    for(it=cnt.begin();it != cnt.end(); it++){
       if ((*it) == obj){
          __typename T::value_type& of = *it;
          sc->set_obj_line_style((void*)(&of),l);
	  return true;
       }
    }
    return false;  
  }
  // ---------------------------------

  template<class T>  
  int get_obj_line_width(GeoBaseScene<T>* sc, void* adr)
  /*{\Mopl returns the line width of the object at |(*adr)|.}*/
  { return sc->get_obj_line_width(adr); }   

  template<class T>    
  int set_obj_line_width(GeoBaseScene<T>* sc, void* adr, int w)  
  /*{\Mopl sets the line width of the object at |(*adr)| to |w|.}*/
  { return sc->set_obj_line_width(adr,w); }    

  // -------------- new --------------
  template<class T>
  bool get_obj_line_width(GeoBaseScene<T>* sc, const __typename T::value_type& obj, int& l)
  /*{\Mopl if there is an object $o$ in the container of scene $sc$ with
  $o==obj$ the line width of $o$ is assigned to $l$ and $true$ is returned.
  Otherwise false is returned.
  }*/
  { 
    T& cnt = sc->get_objref();
    __typename T::iterator it;
    
    for(it=cnt.begin();it != cnt.end(); it++){
       if ((*it) == obj){
          __typename T::value_type& of = *it;
          l = sc->get_obj_line_width((void*)(&of));
	  return true;
       }
    }
    return false;
  }

  template<class T>    
  bool set_obj_line_width(GeoBaseScene<T>* sc, const __typename T::value_type& obj, int l)
  /*{\Mopl if there is an object $o$ in the container of scene $sc$ with
  $o==obj$ the line width of $o$ is set to $l$ and true will be
  returned. Otherwise false will be returned.}*/
  { 
    T& cnt = sc->get_objref();
    __typename T::iterator it;
    
    for(it=cnt.begin();it != cnt.end(); it++){
       if ((*it) == obj){
          __typename T::value_type& of = *it;
          sc->set_obj_line_width((void*)(&of),l);
	  return true;
       }
    }
    return false;  
  }
  // ---------------------------------
    
  template<class T>
  void reset_obj_attributes(GeoBaseScene<T>* sc)
  /*{\Mopl deletes all individual attributes of objects in scene |(*sc)|.}*/
  { sc->undefine_all(); }
  

#endif
  
  void set_active(geo_scene sc,bool ac) { sc->set_active(ac); }
  
  /*{\Mtext
    \medskip
    {\bf d) Input and Output Operations} }*/
    
  void read(geo_scene sc,istream& is) { sc->read(is,false); }
  /*{\Mopl reads the contents of |sc| from input stream |is|.
           Before the contents of |sc| is cleared.
  }*/

  void write(geo_scene sc,ostream& os) { sc->write(os,string("")); }
  /*{\Mopl writes the contents of |sc| to output stream |os|. }*/
  
  void write_active_scene(ostream& os) { if (cur) cur->write(os,string("")); }
  /*{\Mopl writes the contents of the active scene of |\Mvar|
          to output stream |os|. }*/  
  
  void read_scene(string filename);
  /*{\Xopl  reads file $filename$. The file must be written by
            write\_to\_file() and must contain objects of the
	    same type the currently edited scene has, if there
	    is one. Then the contents of file |filename| will
	    become the contents of the currently edited scene.
	    If there is no currently edited scene, a new scene
	    will be created and the contents of file |filename| will
	    become the contents of this scene.
	    
 }*/
  void write_scene(string filename);
  /*{\Xopl  writes the contents of the active scene of |\Mvar| to file 
            $filename$.
	    }*/

  void write_scene(geo_scene sc, string filename,bool check_file_exists = true);
  /*{\Xopl  writes the contents of scene |sc| of |\Mvar| to file 
            $filename$.
	    }*/
  /*{\Mtext
    \medskip
    {\bf e) View Operations} }*/

  void   zoom_up();
  /*{\Mopl The visible range is reduced to the half. }*/
  void   zoom_down();
  /*{\Mopl The visible range is doubled. }*/
  void   zoom_area();

  void   adjust_zoom_rect(double& x0, double& y0, double& x1, double& y1) ;
  void   adjust_zoom_rect(double  x0, double  y0, double  x,  double  y, double& x1, double& y1, double& x2, double& y2);

  void fill_window();
  /*{\Mopl changes window coordinate system, so that the objects of the 
           currently active scene fill the window. }*/

  void reset_window();
  // resets the visible range to the values that where current when constructing |\Mvar| 

  string get_bg_pixmap() const { return bg_pixmap; }
  /*{\Mopl returns the name of the current background pixmap.}*/
  	    
  string set_bg_pixmap(string pix_name); 	  
  /*{\Mopl changes the window background pixmap to pixmap with name |pix_name|.
           Returns the name of the previous background pixmap.
  }*/
  
  color get_bg_color() const;
  /*{\Mopl returns the current background color.}*/
  
  color set_bg_color(const color& c);
  /*{\Mopl sets the background color to |c| and returns its previous value.}*/
  
  bool  get_show_grid() const;
  /*{\Mopl returns true, if the grid will be shown, false otherwise.}*/
  
  bool  set_show_grid(bool sh);
  /*{\Mopl sets the show grid flag to |sh| and returns the previous value.}*/
  
  double  get_grid_dist() const;
  /*{\Mopl returns the grid width parameter.}*/
  
  double  set_grid_dist(double g);
  /*{\Mopl sets the grid width parameter to |g| and returns the previous value.}*/

  grid_style  get_grid_style() const;
  /*{\Mopl returns the grid style parameter.}*/
  
  grid_style  set_grid_style(grid_style g);
  /*{\Mopl sets the grid style parameter to |g| and returns the previous value.}*/  
  
  bool  get_show_position() const;
  /*{\Mopl returns true, if the mouse position will be shown, false otherwise.}*/
  
  bool  set_show_position(bool sp);
  /*{\Mopl sets the show position flag to |sp| and returns the previous value.}*/  
  
  // parameters for d3 output
  
  bool get_d3_elimination() const;
  
  bool set_d3_elimination(bool b);
  
  bool get_d3_solid() const;
  
  bool set_d3_solid(bool b);  

  int get_d3_animation_speed() const;
  
  int set_d3_animation_speed(int s);
  
  bool get_show_d3_edges() const;
  
  bool set_show_d3_edges(bool b);
  
  double get_d3_z_value() const { return gw_d3_zvalue; }
  
  double set_d3_z_value(double zn) { double old = gw_d3_zvalue; gw_d3_zvalue = zn; return old; }
  
  void select(const point&);
  void select_all();
  void select();
  void unselect();

   
  /*{\Mtext
    \medskip
    {\bf f) Handling of events} 

   \Mname provides operations for changing its default handling of events. 
   As in |GraphWin| (cf. \ref{Graph Windows}) the user can define what 
   action should follow a mouse or key event. Constants are defined as in 
   |GraphWin| : 
   \begin{itemize}
   \item  A\_LEFT  (left mouse-button)
   \item  A\_MIDDLE (middle mouse-button)
   \item  A\_RIGHT (right mouse-button)
   \item  A\_SHIFT (shift-key)
   \item  A\_CTRL (control-key)
   \item  A\_ALT (alt-key)
   \item  A\_DOUBLE (double click)
   \item  A\_DRAG (button not released)
   \item  A\_IMMEDIATE (do it immediatly without dragging or double click 
   check)
   \item  A\_OBJECT (editable object at mouse position).
   \end{itemize}
   and can be combined with OR ( \vline\ ).
   }*/
  
  
  void set_action(long mask, geo_action f=0);
  /*{\Mopl  set action on condition $mask$ to $f$. |geo_action| is a
            function of type |void (*)(GeoWin&, const point&)|. 
            For |f == 0| the corresponding action is deleted. }*/
  
  geo_action get_action(long mask);
  /*{\Mopl  get action defined for condition $mask$.  }*/
  
  void reset_actions();
  /*{\Mopl	set all actions to their default values. }*/

  
  /*{\Mtext    
    \medskip
    Default values are defined as follows :
    \begin{itemize}
    \item A\_LEFT   or   A\_LEFT \vline\ A\_OBJECT \newline
    read a new object at mouse position.
    \item A\_LEFT \vline\ A\_DRAG    \newline       scrolling the window.
    \item A\_LEFT \vline\ A\_DRAG \vline\ A\_OBJECT \newline move the object.
    \item A\_LEFT \vline\ A\_CTRL \newline 
    pin current scene at mouse position or delete the pin point if 
    it is currently there. 
    \item A\_MIDDLE \vline\  A\_OBJECT \newline
    toggle the selection state of the object at mouse position.
    \item A\_MIDDLE \vline\ A\_DRAG 
    \newline  toggle the selection state of the objects in the dragging area.
    \item A\_RIGHT \vline\  A\_IMMEDIATE \newline
    set the options of the currently active scene.
    \item A\_RIGHT \vline\  A\_IMMEDIATE \vline\  A\_OBJECT \newline
    opens a menu for the object at mouse position.
    \end{itemize}
    }*/


  void clear_actions();
  /*{\Mopl	clears all actions. }*/
  
  /*{\Mtext
    \medskip
     {\bf Scene events}
     
     The following event handling functions can be set for
     edit scenes:
     \begin{itemize}
     \item Pre add handler
     \item Pre add change handler
     \item Post add handler
     \item Pre delete handler
     \item Post delete handler
     \item Start, Pre, Post and End change handler
  
     \end{itemize}
     
     The add handlers will be called when a user tries to add an object
     to an edit scene in GeoWin, the delete handlers will be called when
     the user tries to delete an object and the change handlers will be
     called when the user tries to change an object (for instance by moving
     it).
     The templated set operations for setting handlers uses member templates. 
     If your compiler does not support member templates, you should use instead
     the templated functions |geowin_set_HANDLER|, where |HANDLER| is one the
     following handlers. 
     All handling functions get as the first parameter a reference to the 
     |\Mname|, where the scene belongs to.
         
  }*/
  
#ifdef __HAS_MEMBER_TEMPLATES__
  
  // add handler
  
  template<class T,class F>
  bool set_pre_add_handler(GeoEditScene<T>* sc, F handler)
  /*{\Mopl sets the handler that is called before an object is added to |(*sc)|.
  |handler| must have type |bool (*handler)(GeoWin&, const T::value_type &)|.
  |handler| gets a reference to the added object. If |handler| returns false, 
  the object will not be added to the scene.}*/
  { return geowin_set_pre_add_handler(sc,handler); }
  
  template<class T,class F>
  bool set_pre_add_change_handler(GeoEditScene<T>* sc, F handler )
  // handler: bool (*handler)(GeoWin&, const T::value_type &, T::value_type &)
  { return geowin_set_pre_add_change_handler(sc,handler); }
  
  template<class T,class F>
  bool set_post_add_handler(GeoEditScene<T>* sc, F handler)
  /*{\Mopl sets the handler that is called after an object is added to |(*sc)|. 
  |handler| must have type |void (*handler)(GeoWin&, const T::value_type &)|.
  |handler| gets a reference to the added object.
  }*/
  { return geowin_set_post_add_handler(sc,handler); }

  // delete handler
    
  template<class T,class F>
  bool set_pre_del_handler(GeoEditScene<T>* sc, F handler)
  /*{\Mopl sets the handler that is called before an object is 
          deleted from |(*sc)|.
  |handler| must have type |bool (*handler)(GeoWin&, const T::value_type &)|.
  |handler| gets a reference to the added object. If |handler| returns true, the object
  will be deleted, if |handler| returns false, the object will not be deleted.}*/
  { return geowin_set_pre_del_handler(sc,handler); }
  
  template<class T,class F>
  bool set_post_del_handler(GeoEditScene<T>* sc, F handler)
  /*{\Mopl sets the handler that is called after an object is 
          deleted from |(*sc)|.
  |handler| must have type |void (*handler)(GeoWin&, const T::value_type &)|.
  }*/
  { return geowin_set_post_del_handler(sc,handler); }
  
  // change handler
  
  template<class T,class F>
  bool set_start_change_handler(GeoEditScene<T>* sc, F handler)
  /*{\Mopl sets the handler that is called when a geometric object from |(*sc)| 
  starts changing (for instance when you move it or rotate it).
  |handler| must have type |bool (*handler)(GeoWin&, const T::value_type &)|.
  The handler function gets a reference to the object.
  }*/
  { return geowin_set_start_change_handler(sc,handler); }

  template<class T,class F>
  bool set_pre_move_handler(GeoEditScene<T>* sc, F handler)
  /*{\Mopl sets the handler that is called before every move operation.
  |handler| must have type |bool (*handler)(GeoWin&, const T::value_type &, double x, double y)|. 
   The handler gets as the second parameter a reference to the object, as the third parameter
   and fourth parameter the move vector.
   If the handler returns true, the change operation will be executed, if the handler
   returns false, it will not be executed. 
 }*/
  { return geowin_set_pre_move_handler(sc,handler); }  
  
  template<class T,class F>
  bool set_post_move_handler(GeoEditScene<T>* sc, F handler)
  /*{\Mopl sets the handler that is called after every move operation.
  |handler| must have type |void (*handler)(GeoWin&, const T::value_type &, double x, double y)|. 
  The handler gets as the second parameter a reference to the object, as the third parameter
  and fourth parameter the move vector.  
  }*/
  { return geowin_set_post_move_handler(sc,handler); }
 
  template<class T,class F>
  bool set_pre_rotate_handler(GeoEditScene<T>* sc, F handler)
  /*{\Mopl sets the handler that is called before every rotate operation.
  |handler| must have type |bool (*handler)(GeoWin&, const T::value_type &, double x, double y, double a)|. 
   If the handler returns true, the rotate operation will be executed, if the handler
   returns false, it will not be executed. 
 }*/
  { return geowin_set_pre_rotate_handler(sc,handler); }  
  
  template<class T,class F>
  bool set_post_rotate_handler(GeoEditScene<T>* sc, F handler)
  /*{\Mopl sets the handler that is called after every rotate operation.
  |handler| must have type |void (*handler)(GeoWin&, const T::value_type &, double x, double x, double a)|. 
  }*/
  { return geowin_set_post_rotate_handler(sc,handler); } 
  
  template<class T,class F>
  bool set_end_change_handler(GeoEditScene<T>* sc, F handler)
  /*{\Mopl sets the handler that is called when a geometric object from |(*sc)| 
  ends changing.  |handler| gets the object as the second parameter.
  |handler| must have type |void (*handler)(GeoWin&, const T::value_type &)|.}*/
  { return geowin_set_end_change_handler(sc,handler); }

  /*{\Mtext
    \medskip
     {\bf Generator functions:}
     The following operation can be used to set a generator function for an edit scene.
     The operation uses member templates. 
     If your compiler does not support member templates, you should use instead
     the templated function |geowin_set_generate_fcn|. 
 }*/
     
  template<class T>
  bool set_generate_fcn(GeoEditScene<T>* sc, void (*f)(GeoWin& gw,T& L))
  /*{\Mopl sets the generator function for edit scene |(*sc)|. 
           The function gets the GeoWin where |(*sc)| belongs to and
	   a reference to the container |L| of |(*sc)|. The function
	   should write the generated objects to |L|.
  }*/
  { return geowin_set_generate_fcn(sc,f); }
  
  template<class T,class T2>
  bool set_edit_object_fcn(GeoEditScene<T>* sc, T2 f)  
  { return geowin_set_edit_object_fcn(sc,f); }  
  
  
  template<class T>
  bool add_buffer_fcn(GeoEditScene<T>* sc, void (*f)(GeoWin&, list<__typename T::value_type>&), const char* name)  
  {
    return geowin_add_buffer_fcn(sc,f,name);
  }
  
  template<class S, class R>
  bool set_copy_attr_test_fcn(GeoResultScene<S,R>* sc, \
                              bool (*f)(color&,color&,line_style&,int&,__typename S::iterator&,__typename R::iterator&, int))
  {
    return geowin_set_copy_attr_test_fcn(sc,f);
  }
  
  /*{\Mtext
    \medskip
     {\bf Input objects:}
     The following operation can be used to set an input object for an edit scene.
     The operation uses member templates. 
     If your compiler does not support member templates, you should use instead
     the templated functions prefixed with  $geowin$.
     A GeoInputObject\<GeoObj\> has the following virtual functions:
     
        void operator()(GeoWin\&\ gw, list\<GeoObj\>\&\ L);
	
     This virtual function is called for the input of objects. The new objects have to be
     returned in $L$.
    
        void options(GeoWin\&\ gw);   
	
     This function is called for setting options for the input object.
     
 }*/
     
  template<class T>
  bool set_input_object(GeoEditScene<T>* sc, const GeoInputObject<__typename T::value_type>& obj, string name)
  /*{\Mopl sets the input object |obj| for edit scene |(*sc)|. 
           The function gets the GeoWin where |(*sc)| belongs to and
	   a reference to a list |L|. The function must write the new objects to |L|.
  }*/
  { return geowin_set_input_object(sc,obj,name); }  
  
  template<class T>
  bool add_input_object(GeoEditScene<T>* sc, const GeoInputObject<__typename T::value_type>& obj, string name)
  /*{\Mopl  adds the input object |obj| to the list of available input 
           objects of edit scene |(*sc)| without setting |obj| as input object.

  }*/
  { return geowin_add_input_object(sc,obj,name); }
  
  // draw function
  
  template<class T>
  void set_draw_object_fcn(GeoBaseScene<T>* sc, window& (*fcn)(window&, const __typename T::value_type &, int w))
  /*{\Mopl  sets a function |fcn| for scene |(*sc)| that will be called for drawing the
            objects of scene |(*sc)|. If no such function is set (the default), the
	    output operator is used.
  }*/
  { geowin_set_draw_object_fcn(sc,fcn); }

#endif

  void set_draw_object_parameters(geo_scene sc,const list<string>& LS)
  { sc->draw_object_parameters = LS; }

  void set_quit_handler(bool (*f)(const GeoWin& gw));
  /*{\Mopl sets a handler function |f| that is called when the user 
          clicks the
          quit menu button. |f| should return true for allowing quiting,
	  false otherwise. }*/
  
  void set_done_handler(bool (*f)(const GeoWin& gw)); 
  /*{\Mopl sets a handler function |f| that is called when the user clicks
          the
          done menu button. |f| should return true for allowing quiting,
	  false otherwise. }*/
  
  /*{\Mtext
    \medskip
    {\bf g) Scene Group Operations\\} 
    |GeoWin| can manage scenes in groups. It is possible to add and remove
    scenes to/from groups.
    Various parameters and dependences can be set for whole groups.
    Note that |geo_scenegroup| is a pointer to a scene group.
 }*/
 

  geo_scenegroup new_scenegroup(string name);
  /*{\Mopl Creates a new scene group with name |name| and returns a pointer
           to it.
  }*/

  geo_scenegroup new_scenegroup(string name, const list<geo_scene>& LS);
  /*{\Mopl Creates a new scene group |name| and adds the scenes in |LS|
           to this group.
  }*/
  
  void insert(geo_scenegroup GS, geo_scene sc);
  /*{\Mopl adds |sc| to scene group |GS| .
  }*/
  
  bool del(geo_scenegroup GS, geo_scene sc);
  /*{\Mopl removes |sc| from scene group |GS| and returns true, if the operation
           was succesful (false: |sc| was not in |GS|).
  }*/
    
  /*{\Mtext
    \medskip
    {\bf h) Further Operations} }*/

  double get_mfct() { return mouse_fct; }
  void init_data(geo_scene sc) { sc->init_data(); }

  bool get_debug_mode(geo_scene sc) const
  { return sc->debug_mode; }
    
  bool set_debug_mode(geo_scene sc,bool mode)
  { bool rt = sc->debug_mode;
    sc->debug_mode=mode;
    return rt; 
  }
  
  int set_button_width(int w);
  /*{\Mopl sets the width of the scene visibility buttons in |\Mvar| and
  returns the previous value.}*/
  
  int set_button_height(int h);
  /*{\Mopl sets the height of the scene visibility buttons in |\Mvar| and
  returns the previous value.}*/  
  
  /*{\Mtext    
    \medskip
  You can associate a) buttons with labels or b) bitmap buttons with the visibility
  of a scene in GeoWin. You cannot use a) and b) at the same time.
  The following operations allow you to use add such visibility buttons to GeoWin.
  Note that before setting bitmap buttons with the |set_bitmap| operation you have to
  set the button width and height.}*/
  
  void set_label(geo_scene sc, string label);
  /*{\Mop associates a button with label |label| with the visibility of scene |sc|.}*/
  
  void set_bitmap(geo_scene sc, unsigned char* bitmap);
  /*{\Mop associates a button with bitmap |bitmap| with the visibility of scene |sc|.}*/ 
  
  void set_activate_bitmap(geo_scene sc, unsigned char* bitmap);
  
  void  add_scene_buttons(const list<geo_scene>& Ls, const list<string>& Ln);
  /*{\Mopl add a multiple choice panel for visibility of the scenes in $Ls$ to |\Mvar|.
  The button for the n-th scene in $Ls$ gets the n-th label in $Ln$.}*/

  
  void  add_scene_buttons(const list<geo_scene>& Ls, int w, int h, unsigned char** bm);
  /*{\Mopl add a multiple choice panel for visibility of the scenes in $Ls$ to |\Mvar|.
  The button for the n-th scene in $Ls$ gets the n-th bitmap in $bm$. The bitmaps have
  width $w$ and height $h$.}*/
  
  list<geo_scene> get_scenes() { return scenes; }
  /*{\Mopl  returns the scenes of |\Mvar|.}*/
  
  list<geo_scenegroup> get_scenegroups() { return scene_groups; }
  /*{\Mopl  returns the scene groups of |\Mvar|.}*/  
  
  list<geo_scene> get_scenes(geo_scenegroup gs) { return gs->group_members; }
  /*{\Mopl  returns the scenes of group |gs|.}*/
  
  list<geo_scene> get_visible_scenes();
  /*{\Mopl  returns the visible scenes of |\Mvar|.}*/
 
  void add_dependence(geo_scene sc1, geo_scene sc2) { sc1->add_dependence(sc2);}
  /*{\Mopl makes |sc2| dependent from |sc1|. That means that |sc2|
           will be updated when the contents of |sc1| changes. }*/

  void del_dependence(geo_scene sc1, geo_scene sc2) { sc1->del_dependence(sc2);}
  /*{\Mopl deletes the dependence of scene |sc2| from |sc1|. }*/

  void set_frame_label(const char* label) { Wp->set_frame_label(string(label)); }
/*{\Mopl   makes |label| the frame label of |\Mvar|. }*/


  int open_panel(panel& P);
  /*{\Mopl displays panel |P| centered on the drawing area of |\Mvar|,
           disabels the menu bar of |\Mvar| and returns the result of
	   |P.open()|.}*/
           
  
  int open_panel(file_panel& P);
  
  // node  and edge color maps ...
  map<node,color>& get_node_color_map() { return node_color_map; }
  map<edge,color>& get_edge_color_map() { return edge_color_map; }
  
  // add additional objects to scenes ...
  // returns the list item of the added object
  
 /*{\Xtext
    \medskip
    {\bf Additional objects} 
 }*/  
  
  list_item add_remark(geo_scene sc,double x,double y,string rem);
  list_item add_remark(geo_scene sc,double x,double y,double wd,string rem);
  
  void enable_menus();
  /*{\Mopl enables the menus of |\Mvar|.}*/
  
  void disable_menus();
  /*{\Mopl disables the menus of |\Mvar|, but not the |User| menu.}*/
 
  double version();
  /*{\Mopl returns the |GeoWin| version number.}*/
  
  double fileformatversion();

  void message(string msg);
  /*{\Mopl displays message |msg| on top of the drawing area.
          If |msg| is the empty string, a previously written
	  message is deleted.
  }*/

  void msg_open(string msg);
  /*{\Mopl displays message |msg| in the message window of |\Mvar| .
      If the message window is not open, it will be opened.
  }*/
  
  void   msg_close() { if(msg_win->is_open()) msg_win->close(); }
  /*{\Mopl closes the message window.}*/
  void   msg_clear() { if(msg_win->is_open()) msg_win->del_messages(); }
   /*{\Mopl clears the message window.}*/

  geowin_redraw* set_redraw_pt(geo_scene sc,geowin_redraw* rd)
  { geowin_redraw* old=sc->redraw_pt;
    sc->redraw_pt=rd; return old;
  }
  
  geowin_redraw* get_redraw_pt(geo_scene sc);

  void   show_d3();
  void   hide_d3();

  void   set_d3_fcn(geo_scene sc, void (*f)(geo_scene gs, d3_window& W, GRAPH<d3_point,int>& H)) 
  /*{\Mopl sets a function for computing 3d output. The parameters of the function are
  the |geo_scene| for that it will be set and a function pointer. The function |f| will get the scene
  for that it was set and the reference to a |d3_window| that will be the output window.
  }*/
  { sc->init_d3_window = f; }
  
  D3_FCN  get_d3_fcn(geo_scene sc)
  /*{\Mopl returns the function for computing 3d output that is set for scene |sc|.
  The returned function has pointer type |void (*)(geo_scene, d3_window&, GRAPH<d3_point,int>&)|.}*/
  { return sc->init_d3_window; }
  
  /*{\Mtext    
    \medskip
    \Mname can be pined at a point in the plane. As standard behavior it is
    defined that moves of geometric objects will be rotations around the
    pin point. }*/
    
  void draw_pin();

  bool get_pin_point( point& p ) const;
  /*{\Mopl returns the pin point in $p$ if it is set.}*/
  void set_pin_point( point  p );
  /*{\Mopl sets the pin point to $p$.}*/
  void del_pin_point( ); 
 /*{\Mopl deletes the pin point.}*/
 
  int add_call(GeoFunctions* f, string label, window* m = 0);
  /*{\Xopl adds a menu item $label$ to menu |m| of $gw$. 
           If |m| points to |0| the "User" Menu is choosen.}*/

  int add_button_call(GeoFunctions* f, string label, window* w = 0, char* m = 0);
  /*{\Xopl adds a menu button to  $gw$. 
           |m| is the pixmap of the button.}*/

  void add_help_text(string name) { help_list.append(name); }
  /*{\Mop  adds the help text contained in |name.hlp| with label |name|
           to the help menu of the main window. The file |name.hlp| must
           exist either in the current working directory or in
           |\$LEDAROOT/incl/Help|. Note that this operation must be called
           before |gw.display()|. }*/

#ifdef __HAS_MEMBER_TEMPLATES__

  /*{\Mtext
    \medskip
    The templated |add_user_call| operation uses member templates. If your 
    compiler does not support member templates, you should use instead
    the templated function |geowin_add_user_call| with
    |\Mvar| as an additional first parameter.
    
 }*/
  
  template<class F> void add_user_call(string label, F f)
   /*{\Mopl  adds a menu item $label$ to the "User" menu of $GW$. 
             User defined function |geo_call(GeoWin& gw, F f, string label)| 
	     is called whenever this menu button was pressed. This menu 
	     definition has to be finished before $GW$ is opened. }*/
  {
    geowin_add_user_call(*this, label, f);
  }
#endif 
 
};

// removed from templates ...

extern _exportF bool geowin_show_options2(GeoScene* scn,panel* p,GeoWin *gw,color& filling_color,
                                     bool& high_light,bool fredraw, list<string> fnames, 
				     int& number, geowin_defining_points& hdp);
extern _exportF void mouse_pos(long& MASK,GeoWin* gw, bool b);

class _exportC GeoProp {
  protected:
  
  geo_scene prop_my_scene;

  map<void*, void*> * original; 

  // color of the boundary of the object :
  map<void*, color>* color1_map;

  // color of the interior of the object :
  map<void*, color>* color2_map;

  map<void*, line_style>* lst_map;  
  map<void*, int>* lw_map;

  // labels for the objects
  map<void*, string>* label_map;
  
  GeoProp();

public:

  // Methods on colormap1 :
  bool colors_defined1()  { return  color1_map != 0; }

  void undefine_colors1() { if(color1_map) delete color1_map; color1_map = 0;}

  color get_obj_color(void* o); 
  color  set_obj_color(void* obj, color c);

  // Methods on colormap2 :
  bool colors_defined2()  { if (color2_map==NULL) return false; else return true; }
  void undefine_colors2() { if(color2_map) delete color2_map; color2_map = 0; }

  color get_obj_fill_color(void* o);
  color set_obj_fill_color(void* obj, color c);
  
  // Methods on line_style_map :
  bool line_styles_defined()   { if (lst_map==NULL) return false; else return true; }
  void undefine_line_styles()  { if(lst_map) delete lst_map; lst_map = 0; }

  line_style get_obj_line_style(void* o);
  line_style set_obj_line_style(void* obj, line_style lst);

  // Methods on line_width_map :
  bool line_width_defined()   { if (lw_map==NULL) return false; else return true; }
  void undefine_line_width()  { if(lw_map) delete lw_map; lw_map = 0; }

  int get_obj_line_width(void* o);
  int set_obj_line_width(void* obj, int w);

  // methods on label_map
  bool labels_defined()   { if (label_map==NULL) return false; else return true; }
  void undefine_labels()  { 
   if(label_map) delete label_map; 
   label_map = 0; 
  }

  bool get_obj_label(void* o,string& label);
  void set_obj_label(void* obj, string label);
  
  void setup_focus_dialog(window&,void*);

  void set_original_properties(void* other, void* orig);

  void set_def_properties(void* o);

  void original_properties(void* o);
  
  void set_default_properties(void* o);

  void undefine_all();
 
  int keyboard_panel(window& w, string& nval);
  
  int focus_dialog(string& nval, window& w);

  color oldcl;
  color oldfl;
  line_style old_ls;
  int oldw;
  color text_clr;
  point_style old_ps;
  
  void set_window_params(window& w, void* adr, PresentationType pt);

  void restore_window_params(window& w);
  
  void set_ps_params(ps_file& F, void* adr);

};

template<class T> class _exportC GeoTEditScene : public GeoEditor, public GeoProp
{  
  protected :
  
  bool (*box_intersection_fcn)(const T& , double, double, double, double,bool);
  void (*get_bounding_box_fcn)(const T&, double&, double&, double&, double&);

  void (*move_fcn)(T& obj, double, double);
  void (*rotate_fcn)(T& obj, double, double, double);

  public :

  void (*move_point_fcn)(T&, double, double, int);
  bool obj_defining_points_change;
  int obj_pnr;
  
  // alternative draw function
  //window& (*draw_fcn)(window&, const T&);
  void* draw_fcn;
  
  // handler function
  bool (*pre_add_fcn)(GeoWin&, const T&);
  bool (*pre_add_changer)(GeoWin&, const T&, T&);
  void (*post_add_fcn)(GeoWin&, const T&);
  
  bool (*pre_del_fcn)(GeoWin&, const T&);
  void (*post_del_fcn)(GeoWin&, const T&);
  
  bool (*start_change_fcn)(GeoWin&, const T&);
  
  bool (*pre_move_fcn)(GeoWin&, const T&, double x, double y);
  void (*post_move_fcn)(GeoWin&, const T&, double x, double y);

  bool (*pre_rotate_fcn)(GeoWin&, const T&, double x, double y, double a);
  void (*post_rotate_fcn)(GeoWin&, const T&, double x, double y, double a);  
  
  void (*end_change_fcn)(GeoWin&, const T&);

  
  GeoTEditScene() : GeoEditor(), GeoProp() 
  {
   draw_fcn = 0;
    
   box_intersection_fcn = 0;
   get_bounding_box_fcn = 0;
   move_fcn = 0;
   rotate_fcn = 0;
    
   pre_add_fcn = 0;
   pre_add_changer = 0;
   post_add_fcn = 0;
   pre_del_fcn = 0;
   post_del_fcn = 0;
   start_change_fcn = 0;
   pre_move_fcn = 0;
   post_move_fcn = 0;
   pre_rotate_fcn = 0;
   post_rotate_fcn = 0;
   end_change_fcn = 0;
  } 

  void move_point(T& t, double dx, double dy)
  { if (move_point_fcn) move_point_fcn(t,dx,dy,obj_pnr); }
  
 
  T read_object(istream& is)          { T t; is >> t; return t; }
  void write_object(ostream& os, T t) { os << t; }
  
  void move (T& t,  double dx, double dy)
  { if (move_fcn) move_fcn(t, dx, dy);  }

  void rotate (T& t,  double x, double y, double alpha)
  { if (rotate_fcn) rotate_fcn(t, x, y, alpha); }
  
  void set_box_intersection_fcn(bool (*f)(const T& , double, double, 
					  double, double,bool))
  { box_intersection_fcn = f; }
  
  void set_get_bounding_box_fcn(void (*f)(const T&, double&, double&, 
					  double&, double&))
  { get_bounding_box_fcn = f; }

  void set_move_fcn(void (*f)(T&, double, double))
  { move_fcn = f; }
  
  void set_rotate_fcn(void (*f)(T&, double, double, double))
  { rotate_fcn = f;}
};

template<class iterator>  struct _exportC geo_object_properties
{
  // class defines properties of edited objects
  iterator    pos;         // position in edited container
  list_item   selected;    // nil if the object is not selected, 
                           // position in list of selected objects otherwise
  
  geo_object_properties(const geo_object_properties& gp)
    : pos(gp.pos), selected(gp.selected){}
  
  geo_object_properties(iterator it) 
    : pos(it), selected(nil) {}
  
  geo_object_properties() : pos(), selected(nil){}
  
  geo_object_properties(iterator it, list_item lit)
    : pos(it), selected(lit) {}

  LEDA_MEMORY(geo_object_properties);
};


// **************************************************************************
// ****************     class GeoBaseScene      *********************
// every builder builds a prototype


template<class T> class GeoBaseScene;
template<class T> class GeoBaseSceneBuilder : public GeoSceneBuilder
{
  friend class GeoBaseScene<T>;

  public :
  
  GeoBaseSceneBuilder() 
    : GeoSceneBuilder(new GeoBaseScene<T>)  { }
};

template<class T> 
GeoBaseScene<T>* make_base_prototype(T* t, string str);
template<class T> 
GeoBaseScene<T>* get_base_prototype(T* t);


template<class T> class GeoBaseScene : public GeoScene, public GeoTEditScene<__typename T::value_type>
{  
  protected :

  typedef __typename T::iterator                iterator;
  typedef __typename T::value_type              GeoObj;
  typedef geo_object_properties<iterator>       geo_props;
  typedef window& (*FUNC3) (window&, const GeoObj&, int);
  
  friend GeoBaseScene<T>* make_base_prototype __temp_friend_decl(T* t, string str);
  friend GeoBaseScene<T>* get_base_prototype __temp_friend_decl (T* t);

  friend class GeoBaseSceneBuilder<T>;
  friend class _exportC GeoWin;
  
public:

#ifdef NO_STATIC_DATA_MEMBER
  
  static GeoBaseSceneBuilder<T>& b1()
  {
    static GeoBaseSceneBuilder<T> sb1;
    return sb1;
  }

#else
  
  static GeoBaseSceneBuilder<T> sb1;
  static GeoBaseSceneBuilder<T>& b1()
  {
    return sb1;
  }
#endif

  T*                     objs;    //dataobject to display
  geowin_redraw_container<T>* gw_redraw_cnt;
  
  string (*info_fcn)(const T&);
  void  (*objects_init_d3_window)(const T&,d3_window&, GRAPH<d3_point,int>&);
  void  (*defining_points_fcn)(const GeoObj&, list<point>&);
  geowin_defining_points     handle_defining_points;

  iterator mouse_obj; 
  map<void*, geo_props>  props;
 
  // for adding/deleting objects ...
  list<GeoObj>  changed;     // new inserted/deleted/changed objects
  list<GeoObj>  changed2;    // change: old objects (for move/rotate)
  
  GeoBaseScene() : GeoScene(0)
  {
    //b1();
    // set myobjs true in GeoScene constructor ...
    prop_my_scene = this; 
    objs          = new T;
    info_fcn      = 0;
    objects_init_d3_window = NULL;
    defining_points_fcn = NULL;
    handle_defining_points = geowin_highlight;
    gw_redraw_cnt = NULL;
  } 
  
  ~GeoBaseScene()
  {
    if( myobjs ) delete objs;
    undefine_all();
  }

  virtual GeoScene* clone()
  {
    GeoBaseScene<T>* sc = new GeoBaseScene<T>;
    sc->init_from_prototype(this);
    return sc;
  }   
  
  virtual bool IsSuperOrEqual( GeoScene* sc ) 
  {
    if( b1().prototypeid == sc->GeoSceneId() ) return true; 
    return false;
  }
  
  public : 
  
  void set_objects_init_d3_window(void  (*f)(const T&,d3_window&, GRAPH<d3_point,int>&))
  { objects_init_d3_window = f; }
  
  void set_defining_points_fcn(void (*f)(const GeoObj&, list<point>&))
  { defining_points_fcn = f; }  
  
  void set_handle_defining_points(geowin_defining_points gdp)
  { handle_defining_points = gdp; }

  // operations for lists of changed/added/deleted objects ...

  virtual void clear_op_objs() { changed.clear(); changed2.clear(); change_mode=-1; }
  
  // returns a reference to the container :
  T&   get_objref()   { return *objs; }
  
  // sets the container reference:
  void set_objref(T& t)   
  { 
    if( myobjs )  { delete objs; }
    objs = &t;
    myobjs = false;
    init_data();
  }
  
  //deletes object reference, if not myobjs ...
  virtual void del_objref()
  {
    if (! myobjs) objs=NULL;
  }
  
  // returns a copy of the container :
  T    get_objects()     { return *objs; }
  
  // fills the container with a copy of cp
  void set_objects(T cp) { *objs = cp; init_data();  }
  
  virtual int GeoSceneId() const { return b1().prototypeid; }

  virtual void init_from_prototype(GeoScene* proto)
  {
    GeoScene::init_from_prototype(proto);
    GeoBaseScene<T>* pr = (GeoBaseScene<T>*)proto;
    set_info_fcn(pr->info_fcn);
    draw_fcn = pr->draw_fcn;
    objects_init_d3_window = pr->objects_init_d3_window;
    defining_points_fcn = pr->defining_points_fcn;
  }
  
  virtual string information()
  {
    string str(GeoScene::information());
    if( info_fcn && objs!=NULL) str += info_fcn(*objs);
    return str;
  }
  
  void set_info_fcn( string (*f)(const T&)  ) { info_fcn = f; }

  bool get_select(const GeoObj& obj) 
  { 
    return (props.defined((void*)(&obj)) && props[(void*)(&obj)].selected);
  }

  virtual void compute_d3_output(GeoScene* sc, d3_window& W, GRAPH<d3_point,int>& H)
  {
    if (init_d3_window!=NULL) init_d3_window(sc,W,H); 
    else if (objects_init_d3_window!=NULL) objects_init_d3_window(*objs,W,H);
  }

  void draw_object(const GeoObj& obj, window& w, PresentationType pt)
  {
    void*      adr  = (void*)(&obj);
    
    set_window_params(w,adr,pt);

    if (draw_fcn) { // if draw_fcn is set, use it ...
     ((FUNC3)draw_fcn)(w, obj, draw_mode_number);
    }
    else w << obj; 

    string label;
    if (get_obj_label(adr,label))
    { // get bounding box and draw label
      double xw1,xw2,yw1,yw2;
      get_bounding_box_fcn(obj,xw1,xw2,yw1,yw2);
      w.draw_ctext((xw1+xw2)/2,(yw1+yw2)/2,label, text_clr);
    }     
    
    restore_window_params(w);
  } 

  void draw_object_with_properties(const GeoObj& obj)
  {
    window& w = gw->get_window();
    bool draw_flag=false;
    
    PresentationType pt = geowin_normal;
    if( get_select(obj) )  pt = geowin_selected; 

    if( mouse_obj_exist ) {  
      if ( !(mouse_obj != props[(void*)(&obj)].pos) ) 
      {  if (high_light) pt = geowin_focus; 
         if (handle_defining_points==geowin_highlight) draw_flag=true; 
      } 
    }

    draw_object(obj, w, pt);
    list<point> hcont; 
    
    if (defining_points_fcn && (handle_defining_points==geowin_show || draw_flag)) 
       defining_points_fcn(obj,hcont);
    show_points(hcont);
  }

  virtual void redraw(window* w, double x1, double y1, double x2, double y2)
  {
    //set calling GeoWin and scene 
    GeoWin::call_win = gw;
    GeoWin::call_scene = this;
  
    oldwl  = w->set_line_width(get_line_width());
    oldstl = w->set_line_style(l_style);
    oldpstl = w->set_point_style(p_style);
    bool b=true;
    
    if (gw_redraw_cnt) { b = gw_redraw_cnt->operator() (*objs,*w,col1,col2,x1,y1,x2,y2); }
    else {
     if (redraw_pt) { b = redraw_pt->operator() (*w,col1,col2,x1,y1,x2,y2); }
    }
    
    if (b) { // iteration on the container storing the objects ...
       iterator it = objs->begin();
       while( it != objs->end() ) 
       { 
        draw_object_with_properties(*it); 
	it++;
       }
    }

    GeoScene::redraw(w, x1, y1, x2, y2);
  }
  
  // Read - Write
  void write(ostream& os, string tr){
    iterator it   = objs->begin(), stop  = objs->end();
    if( it != stop )  { os << *it++; while( it != stop ) os << ' ' << tr << *it++;   }
    os.flush();
  }

  void write_postscript(ps_file& F)  {  
   if (gw_redraw_cnt) { if (gw_redraw_cnt->write_postscript(*objs, F,col1,col2)) return; }
    else {
     if (redraw_pt){ if (redraw_pt->write_postscript(F,col1,col2)) return; }
    }

    iterator it = objs->begin(), stop = objs->end();
  
     while(it != stop)
     {
	GeoObj& obj = *it;
        set_ps_params(F,(void*)(&obj));
        F << obj;
	it++;
     }
     
     GeoScene::write_postscript(F);
  }

  virtual void read(istream& in, bool keep){
   if (!keep) objs->clear();
   for(;;)
    { char c;
      while (in.get(c) && isspace(c));    if (!in) break;   in.putback(c);
      GeoObj p;  in >> p;  objs->push_back(p);
    }
    init_data();
  }

};

#ifndef NO_STATIC_DATA_MEMBER
template<class T> GeoBaseSceneBuilder<T> GeoBaseScene<T>::sb1;
#endif

template<class T> GeoBaseScene<T>* make_base_prototype(T* t, string str)
{
  int id =  GeoBaseScene<T>::b1().get_id();
  GeoScenePrototypes::set_type_name(id, str);
  return (GeoBaseScene<T>*)(GeoScenePrototypes::get_prototype(id));
}

template<class T> GeoBaseScene<T>* get_base_prototype(T* t)
{
  int id =  GeoBaseScene<T>::b1().get_id();
  return (GeoBaseScene<T>*)(GeoScenePrototypes::get_prototype(id));
}

// ***************************************************************************
// *****************     class GeoEditScene     ******************************


template<class T> class GeoEditScene;
template<class T> class _exportC GeoEditSceneBuilder : public GeoSceneBuilder
{
  friend class GeoEditScene<T>;
  
  public :
  
  GeoEditSceneBuilder() : GeoSceneBuilder(new GeoEditScene<T>) 
  {
    GeoEditScene<T>* sc = 
      (GeoEditScene<T>*)(GeoScenePrototypes::get_prototype(prototypeid));
    sc->id = prototypeid;
  }
  
};


// input functions for Edit Scenes ...
template<class GeoObj>
class _exportC GeoInputObjectWrapper {
  typedef void (*FCN)(GeoWin&, list<GeoObj>&);
  string name;
  GeoInputObject<GeoObj>* alternative_input_object;
  void (*f)(GeoWin&, list<GeoObj>&);

  public:
   GeoInputObjectWrapper() { }
   
   GeoInputObjectWrapper(const GeoInputObject<GeoObj>& obj, string n)
   { alternative_input_object = (GeoInputObject<GeoObj>*) (&obj); f=NULL; name=n; }
   
   GeoInputObjectWrapper(void (*fcn)(GeoWin&, list<GeoObj>&), string n)
   { alternative_input_object = NULL; f=fcn; name=n; }
   
   GeoInputObject<GeoObj>* get_obj_ptr() { return alternative_input_object; }
   FCN get_fcn() { return f; }
   string  get_name(){ return name; }
};

template<class GeoObj>
inline int compare(const GeoInputObjectWrapper<GeoObj>& f1, const GeoInputObjectWrapper<GeoObj>& f2)
{ return 0; }

template<class GeoObj>
inline istream& operator>>(istream& i, GeoInputObjectWrapper<GeoObj>&)
{ return i; }

template<class GeoObj>
inline ostream& operator<<(ostream& o, const GeoInputObjectWrapper<GeoObj>&)
{ return o; }

template<class T>
class GeoIteratorWrapper{
public:
  T it;
  GeoIteratorWrapper() { }
  GeoIteratorWrapper(T t) { it=t;}
  GeoIteratorWrapper(const GeoIteratorWrapper& gi) { it=gi.it; }
};

template<class GeoIt>
inline int compare(const GeoIteratorWrapper<GeoIt>&, const GeoIteratorWrapper<GeoIt>& )
{ return 0; }

template<class GeoIt>
inline istream& operator>>(istream& i, GeoIteratorWrapper<GeoIt>&)
{ return i; }

template<class GeoIt>
inline ostream& operator<<(ostream& o, const GeoIteratorWrapper<GeoIt>&)
{ return o; }

template<class T> 
class  GeoEditScene : public GeoBaseScene<T>
{  
  friend class _exportC GeoEditSceneBuilder<T>;
  friend class _exportC GeoWin;

  public :

#ifdef NO_STATIC_DATA_MEMBER
  
  static GeoEditSceneBuilder<T>& b2()
  {
    static GeoEditSceneBuilder<T> sb2;
    return sb2;
  }
  
#else
  static GeoEditSceneBuilder<T> sb2;
  static GeoEditSceneBuilder<T>& b2()
  {
    return sb2;
  }
#endif
 
  typedef __typename T::value_type              GeoObj;
  typedef __typename T::iterator                iterator; 
  typedef geo_object_properties<iterator>       geo_props;
  typedef GeoInputObjectWrapper<GeoObj>         INP_FCN;
  typedef GeoIteratorWrapper<iterator>          ITW;
  typedef list<GeoObj>                          GeoObjList;
  typedef __typename GeoObjList::iterator       iterator2;   
  

  void (*generate_fcn)(GeoWin&, T&);
  void (*edit_obj_fcn)(GeoWin&, GeoObj&, int);
  void (*post_window_default_input_handler)(GeoWin&, GeoObj&);

  // here are the various functions for the buffer
  list<INP_FCN>           buffer_operations;
  
  INP_FCN *alternative_input_fcn; 
  list<INP_FCN>           input_fcns;

  protected:

  list<ITW>               sel_objs;
  list<GeoObj>            clip_objs;
  ITW                     itw_obj1;
                    

  GeoEditScene() : GeoBaseScene<T>()
  {
    //b2();
    edit_menu_type = edit_menu2;
    alternative_input_fcn = NULL;
  }  
  
  virtual geo_scene clone()
  {
    GeoEditScene<T>* sc = new GeoEditScene<T>;
    sc->init_from_prototype(this);    
    return sc;
  }  
  
  virtual bool IsSuperOrEqual( geo_scene sc ) 
  {
    if( b2().prototypeid == sc->GeoSceneId() ) return true; 
    return GeoBaseScene<T>::IsSuperOrEqual(sc);
  }
    
  bool add_object(const GeoObj& obj,iterator& back)
  {
    if( !pre_add_fcn || pre_add_fcn(*gw, obj) )
      {
        iterator it;
	// we use this flag because of some
	// problems with SUN_PRO
	bool bvl=true;

        if (pre_add_changer) {
	
           GeoObj obj2;
           if (pre_add_changer(*gw, obj, obj2))  { it = objs->insert(objs->end(), obj2); }
           else { bvl=false; } 
      
        }
        else it = objs->insert(objs->end(), obj); 

        if (bvl){
         back=it;
	 geo_props gp(it);
         GeoObj& nwob = *it;
	 props[(void*)(&nwob)] = gp;
         set_default_properties((void*)(&nwob));
	 if (cyclic_colors){
	   set_obj_color((void*)(&nwob),color(1+cyclic_colors_counter%16));
	   set_obj_fill_color((void*)(&nwob),color(1+cyclic_colors_counter%16));
	   cyclic_colors_counter++;
	   cyclic_fill_colors_counter++;
	 }
	 
	 if(post_add_fcn) post_add_fcn(*gw, nwob);

	 return true;
	}
      }
    return false;
  }

  bool del_object(iterator it)
  { 
    GeoObj& obj = *it;
  
    if( !pre_del_fcn || pre_del_fcn(*gw, obj) )
      {
	set_select(it, false);
	if( mouse_obj_exist && !(mouse_obj != it)) mouse_obj_exist = false; 
	//objs->erase(it);

        set_default_properties((void*)(&obj));
	if( post_del_fcn ) post_del_fcn(*gw, obj);
	// changed (erase operation was before set_default_properties)
        objs->erase(it);
	
	return true;
      }
    return false;
  }

  void set_select(iterator it, bool b)
  {
    GeoObj& obj = *it;  
  
    if( b != get_select(obj) )
      if( b ) props[(void*)(&obj)].selected = sel_objs.append(ITW(it));
      else
	{
	  sel_objs.del_item(props[(void*)(&obj)].selected);
	  props[(void*)(&obj)].selected = nil;
	}
  }
  
  void set_select(const list<ITW>& L, bool b)
  { forall(itw_obj1, L) set_select(itw_obj1.it, b); }
  
  public :
  
  void add_buffer_fcn(void (*f)(GeoWin&, list<GeoObj>&), const char* fcn_name)
  {
    buffer_operations.append(GeoInputObjectWrapper<GeoObj>(f,string(fcn_name)));    
  }
  
  void set_alternative_input_object(const GeoInputObject<GeoObj>& obj, string n)
  { 
    input_fcns.append(INP_FCN(obj,n));
    alternative_input_fcn = &(input_fcns[input_fcns.last()]); 
  }
  
  void add_alternative_input_object(const GeoInputObject<GeoObj>& obj,string n)
  { input_fcns.append(INP_FCN(obj,n)); }
  
  virtual void set_alternative_input_fcn(int i)
  {
     if (i==0)  { alternative_input_fcn=NULL; fcn_state = i; gw->INP_STATE=i; }
     else {
       if (i<=input_fcns.length()) {
        list_item it = input_fcns.get_item(i-1);
        alternative_input_fcn = &(input_fcns[it]);  
	fcn_state = i; gw->INP_STATE=i;
       }
     }  
     gw->redraw_inp_panel();
  }
  
  list<string> get_fcn_names(int& nb, bool flag)
  // flag true: return input fcn names, false: return algo names ...
  {
    nb=0;
    list<string> fcns;
    int i=1;
    INP_FCN iter;
    
    if (! flag)
      forall(iter,buffer_operations) fcns.append(iter.get_name()); 
    else
      forall(iter,input_fcns) { 
       if ((alternative_input_fcn!=NULL) && (iter.get_obj_ptr() == alternative_input_fcn->get_obj_ptr())) nb=i;
       fcns.append(iter.get_name()); i++; 
      }
      
    return fcns;
  }

  bool find_object(double x, double y)
  {
    if ( !gw ) return false;
    window& w = gw->get_window();
    double d  = w.pix_to_real(1)* gw->get_mfct();
    double x1=x-d, x2=x+d, y1=y-d, y2=y+d;
    
    iterator it = objs->begin(), stop = objs->end();
    GeoObj obj;
    list<point> hcont;  
    
    iterator old_mouse_obj = mouse_obj;
    bool old_mouse_obj_exist = mouse_obj_exist;

    mouse_obj_exist = false;
    obj_defining_points_change = false;
    
    if (defining_points_fcn && (handle_defining_points!=geowin_hide)){
      while (it != stop){
        defining_points_fcn(*it,hcont);
        point piter;
	int cnt=0;
        forall(piter,hcont){
	  double xw = piter.xcoord(), yw = piter.ycoord();
	  if ((xw>=x1) && (xw<=x2) && (yw>=y1) && (yw<=y2)) {
	     obj_defining_points_change=true;
	     obj_pnr= cnt;
	  }
	  cnt++;
	}
        hcont.clear();	
	it++;
      }
    }

    it = objs->begin();
    while(it != stop)
      {
	obj = *it;
	if( box_intersection_fcn(obj, x1, y1, x2, y2,true) )
	  {
	    mouse_obj_exist = true;
	    mouse_obj = it;
	  }
	it++;
      }

    if ((high_light || (defining_points_fcn && (handle_defining_points == geowin_highlight))) && 
        (old_mouse_obj != mouse_obj || old_mouse_obj_exist != mouse_obj_exist))
    { gw->redraw();
      if (mouse_obj_exist) draw_object_with_properties(*mouse_obj); 
     }
       
    return mouse_obj_exist;
  }
  
  // virtual GeoScene members
  
  virtual int GeoSceneId() const { return b2().prototypeid; }
  virtual GeoEditor* type_editor()  { return this; }
  
  virtual void init_from_prototype(geo_scene proto)
  {
    GeoBaseScene<T>::init_from_prototype(proto);
    
    edit_menu_type = edit_menu2;
    
    GeoEditScene<T>* pr = (GeoEditScene<T>*)proto;    
    
    set_box_intersection_fcn(pr->box_intersection_fcn);
    set_get_bounding_box_fcn(pr->get_bounding_box_fcn);    
    set_move_fcn(pr->move_fcn);
    rotate_fcn = pr->rotate_fcn;
    generate_fcn = pr->generate_fcn;
    edit_obj_fcn = pr->edit_obj_fcn;
    post_window_default_input_handler = pr->post_window_default_input_handler;
    move_point_fcn = pr->move_point_fcn;
    input_fcns = pr->input_fcns;
    buffer_operations= pr->buffer_operations;
    
    pre_add_fcn = pr->pre_add_fcn;
    pre_add_changer = pr->pre_add_changer;
    post_add_fcn = pr->post_add_fcn;
    pre_del_fcn = pr->pre_del_fcn;
    post_del_fcn = pr->post_del_fcn;
    start_change_fcn = pr->start_change_fcn;
    pre_move_fcn = pr->pre_move_fcn;
    post_move_fcn = pr->post_move_fcn;
    pre_rotate_fcn = pr->pre_rotate_fcn;
    post_rotate_fcn = pr->post_rotate_fcn;    
    end_change_fcn = pr->end_change_fcn;
  }

  virtual void init_data()
  { 
    undefine_all();
    mouse_obj_exist = false;

    props.clear();
    sel_objs.clear();
    clip_objs.clear();
    
    iterator it = objs->begin(), stop = objs->end();
    while( it != stop ) 
      {
	geo_props gp(it);
        GeoObj& act= *it;
	props[(void*)(&act)] = gp;
        it++;
      }

    GeoScene::init_data(); 
  }
 
  virtual void edit() { if(gw) gw->edit(this); }
  
  virtual void mouse_at_pos(double x, double y, long& MASK)
  {
    //cout << x << " " << y << "\n";
    mouse_pos(MASK,gw, find_object(x,y));
  }
  
  virtual void scene_input_options()
  { if (alternative_input_fcn != NULL) alternative_input_fcn->get_obj_ptr()->options((*gw));
  }

  void results_handle(const GeoObj& t)
  {
     if( !results.empty() )
     {
      change_mode=0;
      changed.append(t);
      update_and_redraw();
     }
     else draw_object_with_properties(t); 
   } 

  // virtual GeoEditor members  
  void scene_read_object(int srk)
  {
    GeoObj t;
    iterator hl;
    
    list<GeoObj> L;
    window& w = gw->get_window();
    
    if (srk == 0){
     if (alternative_input_fcn != NULL) {
       alternative_input_fcn->get_obj_ptr()->operator()((*gw),L);
       iterator2 it2 = L.begin();
       while( it2 != L.end() ) {
        if (add_object(*it2,hl)) changed.append(*it2); it2++; 
      }
      change_mode = 0;
      update_and_redraw(); 
      return;
     }
     //cout << "read!\n"; cout.flush();
     w >> t;
     if (post_window_default_input_handler) post_window_default_input_handler((*gw),t);
    } 
    else {
      but = keyboard_panel(gw->get_window(), nval);
      if( but == CANCEL_BUTTON ) return;
      string_istream IS(nval);
      IS >> t; 
    }
    
    if( !add_object(t,hl) )  return; 
    results_handle(t);
    gw->update_status_line();
  }

  virtual void toggle_selection() 
  {
    if( mouse_obj_exist )
      {
	GeoObj& obj  = *mouse_obj;
	set_select(mouse_obj, !get_select(obj));
	if( gw ) draw_object_with_properties(obj);
      }
  }
  
  virtual bool options(panel* p)
  {  
    int i;
    list<string> hlp = get_fcn_names(i, true);
    geowin_show_options2((GeoScene*)this,p,gw,filling_color,high_light,true,hlp,i,handle_defining_points);
    set_alternative_input_fcn(i);
    return true;
  }

  void select_in_rect(bool uflag, double x1, double y1, double x2, double y2,bool b)
  // uflag false : select in rect, true: unselect
  {
    bool sel = false;
    list<ITW> tmp;
    
    if (! uflag){
     iterator it = objs->begin();
     iterator stop = objs->end();
    
     while(it != stop ) 
     {
       if(b || box_intersection_fcn(*it, x1, y1, x2, y2,true) ) tmp.push(ITW(it)); 
       it++;
     }
     forall(itw_obj1, tmp)    if( !get_select(*(itw_obj1.it)) )   { sel = true; break; }
    }
    else  tmp = sel_objs; 
    
    set_select(tmp, sel);
    if( !tmp.empty() && gw ) gw->redraw();
  }

  void get_selected_objects(list<GeoObj>& cnt)
  {
	GeoObj obj2;
	forall(itw_obj1, sel_objs) { 
	  obj2 = *(itw_obj1.it);
          cnt.push_back(obj2); 
        }  
  }  

  virtual void copy()
  {
    if( !sel_objs.empty() )
      {
	clip_objs.clear();
	get_selected_objects(clip_objs);
	
	set_select(sel_objs, false);
	gw->redraw();
      }
  }

  virtual void paste()
  {

    if ( !clip_objs.empty() )
      {
	GeoObj obj;
        iterator it;
	forall(obj, clip_objs)
	  {
	    if (add_object(obj,it)) changed.append(obj);
            GeoObj& obnew= *it;
            set_select(it,true);
	    draw_object_with_properties(obnew);
	  }

	clip_objs.clear();
	change_mode=0;
	
	//update();
	update_and_redraw();
	gw->update_status_line();
      }
  }
  
  virtual bool start_changing()
  {
    original = new map<void*, void*>;
    
    if( mouse_obj_exist  && !get_select(*mouse_obj) )
      {
	if( !start_change_fcn || start_change_fcn(*gw, *mouse_obj) )
	  mouse_changing = true;
	else return false;
        GeoObj& mob= *mouse_obj;
	(*original)[(void*) (&mob)] = (void*) (&mob);
      }
    else
      {
	mouse_changing = false;
	
	forall(itw_obj1, sel_objs) 
	  {
	    if( start_change_fcn && !start_change_fcn(*gw, *(itw_obj1.it)) ) return false;
	    GeoObj& ob = *(itw_obj1.it);
	    (*original)[(void*)(&ob)] = (void*)(&ob);
	  }
      }
    while_dragging = true;
    return true;
  }
  
  virtual void stop_changing()
  {
    if( mouse_changing )
      {
	if ( end_change_fcn ) end_change_fcn(*gw, *mouse_obj);
	mouse_changing = false;
        GeoObj& mob= *mouse_obj;
	original_properties((void*)(&mob)); 
      }
    else
      forall(itw_obj1, sel_objs)
      {
	if ( end_change_fcn ) end_change_fcn(*gw, *(itw_obj1.it));
	GeoObj& ob = *(itw_obj1.it);
	original_properties((void*)(&ob));
      }
    
    while_dragging = false;
    delete original;
    original = 0;
    update_and_redraw();
  }
  
  virtual void call_buffer_fcn(int w, bool flag)
  // flag true ... call buffer fcn, false ... print buffer contents to std output
  { 
     list<GeoObj> L;
     forall(itw_obj1,sel_objs) {
       if (flag) L.append(*(itw_obj1.it));
       else cout << *(itw_obj1.it) << "\n";
     }
     list_item it = buffer_operations.get_item(w);
     if (flag) buffer_operations[it].get_fcn()(*gw,L);
  }

  virtual void move_or_rotate_sel(double dx, double dy, double alpha, bool b, bool update_flag)
  // b true: move(dx,dy), false: rotate(dx,dy,alpha)
  { 
    if( !mouse_changing && sel_objs.empty() ) return;
    
    if( mouse_changing )
      {
	GeoObj& obj1 = *mouse_obj;
	if (b) { // move
	 if ( !pre_move_fcn  || (pre_move_fcn(*gw,obj1,dx,dy))){
	  changed.append(obj1);
	  if (!obj_defining_points_change) move( obj1, dx, dy);
	  else move_point(obj1, dx, dy);
	  changed2.append(obj1);
	  if (post_move_fcn) post_move_fcn(*gw,obj1,dx,dy);
	 }
	}
	else { // rotate
	 if (!pre_rotate_fcn  || (pre_rotate_fcn(*gw,obj1,dx,dy,alpha))){	
	  changed.append(obj1);
	  rotate( obj1, dx, dy, alpha);
	  changed2.append(obj1);
	  if (post_rotate_fcn) post_rotate_fcn(*gw,obj1,dx,dy,alpha);
	 }
	}
      }
    else
      {
 	forall(itw_obj1, sel_objs)
	  {
	   if (b) { // move
	    if (!pre_move_fcn  || (pre_move_fcn(*gw,*(itw_obj1.it),dx,dy))){	
	      changed.append(*(itw_obj1.it));  
	      move( *(itw_obj1.it), dx, dy);
	      changed2.append(*(itw_obj1.it));
	      if (post_move_fcn) post_move_fcn(*gw,*(itw_obj1.it),dx,dy);
	    }
	   }
	   else { // rotate 
	    if (!pre_rotate_fcn || (pre_rotate_fcn(*gw,*(itw_obj1.it),dx,dy,alpha))){	 
	     changed.append(*(itw_obj1.it)); 
	     rotate( *(itw_obj1.it), dx, dy, alpha);
	     changed2.append(*(itw_obj1.it));
	     if (post_rotate_fcn) post_rotate_fcn(*gw,*(itw_obj1.it),dx,dy,alpha);
	    }	   
	   }
	  }
      }	
      
     change_mode=2;	
     if (update_flag) update_and_redraw();
  }

  virtual void del_sel()
  { 
    if ( !sel_objs.empty() )
      {
	forall(itw_obj1, sel_objs)  {
	  GeoObj ob = *(itw_obj1.it);
	  if(del_object(itw_obj1.it)) {
	     changed.append(ob);
	  }
	}
	change_mode=1;
	update_and_redraw();
      }
  }
  
  virtual bool fill_rect(double& x1, double& x2, double& y1, double& y2)
  {
    iterator it = objs->begin();
    iterator stop = objs->end();
   
    if ( it != stop ) get_bounding_box_fcn( *it++, x1, x2, y1, y2 );
    else return false;

    double x1akt,x2akt,y1akt,y2akt;

    while( it != stop ) {
       get_bounding_box_fcn( *it++, x1akt, x2akt, y1akt, y2akt );
       if (x1akt<x1) x1=x1akt;
       if (x2akt>x2) x2=x2akt;
       if (y1akt<y1) y1=y1akt;
       if (y2akt>y2) y2=y2akt;
    }
    return true;
  }

  virtual void clear()
  {
    if (objs){
    iterator it = objs->begin();
    iterator stop = objs->end();
    
    while( it != stop ) del_object( it++ );
    if (objs->empty()){
     sel_objs.clear(); 
     props.clear();
     mouse_obj_exist = false;

     undefine_all();
    }
    update_and_redraw();
    }
  }
  
  virtual void read(istream& in, bool keep){
   if (!keep) objs->clear();
   T tmp;
   for(;;)
    { char c;
      while (in.get(c) && isspace(c));    if (!in) break;   in.putback(c);
      GeoObj p;  in >> p;  tmp.push_back(p);
    }
    iterator it = tmp.begin(),hlp;
    while( it != tmp.end() ) {
      if (add_object(*it,hlp)) changed.append(*it); it++; 
    }
    change_mode = 0;
    update_and_redraw();     
  }  

  virtual void generate()
  {
    T tmp;
    generate_fcn(*gw, tmp);
    iterator it = tmp.begin(),hlp;
    while( it != tmp.end() ) {
      if (add_object(*it,hlp)) changed.append(*it); it++; 
    }
    change_mode = 0;
    update_and_redraw(); 
  }
  
  virtual void setup_focus_or_raise(bool flag)
  {
    if( mouse_obj_exist )
      {
	GeoObj& objct    = *mouse_obj;
        void* objptr        = (void*)(&objct);
	
	if (flag) { // setup focus ...
	 window& w = gw->get_window();
         setup_focus_dialog(w, objptr);
	}
	else {	
         GeoObj obj2 = objct;
         iterator zg;

         if (add_object(obj2,zg)){
          GeoObj& zlo = *zg;
          set_original_properties((void*)(&zlo) ,objptr);
          del_object(mouse_obj);
         } 
         update();
	}
	
	gw->redraw();
      }
  }
  
  virtual void obj_edit(){
	if (mouse_obj_exist && edit_obj_fcn) edit_obj_fcn(*gw,*mouse_obj,edit_mode);
  }

  virtual void obj_focus(){
    if( mouse_obj_exist )
      {
	GeoObj& obj = *mouse_obj; 
        GeoObj obj2;
        string_ostream O;
        O <<  obj << ends;
        string nvl=O.str();

        but= focus_dialog(nvl, gw->get_window());

        if( but == CANCEL_BUTTON ) return;
        string_istream IS(nvl);
        IS >> obj2;
 
        iterator zg;

        if (add_object(obj2,zg)){
         GeoObj& zlo = *mouse_obj;
	 GeoObj& zln = *zg;
         set_original_properties((void*)(&zln),(void*)(&zlo));
         del_object(mouse_obj);
        }
       
        update_and_redraw();
      }
  }

  virtual void del_focus()
  {  
    if (mouse_obj_exist)
    { if (get_select(*mouse_obj))  del_sel(); 
      else {
        GeoObj gob = *mouse_obj;
        if (del_object(mouse_obj))
        { 
	  change_mode=1;
	  changed.append(gob);
	  update_and_redraw();
         }
      }
    }
  }

};

#ifndef NO_STATIC_DATA_MEMBER
template<class T> GeoEditSceneBuilder<T> GeoEditScene<T>::sb2;
#endif

template<class T> GeoEditScene<T>* geowin_new_scene(GeoWin& gw, T& t, void (*f)(geo_scene, d3_window&, GRAPH<d3_point,int>&)=NULL)
{
  GeoEditScene<T>* sc = (GeoEditScene<T>*)(GeoEditScene<T>::b2().new_scene());
  sc->set_objref(t);
  gw.insert_scene(sc);
  sc->init_default_values();
  if (f != NULL) sc->init_d3_window = f;
  return sc;
}

template<class T> GeoEditScene<T>* make_edit_prototype(T* t, string str)
{
  int id = GeoEditScene<T>::b2().get_id();
  GeoScenePrototypes::set_type_name(id, str);
  return (GeoEditScene<T>*)(GeoScenePrototypes::get_prototype(id));
}

template<class T> GeoEditScene<T>* get_edit_prototype(T* t)
{
  int id = GeoEditScene<T>::b2().get_id();
  return (GeoEditScene<T>*)(GeoScenePrototypes::get_prototype(id));
}


template <class T, class R, class F>
void geowin_copy_obj_attr(GeoBaseScene<T>* inp_scene, GeoBaseScene<R>* res_scene, F test_fcn)
//bool (*test_fcn)(color&,color&,line_style&,int&,__typename T::iterator&,__typename R::iterator&,int) = NULL)
{
  typedef __typename T::iterator                iscene_iterator;         
  typedef __typename R::iterator                rscene_iterator;
  typedef __typename T::value_type              iscene_vtype;         
  typedef __typename R::value_type              rscene_vtype;  
  
  T& cn1 = inp_scene->get_objref();
  R& cn2 = res_scene->get_objref();
  
  iscene_iterator iit = cn1.begin();
  rscene_iterator rit = cn2.begin();
  
  int counter=0;
  
  for(;iit != cn1.end() ,rit != cn2.end();iit++,rit++){
    iscene_vtype& ob1 = *iit;
    rscene_vtype& ob2 = *rit;
    void * adr_inp = (void*)(&ob1);
    void * adr_res = (void*)(&ob2);
    
    color bc = inp_scene->get_obj_color(adr_inp);
    color fc = inp_scene->get_obj_fill_color(adr_inp);
    line_style lst = inp_scene->get_obj_line_style(adr_inp);
    int w = inp_scene->get_obj_line_width(adr_inp);
    
    if ((test_fcn == NULL) || (test_fcn(bc,fc,lst,w,iit,rit,counter))) {
      res_scene->set_obj_color(adr_res,bc);
      res_scene->set_obj_fill_color(adr_res,fc);
      res_scene->set_obj_line_style(adr_res,lst);
      res_scene->set_obj_line_width(adr_res,w);
    }
  }
  
  // add here a loop for the rest of objects in the container cn2 of res_scene???
}

// ***************************************************************************
// *****************     class GeoResultScene     ****************************

template<class S, class R> class GeoResultScene;
template<class S, class R> class _exportC GeoResultSceneBuilder : public GeoSceneBuilder
{
  friend class GeoResultScene<S,R>;

  public :
  
  GeoResultSceneBuilder() : GeoSceneBuilder(new GeoResultScene<S,R>) { }
  
};

template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw,
					  void (*f)(const S&, R&),
					  GeoBaseScene<S>*,
					  R&, const char* str);

template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw,
					  void (*f)(const S&, R&),
					  GeoBaseScene<S>*, 
					  R*, const char* str);


template<class S, class R> class GeoResultScene : public GeoBaseScene<R>
{ 
  friend class _exportC GeoResultSceneBuilder<S,R>;
  friend class _exportC GeoWin;

public:  
  typedef __typename S::value_type  GeoObjInput;
  typedef __typename R::value_type  GeoObjOutput;  
  typedef __typename S::iterator    IteratorInput;
  typedef __typename R::iterator    IteratorResult;  

  
#ifdef NO_STATIC_DATA_MEMBER2  
  
  static GeoResultSceneBuilder<S,R>& b3()
  {
    static GeoResultSceneBuilder<S,R> sb3;
    return sb3;
  }
  
#else
  
  static GeoResultSceneBuilder<S,R> sb3;
  static GeoResultSceneBuilder<S,R>& b3()
  {
    return sb3;
  }
#endif
   
  GeoBaseScene<S>* input_scene;
  
  bool (*test_fcn)(color&,color&,line_style&,int&, IteratorInput&, IteratorResult&,int);

  // first parameter GeoWin of the result scene, second parameter input scene
  // third parameter result scene...
  void (*update_fcn)(const S&, R&);

  geowin_update<S,R>* pt_update;
  
  GeoResultScene() : GeoBaseScene<R>() 
  { 
    //b3();
    update_fcn=NULL;
    test_fcn = NULL;
    pt_update=NULL;
  }
  
  virtual ~GeoResultScene() {}
  
  virtual GeoScene* clone()
  {
    GeoResultScene<S,R>* sc = new GeoResultScene<S,R>;
    sc->init_from_prototype(this);    
    return sc;
  }   
    
  virtual bool IsSuperOrEqual( geo_scene sc ) 
  {
    if( b3().prototypeid == sc->GeoSceneId() ) return true; 
    return GeoBaseScene<R>::IsSuperOrEqual(sc);
  }
   
  virtual int GeoSceneId() const { return b3().prototypeid; }
  
  virtual void init_from_prototype(geo_scene)
  {
    // use prototype of super class for initialzation
    int id1 =  GeoBaseScene<R>::b1().get_id();
    
    if( id1 == -1 ) 
      error_handler(1, "GeoResultScene derived from unknown base scene.");
    else
      {
	geo_scene base_proto = GeoScenePrototypes::get_prototype(id1);
	GeoBaseScene<R>::init_from_prototype(base_proto);
	edit_menu_type = -1;
      }
  }
  
  void set_input_scene(GeoBaseScene<S>* input)
  {
    input_scene = input;
    input_scene->add_dependence(this);
  }

  void set_update_object(geowin_update<S,R>* up)
  {
    pt_update= up;
  }

  void set_update_fcn( void (*f)(const S&, R&) )
  { update_fcn = f; }
  
  virtual void update()
  {
    //set calling GeoWin and scene 
    GeoWin::call_win = gw;
    GeoWin::call_scene = this;
    GeoWin::call_inp_scene = input_scene;
    
    float timeact= used_time();

   if (is_visible()){
    if (debug_mode) gw->write_scene(input_scene, debug_file_name, false); 
   
    if (pt_update != NULL) { // function object
      int mode = input_scene->change_mode;    
      bool ret = false;
      __typename list<GeoObjInput>::iterator it,it2;

      if ((mode >=0) && (mode <=2)) { 
       list<GeoObjInput>& L1 = input_scene->changed;
       list<GeoObjInput>& L2 = input_scene->changed2;
       
       if (L1.size()<GEOWIN_UPDATE_SIZE){
       switch(mode)
       {
        case 0: // add ...
        {
	 for(it=L1.begin();it != L1.end(); it++) {
	   ret = pt_update->insert(*it);
	   if (! ret) break;
	 }
	 break;
        }
        case 1: // delete ...
        {
	 for(it=L1.begin();it != L1.end(); it++) {
	   ret = pt_update->del(*it); 
	   if (! ret) break;
	 }
	 break;
        }
        case 2: // change ...
        {
         for(it=L1.begin(),it2=L2.begin();it != L1.end(); it++,it2++) {
	   ret = pt_update->change(*it,*it2);
	   if (! ret) break;
	 }
         break;
        }
       }
       }
      }
      // update function of the update object ...
      if (! ret) pt_update->update(input_scene->get_objref(),*objs) ;  
    }
    
    else { // function
      if (update_fcn != NULL) update_fcn(input_scene->get_objref(), *objs);
    }
   }

   if (gw && gw->get_time_meas() && (pt_update!=NULL || update_fcn!=NULL))
      cout << get_name() << ":" << used_time(timeact) << " s.\n";

   // set object attributes ...
   if (copy_attr) geowin_copy_obj_attr(input_scene, this, test_fcn); 
      
   GeoBaseScene<R>::update();

  } 
  

};

#ifndef NO_STATIC_DATA_MEMBER2 
template<class S, class R> GeoResultSceneBuilder<S,R> GeoResultScene<S,R>::sb3;
#endif



template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw,
					  void (*f)(const S&,R&),
					  GeoBaseScene<S>* input, 
					  const char* str, int fl)
{
  GeoResultScene<S,R>* sc = 
    (GeoResultScene<S,R>*)(GeoResultScene<S,R>::b3().new_scene());
  sc->set_base_name(str);
  sc->set_input_scene(input);
  sc->set_update_fcn(f);
 
  gw.insert_scene(sc);
  sc->init_default_values();
  sc->update();  
  return sc; 
}


template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw,
					  void (*f)(const S&,R&), geo_scene sc, 
					  const char* str, void (*d3f)(geo_scene, d3_window&, GRAPH<d3_point,int>&) = NULL)
{ GeoResultScene<S,R>* scr = geowin_new_scene(gw, f, (GeoBaseScene<S>*)sc, str, 0); 
  if (d3f != NULL) scr->init_d3_window = d3f;
  return scr;
}

template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw, geowin_update<S,R>& up, geo_scene sc, const char* name, 
                                      void (*d3f)(geo_scene, d3_window&, GRAPH<d3_point,int>&) = NULL)
{
  GeoResultScene<S,R>* res =  (GeoResultScene<S,R>*)(GeoResultScene<S,R>::b3().new_scene());
  res->set_base_name(name);
  res->set_input_scene((GeoBaseScene<S>*)sc); 
  res->set_update_object(&up);
 
  gw.insert_scene(res);
  res->init_default_values();
  res->update();  
  
  if (d3f != NULL) res->init_d3_window = d3f;
  return res;  
}

template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw, geowin_update<S,R>& up,geowin_redraw& rb, geo_scene sc,const char* name,
                                      void (*d3f)(geo_scene, d3_window&, GRAPH<d3_point,int>&) = NULL)
{
  GeoResultScene<S,R>* res =  (GeoResultScene<S,R>*)(GeoResultScene<S,R>::b3().new_scene());
  res->set_base_name(name);
  res->set_input_scene((GeoBaseScene<S>*)sc); 
  res->set_update_object(&up);

  gw.insert_scene(res);
  res->init_default_values();
  gw.set_redraw_pt(res, &rb); 
  res->update();  
  
  if (d3f != NULL) res->init_d3_window = d3f;  
  return res;  
}

template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw, geowin_update<S,R>& up,geowin_redraw_container<R>& rd, geo_scene sc,const char* name,
                                      void (*d3f)(geo_scene, d3_window&, GRAPH<d3_point,int>&) = NULL)
{
  GeoResultScene<S,R>* res =  (GeoResultScene<S,R>*)(GeoResultScene<S,R>::b3().new_scene());
  res->set_base_name(name);
  res->set_input_scene((GeoBaseScene<S>*)sc); 
  res->set_update_object(&up);
  
  // redraw container object ...
  res->gw_redraw_cnt = &rd;

  gw.insert_scene(res);
  res->init_default_values();
  res->update();  
  
  if (d3f != NULL) res->init_d3_window = d3f;  
  return res;  
}

// setting update objects
template<class S,class R>
void geowin_set_update(geo_scene res, geowin_update<S,R>& up)
{ 
 GeoResultScene<S,R>* result = (GeoResultScene<S,R>*)res;
 result->set_update_fcn(NULL);
 result->set_update_object(&up);
}

// setting update functions
template<class S,class R>
void geowin_set_update(geo_scene res, void (*f_update)(const S&, R&))
{
 GeoResultScene<S,R>* result = (GeoResultScene<S,R>*)res;
 result->set_update_fcn(f_update);
 result->set_update_object(NULL); 
}

/*{\Mtext \bigskip {\bf 4. Non-Member Functions} }*/

class _exportC GeoEditorMember : public GeoFunctions
{
  void (GeoEditor::*f)(void);
  
  public : 
  
  GeoEditorMember(void (GeoEditor::*g)()) : GeoFunctions(""), f(g) {}
 
  virtual ~GeoEditorMember() {}
  virtual void call(GeoWin& gw) 
  {  
    geo_scene  sc = gw.get_active_scene();
    geo_editor ed = sc ? sc->type_editor() : 0;
    if( ed ) (ed->*f)();
  }
};

class _exportC GeoSceneMember : public GeoFunctions
{
  void (GeoScene::*f)(void);
  
  public : 
  
  GeoSceneMember(void (GeoScene::*g)()) : GeoFunctions(""), f(g) {}
  virtual ~GeoSceneMember() {}
  virtual void call(GeoWin& gw) 
  {  
    geo_scene  sc = gw.get_active_scene();
    if( sc ) (sc->*f)();
  }
};


template<class F> 
void geowin_add_user_call(GeoWin& gw, string label, F f)
{
  if( f)
    {
      GeoFunctions* fp = new GeoFunction<F>(f, label);
      gw.add_call(fp, label);
    }
}

inline GeoWin* get_geowin(geo_scene sc)
/*{\Mfuncl
  returns a pointer to the |GeoWin| of |sc|.}*/
{ return sc->get_geowin(); }


void _exportF geo_call(GeoWin& gw, void (*fkt)(GeoWin&), string);
void _exportF geo_call(GeoWin& gw, void (*fkt)(), string);

template<class T> bool geowin_get_objects(GeoWin& gw, geo_scene sc, T& t)
  {
    GeoBaseScene<T>* pr=get_base_prototype(&t);
    if( pr->IsMyKindOfScene(sc) )
      {
	pr = (GeoBaseScene<T>*)sc;
	t = pr->get_objects();
	return true;
      }
    return false;
  }
  
template <class T>
void geowin_get_selected_objects(GeoWin& gw,GeoEditScene<T>* sc, T& cnt)
{
   typedef __typename T::value_type value_type;
   list<value_type> HL;
   
   sc->get_selected_objects(HL);
   value_type iter;
   forall(iter,HL) cnt.push_back(iter);
}


inline void GeowinMember::call(GeoWin& gw) { (gw.*f)(); }

//  template functions for setting handlers ...
// add handler
  
template<class T,class F>
bool geowin_set_pre_add_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->pre_add_fcn = handler; 
 return true;
}
  
template<class T,class F>
bool geowin_set_pre_add_change_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->pre_add_changer = handler; 
 return true;
}
  
template<class T,class F>
bool geowin_set_post_add_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->post_add_fcn = handler; 
 return true;
}

// delete handler
    
template<class T,class F>
bool geowin_set_pre_del_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->pre_del_fcn = handler; 
 return true;
}
  
template<class T,class F>
bool geowin_set_post_del_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->post_del_fcn = handler; 
 return true;
}
  
// change handler
  
template<class T,class F>
bool geowin_set_start_change_handler(GeoEditScene<T>* sc, F handler )
{
 if (sc == NULL) return false;
 sc->start_change_fcn = handler; 
 return true;
}

template<class T,class F>
bool geowin_set_pre_move_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->pre_move_fcn = handler; 
 return true;
}
  
template<class T,class F>
bool geowin_set_post_move_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->post_move_fcn = handler; 
 return true;
}
  
template<class T,class F>
bool geowin_set_pre_rotate_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->pre_rotate_fcn = handler; 
 return true;
}
  
template<class T,class F>
bool geowin_set_post_rotate_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->post_rotate_fcn = handler; 
 return true;
}

template<class T,class F>
bool geowin_set_end_change_handler(GeoEditScene<T>* sc, F handler )
{
 if (sc == NULL) return false;
 sc->end_change_fcn = handler; 
 return true; 
}

template<class T>
bool geowin_set_generate_fcn(GeoEditScene<T>* sc, void (*f)(GeoWin& gw,T& L))
{
 if (sc == NULL) return false;
 sc->generate_fcn = f;
 return true;
}

template<class T, class T2>
bool geowin_set_edit_object_fcn(GeoEditScene<T>* sc, T2 f)
{
 if (sc == NULL) return false;
 sc->edit_obj_fcn = f;
 return true;
}


template<class T,class F>
bool geowin_add_buffer_fcn(GeoEditScene<T>* sc, F f, const char* name)
{
 if (sc == NULL) return false;
 sc->add_buffer_fcn(f,name);
 return true;
}

// third template argument because of SUN CC ...
template<class S, class R, class T>
bool geowin_set_copy_attr_test_fcn(GeoResultScene<S,R>* sc, T f)
{
 if (sc==NULL) return false;
 sc->test_fcn = f; 
 return true;
}


// here a second template argument because of SUN CC ...
template<class T, class T2>
bool geowin_set_input_object(GeoEditScene<T>* sc, const GeoInputObject<T2>& obj, string fname)
{
 if (sc == NULL) return false;
 sc->set_alternative_input_object(obj,fname);
 return true;
}

template<class T, class T2>
bool geowin_add_input_object(GeoEditScene<T>* sc, const GeoInputObject<T2>& obj, string fname)
{
 if (sc == NULL) return false;
 sc->add_alternative_input_object(obj,fname);
 return true;
}

template<class T, class T2>
void geowin_set_draw_object_fcn(GeoBaseScene<T>* sc, T2 fcn)
{ sc->draw_fcn = (void*) fcn; }


// set object properties in scenes
template<class T> color geowin_get_obj_color(GeoBaseScene<T>* sc, void* adr)
{ return sc->get_obj_color(adr); }

template<class T> color geowin_set_obj_color(GeoBaseScene<T>* sc, void* adr, color c)
{ return sc->set_obj_color(adr,c); } 

template<class T> color geowin_get_obj_fill_color(GeoBaseScene<T>* sc, void* adr)
{ return sc->get_obj_fill_color(adr); }

template<class T> color geowin_set_obj_fill_color(GeoBaseScene<T>* sc, void* adr, color c)
{ return sc->set_obj_fill_color(adr,c); }  

template<class T> line_style geowin_get_obj_line_style(GeoBaseScene<T>* sc, void* adr)
{ return sc->get_obj_line_style(adr); }    

template<class T> line_style geowin_set_obj_line_style(GeoBaseScene<T>* sc, void* adr, line_style l)
{ return sc->set_obj_line_style(adr,l); }  

template<class T> int geowin_get_obj_line_width(GeoBaseScene<T>* sc, void* adr)
{ return sc->get_obj_line_width(adr); }   

template<class T> int geowin_set_obj_line_width(GeoBaseScene<T>* sc, void* adr, int w)  
{ return sc->set_obj_line_width(adr,w); }    

// handle defining points ...
template<class T>    
void geowin_set_handle_defining_points(GeoEditScene<T>* sc, geowin_defining_points gdp)
{ sc->set_handle_defining_points(gdp); } 


GEOWIN_END_NAMESPACE


#if LEDA_ROOT_INCL_ID == 410096
#undef LEDA_ROOT_INCL_ID
#include <LEDA/UNDEFINE_NAMES.h>
#endif


#endif



