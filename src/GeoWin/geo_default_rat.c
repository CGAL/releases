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
// file          : src/GeoWin/geo_default_rat.c
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

void init_leda_rat_default_types()
{
#if defined INIT_GEOWIN_LEDA_DEFAULT_TYPES

  geowin_init_default_type((list<rat_point>*)0,   string("RationalPoints"));
  geowin_init_default_type((list<rat_segment>*)0, string("RationalSegments"));
  
  geowin_init_default_type((list<rat_ray>*)0,     string("RationalRays"));
  geowin_init_default_type((list<rat_line>*)0,    string("RationalLines"));
  geowin_init_default_type((list<rat_circle>*)0,  string("RationalCircles"));

  geowin_init_default_type((list<rat_polygon>*)0, string("RationalSimplePolygons"));
  
  geowin_init_default_type((list<rat_gen_polygon>*)0, string("RationalGeneralizedPolygons"));

#if defined LEDA_RECTANGLES
  geowin_init_default_type((list<rat_rectangle>*)0,   string("RationalRectangles"));
#endif

  geowin_init_default_type((list<d3_rat_point>*)0,    string("D3-RationalPoints"));

#endif
}

GEOWIN_END_NAMESPACE


