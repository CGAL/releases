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
// file          : include/CGAL/polygon_function_objects.h
// package       : Partition_2 (1.18)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/03/12 10:49:31 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Function objects for testing polygon properties
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef POLYGON_FUNCTION_OBJECTS_H
#define POLYGON_FUNCTION_OBJECTS_H

#include<CGAL/is_y_monotone_2.h>

namespace CGAL {

template <class Traits>
class Is_vacuously_valid 
{
  public:

     Is_vacuously_valid(Traits ) {}

     template <class ForwardIterator>
     bool operator()(ForwardIterator, ForwardIterator)
     {  return true; }

};


template <class Traits>
class Is_convex_2
{
  public:
     Is_convex_2(Traits t): traits(t) {}
  
     template <class ForwardIterator>
     bool operator()(ForwardIterator first, ForwardIterator last)
     {  return is_convex_2(first, last, traits); }

  private:
     Traits  traits;
};

template <class Traits>
class Is_y_monotone_2
{
  public:
     Is_y_monotone_2(Traits t): traits(t) {}
  
     template <class ForwardIterator>
     bool operator()(ForwardIterator first, ForwardIterator last)
     {  return is_y_monotone_2(first, last, traits); }

  private:
     Traits  traits;
};

}

#endif // POLYGON_FUNCTION_OBJECTS_H
