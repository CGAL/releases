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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Triangulation_handles_2.h
// package       : Triangulation (4.30)
// source        : $RCSfile: Triangulation_handles_2.h,v $
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1999/12/10 15:05:54 $
//
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_HANDLES_2_H
#define CGAL_TRIANGULATION_HANDLES_2_H

#include <CGAL/Pointer.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds >
class Triangulation_face_2;

template <  class Gt, class Tds >
class Triangulation_vertex_2;

template <  class Gt, class Tds>
class Triangulation_all_faces_iterator_2;

template <  class Gt, class Tds>
class Triangulation_all_vertices_iterator_2;

template <  class Gt, class Tds>
class Triangulation_finite_faces_iterator_2;

template <  class Gt, class Tds>
class Triangulation_finite_vertices_iterator_2;

template <  class Gt, class Tds>
class Triangulation_face_circulator_2;

template <  class Gt, class Tds>
class Triangulation_vertex_circulator_2;

template <  class Gt, class Tds>
class Triangulation_line_face_circulator_2;


template <  class Gt, class Tds>
class Triangulation_face_handle_2
  :public Pointer<Triangulation_face_2<Gt,Tds> > 
{
public:
  typedef Pointer<Triangulation_face_2<Gt,Tds> >        Pointer_;
  typedef Triangulation_face_2<Gt,Tds>                  Face;
  typedef Triangulation_face_handle_2<Gt,Tds>           Face_handle;
  
  typedef Triangulation_all_faces_iterator_2<Gt,Tds>    All_faces_iterator;
  typedef Triangulation_finite_faces_iterator_2<Gt,Tds> Finite_faces_iterator;
  typedef Triangulation_face_circulator_2<Gt,Tds>       Face_circulator;
  typedef Triangulation_line_face_circulator_2<Gt,Tds> Line_face_circulator;

  Triangulation_face_handle_2()
    : Pointer_(NULL)
    {}

  Triangulation_face_handle_2( Face* p)
    : Pointer_(p)
    {}

  Triangulation_face_handle_2( const Face_handle& p)
    : Pointer_(p.ptr())
    {}

  Triangulation_face_handle_2(const Finite_faces_iterator& fit)
    : Pointer_(&(*fit))
    {}
  
  Triangulation_face_handle_2(const All_faces_iterator& fit)
    : Pointer_(&(*fit))
    {}

  Triangulation_face_handle_2(const Face_circulator& fc)
    : Pointer_(&(*fc))
    {}

  Triangulation_face_handle_2(const Line_face_circulator& fc)
    : Pointer_(&(*fc))
    {}

  Face_handle& operator=(Face* p)
    {
      ptr() = p ;
      return *this;
    }
    
  Face_handle& operator=(const Face_handle& p)
    {
      ptr() = p.ptr();
      return *this;
    }
};

template < class Gt, class Tds>
class Triangulation_vertex_handle_2
  :public Pointer<Triangulation_vertex_2<Gt,Tds> > 
{
public:
  typedef Pointer<Triangulation_vertex_2<Gt,Tds> >  Pointer_;
  typedef Triangulation_vertex_2<Gt,Tds>            Vertex;
  typedef Triangulation_vertex_handle_2<Gt,Tds>     Vertex_handle;
  
  typedef Triangulation_all_vertices_iterator_2<Gt,Tds> 
                                                    All_vertices_iterator;
  typedef Triangulation_finite_vertices_iterator_2<Gt,Tds> 
                                                    Finite_vertices_iterator;
  typedef Triangulation_vertex_circulator_2<Gt,Tds> Vertex_circulator;
  
  Triangulation_vertex_handle_2()
    : Pointer_(NULL)
    {}

  Triangulation_vertex_handle_2( Vertex* p)
    : Pointer_(p)
    {}

  Triangulation_vertex_handle_2(const Vertex_handle& p)
    : Pointer_(p.ptr())
    {}

  Triangulation_vertex_handle_2(const Finite_vertices_iterator& vit)
    : Pointer_(&(*vit))
    {}
  
  Triangulation_vertex_handle_2(const All_vertices_iterator& vit)
    : Pointer_(&(*vit))
    {}

  Triangulation_vertex_handle_2(const Vertex_circulator& vc)
    : Pointer_(&(*vc))
    {}
  
  Vertex_handle& operator=(Vertex* p)
    {
        ptr() = p ;
        return *this;
    }
    
  Vertex_handle& operator=(const Vertex_handle& p)
    {
        ptr() = p.ptr();
        return *this;
    }
  
 };

CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_HANDLES_2_H
