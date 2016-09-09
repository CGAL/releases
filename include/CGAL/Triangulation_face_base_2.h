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
// file          : include/CGAL/Triangulation_face_base_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Triangulation_face_base_2.h,v $
// revision      : $Revision: 1.15 $
// revision_date : $Date: 1999/09/27 17:31:31 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_FACE_BASE_2_H
#define CGAL_TRIANGULATION_FACE_BASE_2_H


#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>

CGAL_BEGIN_NAMESPACE 

template < class Gt >
class Triangulation_face_base_2 
  : public Triangulation_cw_ccw_2
{
public:
  typedef Triangulation_face_base_2  Face_base;

private:
  void* V[3];
  void* N[3];

public:
  Triangulation_face_base_2();
  Triangulation_face_base_2(void* v0, void* v1, void* v2);
  Triangulation_face_base_2(void* v0, void* v1, void* v2,
			    void* n0, void* n1, void* n2);

  void* vertex(int i) const;
  bool has_vertex(const void* v) const;
  bool has_vertex(const void* v, int& i) const ;
  int vertex_index(const void* v) const ;
 
  void* neighbor(int i) const ;
  bool has_neighbor(const void* n) const;
  bool has_neighbor(const void* n, int& i) const;
  int face_index(const void* n) const;

  void set_vertex(int i, void* v);
  void set_vertices();
  void set_vertices(void* v0, void* v1, void* v2);
  void set_neighbor(int i, void* n) ;
  void set_neighbors();
  void set_neighbors(void* n0, void* n1, void* n2);
  void reorient();
  void ccw_permute();
  void cw_permute();
  
  int dimension() const;
  //the following trivial is_valid to allow
  // the user of derived face base classes 
  // to add their own purpose checking
  bool is_valid(bool /* verbose */ = false, int /* level */ = 0) const
  {return true;}
  

};

template <class Gt>
Triangulation_face_base_2<Gt> ::
Triangulation_face_base_2()
{
  set_vertices();
  set_neighbors();
}

template <class Gt>
Triangulation_face_base_2<Gt> ::
Triangulation_face_base_2( void* v0, void* v1, void* v2)
{
  set_vertices(v0, v1, v2);
  set_neighbors();
}

template <class Gt>
Triangulation_face_base_2<Gt> ::
Triangulation_face_base_2(void* v0, void* v1, void* v2,
			  void* n0, void* n1, void* n2)
{
  set_vertices(v0, v1, v2);
  set_neighbors(n0, n1, n2);
}


template <class Gt>
inline void*
Triangulation_face_base_2<Gt> ::
vertex(int i) const
{
  CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2);
  return V[i];
} 


template <class Gt>
inline bool
Triangulation_face_base_2<Gt> ::
has_vertex(const void* v) const
{
  return (V[0] == v) || (V[1] == v) || (V[2]== v);
}
    
template <class Gt>
inline bool
Triangulation_face_base_2<Gt> ::    
has_vertex(const void* v, int& i) const
{
  if (v == V[0]) {
    i = 0;
    return true;
  }
  if (v == V[1]) {
    i = 1;
    return true;
  }
  if (v == V[2]) {
    i = 2;
    return true;
  }
  return false;
}
    
template <class Gt>    
inline int
Triangulation_face_base_2<Gt> :: 
vertex_index(const void* v) const
{
  if (v == V[0]) return 0;
  if (v == V[1]) return 1;
  CGAL_triangulation_assertion( v == V[2] );
  return 2;
}

template <class Gt>    
inline void* 
Triangulation_face_base_2<Gt> ::
neighbor(int i) const
{
  CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2);
  return N[i];
}
    
template <class Gt>      
inline bool 
Triangulation_face_base_2<Gt> ::
has_neighbor(const void* n) const
{
  return (N[0] == n) || (N[1] == n) || (N[2] == n);
}
    
    
template <class Gt>      
inline bool 
Triangulation_face_base_2<Gt> ::
has_neighbor(const void* n, int& i) const
{
  if(n == N[0]){
    i = 0;
    return true;
  }
  if(n == N[1]){
    i = 1;
    return true;
  }
  if(n == N[2]){
    i = 2;
    return true;
  }
  return false;
}

    
    
template <class Gt>      
inline int 
Triangulation_face_base_2<Gt> ::
face_index(const void* n) const
{
  if (n == N[0]) return 0;
  if (n == N[1]) return 1;
  CGAL_triangulation_assertion( n == N[2] );
  return 2;
}
    
template <class Gt>      
inline void
Triangulation_face_base_2<Gt> :: 
set_vertex(int i, void* v)
{
  CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2);
  V[i] = v;
}
    
template <class Gt>      
inline void
Triangulation_face_base_2<Gt> ::     
set_neighbor(int i, void* n)
{
  CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2);
  N[i] = n;
}

template <class Gt>      
inline void
Triangulation_face_base_2<Gt> :: 
set_vertices()
{
  V[0] = V[1] = V[2] = NULL;
}
    
template <class Gt>      
inline void
Triangulation_face_base_2<Gt> ::     
set_vertices(void* v0,  void* v1, void* v2)
{
  V[0] = v0;
  V[1] = v1;
  V[2] = v2;
}
    
template <class Gt>      
inline void
Triangulation_face_base_2<Gt> :: 
set_neighbors()
{
  N[0] = N[1] = N[2] = NULL;
}
    
template <class Gt>      
inline void
Triangulation_face_base_2<Gt> :: 
set_neighbors(void* n0,void* n1, void* n2)
{
  N[0] = n0;
  N[1] = n1;
  N[2] = n2;
}

template <class Gt>
void
Triangulation_face_base_2<Gt> :: 
reorient()
{
  //exchange the vertices 0 and 1
  set_vertices (V[1],V[0],V[2]);
  set_neighbors(N[1],N[0],N[2]);
}

template <class Gt>
inline void 
Triangulation_face_base_2<Gt> ::
ccw_permute()
{
  set_vertices (V[2],V[0],V[1]);
  set_neighbors(N[2],N[0],N[1]);
}


template <class Gt>
inline void 
Triangulation_face_base_2<Gt> ::
cw_permute()
{
  set_vertices (V[1],V[2],V[0]);
  set_neighbors(N[1],N[2],N[0]);
}


template < class Gt>
inline  int 
Triangulation_face_base_2<Gt> ::
dimension() const
{
  if (V[2] != NULL) {return 2;}
  else return( V[1] != NULL ? 1 : 0);
}




CGAL_END_NAMESPACE 

#endif //CGAL_TRIANGULATION_FACE_BASE_2_H
