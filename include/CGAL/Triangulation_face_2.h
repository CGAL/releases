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
// file          : include/CGAL/Triangulation_face_2.h
// package       : Triangulation (2.10)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_face_2.h,v $
// revision      : $Revision: 1.4.1.8 $
// revision_date : $Date: 1998/12/03 17:11:33 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_FACE_2_H
#define CGAL_TRIANGULATION_FACE_2_H

#include <CGAL/Pointer.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_default_data_structure_2.h>


template < class Gt, class Tds >
class CGAL_Triangulation_vertex_2;

template < class Gt, class Tds >
class CGAL_Triangulation_vertex_handle_2;

template < class Gt, class Tds >
class CGAL_Triangulation_face_handle_2;

template < class Gt, class Tds >
class CGAL_Triangulation_face_2  : public  Tds::Face
{
public:
  //  typedef Tds Tds;

  typedef Gt  Geom_traits;
  typedef typename Geom_traits::Point Point;
  typedef typename Geom_traits::Segment Segment;
  typedef typename Geom_traits::Triangle Triangle;

  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;

  typedef CGAL_Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef CGAL_Triangulation_face_2<Gt,Tds> Face;

  typedef CGAL_Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  typedef CGAL_Triangulation_face_handle_2<Gt,Tds> Face_handle;
  //  typedef pair<Face_handle, int>     Edge;


  inline
  CGAL_Triangulation_face_2()
    : Fa()
  { }

  inline
  CGAL_Triangulation_face_2(const Vertex_handle& v0,
			  const Vertex_handle& v1,
			  const Vertex_handle& v2)
    : Fa(&(*v0), &(*v1), &(*v2))
  {}
        
    
  inline
  CGAL_Triangulation_face_2(const Vertex_handle& v0,
			  const Vertex_handle& v1,
			  const Vertex_handle& v2,
			  const Face_handle& n0,
			  const Face_handle& n1,
			  const Face_handle& n2)
    : Fa(&(*v0), &(*v1), &(*v2),&(*n0), &(*n1), &(*n2)) 
  {}
        
    

  // Vertex access functions
  inline Vertex_handle vertex(int i) const
  {
    return  ((Vertex *)(Fa::vertex(i)));
  }
    
    
  inline bool has_vertex(const Vertex_handle& v) const
  {
        return (Fa::has_vertex( & (*v)) );
  }
    
    
  inline bool has_vertex(const Vertex_handle& v, int& i) const
  {
    return Fa::has_vertex( &(*v), i);
  }

  inline int index(const Vertex_handle& v) const
  {
    return Fa::index( &(*v));
  }
  
  
 

  //ACCESS FUNCTIONS
  inline
  Face_handle neighbor(int i) const
  {
    return (Face *)(Fa::neighbor(i));
  }

   inline int index(const Face_handle& f) const
  {
    return Fa::index( &(*f));
  }
  
  inline bool has_neighbor(const Face_handle& f) const
  {
    return Fa::has_neighbor( &(*f));
  }

  inline bool has_neighbor(const Face_handle& f, int &i) const
  {
    return Fa::has_neighbor( &(*f), i);
  }

 
  inline Face_handle handle() const
  {
    return Face_handle(this);
  }

 //Setting
  inline
  void set_vertices(const Vertex_handle& v0,
		    const Vertex_handle& v1,
		    const Vertex_handle& v2)
    {
        Fa::set_vertices(&(*v0), &(*v1), &(*v2));
    }
    
  inline
    void set_neighbors(const Face_handle& n0,
                       const Face_handle& n1,
                       const Face_handle& n2)
    {
        Fa::set_neighbors(&(*n0), &(*n1), &(*n2));
    }

  inline  
  void set_vertices() 
  {
    Fa::set_vertices();
  }
   
 inline
  void set_neighbors() 
  {
    Fa::set_neighbors();
  }
    
  inline
    void set_vertex(int i, const Vertex_handle& v)
    {
        Fa::set_vertex(i, &(*v));
    }

    inline
    void set_neighbor(int i, const Face_handle& n)
    {
        Fa::set_neighbor(i, &(*n));
    }

};

#endif //CGAL_TRIANGULATION_FACE_2_H
