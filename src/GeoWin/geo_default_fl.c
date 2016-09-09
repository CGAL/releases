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
// file          : src/GeoWin/geo_default_fl.c
// package       : GeoWin (1.0.8)
// revision      : 1.0.8
// revision_date : 17 December 1999 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken@informatik.uni-halle.de>)
// ============================================================================


#include <LEDA/geowin.h>
#include <LEDA/geowin_init.h>

GEOWIN_BEGIN_NAMESPACE

void init_leda_float_default_types()
{
#if defined INIT_GEOWIN_LEDA_DEFAULT_TYPES

  geowin_init_default_type((list<point>*)0,       string("Points"));
  geowin_init_default_type((list<segment>*)0,     string("Segments"));

  geowin_init_default_type((list<ray>*)0,         string("Rays"));
  geowin_init_default_type((list<line>*)0,        string("Lines"));
  geowin_init_default_type((list<circle>*)0,      string("Circles"));

  geowin_init_default_type((list<polygon>*)0,     string("SimplePolygons"));
  
  geowin_init_default_type((list<gen_polygon>*)0, string("GeneralizedPolygons"));

#if defined LEDA_RECTANGLES
  geowin_init_default_type((list<rectangle>*)0,   string("Rectangles"));
#endif

  geowin_init_default_type((list<d3_point>*)0,    string("D3-Points"));

#endif
}

GEOWIN_END_NAMESPACE

