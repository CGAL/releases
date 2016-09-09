// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : src/GeoWin/LEDA/geowin.h
// package       : GeoWin (1.0.8)
// revision      : 1.0.8
// revision_date : 17 December 1999 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken>)
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef LEDA_GEOWIN_H
#define LEDA_GEOWIN_H

#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 400090
#include <LEDA/REDEFINE_NAMES.h>
#endif


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
#include<ctype.h>


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


GEOWIN_BEGIN_NAMESPACE

class _exportC geowin_redraw
{
public:

 virtual void draw(window& W,color c1,color c2,double x1,double y1,double x2,double y2) 
 { }
  
 virtual bool write_postscript(ps_file& PS,color c1,color c2) { return false; }
  
 virtual void operator() (window& W,color c1,color c2,double x1,double y1,double x2,double y2 ) 
 { draw(W,c1,c2,x1,y1,x2,y2); }
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
#define option_menu      zoom_menu + 1
#define scene_opt_menu   option_menu + 1
#define run_menu         scene_opt_menu + 1

#define scene_list_menu  run_menu + 1
#define scene_cont_menu  scene_list_menu + 1
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
#define GEO_CM_OK            3
#define GEO_CM_QUIT          4
#define GEO_CM_ACTIVE_OPT    5

#define GEO_CM_CLEAR         9
#define GEO_CM_VISIBLE       10
#define GEO_CM_BUTTONS       11

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

extern _exportF void setup_font(window &w, double sz);

class _exportC GeoScene;

template<class T> class GeoBaseScene;
template<class T> class GeoEditScene;
template<class S,class R> class GeoResultScene;

class _exportC GeoSceneBuilder;
class _exportC GeoEditor;

// Geo remarks; include them into the Geowin_GeoObj

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

// class GeoWin_GeoObj
// objects that can be inserted in scenes ...
// ------------------------------------------------

class _exportC GeoWin_GeoObj {
 GeoScene* my_scene;
 int mode;
 // =0 ... no object allocated
 // =1 ... point
 // =2 ... segment
 // =3 ... ray
 // =4 ... line
 // =5 ... circle
 // =6 ... gen_polygon
 // =7 ... GeoRemark
 
 void* object_ptr; // pointer to the object...
 
 //attributes of the GeoWin_GeoObj
 color interior;
 color boundary;
 line_style l_style;
 int l_width;
 
 public:
   GeoWin_GeoObj() {mode =0; }
   GeoWin_GeoObj(const point&);
   GeoWin_GeoObj(const segment&);
   GeoWin_GeoObj(const ray&);
   GeoWin_GeoObj(const line&);
   GeoWin_GeoObj(const circle&);
   GeoWin_GeoObj(const gen_polygon&);
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
  
  virtual void mouse_read_object() = 0; // reads in a geoobject
  virtual void keyboard_read_object() = 0; // object input 
  virtual void generate()    = 0; // generates objects
  
  virtual void toggle_selection() = 0; // changes the selectionstate of the object with focus
  virtual void select_in_rect(double x1, double y1, double x2, double y2) = 0;
  virtual void select_all() =0;
  virtual void unselect() = 0;  //unselects all
  virtual bool fill_rect(double&, double&, double&, double&) = 0;  //get bounding box
  virtual void copy()        = 0;
  virtual void paste()       = 0;
  virtual void del_sel()     = 0;
  virtual void del_focus()   = 0;
  virtual void setup_focus() = 0;
  virtual void obj_focus()   = 0;
  virtual void raise_object()= 0;
  virtual void clear()       = 0;

  virtual bool start_changing() = 0; // called, when the position of an object is changed
  virtual void move_sel(double, double)    = 0;
  virtual void rotate_sel(double, double, double)  = 0;
  virtual void stop_changing()  = 0;
 
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

  void (*init_d3_window)(GeoScene* sc, d3_window& W, GRAPH<d3_point,int>& H);  

  list_item  pos;   // position in the list of scenes which are managed by |gw|
  
  // drawing parameters :
  color      col1;  //color for normal drawing  
  color      col2;  //color for selected drawing
  color      filling_color; // color for filled objects

  int        back_line_width;   // for objects, if the scene is not active
  int        active_line_width; // for objects in the currently active scene
  line_style  l_style;
  point_style p_style;

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
  
  GeoScene(GeoWin* win);
  
  virtual ~GeoScene();

  static GeoScene* new_scene(string str); // parameter: prototype name or -id
  static GeoScene* new_scene(int id);
  
  void init_default_values();
  // set colors and other parameters ...

  geowin_redraw* get_redraw_pt()  { return redraw_pt; } 

  GeoWin*          get_geowin()  { return gw; }
   
  virtual geo_editor type_editor()  { return 0; }
  
  bool IsMyKindOfScene( GeoScene* sc );
  virtual int GeoSceneId() const = 0;
  
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

  virtual void init_data()=0;

  virtual void redraw(window* w, double x1, double y1, double x2, double y2); 
  
  virtual void mouse_at_pos(double, double, long& MASK);
  /* informs this scene about current mouse position. |MASK| will
     be checked for userdefined actions  */ 

  virtual void update();
  
  void    scene_options()  { options((panel*)0); }
  virtual void clear() { }
  virtual void del_objref() {}

  virtual void options(panel* p = 0);
  virtual void contents();

  virtual string information();

  virtual void edit() = 0;
 
  virtual void read(istream& is) = 0;
  virtual void write(ostream& os, string tr) = 0;
  virtual void write_postscript(ps_file& f);  
};

typedef GeoScene* geo_scene;

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
    \item |line_width| is the line width used for drawing the objects
          (type |int|)
    \item |active_line_width| is the line width used for drawing the objects if the
          scene is active (type |int|)
    \item |line_style| is the line style used for drawing the objects
          (type |line_style|)
    \item |point_style| is the point style used for drawing points
          (type |point_style|)	  
    \item |visible| is |true| if the scene is visible in his |GeoWin|, |false| otherwise
          (type |bool|)
    \item |active| is |true| if the scene has input focus (is currently edited) in
          his |GeoWin|, |false| otherwise (type |bool|)
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
  
  // window member parameters :
  // **************************
  window* Wp;
  window* msg_win;
  d3_window* d3_win;
  window* Whelpd3;
  
  string cur_info;
  void draw_info();

  // is |true| iff the window was opened
  bool   is_open;
  
  // if |is_locked| is true, no redraws take place  (flag to avoid multiple 
  // redraws)
  bool   is_locked;
  
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
  
  // animation steps for zooming
  int gw_anim_steps;

  // parameter for size of the isorect. around mousepointer
  // (used when finding objects)
  double mouse_fct;

  // menu member parameters :
  // ************************
  
  // array of all menus : 
  menu**  menus;  
  
  // array of associated menu functions :
  GeoFunctions** menu_fcn;
  int            menu_fcn_count;  // number of all menu items
  int            user_fcn_count;  // number of user defined menu items
  
  // values for the NEW, WRITE, CLOSE, DONE and QUIT buttons
  int     buttons[GEO_CM_BUTTONS];
  int     button_info[GEO_CM_BUTTONS];  // and infos about their status
                         // 0 = inactive, 1 = active, 2 = button depend

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

  // currently active scene :
  geo_scene       cur;

  // if a special scene should be edited, |edit_scene| points 
  // to this scene 
  geo_scene       edit_scene;

