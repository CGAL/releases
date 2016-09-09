// ======================================================================
//
// Copyright (c) 1999,2001 The CGAL Consortium

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
// file          : include/CGAL/Handle_for.h
// package       : Kernel_basic (3.90)
// revision      : $Revision: 1.9 $
// revision_date : $Date: 2002/01/04 14:07:53 $
// author(s)     : Stefan Schirra, Sylvain Pion
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_HANDLE_FOR_H
#define CGAL_HANDLE_FOR_H

#include <CGAL/memory.h>

CGAL_BEGIN_NAMESPACE

struct Ref_counted {}; // For backward compatibility.  It's obsolete.

template <class U>
struct Ref_counted2
{
    Ref_counted2(const U& u) : count(1), u_(u)  {}
    Ref_counted2(const Ref_counted2& r) : count(1), u_(r.u()) {}

    U* base_ptr() { return &u_; }

#ifdef CGAL_USE_LEDA
    // Speeds things up with LEDA and New_delete_allocator<>.
    LEDA_MEMORY(Ref_counted2)
#endif

    void add_reference() { ++count; }
    void remove_reference() { --count; }
    bool is_shared() const { return count > 1; }

private:

    const U& u() const { return u_; }

    unsigned int count;
    U u_;
};


template <class T, class Alloc = CGAL_ALLOCATOR(T) >
class Handle_for
{
    typedef Ref_counted2<T>                                     RefCounted;

#ifndef CGAL_CFG_NO_NESTED_TEMPLATE_KEYWORD
    typedef typename Alloc::template rebind<RefCounted>::other  Allocator;
  public:
#else
  public:
    // For VC++, we must hardcode the default allocator.
    typedef CGAL_ALLOCATOR(RefCounted)                          Allocator;
#endif

    typedef T element_type;

    Handle_for()
    {
        ptr_ = allocator.allocate(1);
	initialize_with(T());
    }

    Handle_for(const T& t)
    {
        ptr_ = allocator.allocate(1);
	initialize_with(t);
    }

    Handle_for(const Handle_for& h)
    {
        ptr_ = h.ptr_;
        ptr_->add_reference();
    }

    ~Handle_for()
    {
	remove_reference();
    }

    Handle_for&
    operator=(const Handle_for& h)
    {
        h.ptr_->add_reference();
	remove_reference();
        ptr_ = h.ptr_;
        return *this;
    }

// protected:

    void
    initialize_with(const T& t)
    {
        allocator.construct(ptr_, RefCounted(t));
    }

    bool
    identical(const Handle_for& h) const
    { return ptr_ == h.ptr_; }

    long int
    id() const
    { return reinterpret_cast<long int>(&*ptr_); }

    // Ptr() is the "public" access to the pointer.  Both const and non-const.
    // non-const does copy-on-write.
    const T *
    Ptr() const
    { return ptr_->base_ptr(); }

    /*
    T *
    Ptr()
    {
	copy_on_write();
	return ptr_;
    }
    */

    bool
    is_shared() const
    {
	return ptr_->is_shared();
    }

protected:

    void
    copy_on_write()
    {
      if ( is_shared() )
      {
        RefCounted* tmp_ptr = allocator.allocate(1);
        allocator.construct( tmp_ptr, *ptr_);
        ptr_->remove_reference();
        ptr_ = tmp_ptr;
      }
    }

    // ptr() is the protected access to the pointer.  Both const and non-const.
    T *
    ptr()
    { return ptr_->base_ptr(); }

    const T *
    ptr() const
    { return ptr_->base_ptr(); }

private:

    void
    remove_reference()
    {
      if (! is_shared() ) {
          allocator.destroy( ptr_);
          allocator.deallocate( ptr_, 1);
      }
      else
	  ptr_->remove_reference();
    }

    static Allocator allocator; // Should this go in RefCounted2<> ?
    typename Allocator::pointer      ptr_;
};


template <class T, class Allocator>
typename Handle_for<T, Allocator>::Allocator
Handle_for<T, Allocator>::allocator;

CGAL_END_NAMESPACE

#endif // CGAL_HANDLE_FOR_H
