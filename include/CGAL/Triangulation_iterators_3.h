// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Triangulation_iterators_3.h
// package       : Triangulation3 (1.29)
// revision      : $Revision: 1.15 $
//
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis 
//                 (Mariette Yvinec)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_ITERATORS_3_H
#define CGAL_TRIANGULATION_ITERATORS_3_H

#include <utility>
#include <iterator>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_ds_iterators_3.h>

#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds >
class Triangulation_3;

template < class Gt, class Tds >
class Triangulation_cell_3;

template < class Gt, class Tds >
class Triangulation_vertex_3;

template < class Gt, class Tds>
class Triangulation_3;

template < class Gt, class Tds>
class Triangulation_cell_iterator_3;

template < class Gt, class Tds>
class Triangulation_facet_iterator_3;

template < class Gt, class Tds>
class Triangulation_edge_iterator_3;

template < class Gt, class Tds>
class Triangulation_vertex_iterator_3;


template < class Gt, class Tds>
class Triangulation_cell_iterator_3
{
public:
  typedef typename Triangulation_3<Gt,Tds>::Cell       value_type;
  typedef typename Triangulation_3<Gt,Tds>::Cell *     pointer;
  typedef typename Triangulation_3<Gt,Tds>::Cell &     reference;
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;

  typedef typename Tds::Cell Ctds;
  typedef typename Tds::Cell_iterator Iterator_base;

  typedef typename Triangulation_3<Gt,Tds>::Cell Cell;
  typedef typename Triangulation_3<Gt,Tds>::Vertex Vertex;
  typedef typename Triangulation_3<Gt,Tds>::Vertex_handle Vertex_handle;  
  typedef typename Triangulation_3<Gt,Tds>::Cell_handle Cell_handle;
  typedef Triangulation_3<Gt,Tds> Triang;

  typedef Triangulation_cell_iterator_3<Gt,Tds> Cell_iterator;

  Triangulation_cell_iterator_3()
    : _ib(), _tr(NULL), _inf(true)
  {}
        
  Triangulation_cell_iterator_3(Triangulation_3<Gt,Tds> *tr, bool inf)
    : _ib( &(tr->_tds)), _tr(tr), _inf(inf)
    { 
      if (! _inf) {
	while ( // ( _ib != _tr->_tds.cells_end() ) &&
	       // useless : there must be at least one finite cell
	       // since precond in _ib : dimension == 3
	       _tr->is_infinite(Cell_handle( (Cell *) &(*(_ib)) )) )
	  { ++_ib; }
      }
    }
  
  // for past-end iterator
  // does not need to find a finite cell
  Triangulation_cell_iterator_3(Triangulation_3<Gt,Tds> *tr)
    : _ib( &(tr->_tds), 1), _tr(tr), _inf(true)
  { }
       
  Triangulation_cell_iterator_3(const Cell_iterator & cit)
    : _ib(cit._ib), _tr(cit._tr), _inf(cit._inf)
  {}
        
  Cell_iterator&
  operator=(const Cell_iterator & cit)
  { 
    _ib = cit._ib;
    _tr = cit._tr;
    _inf = cit._inf;
    return *this;
  }
  
  bool
  operator==(const Cell_iterator & cit) const
  {
    if ( _tr != cit._tr ) 
      return false;

    if ( ( _ib == _tr->_tds.cells_end() ) 
	 || ( cit._ib == _tr->_tds.cells_end() ) ) 
      return ( _ib == cit._ib );

    return ( ( _ib == cit._ib ) && ( _inf == cit._inf ) );
  }

  bool
  operator!=(const Cell_iterator & cit)
  {
    return ( !(*this == cit) );
  }

  Cell_iterator &
  operator++()
  {
    if (_inf) {
      ++_ib;
    }
    else {
      do {
	++_ib; 
      } while ( ( _ib != _tr->_tds.cells_end() )
		&& _tr->is_infinite(Cell_handle( (Cell *) &(*(_ib)) )) );
    }
    return *this;   
  }

  Cell_iterator &
  operator--()
  {
    if (_inf) {
      --_ib;
    }
    else{
      do {
	--_ib;
      } while ( ( _ib != _tr->_tds.cells_end() )
		&& _tr->is_infinite(Cell_handle( (Cell *) &(*(_ib)) )) );
    }
    return *this;   
  }