  // list of names of scene types that can be edited by this |\Mname|
  list<string> editables;

  // maps scene names to its number to avoid duplicates
  d_array<string, int>    scene_name_map;


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

  // calls |activate| for the scene, for which |ids[geo_active_id] == id|
  void activate(int id);
  friend void geo_activate(int n);
  
  // calls member |options| for the scene, for which |ids[geo_opt_id] == id|
  void scene_options(int id);
 // calls member |contents| for the scene, for which |ids[geo_cont_id] == id|  
  void scene_contents(int id);
  void active_scene_options();
  
  friend void geo_scene_option(int n);
  friend void geo_scene_contents(int n);

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
  // panel for the setting of minimal and Maximal coordinates
  void scaling_options();
  // panel for setting d3 output options
  void d3_options();

  // handling :
  // ----------

  friend _exportF void geo_move(GeoWin& gw, const point& p);
  friend _exportF void geo_rotate(GeoWin& gw, const point& p);
  friend _exportF void geo_object_dragging(GeoWin& gw, const point& p);

  // rotate selected object around pin point :
  void   rotate();
  void   rotate(const point& p);
  void   rotate(const point& p1, const point& p2);

  // move selected object with mouse cursor
  void   move();
  void   move(const point& p);
 
  void rotate_menu() { rotate(); }
  void move_menu()   { move();   }
  void select_menu() { select(); }
  void redraw_menu() { redraw(); }
  void destroy_menu(){ destroy();}

  void help_about();
  void help_news ();
  void help_buttons(); 
  
  void help_user();  

 
  // visibility :
  // ------------
  
  void visible_scenes();

  public :
  
  // file operations...
  void save_ps();
  void save_ps_vis(); // writes all visible scenes in ps - format...
  void file_open();
  void write_ps(string filename);
  void write_ps_vis(string filename);
  void write_scene_woh(string filename);
  void file_save();
  void file_save_woh();
  void save_screen();

  /*{\Mcreation GW}*/

  GeoWin(const char* label = "GEOWIN"); 
  /*{\Mcreate creates a GeoWin $GW$. |\Mvar| is constructed with 
              frame label $label$}*/ 

  GeoWin(double x,double y,const char* label = "GEOWIN"); 
  /*{\Mcreate creates a GeoWin $GW$. |\Mvar| is constructed with 
              frame label $label$ and physical size $x\times y$. }*/  
  
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
    
    The following templated |new_scene| operation can be used to create 
    edit scenes.
    The |CONTAINER| has to be a |list<T>| , where T is a 2d LEDA kernel type,
    a |d3_point| or a |d3_rat_point|.
    }*/ 
    

  template<class CONTAINER> GeoEditScene<CONTAINER>* new_scene(CONTAINER& c) 
    /*{\Mopl creates a new edit scene for |c|. |c| will be edited by |\Mvar|.}*/
  {
    return geowin_new_scene(*this, c);
  }

  template<class CONTAINER> GeoEditScene<CONTAINER>* new_scene(CONTAINER* c) 
  { return geowin_new_scene(*this, c); }

  
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
    
    It is also possible to provide user defined redraw for a scene.
    For this purpose we use redraw objects derived from |geowin_redraw|.
    The derived class has to overwrite the virtual redraw function

     |void draw(window& W,color c1,color c2,double x1,double y1,double x2,double y2)|
     
    of the base class to provide a user defined redraw function. The first 3 parameters
    of this function are the redraw window and the first and second drawing color (|color| 
    and |color2|) of the scene.
    
    Note that |S| and |R| in the following operations are template parameters.
    |S| and |R| have to be a |list<T>|, where T is a 2d LEDA kernel type,
    a |d3_point| or a |d3_rat_point|.
    |S| is the type of the contents of the input scene, |R| the type of the contents
    of the created result scene.
    
 }*/

  template<class S, class R> 
  GeoResultScene<S,R>* new_scene(void (*f_update)(const S&, R&), geo_scene sc, string str)
    /*{\Mopl  creates a new result scene with name |str|.
             The input scene for this new result scene will be |sc|.
             The update function will be |f_update|. }*/
  { return geowin_new_scene(*this, f_update, sc, str);  }

  //result scene for update objects...
  template<class S,class R>
  GeoResultScene<S,R>* new_scene(geowin_update<S,R>& up, geo_scene sc_input, string str)
    /*{\Mopl  creates a new result scene with name |str|.
             The input scene for this new result scene will be |sc_input|.
             The update object will be |up|. }*/
  { return geowin_new_scene(*this,up,sc_input,str); }
     
  template<class S,class R>
  GeoResultScene<S,R>* new_scene(geowin_update<S,R>& up, geowin_redraw& rd, geo_scene sc_input, string str)
    /*{\Mopl  creates a new result scene with name |str|.
             The input scene for this new result scene will be |sc_input|.    
             The update object will be |ub|.  
	     The redraw object will be |rd|. }*/
  { return geowin_new_scene(*this,up,rd,sc_input,str); }

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
#endif

  void edit();
  /*{\Mop starts the interactive mode of |\Mvar|. The operation returns 
         if either the $DONE$ or $Quit$ button was pressed. }*/

  bool edit(geo_scene sc);
  /*{\Mop  edits scene $sc$. Returns |false| when the Quit-Button was pressed,
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
  
  int  set_cursor(int cursor_id = -1) { return Wp->set_cursor(cursor_id); }
  /*{\Mopl sets the mouse cursor to $cursor\_id$. }*/


  /*{\Mtext
    \medskip
    {\bf c) Scene Operations} }*/

  void insert(geo_scene sc);
  void remove(geo_scene sc);
  // removes scene |sc| from $GW$. Contents of |sc| will not be destroyed.
  
  void destroy(geo_scene sc);
  /*{\Mopl removes scene |sc| from $GW$ and destroys it. }*/

  geo_scene get_scene_with_name(string nm) const;
  /*{\Mopl returns the scene with name |nm| or nil if there is no scene
           with name |nm|.}*/
	   
  void   activate(geo_scene sc);
  /*{\Mopl  makes scene |sc| the active scene of |\Mvar|. }*/ 
  
  geo_scene get_active_scene() const;
  /*{\Mopl  returns the active scene of |\Mvar|. }*/ 
  
  bool is_active(geo_scene sc) const { return sc->get_active(); }
  /*{\Mopl returns true if |sc| is an active scene in a |\Mname|. }*/

  /*{\Mtext
    \medskip
    The following $get$ and $set$ operations can be used for retrieving and
    changing scene parameters. All $set$ operations return the previous 
    value. }*/

  string get_name(geo_scene sc) const { return sc->get_name(); }
  /*{\Mopl returns the |name| of scene |sc|. }*/ 
    
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

  color get_color2(geo_scene sc) const;

  color set_color2(geo_scene sc, color c);

  color get_selection_color(geo_scene sc) const { return get_color2(sc); }
  /*{\Mopl returns the boundary drawing color for selected objects (color2)
          of scene |sc|. }*/

  color set_selection_color(geo_scene sc, color c){ return set_color2(sc,c); }
  /*{\Mopl sets the boundary drawing color for selected objects (color2)
          of scene |sc| to |c|. }*/


  color get_fill_color(geo_scene sc) const;
  /*{\Mopl returns the fill color of |sc|.}*/  
 
  color set_fill_color(geo_scene sc,color c);
  /*{\Mopl sets the fill color of |sc| to |c|. Use color $invisible$ 
           to disable filling.}*/ 

  int get_line_width(geo_scene sc) const { return sc->back_line_width; }
  /*{\Mopl returns the line width of scene |sc| .}*/

  int get_active_line_width(geo_scene sc) const 
  /*{\Mopl returns the active line width of |sc| .}*/
  { return sc->active_line_width; }
  
  int set_line_width(geo_scene sc,int w) 
  /*{\Mopl sets the line width for scene |sc| to |w|.}*/
  { int val=sc->back_line_width; sc->back_line_width=w; return val;}
  
  int set_active_line_width(geo_scene sc,int w) 
  /*{\Mopl sets the active line width of scene |sc| to |w|.}*/
  { int val=sc->active_line_width; sc->active_line_width=w; return val; }

  line_style get_line_style(geo_scene sc) const { return sc->l_style; }
  /*{\Mopl returns the line style of |sc|.}*/
  
  line_style set_line_style(geo_scene sc, line_style l) 
  /*{\Mopl sets the line style of scene |sc| to |l|.}*/
  { line_style val=sc->l_style; sc->l_style=l; return val; }
  
  bool get_visible(geo_scene sc) const;
  /*{\Mopl returns the visible flag of scene |sc|. }*/
  
  bool set_visible(geo_scene sc, bool v);
  /*{\Mopl sets the visible flag of scene |sc| to |v|. }*/
  
  void set_all_visible(bool v);
  /*{\Mopl sets the visible flag of all scenes that are 
          currently in |\Mvar| to |v|.}*/
  
  point_style get_point_style(geo_scene sc) const { return sc->p_style; }
  /*{\Mopl returns the point style of |sc|.}*/
  
  point_style set_point_style(geo_scene sc, point_style p) 
  /*{\Mopl sets the point style of |sc| to |p|}*/ 
  { point_style pold= sc->p_style; sc->p_style=p; return pold; }

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

  template<class T>  
  color get_obj_fill_color(GeoBaseScene<T>* sc, void* adr)
  /*{\Mopl returns the interior color of the object at |(*adr)|.}*/ 
  { return sc->get_obj_fill_color(adr); }

  template<class T>  
  color set_obj_fill_color(GeoBaseScene<T>* sc, void* adr, color c)
  /*{\Mopl sets the interior color of the object at |(*adr)| to |c|.}*/    
  { return sc->set_obj_fill_color(adr,c); }  

  template<class T>
  line_style get_obj_line_style(GeoBaseScene<T>* sc, void* adr)
  /*{\Mopl returns the line style of the object at |(*adr)|.}*/
  { return sc->get_obj_line_style(adr); }    

  template<class T>    
  line_style set_obj_line_style(GeoBaseScene<T>* sc, void* adr, line_style l)
  /*{\Mopl sets the line style of the object at |(*adr)| to |l|.}*/
  { return sc->set_obj_line_style(adr,l); }  

  template<class T>  
  int get_obj_line_width(GeoBaseScene<T>* sc, void* adr)
  /*{\Mopl returns the line width of the object at |(*adr)|.}*/
  { return sc->get_obj_line_width(adr); }   

  template<class T>    
  int set_obj_line_width(GeoBaseScene<T>* sc, void* adr, int w)  
  /*{\Mopl sets the line width of the object at |(*adr)| to |w|.}*/
  { return sc->set_obj_line_width(adr,w); }    
  
