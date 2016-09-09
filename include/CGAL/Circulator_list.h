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
// file          : include/CGAL/Circulator_list.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/01/19 10:08:38 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: List of circulators
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_CIRCULATOR_LIST_H
#define CGAL_CIRCULATOR_LIST_H

#include <list>
#include <iostream>

namespace CGAL {

template <class Circulator>
class Circulator_list : public std::list<Circulator> 
{

public:
  Circulator_list() 
  {}

  Circulator_list(Circulator first) 
  {
      if (first == NULL) return;

      Circulator current = first;
      do 
      {
         push_back(current);
      } while (++current != first);
  }
};

template <class C>
std::ostream& operator<<(std::ostream& os, const Circulator_list<C>& c)
{
     typename Circulator_list<C>::const_iterator current;
     for (current = c.begin(); current != c.end(); current++)
     {
        os << **current << " ";
     }
     return os;
}
}

#endif // CGAL_CIRCULATOR_LIST_H
