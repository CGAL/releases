// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Modifier_base.h
// package       : Modifier (1.3.5)
// chapter       : $CGAL_Chapter: Protected access to the internal repr.$
// source        : modifier.fw
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1999/11/22 14:07:46 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Modifier providing protected access to internal representations.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_MODIFIER_BASE_H
#define CGAL_MODIFIER_BASE_H 1

CGAL_BEGIN_NAMESPACE

template <class R>
class Modifier_base {
    // Abstract Base Class for protected internal access.
    // It defines the common interface for all modifiers.
public:
    typedef R Representation;
    virtual void operator()( R& rep) = 0;
        // Postcondition: `rep' is a valid representation.
    virtual ~Modifier_base() {}
};

CGAL_END_NAMESPACE

#endif // CGAL_MODIFIER_BASE_H //
// EOF //
