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
// file          : include/CGAL/is_y_monotone_2.h
// package       : Partition_2 (1.18)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/01/19 10:08:42 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: y-monotonicity testing for polygon
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IS_Y_MONOTONE_2_H
#define CGAL_IS_Y_MONOTONE_2_H

#include <CGAL/circulator.h>
#include <CGAL/ch_selected_extreme_points_2.h>
#include <iterator>
#include <list>

namespace CGAL {

template<class InputIterator, class Traits>
bool 
is_y_monotone_2(InputIterator first, InputIterator last,
                const Traits& traits)
{
   typedef typename Traits::Point_2                  Point_2;
   typedef typename Traits::Less_yx_2                Less_yx_2;
   typedef std::list<Point_2>                        Vertex_list;
   typedef typename Vertex_list::iterator            I;
   typedef Circulator_from_iterator<I>               Circulator;

   Vertex_list  polygon(first, last);
   I n_point_ref;
   I s_point_ref;

   // find the extreme north and south points
   ch_n_point(polygon.begin(), polygon.end(), n_point_ref, traits);
   ch_s_point(polygon.begin(), polygon.end(), s_point_ref, traits);

   Circulator north_c(polygon.begin(), polygon.end(), n_point_ref);
   Circulator south_c(polygon.begin(), polygon.end(), s_point_ref);

   Less_yx_2 less_yx = traits.less_yx_2_object();

   Circulator prev_c = south_c;
   Circulator c = south_c;

   for (c++; c != north_c; c++)
   {
      if (!less_yx(*prev_c, *c)) return false;
      prev_c = c;
   }

   prev_c = north_c;
   c = north_c;
   for (c++; c != south_c; c++)
   {
      if (!less_yx(*c, *prev_c)) return false;
      prev_c = c;
   }
   return true;
}

template<class InputIterator>
bool 
is_y_monotone_2(InputIterator first, InputIterator last)
{
   typedef typename std::iterator_traits<InputIterator>::value_type Point_2;
   return CGAL_is_y_monotone_2(first, last, reinterpret_cast<Point_2*>(0));
}

template<class InputIterator, class R>
bool 
CGAL_is_y_monotone_2(InputIterator first, InputIterator last, Point_2<R>*)
{
   return is_y_monotone_2(first, last, R());
}


}

#endif // CGAL_IS_Y_MONOTONE_2_H
