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
// file          : src/GeoWin/LEDA/geowin_init.h
// package       : GeoWin (1.0.8)
// revision      : 1.0.8
// revision_date : 17 December 1999 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken>)
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef LEDA_GEOWIN_ADDITIONAL_H
#define LEDA_GEOWIN_ADDITIONAL_H

#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 400951
#include <LEDA/REDEFINE_NAMES.h>
#endif

#include <LEDA/geowin.h>
#include <LEDA/d3_rat_point.h>


GEOWIN_BEGIN_NAMESPACE

bool geowin_IntersectsBox(const point&, double, double, double, double, bool); 
bool geowin_IntersectsBox(const segment&, double, double, double, double, bool );
bool geowin_IntersectsBox(const ray&, double, double, double, double, bool);
bool geowin_IntersectsBox(const line&, double, double, double, double, bool);
bool geowin_IntersectsBox(const circle&, double, double, double, double, bool);
bool geowin_IntersectsBox(const polygon&,  double, double, double, double, bool);
bool geowin_IntersectsBox(const gen_polygon&,  double, double, double, double, bool);
bool geowin_IntersectsBox(const d3_point&, double, double, double, double, bool);
bool geowin_IntersectsBox(const rectangle&, double, double, double, double, bool);


void geowin_BoundingBox(const point&, double&, double&, double&, double&);
void geowin_BoundingBox(const segment&, double&, double&, double&, double&);
void geowin_BoundingBox(const ray&, double&, double&, double&, double&);
void geowin_BoundingBox(const line&, double&, double&, double&, double&);
void geowin_BoundingBox(const circle&, double&, double&, double&, double&);
void geowin_BoundingBox(const polygon&, double&, double&, double&, double&);
void geowin_BoundingBox(const gen_polygon&, double&, double&, double&, double&);
void geowin_BoundingBox(const d3_point&, double&, double&, double&, double&);
void geowin_BoundingBox(const rectangle&, double&, double&, double&, double&);


void geowin_Translate(point& obj, double dx, double dy);
void geowin_Translate(segment& obj, double dx, double dy);
void geowin_Translate(ray& obj, double dx, double dy);
void geowin_Translate(line& obj, double dx, double dy);
void geowin_Translate(circle& obj, double dx, double dy);
void geowin_Translate(polygon& obj, double dx, double dy);
void geowin_Translate(gen_polygon& obj, double dx, double dy);
void geowin_Translate(d3_point& p, double dx, double dy);
void geowin_Translate(rectangle& obj, double dx, double dy);


void geowin_Rotate(point& obj, double x, double y, double a);
void geowin_Rotate(segment& obj, double x, double y, double a);
void geowin_Rotate(ray& obj, double x, double y, double a);
void geowin_Rotate(line& obj, double x, double y, double a);
void geowin_Rotate(circle& obj, double x, double y, double a);
void geowin_Rotate(polygon& obj, double x, double y, double a);
void geowin_Rotate(gen_polygon& obj, double x, double y, double a);
void geowin_Rotate(d3_point& p, double x, double y, double a);
void geowin_Rotate(rectangle& obj, double x, double y, double a);


void geowin_generate_objects(GeoWin& gw, list<point>& L);
void geowin_generate_objects(GeoWin& gw, list<segment>& S);
void geowin_generate_objects(GeoWin& gw, list<ray>& L);
void geowin_generate_objects(GeoWin& gw, list<line>& L);
void geowin_generate_objects(GeoWin& gw, list<circle>& C);
void geowin_generate_objects(GeoWin& gw, list<polygon>& Pl);
void geowin_generate_objects(GeoWin& gw, list<gen_polygon>& Pl);
void geowin_generate_objects(GeoWin& gw, list<d3_point>& Pl);
void geowin_generate_objects(GeoWin& gw, list<rectangle>& Pl);


#if !defined(NO_RAT_ALGORITHMS)

void geowin_Translate(rat_point& obj, double dx, double dy);
void geowin_Translate(rat_segment& obj, double dx, double dy);
void geowin_Translate(rat_ray& obj, double dx, double dy);
void geowin_Translate(rat_line& obj, double dx, double dy);
void geowin_Translate(rat_circle& obj, double dx, double dy);
void geowin_Translate(rat_polygon& obj, double dx, double dy);
void geowin_Translate(rat_gen_polygon& obj, double dx, double dy);
void geowin_Translate(d3_rat_point& p, double dx, double dy);
void geowin_Translate(rat_rectangle& obj, double dx, double dy);

void geowin_Rotate(rat_point& obj, double x, double y, double a);
void geowin_Rotate(rat_segment& obj, double x, double y, double a);
void geowin_Rotate(rat_ray& obj, double x, double y, double a);
void geowin_Rotate(rat_line& obj, double x, double y, double a);
void geowin_Rotate(rat_circle& obj, double x, double y, double a);
void geowin_Rotate(rat_polygon& obj, double x, double y, double a);
void geowin_Rotate(rat_gen_polygon& obj, double x, double y,double a);
void geowin_Rotate(d3_rat_point& p, double x, double y, double a);
void geowin_Rotate(rat_rectangle& obj, double x, double y, double a);


