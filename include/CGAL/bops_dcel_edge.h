//  -*- Mode: c++ -*-
// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/bops_dcel_edge.h
// package       : bops (1.1.2)
// source        : include/CGAL/bops_dcel_edge.h
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:28:51 MET 1998  $
// author(s)     :             Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__DCEL_EDGE_H
#define CGAL__DCEL_EDGE_H

#include <CGAL/bops_dcel_element.h>

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


template <class I>
class CGAL__Dcel_edge_type : public CGAL__Dcel_element_type {
public:
#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_4
  typedef const CGAL__Dcel_vertex_type<I>* vertex;
  typedef const CGAL__Dcel_edge_type<I>*   edge;
  typedef const CGAL__Dcel_face_type<I>*   face;
#else 
  typedef typename I::const_vertices_iterator vertex;
  typedef typename I::const_edges_iterator    edge;
  typedef typename I::const_faces_iterator    face;
#endif

  CGAL__Dcel_edge_type() : CGAL__Dcel_element_type(), _V1(NULL), _V2(NULL),
            _F1(NULL), _F2(NULL), _P1(NULL), _P2(NULL)
  {
  } 

  CGAL__Dcel_edge_type( vertex v1, vertex v2,
    CGAL__Dcel_Color col = CGAL__NO_COLOR
  ) 
    : CGAL__Dcel_element_type(col), _V1(v1), _V2(v2),
      _F1(NULL), _F2(NULL), _P1(NULL), _P2(NULL)
  {
  } 

  //CGAL__Dcel_edge_type( const CGAL__Dcel_edge_type<I>& e ) { *this= e; }

  CGAL__Dcel_edge_type( const CGAL__Dcel_edge_type<I>& e, int ind) 
    : CGAL__Dcel_element_type(ind, e.color()) {
    assign(e);
  }

  vertex  V1() const { return _V1; }
  vertex  V2() const { return _V2; }
  face    F1() const { return _F1; }
  face    F2() const { return _F2; }
  edge    P1() const { return _P1; }
  edge    P2() const { return _P2; }

  vertex  opposite_vertex(vertex v) const {
    return v==_V2 ? _V1 : _V2;
  }

  face  opposite_face(face f) const {
    return f==_F2 ? _F1 : _F2;
  }

  face&  opposite_face(face f) {
    return f==_F2 ? _F1 : _F2;
  }

  face    left_face(vertex v1) const {
    return v1==_V1 ? _F1 : _F2;
  }

  face&   left_face(vertex v1) {
    return v1==_V1 ? _F1 : _F2;
  }

  vertex  V(CGAL__Dcel_edge_id i) const {
    return i==VERTEX_1 ? _V1 : _V2;
  }
  face    F(CGAL__Dcel_edge_id i) const {
    return i==FACE_1 ? _F1 : _F2;
  }
  edge    P(CGAL__Dcel_edge_id i) const {
    return i==EDGE_1 ? _P1 : _P2;
  }

/* protected: */

  vertex& V1()       { return _V1; }
  vertex& V2()       { return _V2; }
  face&   F1()       { return _F1; }
  face&   F2()       { return _F2; }
  edge&   P1()       { return _P1; }
  edge&   P2()       { return _P2; }

  vertex& V(CGAL__Dcel_edge_id i) {
    return i==VERTEX_1 ? _V1 : _V2;
  }
  face&   F(CGAL__Dcel_edge_id i) {
    return i==FACE_1 ? _F1 : _F2;
  }
  edge&   P(CGAL__Dcel_edge_id i) {
    return i==EDGE_1 ? _P1 : _P2;
  }

  void assign(const CGAL__Dcel_edge_type<I>& e) {
    _V1= e._V1; _V2= e._V2;
    _F1= e._F1; _F2= e._F2;
    _P1= e._P1; _P2= e._P2;
  }
  friend class CGAL__Dcel_base<I>;
private:
    /* first and second point of this edge */
    /* defines a direction implicitely */
  vertex _V1, _V2;
    /* left and right face of this edge */
  face _F1, _F2;
    /* P1 or P2 points to edges CCW from V1 or V2, respectively */
  edge _P1, _P2;

    /* P3 or P4 points to edges CLW from V1 or V2, respectively */
  /* edge _P3, _P4; */
};

#endif /* CGAL__DCEL_EDGE_H */

