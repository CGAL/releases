// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

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
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/segment_intersection_points_2.h
// package       : Convex_hull_2 (3.34)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/12/11 14:00:54 $
// author(s)     : Stefan Schirra 
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef SEGMENT_INTERSECTION_POINTS_2_H
#define SEGMENT_INTERSECTION_POINTS_2_H

#include <CGAL/basic.h>
#include <CGAL/stl_extensions.h>
#include <iterator>

namespace CGAL {

/*
#include <CGAL/Segment_2_Segment_2_intersection.h>
template <class ForwardIterator, class OutputIterator, class R>
OutputIterator
si_brute_force(ForwardIterator first, ForwardIterator last,
                    OutputIterator result,
                    const R& )
{
  typedef Point_2<R>         Point;
  ForwardIterator inner, outer;
  Object i_obj;
  Point p;
  for ( outer = first; outer != last; ++outer)
      for ( inner = successor(outer); inner != last; ++inner)
      {
          i_obj = intersection( *outer, *inner);
          if ( assign( p, i_obj) )
              result++ = p;
      }
  return result;
}
*/

template <class ForwardIterator, class OutputIterator, class Traits>
OutputIterator
si_brute_force_II(ForwardIterator first, ForwardIterator last,
                  OutputIterator result,
                  const Traits& traits)
{
  typedef typename Traits::Point_2         Point;
  typedef typename Traits::Line_2          Line;
  typedef typename Traits::Orientation_2   Orientation;
  Orientation orientation = traits.orientation_2_object();

  for ( ForwardIterator outer = first; outer != last; ++outer)
      for ( ForwardIterator inner = successor(outer); inner != last; ++inner)
      {
          Point s1 = (*outer).source();
          Point e1 = (*outer).target();
          Point s2 = (*inner).source();
          Point e2 = (*inner).target();
          if ( (orientation( s1, e1, s2) != orientation( s1, e1, e2))
             &&(orientation( s2, e2, s1) != orientation( s2, e2, e1)))
          {
              Line l1( s1, e1);
              Line l2( s2, e2);
              result++ =  Point( l1.b()*l2.c() - l2.b()*l1.c(),
                                 l2.a()*l1.c() - l1.a()*l2.c(),
                                 l1.a()*l2.b() - l2.a()*l1.b());
          }
      }
  return result;
}

template <class ForwardIterator, class OutputIterator, class Traits>
OutputIterator
segment_intersection_points_2(ForwardIterator first, ForwardIterator last,
                              OutputIterator result,
                              const Traits& traits)
{ return si_brute_force_II( first, last, result, traits); }

template <class ForwardIterator, class OutputIterator, class Traits>
OutputIterator
segment_intersection_points_2(ForwardIterator first, ForwardIterator last,
                              OutputIterator result)
{
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    return segment_intersection_points_2( first, last, result, Kernel()); 
}

} // namespace CGAL

#endif // SEGMENT_INTERSECTION_POINTS_2_H
