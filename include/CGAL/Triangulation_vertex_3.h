// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Triangulation_vertex_3.h
// package       : Triangulation_3 (1.83)
// revision      : $Revision: 1.17 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_VERTEX_3_H
#define CGAL_TRIANGULATION_VERTEX_3_H

#include <CGAL/basic.h>
#include <CGAL/Triangulation_short_names_3.h>

#include <CGAL/Triangulation_cell_3.h>
#include <CGAL/Triangulation_handles_3.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds > class Triangulation_cell_3;
template < class Gt, class Tds > class Triangulation_vertex_handle_3;
template < class Gt, class Tds > class Triangulation_cell_handle_3;

template<class Gt, class Tds >
class Triangulation_vertex_3
  : public Tds::Vertex
{
  typedef typename Tds::Vertex Vtds;
  typedef typename Tds::Cell Ctds;

  typedef Triangulation_cell_3<Gt,Tds> Cell;
  typedef Triangulation_vertex_handle_3<Gt,Tds> Vertex_handle;
  typedef Triangulation_cell_handle_3<Gt,Tds> Cell_handle;

public:
 
  typedef typename Gt::Point_3 Point;

  Triangulation_vertex_3()
     : Vtds() {}

  Triangulation_vertex_3(const Point & p)
    :  Vtds(p) {}

  Triangulation_vertex_3(const Point & p, Cell_handle c)
    :  Vtds(p, &(*c)) {}

  Triangulation_vertex_3(Cell_handle c)
    :  Vtds(&(*c)) {}

  void set_cell(Cell_handle c)
  {
    Vtds::set_cell(&(*c));
  }

  Cell_handle cell() const
  {
    return (Cell *) Vtds::cell();
  }

  Vertex_handle handle()
  {
    return Vertex_handle(this);
  }
};

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_VERTEX_3_H
