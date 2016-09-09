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
// file          : include/CGAL/Triangulation_circulators_2.h
// package       : Triangulation (2.10)
// source        : $RCSfile: Triangulation_circulators_2.h,v $
// revision      : $Revision: 1.2.1.11 $
// revision_date : $Date: 1998/12/09 10:41:31 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_CIRCULATORS_2_H
#define CGAL_TRIANGULATION_CIRCULATORS_2_H

#include <pair.h>
#include <iterator.h>
#include <CGAL/circulator.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>
#include <CGAL/Triangulation_ds_circulators_2.h>

template <class Gt, class Tds >
class CGAL_Triangulation_2;

template <class Gt,  class Tds >
class CGAL_Triangulation_face_2;

template <class Gt,  class Tds >
class CGAL_Triangulation_vertex_2;

template < class Gt, class Tds >
class CGAL_Triangulation_face_circulator_2;

template < class Gt, class Tds >
class CGAL_Triangulation_vertex_circulator_2;

template < class Gt, class Tds >
class CGAL_Triangulation_edge_circulator_2;

template < class Gt, class Tds>
class CGAL_Triangulation_face_circulator_2
    : public 
    CGAL_Bidirectional_circulator_base<CGAL_Triangulation_face_2<Gt,Tds>,
					ptrdiff_t,size_t>,
      public CGAL_Triangulation_cw_ccw_2
{
public:
  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;
  typedef typename Tds::Face_circulator  Base_face_circulator;

  typedef CGAL_Triangulation_face_2<Gt,Tds> Face;
  typedef CGAL_Triangulation_vertex_2<Gt, Tds> Vertex;
  typedef CGAL_Triangulation_vertex_handle_2<Gt, Tds> Vertex_handle;
  typedef CGAL_Triangulation_face_handle_2<Gt, Tds>  Face_handle;
  typedef pair<Face_handle, int>     Edge;

  typedef CGAL_Triangulation_face_circulator_2<Gt,Tds>      Face_circulator;
  typedef CGAL_Triangulation_edge_circulator_2<Gt,Tds>      Edge_circulator;
  typedef CGAL_Triangulation_vertex_circulator_2<Gt,Tds>    Vertex_circulator;


  CGAL_Triangulation_face_circulator_2()
    : _bfc()
  {}

  CGAL_Triangulation_face_circulator_2(const Vertex_handle& v)
    : _bfc(&(*v))
  {}

  CGAL_Triangulation_face_circulator_2(const Vertex_handle& v,
				       const Face_handle& f)
    : _bfc( &(*v), &(*f))
  {}

 
   
   CGAL_Triangulation_face_circulator_2(const Face_circulator &fc)
    : _bfc(fc._bfc)
  {}
   
  CGAL_Triangulation_face_circulator_2 &operator=(const Face_circulator &fc)
  {
    _bfc = fc._bfc;
    return *this;
  }
  
  Face_circulator& operator++()
  {
    ++_bfc;
      return *this;
  }
        
  Face_circulator operator++(int)
  {
    Face_circulator tmp(*this);
    ++(*this);
    return tmp;
  }
        
  Face_circulator& operator--()
  {
    --_bfc;
    return *this;
  }
        
  Face_circulator operator--(int)
  {
    Face_circulator tmp(*this);
    --(*this);
    return tmp;
  }
  
  bool operator==(const Face_circulator &fc) const
  {
            return (_bfc == fc._bfc) ;
  }
        
        
  bool operator!=(const Face_circulator &fc) const
  {
            return ! (*this == fc);
  }
   
  bool is_empty() const
  {
    return( _bfc.is_empty());
  }


  bool  operator==(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return (_bfc == NULL);
  }
        
  bool
  operator!=(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return ! (*this == NULL);
  }

  
        
  inline Face& operator*() const
  {
    return (Face&  )(*_bfc);
  }

  inline Face* operator->() const
  {
    return   (Face*)( & (*_bfc));
  }
  
  
private:
  Base_face_circulator  _bfc;
};


template < class Gt, class Tds>
class CGAL_Triangulation_vertex_circulator_2
    : public CGAL_Bidirectional_circulator_base<
