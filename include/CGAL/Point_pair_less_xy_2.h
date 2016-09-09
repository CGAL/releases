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
// file          : include/CGAL/Point_pair_less_xy_2.h
// package       : Partition_2 (1.18)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/01/12 12:58:44 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Lexicographical ordering of a pair of points
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_POINT_PAIR_LESS_XY_2_H
#define CGAL_POINT_PAIR_LESS_XY_2_H

#include <utility>

namespace CGAL {

//
// Given two pairs of points determine their lexicographical order by first
// comparing the first points lexicographically and then the second points if
// the first are equal
//
template <class Traits>
class Point_pair_less_xy_2
{
   typedef typename Traits::Point_2           Point_2;
   typedef std::pair<Point_2, Point_2>        Point_pair;
   typedef typename Traits::Less_xy_2         Less_xy_2;

   public:
     Point_pair_less_xy_2() : _less_xy_2(Traits().less_xy_2_object())
     { }
     

     bool 
     operator()(const Point_pair& p, const Point_pair& q) const
     { 
        if (_less_xy_2(p.first, q.first))
            return true;
        else if (_less_xy_2(q.first, p.first))
            return false;
        else if (_less_xy_2(p.second, q.second))
            return true;
        else
            return false;
     }

   private:
      Less_xy_2 _less_xy_2;
};

}

#endif // CGAL_POINT_PAIR_LESS_XY_H

