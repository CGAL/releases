// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/Triangulation_ds_iterators_2.h
// package       : Triangulation_2 (7.32)
// source        : $RCSfile: Triangulation_ds_iterators_2.h,v $
// revision      : $Revision: 1.32 $
// revision_date : $Date: 2002/04/05 06:38:26 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_DS_ITERATORS_2_H
#define CGAL_TRIANGULATION_DS_ITERATORS_2_H

#include <iterator>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>


CGAL_BEGIN_NAMESPACE

// The  iterator_base visits all the full dimensional faces 
// of the Tds
// whatever may be the dimension of the Tds
// The following iterator visit the 2-faces

template<class Tds>
class Triangulation_ds_face_iterator_2
  : public Tds::Iterator_base
{
public:
  typedef typename Tds::Iterator_base           Base;
  typedef typename Tds::Face_handle             Face_handle;
  typedef Triangulation_ds_face_iterator_2<Tds> Face_iterator;

  Triangulation_ds_face_iterator_2() : Base() {}
   
  Triangulation_ds_face_iterator_2(const Tds * tds) 
    : Base(tds->face_container().begin())
    {}

  Triangulation_ds_face_iterator_2(const Tds* tds, int)
    : Base(tds->face_container().end())
    {}

  operator Face_handle() const {return (*this)->handle();}
};


template < class Tds>
class Triangulation_ds_vertex_iterator_2 
  : public Tds::Vertex_container::iterator
{
public:
  typedef typename Tds::Vertex_container::iterator Vertex_iterator_base;
  typedef typename Tds::Vertex_handle              Vertex_handle;
  typedef Triangulation_ds_vertex_iterator_2<Tds>  Vertex_iterator;
  
  Triangulation_ds_vertex_iterator_2() : Vertex_iterator_base() {}
    
  Triangulation_ds_vertex_iterator_2(const Tds* tds)
    : Vertex_iterator_base(tds->vertex_container().begin()) {}
   
  Triangulation_ds_vertex_iterator_2(const Tds* tds, int )
    : Vertex_iterator_base(tds->vertex_container().end()) {}
   
  operator Vertex_handle() const {return (*this)->handle();}
};


template <class Tds>
class Triangulation_ds_edge_iterator_2
{
public:
  typedef typename Tds::Edge           Edge;
  typedef typename Tds::Iterator_base  Iterator_base;
  typedef typename Tds::Face_handle    Face_handle();
    
  typedef Edge            value_type;
  typedef Edge*           pointer;
  typedef Edge&           reference;
  typedef std::size_t                            size_type;
  typedef std::ptrdiff_t                         difference_type;
  typedef std::bidirectional_iterator_tag        iterator_category;

  typedef Triangulation_ds_edge_iterator_2<Tds> Edge_iterator;
  
private:
const Tds* _tds;
Iterator_base pos;
mutable Edge edge;

public:
  Triangulation_ds_edge_iterator_2()  {}
  Triangulation_ds_edge_iterator_2(const Tds * tds);
  Triangulation_ds_edge_iterator_2(const Tds* tds, int );

  bool  operator==(const Edge_iterator& fi) const ;
  bool  operator!=(const Edge_iterator& fi) const {return !(*this== fi);}
  Edge_iterator&    operator++();
  Edge_iterator&    operator--();
  Edge_iterator    operator++(int);
  Edge_iterator    operator--(int);
  Edge*     operator->() const;
  Edge&     operator*() const ;

private: 
  void increment();
  void decrement();
  bool associated_edge();
};


// Edge iterator implementation

template<class Tds>
Triangulation_ds_edge_iterator_2<Tds> ::
Triangulation_ds_edge_iterator_2(const Tds * tds)
 :  _tds(tds) 
{
  edge.second = 0;
  if (_tds->dimension()<= 0) {
    pos = _tds->face_container().end();       // there is no edge
    return;
  }
  pos = _tds->face_container().begin();
  if (_tds->dimension() == 1) edge.second = 2;
    while ( pos != _tds->face_container().end()  
	  && !associated_edge() ) increment();
}

template<class Tds>
Triangulation_ds_edge_iterator_2<Tds> ::
Triangulation_ds_edge_iterator_2(const Tds * tds, int )
  : _tds(tds) 
{
  pos = tds->face_container().end();
  edge.second = 0;
  if (_tds->dimension() == 1) {edge.second = 2;}
}


template<class Tds>
inline
bool
Triangulation_ds_edge_iterator_2<Tds> ::
operator==(const Edge_iterator& fi) const
{
  return _tds == fi._tds  && pos == fi.pos  && edge.second == fi.edge.second;
}

template<class Tds>
inline
void
Triangulation_ds_edge_iterator_2<Tds> ::
increment()
{
  CGAL_triangulation_precondition(_tds->dimension() >= 1);
  if (_tds->dimension() == 1) ++pos;
  else  if (edge.second == 2) {edge.second =  0; ++pos;}
  else       edge.second += 1;
  return;
}

template<class Tds>
inline
void
Triangulation_ds_edge_iterator_2<Tds> ::
decrement()
{
  CGAL_triangulation_precondition(_tds->dimension() >= 1);
  if (_tds->dimension() == 1) --pos;
  else    if (edge.second == 0) { edge.second = 2; --pos;}
  else  edge.second -= 1;
  return;
}

template<class Tds>
inline
bool
Triangulation_ds_edge_iterator_2<Tds> ::
associated_edge()
{
  if (_tds->dimension() == 1) {return true;}
  return pos->handle() < pos->neighbor(edge.second);
}

template<class Tds>
inline
Triangulation_ds_edge_iterator_2<Tds>&
Triangulation_ds_edge_iterator_2<Tds> ::
operator++()
{
  //CGAL_triangulation_precondition(pos != Iterator_base() && 
  //			       pos != _tds->face_container().end());
  do     increment();
  while( pos != _tds->face_container().end() && !associated_edge());
  return *this;
}
    

template<class Tds>
inline
Triangulation_ds_edge_iterator_2<Tds>&
Triangulation_ds_edge_iterator_2<Tds> ::
operator--()
{
  // CGAL_triangulation_precondition(pos != Iterator_base() 
  //                          && *this != Edge_iterator(_tds));
  do      decrement();
  while ( !associated_edge() && *this != Edge_iterator(_tds) ); 
  return *this;
}

    
template<class Tds>
inline
Triangulation_ds_edge_iterator_2<Tds>
Triangulation_ds_edge_iterator_2<Tds> ::    
operator++(int)
{
  Edge_iterator tmp(*this);
  ++(*this);
  return tmp;
}
    
template<class Tds>
inline
Triangulation_ds_edge_iterator_2<Tds>
Triangulation_ds_edge_iterator_2<Tds> ::     
operator--(int)
{
  Edge_iterator tmp(*this);
  --(*this);
  return tmp;
}
    
template<class Tds>
inline
typename Triangulation_ds_edge_iterator_2<Tds>::Edge*
Triangulation_ds_edge_iterator_2<Tds> ::    
operator->() const
{
  edge.first = pos->handle();
  return &edge;
}

template<class Tds>
inline
typename Triangulation_ds_edge_iterator_2<Tds>::Edge&
Triangulation_ds_edge_iterator_2<Tds> ::    
operator*() const 
{
  edge.first = pos->handle();
  return edge;
}
CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_DS_ITERATORS_2_H

