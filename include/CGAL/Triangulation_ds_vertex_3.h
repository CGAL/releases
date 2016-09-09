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
// file          : include/CGAL/Triangulation_ds_vertex_3.h
// package       : Triangulation_3 (1.83)
// revision      : $Revision: 1.21 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// vertex of a combinatotial triangulation of any dimension <=3

#ifndef CGAL_TRIANGULATION_DS_VERTEX_3_H
#define CGAL_TRIANGULATION_DS_VERTEX_3_H

#include <CGAL/basic.h>
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

  // CONSTRUCTORS

  Triangulation_ds_vertex_3()
    : Vb()
  { set_order_of_creation(); }
    
  Triangulation_ds_vertex_3(const Point & p)
    :  Vb(p)
  { set_order_of_creation(); }
    
  Triangulation_ds_vertex_3(const Point & p, Cell * c)
    :  Vb(p, c)
  { set_order_of_creation(); }

  Triangulation_ds_vertex_3(Cell * c)
    :  Vb(c)
  { set_order_of_creation(); }

  // ACCESS

  Cell* cell() const
  {
    return (Cell *) (Vb::cell());
  }
    
  // SETTING

  void set_cell(Cell* c)
  {
    Vb::set_cell(c);
  }

  // CHECKING

  bool is_valid(bool verbose = false, int level = 0) const;

  // used for symbolic perturbation in remove_vertex for Delaunay
  // undocumented
  void set_order_of_creation()
  {
    static int nb=-1; 
    _order_of_creation = ++nb;
  }

  int get_order_of_creation() const
  {
      return _order_of_creation;
  }
  
private:
  int _order_of_creation;
};

template < class VH>
class Vertex_tds_compare_order_of_creation {
public:
  bool operator()(VH u, VH v) const {
    return u->get_order_of_creation() < v->get_order_of_creation();
  }
};

template <class Vb, class Cb >
bool
Triangulation_ds_vertex_3<Vb,Cb>::is_valid
(bool verbose, int level) const
{
  bool result = Vb::is_valid(verbose,level) && cell()->has_vertex(this);
  if ( ! result ) {
    if ( verbose )
      std::cerr << "invalid vertex" << std::endl;
    CGAL_triangulation_assertion(false);
  }
  return result;
}

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_DS_VERTEX_3_H
