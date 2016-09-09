// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Triangulation_handles_2.h
// package       : Triangulation (3.17)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_handles_2.h,v $
// revision      : $Revision: 1.2.1.5 $
// revision_date : $Date: 1999/02/26 16:02:56 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_HANDLES_2_H
#define CGAL_TRIANGULATION_HANDLES_2_H

#include <CGAL/Triangulation_short_names_2.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds >
class Triangulation_face_2;

template <  class Gt, class Tds >
class Triangulation_vertex_2;

template <  class Gt, class Tds>
class Triangulation_face_iterator_2;

template <  class Gt, class Tds>
class Triangulation_vertex_iterator_2;

template <  class Gt, class Tds>
class Triangulation_face_circulator_2;

template <  class Gt, class Tds>
class Triangulation_vertex_circulator_2;


template <  class Gt, class Tds>
class Triangulation_face_handle_2
  :public Pointer<Triangulation_face_2<Gt,Tds> > 
{
public:
  typedef Pointer<Triangulation_face_2<Gt,Tds> > Pointer;
  typedef Triangulation_face_2<Gt,Tds> Face;
  typedef Triangulation_face_handle_2<Gt,Tds> Face_handle;
  
  typedef Triangulation_face_iterator_2<Gt,Tds>      Face_iterator;
  typedef Triangulation_face_circulator_2<Gt,Tds>    Face_circulator;
  
  inline 
  Triangulation_face_handle_2()
    : Pointer(NULL)
  {}

  inline  
  Triangulation_face_handle_2(const Face* p)
    : Pointer((Face*)p)
  {}

  inline Face_handle& operator=(const Face*& p)
    {
        ptr() = p ;
        return *this;
    }
    
    inline Face_handle& operator=(const Face_handle& p)
    {
        ptr() = p.ptr();
        return *this;
    }
  
   inline  
    Triangulation_face_handle_2(const Face_iterator& fit)
        : Pointer(&(*fit))
    {}
  

  inline  
   Triangulation_face_handle_2(const Face_circulator& fc)
        : Pointer(&(*fc))
    {}
};

template < class Gt, class Tds>
class Triangulation_vertex_handle_2
  :public Pointer<Triangulation_vertex_2<Gt,Tds> > 
{
public:
  typedef Pointer<Triangulation_vertex_2<Gt,Tds> > Pointer;
  typedef Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  
  typedef Triangulation_vertex_iterator_2<Gt,Tds>      Vertex_iterator;
  typedef Triangulation_vertex_circulator_2<Gt,Tds>    Vertex_circulator;
  
  inline 
  Triangulation_vertex_handle_2()
    : Pointer(NULL)
  {}

  inline  
  Triangulation_vertex_handle_2(const Vertex* p)
        : Pointer((Vertex*)p)
    {}

  inline Vertex_handle& operator=(const Vertex*& p)
    {
        ptr() = p ;
        return *this;
    }
    
    inline Vertex_handle& operator=(const Vertex_handle& p)
    {
        ptr() = p.ptr();
        return *this;
    }
  
   inline  
   Triangulation_vertex_handle_2(const Vertex_iterator& vit)
        : Pointer(&(*vit))
    {}

  
  inline  
   Triangulation_vertex_handle_2(const Vertex_circulator& vc)
        : Pointer(&(*vc))
    {}
  
};

CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_HANDLES_2_H
