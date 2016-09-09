// Copyright (c) 1997  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Planar_map/include/CGAL/Pm_point_location_base.h,v $
// $Revision: 1.4 $ $Date: 2003/09/18 10:24:34 $
// $Name: current_submission $
//
// Author(s)     : Iddo Hanniel <hanniel@math.tau.ac.il>
//                 Oren Nechushtan <theoren@math.tau.ac.il>
#ifndef CGAL_PM_POINT_LOCATION_BASE_H
#define CGAL_PM_POINT_LOCATION_BASE_H

#ifndef CGAL_PM_BOUNDING_BOX_BASE_H
#include <CGAL/Pm_bounding_box_base.h>
#endif

CGAL_BEGIN_NAMESPACE


////////////////////////////////////////////////////////////////////
//               ABSTRACT BASE CLASS OF STRATEGY
//////////////////////////////////////////////////////////////////

template <class Planar_map_>
class Pm_point_location_base {
public:
  typedef Planar_map_ Planar_map;
  typedef typename Planar_map::Traits Traits;
  typedef typename Planar_map::Locate_type Locate_type;
  typedef typename Planar_map::Ccb_halfedge_circulator 
    Ccb_halfedge_circulator;
  typedef typename Planar_map::Halfedge_handle Halfedge_handle;
  typedef typename Planar_map::Halfedge_iterator Halfedge_iterator;
  typedef typename Planar_map::Halfedge Halfedge;
  typedef std::vector<Halfedge_handle> Halfedge_handle_container;
  typedef typename Halfedge_handle_container::iterator 
                                        Halfedge_handle_iterator;
  typedef typename Traits::X_curve X_curve;
//  typedef typename Traits::X_curve_iterator X_curve_iterator;
  typedef typename Traits::Point Point;
  typedef Pm_bounding_box_base<Planar_map> Bounding_box;
  typedef typename Bounding_box::Token Token;
  
  Pm_point_location_base() {}
  
  virtual void init(Planar_map& pmp, Traits& tr) = 0;
  virtual ~Pm_point_location_base() {}
  
  virtual void insert(Halfedge_handle h,const X_curve& cv) = 0;  
  //h is the handle in which the curveis heald in the pm.
  
  
  /* Ignores the bounding box */
  virtual Halfedge_handle locate(const Point& p, Locate_type& lt) const = 0;
  /* Applies the bounding box */
  virtual Halfedge_handle locate(const Point& p, Locate_type& lt)
  {
    return locate(p,lt);
  }
  /* Ignores the bounding box */
  virtual Halfedge_handle vertical_ray_shoot(const Point& p, Locate_type& lt, 
                                             bool up) const = 0;
  /* Applies the bounding box */
  virtual Halfedge_handle vertical_ray_shoot(const Point& p, Locate_type& lt, 
					     bool up)
  {
    return vertical_ray_shoot(p,lt,up);
  }
  //the function is called after the combinatoric split
  //cv is the original curve , e1 e2 are the new halfedges returned 
  virtual void split_edge(const X_curve &cv,
                          Halfedge_handle e1,
                          Halfedge_handle e2
                          //additions by iddo for arrangement
                          ,const X_curve& cv1, const X_curve& cv2
                          //end additions
                          ) = 0;
  
  
  //called after combinatoric merge
  //e is the new edge cv1,cv2 are the original curves
  virtual void merge_edge(const X_curve &cv1,
                          const X_curve &cv2,
                          Halfedge_handle e 
                          //additions by iddo for arrangement
                          ,const X_curve& cv
                          //end additions
                          ) = 0; 
  
  //called before combinatoric deletion
  virtual void remove_edge(Halfedge_handle e) = 0;

  // - undocumented functions -
  virtual void remove_edge(const Halfedge_handle_iterator&,
		const Halfedge_handle_iterator&) {};
  virtual void clear() {};
  virtual void update(const Halfedge_handle_iterator&,
                      const Halfedge_handle_iterator&,
                      const Token& token)
  { token.rebuild_bounding_box(this); };
  // Should changed to = 0 in the near future.
  // --------------------------  

  virtual const Traits* get_traits() const = 0;
  
#ifdef CGAL_PM_DEBUG
  virtual void debug() = 0;
#endif
  
};


CGAL_END_NAMESPACE

#endif //CGAL_PM_POINT_LOCATION_BASE_H
