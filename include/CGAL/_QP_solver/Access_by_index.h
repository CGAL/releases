// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-2.2-I-51 $
// release_date  : $CGAL_Date: 2000/10/01 $
//
// file          : include/CGAL/_QP_solver/Access_by_index.h
// package       : _QP_solver (0.9)
// maintainer    : Sven Sch�nherr <sven@inf.ethz.ch>
//
// revision      : 0.2
// revision_date : 2000/08/11 00:00:00
//
// author(s)     : Sven Sch�nherr
// coordinator   : ETH Z�rich (Bernd G�rtner <gaertner@inf.ethz.ch>)
//
// implementation: access by index function class
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