#endif
  
  void set_active(geo_scene sc,bool ac) { sc->set_active(ac); }
  
  /*{\Mtext
    \medskip
    {\bf d) Input and Output Operations} }*/
    
  void read(geo_scene sc,istream& is) { sc->read(is); }
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
	    
  /*{\Mtext \newpage}*/
	      

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

  string get_bg_pixmap()  { return bg_pixmap; }
  /*{\Mopl returns the name of the current background pixmap.}*/
  	    
  string set_bg_pixmap(string pix_name); 	  
  /*{\Mopl changes the window background pixmap to pixmap with name |pix_name|.
           Returns the name of the previous background pixmap.
  }*/
  
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
     \item Post add handler
     \item Pre delete handler
     \item Post delete handler
     \item Pre and Post move handler
     \item Pre and Post rotate handler
     \item Start and End change handler
  
     \end{itemize}
     
     The add handlers will be called when a user tries to add an object
     to an edit scene in GeoWin, the delete handlers will be called when
     the user tries to delete an object and the change handlers will be
     called when the user tries to change an object (for instance by moving
     it or rotating it).
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
#endif

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
    {\bf g) Further Operations} }*/
    
  list<geo_scene> get_scenes() { return scenes; }
  /*{\Mopl  returns the scenes of |\Mvar|.}*/

  double get_mfct() { return mouse_fct; }
  void init_data(geo_scene sc) { sc->init_data(); }
 
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
  
  // add additional objects to scenes ...
  // returns the list item of the added object
  
 /*{\Xtext
    \medskip
    {\bf Additional objects} 
    
    Every |geo_scene| can hold additional objects, that are not in the container
    of the scene. The type of an additional object can be:
    \begin{itemize}
    \item |point|
    \item |segment|
    \item |ray|
    \item |line|
    \item |circle|
    \item |gen_polygon|
    \end{itemize} 
    The operations adding an additional object to a scene return a |list_item| ,
    that can be used for changing the attributes of the object and for deleting
    the object.
    Every additional object has the following attributes:
    \begin{itemize}
    \item |color| (boundary color)
    \item |fill_color| (color of the interior)
    \item |line_style| (line style of the object)
    \item |line_width| (line width of the object)
    \end{itemize}
 }*/  
  
  list_item add_point(geo_scene sc, point p);
  /*{\Xopl adds point |p| to scene |sc|.}*/
  
  list_item add_segment(geo_scene sc, segment s);
 /*{\Xopl adds segment |s| to scene |sc|.}*/  
 
  list_item add_ray(geo_scene sc, ray r);
 /*{\Xopl adds ray |r| to scene |sc|.}*/    
  
  list_item add_line(geo_scene sc, line l);
 /*{\Xopl adds line |l| to scene |sc|.}*/    
  
  list_item add_circle(geo_scene sc, circle c);
 /*{\Xopl adds circle |c| to scene |sc|.}*/    
  
  list_item add_gen_polygon(geo_scene sc, gen_polygon g);
 /*{\Xopl adds gen\_polygon |g| to scene |sc|.}*/    
  
  list_item add_remark(geo_scene sc,double x,double y,string rem);
  list_item add_remark(geo_scene sc,double x,double y,double wd,string rem);

 /*{\Xtext
    \medskip
    The following operations are used for setting/getting the
    attributes of an additional object. Every |set| operation
    returns the previous value.
    Every set/get operation gets as the first parameter the scene
    holding the additional object. The second parameter is the 
    |list_item| that was returned by the |add| operation. This
    parameter decribes the position of the object in the scene and 
    is used for retrieving the object.
  }*/  
  
  color additional_object_get_color(geo_scene sc, list_item it) const;  
  /*{\Xopl returns the boundary color of the additional object in scene |sc|
           at position |it|.
  }*/
  
  color additional_object_set_color(geo_scene sc, list_item it, color c);
  /*{\Xopl sets the boundary color of the additional object in scene |sc|
           at position |it| to |c|.
  }*/  
  
  color additional_object_get_fill_color(geo_scene sc, list_item it) const;
  /*{\Xopl returns the interior color of the additional object in scene |sc|
           at position |it|.
  }*/  
  
  color additional_object_set_fill_color(geo_scene sc, list_item it, color c);
  /*{\Xopl sets the interior color of the additional object in scene |sc|
           at position |it| to |c|.
  }*/  
  
  line_style additional_object_get_line_style(geo_scene sc, list_item it) const;
  /*{\Xopl returns the line style of the additional object in scene |sc|
           at position |it|.
  }*/  
  
  line_style additional_object_set_line_style(geo_scene sc, list_item it,line_style l);
  /*{\Xopl sets the line style of the additional object in scene |sc|
           at position |it| to |l|.
  }*/  
  
  int additional_object_get_line_width(geo_scene sc, list_item it) const;
  /*{\Xopl returns the line width of the additional object in scene |sc|
           at position |it|.
  }*/   
  
  int additional_object_set_line_width(geo_scene sc, list_item it,int l);  
  /*{\Xopl sets the line width of the additional object in scene |sc|
           at position |it| to |l|.
  }*/ 

  void delete_additional_object(geo_scene sc, list_item it);
  /*{\Xopl removes the additional object at position |it| from scene |sc|.}*/  
  
  void delete_additional_objects(geo_scene sc);
  /*{\Xopl removes all additional objects from scene |sc|.}*/   
  
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
  for that it was set and the reference to a |d3_window| that will be the output window.}*/
  { sc->init_d3_window = f; }
  
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

