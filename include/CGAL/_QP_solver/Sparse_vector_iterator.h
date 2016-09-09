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
// file          : include/CGAL/_QP_solver/Sparse_vector_iterator.h
// package       : _QP_solver (0.9.7)
//
// revision      : 0.1
// revision_date : 2000/08/09
//
// author(s)     : Sven Schönherr
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: sparse vector iterator
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_SPARSE_VECTOR_ITERATOR_H
#define CGAL_SPARSE_VECTOR_ITERATOR_H

#include <CGAL/basic.h>
#include <iterator>
#include <utility>
#include <vector>

CGAL_BEGIN_NAMESPACE

template < class NT >
class Sparse_vector_iterator {
  public:
    typedef  NT                                value_type;
    typedef  ptrdiff_t                         difference_type;
    typedef  value_type*                       pointer;
    typedef  value_type&                       reference;
    typedef  std::random_access_iterator_tag   iterator_category;

    typedef  Sparse_vector_iterator<NT>        Self;
    typedef  value_type                        Val;
    typedef  difference_type                   Dist;

    typedef  std::pair<Dist,Val>               Entry;
    typedef  std::vector<Entry>                Entries;
    typedef  typename Entries::const_iterator  EntryIterator;

    // forward operations
    Sparse_vector_iterator( ) : curr( 0), zero( 0) { }

    bool   operator == ( const Self& it) const { return ( curr == it.curr); }
    bool   operator != ( const Self& it) const { return ( curr != it.curr); }

    Val    operator *  ( ) const
	{
	    EntryIterator it;
	    for ( it = entries.begin(); it != entries.end(); ++it)
		if ( curr == it->first) return it->second;
	    return zero;
	}

    Self&  operator ++ (    ) {                   ++curr; return *this; }
    Self   operator ++ ( int) { Self tmp = *this; ++curr; return tmp;   }

    // bidirectional operations
    Self&  operator -- (    ) {                   --curr; return *this; }
    Self   operator -- ( int) { Self tmp = *this; --curr; return tmp;   }

    // random access operations
    Self&  operator += ( Dist n) { curr += n; return *this; }
    Self&  operator -= ( Dist n) { curr -= n; return *this; }

    Self   operator +  ( Dist n) const { Self tmp=*this; return tmp+=n; }
    Self   operator -  ( Dist n) const { Self tmp=*this; return tmp-=n; }

    Dist   operator - ( const Self& it) const { return curr - it.curr; }

    Val    operator [] ( Dist i) const
	{
	    Dist index = curr+i;
	    EntryIterator it;
	    for ( it = entries.begin(); it != entries.end(); ++it)
		if ( index == it->first) return it->second;
	    return zero;
	}

    bool   operator <  ( const Self&) const { return ( curr <  it.curr); }
    bool   operator >  ( const Self&) const { return ( curr >  it.curr); }
    bool   operator <= ( const Self&) const { return ( curr <= it.curr); }
    bool   operator >= ( const Self&) const { return ( curr >= it.curr); }

    // additional operations
    void  push_back( const Entry& entry) { entries.push_back( entry); }

  private:
    Dist                curr;
    NT                  zero;
    std::vector<Entry>  entries;
};

CGAL_END_NAMESPACE
  
#endif

// ===== EOF ==================================================================
