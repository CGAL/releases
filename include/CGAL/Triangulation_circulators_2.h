// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Triangulation_circulators_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Triangulation_circulators_2.h,v $
// revision      : $Revision: 1.12 $
// revision_date : $Date: 1999/08/17 12:27:12 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_CIRCULATORS_2_H
#define CGAL_TRIANGULATION_CIRCULATORS_2_H

#include <utility>
#include <iterator>
#include <CGAL/circulator.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>
#include <CGAL/Triangulation_ds_circulators_2.h>

CGAL_BEGIN_NAMESPACE 

template <class Gt, class Tds >
class Triangulation_2;

template <class Gt,  class Tds >
class Triangulation_face_2;

template <class Gt,  class Tds >
class Triangulation_vertex_2;

template < class Gt, class Tds >
class Triangulation_face_circulator_2;

template < class Gt, class Tds >
class Triangulation_vertex_circulator_2;

template < class Gt, class Tds >
class Triangulation_edge_circulator_2;

template < class Gt, class Tds>
class Triangulation_face_circulator_2
    : public 
    Bidirectional_circulator_base<Triangulation_face_2<Gt,Tds>,
				   CGAL_STD::ptrdiff_t,CGAL_STD::size_t>,
      public Triangulation_cw_ccw_2
{
public:
  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;
  typedef typename Tds::Face_circulator  Base_face_circulator;

  typedef Triangulation_face_2<Gt,Tds> Face;
  typedef Triangulation_vertex_2<Gt, Tds> Vertex;
  typedef Triangulation_vertex_handle_2<Gt, Tds> Vertex_handle;
  typedef Triangulation_face_handle_2<Gt, Tds>  Face_handle;
  typedef std::pair<Face_handle, int>     Edge;

  typedef Triangulation_face_circulator_2<Gt,Tds>      Face_circulator;
  typedef Triangulation_edge_circulator_2<Gt,Tds>      Edge_circulator;
  typedef Triangulation_vertex_circulator_2<Gt,Tds>    Vertex_circulator;

private:
  Base_face_circulator  _bfc;

public:
  Triangulation_face_circulator_2()     : _bfc()   {}

  Triangulation_face_circulator_2(Vertex_handle v,
				  Face_handle f= Face_handle()) 
    {
      if(f == Face_handle()) _bfc=Base_face_circulator(&(*v));
      else _bfc=Base_face_circulator(&(*v), &(*f));
    }
  
  Face_circulator& operator++()  {    ++_bfc;  return *this;}
  Face_circulator& operator--()  {    --_bfc;  return *this;}
  Face_circulator operator++(int);
  Face_circulator operator--(int);
  bool operator==(const Face_circulator &fc) const {return _bfc == fc._bfc;}
  bool operator!=(const Face_circulator &fc) const {return !(*this == fc);}
  bool is_empty() const {return( _bfc.is_empty());}
  bool  operator==(CGAL_NULL_TYPE n) const {return _bfc==n;}
  bool  operator!=(CGAL_NULL_TYPE n) const {return !(*this == n);}
  Face& operator*() const {return static_cast<Face&>(*_bfc);}
  Face* operator->() const {return  static_cast<Face*>(&(*_bfc));}
 
};


template < class Gt, class Tds>
class Triangulation_vertex_circulator_2
  : public Bidirectional_circulator_base<Triangulation_vertex_2<Gt,Tds>,
                                    CGAL_STD::ptrdiff_t,CGAL_STD::size_t>,
    public Triangulation_cw_ccw_2
{
public:
  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;
  typedef typename Tds::Vertex_circulator  Base_vertex_circulator;

  typedef Triangulation_face_2<Gt,Tds> Face;
  typedef Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  typedef Triangulation_face_handle_2<Gt,Tds> Face_handle;
 
  typedef Triangulation_vertex_circulator_2<Gt,Tds>    Vertex_circulator;

private:
  Base_vertex_circulator  _bvc;

public: 
  Triangulation_vertex_circulator_2()     : _bvc()   {}

  Triangulation_vertex_circulator_2(Vertex_handle v,
				    Face_handle f = Face_handle())
   {
    if(f == Face_handle()) _bvc=Base_vertex_circulator(&(*v));
    else _bvc=Base_vertex_circulator(&(*v), &(*f));
   }

  Vertex_circulator& operator++()  { ++_bvc; return *this; }
  Vertex_circulator& operator--()  { --_bvc; return *this; }      
  Vertex_circulator operator++(int);
  Vertex_circulator operator--(int);
  bool operator==(const Vertex_circulator &vc) const 
    {return (_bvc == vc._bvc);}
  bool operator!=(const Vertex_circulator &vc) const {return ! (*this == vc);}
  bool is_empty() const { return( _bvc.is_empty()); }
  bool  operator==(CGAL_NULL_TYPE n) const {return _bvc==n;}
  bool  operator!=(CGAL_NULL_TYPE n) const {return !(*this == n);}
  Vertex& operator*() const { return static_cast<Vertex&>(*_bvc);}
  Vertex* operator->() const { return static_cast<Vertex*>(&(*_bvc));}
};


