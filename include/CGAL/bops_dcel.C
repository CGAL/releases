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


// Source: bops_dcel.C
// Author: Wolfgang Freiseisen
 


#ifndef CGAL__DCEL_C
#define CGAL__DCEL_C

#ifndef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/bops_dcel.h>
#endif

#include <CGAL/bops_V2E_rep.h>
#include <CGAL/bops_dcel_out.h>
#include <CGAL/bops_V2E_rep_out.h>

//#define CGAL__DCEL_DEBUG_ON

#ifndef CGAL_POINT_DEFINED
template< class T >
bool smaller_than(T x1, T y1, T x2, T y2) {
// only for testing without CGAL-Points
  int quadrant1= (x1 < 0) ? (y1<0 ? 3 : 2) : (y1<0 ? 4 : 1);
  int quadrant2= (x2 < 0) ? (y2<0 ? 3 : 2) : (y2<0 ? 4 : 1);
  if( quadrant1 < quadrant2 ) return true;
  if( quadrant1 > quadrant2 ) return false;
  return y1 * x2 < y2 * x1;
} 
#endif // CGAL_POINT_DEFINED

#ifdef CGAL_POINT_DEFINED
template<class R>
#endif
bool CGAL__leftturn(const CGAL__Point_2& p0, /* "origin" */
                   const CGAL__Point_2& p1,
                   const CGAL__Point_2& p2) {
#ifdef CGAL_POINT_DEFINED
  return (p1-p0).direction() < (p2-p0).direction();
#else
  return smaller_than(
   p1.first-p0.first, p1.second-p0.second,
   p2.first-p0.first, p2.second-p0.second
  );
#endif
}


#ifdef CGAL_POINT_DEFINED
template<class R>
#endif
struct CGAL__Dcel_V2E_compare {
   CGAL__Point_2 pts( CGAL__Dcel_vertex v ) {
     return CGAL__Vertex_to_point_2(v, CGAL__Point_2());
   }
   bool operator()(
       CGAL__Dcel_vertex v0,  /* "origin" */
       CGAL__Dcel_vertex v1 ,
       CGAL__Dcel_vertex v2 )
       {
          return CGAL__leftturn( pts(v0), pts(v1), pts(v2) );
       }
};


/*
  Implementation of the Double Connected Edge List (DCEL)
  -------------------------------------------------------

  template <class R> class DCEL__Dcel;
*/

#ifdef CGAL_POINT_DEFINED
template <class R> void CGAL__Dcel<R> ::
insert_points(const list< CGAL_Point_2<R> >& points)
#else
void CGAL__Dcel ::
insert_points(const list<CGAL__Point_2>& points)
#endif
{
    //vector<vertex_iterator> c_it; /* help-array */
    /* insert vertices (also in help array) */
  _v_list.reserve(points.size());
  int n= 0;
  list< CGAL__Point_2 >::const_iterator it;
  for( it= points.begin(); it != points.end(); it++ ) 
      c_it.push_back( insert_point( *it, n++ ) );

#ifdef CGAL__DCEL_DEBUG_ON
  print(cout, "c_it", c_it.begin(), c_it.end() );
#endif /* CGAL__DCEL_DEBUG_ON */
  return;
}


#ifdef CGAL_POINT_DEFINED
template <class R> void CGAL__Dcel<R> ::
insert_points(const deque< CGAL_Point_2<R> >& points)
#else
void CGAL__Dcel ::
insert_points(const deque<CGAL__Point_2>& points)
#endif
{
  // vector<vertex_iterator> c_it; /* help-array */
  /* insert vertices (also in help array) */
  _v_list.reserve(points.size());
  int n= 0;
  deque< CGAL__Point_2 >::const_iterator it;
  for( it= points.begin(); it != points.end(); it++ ) 
      c_it.push_back( insert_point( *it, n++ ) );

#ifdef CGAL__DCEL_DEBUG_ON
  print(cout, "c_it", c_it.begin(), c_it.end() );
#endif /* CGAL__DCEL_DEBUG_ON */
  return;
}


