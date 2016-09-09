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
// file          : include/CGAL/NT_converter.h
// package       : Number_types (4.57)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/02/21 16:57:14 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_NT_CONVERTER_H
#define CGAL_NT_CONVERTER_H

CGAL_BEGIN_NAMESPACE

// A number type converter usable as default, using the conversion operator.

template < class NT1, class NT2 >
struct NT_converter
{
    NT2
    operator()(const NT1 &a) const
    {
        return NT2(a);
    }
};


// A number type converter to Interval_base, using to_interval().

template < class NT >
struct Interval_converter
{
    Interval_base
    operator()(const NT &a) const
    {
        return to_interval(a);
    }
};

CGAL_END_NAMESPACE

#endif // CGAL_NT_CONVERTER_H
