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
// file          : include/CGAL/Handle_for_virtual.h
// package       : Kernel_basic (3.90)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/12/02 17:05:23 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_HANDLE_FOR_VIRTUAL_H
#define CGAL_HANDLE_FOR_VIRTUAL_H

CGAL_BEGIN_NAMESPACE

class Ref_counted_virtual
{
  public:
    Ref_counted_virtual() : count(1) {}
    Ref_counted_virtual(const Ref_counted_virtual&) : count(1) {}

    void  add_reference() { ++count; }
    void  remove_reference() { --count; }
    bool  is_referenced() { return (count != 0); }
    bool  is_shared() { return (count > 1); }

    virtual ~Ref_counted_virtual() {}

  protected:
    unsigned int count;
};


template <class RefCounted>
// RefCounted must provide
// add_reference()
// remove_reference()
// bool is_referenced()
// bool is_shared()
// and initialize count to 1 in default and copy constructor
class Handle_for_virtual
{
  public:

    Handle_for_virtual(const RefCounted& rc)
    {
      ptr = new RefCounted(rc);
    }

    Handle_for_virtual()
    {
      ptr = NULL;
    }

    Handle_for_virtual( const Handle_for_virtual& h)
    {
      ptr = h.ptr;
      ptr->add_reference();
    }

    ~Handle_for_virtual()
    {
      ptr->remove_reference();
      if ( !ptr->is_referenced() )
	  delete ptr;
    }

    Handle_for_virtual&
    operator=( const Handle_for_virtual& h)
    {
      h.ptr->add_reference();
      ptr->remove_reference();
      if ( !ptr->is_referenced() )
	  delete ptr;
      ptr = h.ptr;
      return *this;
    }

// protected:
    typedef RefCounted element_type;

    template <class T>
    void
    initialize_with( const T& rc)
    {
	ptr = new T(rc);
    }

    bool
    identical( const Handle_for_virtual& h) const
    { return ptr == h.ptr; }

    long int
    id() const
    { return reinterpret_cast<long int>(&*ptr); }

    const RefCounted *
    Ptr() const
    { return ptr; }

    /*
    T *
    Ptr()
    {
	copy_on_write();
	return ptr;
    }
    */

    /*
// private:
    void
    copy_on_write()
    {
      if ( ptr->is_shared() )
      {
        RefCounted* tmp_ptr = allocator.allocate(1);
        allocator.construct( tmp_ptr, *ptr);
        ptr->remove_reference();
        ptr = tmp_ptr;
      }
    }
    */
protected:

    /*
    RefCounted * ptr() const
    {
	return ptr;
    }
    */

private:

    RefCounted * ptr;
};

CGAL_END_NAMESPACE

#endif // CGAL_HANDLE_FOR_VIRTUAL_H
