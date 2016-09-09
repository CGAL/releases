// ======================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

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
// file          : include/CGAL/_QP_solver/Access_by_index.h
// package       : _QP_solver (0.9.3)
//
// revision      : 0.2
// revision_date : 2000/08/11
//
// author(s)     : Sven Schönherr
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: access by index function class
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ACCESS_BY_INDEX_H
#define CGAL_ACCESS_BY_INDEX_H

#include <CGAL/basic.h>
#include <functional>
#include <iterator>

CGAL_BEGIN_NAMESPACE

template < class RndAccIt, bool check_lower = false, bool check_upper = false>
class Access_by_index {
  public:
    typedef  int                        argument_type;
    typedef  typename std::iterator_traits<RndAccIt>::value_type
                                        result_type;

    Access_by_index( RndAccIt it = RndAccIt(),
		     const result_type& default_result = result_type(),
		     int lower = 0, int upper = 0)
        : a( it), r( default_result)
        {
	    if ( check_lower) l = lower;
	    if ( check_upper) u = upper;
	}

    result_type  operator () ( int i) const
        {
	    if ( check_lower && i <  l) return r;
	    if ( check_upper && i >= u) return r;
	    return a[ i];
	}

  private:
    RndAccIt     a;
    int          l;
    int          u;
    result_type  r;
};

CGAL_END_NAMESPACE
  
#endif

// ===== EOF ==================================================================
