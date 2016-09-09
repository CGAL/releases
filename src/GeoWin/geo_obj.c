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
// file          : src/GeoWin/geo_obj.c
// package       : GeoWin (1.0.8)
// revision      : 1.0.8
// revision_date : 17 December 1999 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken@informatik.uni-halle.de>)
// ============================================================================

#include <LEDA/geowin.h>

GEOWIN_BEGIN_NAMESPACE

// ******************* GeoWin GeoObjects *************************
 
GeoWin_GeoObj::GeoWin_GeoObj(const point& p)
{
 init();
 point* zg= new point;
 *zg=p;
 object_ptr= (void*) zg;
 mode=1;
}
  
GeoWin_GeoObj::GeoWin_GeoObj(const segment& s)
{
 init();
 segment* zg= new segment;
 *zg=s;
 object_ptr= (void*) zg;
 mode=2; 
}

GeoWin_GeoObj::GeoWin_GeoObj(const ray& r)
{
 init();
 ray* zg= new ray;
 *zg=r;
 object_ptr= (void*) zg;
 mode=3; 
}

GeoWin_GeoObj::GeoWin_GeoObj(const line& l)
{
 init();
 line* zg= new line;
 *zg=l;
 object_ptr= (void*) zg;
 mode=4;
}

GeoWin_GeoObj::GeoWin_GeoObj(const circle& c)
{
 init();
 circle* zg= new circle;
 *zg=c;
 object_ptr= (void*) zg;
 mode=5;
}

GeoWin_GeoObj::GeoWin_GeoObj(const gen_polygon& g)
{
 init();
 gen_polygon* zg= new gen_polygon;
 *zg=g;
 object_ptr= (void*) zg;
 mode=6;
}

GeoWin_GeoObj::GeoWin_GeoObj(const GeoRemark& g)
{
 init();
 GeoRemark* zg= new GeoRemark;
 *zg=g;
 object_ptr= (void*) zg;
 mode=7;
}

GeoWin_GeoObj::GeoWin_GeoObj(const GeoWin_GeoObj& g)
{
 my_scene=g.my_scene;
 mode=g.mode;
 interior=g.interior;
 boundary=g.boundary;
 l_style=g.l_style;
 l_width=g.l_width;
 switch(mode) {
 case 1:
 {
   point* zg= new point;
   *zg= *((point*)(g.object_ptr));
   object_ptr= (void*) zg;
   break;
 }
 case 2:
 {
   segment* zg= new segment;
   *zg= *((segment*)(g.object_ptr));
   object_ptr= (void*) zg;
   break;
 }
 case 3:
 {
   ray* zg= new ray;
   *zg= *((ray*)(g.object_ptr));
   object_ptr= (void*) zg;
   break;
 }
 case 4:
 {
   line* zg= new line;
   *zg= *((line*)(g.object_ptr));
   object_ptr= (void*) zg;
   break;
 }
 case 5:
 {
   circle* zg= new circle;
   *zg= *((circle*)(g.object_ptr));
   object_ptr= (void*) zg;
   break;
 }
 case 6:
 {
   gen_polygon* zg= new gen_polygon;
   *zg= *((gen_polygon*)(g.object_ptr));
   object_ptr= (void*) zg;
   break;
 }
 case 7:
 {
   GeoRemark* zg= new GeoRemark;
   *zg= *((GeoRemark*)(g.object_ptr));
   object_ptr= (void*) zg;
   break;
 }
 }
}
   
GeoWin_GeoObj::~GeoWin_GeoObj()
{

  //cout << "Destruktor!\n"; cout.flush();
  
// free the allocated memory ...
  switch(mode) {
  case 1:
   { 
     point* pt= (point*)object_ptr;
     delete pt;
     break;
   }
  case 2:
   {
     segment* pt= (segment*)object_ptr;
     delete pt;
     break;
   }
  case 3:
   {
     ray* pt= (ray*)object_ptr;
     delete pt;
     break;
   }
  case 4:
   {
     line* pt= (line*)object_ptr;
     delete pt;
     break;
   }
  case 5:
   { 
     circle* pt= (circle*)object_ptr;
     delete pt;
     break;
   }
  case 6:
   {
     gen_polygon* pt= (gen_polygon*)object_ptr;
     delete pt;
     break;
   }
  case 7:
   { 
     GeoRemark* pt= (GeoRemark*)object_ptr;
     delete pt;
     break;
   }
  }
}

