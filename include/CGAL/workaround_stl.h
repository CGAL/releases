// ======================================================================
//
// Copyright (c) 1997,1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/workaround_stl.h
// package       : Configuration (1.16)
// chapter       : $CGAL_Chapter: Configuration $
//
// source        : web/workarounds.aw
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1998/07/17 12:53:52 $
// author(s)     : Sven Schönherr
//
// coordinator   : Utrecht University (Wieger Wesselink)
//
// implementation: Workarounds for STL
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_WORKAROUND_STL_H
#define CGAL_WORKAROUND_STL_H 1

// fix for GNU's type unification bug in STL's `distance' function
// ---------------------------------------------------------------
template < class BidirectionalIterator, class Distance >
void
distance( BidirectionalIterator first,
          BidirectionalIterator last,
          Distance& n);

template < class BidirectionalIterator, class Distance >
inline
void
CGAL__distance( BidirectionalIterator first,
                BidirectionalIterator last,
                Distance& n)
{
#ifdef CGAL_STL_GCC
    while ( first != last) {
        ++first;
        ++n;
    }
#else
    distance( first, last, n);
#endif // CGAL_STL_GCC
}

#endif // CGAL_WORKAROUND_STL_H

// ===== EOF ==================================================================
