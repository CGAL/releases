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
// file          : include/CGAL/random_polygon_2.h
// package       : Generator (2.40)
// chapter       : Geometric Object Generators
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/07/12 18:31:00 $
//
// author(s)     : Susan Hert
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// implementation: Random Simple Polygons
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_RANDOM_POLYGON_2_H
#define CGAL_RANDOM_POLYGON_2_H

#include <list>
#include <set>
#include <vector>
#include <assert.h>
#include <CGAL/Simplicity_sweep_2.h>
#include <CGAL/Random_polygon_traits_2.h>

namespace CGAL {

//
// Using the provided point generator, generates a set of n points and 
// produces  a simple polygon from the unique subset of points within this 
// set.
// 
// Each of the p possible simple polygons for the unique point set is 
// generated with probability greater than 0 but the polygons are not 
// generated with uniform probability.
//
template <class PointGenerator, class OutputIterator, class Traits>
OutputIterator random_polygon_2(int n,  OutputIterator result, 
                                const PointGenerator& pg, const Traits& traits)
{
   typedef typename Traits::Point_2           Point_2;
   typedef std::vector<Point_2>               Vertex_list;
   typedef typename Vertex_list::iterator     Iterator;

   std::pair<Iterator, Iterator>  reverse_range;
   Vertex_list  vertices;

   copy_n_unique(pg, n, std::back_inserter(vertices), traits);
   CGAL_assertion(!duplicate_points(vertices.begin(), vertices.end(), traits));

   std::random_shuffle(vertices.begin(), vertices.end());

   bool changing = true;

   Simplicity_sweep_2<Iterator,Traits>  S(traits);

   while (changing)
   {
      changing = S.sweep(vertices.begin(), vertices.end(), reverse_range);
     
     // gets rid of an intersection by reversing the order of the vertices 
     // between the endpoints of two intersecting edges 
      if (changing)
         std::reverse(reverse_range.first, ++reverse_range.second);
   }

   if (orientation_2(vertices.begin(), vertices.end()) == CLOCKWISE)
      std::reverse(vertices.begin(), vertices.end());


   CGAL_assertion(is_simple_2(vertices.begin(), vertices.end()));
   for (Iterator it = vertices.begin(); it != vertices.end(); it++)
   {
      *result = *it;
      result++;
   }
   return result;
}

template <class PointGenerator, class OutputIterator>
inline
OutputIterator random_polygon_2( int n,  OutputIterator result, 
                                 const PointGenerator& pg )
{
   typedef typename std::iterator_traits<PointGenerator>::value_type  Point_2;
   return _random_polygon_2(n, result, pg, reinterpret_cast<Point_2*>(0));
}

template <class PointGenerator, class OutputIterator, class R>
inline
OutputIterator _random_polygon_2( int n,  OutputIterator result, 
                                 const PointGenerator& pg, Point_2<R>*)
{
   return random_polygon_2(n, result, pg, Random_polygon_traits_2<R>());
}


template <class ForwardIterator, class Traits>
bool duplicate_points(ForwardIterator first, ForwardIterator beyond, 
                      const Traits& )
{
   typedef typename Traits::Point_2      Point_2;
   typedef typename Traits::Less_yx_2    Less_yx_2;
   std::set<Point_2,Less_yx_2>  point_set;
   int i = 0;
   for (; first != beyond; first++, i++)
      if (!(point_set.insert(*first)).second) return true;
   return false;
}

template <class ForwardIterator>
bool duplicate_points(ForwardIterator first, ForwardIterator beyond)
{
   typedef typename std::iterator_traits<ForwardIterator>::value_type  Point_2;
   return _duplicate_points(first, beyond, reinterpret_cast<Point_2*>(0));
}

template <class ForwardIterator, class R>
bool _duplicate_points(ForwardIterator first, ForwardIterator beyond,
                       Point_2<R>*)
{
   return duplicate_points(first, beyond, Random_polygon_traits_2<R>());
}

// Copies the first n points from the input iterator to the output iterator,
// removing any duplicates.  Thus fewer than n points may be inserted into
// the output iterator.
template <class InputIterator, class Size, class OutputIterator, class Traits>
OutputIterator copy_n_unique(InputIterator first, Size n, 
                             OutputIterator result,
                             const Traits& )
{
   typedef typename Traits::Point_2    Point_2;
   typedef typename Traits::Less_yx_2  Less_yx_2;

   std::set<Point_2, Less_yx_2>    sorted_point_set;
   int i;
   for (i = 0; i < n; i++)
   {
      if (sorted_point_set.insert(*first).second)
      {
          *result = *first;
          result++;
      }   
      first++;
   }
   return result;
}

template <class InputIterator, class Size, class OutputIterator>
inline
OutputIterator copy_n_unique(InputIterator first, Size n, 
                             OutputIterator result)
{
   typedef typename std::iterator_traits<InputIterator>::value_type  Point_2;
   return _copy_n_unique(first, n, result, reinterpret_cast<Point_2*>(0));
}

template <class InputIterator, class Size, class OutputIterator, class R>
inline
OutputIterator _copy_n_unique(InputIterator first, Size n, 
                              OutputIterator result, Point_2<R>*)
{
   return copy_n_unique(first, n, result, Random_polygon_traits_2<R>());
}

} // namespace CGAL

#endif
