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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Triangulation_cell_3.h
// package       : Triangulation3 (1.42)
// revision      : $Revision: 1.13 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis 
//                 (Mariette Yvinec)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_CELL_3_H
#define CGAL_TRIANGULATION_CELL_3_H

#include <CGAL/Pointer.h>
#include <CGAL/Triangulation_data_structure_3.h>

#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds >
class Triangulation_vertex_3;

template < class Gt, class Tds >
class Triangulation_vertex_handle_3;

template < class Gt, class Tds >
class Triangulation_cell_handle_3;

template < class Gt, class Tds >
class Triangulation_cell_3
  : public Tds::Cell
{
public:

  typedef typename Gt::Point Point;

  typedef typename Tds::Vertex Vtds;
  typedef typename Tds::Cell Ctds;

  typedef Triangulation_vertex_3<Gt,Tds> Vertex;

  typedef Triangulation_vertex_handle_3<Gt,Tds> Vertex_handle;
  typedef Triangulation_cell_handle_3<Gt,Tds> Cell_handle;

  inline
  Triangulation_cell_3()
    : Ctds()
  { }

//   inline
//   Triangulation_cell_3(Tds& tds)
//     : Ctds(tds)
//   { }

  inline
  Triangulation_cell_3(Vertex_handle v0,
		       Vertex_handle v1,
		       Vertex_handle v2,
		       Vertex_handle v3)
    : Ctds(&(*v0), &(*v1), &(*v2), &(*v3))
  {}
    
  inline
  Triangulation_cell_3(Vertex_handle v0,
		       Vertex_handle v1,
		       Vertex_handle v2,
		       Vertex_handle v3,
		       Cell_handle n0,
		       Cell_handle n1,
		       Cell_handle n2,
		       Cell_handle n3)
    : Ctds(&(*v0), &(*v1), &(*v2), &(*v3), 
	   &(*n0), &(*n1), &(*n2), &(*n3)) 
  {}

  // Vertex access functions
  inline Vertex_handle vertex(int i) const
  {
    return  ((Vertex *)(Ctds::vertex(i)));
  }
    
  inline bool has_vertex(const Vertex_handle & v) const
  {
    return (Ctds::has_vertex( & (*v)) );
  }
    
  inline bool has_vertex(const Vertex_handle & v, int & i) const
  {
    return Ctds::has_vertex( &(*v), i);
  }

  inline int index(const Vertex_handle & v) const
  {
    return Ctds::index( &(*v));
  }

  //ACCESS FUNCTIONS
  inline
  Cell_handle neighbor(int i) const
  {
    return (Triangulation_cell_3 *)(Ctds::neighbor(i));
  }

  inline int index(Cell_handle c) const
  {
    return Ctds::index( &(*c));
  }

  inline Vertex_handle mirror_vertex(int i) const
    {
      return Ctds::mirror_vertex(i);
    }

  inline 
  int mirror_index(int i) const
    {
      return Ctds::mirror_index(i);
    }
  
  inline bool has_neighbor(Cell_handle c) const
  {
    return Ctds::has_neighbor( &(*c));
  }

  inline bool has_neighbor(Cell_handle c, int & i) const
  {
    return Ctds::has_neighbor( &(*c), i);
  }
 
  inline Cell_handle handle() const
  {
    return Cell_handle(this);
  }

 //Setting
  void set_vertices(Vertex_handle v0,
		    Vertex_handle v1,
		    Vertex_handle v2,
		    Vertex_handle v3)
  {
    Ctds::set_vertices(&(*v0), &(*v1), &(*v2), &(*v3));
  }
    
  void set_neighbors(Cell_handle n0,
		     Cell_handle n1,
		     Cell_handle n2,
		     Cell_handle n3)
  {
    Ctds::set_neighbors(&(*n0), &(*n1), &(*n2), &(*n3));
  }
    
  void set_vertices() 
  {
    Ctds::set_vertices();
  }
    
  void set_neighbors() 
  {
    Ctds::set_neighbors();
  }
    
  void set_vertex(int i, Vertex_handle v)
  {
    Ctds::set_vertex(i, &(*v));
  }
    
  void set_neighbor(int i, Cell_handle n)
  {
    Ctds::set_neighbor(i, &(*n));
  }

//   inline bool is_valid(bool verbose = false, int level = 0) const
//   {
//     return Ctds::is_valid(verbose,level);
//   }
};

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_CELL_3_H
