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
// file          : include/CGAL/Triangulation_vertex_3.h
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

#ifndef CGAL_TRIANGULATION_VERTEX_3_H
#define CGAL_TRIANGULATION_VERTEX_3_H

#include <CGAL/Pointer.h>
//#include <CGAL/Triangulation_data_structure_3.h>
#include <CGAL/Triangulation_circulators_3.h>
#include <CGAL/Triangulation_cell_3.h>
#include <CGAL/Triangulation_vertex_3.h>
#include <CGAL/Triangulation_handles_3.h>

#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds >
class Triangulation_cell_3;

template < class Gt, class Tds >
class Triangulation_vertex_handle_3;

template < class Gt, class Tds >
class Triangulation_cell_handle_3;

template<class Gt, class Tds >
class Triangulation_vertex_3
  : public Tds::Vertex
{
public:
  
  typedef typename Gt::Point Point;

  typedef typename Tds::Vertex Vtds;
  typedef typename Tds::Cell Ctds;

  typedef Triangulation_cell_3<Gt,Tds> Cell;
  
  typedef Triangulation_vertex_handle_3<Gt,Tds> Vertex_handle;
  typedef Triangulation_cell_handle_3<Gt,Tds> Cell_handle;
  
  Triangulation_vertex_3()
     : Vtds()
  {}

  Triangulation_vertex_3(const Point & p)
    :  Vtds(p)
  {}
    
  Triangulation_vertex_3(const Point & p, Cell_handle c)
    :  Vtds(p, &(*c))
  {}

  Triangulation_vertex_3(Cell_handle c)
    :  Vtds(&(*c))
  {}

  inline void set_cell(Cell_handle c)
  {
    Vtds::set_cell(&(*c));
  }
    
  inline void set_point(const Point & p)
  {
    Vtds::set_point(p);
  }
    
  inline Cell_handle cell() const
  {
    return (Cell *) Vtds::cell();
  }
        
  inline Vertex_handle handle() const
  {
    return Vertex_handle(this);
  }

  inline bool is_valid(bool verbose = false, int level = 0) const
  {
    return Vtds::is_valid(verbose,level);
  }
//   inline Vertex_circulator incident_vertices()
//   {
//     return Vertex_circulator(handle(), cell());
//   }

//   inline Vertex_circulator incident_vertices(const Cell_handle& c)
//   {
//     return Vertex_circulator(handle(), c);
//   } 

//   inline 
//   Cell_circulator incident_cells()
//   {
//     return Cell_circulator(handle(), cell());
//   }
    
//   inline Cell_circulator incident_cells(const Cell_handle& c)
//   {
//     return Cell_circulator(handle(), c);
//   }
    
//   inline Edge_circulator incident_edges()
//   {
//     return Edge_circulator(handle(), cell());
//   }
 
//   inline Edge_circulator incident_edges(const Cell_handle& c)
//   {
//     return Edge_circulator(handle(), c);
//   }
    
};

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_VERTEX_3_H