  Cell_iterator
  operator++(int)
  {
    Cell_iterator tmp(*this);
    ++(*this);
    return tmp;
  }
        
  Cell_iterator
  operator--(int)
  {
    Cell_iterator tmp(*this);
    --(*this);
    return tmp;
  }
        
  inline Cell & operator*() const
  {
    return (Cell &)(*_ib);
  }

  inline Cell* operator->() const
  {
    return (Cell*)( &(*_ib) );
  }
     
private: 
  Iterator_base _ib;
  Triang * _tr;
  bool _inf; // if _inf == true, traverses all cells
               // else only traverses finite cells
};


template < class Gt, class Tds>
class Triangulation_vertex_iterator_3
{
public:
  typedef typename Triangulation_3<Gt,Tds>::Vertex       value_type;
  typedef typename Triangulation_3<Gt,Tds>::Vertex *     pointer;
  typedef typename Triangulation_3<Gt,Tds>::Vertex &     reference;
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;

  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Vertex_iterator Iterator_base;

  typedef typename Triangulation_3<Gt,Tds>::Vertex Vertex;
  typedef typename Triangulation_3<Gt,Tds>::Vertex_handle Vertex_handle;
  typedef Triangulation_3<Gt,Tds> Triang;

  typedef Triangulation_vertex_iterator_3<Gt,Tds> Vertex_iterator;

  Triangulation_vertex_iterator_3()
    : _ib(), _tr(NULL), _inf(true)
  {}
        
  Triangulation_vertex_iterator_3(Triangulation_3<Gt,Tds> * tr, bool inf)
    : _ib( &(tr->_tds)), _tr(tr), _inf(inf)
    { 
      if (! _inf) {
	if ( _tr->is_infinite(Vertex_handle( (Vertex *) &(*(_ib)) )) ) {
	  ++_ib;
	}
      }
    }
        
  // for past-end iterator
  // does not need to find a finite cell
  Triangulation_vertex_iterator_3(Triangulation_3<Gt,Tds> * tr)
    : _ib( &(tr->_tds), 1), _tr(tr)
  { }
       
  Triangulation_vertex_iterator_3(const Vertex_iterator & vi)
    : _ib(vi._ib), _tr(vi._tr), _inf(vi._inf)
  {}
        
  Vertex_iterator &
  operator=(const Vertex_iterator & vi)
  { 
    _ib = vi._ib;
    _tr = vi._tr;
    _inf = vi._inf;
    return *this;
  }
  
  bool
  operator==(const Vertex_iterator & vi) const
  {
    if ( _tr != vi._tr ) 
      return false;

    if ( ( _ib == _tr->_tds.vertices_end() ) 
	 || ( vi._ib == _tr->_tds.vertices_end() ) ) 
      return ( _ib == vi._ib );

    return ( ( _ib == vi._ib ) && ( _inf == vi._inf ) );
  }

  bool
  operator!=(const Vertex_iterator & vi)
  {
    return ( !(*this == vi) );
  }

  Vertex_iterator &
  operator++()
  {
    if (_inf) {
      ++_ib;
    }
    else {
      ++_ib; 
      if ( _tr->is_infinite(Vertex_handle( (Vertex *) &(*(_ib)) )) ) {
	++_ib;
      }
    }
    return *this;   
  }

  Vertex_iterator &
  operator--()
  {
    if (_inf) {
      --_ib;
    }
    else{
      --_ib;
      if ( _tr->is_infinite(Vertex_handle( (Vertex *) &(*(_ib)) )) ) {
	--_ib;
      }
    }
    return *this;   
  }

  Vertex_iterator
  operator++(int)
  {
    Vertex_iterator tmp(*this);
    ++(*this);
    return tmp;
  }
        
  Vertex_iterator
  operator--(int)
  {
    Vertex_iterator tmp(*this);
    --(*this);
    return tmp;
  }

  inline Vertex & operator*() const
  {
    return (Vertex &)(*_ib);
  }

