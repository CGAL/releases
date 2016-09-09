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
// file          : include/CGAL/bops_dcel.C
// package       : bops (1.0.5)
// source        : include/CGAL/bops_dcel.C
// revision      : $Revision: 1.0.5 $
// revision_date : $Date: Tue Jun 30 19:04:27 MET DST 1998  $
// author(s)     :        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__DCEL_C
#define CGAL__DCEL_C

#ifndef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/bops_dcel.h>
#endif

#include <CGAL/bops_V2E_rep.h>
#include <CGAL/bops_dcel_out.h>
#include <CGAL/bops_V2E_rep_out.h>

//#define CGAL__DCEL_DEBUG_ON


template<class I>
struct CGAL__Dcel_V2E_compare : public I {
   typedef const CGAL__Dcel_vertex_type<I>* vertex;
   typedef typename I::Point Point;
   typedef typename I::Direction Direction;
   Point p0;

   CGAL__Dcel_V2E_compare(vertex v0) : p0((*v0).point()) { }
   bool operator()(vertex v1, vertex v2 ) const { return compare(v1,v2); }
   bool compare(vertex v1, vertex v2 ) const {
     Point p1= (*v1).point(), p2= (*v2).point();
     Direction d1= I::direction_of(p0,p1);
     Direction d2= I::direction_of(p0,p2);
     return d1 < d2; 
   }
};




/*
  Implementation of the Double Connected Edge List (DCEL)
  -------------------------------------------------------

  template <class I> class DCEL__Dcel;
*/


