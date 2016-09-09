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
// file          : include/CGAL/Counting_iterator.h
// package       : STL_Extension (2.6)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/04/07 18:31:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// An iterator adaptor for the identity function.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_COUNTING_ITERATOR_H
#define CGAL_COUNTING_ITERATOR_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

CGAL_BEGIN_NAMESPACE

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class I, class Val>
#else
template < class I,
           class Val = typename std::iterator_traits<I>::value_type>
#endif
class Counting_iterator {
private:
    I            nt;    // The internal iterator.
    std::size_t  d_i;   // The internal counter.
public:
    typedef I  Iterator;
    typedef Counting_iterator<I,Val> Self;

    typedef std::input_iterator_tag  iterator_category;
    typedef Val                      value_type;
    typedef std::ptrdiff_t           difference_type;
    typedef const value_type&        reference;
    typedef const value_type*        pointer;

// CREATION
// --------

    Counting_iterator( std::size_t i = 0)             : d_i(i) {}
    Counting_iterator( Iterator j, std::size_t i = 0) : nt(j), d_i(i) {}

// OPERATIONS Forward Category
// ---------------------------

    Iterator    current_iterator() const { return nt;}
    std::size_t current_counter()  const { return d_i;}

    bool operator==( const Self& i) const { return ( d_i == i.d_i); }
    bool operator!=( const Self& i) const { return !(*this == i);   }
    reference  operator*()  const { return *nt; }
    pointer    operator->() const { return nt.operator->(); }
    Self& operator++() {
        ++nt;
        ++d_i;
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    friend inline  value_type*
    value_type( const Self&) { return (value_type*)(0); }
    friend inline  iterator_category
    iterator_category( const Self&){ return iterator_category(); }
    friend inline  difference_type*
    distance_type( const Self&) { return (difference_type*)(0); }
    friend inline  Iterator_tag
    query_circulator_or_iterator( const Self&) { return Iterator_tag(); }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

CGAL_END_NAMESPACE
#endif // CGAL_COUNTING_ITERATOR_H //
// EOF //