CGAL_Triangulation_vertex_2<Gt,Tds>,ptrdiff_t,size_t>,
  public CGAL_Triangulation_cw_ccw_2
{
public:
  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;
  typedef typename Tds::Vertex_circulator  Base_vertex_circulator;

  typedef CGAL_Triangulation_face_2<Gt,Tds> Face;
  typedef CGAL_Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef CGAL_Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  typedef CGAL_Triangulation_face_handle_2<Gt,Tds> Face_handle;
  typedef pair<Face_handle, int>     Edge;

  typedef CGAL_Triangulation_face_circulator_2<Gt,Tds>      Face_circulator;
  typedef CGAL_Triangulation_edge_circulator_2<Gt,Tds>      Edge_circulator;
  typedef CGAL_Triangulation_vertex_circulator_2<Gt,Tds>    Vertex_circulator;

 
  CGAL_Triangulation_vertex_circulator_2()
    : _bvc()
  {}

  CGAL_Triangulation_vertex_circulator_2(const Vertex_handle& v)
    : _bvc(&(*v))
  {}

  CGAL_Triangulation_vertex_circulator_2(const Vertex_handle& v,
				       const Face_handle& f)
    : _bvc( &(*v), &(*f))
  {}
   
   CGAL_Triangulation_vertex_circulator_2(const Vertex_circulator &vc)
    : _bvc(vc._bvc)
  {}
   
  CGAL_Triangulation_vertex_circulator_2 &
	operator=(const Vertex_circulator &vc)
  {
    _bvc = vc._bvc;
    return *this;
  }
  
  Vertex_circulator& operator++()
  {
    ++_bvc;
    return *this;
  }
        
  Vertex_circulator operator++(int)
  {
    Vertex_circulator tmp(*this);
    ++(*this);
    return tmp;
  }
        
  Vertex_circulator& operator--()
  {
    --_bvc;
    return *this;
  }
        
  Vertex_circulator operator--(int)
  {
    Vertex_circulator tmp(*this);
    --(*this);
    return tmp;
  }
  
  bool operator==(const Vertex_circulator &vc) const
  {
            return (_bvc == vc._bvc) ;
  }
        
        
  bool operator!=(const Vertex_circulator &vc) const
  {
            return ! (*this == vc);
  }
  
  bool is_empty() const
  {
    return( _bvc.is_empty());
  }


      
  bool  operator==(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return (_bvc == (CGAL_NULL_TYPE) NULL);
  }
        
  bool
  operator!=(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return ! (*this == (CGAL_NULL_TYPE) NULL);
  }
        
  inline Vertex& operator*() const
  {
    return (Vertex &)(*_bvc);
  }

  inline Vertex* operator->() const
  {
    return   (Vertex*)( & (*_bvc));
  }
  
  
private:
  Base_vertex_circulator  _bvc;
};


template < class Gt, class Tds>
class CGAL_Triangulation_edge_circulator_2
  : public 
   CGAL_Bidirectional_circulator_base< 
          typename CGAL_Triangulation_2<Gt,
	    Tds>::Edge,ptrdiff_t,size_t>,
    public CGAL_Triangulation_cw_ccw_2
{
public:
  typedef Tds Triangulation_data_structure;

  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;
  typedef typename Tds::Edge_circulator  Base_edge_circulator;

  typedef CGAL_Triangulation_face_2<Gt,Tds> Face;
  typedef CGAL_Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef CGAL_Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  typedef CGAL_Triangulation_face_handle_2<Gt,Tds> Face_handle;
  typedef pair<Face_handle, int>     Edge;

  typedef CGAL_Triangulation_face_circulator_2<Gt,Tds>      Face_circulator;
  typedef CGAL_Triangulation_edge_circulator_2<Gt,Tds>      Edge_circulator;
  typedef CGAL_Triangulation_vertex_circulator_2<Gt,Tds>    Vertex_circulator;

  
  CGAL_Triangulation_edge_circulator_2()
    : _bec()
  {}

  CGAL_Triangulation_edge_circulator_2(const Vertex_handle& v)
    : _bec(&(*v))
  {}

  CGAL_Triangulation_edge_circulator_2(const Vertex_handle& v,
				       const Face_handle& f)
    : _bec( &(*v), &(*f))
  {}
   
   CGAL_Triangulation_edge_circulator_2(const Edge_circulator &ec)
    : _bec(ec._bec)
  {}
   
  CGAL_Triangulation_edge_circulator_2 &operator=(const Edge_circulator &ec)
  {
    _bec = ec._bec;
    return *this;
  }
  
  Edge_circulator& operator++()
  {
    ++_bec;
    return *this;
  }
        
  Edge_circulator operator++(int)
  {
    Edge_circulator tmp(*this);
    ++(*this);
    return tmp;
  }
        
  Edge_circulator& operator--()
  {
    --_bec;
    return *this;
  }
        
  Edge_circulator operator--(int)
  {
    Edge_circulator tmp(*this);
    --(*this);
    return tmp;
  }
  
  bool operator==(const Edge_circulator &ec) const
  {
            return (_bec == ec._bec) ;
  }
        
        
  bool operator!=(const Edge_circulator &ec) const
  {
            return ! (*this == ec);
  }
        
   bool is_empty() const
  {
    return( _bec.is_empty());
  }

  bool  operator==(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return (_bec == NULL);
  }
        
  bool
  operator!=(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return ! (*this == NULL);
  }
        
  inline Edge operator*() const
  {
    Face_handle fh = (Face *) ((*_bec).first);
    return make_pair( fh  , (*_bec).second );
  }

    
private:
  Base_edge_circulator  _bec;
};


#endif //CGAL_TRIANGULATION_CIRCULATORS_2_H