  inline Vertex* operator->() const
  {
    return   (Vertex*)( &(*_ib) );
  }
     
private:
  Iterator_base   _ib;
  Triang * _tr;
  bool _inf; // if _inf == true, traverses all vertices
               // else only traverses finite vertices
};


template < class Gt, class Tds>
class Triangulation_edge_iterator_3
{
public:
  typedef typename Triangulation_3<Gt,Tds>::Edge       value_type;
  typedef typename Triangulation_3<Gt,Tds>::Edge *     pointer;
  typedef typename Triangulation_3<Gt,Tds>::Edge &     reference;
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;

  typedef typename Tds::Edge Etds;
  typedef typename Tds::Edge_iterator  Iterator_base;

  typedef typename Triangulation_3<Gt,Tds>::Edge Edge;
  typedef typename Triangulation_3<Gt,Tds>::Cell_handle Cell_handle;
  typedef typename Triangulation_3<Gt,Tds>::Cell Cell;
  typedef Triangulation_3<Gt,Tds> Triang;

  typedef Triangulation_edge_iterator_3<Gt,Tds>      Edge_iterator;

  Triangulation_edge_iterator_3()
    : _ib(), _tr(NULL), _inf(true)
  {}
        
  Triangulation_edge_iterator_3(Triangulation_3<Gt,Tds> *tr, bool inf)
    : _ib( &(tr->_tds)), _tr(tr), _inf(inf)
  { 
    if (! _inf) {
	while ( // ( _ib != _tr->_tds.cells_end() ) &&
	   // useless : there must be at least one finite cell
	   // since precond in _ib : dimension == 3
	       _tr->is_infinite(make_triple(Cell_handle((Cell *)(*_ib).first),
					    (*_ib).second, (*_ib).third )) )
	  { ++_ib; }
    }
  }
        
  Triangulation_edge_iterator_3(Triangulation_3<Gt,Tds> *tr)
    : _ib( &(tr->_tds), 1), _tr(tr), _inf(true)
    // _inf is initialized but should never be used
  { }
       
  Triangulation_edge_iterator_3(const Edge_iterator & ei)
    : _ib(ei._ib), _tr(ei._tr), _inf(ei._inf)
  {}
        
  Edge_iterator &
  operator=(const Edge_iterator & ei)
  { 
    _ib = ei._ib;
    _tr = ei._tr;
    _inf = ei._inf;
    return *this;
  }
  
  bool
  operator==(const Edge_iterator & ei) const
  {
    if ( _tr != ei._tr ) 
      return false;

    if ( ( _ib == _tr->_tds.edges_end() ) 
	 || ( ei._ib == _tr->_tds.edges_end() ) ) 
      return ( _ib == ei._ib );

    return ( ( _ib == ei._ib ) && ( _inf == ei._inf ) );
  }

  bool
  operator!=(const Edge_iterator & ei)
  {
    return !(*this == ei);
  }

  Edge_iterator &
  operator++()
  {
    if (_inf) {
      ++_ib;
    }
    else {
      do {
	++_ib; 
      } while ( ( _ib != _tr->_tds.edges_end() )
		&& _tr->is_infinite(make_triple(Cell_handle
						( (Cell *) (*_ib).first),
						(*_ib).second,
						(*_ib).third )) );
    }
    return *this;   
  }

  Edge_iterator &
  operator--()
  {
    if (_inf) {
      --_ib;
    }
    else{
      do {
	--_ib;
      } while ( ( _ib != _tr->_tds.edges_end() )
	      && _tr->is_infinite(make_triple(Cell_handle
					      ( (Cell *) (*_ib).first),
					      (*_ib).second,
					      (*_ib).third )) );
    }
    return *this;   
  }

  Edge_iterator
  operator++(int)
  {
    Edge_iterator tmp(*this);
    ++(*this);
    return tmp;
  }
        
  Edge_iterator
  operator--(int)
  {
    Edge_iterator tmp(*this);
    --(*this);
    return tmp;
  }
        
  inline Edge operator*() const
  {
    Cell_handle ch = (Cell *)( (*_ib).first );
    return make_triple( ch, (*_ib).second, (*_ib).third );
  }
     
private:
  Iterator_base _ib ;
  Triang * _tr;
  bool _inf; // if _inf == true, traverses all edges
               // else only traverses finite edges
};

