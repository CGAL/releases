// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// file          : include/CGAL/Handle_hash_function.h
// package       : Hash_map (0.9.7)
// chapter       : STL_Extensions
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/07/16 21:03:21 $
//
// author(s)     : Michael Seel
//                 Lutz Kettner
// coordinator   : Michael Seel
//
// implementation: Hash Map by chained hashing, default hash function
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_HANDLE_HASH_FUNCTION_H
#define CGAL_HANDLE_HASH_FUNCTION_H

#include <CGAL/basic.h>
#include <cstddef>

CGAL_BEGIN_NAMESPACE

struct Handle_hash_function {
    typedef std::size_t result_type;
    template <class H> 
    std::size_t operator() (const H& h) const { 
        return std::size_t(&*h) / 
            sizeof( typename std::iterator_traits<H>::value_type);
    } 
};

CGAL_END_NAMESPACE

#endif // CGAL_HANDLE_HASH_FUNCTION_H
// EOF

