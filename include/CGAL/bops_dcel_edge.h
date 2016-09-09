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


// Source: dcel_edge.h
// Author: Wolfgang Freiseisen
 


#ifndef CGAL__DCEL_EDGE_H
#define CGAL__DCEL_EDGE_H

#include <CGAL/bops_dcel_defs.h>

/*
  EDGE in the DCEL:
  -----------------
  edge_type:        V1, V2, F1, F2, P1, P2, color
  edge:             typedef const CGAL__Dcel_edge_type*   CGAL__Dcel_edge;
  container:        vector<CGAL__Dcel_edge_type>
  edge_iterator:    typedef vector<CGAL__Dcel_edge_type>::const_iterator
  conversion:       edge and edge_iterator are type-identical
*/

enum CGAL__Dcel_edge_id {
  FACE_1   = 1, FACE_2   = 2,
  VERTEX_1 = 1, VERTEX_2 = 2,
  EDGE_1   = 1, EDGE_2   = 2
};


class CGAL__Dcel_edge_type {
public:

  CGAL__Dcel_edge_type() :
            _V1(NULL), _V2(NULL),
            _F1(NULL), _F2(NULL),
            _P1(NULL), _P2(NULL),
            _color(CGAL__NO_COLOR), _index(-1)
  {
  } 

  CGAL__Dcel_edge_type(
    CGAL__Dcel_vertex v1,
    CGAL__Dcel_vertex v2,
    CGAL__Dcel_Color col = CGAL__NO_COLOR
  ) :
            _V1(v1), _V2(v2),
            _F1(NULL), _F2(NULL),
            _P1(NULL), _P2(NULL),
            _color(col), _index(-1)
  {
  } 

  CGAL__Dcel_edge_type( const CGAL__Dcel_edge_type& e ) { *this= e; }
  CGAL__Dcel_edge_type( const CGAL__Dcel_edge_type& e, int ind) {
    *this= e;
    _index= ind;
  }

  CGAL__Dcel_edge_type& operator=( const CGAL__Dcel_edge_type& e ) {
    _V1= e._V1; _V2= e._V2;
    _F1= e._F1; _F2= e._F2;
    _P1= e._P1; _P2= e._P2;
    _color= e._color;
    _index= e._index;
    return *this;
  }

  CGAL__Dcel_Color  color() const { return _color; }
  CGAL__Dcel_Color set_color(CGAL__Dcel_Color c) { _color= c; return c;}

  CGAL__Dcel_vertex  V1() const { return _V1; }
  CGAL__Dcel_vertex  V2() const { return _V2; }
  CGAL__Dcel_face    F1() const { return _F1; }
  CGAL__Dcel_face    F2() const { return _F2; }
  CGAL__Dcel_edge    P1() const { return _P1; }
  CGAL__Dcel_edge    P2() const { return _P2; }

  CGAL__Dcel_vertex  opposite_vertex(CGAL__Dcel_vertex v) const {
    return v==_V2 ? _V1 : _V2;
  }

  CGAL__Dcel_face    left_face(CGAL__Dcel_vertex v1) const {
    return v1==_V1 ? _F1 : _F2;
  }

  CGAL__Dcel_face&   left_face(CGAL__Dcel_vertex v1) {
    return v1==_V1 ? _F1 : _F2;
  }

  CGAL__Dcel_vertex  V(CGAL__Dcel_edge_id i) const {
    return i==VERTEX_1 ? _V1 : _V2;
  }
  CGAL__Dcel_face    F(CGAL__Dcel_edge_id i) const {
    return i==FACE_1 ? _F1 : _F2;
  }
  CGAL__Dcel_edge    P(CGAL__Dcel_edge_id i) const {
    return i==EDGE_1 ? _P1 : _P2;
  }
  int index() const { return _index; }

/* protected: */
  CGAL__Dcel_Color& color() { return _color; }

  CGAL__Dcel_vertex& V1()       { return _V1; }
  CGAL__Dcel_vertex& V2()       { return _V2; }
  CGAL__Dcel_face&   F1()       { return _F1; }
  CGAL__Dcel_face&   F2()       { return _F2; }
  CGAL__Dcel_edge&   P1()       { return _P1; }
  CGAL__Dcel_edge&   P2()       { return _P2; }

  CGAL__Dcel_vertex& V(CGAL__Dcel_edge_id i) {
    return i==VERTEX_1 ? _V1 : _V2;
  }
  CGAL__Dcel_face&   F(CGAL__Dcel_edge_id i) {
    return i==FACE_1 ? _F1 : _F2;
  }
  CGAL__Dcel_edge&   P(CGAL__Dcel_edge_id i) {
    return i==EDGE_1 ? _P1 : _P2;
  }

  friend class CGAL__Dcel_base;
private:
    /* first and second point of this edge */
    /* defines a direction implicitely */
  CGAL__Dcel_vertex _V1, _V2;
    /* left and right face of this edge */
  CGAL__Dcel_face _F1, _F2;
    /* P1 or P2 points to edges CCW from V1 or V2, respectively */
  CGAL__Dcel_edge _P1, _P2;

    /* P3 or P4 points to edges CLW from V1 or V2, respectively */
  /* CGAL__Dcel_edge _P3, _P4; */

  CGAL__Dcel_Color _color;
  int _index;
};

#endif /* CGAL__DCEL_EDGE_H */

