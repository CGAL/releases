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


// Source: dcel.h
// Author: Wolfgang Freiseisen

#ifndef CGAL__DCEL_H
#define CGAL__DCEL_H

#include <CGAL/bops_dcel_defs.h>
#include <CGAL/bops_dcel_base.h>



/*
  Implementation of the Double Connected Edge List (DCEL)
  -------------------------------------------------------

  template <class R> class DCEL__Dcel;

*/
  typedef  pair<int,int> epair;


#ifdef CGAL_POINT_DEFINED
template <class R>
#endif
class CGAL__Dcel : public CGAL__Dcel_base
{
  typedef CGAL__Dcel_base SUPER;
  typedef CGAL__Dcel<R>   THIS;
public:
  typedef vector<CGAL__Dcel_edge_type>  ::const_iterator edge_iterator;
  typedef vector<CGAL__Dcel_face_type>  ::const_iterator face_iterator;
  typedef vector<CGAL__Dcel_vertex_type>::const_iterator vertex_iterator;

  CGAL__Dcel() {}

  CGAL__Dcel(const CGAL__Dcel<R>& dl) { *this= dl; }
  
  CGAL__Dcel( const list< epair >& eds, const list< CGAL__Point_2 >& pts ) {
    insert(eds,pts);
  }

  CGAL__Dcel( const list< epair >& eds, const deque< CGAL__Point_2 >& pts ) {
    insert(eds,pts);
  }

  bool colorize(const list< CGAL__Point_2 >& pgon, const CGAL__Dcel_Color& col);


  CGAL__Point_2 point(vertex_iterator v) const {
    return CGAL__Vertex_to_point_2(v, CGAL__Point_2());
  }

  vertex_iterator find( const CGAL__Point_2& pt ) const {
#ifdef CGAL_POINT_DEFINED
     CGAL__Dcel_point_compare<R> pred(pt);
#else
     CGAL__Dcel_point_compare    pred(pt);
#endif
     return  find_if(_v_list.begin(), _v_list.end(), pred );
  }

  vertex_iterator null_vertex(void) const {
    return _v_list.end();
  }

private:
  void insert_points(const list< CGAL__Point_2 >&  pts);
  void insert_points(const deque< CGAL__Point_2 >& pts );

  list< epair > edges;
  vector<vertex_iterator> c_it; /* help-array */

public:
  void insert(const list< epair >& eds, const list< CGAL__Point_2 >& pts ) {
      insert_points(pts);
      edges= eds; // since compiler (g++, Solaris)  problems, we have to do this
      insert_edges(); edges=  list< epair >();
      c_it= vector<vertex_iterator>();
  }

  void insert(const list< epair >& eds, const deque< CGAL__Point_2 >& pts ) {
      insert_points(pts);
      edges= eds; // since compiler (g++, Solaris)  problems, we have to do this
      insert_edges(); edges=  list< epair >();
      c_it= vector<vertex_iterator>();
  }

private:

  void insert_edges();

  vertex_iterator insert_point( const CGAL__Point_2& pt, int index ) {
#ifdef CGAL_POINT_DEFINED
    CGAL_Object obj= CGAL_make_object(pt);
    return insert_new_vertex(obj, index);
#else
    return insert_new_vertex(pt, index);
#endif
  }
  
  vertex_iterator insert_new_vertex(
#ifdef CGAL_POINT_DEFINED
    const CGAL_Object& obj,
#else
    const CGAL__Point_2& pt,
#endif
    int index,
    CGAL__Dcel_Color col = CGAL__NO_COLOR
  )
  {
#ifdef CGAL_POINT_DEFINED
     CGAL_Point_2<R> pt;
     CGAL_assign(pt, obj);
#endif
     vertex_iterator it= find(pt);

     if( it == null_vertex() ) 
       /* vertex does not exist, hence append vertex */
#ifdef CGAL_POINT_DEFINED
       it= SUPER::insert( CGAL__Dcel_vertex_type(obj, index, col) );
#else
       it= SUPER::insert( CGAL__Dcel_vertex_type(pt, index, col) );
#endif

     return it;
  }

};


#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/bops_dcel.C>
#endif 

#endif /* CGAL__DCEL_H */

