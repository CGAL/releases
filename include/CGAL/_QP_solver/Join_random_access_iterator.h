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
// file          : include/CGAL/_QP_solver/Join_random_access_iterator.h
// package       : _QP_solver (0.9.7)
//
// revision      : 0.3
// revision_date : 2000/09/11
//
// author(s)     : Sven Schönherr
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: join random access iterator
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_JOIN_RANDOM_ACCESS_ITERATOR_H
#define CGAL_JOIN_RANDOM_ACCESS_ITERATOR_H

#include <CGAL/basic.h>
#include <iterator>

CGAL_BEGIN_NAMESPACE

template < class RndAccIt, class Operation >
class Join_random_access_iterator_1 {
  public:
    typedef  typename Operation::result_type  value_type;
    typedef  ptrdiff_t                        difference_type;
    typedef  value_type*                      pointer;
    typedef  value_type&                      reference;
    typedef  std::random_access_iterator_tag  iterator_category;

    typedef  Join_random_access_iterator_1<RndAccIt,Operation>  Self;
    typedef  value_type                                         Val;
    typedef  difference_type                                    Dist;
    typedef  reference                                          Ref;

    // forward operations
    Join_random_access_iterator_1( ) { }
    Join_random_access_iterator_1( const RndAccIt& it_1) : it1( it_1) { }
    Join_random_access_iterator_1( const RndAccIt&  it_1,
				   const Operation& operation)
	: it1( it_1), op( operation) { }

    bool   operator == ( const Self& it) const { return ( it1 == it.it1); }
    bool   operator != ( const Self& it) const { return ( it1 != it.it1); }

    Val    operator *  ( ) const { return op( *it1); }

    Self&  operator ++ (    ) {                   ++it1; return *this; }
    Self   operator ++ ( int) { Self tmp = *this; ++it1; return tmp;   }

    // bidirectional operations
    Self&  operator -- (    ) {                   --it1; return *this; }
    Self   operator -- ( int) { Self tmp = *this; --it1; return tmp;   }

    // random access operations
    Self&  operator += ( Dist n) { it1 += n; return *this; }
    Self&  operator -= ( Dist n) { it1 -= n; return *this; }

    Self   operator +  ( Dist n) const { Self tmp = *this; return tmp += n; }
    Self   operator -  ( Dist n) const { Self tmp = *this; return tmp -= n; }

    Dist   operator -  ( const Self& it) const { return it1 - it.it1; }

    Val    operator [] ( int i) const { return op( it1[ i]); }

    bool   operator <  ( const Self&) const { return ( it1 <  it.it1); }
    bool   operator >  ( const Self&) const { return ( it1 >  it.it1); }
    bool   operator <= ( const Self&) const { return ( it1 <= it.it1); }
    bool   operator >= ( const Self&) const { return ( it1 >= it.it1); }

  private:
    RndAccIt   it1;
    Operation  op;
};

CGAL_END_NAMESPACE
  
#endif

// ===== EOF ==================================================================
