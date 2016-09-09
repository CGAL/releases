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
// file          : include/CGAL/Triangulation_ds_circulators_2.h
// package       : Triangulation (2.10)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_ds_circulators_2.h,v $
// revision      : $Revision: 1.3.1.12 $
// revision_date : $Date: 1998/12/14 09:41:55 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_DS_CIRCULATORS_2_H
#define CGAL_TRIANGULATION_DS_CIRCULATORS_2_H



#include <pair.h>
#include <iterator.h>
#include <CGAL/circulator.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>

template < class Vertex, class Face >
class CGAL_Triangulation_ds_face_circulator_2
    : public CGAL_Bidirectional_circulator_base<Face,ptrdiff_t,size_t>,
      public CGAL_Triangulation_cw_ccw_2
{
public:
  
  typedef CGAL_Triangulation_ds_face_circulator_2<Vertex,Face> Face_circulator;


  CGAL_Triangulation_ds_face_circulator_2()
    : _v(NULL), pos(NULL)
  {}
        
  CGAL_Triangulation_ds_face_circulator_2(Vertex* v)
    :  _v(v), pos(v->face())
  {}

  CGAL_Triangulation_ds_face_circulator_2(Vertex* v,   Face* f)
          : _v(v), pos(f)
  {}
        
        
  CGAL_Triangulation_ds_face_circulator_2(const Face_circulator &fc)
    : _v(fc._v), pos(fc.pos)
  {}
        
   
  Face_circulator& operator++()
  {
    CGAL_triangulation_precondition( (pos != NULL) && (_v != NULL) );
    int i = pos->index(_v);
    pos = pos->neighbor(ccw(i));
    if(pos == NULL){
      pos = _v->face();
    }
    return *this;
  }
        
  Face_circulator operator++(int)
  {
    CGAL_triangulation_precondition( (pos  != NULL) && (_v != NULL) );
    Face_circulator tmp(*this);
    ++(*this);
    return tmp;
  }
        
  Face_circulator& operator--()
  {
    CGAL_triangulation_precondition( (pos != NULL) && (_v != NULL) );
    int i = pos->index(_v);
    Face* f = pos->neighbor(cw(i));
    if(f == NULL) {
      Face* n;
      do{
	i = pos->index(_v);
	//	n = pos->neighbor(cw(i));
	n = pos->neighbor(ccw(i));
	if(n != NULL){
	  pos = n;
	}
      }while(n != NULL);
    }
    else{
      pos = f;
    }
    return *this;
  }
        
        
  Face_circulator operator--(int)
  {
    CGAL_triangulation_precondition( (pos != NULL) && (_v != NULL) );
    Face_circulator tmp(*this);
    --(*this);
    return tmp;
  }

  inline Face& operator*() const
  {
    return *pos;
  }

  inline Face* operator->() const
  {
    return pos;
  }
  
  bool operator==(const Face_circulator &fc) const
  {
    return (_v == fc._v) &&  (pos == fc.pos);
  }
        
        
  bool operator!=(const Face_circulator &fc) const
  {
    return ! (*this == fc);
  }
   
  bool is_empty() const
  {
    return ((_v == NULL) || (pos == NULL));
  }

  bool
  operator==(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return (_v == NULL || pos == NULL);
  }
        
  bool
  operator!=(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return ! (*this == NULL);
  }
        
private:
  Vertex* _v;
  Face* pos;

};


template < class Vertex, class Face >
class CGAL_Triangulation_ds_vertex_circulator_2 :
    public
CGAL_Bidirectional_circulator_base<Vertex,ptrdiff_t,size_t>,
  public  CGAL_Triangulation_cw_ccw_2
{
public:
  
  typedef CGAL_Triangulation_ds_vertex_circulator_2<Vertex, Face> 
                                          Vertex_circulator;
    
  
  CGAL_Triangulation_ds_vertex_circulator_2()
    :  _v(NULL), _f(NULL)
  {}
                
  CGAL_Triangulation_ds_vertex_circulator_2( Vertex* v,  Face* f)
    : _v( v ), _f(f)
  {
    if( _f != NULL ) {
      int i = _f->index( _v );
      _ri = ccw(i);
    }
  }
        
  CGAL_Triangulation_ds_vertex_circulator_2(Vertex* v)
				      
    : _v( v ), _f(v->face())
  {
    if( _f != NULL ) {
      int i = _f->index( _v );
      _ri = ccw(i);
    }
  }

  CGAL_Triangulation_ds_vertex_circulator_2(const Vertex_circulator &vc)
    : _ri(vc._ri), _v(vc._v), _f(vc._f)
  {}
        
              
  Vertex_circulator &operator=(const Vertex_circulator &vc)
  {
    _v = vc._v;
    _ri = vc._ri;
    _f = vc._f;
    return *this;
  }   

  inline Vertex& operator*() const
  {
    return *(_f->vertex(_ri));
  }

  inline Vertex* operator->() const
  {
    return _f->vertex(_ri);
  }

  Vertex_circulator& operator++()
  {
    Face* n = _f;
    int i = _f->index(_v);
    n = _f->neighbor(ccw(i));
    if(n == NULL){
      if(_ri == (int)ccw(i)){
	_ri = cw(i);
      } else {
	_f = _v->face();
	i = _f->index(_v);
	_ri = ccw(i);
      }
    } 
    else {
      _f = n;
      i = _f->index(_v);
      _ri = ccw(i);
    }
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
    Face* n = _f;
    int i = _f->index(_v);
    n = _f->neighbor(cw(i));
    if(n == NULL) {
      do{
	n = _f->neighbor(ccw(i));
	if(n != NULL){
	  _f = n;
	  i = _f->index(_v);
	}
      }while(n != NULL);
      i = _f->index(_v);
      _ri = cw(i);
    } 
    else {
      if(_ri == (int) cw(i)){
	_ri = ccw(i);
      } 
      else {
	_f = n;
	i = _f->index(_v);
	_ri = ccw(i);
      }
    }
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
    return (_v == vc._v) &&  (_ri == vc._ri) && (_f == vc._f);
  }
               
  bool operator!=(const Vertex_circulator &vc) const
  {
    return ! (*this == vc);
  }
               
  bool is_empty() const
  {
    return ((_v == NULL) || (_f == NULL));
  }


 bool operator==(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return (_v == NULL) || (_f == NULL);
  }
        
        
  bool operator!=(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return !(*this == NULL);
  }
        
private:
  int  _ri;
  Vertex* _v;
  Face* _f;
        
};



