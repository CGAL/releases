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
// file          : include/CGAL/Triangulation_dsul_face_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Triangulation_dsul_face_2.h,v $
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2000/08/21 12:26:53 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_DSUL_FACE_2_H
#define CGAL_TRIANGULATION_DSUL_FACE_2_H

#include <CGAL/Triangulation_short_names_2.h>

CGAL_BEGIN_NAMESPACE 

template <class Vb, class Fb >
class  Triangulation_dsul_vertex_2 ;


template < class Vb, class Fb >
class  Triangulation_dsul_face_2
  : public Fb
{
public:
  typedef Vb Vertex_base;
  typedef Fb Face_base;
  typedef Triangulation_dsul_vertex_2<Vertex_base,Face_base> Vertex;
  typedef Triangulation_dsul_face_2<Vertex_base,Face_base> Face;

private:
  Face* _previous;
  Face* _next;

public :
  // creators
  Triangulation_dsul_face_2()
    : Face_base(), _previous(this), _next(this)
  {}
    
  Triangulation_dsul_face_2(Vertex* v0, Vertex* v1, Vertex* v2)
    :  Face_base(v0,v1,v2)
  {}
    
  Triangulation_dsul_face_2(Vertex* v0, Vertex* v1, Vertex* v2,
			  Face* n0, Face* n1, Face* n2)
    :  Face_base(v0,v1,v2,n0,n1,n2)
  {}

  Triangulation_dsul_face_2( const Face & f)
    : Face_base(f)
    {}

  //setting
  void set_vertex(int i, Vertex* v) { Face_base::set_vertex(i,v);}
  void set_neighbor(int i, Face* n) { Face_base::set_neighbor(i,n);}
  void set_vertices() { Face_base::set_vertices();}
  void set_neighbors() { Face_base::set_neighbors();}
  void set_vertices(Vertex* v0, Vertex* v1, Vertex* v2);
  void set_neighbors(Face* n0, Face* n1, Face* n2);
  //void reorient();  inherited from Face_base
 
  //Vertex Access Member Functions
  Vertex* vertex(int i) const;
  Vertex* mirror_vertex(int i) const;
  bool has_vertex(const Vertex* v) const;
  bool has_vertex(const Vertex* v, int& i) const;
  int index(const Vertex* v) const;

  // Neighbors Access Functions
  Face* neighbor(int i) const;
  bool has_neighbor(const Face* n) const;
  bool has_neighbor(const Face* n, int& i) const;
  int index(const Face* n) const;
  int mirror_index(int i) const;

  //Miscelleanous
  bool is_valid(bool verbose = false, int level = 0) const;

  //Handling the list of faces
  Face* previous() const {return _previous;}
  Face* next() const {return _next;}
  void  set_previous(Face* f) {_previous = f;};
  void  set_next(Face* f) {_next = f;};
};



template < class Vb, class Fb >
inline void 
Triangulation_dsul_face_2<Vb,Fb>::
set_vertices(Vertex* v0, Vertex* v1, Vertex* v2)
{
  Face_base::set_vertices(v0,v1,v2);
}

template < class Vb, class Fb >
inline void 
Triangulation_dsul_face_2<Vb,Fb>::
set_neighbors(Face* n0, Face* n1, Face* n2)
{
  Face_base::set_neighbors(n0,n1,n2);
}

template < class Vb, class Fb >
inline
Triangulation_dsul_vertex_2<Vb,Fb> *
Triangulation_dsul_face_2<Vb,Fb>::
vertex(int i) const
{
  return( (Vertex*) (Face_base::vertex(i)));
} 

template < class Vb, class Fb >
inline
Triangulation_dsul_vertex_2<Vb,Fb> *
Triangulation_dsul_face_2<Vb,Fb>::
mirror_vertex(int i) const
{
  CGAL_triangulation_precondition ( neighbor(i) != NULL);
  return neighbor(i)->vertex(neighbor(i)->index(this));
}

template < class Vb, class Fb >
inline int
Triangulation_dsul_face_2<Vb,Fb>::
mirror_index(int i) const
{
  CGAL_triangulation_precondition (neighbor(i) != NULL);
  return neighbor(i)->index(this);
}

template < class Vb, class Fb >
inline  bool 
Triangulation_dsul_face_2<Vb,Fb>::
has_vertex(const Vertex* v) const
{
  return (Face_base::has_vertex(v));
}
    
template < class Vb, class Fb >
inline  bool 
Triangulation_dsul_face_2<Vb,Fb>::    
has_vertex(const Vertex* v, int& i) const
{
  return (Face_base::has_vertex(v,i));
}
    
template < class Vb, class Fb >
inline  int 
Triangulation_dsul_face_2<Vb,Fb>::  
index(const Vertex* v) const
{
  return(Face_base::vertex_index(v));
}

// Neighbors Access Functions
template < class Vb, class Fb >
inline   
Triangulation_dsul_face_2<Vb,Fb>* 
Triangulation_dsul_face_2<Vb,Fb>::  
neighbor(int i) const
{
  return ((Face*) Face_base::neighbor(i));
}
    
template < class Vb, class Fb >
inline  bool 
Triangulation_dsul_face_2<Vb,Fb>::  
has_neighbor(const Face* n) const
{
  return (Face_base::has_neighbor(n));
}
    
template < class Vb, class Fb >
inline  bool 
Triangulation_dsul_face_2<Vb,Fb>::      
has_neighbor(const Face* n, int& i) const
{
  return (Face_base::has_neighbor(n,i));
}
    
template < class Vb, class Fb >
inline  int 
Triangulation_dsul_face_2<Vb,Fb>::    
index(const Face* n) const
{
  return(Face_base::face_index(n));
}
    
//Miscelleanous
template < class Vb, class Fb >
bool
Triangulation_dsul_face_2<Vb,Fb>::  
is_valid(bool verbose, int level) const
{
  bool result = Face_base::is_valid(verbose, level);
  for(int i = 0; i <= dimension(); i++) {
    Face* n = neighbor(i);
    int in = n->index(this);
    result = result && ( this == n->neighbor(in) );
    switch(dimension()) {
    case 0 : 
      break;
    case 1 :
      result = result &&  in == 1-i;
      result = result && ( this->vertex(1-i) == n->vertex(1-in));
      break;
    case 2 :
      result = result && ( this->vertex(cw(i)) == n->vertex(ccw(in)))
	              && ( this->vertex(ccw(i)) == n->vertex(cw(in)));
      break;
    }
  }
  return result;
}


CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_DSUL_FACE_2_H
