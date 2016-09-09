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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Triangulation_iterators_2.h
// package       : Triangulation (2.10)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_iterators_2.h,v $
// revision      : $Revision: 1.2.1.5 $
// revision_date : $Date: 1998/12/09 10:41:34 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_ITERATORS_2_H
#define CGAL_TRIANGULATION_ITERATORS_2_H



#include <pair.h>
#include <iterator.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>
#include <CGAL/Triangulation_ds_iterators_2.h>

template < class Gt, class Tds >
class CGAL_Triangulation_face_2;

template < class Gt, class Tds >
class CGAL_Triangulation_vertex_2;

template < class Gt, class Tds>
class CGAL_Triangulation_face_iterator_2;

template < class Gt, class Tds>
class CGAL_Triangulation_vertex_iterator_2;

template < class Gt, class Tds>
class CGAL_Triangulation_edge_iterator_2;


template < class Gt, class Tds>
class CGAL_Triangulation_face_iterator_2
 : public
bidirectional_iterator<CGAL_Triangulation_face_2<Gt,Tds>,ptrdiff_t>,
  public CGAL_Triangulation_cw_ccw_2
{
public:
  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;
  typedef typename Tds::Face_iterator  Iterator_base;

  typedef CGAL_Triangulation_face_2<Gt,Tds> Face;
  typedef CGAL_Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef typename Vertex::Vertex_handle Vertex_handle;
  typedef typename Face::Face_handle Face_handle;
  typedef pair<Face_handle, int>     Edge;

  typedef CGAL_Triangulation_face_iterator_2<Gt,Tds>      Face_iterator;
  typedef CGAL_Triangulation_edge_iterator_2<Gt,Tds>      Edge_iterator;
  typedef CGAL_Triangulation_vertex_iterator_2<Gt,Tds>    Vertex_iterator;

  
  CGAL_Triangulation_face_iterator_2()
    : _ib()
  {}
        
  CGAL_Triangulation_face_iterator_2(CGAL_Triangulation_2<Gt,Tds> *tr)
            : _ib( &(tr->_tds))
  { }
        
  CGAL_Triangulation_face_iterator_2(CGAL_Triangulation_2<Gt,Tds> *tr, int i)
    : _ib( &(tr->_tds), i)
  { }
       
  CGAL_Triangulation_face_iterator_2(const Face_iterator& fi)
          : _ib(fi._ib)
  {}
        
        
   Face_iterator&
        operator=(const Face_iterator& fi)
  { 
    _ib = fi._ib;
    return *this;
  }
  
  bool
  operator==(const Face_iterator& fi) const
  {
    return ( _ib == fi._ib);
  }

  bool
  operator!=(const Face_iterator& fi)
  {
    return !(*this == fi);
  }

  Face_iterator&
  operator++()
  {
    ++_ib; 
    return *this;   
  }

  Face_iterator&
  operator--()
  {
    --_ib;
    return *this;   
  }

  Face_iterator
  operator++(int)
  {
    Face_iterator tmp(*this);
    ++(*this);
    return tmp;
  }
        
        
  Face_iterator
  operator--(int)
  {
    Face_iterator tmp(*this);
    --(*this);
    return tmp;
  }
        
  inline Face& operator*() const
  {
    return (Face &)(*_ib);
  }

  inline Face* operator->() const
  {
    return   (Face*)( & (*_ib));
  }
     
private:
  Iterator_base   _ib;
};


