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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/bops_dcel_base.h
// package       : bops (1.0.5)
// source        : include/CGAL/bops_dcel_base.h
// revision      : $Revision: 1.0.5 $
// revision_date : $Date: Tue Jun 30 19:04:29 MET DST 1998  $
// author(s)     :        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__DCEL_BASE_H
#define CGAL__DCEL_BASE_H


#include <CGAL/bops_dcel_defs.h>
#include <CGAL/bops_dcel_vertex.h>
#include <CGAL/bops_dcel_face.h>
#include <CGAL/bops_dcel_edge.h>


#include <CGAL/bops_V2E_rep.h>

/*
  Implementation of the Double Connected Edge List (DCEL)
  -------------------------------------------------------

  template <class R> class DCEL__Dcel_base;
*/

template <class I>
class CGAL__Dcel_base : public I {
private:
	CGAL__Dcel_edge_type<I>   eeeeeee;
	CGAL__Dcel_vertex_type<I> vvvvvvv;
public:
  typedef typename I::Point Point;
  typedef typename I::const_vertices_iterator const_vertices_iterator;
  typedef typename I::edge_iterator  edge_iterator;
  typedef typename I::face_iterator  face_iterator;
  typedef typename I::const_points_iterator const_points_iterator;

  typedef CGAL__V2E_rep_base_type<const_vertices_iterator,edge_iterator>
          V2E_rep_base_dcel;

  CGAL__Dcel_base() {}
  CGAL__Dcel_base(const CGAL__Dcel_base<I>& dl) {*this= dl;}

  ~CGAL__Dcel_base() {}


  CGAL__Dcel_base<I>& operator=(const CGAL__Dcel_base<I>& dl) {
    // this will not work, since the iterators have to be updated
    _v_list= dl._v_list;
    _f_list= dl._f_list;
    _e_list= dl._e_list;
  /*
    edge_iterator e, e1;
    for(e= _e_list.begin(); e != _e_list.end(); e++) {
      (*e).V1()= _v_list[*(e1).V1().index()];
    }
      
  */
    return *this;
  }

  int number_of_vertices() const { return _v_list.size(); }
  int number_of_edges() const { return _e_list.size(); }
  int number_of_faces() const { return _f_list.size(); }


#ifdef CGAL_CFG_RETURN_TYPE_BUG_2
  void construct_vertex_cycles( V2E_rep_base_dcel& v2e_rep) {
    /* construction of vertex cycles */
    /* preconditions:
                vertex list _v_list is initialized: 
                edge   list _e_list is initialized: V1, V2
                vertex-to-edge representation is initialized and sorted
    */
    _v2e= &v2e_rep;
    construct_vertex_cycles();
  }
#else
  void construct_vertex_cycles( V2E_rep_base_dcel& v2e_rep);
#endif // CGAL_CFG_RETURN_TYPE_BUG_2

  void construct_face_cycles( void );
    /* construction of face cycles */
    /* preconditions:
          face list _f_list is not initialized, it will be cleared and filled
          edge list _e_list is initialized: V1, V2, P1, P2
    */

  //const_edges_iterator operator[](int i) const { return _e_list[i]; }
  //edges_iterator       operator[](int i) { return _e_list[i]; }

  edge_iterator begin() const { return _e_list.begin(); }
  edge_iterator end()   const { return _e_list.end(); }

  const_vertices_iterator vertex_begin() const { return _v_list.begin(); }
  const_vertices_iterator vertex_end()   const { return _v_list.end(); }

  face_iterator face_begin() const { return _f_list.begin(); }
  face_iterator face_end()   const { return _f_list.end(); }

  bool face_inside_in_face(face_iterator f1, face_iterator f2) const {
    /* returns true iff face f1 is inside of face f2.
       But only ONE depth is recognized, i.e. 
       if f1 is inside of f3 and f3 is inside f2 then false is returned.
    */ 
    edge_iterator e0, e;
    e0= e= begin(f1);
    do  {
      if( (*e).opposite_face(f1) != f2 ) return false;
    }
    while( (e= next(e, f1)) != e0 );
    return true;
  }
  

  edge_iterator insert( const CGAL__Dcel_edge_type<I>& et ) {
    _e_list.push_back( CGAL__Dcel_edge_type<I>(et, (int)_e_list.size()) );
    edge_iterator i= _e_list.end();
    advance(i, -1);
    return i;
  }

  const_vertices_iterator insert( const CGAL__Dcel_vertex_type<I>& vt ) {
    _v_list.push_back( vt );
    const_vertices_iterator i= _v_list.end();
    advance(i, -1);
    return i;
  }

  const_points_iterator insert( const Point& pt ) {
# ifdef CGAL__BOPS_DEBUG_ON
    pair<const_points_iterator,bool> ret_val;
    ret_val= _point_list.insert(pt);
    cout << "insert point" << pt << "= ("
         << *ret_val.first << ',' << ret_val.second << ')' << endl;
    return ret_val.first;
#  else
    return _point_list.insert(pt).first;
#  endif
  }

  face_iterator insert( const CGAL__Dcel_face_type<I>& ft ) {
    _f_list.push_back( ft );
    face_iterator i= _f_list.end();
    advance(i, -1);
    return i;
  }


  edge_iterator begin(  const_vertices_iterator v ) const {
    return v->header();
  }

  edge_iterator next( edge_iterator e, const_vertices_iterator v ) const {
    return (e->V1() == v) ? e->P1() : e->P2();
  }

  edge_iterator begin(  face_iterator f ) const { return f->header(); }
  edge_iterator next( edge_iterator e, face_iterator f ) const {
    return (e->F1() == f) ? e->P1() : e->P2();
  }

  list<edge_iterator> get_all_edges( const_vertices_iterator v ) const {
    /* traces the edges counterclockwise about vertex v */
    list<edge_iterator> A;
    edge_iterator a, e= begin(v);
    A.push_back(e);
    for( a= next(e,v); a != e; a= next(a,v) ) A.push_back(a);
    return A;
  }

  list<edge_iterator> get_all_edges( face_iterator f ) const {
    /* traces the edges clockwise about face f */
    list<edge_iterator> A;
    edge_iterator a, e= begin(f);
    A.push_back(e);
    for( a= next(e,f); a != e; a= next(a,f) ) A.push_back(a);
    return A;
  }

protected:
  typename I::Vertices_container _v_list;
  typename I::Faces_container    _f_list;
  typename I::Edges_container    _e_list;
  typename I::Points_container   _point_list;

/*
  list<edge>              _e_list;
  vector<edge_iterator>   _i_e_list;
  list<vertex>            _v_list;
  vector<vertex_iterator> _i_v_list;
  list<face>              _f_list;
  set<points>             _point_list;

  map<point_iterator,vertex_iterator> _point_vertex_map;


  new functions:
     vertex_iterator insert_new_vertex(point);
     edge_iterator   insert_new_edge(vertex, vertex);
     edge_iterator   break_edge(edge, vertex); 
     edge_iterator   break_edge(edge, point); 
     edge_iterator   delete_edge(edge); 
     edge_iterator   delete_vertex(vertex); 
*/

#ifdef CGAL_CFG_RETURN_TYPE_BUG_2
  void construct_vertex_cycles();
  V2E_rep_base_dcel *_v2e;
#endif // CGAL_CFG_RETURN_TYPE_BUG_2
};

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/bops_dcel_base.C>
#endif 

#endif /* CGAL__DCEL_BASE_H */

