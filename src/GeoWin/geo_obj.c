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
// file          : src/GeoWin/geo_obj.c
// package       : GeoWin (1.1.9)
// revision      : 1.1.9
// revision_date : 27 September 2000 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken@informatik.uni-trier.de>)
// ============================================================================


#include <LEDA/geowin.h>

GEOWIN_BEGIN_NAMESPACE

// ******************* GeoWin GeoObjects *************************


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
  switch(mode) {
  case 7:
   { 
     GeoRemark* pt= (GeoRemark*)object_ptr;
     delete pt;
     break;
   }
  }
}

int GeoWin_GeoObj::get_mode() const
{ return mode; }

void* GeoWin_GeoObj::get_ptr()
{ return object_ptr; }

void GeoWin_GeoObj::draw(window& W) const
{
 // set the parameter of the object ...
 color fc = W.set_fill_color(interior);
 color bd = W.set_color(boundary);
 line_style ls = W.set_line_style(l_style);
 int lw = W.set_line_width(l_width);
 
 switch(mode) {
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




