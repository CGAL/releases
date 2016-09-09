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
// file          : include/CGAL/bops_V2E_rep.h
// package       : bops (1.0.5)
// source        : include/CGAL/bops_V2E_rep.h
// revision      : $Revision: 1.0.5 $
// revision_date : $Date: Tue Jun 30 19:04:26 MET DST 1998  $
// author(s)     :        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__V2E_REP_H
#define CGAL__V2E_REP_H

#include <list.h>
#include <vector.h>
#include <algo.h>

#ifdef CGAL__DCEL__V2E_DEBUG_ON
#include <CGAL/bops_dcel_out.h>
#endif


// forward declaration 
template< class T_vertex, class T_edge>
class CGAL__V2E_rep_base_type;

/*---------------------------------------------------------------------------*/
template< class T_vertex, class T_edge >
class CGAL__V2E_rep_vertex {
  int      _index;  /* index of this vertex (in header-list) */
  T_vertex _vertex; /* vertex information */
  T_edge   _edge;   /* edge information */
  int      _next;   /* index to next vertex of this sublist */
                   /* calc: container< ... >.begin() + next */
                   /* works only for containers with random access iterators */
  friend class CGAL__V2E_rep_base_type<T_vertex, T_edge>;

public:
  CGAL__V2E_rep_vertex() {};
  CGAL__V2E_rep_vertex(int ind, T_vertex v, T_edge e) :
    _index(ind), _vertex(v), _edge(e), _next(-1) {};

  /* returns index of this vertex (in header-list) */
  operator int()   const { return _index; }
  int      index() const { return _index; }
  int&     next()  { return _next; } // should be private !!!
  int      next()  const { return _next; }
                   /* returns index to next vertex of this sublist */
                   /* calc: container< ... >.begin() + next */
                   /* works only for containers with random access iterators */
  T_vertex  vertex()const { return _vertex; }   /* returns vertex information */
  T_vertex& vertex()      { return _vertex; }   /* returns vertex information */
  T_edge    edge()  const { return _edge; }   /* returns edge information */
};

/*---------------------------------------------------------------------------*/
template<class Iterator>
class CGAL__V2E_rep_header {
public:

  CGAL__V2E_rep_header() : _this_set(false), _size(0)  {}
  CGAL__V2E_rep_header(Iterator h) :
            _begin(h), _end(h), _this_set(false), _size(0)  {}

  int size() const { return _size; }
  bool isEmpty() const { return (_size ==0); }
  bool isThisSet() const { return _this_set; }
  Iterator vertex() const { return _this_vertex; }
  Iterator begin() const { return _begin; }
  Iterator end() const { return _end; }

  void vertex(Iterator v) { /* sets information for this vertex */
    if( !isThisSet() ) {
      _this_vertex= v;
      _this_set= true;
    }
  }

  int& size() { return _size; }
  Iterator& begin() { return _begin; }
  Iterator& end() { return _end; }

private:
  Iterator _begin; /* pointer to first vertex */
  Iterator _end;   /* pointer to last vertex */
  Iterator _this_vertex;   /* pointer to this vertex */
  bool _this_set;  /* true if this_vertex is set */
  int      _size;  /* how many vertices are appended */
};


/*---------------------------------------------------------------------------*/
template< class T_vertex, class T_edge>
class CGAL__V2E_rep_base_type {
public:

  typedef CGAL__V2E_rep_vertex<T_vertex,T_edge>     vertex_type;
  typedef typename vector<vertex_type>::iterator       vertex_iterator;
  typedef typename vector<vertex_type>::const_iterator vertex_const_iterator;
  typedef CGAL__V2E_rep_header< vertex_iterator >   header_type;
  typedef typename vector<header_type>::iterator       header_iterator;
  typedef typename vector<header_type>::const_iterator header_const_iterator;
  typedef typename vector<header_type>::size_type      size_type;

private:
	header_type hhhhhhh; // for sparc_SunOS-5.5_CC-4.2

public:
  CGAL__V2E_rep_base_type() {}
  CGAL__V2E_rep_base_type(size_type n_vertices, size_type m_edges) {
    init(n_vertices, m_edges);
  }