#ifdef CGAL_POINT_DEFINED
template <class R> void CGAL__Dcel<R> ::
#else
void CGAL__Dcel ::
#endif
insert_edges() {

typedef CGAL__V2E_rep_type<vertex_iterator,edge_iterator, 
        CGAL__Dcel_V2E_compare<R> >
  V2E_rep_dcel;
typedef CGAL__V2E_rep_base_type<vertex_iterator,edge_iterator>
  V2E_rep_base;

#if 0
    vector<vertex_iterator> c_it; /* help-array */
    /* insert vertices (also in help array) */
    _v_list.reserve(points.size());
    int n= 0;
    list< CGAL__Point_2 >::const_iterator it;
    for(  it= points.begin(); it != points.end(); it++ ) 
      c_it.push_back( insert_point( *it, n++ ) );

#ifdef CGAL__DCEL_DEBUG_ON
    print(cout, "c_it", c_it.begin(), c_it.end() );
#endif /* CGAL__DCEL_DEBUG_ON */
#endif

    /* insert edges */
    _e_list.reserve(edges.size());
    list< pair<int,int> >::const_iterator ee;
    for( ee= edges.begin(); ee != edges.end(); ee++ )
      CGAL__Dcel_base::insert( CGAL__Dcel_edge_type(c_it[(*ee).first], c_it[(*ee).second]) );
    
#ifdef CGAL__DCEL_DEBUG_ON
    cout << "VERTICES inserted: " << endl;
    print(cout, "dcel", this->begin(), this->end() );
#endif /* CGAL__DCEL_DEBUG_ON */

    /* template< class T_vertex, class T_edge, class T_compare > */
    V2E_rep_dcel v2e_rep( c_it.size(), edges.size() );

    /* insertion in vertex-to-edge rep. */
    /* vertex_iterator v0= _v_list.begin(); */
    vertex_iterator v1, v2;
    int iv1, iv2;
    for( edge_iterator e= _e_list.begin(); e != _e_list.end(); e++ ) {
      v1= (*e).V1();
      v2= (*e).V2();
      iv1= (*v1).index();
      iv2= (*v2).index();
#ifdef CGAL__DCEL_DEBUG_ON
      cout << "insert: " << e << '(' << iv1 << ',' << iv2 << ')' << endl;
#endif /* CGAL__DCEL_DEBUG_ON */
      v2e_rep.insert( iv1, (*e).V1(), iv2, (*e).V2(), e);
      //v2e_rep.insert( (*e).V1()-v0, (*e).V1(), (*e).V2()-v0 , (*e).V2(), e);
    }

#ifdef CGAL__DCEL_DEBUG_ON
    cout << (V2E_rep_base)v2e_rep;
#endif /* CGAL__DCEL_DEBUG_ON */

    v2e_rep.sort_vertices_CCW();

#ifdef CGAL__DCEL_DEBUG_ON
    cout << (V2E_rep_base)v2e_rep;
#endif /* CGAL__DCEL_DEBUG_ON */


    /* construction of vertex cycles */
    construct_vertex_cycles( v2e_rep );
#ifdef CGAL__DCEL_DEBUG_ON
    cout << "POINTERS inserted: " << endl;
    print(cout, "dcel", this->begin(), this->end() );
#endif /* CGAL__DCEL_DEBUG_ON */
  
    /* construction of face cycles */
    construct_face_cycles();
#ifdef CGAL__DCEL_DEBUG_ON
    cout << "FACES inserted: " << endl;
    print(cout, "dcel", this->begin(), this->end() );
#endif /* CGAL__DCEL_DEBUG_ON */

    return;
  }