extern _exportF void update_gw(GeoWin *gw);
extern _exportF bool show_options(GeoScene* sc,panel* p,GeoWin *gw,color& filling_color,bool fredraw); 
extern _exportF bool show_options2(GeoScene* scn,panel* p,GeoWin *gw,color& filling_color,bool& high_light,bool fredraw);
extern _exportF void mouse_pos(long& MASK,GeoWin* gw, bool b);
extern _exportF void setup_focus_dialog(panel& p,color& c1,color& c2,int& lw,line_style& ls,string& label,bool  fredraw);


class _exportC GeoProp {
  protected:

  map<void*, void*> * original; 

  // color of the boundary of the object :
  map<void*, color>* color1_map;

  // color of the interior of the object :
  map<void*, color>* color2_map;

  map<void*, line_style>* lst_map;  
  map<void*, int>* lw_map;

  // labels for the objects
  map<void*, string>* label_map;

public:

  // Methods on colormap1 :
  bool colors_defined1()  { return  color1_map != 0; }

  void undefine_colors1() { if(color1_map) delete color1_map; color1_map = 0;}

  virtual color get_default_color1() = 0;
  virtual color get_sel_color() = 0; 

  color get_obj_color(void* o); 
  color  set_obj_color(void* obj, color c);

  // Methods on colormap2 :
  bool colors_defined2()  { if (color2_map==NULL) return false; else return true; }
  void undefine_colors2() { if(color2_map) delete color2_map; color2_map = 0; }

  virtual color get_default_color2() = 0;

  color get_obj_fill_color(void* o);
  color set_obj_fill_color(void* obj, color c);
  
  // Methods on line_style_map :
  bool line_styles_defined()   { if (lst_map==NULL) return false; else return true; }
  void undefine_line_styles()  { if(lst_map) delete lst_map; lst_map = 0; }
  
  virtual point_style get_default_point_style() = 0;

  virtual line_style get_default_line_style() = 0;

  line_style get_obj_line_style(void* o);
  line_style set_obj_line_style(void* obj, line_style lst);

  // Methods on line_width_map :
  bool line_width_defined()   { if (lw_map==NULL) return false; else return true; }
  void undefine_line_width()  { if(lw_map) delete lw_map; lw_map = 0; }

  virtual int get_default_line_width() = 0;

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

  void set_original_properties(void* o, void* obj);

  void set_def_properties(void* o);

  void original_properties(void* o);
  
  void set_default_properties(void* o);

  void undefine_all();

};