template < class Gt, class Tds>
class Triangulation_edge_circulator_2
  : public 
   Bidirectional_circulator_base< 
          typename Triangulation_2<Gt, Tds>::Edge, 
           CGAL_STD::ptrdiff_t, CGAL_STD::size_t>,
    public Triangulation_cw_ccw_2
{
public:
  typedef Tds Triangulation_data_structure;

  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;
  typedef typename Tds::Edge_circulator  Base_edge_circulator;

  typedef Triangulation_face_2<Gt,Tds> Face;
  typedef Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  typedef Triangulation_face_handle_2<Gt,Tds> Face_handle;
  typedef std::pair<Face_handle, int>     Edge;

  typedef Triangulation_edge_circulator_2<Gt,Tds>      Edge_circulator;
    
private:
  Base_edge_circulator  _bec;

public:
  Triangulation_edge_circulator_2()    : _bec()   {}

  Triangulation_edge_circulator_2(Vertex_handle v,
				  Face_handle f=Face_handle()) 
    {
      if(f == Face_handle()) _bec=Base_edge_circulator(&(*v));
      else _bec=Base_edge_circulator(&(*v), &(*f));
    }
  
  Edge_circulator& operator++()  { ++_bec; return *this;  }
  Edge_circulator& operator--()  { --_bec; return *this;  }      
  Edge_circulator operator++(int);
  Edge_circulator operator--(int);
  bool operator==(const Edge_circulator &ec) const {return (_bec == ec._bec);}
  bool operator!=(const Edge_circulator &ec) const {return ! (*this == ec); }
  bool is_empty() const   { return( _bec.is_empty());  }
  bool  operator==(CGAL_NULL_TYPE n) const {return (_bec == n);}
  bool  operator!=(CGAL_NULL_TYPE n) const {return ! (*this == n);}
  Edge operator*() const ;
  
};

template < class Gt, class Tds>
inline
Triangulation_face_circulator_2<Gt,Tds> 
Triangulation_face_circulator_2<Gt,Tds>:: 
operator++(int)
{
  Face_circulator tmp(*this);
  ++(*this);
  return tmp;
}

template < class Gt, class Tds>
inline
Triangulation_face_circulator_2<Gt,Tds> 
Triangulation_face_circulator_2<Gt,Tds>:: 
operator--(int) 
{
  Face_circulator tmp(*this);
  --(*this);
  return tmp;
}

template < class Gt, class Tds>
inline
Triangulation_vertex_circulator_2<Gt,Tds> 
Triangulation_vertex_circulator_2<Gt,Tds>:: 
operator++(int)
{
  Vertex_circulator tmp(*this);
  ++(*this);
  return tmp;
}

template < class Gt, class Tds>
inline
Triangulation_vertex_circulator_2<Gt,Tds> 
Triangulation_vertex_circulator_2<Gt,Tds>:: 
operator--(int) 
{
  Vertex_circulator tmp(*this);
  --(*this);
  return tmp;
}  

template < class Gt, class Tds>
inline
Triangulation_edge_circulator_2<Gt,Tds> 
Triangulation_edge_circulator_2<Gt,Tds>:: 
operator++(int) 
{
  Edge_circulator tmp(*this);
  ++(*this);
  return tmp;
}

template < class Gt, class Tds>
inline
Triangulation_edge_circulator_2<Gt,Tds> 
Triangulation_edge_circulator_2<Gt,Tds>:: 
operator--(int)      
{
  Edge_circulator tmp(*this);
  --(*this);
  return tmp;
}

template < class Gt, class Tds>
inline
Triangulation_edge_circulator_2<Gt,Tds>::Edge
Triangulation_edge_circulator_2<Gt,Tds>::
operator*() const 
{
  Face_handle fh = static_cast<Face *>((*_bec).first);
  return std::make_pair( fh  , (*_bec).second );
}

CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_CIRCULATORS_2_H
