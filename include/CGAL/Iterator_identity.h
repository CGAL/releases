// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Iterator_identity.h
// author(s)     : Lutz Kettner  
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_ITERATOR_IDENTITY_H
#define CGAL_ITERATOR_IDENTITY_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class I, class Ref, class Ptr, class Val, class Dist, class Ctg>
#else
template < class I,
           class Ref  = typename iterator_traits<I>::reference,
           class Ptr  = typename iterator_traits<I>::pointer,
           class Val  = typename iterator_traits<I>::value_type,
           class Dist = typename iterator_traits<I>::difference_type,
           class Ctg  = typename iterator_traits<I>::iterator_category>
#endif
class CGAL_Iterator_identity {
private:
    I        nt;    // The internal iterator.
public:
    typedef I  Iterator;
    typedef CGAL_Iterator_identity<I,Ref,Ptr,Val,Dist,Ctg> Self;

    typedef  Ctg                                     iterator_category;
    typedef  Val                                     value_type;
    typedef  Dist                                    difference_type;

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    typedef  value_type&                             reference;
    typedef  value_type*                             pointer;
#else
    typedef  typename iterator_traits<I>::reference  reference;
    typedef  typename iterator_traits<I>::pointer    pointer;
#endif
    typedef  const value_type&                       const_reference;
    typedef  const value_type*                       const_pointer;

// CREATION
// --------

    CGAL_Iterator_identity() {}
    CGAL_Iterator_identity( Iterator j) : nt(j) {}

// OPERATIONS Forward Category
// ---------------------------

    Iterator  current_iterator() const { return nt;}

    bool operator==( const Self& i) const {
        return ( nt == i.nt);                                    //###//
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }
    Ref  operator*() const {
        return *nt;                                              //###//
    }
#ifndef CGAL_CFG_NO_ARROW_OPERATOR
#ifdef CGAL_CFG_NO_LAZY_INSTANTIATION
    Ptr  operator->() const {
        return &(*nt);                                           //###//
    }
#else
    Ptr  operator->() const {
        return nt.operator->();                                  //###//
    }
#endif
#endif
    Self& operator++() {
        ++nt;                                                    //###//
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }

// OPERATIONS Bidirectional Category
// ---------------------------------

    Self& operator--() {
        --nt;                                                    //###//
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }

// OPERATIONS Random Access Category
// ---------------------------------

// Make this adaptor bidirectional by default
// if implicit instantiation is buggy.
#ifndef CGAL_CFG_NO_LAZY_INSTANTIATION
    Self& operator+=( difference_type n) {
        nt += n;                                                 //###//
        return *this;
    }
    Self  operator+( difference_type n) const {
        Self tmp = *this;
        return tmp += n;
    }
    Self& operator-=( difference_type n) {
        return operator+=( -n);
    }
    Self  operator-( difference_type n) const {
        Self tmp = *this;
        return tmp += -n;
    }
    difference_type  operator-( const Self& i) const {
        return nt - i.nt;                                        //###//
    }
    Ref  operator[]( difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    bool operator<( const Self& i) const {
        return ( nt < i.nt);                                     //###//
    }
    bool operator>( const Self& i) const {
        return i < *this;
    }
    bool operator<=( const Self& i) const {
        return !(i < *this);
    }
    bool operator>=( const Self& i) const {
        return !(*this < i);
    }
#endif // CGAL_CFG_NO_LAZY_INSTANTIATION //
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    friend inline  value_type*
    value_type( const Self&) {
        return (value_type*)(0);
    }
    friend inline  Ctg
    iterator_category( const Self&){
        return Ctg();
    }
    friend inline  Dist*
    distance_type( const Self&) {
        return (Dist*)(0);
    }
    friend inline  CGAL_Iterator_tag
    CGAL_query_circulator_or_iterator( const Self&) {
        return CGAL_Iterator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class D, class I, class Ref, class Ptr, class Val,
           class Dist, class Ctg>
inline
CGAL_Iterator_identity<I,Ref,Ptr,Val,Dist,Ctg>
operator+( D n, CGAL_Iterator_identity<I,Ref,Ptr,Val,Dist,Ctg> i) {
    return i += Dist(n);
}
#endif // CGAL_ITERATOR_IDENTITY_H //
// EOF //