template<class T> class _exportC GeoTEditScene : public GeoEditor, public GeoProp
{  
  protected :
    
  window& (*draw_fcn)(window&, const T&);
  
  bool (*box_intersection_fcn)(const T& , double, double, double, double,bool);
  void (*get_bounding_box_fcn)(const T&, double&, double&, double&, double&);

  void (*move_fcn)(T& obj, double, double);
  void (*rotate_fcn)(T& obj, double, double, double);
  
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

  public :
  
  GeoTEditScene() : GeoEditor() 
  {
   color1_map = 0;
   color2_map = 0;
   lst_map    = 0;
   lw_map     = 0;
   label_map  = 0;
   original   = 0;
    
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
  
 
  T read_object(istream& is)          { T t; is >> t; return t; }
  void write_object(ostream& os, T t) { os << t; }
  

  void draw_object(const T& obj, window& w, PresentationType pt)
  {
    if (draw_fcn) 
    { draw_fcn(w, obj);
      return;
     }

    void*      adr  = (void*)(&obj);

    color c = get_obj_color(adr);
    if (pt != geowin_normal) c =  get_sel_color();

    color fc = get_obj_fill_color(adr);

    color       oldc = w.set_color(c);
    color       oldf = w.set_fill_color(fc);
    line_style  old_ls = w.set_line_style(get_obj_line_style(adr));
    int         oldw = w.set_line_width(get_obj_line_width(adr));

    point_style old_ps = w.set_point_style(get_default_point_style());

    w << obj; 

    string label;
    if (get_obj_label(adr,label))
    { // get bounding box and draw label
      double xw1,xw2,yw1,yw2;
      get_bounding_box_fcn(obj,xw1,xw2,yw1,yw2);
      setup_font(w,3);
      w.draw_ctext((xw1+xw2)/2,(yw1+yw2)/2,label,black);
    }     

    w.set_color(oldc);
    w.set_fill_color(oldf);
    w.set_point_style(old_ps);
    w.set_line_style(old_ls);
    w.set_line_width(oldw);
  } 
  

  bool intersects_rect(T& t, double x1, double y1, double x2, double y2)
  { return box_intersection_fcn(t, x1, y1, x2,y2, true); } //was get_obj_filled

  void get_bounding_box(T& t,  double& x1, double& x2, double& y1, double& y2)
  { get_bounding_box_fcn(t, x1, x2, y1, y2); }
  
  void move (T& t,  double dx, double dy)
  { if (move_fcn) move_fcn(t, dx, dy);  }
  
  void rotate (T& t,  double x, double y, double alpha)
  { if (rotate_fcn) rotate_fcn(t, x, y, alpha); }

  virtual void set_draw_fcn( window& (*f)(window&, const T&) )
  { draw_fcn = f; }
  
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

  // add_handlers
  void set_pre_add_handler(bool (*f)(GeoWin&, const T&))
  { pre_add_fcn = f; }
  void set_pre_add_changer(bool (*f)(GeoWin&, const T&, T&))
  { pre_add_changer = f; }  
  void set_post_add_handler(void (*f)(GeoWin&, const T&))
  { post_add_fcn = f; }
  
  // del_handlers
  void set_pre_del_handler(bool (*f)(GeoWin&, const T&))
  { pre_del_fcn = f; }
  void set_post_del_handler(void (*f)(GeoWin&, const T&))
  { post_del_fcn = f; }
  
  // change_handlers
  void set_start_change_handler(bool (*f)(GeoWin&, const T&))
  { start_change_fcn = f; }
  void set_pre_move_handler(bool (*f)(GeoWin&, const T&, double x, double y))
  { pre_move_fcn = f; }
  void set_post_move_handler(void (*f)(GeoWin&, const T&, double x, double y))
  { post_move_fcn = f; }
  void set_pre_rotate_handler(bool (*f)(GeoWin&, const T&, double x, double y, double a))
  { pre_rotate_fcn = f; }
  void set_post_rotate_handler(void (*f)(GeoWin&, const T&, double x, double y, double a))
  { post_rotate_fcn = f; }  
  void set_end_change_handler(void (*f)(GeoWin&, const T&))
  { end_change_fcn = f; }
};

template<class iterator>  struct _exportC geo_object_properties
{
  // class defines properties of edited objects
  iterator    pos;         // postion in edited container
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
GeoBaseScene<T>* get_base_prototype(T* t);


template<class T> class GeoBaseScene : public GeoScene, public GeoTEditScene<__typename T::value_type>
{  
  protected :

  typedef __typename T::iterator                iterator;
  typedef __typename T::value_type              GeoObj;
  typedef geo_object_properties<iterator>       geo_props;

  friend GeoBaseScene<T>* get_base_prototype __temp_friend_decl (T* t);

  friend class GeoBaseSceneBuilder<T>;

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
  bool                   myobjs;  //true,if the memory for the data object was allocated by this Geoscene
  
  void   (*redraw_fcn)(const T&, window&, color c1, color c2, 
		       double x1, double y1, double x2, double y2);

  
  string (*info_fcn)(const T&);

  bool  high_light;
  bool     mouse_obj_exist;
  iterator mouse_obj; 
  map<void*, geo_props>  props;
  bool   base_mode;

  
  GeoBaseScene() : GeoScene(0)
  {
    //b1();
    objs          = new T;
    myobjs        = true;
    redraw_fcn    = 0;
    info_fcn      = 0;
    base_mode     = true;
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

  //virtual functions from GeoEditor/ GeoProp

  virtual color get_default_color1()          { return col1; }
  virtual color get_sel_color()               { return col2; }
  virtual color get_default_color2()          { return filling_color; }
  virtual point_style get_default_point_style() { return p_style; }
  virtual line_style get_default_line_style() { return l_style; }
  virtual int  get_default_line_width()       { return get_line_width(); }

  virtual void mouse_read_object()            { }
  virtual void keyboard_read_object()         { }
  virtual void generate()                     { }
  virtual void toggle_selection()             { }
  virtual void select_in_rect(double x1, double y1, double x2, double y2) { }
  virtual void select_all() { }
  virtual void unselect()   { }
  virtual void copy()       { }
  virtual void paste()      { }
  virtual bool start_changing() { return true; }
  virtual void stop_changing()  { }
  virtual void move_sel(double dx, double dy) { }
  virtual void rotate_sel(double x, double y, double alpha)  { }

  virtual bool fill_rect(double &, double &, double &, double &) { return true; }
  virtual void del_sel()     { }
  virtual void del_focus()   { }
  virtual void setup_focus() { }
  virtual void obj_focus()   { }
  virtual void raise_object(){ }
  virtual void clear()       { }

  
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
    set_redraw_fcn(pr->redraw_fcn);
    set_info_fcn(pr->info_fcn);
  }
  
  virtual void init_data()
  {
    update();    
    update_gw(gw);
  }
  
  virtual string information()
  {
    string str(GeoScene::information());
    //cout << "Call info function!\n"; cout.flush();
    //cout << objs << "\n"; cout.flush();
    if( info_fcn && objs!=NULL) str += info_fcn(*objs);
    //cout << "after call!\n"; cout.flush();
    return str;
  }
  
  void set_redraw_fcn( void (*f) (const T&, window&, color, color,
				  double, double, double, double)   )
  {
    redraw_fcn = f;
  }

  
  void set_info_fcn( string (*f)(const T&)  ) { info_fcn = f; }

  bool get_select(const GeoObj& obj) 
  { 
    return (props.defined((void*)(&obj)) && props[(void*)(&obj)].selected);
  }

  void draw_object_with_properties(const GeoObj& obj)
  {
    window& w = gw->get_window();
    
    PresentationType pt = geowin_normal;
    if( get_select(obj) )  pt = geowin_selected; 

    if( mouse_obj_exist && high_light ) {  
      if ( !(mouse_obj != props[(void*)(&obj)].pos) ) {  pt = geowin_focus; } //egcs change
    }

    draw_object(obj, w, pt);
  }

  virtual void redraw(window* w, double x1, double y1, double x2, double y2)
  {
    int oldw  = w->set_line_width(get_line_width());
    line_style oldst = w->set_line_style(l_style);
    point_style oldpst= w->set_point_style(p_style);

    if (redraw_pt) { redraw_pt->operator() (*w,col1,col2,x1,y1,x2,y2); }
    else {
     if(redraw_fcn && base_mode)  redraw_fcn(*objs, *w, col1, col2, x1, y1, x2, y2); 
     else 
     {
       iterator it = objs->begin();
       while( it != objs->end() ) 
       { 
        draw_object_with_properties(*it); 
	it++;
       }
     }
    }

    GeoScene::redraw(w, x1, y1, x2, y2);
    w->set_point_style(oldpst);
    w->set_line_style(oldst);
    w->set_line_width(oldw);
  }

  virtual void options(panel* p)
  { 
    show_options((GeoScene*)this,p,gw,filling_color,true);
  }
  
  virtual void edit()
  {
    if ( gw) gw->redraw();
  }
  
  // Read - Write
  void write(ostream& os, string tr){
    iterator it   = objs->begin(), stop  = objs->end();
    if( it != stop )  { os << *it++; while( it != stop ) os << ' ' << tr << *it++;   }
    os.flush();
  }

  void write_postscript(ps_file& F)  {  
   if (redraw_pt){ if (redraw_pt->write_postscript(F,col1,col2)) return; }

    iterator it = objs->begin(), stop = objs->end();
  
     while(it != stop)
     {
	GeoObj& obj = *it;
  
	F.set_line_width((int)get_obj_line_width((void*)(&obj)));
	F.set_line_style(get_obj_line_style((void*)(&obj)));
        F.set_fill_color(get_obj_fill_color((void*)(&obj)));
        F.set_color(get_obj_color((void*)(&obj)));
        F << obj;
	it++;
     }
     
     GeoScene::write_postscript(F);
  }

  //void read(istream& is)   {  is >> *objs; init_data(); }
  void read(istream& in){
   objs->clear();
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
    //cout << " GeoEditSceneBuilder!\n"; cout.flush();

    GeoEditScene<T>* sc = 
      (GeoEditScene<T>*)(GeoScenePrototypes::get_prototype(prototypeid));
    sc->id = prototypeid;
  }
  
};

template<class T> GeoEditScene<T>* geowin_new_scene(GeoWin& gw, T& t);
template<class T> GeoEditScene<T>* geowin_new_scene(GeoWin& gw, T* t);
template<class T> GeoEditScene<T>* make_edit_prototype(T* t, string str);
template<class T> GeoEditScene<T>* get_edit_prototype(T* t);

template<class T> 
class  GeoEditScene : public GeoBaseScene<T>
{
  friend GeoEditScene<T>* geowin_new_scene __temp_friend_decl (GeoWin&, T&);
  friend GeoEditScene<T>* geowin_new_scene __temp_friend_decl (GeoWin&, T*);
  friend GeoEditScene<T>* make_edit_prototype __temp_friend_decl (T*, string);
  friend GeoEditScene<T>* get_edit_prototype __temp_friend_decl (T*);
  
  friend class _exportC GeoEditSceneBuilder<T>;

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
  
  protected :  

  void (*generate_fcn)(GeoWin& gw, T& L);

  list<GeoObj*>          sel_objs;
  list<GeoObj>           clip_objs;
                    

  GeoEditScene() : GeoBaseScene<T>()
  {
    //b2();
    edit_menu_type = edit_menu2;
    high_light = false;
    mouse_obj_exist = false;

    labels[geo_col0_label] = "interior";
    labels[geo_col1_label] = "boundary";
    labels[geo_col2_label] = "selected";

    base_mode = false;
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
           else { bvl=false; } //return false;
      
        }
        else it = objs->insert(objs->end(), obj);

        if (bvl){
         back=it;
	 geo_props gp(it);
         GeoObj& nwob = *it;
	 props[(void*)(&nwob)] = gp;
         set_default_properties((void*)(&nwob));
	 if(post_add_fcn) post_add_fcn(*gw, nwob);

	 return true;
	}
      }
    return false;
  }

  bool del_object(const GeoObj& obj)
  {
    if( !pre_del_fcn || pre_del_fcn(*gw, obj) )
      {
	set_select(obj, false);
	iterator it = props[(void*)(&obj)].pos;
	if( mouse_obj_exist && mouse_obj == it) 
               mouse_obj_exist = false; // egcs change
#if !defined(_MSC_VER)
	if (it == NULL) return false;
#endif
	objs->erase(it);

        set_default_properties((void*)(&obj));

	if( post_del_fcn ) post_del_fcn(*gw, obj);
	return true;
      }
    return false;
  }
  

  void set_select(const GeoObj& obj, bool b)
  {
    if( b != get_select(obj) )
      if( b ) props[(void*)(&obj)].selected = sel_objs.append((GeoObj*)(&obj));
      else
	{
	  sel_objs.del_item(props[(void*)(&obj)].selected);
	  props[(void*)(&obj)].selected = nil;
	}
  }
  
  void set_select(const list<GeoObj*>& L, bool b)
  {
    GeoObj* obj;
    forall(obj, L) set_select(*obj, b);
  }
  
  public :

  void set_generate_fcn(void (*f)(GeoWin& gw, T& L))
  { generate_fcn = f;}
  

  
  bool find_object(double x, double y)
  {
    if ( !gw ) return false;
    window& w = gw->get_window();
    //int g     = w.get_grid_mode();
    double d  = w.pix_to_real(1)* gw->get_mfct();
    // cout << d << "\n";
    //double d=1;
    double x1=x-d, x2=x+d, y1=y-d, y2=y+d;
    
    iterator it = objs->begin(), stop = objs->end();
    GeoObj obj;

    iterator old_mouse_obj=mouse_obj; 
    bool ex=mouse_obj_exist;

    mouse_obj_exist = false;

    while(it != stop)
      {
	obj = *it;
	if( intersects_rect(obj, x1, y1, x2, y2) )
	  {
	    mouse_obj_exist = true;
	    mouse_obj = it;
	  }
	it++;
      }

    if (high_light && ex && (!mouse_obj_exist ||  old_mouse_obj!=mouse_obj))
      { GeoObj& hlp=*old_mouse_obj; draw_object_with_properties(hlp); }

    if (high_light && mouse_obj_exist && (!ex || old_mouse_obj!=mouse_obj))
      { GeoObj& hlp=*mouse_obj; draw_object_with_properties(hlp); }
   
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
    
    set_draw_fcn(pr->draw_fcn);
    set_box_intersection_fcn(pr->box_intersection_fcn);
    set_get_bounding_box_fcn(pr->get_bounding_box_fcn);    
    set_move_fcn(pr->move_fcn);
    set_rotate_fcn(pr->rotate_fcn);
    set_generate_fcn(pr->generate_fcn);
    
    set_pre_add_handler(pr->pre_add_fcn);
    set_pre_add_changer(pr->pre_add_changer);
    set_post_add_handler(pr->post_add_fcn);
    set_pre_del_handler(pr->pre_del_fcn);
    set_post_del_handler(pr->post_del_fcn);
    set_start_change_handler(pr->start_change_fcn);
    set_pre_move_handler(pr->pre_move_fcn);
    set_post_move_handler(pr->post_move_fcn);
    set_pre_rotate_handler(pr->pre_rotate_fcn);
    set_post_rotate_handler(pr->post_rotate_fcn);    
    set_end_change_handler(pr->end_change_fcn);
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

    GeoBaseScene<T>::init_data(); 
  }
 
  virtual void edit() { if(gw) gw->edit(this); }
  
  virtual void mouse_at_pos(double x, double y, long& MASK)
  {
    mouse_pos(MASK,gw, find_object(x,y));
  }

  // virtual GeoEditor members
  virtual void mouse_read_object()
  {
    GeoObj t;
    window& w = gw->get_window();
    iterator it;

    if( w >> t )
      {
	if( !add_object(t,it) )  return; 
	if( !results.empty() )
	  {
	    update();
	    gw->redraw();
	  }
	else draw_object_with_properties(t);
	gw->update_status_line();
      }
  }

  virtual void keyboard_read_object()
  {
    GeoObj t;
    iterator it;

    string_ostream O;
    string nval;
    int but;
    panel p;
    p.text_item("\\bf\\blue Input new object:");
    p.text_item("");
    p.string_item("New value:",nval );
	
    p.fbutton("apply",   APPLY_BUTTON); 
    p.button("cancel",   CANCEL_BUTTON);
    but=p.open(gw->get_window());

    if( but == CANCEL_BUTTON ) return;
    string_istream IS(nval);
    IS >> t;

    //cin >> t;
    if( !add_object(t,it) )  return; 
    if( !results.empty() )
    {
       update();
       gw->redraw();
    }
    else draw_object_with_properties(t);
    gw->update_status_line();
  }


  virtual void toggle_selection() 
  {
    if( mouse_obj_exist )
      {
	GeoObj& obj  = *mouse_obj;
	set_select(obj, !get_select(obj));
	if( gw ) draw_object_with_properties(obj);
      }
  }
  
  virtual void options(panel* p)
  {  
    show_options2((GeoScene*)this,p,gw,filling_color,high_light,true);
  }

  virtual void select_in_rect(double x1, double y1, double x2, double y2)
  {
    bool sel = false;
    list<GeoObj*> tmp;
    iterator it = objs->begin();
    iterator stop = objs->end();
    
    while(it != stop ) 
      {
       if( intersects_rect(*it, x1, y1, x2, y2) ) { GeoObj& act=*it; tmp.append(&act); }
       it++;
     }
    
    GeoObj* obj;
    forall(obj, tmp)    if( !get_select(*obj) )   { sel = true; break; }
    set_select(tmp, sel);
    if( !tmp.empty() && gw ) gw->redraw();
  }

  virtual void select_all()
  {
    bool sel = false;
    list<GeoObj*> tmp;
    iterator it = objs->begin();
    iterator stop = objs->end();
    
    while(it != stop ) 
      {
       GeoObj& act=*it;
       tmp.append(&act);
       it++;
     }
    
    GeoObj* obj;
    forall(obj, tmp)    if( !get_select(*obj) )   { sel = true; break; }
    set_select(tmp, sel);
    if( !tmp.empty() && gw ) gw->redraw();    
  }
  
  virtual void unselect()
  {
    set_select(sel_objs, false);
    gw->redraw();
  }
  

  virtual void copy()
  {
    if( !sel_objs.empty() )
      {
	clip_objs.clear();
	GeoObj* obj;
	GeoObj obj2;
	forall(obj, sel_objs) { 
	  obj2 = *obj;
          clip_objs.append(obj2); // ! Achtung !
        }
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
	    add_object(obj,it);
            GeoObj& obnew= *it;
            set_select(obnew,true);
	    draw_object_with_properties(obnew);
	  }

	clip_objs.clear();
	update();
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
	GeoObj* obj;
	
	forall(obj, sel_objs) 
	  {
	    if( start_change_fcn && !start_change_fcn(*gw, *obj) ) return false;
	    (*original)[(void*)obj] = (void*)obj;
	  }
      }
    while_dragging = true;
    return true;
  }
  
  virtual void stop_changing()
  {
    GeoObj* obj;

    if( mouse_changing )
      {
	if ( end_change_fcn ) end_change_fcn(*gw, *mouse_obj);
	mouse_changing = false;
        GeoObj& mob= *mouse_obj;
	original_properties((void*)(&mob)); 
      }
    else
      forall(obj, sel_objs)
      {
	if ( end_change_fcn ) end_change_fcn(*gw, *obj);
	original_properties((void*)obj);
      }
    
    while_dragging = false;
    delete original;
    original = 0;
    update();
    gw->redraw();
  }

  virtual void move_sel(double dx, double dy)
  { 
    if( !mouse_changing && sel_objs.empty() ) return;
    
    if( mouse_changing )
      {
	GeoObj& obj1 = *mouse_obj;
	if ( !pre_move_fcn  || (pre_move_fcn(*gw,obj1,dx,dy))){
	 move( obj1, dx, dy);
	 if (post_move_fcn) post_move_fcn(*gw,obj1,dx,dy);
	}
      }
    else
      {
        GeoObj* obj1;

	forall(obj1, sel_objs)
	  {
	   if (!pre_move_fcn  || (pre_move_fcn(*gw,*obj1,dx,dy))){	  
	     move( *obj1, dx, dy);
	     if (post_move_fcn) post_move_fcn(*gw,*obj1,dx,dy);
	   }
	  }
      }
	
     update(); 
     gw->redraw();
  }

  virtual void rotate_sel(double x, double y, double alpha)
  {
    if( !mouse_changing && sel_objs.empty() ) return;
    
    if( mouse_changing )
      {
	GeoObj& obj1 = *mouse_obj;
	if (!pre_rotate_fcn  || (pre_rotate_fcn(*gw,obj1,x,y,alpha))){	
	 rotate( obj1, x, y, alpha);
	 if (post_rotate_fcn) post_rotate_fcn(*gw,obj1,x,y,alpha);
	}
      }
    else
      {
        GeoObj* obj1;

	forall(obj1, sel_objs)
	  {
	   if (!pre_rotate_fcn || (pre_rotate_fcn(*gw,*obj1,x,y,alpha))){	  
	    rotate( *obj1, x, y, alpha);
	    if (post_rotate_fcn) post_rotate_fcn(*gw,*obj1,x,y,alpha);
	   }	   
	  }
      }
	
     update(); 
     gw->redraw();
  }

  virtual void del_focus()
  {
    if (mouse_obj_exist)
    { if (get_select(*mouse_obj)) del_sel();
      else
        if (del_object(*mouse_obj))
        { update();
          gw->redraw();
          gw->update_status_line();
         }
    }
  }
 

  virtual void del_sel()
  {
    if ( !sel_objs.empty() )
      {
	GeoObj* obj;
	forall(obj, sel_objs)  del_object(*obj);
	update();
	gw->redraw();
	gw->update_status_line();
      }
  }
  
  virtual bool fill_rect(double& x1, double& x2, double& y1, double& y2)
  {
    iterator it = objs->begin();
    iterator stop = objs->end();
   
    if ( it != stop ) get_bounding_box( *it++, x1, x2, y1, y2 );
    else return false;

    double x1akt,x2akt,y1akt,y2akt;

    while( it != stop ) {
       get_bounding_box( *it++, x1akt, x2akt, y1akt, y2akt );
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
    
    while( it != stop ) del_object( *it++ );
    if (objs->empty()){
     sel_objs.clear(); 
     props.clear();
     mouse_obj_exist = false;

     undefine_all();
    }
    
    update();

    gw->redraw();
    gw->update_status_line();
    }
  }

  virtual void generate()
  {
    T tmp;
    generate_fcn(*gw, tmp);
    iterator it = tmp.begin(),hlp;
    while( it != tmp.end() ) add_object(*it++,hlp);
    update(); 
    gw->redraw();
    gw->update_status_line();
  }
  
  virtual void setup_focus()
  {
    if( mouse_obj_exist )
      {
	window& w = gw->get_window();
	panel p("Object Properties");
	GeoObj& objct    = *mouse_obj;
        void* obj        = (void*)(&objct);

	color c1      = get_obj_color(obj);
	color c2      = get_obj_fill_color(obj);
	int   lw     = get_obj_line_width(obj);
	line_style ls = get_obj_line_style(obj);

        string label,old_label;
        if (! get_obj_label(obj,label)) label="";

        setup_focus_dialog(p,c1,c2,lw,ls,label, true);
		
	int but;
	while( (but=p.open(w)) == DEFAULTS_BUTTON )
	  {
	    c1 = get_default_color1();
	    c2 = get_default_color2();
	    lw = get_default_line_width();
	    ls = get_default_line_style();
	  }

	if( but == CANCEL_BUTTON ) return;
	
	if( c1 != get_obj_color(obj) ) set_obj_color(obj, c1);
	if( c2 != get_obj_fill_color(obj) ) set_obj_fill_color(obj, c2);
	if( lw != get_obj_line_width(obj)) set_obj_line_width(obj, lw);
	if( ls != get_obj_line_style(obj)) set_obj_line_style(obj, ls);

        if (! get_obj_label(obj,old_label)) old_label="";        
        if( label != old_label) { set_obj_label(obj, label); }
	
	double x1,  x2, y1, y2;
      
	get_bounding_box( objct, x1, x2, y1, y2 );
	gw->redraw(x1, y1, x2, y2);
      }
  }

  virtual void obj_focus(){
    if( mouse_obj_exist )
      {
	GeoObj& obj = *mouse_obj; 
        void* objptr= (void*)(&obj);

        GeoObj obj2;
        string_ostream O;
        string nval;
        int but;
	panel p;
        p.set_item_width(240);
        p.text_item("\\bf\\blue Object");
        p.text_item("");
        O <<  obj << ends;
        p.text_item(O.str()); p.text_item(""); 
        nval=O.str();
        p.string_item("new value",nval );
	
        p.fbutton("apply",   APPLY_BUTTON); 
        p.button("cancel",   CANCEL_BUTTON);
        but=p.open(gw->get_window());

        if( but == CANCEL_BUTTON ) return;
        string_istream IS(nval);
        IS >> obj2;
 
        iterator zg;

        if (add_object(obj2,zg)){
         GeoObj& zlo = *zg;
         set_original_properties((void*)(&zlo) ,objptr);
         del_object(obj);
        }
       
        update();
        gw->redraw();
      }
  }
  
  virtual void raise_object(){
     if( mouse_obj_exist )
      {
	GeoObj& obj = *mouse_obj; 
        void* objptr= (void*)(&obj);
        GeoObj obj2 = obj;
        iterator zg;

        if (add_object(obj2,zg)){
         GeoObj& zlo = *zg;
         set_original_properties((void*)(&zlo) ,objptr);
         del_object(obj);
        }
       
        update();
        gw->redraw();	
      } 
  }

};

