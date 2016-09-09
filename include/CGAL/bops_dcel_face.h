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


// Source: dcel_face.h
// Author: Wolfgang Freiseisen
 

#ifndef CGAL__DCEL_FACE_H
#define CGAL__DCEL_FACE_H

#include <CGAL/bops_dcel_defs.h>

/*
  FACE in the DCEL:
  -----------------
  face_type:        header (HF), color
  face:             typedef const CGAL__Dcel_face_type*   CGAL__Dcel_face;
  container:        vector<CGAL__Dcel_face_type>
  face_iterator:    typedef vector<CGAL__Dcel_face_type>::const_iterator
  conversion:       face and face_iterator are type-identical
*/


class CGAL__Dcel_face_type {
public:
  CGAL__Dcel_face_type( int ind, CGAL__Dcel_Color col = CGAL__NO_COLOR )
        : _index(ind), _header(NULL), _color(col) {}
  CGAL__Dcel_face_type( CGAL__Dcel_Color col = CGAL__NO_COLOR )
        : _index(-1), _header(NULL), _color(col) {}

  CGAL__Dcel_edge  header() const { return _header; }
  CGAL__Dcel_Color color() const  { return _color; }
  CGAL__Dcel_Color set_color(CGAL__Dcel_Color c) { _color= c; return c;}
  int              index() const  { return _index; }
  CGAL__Dcel_Color& color()   { return _color; }

protected:
  CGAL__Dcel_edge&  header()  { return _header; }

private:
  int _index;
  CGAL__Dcel_edge _header;
  CGAL__Dcel_Color _color;
  friend class CGAL__Dcel_base;
};


#endif /* CGAL__DCEL_FACE_H */
