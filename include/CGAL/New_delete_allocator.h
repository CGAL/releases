// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// file          : include/CGAL/New_delete_allocator.h
// package       : Kernel_basic (3.90)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/10/31 14:34:01 $
// author(s)     : Sylvain Pion
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_NEW_DELETE_ALLOCATOR_H
#define CGAL_NEW_DELETE_ALLOCATOR_H

#include <cstddef> 

template <class T>
class New_delete_allocator
{
 public:
  typedef std::size_t      size_type;
  typedef std::ptrdiff_t   difference_type;
  typedef T                value_type;
  typedef T*               pointer;
  typedef const T*         const_pointer;
  typedef T&               reference;
  typedef const T&         const_reference;

  template <class U> struct rebind { typedef New_delete_allocator<U> other; };

  New_delete_allocator() {}

  pointer
  allocate(size_type, const_pointer = 0)
  { return static_cast<pointer>(0); }

  void
  deallocate(pointer, size_type) {}

  pointer
  address(reference)
  { return static_cast<pointer>(0); }

  const_pointer
  address(const_reference)
  { return static_cast<const_pointer>(0); }

  template <class U>
  void
  construct(U*& ptr, const U& ref)
  { ptr = new U(ref); }

  void
  destroy(pointer p)
  { delete p; }
  // p should have an appropriate type
  // That's why we need the parameterization
  // T should have a virtual destructor

  size_type
  max_size() const
  { return 0; }
};

#endif // CGAL_NEW_DELETE_ALLOCATOR_H