#ifndef NO_STATIC_DATA_MEMBER
template<class T> GeoEditSceneBuilder<T> GeoEditScene<T>::sb2;
#endif

template<class T> GeoEditScene<T>* geowin_new_scene(GeoWin& gw, T& t)
{
  GeoEditScene<T>* sc = (GeoEditScene<T>*)(GeoEditScene<T>::b2().new_scene());
  sc->set_objref(t);
  gw.insert(sc);
  sc->init_default_values();
  return sc;
}

template<class T> GeoEditScene<T>* geowin_new_scene(GeoWin& gw, T* t)
{
  GeoEditScene<T>* sc = (GeoEditScene<T>*)(GeoEditScene<T>::b2().new_scene());
  gw.insert(sc);
  sc->init_default_values();  
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
					  R&, string str);

template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw,
					  void (*f)(const S&, R&),
					  GeoBaseScene<S>*, 
					  R*, string str);


template<class S, class R> class GeoResultScene : public GeoBaseScene<R>
{ 
  friend class _exportC GeoResultSceneBuilder<S,R>;

public:

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

  // first parameter GeoWin of the result scene, second parameter input scene
  // third parameter result scene...
  void (*update_fcn2)(const S&, R&);

  geowin_update<S,R>* pt_update;
  
  GeoResultScene() : GeoBaseScene<R>() 
  { 
    //b3();
    update_fcn2=NULL;
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

  void set_update_object(geowin_update<S,R>& up)
  {
    pt_update= &up;
  }

  void set_update_fcn2( void (*f)(const S&, R&) )
  { update_fcn2 = f; }
  
  virtual void update()
  {
    float timeact= used_time();

   if (is_visible()){
    if (pt_update != NULL) {  pt_update->update(input_scene->get_objref(),*objs) ;  }
    else {
      if (update_fcn2 != NULL) update_fcn2(input_scene->get_objref(), *objs);
    }
   }

   if (gw && gw->get_time_meas() && (pt_update!=NULL || update_fcn2!=NULL))
      cout << get_name() << ":" << used_time(timeact) << " s.\n";
   GeoBaseScene<R>::update();

  } 
  

};

#ifndef NO_STATIC_DATA_MEMBER2 
template<class S, class R> GeoResultSceneBuilder<S,R> GeoResultScene<S,R>::sb3;
#endif


template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw, 
					  void (*f)(const S&, R&),
					  GeoBaseScene<S>* input, 
					  R& r, string str)
{
  GeoResultScene<S,R>* sc = 
    (GeoResultScene<S,R>*)(GeoResultScene<S,R>::b3().new_scene());
  sc->set_base_name(str);
  sc->set_objref(t);
  sc->set_input_scene(input);  
  sc->set_update_fcn2(f);
  
  gw.insert(sc);
  sc->init_default_values(); 
  sc->update(); 
  return sc; 
}

