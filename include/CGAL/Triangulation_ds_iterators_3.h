// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Triangulation_ds_iterators_3.h
// package       : Triangulation_3 (1.114)
// revision      : $Revision: 1.34 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_DS_ITERATORS_3_H
#define CGAL_TRIANGULATION_DS_ITERATORS_3_H

#include <utility>

#include <CGAL/Triangulation_short_names_3.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_ds_circulators_3.h>

CGAL_BEGIN_NAMESPACE

template <class Base, class Handle>
struct Triangulation_iterator_handle_adaptor_3
  : public Base
{
  Triangulation_iterator_handle_adaptor_3() : Base() {}
   
  Triangulation_iterator_handle_adaptor_3(const Base & b) 
    : Base(b) {}

  operator Handle() const {return (*this)->handle();}
};

template < class Tds >
class Triangulation_ds_facet_iterator_3
{
// traverses the list of cells and reports all facets.
public:

  typedef typename Tds::Facet                    value_type;
  typedef const typename Tds::Facet *            pointer;
  typedef const typename Tds::Facet &            reference;
  typedef std::size_t                            size_type;
  typedef std::ptrdiff_t                         difference_type;
  typedef std::bidirectional_iterator_tag        iterator_category;

  typedef typename Tds::Facet                    Facet;
  typedef Triangulation_ds_facet_iterator_3<Tds> Facet_iterator;
  typedef typename Tds::Cell_iterator            Cell_iterator;

  Triangulation_ds_facet_iterator_3()
    {}

  Triangulation_ds_facet_iterator_3(const Tds * tds)
    : _tds(tds)
    {
      facet.second = 0;
      switch ( _tds->dimension() ) {
      case 2:
	pos = _tds->cell_container().begin();
	facet.second = 3;
	return;
      case 3:
	pos = _tds->cell_container().begin();
	while (// there must be at least one facet
	       pos->neighbor(facet.second) < pos ) {
	  increment();
	}
	return;
      default:
	pos = _tds->cell_container().end();
	return;
      }
    }
  
  // used to initialize the past-the end iterator
  Triangulation_ds_facet_iterator_3(const Tds* tds, int)
    : _tds(tds)
    {
	facet.second = 0;
	pos = _tds->cell_container().end();
	if (_tds->dimension() == 2)
	    facet.second = 3;
    }
  
  Facet_iterator& operator++()
  {
    if (_tds->dimension() < 2)
	return *this;

    if (_tds->dimension() == 3) {
      do {
	increment();
      } while ( pos != _tds->cell_container().end()
	     && pos->neighbor(facet.second) < pos );
      // reports a facet when the current cell has a pointer inferior
      // to the pointer of the neighbor cell
      return *this;
    }

    ++pos; // dimension 2
    return *this;
  }
    
  Facet_iterator& operator--()
  {
    if (_tds->dimension() < 2)
	return *this;
    
    if ( _tds->dimension() == 2 ) {
      --pos; // index remains 3
      return *this;
    }

    // dimension 3
    do{
      if (facet.second == 0) {
	// all the facets of the current cell have been examined
	facet.second = 3;
	--pos;
      }
      else
	  --facet.second;
    } while ( pos != _tds->cell_container().end()
	   && pos->neighbor(facet.second) < pos );
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
      return _tds == fi._tds && pos == fi.pos &&
	     facet.second == fi.facet.second;
    }

  bool operator!=(const Facet_iterator& fi) const
    {
      return !(*this == fi);
    }

  reference operator*() const
    {
      facet.first = pos;
      return facet;
    }

  pointer operator->() const
    {
      facet.first = pos;
      return &facet;
    }

private:
  const Tds*  _tds;
  Cell_iterator pos; // current "cell".
  mutable Facet facet; // current facet.

  void increment()
  {
    if (facet.second == 3) {
      // all the faces of the current cell have been examined
      facet.second = 0;
      ++pos;
    }
    // be careful : facet.second should always be 0 when pos = cells_end
    else
	++facet.second;
  }
};

template < class Tds >
class Triangulation_ds_edge_iterator_3
{
// traverses the list of cells and reports each edge.
public:

  typedef typename Tds::Edge                      value_type;
  typedef const typename Tds::Edge *              pointer;
  typedef const typename Tds::Edge &              reference;
  typedef std::size_t                             size_type;
  typedef std::ptrdiff_t                          difference_type;
  typedef std::bidirectional_iterator_tag         iterator_category;

  typedef typename Tds::Edge                      Edge;
  typedef Triangulation_ds_edge_iterator_3<Tds>   Edge_iterator;
  typedef typename Tds::Cell_iterator             Cell_iterator;
  typedef typename Tds::Cell_handle               Cell_handle;
  typedef Triangulation_ds_cell_circulator_3<Tds> Cell_circulator;

  Triangulation_ds_edge_iterator_3()
    : _tds(NULL)
    {
      edge.second = 0;
      edge.third = 1;
    }
  