template < class Vertex, class Face >
class CGAL_Triangulation_ds_edge_circulator_2 :
  public
CGAL_Bidirectional_circulator_base<pair<Face*,int>,ptrdiff_t,size_t>,
public CGAL_Triangulation_cw_ccw_2
{
public:
  typedef CGAL_Triangulation_ds_edge_circulator_2<Vertex,Face> Edge_circulator;
  typedef pair<Face*, int>         Edge;

  CGAL_Triangulation_ds_edge_circulator_2()
    : _v(NULL), _f(NULL)
  {}
            
   CGAL_Triangulation_ds_edge_circulator_2( Vertex* v)
				       
    : _v(v), _f(v->face())
  {
    if( _f != NULL ){
      int i = _f->index(_v);
      _ri = ccw(i);
    }
  }

  CGAL_Triangulation_ds_edge_circulator_2( Vertex* v, Face* f)
    : _v(v), _f(f)
  {
    if( _f != NULL ){
      int i = _f->index(_v);
      _ri = ccw(i);
    }
  }
        
  CGAL_Triangulation_ds_edge_circulator_2(const Edge_circulator &vc)
    : _ri(vc._ri), _v(vc._v), _f(vc._f)
  {}
        
  Edge_circulator &operator=(const Edge_circulator &vc)
  {
    _v = vc._v;
    _ri = vc._ri;
    _f = vc._f;
    return *this;
  }

  Edge
  operator*() const
  {
    if( _f == NULL) {
      return make_pair(_f, 0);
    }
     return make_pair(_f, _ri);
  }
        
  Edge_circulator& operator++()
  {
    Face* n = _f;
    int i = _f->index(_v);
    n = _f->neighbor(ccw(i));
    if(n == NULL){
      if(_ri == (int) ccw(i)){
	_ri = cw(i);
      } 
      else {
	_f = _v->face();
	i = _f->index(_v);
	_ri = ccw(i);
      }
    } 
    else {
      _f = n;
      i = _f->index(_v);
      _ri = ccw(i);
    }
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
    Face* n = _f;
    int i = _f->index(_v);
    n = _f->neighbor(cw(i));
    if(n == NULL){
      do{
	n = _f->neighbor(ccw(i));
	if(n != NULL){
	  _f = n;
	  i = _f->index(_v);
	}
      }while(n != NULL);
      i = _f->index(_v);
      _ri = cw(i);
    } else {
      if(_ri == cw(i)){
	_ri = ccw(i);
      } else {
	_f = n;
	i = _f->index(_v);
	_ri = ccw(i);
      }
    }
    return *this;
  }
        
  Edge_circulator operator--(int)
  {
    Edge_circulator tmp(*this);
    --(*this);
    return tmp;
  }
        
   bool operator==(const Edge_circulator &vc) const
  {
    return (_v == vc._v) &&  (_ri == vc._ri) && (_f == vc._f);
  }
                
  bool operator!=(const Edge_circulator &vc) const
  {
    return ! (*this == vc);
  }

   bool is_empty() const
  {
    return ((_v == NULL) || (_f == NULL));
  }

bool operator==(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return (_v == NULL) || (_f == NULL);
  }
               
  bool operator!=(CGAL_NULL_TYPE n) const
  {
    CGAL_triangulation_assertion( n == NULL);
    return !(*this == NULL);
  }
     
private:
  int _ri;
  Vertex* _v;
  Face* _f;
        
};
        

#endif //CGAL_TRIANGULATION_DS_CIRCULATORS_2_H
