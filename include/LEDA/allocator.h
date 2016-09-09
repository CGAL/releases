// Copyright (c) 2000  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/LEDA/include/LEDA/allocator.h,v $
// $Revision: 1.4 $ $Date: 2003/10/21 12:19:39 $
// $Name: current_submission $
//
// Author(s)     : ?

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

size_type max_size() const
/*{\Mop the largest value |n| for which the call |allocate(n,0)| 
    might succeed.}*/
{ return CGAL_LEDA_SCOPE::std_memory_mgr.max_size(); }

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