template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw,
					  void (*f)(const S&,R&),
					  GeoBaseScene<S>* input, 
					  string str, int fl)
{
  GeoResultScene<S,R>* sc = 
    (GeoResultScene<S,R>*)(GeoResultScene<S,R>::b3().new_scene());
  sc->set_base_name(str);
  sc->set_input_scene(input);
  sc->set_update_fcn2(f);
 
  gw.insert(sc);
  sc->init_default_values();
  sc->update();  
  return sc; 
}


template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw,
					  void (*f)(const S&,R&), geo_scene sc, 
					  string str)
{
  return geowin_new_scene(gw, f, (GeoBaseScene<S>*)sc, str, 0);
}

template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw, geowin_update<S,R>& up, geo_scene sc,string name)
{
  GeoResultScene<S,R>* res =  (GeoResultScene<S,R>*)(GeoResultScene<S,R>::b3().new_scene());
  res->set_base_name(name);
  res->set_input_scene((GeoBaseScene<S>*)sc); 
  res->set_update_object(up);
 
  gw.insert(res);
  res->init_default_values();
  res->update();  
  return res;  
}

template<class S, class R>
GeoResultScene<S,R>* geowin_new_scene(GeoWin& gw, geowin_update<S,R>& up,geowin_redraw& rb, geo_scene sc,string name)
{
  GeoResultScene<S,R>* res =  (GeoResultScene<S,R>*)(GeoResultScene<S,R>::b3().new_scene());
  res->set_base_name(name);
  res->set_input_scene((GeoBaseScene<S>*)sc); 
  res->set_update_object(up);

  gw.insert(res);
  res->init_default_values();
  gw.set_redraw_pt(res, &rb); 
  res->update();  
  return res;  
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


inline void GeowinMember::call(GeoWin& gw) { (gw.*f)(); }

//  template functions for setting handlers ...
// add handler
  
template<class T,class F>
bool geowin_set_pre_add_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->set_pre_add_handler(handler); 
 return true;
}
  