  header_type header(int i) const { return _header_list[i]; }
  vertex_type vertex(int i) const { return _vertex_list[i]; }

  header_const_iterator header_begin() const { return _header_list.begin(); }
  header_const_iterator header_end()   const { return _header_list.end(); }

  header_iterator header_begin() { return _header_list.begin(); }
  header_iterator header_end()   { return _header_list.end(); }

  vertex_const_iterator vertex_begin(header_const_iterator i) const {
    return (*i).begin();
  }
  vertex_const_iterator vertex_next(vertex_const_iterator i) const {
    return (*i).next() == -1 ? vertex_end() : next((*i).next());
  }
  vertex_const_iterator vertex_end(vertex_const_iterator ) const {
    return vertex_end();
  }

  vertex_iterator vertex_begin(header_iterator i) { return (*i).begin(); }
  vertex_iterator vertex_next(vertex_iterator i)  {
    return (*i).next() == -1 ? vertex_end() : next((*i).next());
  }
  vertex_iterator vertex_end(vertex_iterator )   { return vertex_end(); }

  vertex_iterator vertex_begin(int i) const { return header(i).begin(); }
  vertex_iterator vertex_next(int i)  { return next(vertex(i).next()); }
  vertex_iterator vertex_end(int i)   const { return header(i).end(); }

  vertex_const_iterator vertex_begin() const { return _vertex_list.begin(); }
  vertex_const_iterator vertex_end()   const { return _vertex_list.end(); }
  vertex_iterator vertex_begin() { return _vertex_list.begin(); }
  vertex_iterator vertex_end()   { return _vertex_list.end(); }

  bool insert( int iv1, T_vertex v1, int iv2, T_vertex v2, T_edge e) {
    /* returns false, if index iv1 or iv2 is to high */
    /*         in that case no insertion will be done */
    /* returns true, if everything works well */
    if( iv1 >= (int)_header_list.size() || iv2 >= (int)_header_list.size())
      return false;

    vertex_iterator it1= insert(iv1, iv2, v2, e);
    vertex_iterator it2= insert(iv2, iv1, v1, e);
    header(iv1).vertex(it2);
    header(iv2).vertex(it1);
    return true;
  }

  vertex_iterator insert( int i, int iv, T_vertex v, T_edge e) {
    /* returns false, if index i is to high */
    /*         in that case no insertion will be done */
    /* returns true, if everything works well */
    _vertex_list.push_back( CGAL__V2E_rep_vertex<T_vertex,T_edge>(iv,v,e) );
    vertex_iterator it_last= _vertex_list.end();
    advance( it_last, -1);

    if( header(i).isEmpty() ) /* insert new vertex */
      header(i).begin()= it_last;
    else
      (*header(i).end()).next()= next(it_last);
    header(i).end()= it_last;
    header(i).size()++;
    return it_last;
  }


protected:
  typedef typename vector<vertex_iterator>::iterator vertex_iterator_iterator;

  void set_vertices(int v,
       vertex_iterator_iterator from, vertex_iterator_iterator to)
  {
    vertex_iterator set;

    header(v).begin()= *from;
    while( from != to ) {
      set= *from;
      from++;
      (*set).next()= next(*from); /* actualize this iterator */
    }
    from--;
    header(v).end()= *from;
    (*header(v).end()).next()= -1;
    return;
  }

  void init(size_type n_vertices, size_type m_edges ) {
    _no_of_vertices= n_vertices;
    _no_of_edges= m_edges;
    _header_list.reserve( _no_of_vertices );
    _vertex_list.reserve( 2 * _no_of_edges );

    /* initialize header-list */
    for( int i= 0; i < (int)_no_of_vertices; i++ )
      _header_list.push_back(header_type());
  }
  

