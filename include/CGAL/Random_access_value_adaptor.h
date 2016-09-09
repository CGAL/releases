// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Random_access_value_adaptor.h
// package       : STL_Extension (1.17)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.12 $
// revision_date : $Date: 1998/10/08 14:35:33 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Random Access Value Adaptor provides random access for sequences.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_RANDOM_ACCESS_VALUE_ADAPTOR_H
#define CGAL_RANDOM_ACCESS_VALUE_ADAPTOR_H 1
#ifndef CGAL_RANDOM_ACCESS_ADAPTOR_H
#include <CGAL/Random_access_adaptor.h>
#endif // CGAL_RANDOM_ACCESS_ADAPTOR_H

template < class IC, class T >
class CGAL_Random_access_value_adaptor
    :  public CGAL_Random_access_adaptor< IC> {
public:
    CGAL_Random_access_value_adaptor() {}
        // invalid index.

    CGAL_Random_access_value_adaptor( const IC& i)
        : CGAL_Random_access_adaptor< IC>(i) {}
        // empty random access index initialized to start at i.

    CGAL_Random_access_value_adaptor( const IC& i, const IC& j)
        : CGAL_Random_access_adaptor< IC>(i,j) {}
        // random access index initialized with range [i,j).

// OPERATIONS

    T& operator[]( size_type n) const {
        // returns inverse index of k.
        return *(CGAL_Random_access_adaptor< IC>::operator[](n));
    }
};
#endif // CGAL_RANDOM_ACCESS_VALUE_ADAPTOR_H //
// EOF //
