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
// file          : include/CGAL/Triangulation_ds_iterators_3.h
// package       : Triangulation3 (1.29)
// revision      : $Revision: 1.20 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis 
//                 (Mariette Yvinec)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_DS_ITERATORS_3_H
#define CGAL_TRIANGULATION_DS_ITERATORS_3_H

#include <CGAL/triple.h>
#include <utility>
#include <CGAL/triangulation_assertions.h>

#include <CGAL/Triangulation_ds_circulators_3.h>

#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class Vb, class Cb >
class Triangulation_ds_vertex_3;
template < class Vb, class Cb >
class Triangulation_ds_cell_3;
template < class Vb, class Cb >
class Triangulation_data_structure_3;
template <class Tds>
class Triangulation_ds_cell_circulator_3;

template<class Tds>
class Triangulation_ds_cell_iterator_3
{
public:
  typedef typename Tds::Cell       value_type;
  typedef typename Tds::Cell *     pointer;
  typedef typename Tds::Cell &     reference;
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;

  typedef typename Tds::Cell Cell;
  typedef Triangulation_ds_cell_iterator_3<Tds> Cell_iterator;

  // CONSTRUCTORS

  Triangulation_ds_cell_iterator_3()
    : _tds(NULL), pos(NULL)
    {}
  
  Triangulation_ds_cell_iterator_3(Tds * tds)
    : _tds(tds)
    {
//       if ( _tds->dimension() <3 ) { pos = NULL; } // there is no cell yet
      if ( _tds->dimension() <3 ) { pos = _tds->past_end_cell(); }
      // there is no cell yet
      else { pos = _tds->list_of_cells()._next_cell; } 
      // first cell of the list
    }

  // used to initialize the past-the end iterator
  Triangulation_ds_cell_iterator_3(Tds* tds, int)
    : _tds(tds)
    {
//       if ( _tds->dimension() <3 ) { pos = NULL; } // there is no cell yet
//       else { pos = _tds->past_end_cell(); }
      pos = _tds->past_end_cell();
    }
  
// MT ne sert a rien ?
//   Triangulation_ds_iterator_base_3(Tds* tds, Cell* f)
//     : pos(f), _tds(tds)
//     {}
//   Triangulation_ds_cell_iterator_3(const Cell_iterator& fi)
//     : Iterator_base(fi._tds, fi.pos)
//     {}
  
  // OPERATORS
  
  Cell_iterator &
  operator=(const Cell_iterator & fi)
    {
      pos = fi.pos;
      _tds = fi._tds;
      return *this;
    }

  bool
  operator==(const Cell_iterator & fi) const
    {
      return ((pos == fi.pos )&&(_tds==fi._tds));
    }
  
  bool
  operator!=(const Cell_iterator& fi)
    {
      return !(*this == fi);
    }
  
  Cell_iterator &
  operator++()
    {
      // the user should not use ++ on a non-initialized iterator
//       if (pos==NULL){
// 	return *this;            
//       }
      // removed : past the end iterator can go further
//       if ( pos == _tds->past_end_cell() ){
// 	return *this;    
//       } 
      pos = pos->_next_cell;
      return *this;
    }

  Cell_iterator &
  operator--()
    {
      // the user should not use ++ on a non-initialized iterator
//       if (pos==NULL){
// 	return *this;            
//       }
      // removed : begin iterator can go backwards
//       if ( pos == _tds->list_of_cells()._next_cell ) {
// 	return *this;
//       }
      pos = pos->_previous_cell;
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
      return *pos;
    }
    
  inline Cell* operator->() const
    {
      return pos;
    }

private:
  Tds*  _tds;
  Cell* pos;

};

template < class Tds>
class Triangulation_ds_vertex_iterator_3
{
// traverses the list of cells and report for each cell 
// the vertices whose cell() is the current cell

public:
  typedef typename Tds::Vertex       value_type;
  typedef typename Tds::Vertex *     pointer;
  typedef typename Tds::Vertex &     reference;
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;

  typedef typename Tds::Vertex Vertex;
  typedef typename Tds::Cell  Cell;
  typedef Triangulation_ds_vertex_iterator_3<Tds> Vertex_iterator;
  
  Triangulation_ds_vertex_iterator_3()
    : _tds(NULL), pos(NULL), index(0)
    {}
  
  Triangulation_ds_vertex_iterator_3(Tds * tds)
    : _tds(tds), index(0)
    {
      //      if ( _tds->number_of_vertices() == 0 ) { pos = NULL; }
      if ( _tds->number_of_vertices() == 0 ) { 
	pos = _tds->past_end_cell(); 
      }
      else { 
	pos = _tds->list_of_cells()._next_cell; 
	while ( (pos != _tds->past_end_cell())
		  && (pos->vertex(index)->cell() != pos) ) {
	  increment();
	}
      }
    }
  
