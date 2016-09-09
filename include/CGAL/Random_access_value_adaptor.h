// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Random_access_value_adaptor.h
// package       : STL_Extension (2.6)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/04/07 18:31:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Random Access Value Adaptor provides random access for sequences.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_RANDOM_ACCESS_VALUE_ADAPTOR_H
#define CGAL_RANDOM_ACCESS_VALUE_ADAPTOR_H 1
#ifndef CGAL_RANDOM_ACCESS_ADAPTOR_H
#include <CGAL/Random_access_adaptor.h>
#endif // CGAL_RANDOM_ACCESS_ADAPTOR_H

CGAL_BEGIN_NAMESPACE

template < class IC, class T >
class Random_access_value_adaptor : public Random_access_adaptor<IC> {
public:
    Random_access_value_adaptor() {}
        // invalid index.

    Random_access_value_adaptor( const IC& i)
        : Random_access_adaptor<IC>(i) {}
        // empty random access index initialized to start at i.

    Random_access_value_adaptor( const IC& i, const IC& j)
        : Random_access_adaptor<IC>(i,j) {}
        // random access index initialized with range [i,j).

// OPERATIONS

    T& operator[]( size_type n) const {
        // returns inverse index of k.
        return *(Random_access_adaptor<IC>::operator[](n));
    }
};

CGAL_END_NAMESPACE
#endif // CGAL_RANDOM_ACCESS_VALUE_ADAPTOR_H //
// EOF //
