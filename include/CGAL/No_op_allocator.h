// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : No_op_allocator.fw
// file          : include/CGAL/No_op_allocator.h
// package       : Kernel_basic (3.14)
// revision      : 3.14
// revision_date : 15 Sep 2000 
// author(s)     : Lutz Kettner
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_NO_OP_ALLOCATOR_H
#define CGAL_NO_OP_ALLOCATOR_H

template <class T>
class No_op_allocator
{
 public:
  typedef size_t      size_type;
  typedef ptrdiff_t   difference_type;
  typedef T           value_type;
  typedef T*          pointer;
  typedef const T*    const_pointer;
  typedef T&          reference;
  typedef const T&    const_reference;


  No_op_allocator() : Don_t_call(true) {}

  pointer
  allocate(size_type n, const_pointer = 0) { return static_cast<pointer>(0); }

  void
  deallocate(pointer p, size_type n) {}

  pointer
  address(reference r)
  { CGAL_precondition ( !Don_t_call ); return static_cast<pointer>(0); }

  const_pointer
  address(const_reference r)
  { CGAL_precondition ( !Don_t_call ); return static_cast<const_pointer>(0); }

  void
  construct(pointer p, const_reference r)
  { CGAL_precondition ( !Don_t_call ); }
  // It is the user responsibility to construct
  // the element, e.g. using new

  void
  destroy(pointer p)
  { delete p; }
  // p should have an appropriate type
  // That's why we need the parameterization
  // T should have a virtual destructor

  size_type
  max_size() const
  { return 0; }

 private:
  bool  Don_t_call;
};

#endif // CGAL_NO_OP_ALLOCATOR_H