  // used to initialize the past-the end iterator
  Triangulation_ds_vertex_iterator_3(Tds* tds, int)
    : _tds(tds), index(0)
    {
      //      if ( _tds->number_of_vertices() == 0 ) { pos = NULL; }
      //      else { pos = tds->past_end_cell() ; }
      pos = tds->past_end_cell() ;
    }
  
  Vertex_iterator&
  operator++()
  {
    //    if (_tds->number_of_vertices() == 0){ return *this;} should
    //    not be accessed  
    do {
      increment();
    } while ( (pos != _tds->past_end_cell())
	      && (pos->vertex(index)->cell() != pos) );
    return *this;
  }
    
  Vertex_iterator&
  operator--()
  {
    // if (_tds->number_of_vertices() == 0) { return *this;} should
    // not be accessed 
    do{
      if (index == 0){
	// all the vertices of the current cell have been examined
	int d = _tds->dimension();
	if ( d >= 0 ) {index = d;}
	else {index = 0;}
	pos = pos->_previous_cell;
      }
      else { index--; }
    } while ( (pos != _tds->past_end_cell())
	      && (pos->vertex(index)->cell() != pos) );
    return *this;
  }
    
  Vertex_iterator operator++(int)
    {
      Vertex_iterator tmp(*this);
      ++(*this);
      return tmp;
    }
    
  Vertex_iterator operator--(int)
    {
      Vertex_iterator tmp(*this);
      --(*this);
      return tmp;
    }
    
  bool operator==(const Vertex_iterator& fi) const
    {
      return ( (_tds == fi._tds) && (pos == fi.pos) && (index == fi.index) );
    }
    
  bool operator!=(const Vertex_iterator& fi) const
    {
      return !(*this == fi);
    }
    
  inline Vertex & operator*() const
    {
      // case pos == NULL should not be accessed, there is no vertex
      return *(pos->vertex(index));
    }
    
  inline Vertex* operator->() const
    {
      // case pos == NULL should not be accessed, there is no vertex
      return pos->vertex(index);
    }

private:
  Tds*  _tds;
  Cell* pos; // current "cell". Even if the dimension is <3 when 
              // there is no true cell yet.
  int index; // index of the current vertex in the current cell

  void 
  increment()
  {
    if (index >= _tds->dimension()) {
      // all the vertices of the current cell have been examined
      index = 0;
      pos = pos->_next_cell;
    }
    // be careful : index should always be 0 when pos = past_end_cell
    else { index++; }
  }

};

template < class Tds>
class Triangulation_ds_facet_iterator_3
{
// traverses the list of cells and report for each cell 
// the vertices whose cell() is the current cell

public:
  typedef typename Tds::Facet       value_type;
  typedef typename Tds::Facet *     pointer;
  typedef typename Tds::Facet &     reference;
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;

  typedef typename Tds::Cell Cell;
  typedef typename Tds::Facet Facet;
  typedef Triangulation_ds_facet_iterator_3<Tds> Facet_iterator;
  
  Triangulation_ds_facet_iterator_3()
    : _tds(NULL), pos(NULL), index(0)
    {}
  
  Triangulation_ds_facet_iterator_3(Tds * tds)
    : _tds(tds), index(0)
    {
      switch ( _tds->dimension() ) {
      case 2:
	pos = tds->list_of_cells()._next_cell; 
	index = 3;
	return;
      case 3:
	pos = tds->list_of_cells()._next_cell; 
	while ( // useless (pos != _tds->past_end_cell()) &&
	       // there must be at least one facet
	       ( pos->neighbor(index) < pos ) ) {
	  increment();
	}
	return;
      default:
	// pos = NULL;
	pos = tds->past_end_cell() ;
	return;
      }
    }
  
  // used to initialize the past-the end iterator
  Triangulation_ds_facet_iterator_3(Tds* tds, int)
    : _tds(tds), index(0)
    {
      //      if ( _tds->dimension() < 2 ) { pos = NULL; }
      //      else { 
	pos = tds->past_end_cell() ; 
	if  ( _tds->dimension() == 2 ) { index = 3; }
	//      }
    }
  
  Facet_iterator&
  operator++()
  {
    if (_tds->dimension() < 2){ return *this;} 

    if ( _tds->dimension() == 3 ) {
      do {
	increment();
      } while ( (pos != _tds->past_end_cell())
		&& ( (pos->neighbor(index)) < pos ) );
      // reports a facet when the current cell has a pointer inferior
      // to the pointer of the neighbor cell
    return *this;
    }

    pos = pos->_next_cell; // dimension 2
    return *this;
  }
    
