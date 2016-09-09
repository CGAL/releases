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
// file          : include/CGAL/Indirect_less_xy_2.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.1 $
// revision_date : $Date: 2001/07/10 14:17:31 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Given iterators to two points, compares them using Less_xy
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_INDIRECT_LESS_XY_2_H
#define CGAL_INDIRECT_LESS_XY_2_H

namespace CGAL {

template <class Traits>
class Indirect_less_xy_2 
{
   public:
     typedef typename Traits::Less_xy_2     Less_xy_2;

     Indirect_less_xy_2() : _less_xy_2(Traits().less_xy_2_object()) 
     { }
     
     template <class Iterator>
     bool 
     operator()(Iterator p, Iterator q) const
     { 
        return _less_xy_2(*p, *q);
     }

   private:
     Less_xy_2 _less_xy_2;
};

}

#endif // CGAL_INDIRECT_LESS_XY_2_H

