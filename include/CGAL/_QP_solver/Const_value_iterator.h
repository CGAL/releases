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
// file          : include/CGAL/_QP_solver/Const_value_iterator.h
// package       : _QP_solver (0.9.3)
//
// revision      : 0.2
// revision_date : 2000/08/29
//
// author(s)     : Sven Schönherr
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: sparse vector iterator
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CONST_VALUE_ITERATOR_H
#define CGAL_CONST_VALUE_ITERATOR_H

#include <CGAL/basic.h>
#include <iterator>

CGAL_BEGIN_NAMESPACE

template < class T >
class Const_value_iterator
#ifdef __BORLANDC__
    : public CGAL_STD::
        iterator<std::random_access_iterator_tag,T,ptrdiff_t,T*,T&>
#endif
                           {
  public:
    typedef  T                                value_type;
    typedef  ptrdiff_t                        difference_type;
    typedef  value_type*                      pointer;
    typedef  value_type&                      reference;
    typedef  std::random_access_iterator_tag  iterator_category;

    typedef  Const_value_iterator<T>  Self;
    typedef  value_type               Val;
    typedef  difference_type          Dist;
    typedef  reference                Ref;
    typedef  pointer                  Ptr;

    // forward operations
    Const_value_iterator( const T& t = T(), Dist i = 0)
	: index( i), value( t) { }

    bool       operator == ( const Self& it) const { return index == it.index;}
    bool       operator != ( const Self& it) const { return index != it.index;}

    Val        operator *  ( ) const { return  value; }
    Ptr        operator -> ( ) const { return &value; }

    Self&      operator ++ (    ) { ++index; return *this; }
    Self       operator ++ ( int) { Self tmp = *this; ++index; return tmp; }

    // bidirectional operations
    Self&      operator -- (    ) { --index; return *this; }
    Self       operator -- ( int) { Self tmp = *this; --index; return tmp; }

    // random access operations
    Self&  operator += ( Dist i) { index += i; return *this; }
    Self&  operator -= ( Dist i) { index -= i; return *this; }

    Self   operator +  ( Dist i) const
	{ Self tmp = *this; tmp += i; return tmp; }
    Self   operator -  ( Dist i) const
	{ Self tmp = *this; tmp -= i; return tmp; }

    Dist   operator -  ( const Self& it) const { return index - it.index; }

    Val    operator [] ( int) const { return value; }

    bool   operator <  ( const Self& it) const { return index <  it.index; }
    bool   operator >  ( const Self& it) const { return index >  it.index; }
    bool   operator <= ( const Self& it) const { return index <= it.index; }
    bool   operator >= ( const Self& it) const { return index >= it.index; }

  private:
    Dist  index;
    T     value;
};

CGAL_END_NAMESPACE
  
#endif

// ===== EOF ==================================================================