template<class T,class F>
bool geowin_set_pre_add_change_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->set_pre_add_changer(handler); 
 return true;
}
  
template<class T,class F>
bool geowin_set_post_add_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->set_post_add_handler(handler); 
 return true;
}

// delete handler
    
template<class T,class F>
bool geowin_set_pre_del_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->set_pre_del_handler(handler); 
 return true;
}
  
template<class T,class F>
bool geowin_set_post_del_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->set_post_del_handler(handler); 
 return true;
}
  
// change handler
  
template<class T,class F>
bool geowin_set_start_change_handler(GeoEditScene<T>* sc, F handler )
{
 if (sc == NULL) return false;
 sc->set_start_change_handler(handler); 
 return true;
}

template<class T,class F>
bool geowin_set_pre_move_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->set_pre_move_handler(handler); 
 return true;
}
  
template<class T,class F>
bool geowin_set_post_move_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->set_post_move_handler(handler); 
 return true;
}
  
template<class T,class F>
bool geowin_set_pre_rotate_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->set_pre_rotate_handler(handler); 
 return true;
}
  
template<class T,class F>
bool geowin_set_post_rotate_handler(GeoEditScene<T>* sc, F handler )
{ 
 if (sc == NULL) return false;
 sc->set_post_rotate_handler(handler); 
 return true;
}

template<class T,class F>
bool geowin_set_end_change_handler(GeoEditScene<T>* sc, F handler )
{
 if (sc == NULL) return false;
 sc->set_end_change_handler(handler); 
 return true; 
}

template<class T>
bool geowin_set_generate_fcn(GeoEditScene<T>* sc, void (*f)(GeoWin& gw,T& L))
{
 if (sc == NULL) return false;
 sc->set_generate_fcn(f);
 return true;
}

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
{ return sc->set_obj_line_width(adr,l); }    


GEOWIN_END_NAMESPACE


#if LEDA_ROOT_INCL_ID == 400090
#undef LEDA_ROOT_INCL_ID
#include <LEDA/UNDEFINE_NAMES.h>
#endif


#endif



