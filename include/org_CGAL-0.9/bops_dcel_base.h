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


// Source: dcel_base.h
// Author: Wolfgang Freiseisen
 

#ifndef CGAL__DCEL_BASE_H
#define CGAL__DCEL_BASE_H

#include <list.h>
#include <vector.h>
#include <pair.h>

#include <CGAL/bops_dcel_defs.h>
#include <CGAL/bops_dcel_util.h>
#include <CGAL/bops_dcel_vertex.h>
#include <CGAL/bops_dcel_face.h>
#include <CGAL/bops_dcel_edge.h>


#include <CGAL/bops_V2E_rep.h>

/*
  Implementation of the Double Connected Edge List (DCEL)
  -------------------------------------------------------

  template <class R> class DCEL__Dcel;
*/

class CGAL__Dcel_base
{
public:

  typedef vector<CGAL__Dcel_edge_type>  ::const_iterator edge_iterator;
  typedef vector<CGAL__Dcel_face_type>  ::const_iterator face_iterator;
  typedef vector<CGAL__Dcel_vertex_type>::const_iterator vertex_iterator;

  typedef vector<CGAL__Dcel_face_type>  ::iterator nc_face_iterator;
  typedef vector<CGAL__Dcel_vertex_type>::iterator nc_vertex_iterator;
  typedef vector<CGAL__Dcel_edge_type>  ::iterator nc_edge_iterator;

  CGAL__Dcel_base() {}
  CGAL__Dcel_base(const CGAL__Dcel_base& dl) { *this= dl; }

  ~CGAL__Dcel_base() {}


  CGAL__Dcel_base& operator=(const CGAL__Dcel_base& dl) {
    // this will not work, since the iterators have to be updated
    _v_list= dl._v_list;
    _f_list= dl._f_list;
    _e_list= dl._e_list;
  /*
    edge_iterator e, e1;
    for(e= _e_list.begin(); e != _e_list.end(); e++) {
      (*e).V1()= _v_list[*(e1).V1().index()];
      
  */
    return *this;
  }

  int number_of_vertices() const { return _v_list.size(); }
  int number_of_edges() const { return _e_list.size(); }
  int number_of_faces() const { return _f_list.size(); }

  typedef CGAL__V2E_rep_base_type<vertex_iterator,edge_iterator>
        V2E_rep_base_dcel;

  void construct_vertex_cycles( V2E_rep_base_dcel& v2e);
    /* construction of vertex cycles */
    /* preconditions:
                vertex list _v_list is initialized: 
                edge   list _e_list is initialized: V1, V2
                vertex-to-edge representation is initialized and sorted
    */

  void construct_face_cycles( void );
    /* construction of face cycles */
    /* preconditions:
          face list _f_list is not initialized, it will be cleared and filled
          edge list _e_list is initialized: V1, V2, P1, P2
    */

  //edge_iterator operator[](int i) const { return _e_list[i]; }
  //nc_edge_iterator operator[](int i) { return _e_list[i]; }

  edge_iterator begin() const { return _e_list.begin(); }
  edge_iterator end()   const { return _e_list.end(); }

  vertex_iterator vertex_begin() const { return _v_list.begin(); }
  vertex_iterator vertex_end()   const { return _v_list.end(); }

  face_iterator face_begin() const { return _f_list.begin(); }
  face_iterator face_end()   const { return _f_list.end(); }

  edge_iterator insert( const CGAL__Dcel_edge_type& et ) {
    _e_list.push_back( CGAL__Dcel_edge_type(et, (int)_e_list.size()) );
    edge_iterator i= _e_list.end();
    advance(i, -1);
    // (*i)._index= _e_list.size()-1;
    return i;
  }

  vertex_iterator insert( const CGAL__Dcel_vertex_type& vt ) {
    _v_list.push_back( vt );
    vertex_iterator i= _v_list.end();
    advance(i, -1);
    return i;
  }

  face_iterator insert( const CGAL__Dcel_face_type& ft ) {
    _f_list.push_back( ft );
    face_iterator i= _f_list.end();
    advance(i, -1);
    return i;
  }


  edge_iterator begin(  vertex_iterator v ) const { return v->header(); }
  edge_iterator next( edge_iterator e, vertex_iterator v ) const {
    return (e->V1() == v) ? e->P1() : e->P2();
  }

  edge_iterator begin(  face_iterator f ) const { return f->header(); }
  edge_iterator next( edge_iterator e, face_iterator f ) const {
    return (e->F1() == f) ? e->P1() : e->P2();
  }

  list<edge_iterator> get_all_edges( vertex_iterator v ) const;
    /* traces the edges counterclockwise about vertex v */
  list<edge_iterator> get_all_edges( face_iterator f ) const;
    /* traces the edges clockwise about face f */


protected:
  vector<CGAL__Dcel_vertex_type> _v_list;
  vector<CGAL__Dcel_face_type>   _f_list;
  vector<CGAL__Dcel_edge_type>   _e_list;
};

list<CGAL__Dcel_base::edge_iterator> CGAL__Dcel_base::
get_all_edges ( vertex_iterator v ) const {
    /* traces the edges counterclockwise about vertex v */
    list<edge_iterator> A;
    edge_iterator a, e= begin(v);
    A.push_back(e);
    for( a= next(e,v); a != e; a= next(a,v) ) A.push_back(a);
    return A;
}

list<CGAL__Dcel_base::edge_iterator> CGAL__Dcel_base::
get_all_edges( face_iterator f ) const {
    /* traces the edges clockwise about face f */
    list<edge_iterator> A;
    edge_iterator a, e= begin(f);
    A.push_back(e);
    for( a= next(e,f); a != e; a= next(a,f) ) A.push_back(a);
    return A;
}

#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/bops_dcel_base.C>
#endif 

#endif /* CGAL__DCEL_BASE_H */

