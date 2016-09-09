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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/Counting_iterator.h
// package       : STL_Extension (1.14)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1998/03/24 13:39:06 $
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

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class I, class Val>
#else
template < class I,
           class Val = typename iterator_traits<I>::value_type>
#endif
class CGAL_Counting_iterator {
private:
    I        nt;    // The internal iterator.
    size_t   d_i;   // The internal counter.
public:
    typedef I  Iterator;
    typedef CGAL_Counting_iterator<I,Val> Self;

    typedef  input_iterator_tag                      iterator_category;
    typedef  Val                                     value_type;
    typedef  ptrdiff_t                               difference_type;
    typedef  value_type&                             reference;
    typedef  value_type*                             pointer;
    typedef  const value_type&                       const_reference;
    typedef  const value_type*                       const_pointer;

// CREATION
// --------

    CGAL_Counting_iterator( size_t i = 0)             : d_i(i) {}
    CGAL_Counting_iterator( Iterator j, size_t i = 0) : nt(j), d_i(i) {}

// OPERATIONS Forward Category
// ---------------------------

    Iterator  current_iterator() const { return nt;}
    size_t    current_counter()  const { return d_i;}

    bool operator==( const Self& i) const {
        return ( d_i == i.d_i);
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }
    const_reference  operator*() const {
        return *nt;
    }
#ifndef CGAL_CFG_NO_ARROW_OPERATOR
#ifdef CGAL_CFG_NO_LAZY_INSTANTIATION
    const_pointer  operator->() const {
        return &(*nt);
    }
#else
    const_pointer  operator->() const {
        return nt.operator->();
    }
#endif
#endif
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
    value_type( const Self&) {
        return (value_type*)(0);
    }
    friend inline  iterator_category
    iterator_category( const Self&){
        return iterator_category();
    }
    friend inline  difference_type*
    distance_type( const Self&) {
        return (difference_type*)(0);
    }
    friend inline  CGAL_Iterator_tag
    CGAL_query_circulator_or_iterator( const Self&) {
        return CGAL_Iterator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};
#endif // CGAL_COUNTING_ITERATOR_H //
// EOF //
