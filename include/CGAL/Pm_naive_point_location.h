// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/Pm_naive_point_location.h
// package       : Planar_map (5.113)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Iddo Hanniel
//                 Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_PM_NAIVE_POINT_LOCATION_H
#define CGAL_PM_NAIVE_POINT_LOCATION_H

#include <CGAL/Pm_point_location_base.h>
#include <CGAL/Planar_map_2/Planar_map_misc.h>

CGAL_BEGIN_NAMESPACE

////////////////////////////////////////////////////////
//NAIVE STRATEGY
////////////////////////////////////////////////////////

template <class Planar_map_>
class Pm_naive_point_location : public Pm_point_location_base<Planar_map_> {
public:
  typedef Planar_map_ Planar_map;
  typedef typename Planar_map::Traits Traits;
  typedef Pm_point_location_base<Planar_map> Base;
  typedef Pm_naive_point_location<Planar_map> Self;
  typedef typename Planar_map::Traits_wrap Traits_wrap;
  typedef typename Planar_map::Locate_type Locate_type;
  typedef typename Planar_map::Face_handle Face_handle;
  typedef typename Planar_map::Ccb_halfedge_circulator 
    Ccb_halfedge_circulator;
  typedef typename Planar_map::Halfedge_handle Halfedge_handle;
  typedef typename Planar_map::Halfedge_iterator Halfedge_iterator;
  typedef typename Planar_map::Halfedge Halfedge;
  typedef typename Planar_map::Vertex_handle Vertex_handle;
  typedef typename Traits::Point Point;
  typedef typename Traits::X_curve X_curve;
  typedef Pm_bounding_box_base<Planar_map> Bounding_box;
  typedef typename Base::Halfedge_handle_iterator Halfedge_handle_iterator;
  typedef typename Base::Token Token;

public:
  // Constructors
  Pm_naive_point_location() : 
    Pm_point_location_base<Planar_map>(),
    pm(0),
    traits(0) 
  {}

  Pm_naive_point_location(Planar_map * _pm,Traits_wrap * _traits) : 
    Pm_point_location_base<Planar_map>(), traits(_traits), pm(_pm) {}

  inline void init(Planar_map & pmp, Traits & tr) 
  {
    CGAL_precondition_msg(pm == NULL,
    "Point location instance should be uninitialized "
    "(Do not use the same instance for more than one map).");

    pm = &pmp;
    traits = (Traits_wrap*)(&tr);
  }
  
  inline void insert(Halfedge_handle, const X_curve &) {}
  
  Halfedge_handle locate(const Point & p, Locate_type & lt) const;
  Halfedge_handle locate(const Point & p, Locate_type & lt);
  
  Halfedge_handle vertical_ray_shoot(const Point & p,
                                     Locate_type & lt, bool up) const;
  Halfedge_handle vertical_ray_shoot(const Point & p,
                                     Locate_type & lt, bool up);
  
  inline void split_edge(const X_curve &,
                         Halfedge_handle, Halfedge_handle,
                         const X_curve &, const X_curve &) {}
  
  inline void merge_edge(const X_curve &, const X_curve &,
                         Halfedge_handle, const X_curve &) {}
  
  inline void remove_edge(Halfedge_handle) {}
  inline void remove_edge(const Halfedge_handle_iterator &,
                          const Halfedge_handle_iterator &) {};
  inline void clear() {}
  inline void update(const Halfedge_handle_iterator &,
                     const Halfedge_handle_iterator &,
                     const Token & token)
  { token.rebuild_bounding_box(this); }

public:
  inline const Bounding_box * get_bounding_box() const 
  {return pm->get_bounding_box();}
  inline const Traits* get_traits() const {return traits;}
  
protected:
  Halfedge_handle find_lowest(Vertex_handle v,
                              bool highest) const;
  
#ifdef CGAL_PM_DEBUG
  void debug(){}
#endif

protected:
  typedef const Self * cPLp;
  
protected:
  Planar_map * pm;
  Traits_wrap * traits;
};

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/Pm_naive_point_location.C>
#endif

#endif //CGAL_PM_NAIVE_POINT_LOCATION_H
