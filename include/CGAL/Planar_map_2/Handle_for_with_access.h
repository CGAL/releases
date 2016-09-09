// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Planar_map_2/Handle_for_with_access.h
// package       : Planar_map (5.113)
// revision      : 1.0
// revision_date : 27 Jun 2000 
// author(s)     : Oren Nechushtan
// coordinator   : Tel-Aviv University (Dan Halperin)
//
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_PLANAR_MAP_2_HANDLE_FOR_WITH_ACCESS_H
#define CGAL_PLANAR_MAP_2_HANDLE_FOR_WITH_ACCESS_H

#ifndef CGAL_HANDLE_FOR_H
#include <CGAL/Handle_for.h>
#endif

namespace CGAL {

template <class T,
          class Allocator_ = CGAL_ALLOCATOR(T) >
class Handle_for_with_access : public Handle_for<T, Allocator_>
{
  public:
  Handle_for_with_access(const T& rc) : 
    Handle_for<T, Allocator_>(rc){}
  Handle_for_with_access() : Handle_for<T, Allocator_>(){}
  Handle_for_with_access( const Handle_for_with_access& h) : 
    Handle_for<T, Allocator_>(h){}
  
  const T* pointer() const {return Ptr();}

  T* pointer() {return ptr();}
  
};

} // namespace CGAL
#endif // CGAL_PLANAR_MAP_2_HANDLE_FOR_WITH_ACCESS_H