  Facet_iterator&
  operator--()
  {
    if (_tds->dimension() < 2) { return *this;} 
    
    if ( _tds->dimension() == 2 ) {
      pos = pos->_previous_cell; // index remains 3
     return *this;
    }

    // dimension 3
    do{
      if (index == 0){
	// all the facets of the current cell have been examined
	index = 3;
	pos = pos->_previous_cell;
      }
      else { index--; }
    } while ( (pos != _tds->past_end_cell())
	      && (pos->neighbor(index) < pos ) );
    // reports a facet when the current cell has a pointer inferior
    // to the pointer of the neighbor cell
    return *this;
  }
    
  Facet_iterator operator++(int)
    {
      Facet_iterator tmp(*this);
      ++(*this);
      return tmp;
    }
    
  Facet_iterator operator--(int)
    {
      Facet_iterator tmp(*this);
      --(*this);
      return tmp;
    }
    
  bool operator==(const Facet_iterator& fi) const
    {
      return ( (_tds == fi._tds) && (pos == fi.pos) && (index == fi.index) );
    }
    
  bool operator!=(const Facet_iterator& fi) const
    {
      return !(*this == fi);
    }
    
  Facet operator*() const
    {
      // case pos == NULL should not be accessed, there is no facet
      // when dimension <2 
      return std::make_pair(pos, index);
    }
    
private:
  Tds*  _tds;
  Cell* pos; // current "cell". Even if the dimension is <3 when 
              // there is no true cell yet.
  int index; // index of the current facet in the current cell

  void
  increment()
  {
//     if ( _tds->dimension() == 2 ) {
//       pos = pos->_next_cell; // index remains 3
//     }
//     else { // dimension 3
    if (index == 3) {
      // all the feces of the current cell have been examined
      index = 0;
      pos = pos->_next_cell;
    }
    // be careful : index should always be 0 when pos = past_end_cell
    else { index++; }
//    }
  }

};

template < class Tds>
class Triangulation_ds_edge_iterator_3
{
// traverses the list of cells and report for each cell 
// the vertices whose cell() is the current cell

public:
  typedef typename Tds::Edge       value_type;
  typedef typename Tds::Edge *     pointer;
  typedef typename Tds::Edge &     reference;
  typedef std::size_t     size_type;
  typedef std::ptrdiff_t  difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;

  typedef typename Tds::Cell Cell;
  typedef typename Tds::Edge Edge;
  typedef Triangulation_ds_edge_iterator_3<Tds> Edge_iterator;
  typedef Triangulation_ds_cell_circulator_3<Tds> Cell_circulator;
  
  Triangulation_ds_edge_iterator_3()
    : _tds(NULL), pos(NULL), b(0), e(1)
    {}
  
  Triangulation_ds_edge_iterator_3(Tds * tds)
    : _tds(tds), b(0), e(1)
    {
      switch ( _tds->dimension() ) {
      case 1:
	{
	  pos = tds->list_of_cells()._next_cell;
	  return;
	}
      case 2:
	{
	  pos = tds->list_of_cells()._next_cell; 
	  while ( // useless (pos != _tds->past_end_cell()) && 
		 // there must be at least one edge
		 ( pos->neighbor(3-b-e) < pos) ) {
	    increment2();
	  }
	  return;
	}
      case 3:
	{
	  pos = tds->list_of_cells()._next_cell;
	  bool notfound = true;
	  while ( // useless (pos != _tds->past_end_cell()) &&
		 // there must be at least one edge
		 notfound ) {
	    Cell_circulator ccir = _tds->incident_cells(pos,b,e);
	    do {
	      ++ccir;
	    } while ( &(*ccir) > pos ); 
	    // loop terminates since it stops at least when ccir = pos
	    if ( &(*ccir) == pos ) {// pos is the cell with minimum pointer
	      notfound = false;
	    }
	    else {
	      increment3();
	    }
	  }
	  return;
	}
      default:
	{
	  //	  pos = NULL;
	  pos = tds->past_end_cell() ; 
	  return;
	}
      }
    }
  
  // used to initialize the past-the end iterator
  Triangulation_ds_edge_iterator_3(Tds* tds, int)
    : _tds(tds), b(0), e(1)
    {
      //      if ( _tds->dimension() < 1 ) { pos = NULL; }
      //      else { 
	pos = tds->past_end_cell() ; 
	// always b == 0 and e == 1 for past-end-cell
	//      }
    }
  
