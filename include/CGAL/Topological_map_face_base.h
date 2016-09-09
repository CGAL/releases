// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// file          : include/CGAL/Topological_map_face_base.h
// package       : Planar_map (5.113)
// author(s)     : ?
// coordinator   : ?
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef  CGAL_TOPOLOGICAL_MAP_FACE_BASE_H
#define  CGAL_TOPOLOGICAL_MAP_FACE_BASE_H

#ifndef CGAL_HALFEDGEDS_FACE_BASE_H
#include <CGAL/HalfedgeDS_face_base.h>
#endif

#include <list>

CGAL_BEGIN_NAMESPACE

template < class Refs >
class Topological_map_face_list_base : 
  public HalfedgeDS_face_base<Refs, Tag_true>
{
public:
  typedef HalfedgeDS_face_base<Refs, Tag_true>   Base;
  
  // Handles have to explicitly repeated, although they are derived
  typedef typename Base::Vertex_handle           Vertex_handle;
  typedef typename Base::Halfedge_handle         Halfedge_handle;
  typedef typename Base::Face_handle             Face_handle;
  typedef typename Base::Vertex_const_handle     Vertex_const_handle;
  typedef typename Base::Halfedge_const_handle   Halfedge_const_handle;
  typedef typename Base::Face_const_handle       Face_const_handle;
  typedef typename Base::Vertex                  Vertex;
  typedef typename Base::Halfedge                Halfedge;
  
  // Supported options by HDS.
  typedef typename Base::Supports_face_halfedge Supports_face_halfedge;
  
  // Circulator category.
  typedef typename Halfedge::Supports_halfedge_prev  Supports_prev;
  
public:
  // Circulator category.
  // SHAI:
  //typedef Polyhedron_circulator_traits<Supports_prev> Ctr;
  //typedef typename Ctr::iterator_category circulator_category;

  // SHAI: figure out wether you realy want these here
  // and if so, replace names.

  // Circulators around a vertex and around a facet.
  //typedef I_Polyhedron_facet_circ< Halfedge_handle, circulator_category>
  //Halfedge_around_facet_circulator;
  
  //typedef I_Polyhedron_vertex_circ< Halfedge_handle, circulator_category>
  //Halfedge_around_vertex_circulator;
  
  //typedef I_Polyhedron_facet_circ<
  //Halfedge_const_handle,
  //  circulator_category>       Halfedge_around_facet_const_circulator;
  
  //typedef I_Polyhedron_vertex_circ<
  //Halfedge_const_handle,
  //  circulator_category>      Halfedge_around_vertex_const_circulator;
  
  //typedef typename Halfedge_around_vertex_circulator::size_type
  //size_type;
  //typedef typename Halfedge_around_vertex_circulator::difference_type
  //difference_type;
  
public:
  // Hole types
  typedef std::list<Halfedge_handle> Holes_container; 
  
  typedef Holes_container::iterator Holes_iterator; 
  typedef Holes_container::const_iterator Holes_const_iterator;
  
public:
  // We need to repeat the constructors here.
  Topological_map_face_list_base() : holes() {}
  // SHAI: Rewrite copy ctor to copy holes
  //Topological_map_face_list_base( const Base& b) : Base(b) : {}
  
  // New Access Functions (not provided in FacetBase).
  
  /*
  Halfedge_around_facet_circulator facet_begin() {
    // a circulator of halfedges around the facet (counterclockwise).
    return Halfedge_around_facet_circulator( halfedge());
  }
  Halfedge_around_facet_const_circulator facet_begin() const {
    // a circulator of halfedges around the facet (counterclockwise).
    return Halfedge_around_facet_const_circulator( halfedge());
  }
  
  size_type size() const {
    return circulator_size( facet_begin());
  }
  */

  // No longer hidden. Now the restricted version with precondition.
  // sets incident halfedge to h. Precondition: h is incident, i.e.,
  // h->face() == v.
  void  set_halfedge( Halfedge_handle hh) {
    CGAL_assertion( &*(hh->facet()) == this);
    Base::set_halfedge(hh);
  }
  
private:
  Holes_container holes;
public:
  Holes_iterator       holes_begin()       { return holes.begin(); }
  Holes_iterator       holes_end()         { return holes.end();   }

  Holes_const_iterator holes_begin() const { return holes.begin(); }
  Holes_const_iterator holes_end()   const { return holes.end();   }

  void add_hole  (Halfedge_handle hh)      { holes.push_back(hh);  }
  void erase_hole(Holes_iterator hit)      { holes.erase(hit);     }
  void erase_holes(Holes_iterator h_begin, Holes_iterator h_end)
                                           { holes.erase(h_begin, h_end); }
};

CGAL_END_NAMESPACE

#endif // CGAL_I_TOPOLOGICAL_MAP_FACE_BASE_H