bool geowin_IntersectsBox(const rat_point& p, double, double, double, double, bool);
bool geowin_IntersectsBox(const rat_segment& s, double, double, double, double, bool);
bool geowin_IntersectsBox(const rat_ray& r, double, double, double, double, bool); 
bool geowin_IntersectsBox(const rat_line& l, double, double, double, double, bool); 
bool geowin_IntersectsBox(const rat_circle& c, double, double, double, double, bool); 
bool geowin_IntersectsBox(const rat_polygon& p, double, double, double, double, bool);
bool geowin_IntersectsBox(const rat_gen_polygon& p, double, double, double, double, bool);
bool geowin_IntersectsBox(const d3_rat_point&, double, double, double, double, bool);
bool geowin_IntersectsBox(const rat_rectangle&, double, double, double, double, bool);


void geowin_BoundingBox(const rat_point&, double&, double&, double&, double&);
void geowin_BoundingBox(const rat_segment&, double&, double&, double&, double&);
void geowin_BoundingBox(const rat_ray&, double&, double&, double&, double&);
void geowin_BoundingBox(const rat_line&, double&, double&, double&, double&);
void geowin_BoundingBox(const rat_circle&, double&, double&, double&, double&);
void geowin_BoundingBox(const rat_polygon&, double&, double&, double&, double&);
void geowin_BoundingBox(const rat_gen_polygon&, double&, double&, double&, double&);
void geowin_BoundingBox(const d3_rat_point&, double&, double&, double&, double&);
void geowin_BoundingBox(const rat_rectangle&, double&, double&, double&, double&);


void geowin_generate_objects(GeoWin& gw, list<rat_point>& L);
void geowin_generate_objects(GeoWin& gw, list<rat_segment>& L);
void geowin_generate_objects(GeoWin& gw, list<rat_ray>& L);
void geowin_generate_objects(GeoWin& gw, list<rat_line>& L);
void geowin_generate_objects(GeoWin& gw, list<rat_circle>& L);
void geowin_generate_objects(GeoWin& gw, list<rat_polygon>& L);
void geowin_generate_objects(GeoWin& gw, list<rat_gen_polygon>& L);
void geowin_generate_objects(GeoWin& gw, list<d3_rat_point>& L); 
void geowin_generate_objects(GeoWin& gw, list<rat_rectangle>& L); 

#endif




template<class T>
void geowin_fredraw_fcn(const list<T>& L, window& w, color c1, color c2, 
		     bool filled,  double x1, double y1, double x2, double y2)
{
  T t;  
  forall(t, L) 
    if ( geowin_IntersectsBox(t, x1, y1, x2, y2,filled) )
    { if (filled)
         w.set_fill_color(c2);
      else
         w.set_fill_color(invisible);
      w.set_color(c1);
      w << t;
     }
}


template<class T>
string geowin_info_fcn(const list<T>& L)
{ int n = L.length();
  if (n == 1)
    return string("\\black\\tt %d %s", n, leda_tname((T*)0));
  else
    return string("\\black\\tt %d %ss",n, leda_tname((T*)0));
}


template<class T> void geowin_init_default_type( T* t, string str)
{ 
  //links a string (the scene-typename) with the real type
 
  GeoEditScene< T >* sc = make_edit_prototype(t, str);

  sc->set_redraw_fcn(0);

#if !defined GEOWIN_USE_NAMESPACE
  string (*f)(const T&) = geowin_info_fcn;
  sc->set_info_fcn(f);
  sc->set_box_intersection_fcn(geowin_IntersectsBox);
  sc->set_get_bounding_box_fcn(geowin_BoundingBox);
  sc->set_move_fcn(geowin_Translate);
  sc->set_rotate_fcn(geowin_Rotate);
  sc->set_generate_fcn(geowin_generate_objects);
#else
  string (*f)(const T&) = GEOWIN_NAMESPACE_NAME::geowin_info_fcn;
  sc->set_info_fcn(f);
  sc->set_box_intersection_fcn(GEOWIN_NAMESPACE_NAME::geowin_IntersectsBox);
  sc->set_get_bounding_box_fcn(GEOWIN_NAMESPACE_NAME::geowin_BoundingBox);
  sc->set_move_fcn(GEOWIN_NAMESPACE_NAME::geowin_Translate);
  sc->set_rotate_fcn(GEOWIN_NAMESPACE_NAME::geowin_Rotate);
  sc->set_generate_fcn(GEOWIN_NAMESPACE_NAME::geowin_generate_objects);
#endif
} 


template<class T> void geowin_init_basic_type(T* t,string str)
{
  GeoEditScene< T >* sc = make_edit_prototype(t, str);
  sc->set_redraw_fcn(0);

#if !defined GEOWIN_USE_NAMESPACE  
  sc->set_box_intersection_fcn(geowin_IntersectsBox);
  sc->set_get_bounding_box_fcn(geowin_BoundingBox);
#else
  sc->set_box_intersection_fcn(GEOWIN_NAMESPACE_NAME::geowin_IntersectsBox);
  sc->set_get_bounding_box_fcn(GEOWIN_NAMESPACE_NAME::geowin_BoundingBox);
#endif
}


GEOWIN_END_NAMESPACE

#if LEDA_ROOT_INCL_ID == 400951
#undef LEDA_ROOT_INCL_ID
#include <LEDA/UNDEFINE_NAMES.h>
#endif


#endif // _GEOWIN_ADDITIONAL_