#ifdef CGAL_POINT_DEFINED
template <class R> bool CGAL__Dcel<R> ::
#else
bool CGAL__Dcel ::
#endif
colorize(const list< CGAL__Point_2 >& pgon, const CGAL__Dcel_Color& col) {
/* This routine colorizes the interior of a simple polygon 'pgon'
   given by a list of its vertices in counterclockwise order(!).
                                      ^^^^^^^^^^^^^^^^^^^^^^^^^
   The color is given by the input variable 'col' and will be set using
   the or operation, i.e. vertex::set_color( vertex::color() | col );

   return: true  iff everything ok
           false if e.g. polygon not valid
*/

  if( pgon.size() < 3 ) return false;

  list< CGAL__Point_2 >::const_iterator it_p;

  /* get last point */
  list< CGAL__Point_2 >::const_reverse_iterator rit_p= pgon.rbegin();
  CGAL__Point_2 pt= (*rit_p);
  CGAL__Point_2 v1_pt;

  vertex_iterator v0, v1;
  v0= find( pt );       // find first vertex
  nc_vertex_iterator v= (nc_vertex_iterator)v0;
  (*v).set_color( (*v0).color() | col);
  edge_iterator a, e0;
  nc_edge_iterator e;
  nc_face_iterator f;

  list<vertex_iterator> vlist_deg2; // all vertices with degree greater than 2
  
  for(it_p= pgon.begin(); it_p != pgon.end(); it_p++) { /* for all vertices */
    v0= v;
    if( (*v0).degree() > 2 ) 
      vlist_deg2.push_back(v0);

    /* find second vertex 'v1' and edge [v0,v1] */
    a= e0= begin(v0);
    v1= (*a).opposite_vertex(v0);
#ifdef CGAL_POINT_DEFINED
    CGAL_assign(v1_pt, (*v1).point());
    if( v1_pt != *it_p )
#else
    if( (*v1).point() != *it_p )
#endif
    {
      for( a= next(e0,v0); a != e0; a= next(a,v0) ) {
        v1= (*a).opposite_vertex(v0);
#ifdef CGAL_POINT_DEFINED
        CGAL_assign(v1_pt, (*v1).point());
        if( v1_pt == *it_p ) break; /* found !! */
#else
        if( (*v1).point() == *it_p ) break; /* found !! */
#endif
      }
      if( a==e0) return false; /* ABORT: --> polygon not valid */
    }

    e= (nc_edge_iterator)a;
    (*e).set_color( (*e).color()|col);
    v= (nc_vertex_iterator)v1;
    (*v).set_color( (*v).color()|col);
    f= (nc_face_iterator)(*e).left_face(v0); /* v0 -> v1 ** pgon is CCW */
    (*f).set_color( (*f).color()|col);
  }

  
  list<vertex_iterator>::const_iterator vit;
  face_iterator f1, f2;
  for( vit= vlist_deg2.begin(); vit != vlist_deg2.end(); vit++) {
    v0= *vit;
    a= e0= begin(v0);
    do {
      if( !((*a).color() & col ) ) {
        f1= (*a).F1();
        f2= (*a).F2();
        if( (*f1).color()&col && (*f2).color()&col ) {
          e= (nc_edge_iterator)a;
          (*e).set_color( (*a).color()|col );
          v1= (*a).opposite_vertex(v0);
          v= (nc_vertex_iterator)v1;
          (*v).set_color( (*v).color()|col);
          vlist_deg2.push_back(v1);
        }
      }
      a= next(a,v0);
    }
    while( a != e0 );
  }

  return true;
}

#if 0

#ifdef CGAL_POINT_DEFINED
template <class R> bool CGAL__Dcel<R> ::
#else
void CGAL__Dcel ::
#endif
update_colors() {
/* This routine updates all vertex and edge colors,
   i.e. if an edge has two neighbour faces with color c this
        edge also should have color c

        if all consecutive edges of a vertex have color c this
        vertex also should have color c.
*/

  nc_edge_iterator e;
  for( e= begin(); e != end(); e++ ) {
    f1= (*e).F1();
    f2= (*e).F2();
    if( !((*e).color() & CGAL__RED ) ) {
      if( (*f1).color()&CGAL__RED && (*f2).color()&CGAL__RED )
        (*e).set_color( (*e).color()|CGAL__RED );
    }
    if( !((*e).color() & CGAL__BLACK ) ) {
      if( (*f1).color()&CGAL__BLACK && (*f2).color()&CGAL__BLACK )
        (*e).set_color( (*e).color()|CGAL__BLACK );
    }
  }


  nc_vertex_iterator v;
  for(v= vertex_begin(); v != vertex_end(); v++ ) {
    (*v).set_color( (*v).color()|CGAL__RED);
  }
  return;
}
#endif

#endif /* CGAL__DCEL_C */
