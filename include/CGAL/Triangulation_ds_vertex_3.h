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
// file          : include/CGAL/Triangulation_ds_vertex_3.h
// package       : Triangulation_3 (1.114)
// revision      : $Revision: 1.27 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// vertex of a combinatorial triangulation of any dimension <=3

#ifndef CGAL_TRIANGULATION_DS_VERTEX_3_H
#define CGAL_TRIANGULATION_DS_VERTEX_3_H

#include <CGAL/basic.h>
#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template <class Tds>
class  Triangulation_ds_vertex_3 
  : public Tds::Vertex_base
{
  typedef typename Tds::Vertex_base        Vb;
  typedef typename Tds::Vertex_handle      Vertex_handle;
  typedef typename Tds::Cell_handle        Cell_handle;
public:
  typedef typename Tds::Vertex      Vertex;
  typedef typename Tds::Cell        Cell;

  Triangulation_ds_vertex_3()
    : Vb()
  { set_order_of_creation(); }
    
  Cell_handle cell() const
  {
    return (Cell *) (Vb::cell());
  }
    
  void set_cell(const Cell_handle c)
  {
    Vb::set_cell(&*c);
  }

  bool is_valid(bool verbose = false, int level = 0) const;

  // used for symbolic perturbation in remove_vertex for Delaunay
  // undocumented
  int get_order_of_creation() const
  {
      return _order_of_creation;
  }

  Vertex_handle handle() const
  {
      return const_cast<Vertex*>(this);
  }

private:
  void set_order_of_creation()
  {
    _order_of_creation = ++nb;
  }

  int _order_of_creation;

  static int nb;
};

template <class Tds>
int Triangulation_ds_vertex_3<Tds>::nb;


template < class VH>
class Vertex_tds_compare_order_of_creation {
public:
  bool operator()(VH u, VH v) const {
    return u->get_order_of_creation() < v->get_order_of_creation();
  }
};

template <class Tds>
bool
Triangulation_ds_vertex_3<Tds>::is_valid
(bool verbose, int level) const
{
  bool result = Vb::is_valid(verbose,level) && cell()->has_vertex(handle());
  if ( ! result ) {
    if ( verbose )
      std::cerr << "invalid vertex" << std::endl;
    CGAL_triangulation_assertion(false);
  }
  return result;
}

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_DS_VERTEX_3_H
