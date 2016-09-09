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
// file          : include/CGAL/is_degenerate_polygon_2.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.1 $
// revision_date : $Date: 2002/03/19 12:25:52 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: test for degenerate polygon with collinear vertices 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IS_DEGENERATE_POLYGON_2_H
#define CGAL_IS_DEGENERATE_POLYGON_2_H

namespace CGAL {

// tests if a sequence of points represents a degenerate polygon (i.e.
// one of zero area)
template<class BidirectionalIterator, class Traits>
bool 
is_degenerate_polygon_2(BidirectionalIterator first, 
                        BidirectionalIterator last,
                        const Traits& traits)
{
   if (first == last) return true;

   BidirectionalIterator prev = last;
   prev--;
   BidirectionalIterator curr = first;
   BidirectionalIterator next = first;
   next++;

   // fewer than three vertices
   if (prev == first) return true; 
   if (next == last) return true; 

   typedef typename Traits::Orientation_2                Orientation_2;

   Orientation_2 orientation = traits.orientation_2_object();

   while (curr != last)
   {
     if (orientation(*prev, *curr, *next) != COLLINEAR)
        return false;

     prev++;
     if (prev == last)
        prev = first;
     next++;   
     if (next == last)
       next = first;
     curr++;
   }
   return true;

}

template<class InputIterator>
bool 
is_degenerate_polygon_2(InputIterator first, InputIterator last)
{
   if (first == last) return true;

   typedef typename std::iterator_traits<InputIterator>::value_type Point_2;
   typedef typename Kernel_traits<Point_2>::Kernel  K;
   return is_degenerate_polygon_2(first, last, K());
}

}

#endif // CGAL_IS_DEGENERATE_POLYGON_2_H
