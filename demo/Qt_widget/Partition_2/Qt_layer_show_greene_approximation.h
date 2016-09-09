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
// file          : include/CGAL/IO/Qt_layer_show_greene_approximation.h
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

#ifndef CGAL_QT_LAYER_SHOW_GREEN_APPROXIMATION_H
#define CGAL_QT_LAYER_SHOW_GREEN_APPROXIMATION_H

#include <CGAL/IO/Qt_widget_layer.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/partition_2.h>


namespace CGAL {

template <class T>
class Qt_layer_show_greene_approx : public Qt_widget_layer
{
public:
  typedef typename T::FT	      FT;
  typedef CGAL::Cartesian<FT>	      K;
  typedef CGAL::Partition_traits_2<K> Traits;


  Qt_layer_show_greene_approx(T &p) : polygon(p)
  {};
  void draw()
  {
    if(polygon.size() > 2)
      assert( polygon.is_counterclockwise_oriented());

    greene_approx_polys.clear();
    Traits  partition_traits;
    
    CGAL::greene_approx_convex_partition_2(
		polygon.vertices_begin(), 
		polygon.vertices_end(),
		std::back_inserter(greene_approx_polys),
		partition_traits);
    
    std::list<T>::const_iterator p_it;
    for(p_it = greene_approx_polys.begin(); 
		p_it != greene_approx_polys.end(); p_it++)
    {
      *widget << CGAL::GREEN; 
      *widget << *p_it;
    }
    
  };
private:
  T		&polygon;
  std::list<T>	greene_approx_polys;
};//end class 

} // namespace CGAL

#endif // CGAL_QT_WIDGET_GET_SEGMENT_H
