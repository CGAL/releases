// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/Pm_point_location_base.h
// package       : pm (4.20)
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
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef CGAL_PM_POINT_LOCATION_BASE_H
#define CGAL_PM_POINT_LOCATION_BASE_H

CGAL_BEGIN_NAMESPACE


////////////////////////////////////////////////////////////////////
//               ABSTRACT BASE CLASS OF STRATEGY
//////////////////////////////////////////////////////////////////

template <class Planar_map>
class Pm_point_location_base {
public:
  typedef typename Planar_map::Traits Traits;
  typedef typename Planar_map::Locate_type Locate_type;
  typedef typename Planar_map::Halfedge_handle Halfedge_handle;

  typedef typename Traits::X_curve X_curve;
  typedef typename Traits::Point Point;


  Pm_point_location_base() {}

  virtual void init(Planar_map& pmp, Traits& tr) = 0;
  virtual ~Pm_point_location_base() {}

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

#ifdef CGAL_PM_DEBUG
 virtual void debug() = 0;
#endif

};


CGAL_END_NAMESPACE

#endif //CGAL_PM_POINT_LOCATION_BASE_H














