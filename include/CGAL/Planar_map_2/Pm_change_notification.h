// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Planar_map_2/Pm_change_notification.h
// package       : Planar_map (5.113)
// author(s)     : Eyal flato
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_PM_CHANGE_NOTIFICATION_H
#define CGAL_PM_CHANGE_NOTIFICATION_H

//#ifndef CGAL_PLANAR_MAP_MISC_H
//#include <CGAL/Planar_map_2/Planar_map_misc.h>
//#endif

CGAL_BEGIN_NAMESPACE

template<class Planar_map_>
class Pm_change_notification
{
public:
  typedef Planar_map_ Planar_map;
  typedef typename Planar_map::Traits Traits;
  
  virtual void add_edge(const typename Traits::X_curve &, 
                        typename Planar_map::Halfedge_handle, 
                        bool /* original_direction */, bool overlap = false)
  {
      (void) overlap;
  }

  virtual void split_edge(typename Planar_map::Halfedge_handle /* org */,
                          typename Planar_map::Halfedge_handle /* new */,
                          const typename Traits::X_curve &,
                          const typename Traits::X_curve &)
  {
  }

  //  virtual void merge_edge(typename Planar_map::Halfedge_handle orig_edge, 
  //                          typename Planar_map::Halfedge_handle new_edge,
  //                          const typename Traits::X_curve & c)
  //    {
  //    }

  //   virtual void remove_edge(typename Planar_map::Halfedge_handle orig_edge)
  //    {
  //    }

  virtual void split_face(typename Planar_map::Face_handle /* org */, 
                          typename Planar_map::Face_handle /* new */)
  {
  }

  virtual void add_hole(typename Planar_map::Face_handle /* in_face */, 
                        typename Planar_map::Halfedge_handle /* new_hole */)
  {
  }

  virtual const typename Traits::X_curve &
  edge_support_curve(typename Planar_map::Halfedge_handle edge)
  {
    return edge->curve();
  }

  virtual bool have_support_curve()
  {
    return false;
  }

};

CGAL_END_NAMESPACE

#endif  // PM_CHANGE_NOTIFICATION
