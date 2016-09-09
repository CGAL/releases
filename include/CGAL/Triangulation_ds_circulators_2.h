// Copyright (c) 1997  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Triangulation_2/include/CGAL/Triangulation_ds_circulators_2.h,v $
// $Revision: 1.30 $ $Date: 2003/10/29 15:20:07 $
// $Name: current_submission $
//
// Author(s)     : Mariette Yvinec
//                 Menelaos Karavelas <mkaravel@cse.nd.edu>

#ifndef CGAL_TRIANGULATION_DS_CIRCULATORS_2_H
#define CGAL_TRIANGULATION_DS_CIRCULATORS_2_H

#include <utility>
#include <iterator>
#include <CGAL/circulator.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>

CGAL_BEGIN_NAMESPACE

template < class Tds>
class Triangulation_ds_face_circulator_2
  : public Bidirectional_circulator_base< typename Tds::Face,
                                 CGAL_CLIB_STD::ptrdiff_t,
				 CGAL_CLIB_STD::size_t>,
    public Triangulation_cw_ccw_2
      
{
private:
  typedef
  Bidirectional_circulator_base< typename Tds::Face,
                                 CGAL_CLIB_STD::ptrdiff_t,
				 CGAL_CLIB_STD::size_t>  Base_circulator;

public:
  typedef Triangulation_ds_face_circulator_2<Tds> Face_circulator;
  typedef typename Tds::Face                      Face;
  typedef typename Tds::Vertex                    Vertex;
  typedef typename Tds::Face_handle               Face_handle;
  typedef typename Tds::Vertex_handle             Vertex_handle;


private: 
  Vertex_handle _v;
  Face_handle    pos;

public:
  Triangulation_ds_face_circulator_2()
    : _v(), pos()
  {}
  
  Triangulation_ds_face_circulator_2(Vertex_handle v, 
				     Face_handle f = Face_handle());

  // MK: added to satisfy the mips CC 7.40 compiler
  Face_circulator& operator=(const Face_circulator& other);

  Face_circulator& operator++();
  Face_circulator operator++(int);
  Face_circulator& operator--();
  Face_circulator operator--(int);

  bool operator==(const Face_circulator &fc) const;
  bool operator!=(const Face_circulator &fc) const;
#ifdef CGAL_T2_USE_ITERATOR_AS_HANDLE
  bool operator==(const Face_handle &fh) const { return pos == fh; }
  bool operator!=(const Face_handle &fh) const { return pos != fh; }
#endif

  bool is_empty() const;
  bool operator==(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const;
  bool operator!=(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const;

  Face&
  operator*() const
  {
    CGAL_triangulation_precondition(pos != NULL && _v != NULL);
    return *pos;
  }

  Face*
  operator->() const
  {
    CGAL_triangulation_precondition(pos != NULL && _v != NULL);
    return &*pos;
  }
  
  Face_handle base()  const {return pos;}
#ifdef CGAL_T2_USE_ITERATOR_AS_HANDLE   
  operator Face_handle()  const {return pos;}
#endif
};

#ifdef CGAL_T2_USE_ITERATOR_AS_HANDLE
template < class Tds_ >
bool
operator==(typename Tds_::Face_handle fh, Triangulation_ds_face_circulator_2<Tds_> fc)
{
  return (fc==fh);
}

template < class Tds_ >
bool
operator!=(typename Tds_::Face_handle fh, Triangulation_ds_face_circulator_2<Tds_> fc)
{
  return (fc!=fh);
}
#endif

template < class Tds >
class Triangulation_ds_vertex_circulator_2 :
  public Bidirectional_circulator_base< typename Tds::Vertex, 
                                       CGAL_CLIB_STD::ptrdiff_t,
                                       CGAL_CLIB_STD::size_t>,
  public  Triangulation_cw_ccw_2
{
public:
  typedef Triangulation_ds_vertex_circulator_2<Tds> Vertex_circulator;
  typedef typename Tds::Face                      Face;
  typedef typename Tds::Vertex                    Vertex;
  typedef typename Tds::Face_handle               Face_handle;
  typedef typename Tds::Vertex_handle             Vertex_handle; 

private:
  Vertex_handle _v;
  Face_handle   pos;
  int _ri;
  
public:
  Triangulation_ds_vertex_circulator_2()
    :  _v(), pos()
  {}
                
  Triangulation_ds_vertex_circulator_2(Vertex_handle v,
				       Face_handle f = NULL);
       
  Vertex_circulator& operator++();
  Vertex_circulator  operator++(int);
  Vertex_circulator& operator--();
  Vertex_circulator  operator--(int);
 
  bool operator==(const Vertex_circulator &vc) const;
  bool operator!=(const Vertex_circulator &vc) const;
#ifdef CGAL_T2_USE_ITERATOR_AS_HANDLE 
  bool operator==(const Vertex_handle &vh) const { return pos->vertex(_ri) == vh; }
  bool operator!=(const Vertex_handle &vh) const { return pos->vertex(_ri) != vh; }
#endif
  bool is_empty() const;
  bool operator==(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const;
  bool operator!=(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const;

  Vertex&
  operator*() const
  {
    CGAL_triangulation_precondition(pos != NULL && _v != NULL);
    return *(pos->vertex(_ri));
  }

  Vertex*
  operator->() const
  {
    CGAL_triangulation_precondition(pos != NULL && _v != NULL);
    return &*(pos->vertex(_ri));
  }

   Vertex_handle base() const {return pos->vertex(_ri);}
#ifdef CGAL_T2_USE_ITERATOR_AS_HANDLE
   operator Vertex_handle() const {return pos->vertex(_ri);}
#endif
};

#ifdef CGAL_T2_USE_ITERATOR_AS_HANDLE
template < class Tds_ >
inline
bool
operator==(typename Tds_::Vertex_handle vh, Triangulation_ds_vertex_circulator_2<Tds_> vc)
{
  return (vc==vh);
}

template < class Tds_ >
inline
bool
operator!=(typename Tds_::Vertex_handle vh, Triangulation_ds_vertex_circulator_2<Tds_> vc)
{
  return !(vc==vh);
}
#endif

template < class Tds >
class Triangulation_ds_edge_circulator_2 :
  public Bidirectional_circulator_base < typename Tds::Edge, 
                                         CGAL_CLIB_STD::ptrdiff_t,
					 CGAL_CLIB_STD::size_t>,
  public Triangulation_cw_ccw_2
{
public:
  typedef Triangulation_ds_edge_circulator_2<Tds>  Edge_circulator;
  typedef typename Tds::Face                       Face;
  typedef typename Tds::Vertex                     Vertex;
  typedef typename Tds::Edge                       Edge;
  typedef typename Tds::Face_handle                Face_handle;
  typedef typename Tds::Vertex_handle              Vertex_handle;

private:
  int _ri;
  Vertex_handle _v;
  Face_handle  pos;
  mutable Edge edge;

public:
  Triangulation_ds_edge_circulator_2()
    : _v(NULL), pos(NULL)
  {}
            
  Triangulation_ds_edge_circulator_2( Vertex_handle v, 
				      Face_handle f = NULL);

  Edge_circulator& operator++();
  Edge_circulator operator++(int);
  Edge_circulator& operator--();
  Edge_circulator operator--(int);
 
  bool operator==(const Edge_circulator &vc) const;
  bool operator!=(const Edge_circulator &vc) const;
  bool is_empty() const;
  bool operator==(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const;
  bool operator!=(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const;

  Edge*  operator->() const { 
    edge.first=pos;
    edge.second= _ri;
    return &edge;
  }

  Edge& operator*() const {
    edge.first=pos;
    edge.second= _ri;
    return edge;
  }

};


template < class Tds >
Triangulation_ds_face_circulator_2<Tds> ::
Triangulation_ds_face_circulator_2(Vertex_handle v, Face_handle f)
  : _v(v), pos(f)
{
  if (_v == NULL) pos = NULL;
  else if ( pos == NULL) pos = v->face();

  if (pos == NULL || pos->dimension() < 2) { 
    _v = NULL ; pos = NULL; return;}
  else CGAL_triangulation_precondition( pos->has_vertex(v));
}
 
template < class Tds >
Triangulation_ds_face_circulator_2<Tds>&
Triangulation_ds_face_circulator_2<Tds> ::
operator=(const Face_circulator& other)
{
   static_cast<Base_circulator &>(*this) =
    static_cast<const Base_circulator &> (other);
   _v = other._v;
  pos = other.pos;
  return *this;
} 
    
template < class Tds >
Triangulation_ds_face_circulator_2<Tds>&
Triangulation_ds_face_circulator_2<Tds> ::
operator++()
{
  CGAL_triangulation_precondition( (pos != NULL) && (_v != NULL) );
  int i = pos->index(_v);
  pos = pos->neighbor(ccw(i));
  return *this;
}

template < class Tds >
Triangulation_ds_face_circulator_2<Tds>
Triangulation_ds_face_circulator_2<Tds> ::
operator++(int)
{
  CGAL_triangulation_precondition(pos != NULL && _v != NULL);
  Face_circulator tmp(*this);
  ++(*this);
  return tmp;
}

template < class Tds >
Triangulation_ds_face_circulator_2<Tds>&
Triangulation_ds_face_circulator_2<Tds> ::
operator--()
{
   CGAL_triangulation_precondition(pos != NULL && _v != NULL);
   int i = pos->index(_v);
   pos = pos->neighbor(cw(i));
   return *this;
}

template < class Tds >
Triangulation_ds_face_circulator_2<Tds>
Triangulation_ds_face_circulator_2<Tds> ::
operator--(int)
{
  CGAL_triangulation_precondition(pos != NULL && _v != NULL);
  Face_circulator tmp(*this);
  --(*this);
  return tmp;
}

template < class Tds >
inline bool
Triangulation_ds_face_circulator_2<Tds> ::
operator==(const Face_circulator &fc) const
{    
  return (_v == fc._v) &&  (pos == fc.pos);  
}

template < class Tds >
inline bool
Triangulation_ds_face_circulator_2<Tds> ::
operator!=(const Face_circulator &fc) const
{    
return ! (*this == fc);  
}
   
template < class Tds >
inline bool
Triangulation_ds_face_circulator_2<Tds> ::
is_empty() const
{    
return ((_v == NULL) || (pos == NULL));  
}

template < class Tds >
inline bool
Triangulation_ds_face_circulator_2<Tds> ::
operator==(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const
{
  CGAL_triangulation_assertion( n == NULL);
  return (_v == NULL || pos == NULL);
}
        
template < class Tds >
inline bool
Triangulation_ds_face_circulator_2<Tds> ::
operator!=(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const
{
  CGAL_triangulation_assertion( n == NULL);
  return ! (*this == NULL);
}

template < class Tds >
Triangulation_ds_vertex_circulator_2<Tds> ::
Triangulation_ds_vertex_circulator_2 (Vertex_handle v,  
				      Face_handle f)
  : _v( v ), pos(f)
{
  if (_v == NULL) { pos = NULL;}
  else if (pos==NULL) {pos = v->face();}

  if (pos == NULL || pos->dimension() < 1){
    _v = NULL; pos = NULL;return;}
  int i = pos->index(_v);
  if (pos->dimension() == 2) {_ri = ccw(i);}
  else {_ri = 1-i;}
  return;
}


template < class Tds >
Triangulation_ds_vertex_circulator_2<Tds>&
Triangulation_ds_vertex_circulator_2<Tds> ::
operator++()
{
  CGAL_triangulation_precondition(pos != NULL && _v != NULL);
  int i = pos->index(_v);
    
  if (pos->dimension() == 1) { 
    pos = pos->neighbor(1-i);
    _ri = 1 - pos->index(_v);
  }
  else{
    pos = pos->neighbor(ccw(i));
    i = pos->index(_v);
    _ri = ccw(i);
  }
  return *this;
}
        
template < class Tds >
Triangulation_ds_vertex_circulator_2<Tds>
Triangulation_ds_vertex_circulator_2<Tds> ::
operator++(int)
{
  Vertex_circulator tmp(*this);
  ++(*this);
  return tmp;
}

template < class Tds >
Triangulation_ds_vertex_circulator_2<Tds>&
Triangulation_ds_vertex_circulator_2<Tds> ::
operator--()
{
  CGAL_triangulation_precondition(pos != NULL && _v != NULL);
  int i = pos->index(_v);
    
  if (pos->dimension() == 1) { 
    pos = pos->neighbor(1-i);
    _ri = 1 - pos->index(_v);
  }
  else{
    pos = pos->neighbor(cw(i));
    i = pos->index(_v);
    _ri = ccw(i);
  }
  return *this;
}
        
template < class Tds >
Triangulation_ds_vertex_circulator_2<Tds>
Triangulation_ds_vertex_circulator_2<Tds> ::     
operator--(int)
{
  Vertex_circulator tmp(*this);
  --(*this);
  return tmp;
}

template < class Tds >
inline bool
Triangulation_ds_vertex_circulator_2<Tds> ::
operator==(const Vertex_circulator &vc) const
{
  return (_v == vc._v) &&  (_ri == vc._ri) && (pos == vc.pos);
}
               
template < class Tds >
inline bool
Triangulation_ds_vertex_circulator_2<Tds> ::
operator!=(const Vertex_circulator &vc) const
{
  return ! (*this == vc);
}
               
template < class Tds >
inline bool
Triangulation_ds_vertex_circulator_2<Tds> ::
is_empty() const
{
  return (_v == NULL || pos == NULL);
}

template < class Tds >
inline bool
Triangulation_ds_vertex_circulator_2<Tds> ::
operator==(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const
{
  CGAL_triangulation_assertion( n == NULL);
  return (_v == NULL || pos == NULL);
}
        
template < class Tds >
inline bool
Triangulation_ds_vertex_circulator_2<Tds> ::        
operator!=(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const
{
  CGAL_triangulation_assertion( n == NULL);
  return !(*this == NULL);
}
        

template < class Tds >
Triangulation_ds_edge_circulator_2<Tds> ::
Triangulation_ds_edge_circulator_2(Vertex_handle v, Face_handle f)
    : _v(v), pos(f)
{
  if (_v == NULL) { pos = NULL;}
  else if (pos==NULL) {pos = v->face();}
 
  if (pos == NULL || pos->dimension() < 1){
    _v = NULL; pos = NULL;return;}
  int i = pos->index(_v);
  if (pos->dimension() == 2) {_ri = ccw(i);}
  else {_ri = 2;}
  return;
}

template < class Tds >
Triangulation_ds_edge_circulator_2<Tds>&
Triangulation_ds_edge_circulator_2<Tds> ::
operator++()
{
  CGAL_triangulation_precondition(pos != NULL && _v != NULL);
  int i = pos->index(_v);
  if (pos->dimension() == 1) { 
    pos = pos->neighbor(1-i);
    return *this;
  }
  else{
    pos = pos->neighbor(ccw(i));
    i = pos->index(_v);
    _ri = ccw(i);
  }    
  return *this;
}

template < class Tds >
Triangulation_ds_edge_circulator_2<Tds>
Triangulation_ds_edge_circulator_2<Tds> ::
operator++(int)
{
  Edge_circulator tmp(*this);
  ++(*this);
  return tmp;
}

template < class Tds >
Triangulation_ds_edge_circulator_2<Tds>&
Triangulation_ds_edge_circulator_2<Tds> ::
operator--()
{
  CGAL_triangulation_precondition(pos != NULL && _v != NULL);
  int i = pos->index(_v);

  if (pos->dimension() == 1) { 
    pos = pos->neighbor(1-i);
    return *this;
  }
  else{
    pos = pos->neighbor(cw(i));
    i = pos->index(_v);
    _ri = ccw(i);
  }    
  return *this;
}
   
template < class Tds >
Triangulation_ds_edge_circulator_2<Tds>
Triangulation_ds_edge_circulator_2<Tds> ::
operator--(int)
{
  Edge_circulator tmp(*this);
  --(*this);
  return tmp;
}

template < class Tds >
inline bool
Triangulation_ds_edge_circulator_2<Tds> ::
operator==(const Edge_circulator &vc) const
{
  return (_v == vc._v) &&  (_ri == vc._ri) && (pos == vc.pos);
}
                
template < class Tds >
inline bool
Triangulation_ds_edge_circulator_2<Tds> ::
operator!=(const Edge_circulator &vc) const
{
  return ! (*this == vc);
}

template < class Tds >
inline bool
Triangulation_ds_edge_circulator_2<Tds> ::
is_empty() const
{
  return (_v == NULL || pos == NULL);
}

template < class Tds >
inline bool
Triangulation_ds_edge_circulator_2<Tds> ::
operator==(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const
{
  CGAL_triangulation_assertion( n == NULL);
  return (_v == NULL || pos == NULL);
}
               
template < class Tds >
inline bool
Triangulation_ds_edge_circulator_2<Tds> ::
operator!=(CGAL_NULL_TYPE CGAL_triangulation_assertion_code(n)) const
{
  CGAL_triangulation_assertion( n == NULL);
  return !(*this == NULL);
}
       

CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_DS_CIRCULATORS_2_H
