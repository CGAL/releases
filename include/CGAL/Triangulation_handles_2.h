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
// file          : include/CGAL/Triangulation_handles_2.h
// package       : Triangulation (2.10)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_handles_2.h,v $
// revision      : $Revision: 1.2.1.4 $
// revision_date : $Date: 1998/12/03 17:15:35 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_HANDLES_2_H
#define CGAL_TRIANGULATION_HANDLES_2_H

#include <CGAL/Triangulation_short_names_2.h>

template < class Gt, class Tds >
class CGAL_Triangulation_face_2;

template <  class Gt, class Tds >
class CGAL_Triangulation_vertex_2;

template <  class Gt, class Tds>
class CGAL_Triangulation_face_iterator_2;

template <  class Gt, class Tds>
class CGAL_Triangulation_vertex_iterator_2;

template <  class Gt, class Tds>
class CGAL_Triangulation_face_circulator_2;

template <  class Gt, class Tds>
class CGAL_Triangulation_vertex_circulator_2;


template <  class Gt, class Tds>
class CGAL_Triangulation_face_handle_2
  :public CGAL_Pointer<CGAL_Triangulation_face_2<Gt,Tds> > 
{
public:
  typedef CGAL_Pointer<CGAL_Triangulation_face_2<Gt,Tds> > Pointer;
  typedef CGAL_Triangulation_face_2<Gt,Tds> Face;
  typedef CGAL_Triangulation_face_handle_2<Gt,Tds> Face_handle;
  
  typedef CGAL_Triangulation_face_iterator_2<Gt,Tds>      Face_iterator;
  typedef CGAL_Triangulation_face_circulator_2<Gt,Tds>    Face_circulator;
  
  inline 
  CGAL_Triangulation_face_handle_2()
    : Pointer(NULL)
  {}

  inline  
  CGAL_Triangulation_face_handle_2(const Face* p)
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
    CGAL_Triangulation_face_handle_2(const Face_iterator& fit)
        : Pointer(&(*fit))
    {}
  

  inline  
   CGAL_Triangulation_face_handle_2(const Face_circulator& fc)
        : Pointer(&(*fc))
    {}
};

template < class Gt, class Tds>
class CGAL_Triangulation_vertex_handle_2
  :public CGAL_Pointer<CGAL_Triangulation_vertex_2<Gt,Tds> > 
{
public:
  typedef CGAL_Pointer<CGAL_Triangulation_vertex_2<Gt,Tds> > Pointer;
  typedef CGAL_Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef CGAL_Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  
  typedef CGAL_Triangulation_vertex_iterator_2<Gt,Tds>      Vertex_iterator;
  typedef CGAL_Triangulation_vertex_circulator_2<Gt,Tds>    Vertex_circulator;
  
  inline 
  CGAL_Triangulation_vertex_handle_2()
    : Pointer(NULL)
  {}

  inline  
  CGAL_Triangulation_vertex_handle_2(const Vertex* p)
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
   CGAL_Triangulation_vertex_handle_2(const Vertex_iterator& vit)
        : Pointer(&(*vit))
    {}

  
  inline  
   CGAL_Triangulation_vertex_handle_2(const Vertex_circulator& vc)
        : Pointer(&(*vc))
    {}
  
};

#endif //CGAL_TRIANGULATION_HANDLES_2_H