  Edge_iterator&
  operator++()
  {
    switch ( _tds->dimension() ) {
    case 1:
      {
	pos = pos->_next_cell;
	break;
      }
    case 2:
      {
	do {
	  increment2();
	} while ( (pos != _tds->past_end_cell()) && 
		  ( pos->neighbor(3-b-e) < pos) );
	break;
      }
    case 3:
      {
	bool notfound = true;
	do {
	  increment3();
	  if (pos != _tds->past_end_cell()) {
	    Cell_circulator ccir = _tds->incident_cells(pos,b,e);
	    //	  cerr << "sommets pos" << endl ;
	    //	  pp_tds_cell(pos) ;
	    do {
	      ++ccir;
	      //	    cerr << "&*ccir " << &(*ccir) << " pos "
	      //	    << pos << endl; 
	      //	    cerr << "sommets ccir " << endl;
	      //	    pp_tds_cell(&(*ccir));
	    } while ( &(*ccir) > pos );
	    if ( &(*ccir) == pos ) {// pos is the cell with minimum pointer
	      notfound = false;
	    }
	  }
	  else {
	    b=0; e=1;
	  }
	} while ( (pos != _tds->past_end_cell()) &&
		  notfound );
	break;
      }
    default:
      {
	return *this;
      }
    }
    return *this;
  }
    
  Edge_iterator&
  operator--()
  {
    switch (  _tds->dimension() ) {
    case 1:
      {
	pos = pos->_previous_cell; // b, e remain 0, 1
	break;
      }
    case 2:
      {
	do {
	  if (b == 0) {
	    b = 2; e = 0;
	    pos = pos->_previous_cell;
	  }
	  else {
	    b--; 
	    e = b+1; // case b==2, e==0 forbids to write e--
	  }
	} while ( (pos != _tds->past_end_cell()) && 
		  ( pos->neighbor(3-b-e) < pos) );
	break;
      }
    case 3:
      {
	bool notfound = true;
	do {
	  if (b == 0) {
	    if (e == 1) {
	      // all the edges of the current cell have been examined
	      b = 2; e = 3;
	      pos = pos->_previous_cell;
	    }
	    else {
	      e--;
	    }
	  }
	  else {
	    if (e == b+1) {
	      b--;
	      e = 3;
	    }
	    else {
	      e--;
	    }
	  }
	  if (pos != _tds->past_end_cell()) {
	    Cell_circulator ccir = _tds->incident_cells(pos,b,e);
	    // 	while ( &(*ccir) > pos ) {
	    // 	  --ccir;
	    // 	}
	    do {
	      ++ccir;
	    } while ( &(*ccir) > pos );
	    if ( &(*ccir) == pos ) {// pos is the cell with minimum pointer
	      notfound = false;
	    }
	  }
	  else {
	    b=0; e=1;
	  }
	} while ( (pos != _tds->past_end_cell()) &&
		  notfound );
	break;
      }
    default :
      return *this;
    }
    // reports an edge when the current cell has a pointer inferior
    // to the pointer of the neighbor cell
    return *this;
  }
    
  Edge_iterator operator++(int)
    {
      Edge_iterator tmp(*this);
      ++(*this);
      return tmp;
    }
    
  Edge_iterator operator--(int)
    {
      Edge_iterator tmp(*this);
      --(*this);
      return tmp;
    }
    
  bool operator==(const Edge_iterator& ei) const
    {
      return ( (_tds == ei._tds) && (pos == ei.pos) 
	       && (b == ei.b) && (e == ei.e) );
    }
    
  bool operator!=(const Edge_iterator& ei) const
    {
      return !(*this == ei);
    }
    
  Edge operator*() const
    {
      // case pos == NULL should not be accessed, there is no edge
      // when dimension <2 
      return make_triple(pos, b, e);
    }
    
private:
  Tds*  _tds;
  Cell* pos; // current "cell". Even if the dimension is <3 when 
              // there is no true cell yet.
  int b; // index of the first endpoint of the current edge in the current cell
  int e; // index of the second endpoint of the current edge in the
  // current cell 

  void
  increment2()
  {
//     switch ( _tds->dimension() ) {
//     case 1:
//       pos = pos->_next_cell; // b, e remain 0, 1
//     case 2: { 
    if (b == 2) { // e == 0
      // all the edges of the current cell have been examined
      b = 0; e = 1;
      pos = pos->_next_cell;
    }
    // be careful : index should always be 0 when pos = past_end_cell
    else { 
      b++; 
      if ( b == 2 ) {
	e = 0;
      }
      else { // b==1
	e = 2;
      }
    }
//    }
  }

  void
  increment3()
  {
//    case 3: { 
    if (b == 2) { // then e == 3
      // all the edges of the current cell have been examined
      b = 0; e = 1;
      pos = pos->_next_cell;
    }
    else {
      if (e == 3) {
	b++;
	e = b+1;
      }
      else {
	e++;
      }
    }
//    }
//    }
  }

};

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_DS_ITERATORS_3_H