  Triangulation_ds_edge_iterator_3(const Tds * tds)
    : _tds(tds)
    {
      edge.second = 0;
      edge.third = 1;
      switch ( _tds->dimension() ) {
      case 1:
	{
	  pos = _tds->cell_container().begin();
	  return;
	}
      case 2:
	{
	  pos = _tds->cell_container().begin();
	  while ( // there must be at least one edge
		 pos->neighbor(3-edge.second-edge.third) < pos ) {
	    increment2();
	  }
	  return;
	}
      case 3:
	{
	  pos = _tds->cell_container().begin();
	  bool notfound = true;
	  while ( // there must be at least one edge
		 notfound ) {
	    edge.first = pos;
	    Cell_circulator ccir = _tds->incident_cells(edge);
	    do {
	      ++ccir;
	    } while ( pos->handle() < ccir->handle() ); 
	    // loop terminates since it stops at least when ccir = pos
	    if ( ccir->handle() == pos->handle() )
		// pos is the cell with minimal pointer
	      notfound = false;
	    else
	      increment3();
	  }
	  return;
	}
      default:
	{
	  pos = _tds->cell_container().end();
	  return;
	}
      }
    }
  
  // used to initialize the past-the end iterator
  Triangulation_ds_edge_iterator_3(const Tds* tds, int)
    : _tds(tds)
    {
	edge.second = 0;
	edge.third = 1;
	pos = _tds->cell_container().end();
    }
  
  Edge_iterator& operator++()
  {
    switch ( _tds->dimension() ) {
    case 1:
      {
	++pos;
	break;
      }
    case 2:
      {
	do {
	  increment2();
	} while ( pos != _tds->cell_container().end() && 
		  pos->neighbor(3-edge.second-edge.third) < pos );
	break;
      }
    case 3:
      {
	bool notfound = true;
	do {
	  increment3();
	  if (pos != _tds->cell_container().end()) {
	    edge.first = pos;
	    Cell_circulator ccir = _tds->incident_cells(edge);
	    do {
	      ++ccir;
	    } while ( pos->handle() < ccir->handle() );
	    if ( ccir->handle() == pos->handle() )
		// pos is the cell with minimal pointer
	      notfound = false;
	  }
	  else {
	    edge.second=0; edge.third=1;
	  }
	} while ( pos != _tds->cell_container().end() && notfound );
	break;
      }
    default:
      {
	return *this;
      }
    }
    return *this;
  }
    
  Edge_iterator& operator--()
  {
    switch ( _tds->dimension() ) {
    case 1:
      {
	--pos; // edge.second, edge.third remain 0, 1
	break;
      }
    case 2:
      {
	do {
	  if (edge.second == 0) {
	    edge.second = 2; edge.third = 0;
	    --pos;
	  }
	  else {
	    --edge.second;
	    edge.third = edge.second+1;
	    // case edge.second==2, edge.third==0 forbids to write edge.third--
	  }
	} while ( pos != _tds->cell_container().end() && 
		  pos->neighbor(3-edge.second-edge.third) < pos );
	break;
      }
    case 3:
      {
	bool notfound = true;
	do {
	  if (edge.second == 0) {
	    if (edge.third == 1) {
	      // all the edges of the current cell have been examined
	      edge.second = 2; edge.third = 3;
	      --pos;
	    }
	    else
	      --edge.third;
	  }
	  else {
	    if (edge.third == edge.second+1) {
	      --edge.second;
	      edge.third = 3;
	    }
	    else
	      --edge.third;
	  }
	  if (pos != _tds->cell_container().end()) {
	    edge.first = pos;
	    Cell_circulator ccir = _tds->incident_cells(edge);
	    do {
	      ++ccir;
	    } while ( pos->handle() < ccir->handle() );
	    if ( pos->handle() == ccir->handle() )
		// pos is the cell with minimum pointer
	      notfound = false;
	  }
	  else {
	    edge.second=0; edge.third=1;
	  }
	} while ( pos != _tds->cell_container().end() && notfound );
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
      return _tds == ei._tds && pos == ei.pos &&
	     edge.second == ei.edge.second && edge.third == ei.edge.third;
    }
    
  bool operator!=(const Edge_iterator& ei) const
    {
      return !(*this == ei);
    }

  reference operator*() const
    {
      edge.first = pos;
      return edge;
    }

  pointer operator->() const
    {
      edge.first = pos;
      return &edge;
    }

private:
  const Tds*  _tds;
  Cell_iterator pos; // current "cell". Even if the dimension is <3 when 
              // there is no true cell yet.
  mutable Edge edge;  // keeps the indices of the current edge.

  void increment2()
  {
    if (edge.second == 2) { // edge.third == 0
      // all the edges of the current cell have been examined
      edge.second = 0; edge.third = 1;
      ++pos;
    }
    // be careful : index should always be 0 when pos = cells_end
    else { 
      ++edge.second;
      if ( edge.second == 2 )
	edge.third = 0;
      else // edge.second==1
	edge.third = 2;
    }
  }

  void increment3()
  {
    if (edge.second == 2) { // then edge.third == 3
      // all the edges of the current cell have been examined
      edge.second = 0; edge.third = 1;
      ++pos;
    }
    else {
      if (edge.third == 3) {
	edge.second++;
	edge.third = edge.second+1;
      }
      else
	++edge.third;
    }
  }
};

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_DS_ITERATORS_3_H
