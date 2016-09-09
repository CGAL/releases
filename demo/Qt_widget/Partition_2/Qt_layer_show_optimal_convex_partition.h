// ============================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// file          : include/CGAL/IO/Qt_layer_show_optimal_convex_partition.h
// package       : Qt_widget
// author(s)     : Radu Ursu
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// coordinator   : Laurent Rineau
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_QT_LAYER_SHOW_OPTIMAL_CONVEX_H
#define CGAL_QT_LAYER_SHOW_OPTIMAL_CONVEX_H

#include <CGAL/IO/Qt_widget_layer.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/partition_2.h>


namespace CGAL {

template <class T>
class Qt_layer_show_optimal_convex : public Qt_widget_layer
{
public:
  typedef typename T::FT	      FT;
  typedef CGAL::Cartesian<FT>	      K;
  typedef CGAL::Partition_traits_2<K> Traits;


  Qt_layer_show_optimal_convex(T &p) : polygon(p)
  {};
  void draw()
  {
    optimal_convex.clear();
    Traits  partition_traits;
    
    CGAL::optimal_convex_partition_2(polygon.vertices_begin(), 
                                       polygon.vertices_end(),
                           std::back_inserter(optimal_convex),
                                            partition_traits);    
    
    std::list<T>::const_iterator p_it;
    for(p_it = optimal_convex.begin(); p_it != optimal_convex.end(); p_it++)
    {
      *widget << CGAL::YELLOW; 
      *widget << *p_it;
    }
    
  };
private:
  T		&polygon;
  std::list<T>	optimal_convex;
};//end class 

} // namespace CGAL

#endif // CGAL_QT_LAYER_SHOW_OPTIMAL_CONVEX_H