template < class Gt, class Tds>
class Triangulation_facet_iterator_3
{
public:
  typedef typename Triangulation_3<Gt,Tds>::Facet       value_type;
  typedef typename Triangulation_3<Gt,Tds>::Facet *     pointer;
  typedef typename Triangulation_3<Gt,Tds>::Facet &     reference;
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;

  typedef typename Tds::Facet Ftds;
  typedef typename Tds::Facet_iterator  Iterator_base;

  typedef typename Triangulation_3<Gt,Tds>::Facet Facet;
  typedef typename Triangulation_3<Gt,Tds>::Cell_handle Cell_handle;
  typedef typename Triangulation_3<Gt,Tds>::Cell Cell;
  typedef Triangulation_3<Gt,Tds> Triang;

  typedef Triangulation_facet_iterator_3<Gt,Tds> Facet_iterator;

  Triangulation_facet_iterator_3()
    : _ib(), _tr(NULL), _inf(true)
  {}
        
  Triangulation_facet_iterator_3(Triangulation_3<Gt,Tds> *tr, bool inf)
    : _ib( &(tr->_tds)), _tr(tr), _inf(inf)
  {       
    if (! _inf) {
      while ( // ( _ib != _tr->_tds.cells_end() ) &&
	     // useless : there must be at least one finite cell
	     // since precond in _ib : dimension == 3
	     _tr->is_infinite(std::make_pair(Cell_handle
					     ( (Cell *) (*_ib).first),
					     (*_ib).second )) )
	{ ++_ib; }
    }
  }
        
  Triangulation_facet_iterator_3(Triangulation_3<Gt,Tds> *tr)
    : _ib( &(tr->_tds), 1), _tr(tr), _inf(true)
  // _inf is initialized but should never be used
  { }
       
  Triangulation_facet_iterator_3(const Facet_iterator & fi)
    : _ib(fi._ib), _tr(fi._tr), _inf(fi._inf)
  {}
        
  Facet_iterator &
  operator=(const Facet_iterator & fi)
  { 
    _ib = fi._ib;
    _tr = fi._tr;
    _inf = fi._inf;
    return *this;
  }
  
  bool
  operator==(const Facet_iterator & fi) const
  {
    if ( _tr != fi._tr ) 
      return false;

    if ( ( _ib == _tr->_tds.facets_end() ) 
	 || ( fi._ib == _tr->_tds.facets_end() ) ) 
      return ( _ib == fi._ib );

    return ( ( _ib == fi._ib ) && ( _inf == fi._inf ) );
  }

  bool
  operator!=(const Facet_iterator & fi)
  {
    return !(*this == fi);
  }

  Facet_iterator &
  operator++()
  {
    if (_inf) {
      ++_ib;
    }
    else {
      do {
	++_ib; 
      } while ( ( _ib != _tr->_tds.facets_end() )
		&& _tr->is_infinite(std::make_pair(Cell_handle
						   ( (Cell *) (*_ib).first),
						   (*_ib).second )) );
    }
    return *this;   
  }

  Facet_iterator &
  operator--()
  {
    if (_inf) {
      --_ib;
    }
    else{
      do {
	--_ib;
      } while ( ( _ib != _tr->_tds.facets_end() )
		&& _tr->is_infinite(std::make_pair(Cell_handle
						   ( (Cell *) (*_ib).first),
						   (*_ib).second )) );
    }
    return *this;   
  }

  Facet_iterator
  operator++(int)
  {
    Facet_iterator tmp(*this);
    ++(*this);
    return tmp;
  }
        
  Facet_iterator
  operator--(int)
  {
    Facet_iterator tmp(*this);
    --(*this);
    return tmp;
  }
        
  inline Facet operator*() const
  {
    Cell_handle ch = (Cell *)( (*_ib).first );
    return std::make_pair( ch, (*_ib).second );
  }
     
private:
  Iterator_base   _ib ;
  Triang * _tr;
  bool _inf; // if _inf == true, traverses all facets
               // else only traverses finite facets
};

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_ITERATORS_3_H
