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


// Source: dcel_out.h
// Author: Wolfgang Freiseisen
 


#ifndef DCEL_OUT_H
#define DCEL_OUT_H

#ifdef __GNUC__
#include <typeinfo>
#endif

#include <iostream.h>


#ifdef CGAL__DCEL_DEFS_H
ostream& operator<<(ostream& o, const CGAL__Dcel_Color& c) {
  o << int(c);
  return o;
}
#endif

#ifdef CGAL__DCEL_VERTEX_H
ostream& operator<<(ostream& o, const CGAL__Dcel_vertex_type* e) {
  if( e != NULL )
    o << 'v' << (*e).index();
  else
    o << "nil";
  return o;
}
#endif

#ifdef CGAL__DCEL_FACE_H
ostream& operator<<(ostream& o, const CGAL__Dcel_face_type* e) {
  if( e != NULL )
    o << 'f' << (*e).index();
  else
    o << "nil";
  return o;
}
#endif

#ifdef CGAL__DCEL_EDGE_H
ostream& operator<<(ostream& o, const CGAL__Dcel_edge_type* e) {
  if( e != NULL )
    o << '[' << (*e).index() << ']';
  else
    o << "nil";
  return o;
}
#endif


#ifdef CGAL__DCEL_VERTEX_H
ostream& operator<<(ostream& o, const CGAL__Dcel_vertex_type& vertex) {
  o << '(' << vertex.index()
    << ", d" << vertex.degree()
    << ", c" << vertex.color()
    << ", HV=" << vertex.header()
    << ", ";
#ifdef CGAL_POINT_DEFINED
  /* only for TESTING !!!
  CGAL_Point_2< CGAL_Cartesian<int> > pt;
  CGAL_assign( pt, vertex.point() );
  o << "pt(" << pt.x() << ',' << pt.y() << ')';
  */
#else
  o << "pt("
    << vertex.point().first  << ','
    << vertex.point().second << ')';
#endif
  o << ')';
  return o;
}
#endif

#ifdef CGAL__DCEL_FACE_H
ostream& operator<<(ostream& o, const CGAL__Dcel_face_type& face) {
  o << '(' << face.index()
    << ", c" << face.color()
    << ", HF=" << face.header() << ')';
  return o;
}
#endif

#ifdef CGAL__DCEL_EDGE_H
ostream& operator<<(ostream& o, const CGAL__Dcel_edge_type& edge) {
#ifdef CGAL__DCEL_DEBUG_ON
  o << "{ c=" << edge.color() << ", ";
  if( edge.V1() == NULL )
    o << "nil";
  else
    o << (CGAL__Dcel_vertex_type)*(edge.V1());

  o << ", ";
  if( edge.V2() == NULL )
    o << "nil";
  else
    o << (CGAL__Dcel_vertex_type)*(edge.V2());

  o << ", ";
  if( edge.F1() == NULL )
    o << "nil";
  else
    o << (CGAL__Dcel_face_type)*(edge.F1());
  o << ", ";
  if( edge.F2() == NULL )
    o << "nil";
  else
    o << (CGAL__Dcel_face_type)*(edge.F2());

  o << ", " << edge.P1() << ", " << edge.P2();

  o << '}';
#else
  o << "{ " << edge.index() << ": c" << edge.color() << ", "
    << edge.V1() << ", " << edge.V2() << ", "
    << edge.F1() << ", " << edge.F2() << ", "
    << edge.P1() << ", " << edge.P2() << '}';
#endif
  return o;
}
#endif
/*
#ifdef CGAL__DCEL_BASE_H
ostream& operator<<(ostream& o, const CGAL__Dcel_base& dcel) {
  CGAL__Dcel_base::edge_iterator e;
  for( e= dcel.begin(); e != dcel.end(); e++ ) {
    cout << *e << endl;
  }
  return o;
}
#endif
*/

template<class T1, class T2>
ostream& operator<<(ostream& o, pair<T1,T2> p){
  o << p.first << ' ' << p.second;
  return o;
}


template<class Iterator>
ostream& print( ostream& o, char* text, Iterator begin, Iterator end) {
  Iterator it;
  int i= 0;
  for( it= begin; it != end; it++ )
    o << text << '[' << i++ << "]= " << *it << endl;
  return o;
}

#endif DCEL_OUT_H