int GeoWin_GeoObj::get_mode() const
{
 return mode;
}

void* GeoWin_GeoObj::get_ptr()
{
 return object_ptr;
}

void GeoWin_GeoObj::draw(window& W) const
{
 // set the parameter of the object ...
 color fc = W.set_fill_color(interior);
 color bd = W.set_color(boundary);
 line_style ls = W.set_line_style(l_style);
 int lw = W.set_line_width(l_width);
 
 switch(mode) {
  case 1:
   { 
     point* pt= (point*)object_ptr;
     W << (*pt);
     break;
   }
  case 2:
   {
     segment* pt= (segment*)object_ptr;
     W << (*pt);
     break;
   }
  case 3:
   {
     ray* pt= (ray*)object_ptr;
     W << (*pt);
     break;
   }
  case 4:
   {
     line* pt= (line*)object_ptr;
     W << (*pt);
     break;
   }
  case 5:
   { 
     circle* pt= (circle*)object_ptr;
     W << (*pt);
     break;
   }
  case 6:
   {
     gen_polygon* pt= (gen_polygon*)object_ptr;
     W << (*pt);
     break;
   }
  case 7:
   { 
     GeoRemark* pt= (GeoRemark*)object_ptr;
     W << (*pt);    
     break;
   }
  }

 //restore the parameter of the object
 W.set_fill_color(fc);
 W.set_color(bd);
 W.set_line_style(ls);
 W.set_line_width(lw);
}

void GeoWin_GeoObj::write_ps(ps_file& ps) const
{
 // set the parameter of the object ...
 
 ps.set_line_style(l_style);
 ps.set_line_width((int)l_width);
 
 switch(mode) {
  case 1:
   { 
     point* pt= (point*)object_ptr;
     ps.set_fill_color(interior);
     ps.set_color(boundary); 
     ps << (*pt);
     break;
   }
  case 2:
   {
     segment* pt= (segment*)object_ptr;
     ps.set_fill_color(interior);
     ps.set_color(boundary); 
     ps << (*pt);
     break;
   }
  case 3:
   {
     ray* pt= (ray*)object_ptr;
     ps.set_fill_color(interior);
     ps.set_color(boundary);  
     ps << (*pt); 
     break;
   }
  case 4:
   {
     line* pt= (line*)object_ptr;
     ps.set_fill_color(interior);
     ps.set_color(boundary);   
     ps << (*pt); 
     break;
   }
  case 5:
   { 
     circle* pt= (circle*)object_ptr;
     ps.set_fill_color(interior);
     ps.set_color(boundary);    
     ps << (*pt); 
     break;
   }
  case 6:
   {
     gen_polygon* pt= (gen_polygon*)object_ptr;
     ps.set_fill_color(interior);
     ps.set_color(boundary);    
     ps << (*pt); 
     break;
   }
  case 7:
   { 
     GeoRemark* pt= (GeoRemark*)object_ptr;
     ps.set_fill_color(interior);
     ps.set_color(boundary);    
     ps << (*pt);
     break;
   }
  }

}

void GeoWin_GeoObj::init()
{
 interior=ivory;
 boundary=black;
 l_style=solid;
 l_width=1;
}

color GeoWin_GeoObj::get_color() const
{
  return boundary;
}

color GeoWin_GeoObj::set_color(color c) 
{
  color old = boundary;
  boundary = c;
  return old;
}

color GeoWin_GeoObj::get_fill_color() const
{
  return interior;
}

color GeoWin_GeoObj::set_fill_color(color c)
{
  color old = interior;
  interior = c;
  return old;
}

line_style GeoWin_GeoObj::get_line_style() const
{
  return l_style;
}

line_style GeoWin_GeoObj::set_line_style(line_style l) 
{
  line_style old = l_style;
  l_style = l;
  return old;
}

int GeoWin_GeoObj::get_line_width() const
{
  return l_width;
}

int GeoWin_GeoObj::set_line_width(int l)
{
  int old = l_width;
  l_width = l;
  return old;
}

GEOWIN_END_NAMESPACE




