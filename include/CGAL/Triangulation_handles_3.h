// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Triangulation_handles_3.h
// package       : Triangulation3 (1.29)
// revision      : $Revision: 1.11 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis 
//                 (Mariette Yvinec)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_HANDLES_3_H
#define CGAL_TRIANGULATION_HANDLES_3_H

#include <CGAL/Pointer.h>
#include <CGAL/Triangulation_vertex_3.h>
#include <CGAL/Triangulation_cell_3.h>
#include <CGAL/Triangulation_iterators_3.h>
#include <CGAL/Triangulation_circulators_3.h>
  
#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds >
class Triangulation_cell_3;

template <  class Gt, class Tds >
class Triangulation_vertex_3;

template <  class Gt, class Tds>
class Triangulation_cell_iterator_3;

template <  class Gt, class Tds>
class Triangulation_vertex_iterator_3;

template <  class Gt, class Tds>
class Triangulation_cell_circulator_3;

template < class Gt, class Tds>
class Triangulation_vertex_handle_3
  :public Pointer<Triangulation_vertex_3<Gt,Tds> > 
{
public:
  typedef Pointer<Triangulation_vertex_3<Gt,Tds> > Ptr;
  typedef Triangulation_vertex_3<Gt,Tds> Vertex;
  typedef Triangulation_vertex_handle_3<Gt,Tds> Vertex_handle;
  
  typedef Triangulation_vertex_iterator_3<Gt,Tds>      Vertex_iterator;
  
  inline 
  Triangulation_vertex_handle_3()
    : Ptr(NULL)
  {}

  inline  
  Triangulation_vertex_handle_3(const Vertex* v)
    : Ptr((Vertex*)v)
    {}

  inline  
  Triangulation_vertex_handle_3(const Vertex_iterator & vit)
    : Ptr(&(*vit))
    {}
  
  inline Vertex_handle & operator=(const Vertex* & v)
  {
    ptr() = const_cast<Vertex*>(v) ;
    return *this;
  }
    
  inline Vertex_handle & operator=(const Vertex_handle & v)
  {
    ptr() = v.ptr();
    return *this;
  }
  
};

template <class Gt, class Tds>
Triangulation_vertex_3<Gt,Tds> * 
handle2pointer(const Triangulation_vertex_handle_3<Gt,Tds> v)
{
  return v.ptr();
}

template <class Gt, class Tds>
class Triangulation_cell_handle_3
  :public Pointer<Triangulation_cell_3<Gt,Tds> > 
{
public:
  typedef Pointer<Triangulation_cell_3<Gt,Tds> > Ptr;
  typedef Triangulation_cell_3<Gt,Tds> Cell;
  typedef Triangulation_cell_handle_3<Gt,Tds> Cell_handle;
  
  typedef Triangulation_cell_iterator_3<Gt,Tds> Cell_iterator;
  typedef Triangulation_cell_circulator_3<Gt,Tds> Cell_circulator;
  
  inline 
  Triangulation_cell_handle_3()
    : Ptr(NULL)
  {}

  inline  
  Triangulation_cell_handle_3(const Cell* c)
    : Ptr((Cell*)c)
  {}

  inline  
  Triangulation_cell_handle_3(const Cell_iterator & cit)
    : Ptr(&(*cit))
  {}
  
  inline  
  Triangulation_cell_handle_3(const Cell_circulator & ccir)
    : Ptr(&(*ccir))
  {}

  inline Cell_handle & operator=(const Cell* & c)
  {
    ptr() = const_cast<Cell*>(c) ;
    return *this;
  }
    
  inline Cell_handle & operator=(const Cell_handle & c)
  {
    ptr() = c.ptr();
    return *this;
  }
  
};

template <class Gt, class Tds>
Triangulation_cell_3<Gt,Tds> * 
handle2pointer(const Triangulation_cell_handle_3<Gt,Tds> c)
{
  return c.ptr();
}

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_HANDLES_3_H
