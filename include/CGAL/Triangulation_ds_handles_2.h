// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Triangulation_ds_handles_2.h
// package       : Triangulation_2 (7.32)
// source        : $RCSfile: Triangulation_ds_handles_2.h,v $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2002/02/13 10:46:15 $
//
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_DS_HANDLES_2_H
#define CGAL_TRIANGULATION_DS_HANDLES_2_H

#include <CGAL/Pointer.h>

CGAL_BEGIN_NAMESPACE

// template <class Tds >
// class Triangulation_face_iterator_2;

// template <class Tds >
// class Triangulation_face_circulator_2;

// template <class Tds >
// class Triangulation_vertex_iterator_2;

template <class Gt, class Tds>
class Triangulation_line_face_circulator_2;

template <class Tds>
class Triangulation_ds_face_handle_2
  : public Pointer<typename Tds::Face> 
{
public:
  typedef Triangulation_ds_face_handle_2<Tds>          Face_handle;
  typedef Pointer<typename Tds::Face>                  Pointer_;
  typedef typename Tds::Face                           Face;
  typedef typename Tds::Face_iterator                  Face_iterator;
  typedef typename Tds::Face_circulator                Face_circulator;
  //typedef Triangulation_line_face_circulator_2<Gt,Tds> Line_face_circulator;

  Triangulation_ds_face_handle_2()
    : Pointer_(NULL)
    {}

  Triangulation_ds_face_handle_2( Face* p)
    : Pointer_(p)
    {}

  Triangulation_ds_face_handle_2( const Face_handle& p)
    : Pointer_(p.ptr())
    {}

  Triangulation_ds_face_handle_2(const Face_iterator& fit)
    : Pointer_(&(*fit))
    {}
  
  Triangulation_ds_face_handle_2(const Face_circulator& fc)
    : Pointer_(&(*fc))
    {}

//   template<class Gt>
//   Triangulation_ds_face_handle_2(
// 	      Triangulation_line_face_circulator_2<Gt,Tds> lfc)
//     : Pointer_(lfc->handle())
//     {}

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

template <class Tds>
class Triangulation_ds_vertex_handle_2
  : public Pointer<typename Tds::Vertex > 
{
public:
  typedef Triangulation_ds_vertex_handle_2<Tds>     Vertex_handle;
  typedef Pointer< typename Tds::Vertex>            Pointer_;
  typedef typename Tds::Vertex                      Vertex;
  typedef typename Tds::Vertex_iterator             Vertex_iterator;
  typedef typename Tds::Vertex_circulator           Vertex_circulator ;
  
  Triangulation_ds_vertex_handle_2()
    : Pointer_(NULL)
    {}

  Triangulation_ds_vertex_handle_2( Vertex* p)
    : Pointer_(p)
    {}

  Triangulation_ds_vertex_handle_2(const Vertex_handle& p)
    : Pointer_(p.ptr())
    {}

  Triangulation_ds_vertex_handle_2(const Vertex_iterator& vit)
    : Pointer_(&(*vit))
    {}
  
  Triangulation_ds_vertex_handle_2(const Vertex_circulator& vc)
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

#endif //CGAL_TRIANGULATION_DS_HANDLES_2_H
