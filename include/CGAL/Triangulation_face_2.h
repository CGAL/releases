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
// file          : include/CGAL/Triangulation_face_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Triangulation_face_2.h,v $
// revision      : $Revision: 1.12 $
// revision_date : $Date: 2000/06/08 15:10:29 $
//
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_FACE_2_H
#define CGAL_TRIANGULATION_FACE_2_H

#include <CGAL/Pointer.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_default_data_structure_2.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds >
class Triangulation_vertex_2;

template < class Gt, class Tds >
class Triangulation_vertex_handle_2;

template < class Gt, class Tds >
class Triangulation_face_handle_2;

template < class Gt, class Tds >
class Triangulation_face_2  : public  Tds::Face
{
public:
  typedef Gt  Geom_traits;
  typedef typename Geom_traits::Point_2 Point;
  typedef typename Geom_traits::Segment_2 Segment;
  typedef typename Geom_traits::Triangle_2 Triangle;

  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;

  typedef Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef Triangulation_face_2<Gt,Tds> Tr_face;

  typedef Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  typedef Triangulation_face_handle_2<Gt,Tds> Face_handle;


  Triangulation_face_2()
    : Fa()
  { }

  Triangulation_face_2(const Vertex_handle& v0,
		       const Vertex_handle& v1,
		       const Vertex_handle& v2)
    : Fa(&(*v0), &(*v1), &(*v2))
  {}
        
  Triangulation_face_2(const Vertex_handle& v0,
		       const Vertex_handle& v1,
		       const Vertex_handle& v2,
		       const Face_handle& n0,
		       const Face_handle& n1,
		       const Face_handle& n2)
    : Fa(&(*v0), &(*v1), &(*v2),&(*n0), &(*n1), &(*n2)) 
  {}
 
  // Vertex access functions
  Vertex_handle vertex(int i) const;
  Vertex_handle mirror_vertex(int i) const;
  bool has_vertex(const Vertex_handle& v) const;
  bool has_vertex(const Vertex_handle& v, int& i) const;
  int index(const Vertex_handle& v) const;
 
  //ACCESS FUNCTIONS
  Face_handle neighbor(int i) const;
  int index(const Face_handle& f) const;
  bool has_neighbor(const Face_handle& f) const;
  bool has_neighbor(const Face_handle& f, int &i) const;
  int mirror_index(int i) const;
  Face_handle handle() const;
  
  //Setting
  void set_vertices(const Vertex_handle& v0,
		    const Vertex_handle& v1,
		    const Vertex_handle& v2);
  void set_neighbors(const Face_handle& n0,
		     const Face_handle& n1,
		     const Face_handle& n2);
  void set_vertices();
  void set_neighbors(); 
  void set_vertex(int i, const Vertex_handle& v);
  void set_neighbor(int i, const Face_handle& n);
};

// Vertex access functions
template < class Gt, class Tds >
inline
Triangulation_vertex_handle_2<Gt,Tds>
Triangulation_face_2<Gt,Tds>::
vertex(int i) const
{
  return  ((Vertex *)(Fa::vertex(i)));
}
    
template < class Gt, class Tds >
inline
Triangulation_vertex_handle_2<Gt,Tds>
Triangulation_face_2<Gt,Tds>::
mirror_vertex(int i) const
{
  return ((Vertex *)(Fa::mirror_vertex(i)));
}
 
template < class Gt, class Tds >
inline
bool
Triangulation_face_2<Gt,Tds>::  
has_vertex(const Vertex_handle& v) const
{
  return (Fa::has_vertex( & (*v)) );
}
    
template < class Gt, class Tds >
inline
bool
Triangulation_face_2<Gt,Tds>::     
has_vertex(const Vertex_handle& v, int& i) const
{
  return Fa::has_vertex( &(*v), i);
}

template < class Gt, class Tds >
inline
int
Triangulation_face_2<Gt,Tds>::
index(const Vertex_handle& v) const
{
  return Fa::index( &(*v));
}
  
//ACCESS FUNCTIONS
template < class Gt, class Tds >
inline
Triangulation_face_handle_2<Gt,Tds>
Triangulation_face_2<Gt,Tds>::
neighbor(int i) const
{
  return static_cast<Tr_face *>(Fa::neighbor(i));
}

template < class Gt, class Tds >
inline
int
Triangulation_face_2<Gt,Tds>::
index(const Face_handle& f) const
{
  return Fa::index( &(*f));
}
  
template < class Gt, class Tds >
inline
bool
Triangulation_face_2<Gt,Tds>::
has_neighbor(const Face_handle& f) const
{
  return Fa::has_neighbor( &(*f));
}

template < class Gt, class Tds >
inline
bool
Triangulation_face_2<Gt,Tds>::
has_neighbor(const Face_handle& f, int &i) const
{
  return Fa::has_neighbor( &(*f), i);
}

template < class Gt, class Tds >
inline
int
Triangulation_face_2<Gt,Tds>::
mirror_index(int i) const
{
  return Fa::mirror_index(i);
}

template < class Gt, class Tds >
inline
Triangulation_face_handle_2<Gt,Tds>
Triangulation_face_2<Gt,Tds>::
handle() const
{
  Tr_face * ncthis = (Tr_face *) this;
  return Face_handle(ncthis);
}

 //Setting
template < class Gt, class Tds >
inline
void
Triangulation_face_2<Gt,Tds>::
set_vertices(const Vertex_handle& v0,
	     const Vertex_handle& v1,
	     const Vertex_handle& v2)
{
  Fa::set_vertices(&(*v0), &(*v1), &(*v2));
}
    
template < class Gt, class Tds >
inline
void
Triangulation_face_2<Gt,Tds>:: 
set_neighbors(const Face_handle& n0,
	      const Face_handle& n1,
	      const Face_handle& n2)
{
  Fa::set_neighbors(&(*n0), &(*n1), &(*n2));
}

template < class Gt, class Tds >
inline
void
Triangulation_face_2<Gt,Tds>::
set_vertices() 
{
  Fa::set_vertices();
}
   
template < class Gt, class Tds >
inline
void
Triangulation_face_2<Gt,Tds>::
set_neighbors() 
{
  Fa::set_neighbors();
}
    
template < class Gt, class Tds >
inline
void
Triangulation_face_2<Gt,Tds>::
set_vertex(int i, const Vertex_handle& v)
{
  Fa::set_vertex(i, &(*v));
}

template < class Gt, class Tds >
inline
void
Triangulation_face_2<Gt,Tds>::
set_neighbor(int i, const Face_handle& n)
{
  Fa::set_neighbor(i, &(*n));
} 



CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_FACE_2_H