#ifdef  CGAL_CFG_RETURN_TYPE_BUG_2 
template <class I> void CGAL__Dcel<I> :: insert_edges() {
  const list<epair>& edges= *__edges;
#else 
template <class I>
void CGAL__Dcel<I> :: insert_edges( const list<epair>& edges) {
#endif // CGAL_CFG_RETURN_TYPE_BUG_2

  typedef CGAL__V2E_rep_type<const_vertices_iterator,edge_iterator,
          CGAL__Dcel_V2E_compare<I> > V2E_rep_dcel;
  typedef CGAL__V2E_rep_base_type<const_vertices_iterator,edge_iterator>
          V2E_rep_base;


    /* insert edges */
    _e_list.reserve(edges.size());
    list< pair<int,int> >::const_iterator ee;
    for( ee= edges.begin(); ee != edges.end(); ee++ )
      CGAL__Dcel_base<I>::insert(
	CGAL__Dcel_edge_type<I>(c_it[(*ee).first], c_it[(*ee).second])
      );
    
    CGAL__BOPS_DCEL_DEBUG_LN("VERTICES inserted: ");
    CGAL__BOPS_DCEL_DEBUG_ITERATOR("dcel", this->begin(), this->end() );
    CGAL__BOPS_DCEL_DEBUG_ITERATOR("PT",
	  _point_list.begin(), _point_list.end() );

    /* template< class T_vertex, class T_edge, class T_compare > */
    V2E_rep_dcel v2e_rep( c_it.size(), edges.size() );

    /* insertion in vertex-to-edge rep. */
    /* const_vertices_iterator v0= _v_list.begin(); */
    const_vertices_iterator v1, v2;
    int iv1, iv2;
    for( edge_iterator e= _e_list.begin(); e != _e_list.end(); e++ ) {
      v1= (*e).V1();
      v2= (*e).V2();
      iv1= (*v1).index();
      iv2= (*v2).index();
      CGAL__BOPS_DCEL_DEBUG_VAR("insert: ", e);
      CGAL__BOPS_DCEL_DEBUG_PAIR("", iv1, iv2 );
      CGAL__BOPS_DCEL_DEBUG_LN("");
      v2e_rep.insert( iv1, (*e).V1(), iv2, (*e).V2(), e);
    }

    CGAL__BOPS_DCEL_DEBUG((V2E_rep_base)v2e_rep);

    v2e_rep.sort_vertices_CCW();
    CGAL__BOPS_DCEL_DEBUG((V2E_rep_base)v2e_rep);

    /* construction of vertex cycles */
    construct_vertex_cycles( v2e_rep );
    CGAL__BOPS_DCEL_DEBUG_LN("POINTERS inserted: ");
    CGAL__BOPS_DCEL_DEBUG_ITERATOR("dcel", this->begin(), this->end() );
    CGAL__BOPS_DCEL_DEBUG_ITERATOR("V", vertex_begin(), vertex_end() );
  
    /* construction of face cycles */
    construct_face_cycles();
    CGAL__BOPS_DCEL_DEBUG_LN("FACES inserted: ");
    CGAL__BOPS_DCEL_DEBUG_ITERATOR("dcel", this->begin(), this->end() );
    CGAL__BOPS_DCEL_DEBUG_ITERATOR("F", face_begin(), face_end() );

    return;
  }


template <class I>
#ifdef CGAL_CFG_RETURN_TYPE_BUG_2
bool CGAL__Dcel<I>::colorize(const CGAL__Dcel_Color& col) {
  typedef typename I::Point Point;
  const list<Point>& pgon= *__point_list;
#else 
bool CGAL__Dcel<I>::colorize(
			     const list<typename I::Point>& pgon,
			     const CGAL__Dcel_Color& col)
{
  typedef typename I::Point Point;
  typedef typename I::vertices_iterator vertices_iterator;
  typedef typename I::edges_iterator  edges_iterator;
  typedef typename I::faces_iterator  faces_iterator;
  typedef typename I::edge_iterator   edge_iterator;

#endif // CGAL_CFG_RETURN_TYPE_BUG_2
  
/* This routine colorizes the interior of a simple polygon 'pgon'
   given by a list of its vertices in counterclockwise order(!).
                                      ^^^^^^^^^^^^^^^^^^^^^^^^^
   The color is given by the input variable 'col' and will be set using
   the or operation, i.e. vertex::set_color( vertex::color() | col );

   return: true  iff everything ok
           false if e.g. polygon not valid
*/


  if( pgon.size() < 3 ) return false;

  list<Point>::const_iterator it_p;

  /* get last point */
  list<Point>::const_reverse_iterator rit_p= pgon.rbegin();
  Point pt= (*rit_p);
  Point v1_pt;

  const_vertices_iterator v0, v1;
  v0= find( pt );       // find first vertex
  vertices_iterator v= (vertices_iterator)v0;
  (*v).set_color( (*v0).color() | col);
  edge_iterator a, e0;
  edges_iterator e;
  faces_iterator f;

  list<const_vertices_iterator> vlist_deg2;
  // all vertices with degree greater than 2
  
  for(it_p= pgon.begin(); it_p != pgon.end(); it_p++) { /* for all vertices */
    v0= v;
    if( (*v0).degree() > 2 ) 
      vlist_deg2.push_back(v0);

    /* find second vertex 'v1' and edge [v0,v1] */
    a= e0= begin(v0);
    v1= (*a).opposite_vertex(v0);
    //if( (*v1).point() != *it_p )
    if( !compare_points((*v1).point(), *it_p ) )
    {
      for( a= next(e0,v0); a != e0; a= next(a,v0) ) {
        v1= (*a).opposite_vertex(v0);
        //if( (*v1).point() == *it_p ) break; /* found !! */
        if( compare_points((*v1).point(), *it_p) ) break; /* found !! */
      }
      if( a==e0) return false; /* ABORT: --> polygon not valid */
    }

    e= (edges_iterator)a;
    (*e).set_color( (*e).color()|col);
    v= (vertices_iterator)v1;
    (*v).set_color( (*v).color()|col);
    face_iterator face0= (*e).left_face(v0); /* v0 -> v1 ** pgon is CCW */
    face_iterator face1= (*e).opposite_face(face0);
    f= (faces_iterator)face0;
    (*f).set_color( (*f).color()|col);
    if( face_inside_in_face(face1, face0) ) {
      f= (faces_iterator)face1;
      (*f).set_color( (*f).color()|col);
    }
  }

  
  list<const_vertices_iterator>::const_iterator vit;
  face_iterator f1, f2;
  for( vit= vlist_deg2.begin(); vit != vlist_deg2.end(); vit++) {
    v0= *vit;
    a= e0= begin(v0);
    do {
      if( !((*a).color() & col ) ) {
        f1= (*a).F1();
        f2= (*a).F2();
        if( (*f1).color()&col && (*f2).color()&col ) {
          e= (edges_iterator)a;
          (*e).set_color( (*a).color()|col );
          v1= (*a).opposite_vertex(v0);
          v= (vertices_iterator)v1;
          (*v).set_color( (*v).color()|col);
          vlist_deg2.push_back(v1);
        }
      }
      a= next(a,v0);
    }
    while( a != e0 );
  }

  CGAL__BOPS_DCEL_DEBUG_LN("colorized: ");
  CGAL__BOPS_DCEL_DEBUG_ITERATOR("E", this->begin(), this->end() );
  CGAL__BOPS_DCEL_DEBUG_ITERATOR("V", vertex_begin(), vertex_end() );
  CGAL__BOPS_DCEL_DEBUG_ITERATOR("F", face_begin(), face_end() );

  return true;
}



#endif /* CGAL__DCEL_C */