  vertex_const_iterator next(int i) const { return (_vertex_list.begin() + i); }
  vertex_iterator next(int i) { return (_vertex_list.begin() + i); }
  int next(vertex_iterator i) const { return (i - _vertex_list.begin()); }

  header_type& header(int i) { return _header_list[i]; }
  vertex_type& vertex(int i) { return _vertex_list[i]; }

  size_type _no_of_vertices;
  size_type _no_of_edges;
  vector< header_type >     _header_list;
  vector< vertex_type >     _vertex_list;
};

/*---------------------------------------------------------------------------*/
template< class T_vertex, class T_edge, class T_compare >
struct CGAL__V2E_rep_compare : public T_compare {
  typedef CGAL__V2E_rep_vertex<T_vertex,T_edge>     vertex_type;
  typedef typename vector<vertex_type>::const_iterator vertex_iterator;
  CGAL__V2E_rep_compare (vertex_iterator v0) : T_compare((*v0).vertex()) {}
  bool operator()( vertex_iterator v1, vertex_iterator v2 ) {
    return compare((*v1).vertex(),(*v2).vertex());
  }
};

/*---------------------------------------------------------------------------*/
template< class T_vertex, class T_edge, class T_compare >
class CGAL__V2E_rep_type : public CGAL__V2E_rep_base_type<T_vertex, T_edge> {
public:
  
  //typedef CGAL__V2E_rep_type<T_vertex,T_edge,T_compare> THIS;
  //typedef CGAL__V2E_rep_base_type<T_vertex,T_edge>      SUPER;


  typedef CGAL__V2E_rep_vertex<T_vertex,T_edge>     vertex_type;
  typedef typename vector<vertex_type>::iterator             vertex_iterator;
  typedef CGAL__V2E_rep_header< vertex_iterator >   header_type;
  typedef typename vector<header_type>::iterator             header_iterator;
  typedef typename vector<header_type>::size_type            size_type;

public:
  CGAL__V2E_rep_type() {}
  CGAL__V2E_rep_type(size_type n_vertices, size_type m_edges) :
    CGAL__V2E_rep_base_type<T_vertex, T_edge>(n_vertices, m_edges) {}


  void sort_vertices_CCW() {
    /* if function compare is defined correctly this function sorts all 
       vertices counterclockwise */
    for(int v= 0; v < (int)_header_list.size(); v++)
      sort_CCW(v);
    return;
  }


private:

  void sort_CCW(int v) {
    typedef CGAL__V2E_rep_compare<T_vertex,T_edge,T_compare> Compare;
    if( header(v).size() > 2 ) {
      vector<vertex_iterator> Lv;
      Lv.reserve( header(v).size() );
      for( vertex_iterator it= vertex_begin(v);
	   it != vertex_end(it);
	   it= vertex_next(it) )
        Lv.push_back(it);

      Compare compare_object( header(v).vertex());

#ifdef CGAL__DCEL__V2E_DEBUG_ON
      cout << "-----------" << endl;
        cout << "v0= " << (*(header(v).vertex())).vertex() << endl;
      vector<vertex_iterator>::iterator _it;
      int _i= 0;
      for(_i= 0, _it= Lv.begin(); _it != Lv.end(); _i++,_it++)
        cout << "Lv[" << _i << "]= " << (*(*_it)).vertex() << endl;
#endif
      sort(Lv.begin(), Lv.end(),  compare_object );
#ifdef CGAL__DCEL__V2E_DEBUG_ON
      for(_i= 0, _it= Lv.begin(); _it != Lv.end(); _i++,_it++)
        cout << "Lv[" << _i << "]= " << (*(*_it)).vertex() << endl;
#endif
      set_vertices( v, Lv.begin(), Lv.end() );
    }
    return;
  }
};

#endif  /* CGAL__V2E_REP_H */
