/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: dcel_vertex.h
// Author: Wolfgang Freiseisen
 


#ifndef CGAL__DCEL_VERTEX_H
#define CGAL__DCEL_VERTEX_H

#include <list.h>
#include <vector.h>

#include <CGAL/bops_dcel_defs.h>


/*
  VERTEX in the DCEL:
  -------------------
  vertex_type:      point, header, color;
  vertex:           typedef const CGAL__Dcel_vertex_type* CGAL__Dcel_vertex;
  container:        vector<CGAL__Dcel_vertex_type>
  vertex_iterator:  typedef vector<CGAL__Dcel_vertex_type>::const_iterator vertex_iterator;
  conversion:       vertex and vertex_iterator are type-identical

  *---------------------------------------------------------------------*
  *A CGAL_Point< R > is stored as a CGAL_Object to avoid templatizing of*
  *class CGAL__Dcel_vertex_type!                                        *
  *---------------------------------------------------------------------*

  CGAL-point:       CGAL_Point< R > pt;
                    if( CGAL_assign( pt, vertex->point()) )
                      this is a CGAL-point;
                    else
                      this is not a CGAL-point;

                    ...

  CGAL-object:      CGAL_Object obj= CGAL_make_object(pt);
  
*/


class CGAL__Dcel_vertex_type {
public:
  CGAL__Dcel_vertex_type()
        : _header(NULL), _color(CGAL__NO_COLOR ), _degree(0) {}

#ifdef CGAL_POINT_DEFINED
  CGAL__Dcel_vertex_type( const CGAL_Object& pt, int no,
                          CGAL__Dcel_Color col = CGAL__NO_COLOR)
        : _index(no), _point(pt), _header(NULL), _color(col), _degree(0) {}
  CGAL__Dcel_vertex_type( const CGAL_Object& pt,
                          CGAL__Dcel_Color col = CGAL__NO_COLOR)
        : _index(-1), _point(pt), _header(NULL), _color(col), _degree(0) {}

  CGAL_Object point() const {return _point; }

#else

  CGAL__Dcel_vertex_type( const CGAL__Point_2& pt, int no,
                          CGAL__Dcel_Color col = CGAL__NO_COLOR)
        : _index(no), _point(pt), _header(NULL), _color(col), _degree(0) {}
  CGAL__Dcel_vertex_type( const CGAL__Point_2& pt,
                          CGAL__Dcel_Color col = CGAL__NO_COLOR)
        : _index(-1), _point(pt), _header(NULL), _color(col), _degree(0) {}

  CGAL__Point_2 point() const {return _point; }

#endif /* CGAL_POINT_DEFINED */

  int  degree() const { return _degree; }
  CGAL__Dcel_edge  header() const { return _header; }
  CGAL__Dcel_Color color() const { return _color; }
  int              index() const { return _index;}
  CGAL__Dcel_Color set_color(CGAL__Dcel_Color c) { _color= c; return c;}
  CGAL__Dcel_Color& color() { return _color; }

protected:
  CGAL__Dcel_edge&  header() { return _header; }
  void header(CGAL__Dcel_edge h)       { _header= h; }

  friend class CGAL__Dcel_base;

private:

  int              _index;
#ifdef CGAL_POINT_DEFINED
  /* CGAL_Object avoids templatizing */
  CGAL_Object _point;
  CGAL_Object& point() { return _point; }
#else
  CGAL__Point_2 _point;
  CGAL__Point_2& point() {return _point; }
#endif /* CGAL_POINT_DEFINED */

  CGAL__Dcel_edge _header;
  CGAL__Dcel_Color _color;
  int              _degree; /* the degree of this node */
};


#endif /* CGAL__DCEL_VERTEX_H */

