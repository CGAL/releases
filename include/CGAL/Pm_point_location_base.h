// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Pm_point_location_base.h
// package       : pm (2.052)
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
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef CGAL_PM_POINT_LOCATION_BASE_H
#define CGAL_PM_POINT_LOCATION_BASE_H

#ifndef CGAL_PM_CONFIG_H
#include <CGAL/Pm_config.h>
#endif

////////////////////////////////////////////////////////////////////
//               ABSTRACT BASE CLASS OF STRATEGY
//////////////////////////////////////////////////////////////////

template <class Planar_map>
class CGAL_Pm_point_location_base {
public:
  typedef typename Planar_map::Traits Traits;
  typedef typename Planar_map::Locate_type Locate_type;
  typedef typename Planar_map::Halfedge_handle Halfedge_handle;

  typedef typename Traits::X_curve X_curve;
  typedef typename Traits::Point Point;


  CGAL_Pm_point_location_base() {}

  virtual void init(Planar_map& pmp, Traits& tr) = 0;
  virtual ~CGAL_Pm_point_location_base() {}

  virtual void insert(Halfedge_handle h
                      //additions by iddo for arrangement
                      ,const X_curve& cv
                      //end additions
                      ) = 0;  //h is the handle in which the curveis heald in the pm.

  virtual Halfedge_handle locate(const Point& p, Locate_type& lt) = 0;
  virtual Halfedge_handle vertical_ray_shoot(const Point& p, Locate_type& lt, bool up) = 0;

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
};


#endif //CGAL_PM_POINT_LOCATION_BASE_H














