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
// file          : include/LEDA/allocator.h
// package       : LEDA (1.0.1)
// author(s)     : ?
// coordinator   : ?
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef LEDA_ALLOCATOR_H
#define LEDA_ALLOCATOR_H

#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 390009
#include <LEDA/REDEFINE_NAMES.h>
#endif


#include <CGAL/LEDA_basic.h>

// the following piece of code is programmed according to
// the C++ standard clause 20.4.1


template <class T> class leda_allocator;


// specialize for void:
template <> class leda_allocator<void> {
public:
  typedef void*       pointer;
  typedef const void* const_pointer;
  //  reference-to-void members are impossible.
  typedef void        value_type;
  template <class U> struct rebind { typedef leda_allocator<U> other; };
};

/*{\Manpage {leda_allocator} {T} {Memory Allocator} {A}}*/

template <class T>
class leda_allocator {

/*{\Mdefinition An instance |\Mvar| of the data type |\Mname| is
a memory allocator according to the \CC standard. |\Mname| is the
standard compliant interface to the LEDA memory management.}*/

public:
/*{\Mtypes 5}*/
/*{\Mtext Local types are |size_type|, |difference_type|, |value_type|,
|pointer|, |reference|, |const_pointer|, and |const_reference|.}*/

  typedef size_t      size_type;
  typedef ptrdiff_t   difference_type;
  typedef T           value_type;
  typedef T*          pointer;
  typedef const T*    const_pointer;
  typedef T&          reference;
  typedef const T&    const_reference;

  template <class T1> class rebind { public:
  /*{\Mtypemember allows the construction of a derived allocator:\\
     |\Mname::template rebind<T1>::other|\\ is the type
     |leda_allocator<T1>|. }*/
    typedef leda_allocator<T1> other;
  };


/*{\Mcreation 4.5}*/

  leda_allocator() {}
  /*{\Mcreate introduces a variable |\Mvar| of type |\Mname|. }*/

  template <class TO> 
  leda_allocator(const leda_allocator<TO>&) {}
  ~leda_allocator() {}

/*{\Moperations 3 3 }*/

pointer allocate(size_type n, const_pointer = 0)
/*{\Mop returns a pointer to a newly allocated memory range of size
        |n * sizeof(T)|.}*/
{ return 0 == n ? 0 : 
         (T*) CGAL_LEDA_SCOPE::std_memory_mgr.allocate_bytes( n * sizeof(T) ); }

void deallocate(pointer p, size_type n)
/*{\Mop deallocates a memory range of |n * sizeof(T)| starting
        at |p|. \precond the memory range was obtained via |allocate(n)|.}*/
{ CGAL_LEDA_SCOPE::std_memory_mgr.deallocate_bytes(p , n * sizeof(T)); }

pointer address(reference r)
/*{\Mop returns |&r|.}*/
{ return &r; }

const_pointer address(const_reference r)
/*{\Mop returns |&r|.}*/
{ return &r; }

void construct(pointer p, const_reference r)
/*{\Mop makes an inplace new |new( (void*)p ) T(r)|.}*/
{ new(p) value_type(r); }

void destroy(pointer p)
/*{\Mop destroys the object referenced via |p| by calling |p->~T()|.}*/
{ p->~T(); }

size_type max_size() const { return CGAL_LEDA_SCOPE::std_memory_mgr.max_size(); }
/*{\Mop the largest value |n| for which the call |allocate(n,0)| 
    might succeed.}*/

};


/*{\Mimplementation Note that the above class template uses all kinds
of modern compiler technology like member templates, partial specialization
etc. It runs only on a subset of LEDA's general supported platforms like
|g++ > 2.95|, |SGI CC > 7.3|.}*/

#if LEDA_ROOT_INCL_ID == 390009
#undef LEDA_ROOT_INCL_ID
#include <LEDA/UNDEFINE_NAMES.h>
#endif

#endif // LEDA_ALLOCATOR_H

