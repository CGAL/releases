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
// file          : include/CGAL/Simple_Handle_for.h
// package       : Kernel_basic (3.90)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/11/23 14:20:49 $
// author(s)     : Sylvain Pion
// coordinator   : MPI, Saarbruecken  (<Susan.Hert>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SIMPLE_HANDLE_FOR_H
#define CGAL_SIMPLE_HANDLE_FOR_H

CGAL_BEGIN_NAMESPACE

template < class Stored >
class Simple_Handle_for
{
public:

    Simple_Handle_for()
    {}

    Simple_Handle_for(const Stored& rc)
	: _s(rc) {}

    typedef Stored element_type;

    void
    initialize_with(const Stored& rc)
    {
      _s = rc;
    }

    long int
    id() const
    { return reinterpret_cast<long int>(&_s); }

    bool
    identical(const Simple_Handle_for& h) const
    { return id() == h.id(); } // Or should it always return false ?

    const Stored * Ptr() const
    { return &_s; }

    Stored * Ptr()
    { return &_s; }

    const Stored * ptr() const
    { return &_s; }

    Stored * ptr()
    { return &_s; }

    bool
    is_shared() const
    {
	return false;
    }

private:
    void
    copy_on_write()
    {}

    Stored _s;
};

CGAL_END_NAMESPACE

#endif // CGAL_SIMPLE_HANDLE_FOR_H