template < class Gt, class Tds>
class CGAL_Triangulation_vertex_iterator_2
 : public bidirectional_iterator<CGAL_Triangulation_vertex_2<Gt,
   Tds>,ptrdiff_t>,
   public CGAL_Triangulation_cw_ccw_2
{
public:
  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;
  typedef typename Tds::Vertex_iterator  Iterator_base;

  typedef CGAL_Triangulation_face_2<Gt,Tds> Face;
  typedef CGAL_Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef typename Vertex::Vertex_handle Vertex_handle;
  typedef typename Face::Face_handle Face_handle;
  typedef pair<Face_handle, int>     Edge;

  typedef CGAL_Triangulation_face_iterator_2<Gt,Tds>      Face_iterator;
  typedef CGAL_Triangulation_edge_iterator_2<Gt,Tds>      Edge_iterator;
  typedef CGAL_Triangulation_vertex_iterator_2<Gt,Tds>    Vertex_iterator;

 
  CGAL_Triangulation_vertex_iterator_2()
    : _ib()
  {}
        
  CGAL_Triangulation_vertex_iterator_2(CGAL_Triangulation_2<Gt,Tds> *tr)
            : _ib( &(tr->_tds))
  { }
        
  CGAL_Triangulation_vertex_iterator_2(CGAL_Triangulation_2<Gt,Tds> *tr, int i)
    : _ib( &(tr->_tds), i)
  { }
       
  CGAL_Triangulation_vertex_iterator_2(const Vertex_iterator& vi)
          : _ib(vi._ib)
  {}
        
        
   Vertex_iterator&
        operator=(const Vertex_iterator& vi)
  { 
    _ib = vi._ib;
    return *this;
  }
  
  bool
  operator==(const Vertex_iterator& vi) const
  {
    return ( _ib == vi._ib);
  }

  bool
  operator!=(const Vertex_iterator& vi)
  {
    return !(*this == vi);
  }

  Vertex_iterator&
  operator++()
  {
    ++_ib; 
    return *this;   
  }

  Vertex_iterator&
  operator--()
  {
    --_ib;
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
        
  inline Vertex& operator*() const
  {
    return (Vertex &)(*_ib);
  }

  inline Vertex* operator->() const
  {
    return   (Vertex*)( & (*_ib));
  }
     
private:
  Iterator_base   _ib;
};


template < class Gt, class Tds>
class CGAL_Triangulation_edge_iterator_2
 : public bidirectional_iterator<typename
CGAL_Triangulation_2<Gt,Tds>::Edge ,ptrdiff_t>,
  public CGAL_Triangulation_cw_ccw_2
{
public:
  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;
  typedef typename Tds::Edge_iterator  Iterator_base;

  typedef CGAL_Triangulation_face_2<Gt,Tds> Face;
  typedef CGAL_Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef typename Vertex::Vertex_handle Vertex_handle;
  typedef typename Face::Face_handle Face_handle;
  typedef pair<Face_handle, int>     Edge;

  typedef CGAL_Triangulation_face_iterator_2<Gt,Tds>      Face_iterator;
  typedef CGAL_Triangulation_edge_iterator_2<Gt,Tds>      Edge_iterator;
  typedef CGAL_Triangulation_vertex_iterator_2<Gt,Tds>    Vertex_iterator;

 

  CGAL_Triangulation_edge_iterator_2()
    : _ib()
  {}
        
  CGAL_Triangulation_edge_iterator_2(CGAL_Triangulation_2<Gt,Tds> *tr)
            : _ib( &(tr->_tds))
  { }
        
  CGAL_Triangulation_edge_iterator_2(CGAL_Triangulation_2<Gt,Tds> *tr, int i)
    : _ib( &(tr->_tds), i)
  { }
       
  CGAL_Triangulation_edge_iterator_2(const Edge_iterator& ei)
          : _ib(ei._ib)
  {}
        
        
   Edge_iterator&
        operator=(const Edge_iterator& ei)
  { 
    _ib = ei._ib;
    return *this;
  }
  
  bool
  operator==(const Edge_iterator& ei) const
  {
    return ( _ib == ei._ib);
  }

  bool
  operator!=(const Edge_iterator& ei)
  {
    return !(*this == ei);
  }

  Edge_iterator&
  operator++()
  {
    ++_ib; 
     return *this;   
  }

  Edge_iterator&
  operator--()
  {
    --_ib;
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
        
  inline Edge  operator*() const
  {
    Face_handle fh = (Face *)((*_ib).first);
    return make_pair( fh  , (*_ib).second );
  }

  
     
private:
  Iterator_base   _ib ;
};




#endif //CGAL_TRIANGULATION_ITERATORS_2_H
