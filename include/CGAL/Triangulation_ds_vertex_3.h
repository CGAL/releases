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
// file          : include/CGAL/Triangulation_ds_vertex_3.h
// package       : Triangulation3 (1.29)
// revision      : $Revision: 1.14 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis 
//                 (Mariette Yvinec)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
//
// vertex of a combinatotial triangulation of any dimension <=3
//
// ============================================================================

#ifndef CGAL_TRIANGULATION_DS_VERTEX_3_H
#define CGAL_TRIANGULATION_DS_VERTEX_3_H

#include <CGAL/Triangulation_ds_iterators_3.h>

#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template <class Vb, class Cb >
class  Triangulation_ds_vertex_3 
  : public Vb
{

public:
  typedef typename Vb::Point Point;
  typedef Triangulation_ds_vertex_3<Vb,Cb> Vertex;
  typedef Triangulation_ds_cell_3<Vb,Cb> Cell;
//   typedef Triangulation_ds_cell_circulator_3<Vertex,Cell> Cell_circulator;
//   typedef Triangulation_ds_vertex_circulator_3<Vertex,Cell>
  //   Vertex_circulator;  
//   typedef Triangulation_ds_edge_circulator_3<Vertex,Cell> Edge_circulator;

  // CONSTRUCTORS

  inline 
  Triangulation_ds_vertex_3()
    : Vb()
  {}
    
  inline 
  Triangulation_ds_vertex_3(const Point & p)
    :  Vb(p)
  {}
    
  inline 
  Triangulation_ds_vertex_3(const Point & p, Cell * c)
    :  Vb(p, c)
  {}

  inline 
  Triangulation_ds_vertex_3(Cell * c)
    :  Vb(c)
  {}

  // ACCESS

  // point()
  //inherited from Vb

  inline 
  Cell* cell() const
  {
    return ( (Cell *) (Vb::cell()) );
  }
    
  // SETTING

  // set_point()
  //inherited from Vb

  inline 
  void set_cell(Cell* c)
  {
    Vb::set_cell(c);
  }

  inline 
  void set_point(const Point & p)
  {
    Vb::set_point(p);
  }

  // USEFUL NON CONSTANT TIME FUNCTIONS

//   inline Vertex_circulator incident_vertices()
//   {
//     return Vertex_circulator(this, cell());
//   }
    
//   inline Cell_circulator incident_cells()
//   {
//     return Cell_circulator(this, cell());
//   }
    
//   inline Cell_circulator incident_cells(const Cell* c)
//   {
//     return Cell_circulator(this, c);
//   }
    
//   inline Edge_circulator incident_edges()
//   {
//     return Edge_circulator(this, cell());
//   }
       
//   inline Edge_circulator incident_edges(const Cell* c)
//   {
//     return Edge_circulator(this, c);
//   }

    
  // CHECKING

   bool is_valid(bool verbose = false, int level = 0) const;
};

template <class Vb, class Cb >
bool
Triangulation_ds_vertex_3<Vb,Cb>::is_valid
(bool verbose, int level) const
{
  bool result = Vb::is_valid(verbose,level);
  result = result && cell()->has_vertex(this);
  if ( ! result ) {
    if ( verbose ) {
      std::cerr << "invalid vertex" << std::endl;
    }
    CGAL_triangulation_assertion(false);
  }
  return result;
}

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_DS_VERTEX_3_H
