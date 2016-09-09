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
// file          : include/CGAL/Iterator_project.h
// package       : STL_Extension (1.17)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.12 $
// revision_date : $Date: 1998/10/08 14:35:33 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// An iterator adaptor performing a projection on the value type.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_ITERATOR_PROJECT_H
#define CGAL_ITERATOR_PROJECT_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class I, class Fct, class Ref, class Ptr, class Dist, class Ctg>
#else
template < class I,
           class Fct,
           class Ref  = typename iterator_traits<I>::reference,
           class Ptr  = typename iterator_traits<I>::pointer,
           class Dist = typename iterator_traits<I>::difference_type,
           class Ctg  = typename iterator_traits<I>::iterator_category>
#endif
class CGAL_Iterator_project {
protected:
    I        nt;    // The internal iterator.
public:
    typedef  I  Iterator;
    typedef  CGAL_Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg> Self;

    typedef  Ctg                          iterator_category;
    typedef  typename Fct::argument_type  argument_type;
    typedef  typename Fct::result_type    value_type;
    typedef  value_type&                  reference;
    typedef  const value_type&            const_reference;
    typedef  value_type*                  pointer;
    typedef  const value_type*            const_pointer;
    typedef  Dist                         difference_type;


// CREATION
// --------

    CGAL_Iterator_project() {}
    CGAL_Iterator_project( I j) : nt(j) {}

// OPERATIONS Forward Category
// ---------------------------

    Iterator  current_iterator() const { return nt;}
    Ptr       ptr() const {
        Fct fct;
        return &(fct(*nt));                                      //###//
    }

    bool operator==( const Self& i) const {
        return ( nt == i.nt);                                    //###//
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }
    Ref  operator*() const {
        Fct fct;
        return fct(*nt);                                         //###//
    }
#ifndef CGAL_CFG_NO_ARROW_OPERATOR
#ifdef CGAL_CFG_NO_LAZY_INSTANTIATION
    Ptr  operator->() const {
        Fct fct;
        return &(fct(*nt));                                      //###//
    }
#else
    Ptr  operator->() const {
        Fct fct;
        return &(fct(*(nt.operator->())));                       //###//
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
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class D, class Fct, class I, class Ref, class Ptr,
           class Dist, class Ctg>
inline
CGAL_Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg>
operator+( D n, CGAL_Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg> i) {
    return i += Dist(n);
}

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class I, class Fct, class Ref, class Ptr, class Dist, class Ctg>
inline  Ctg
iterator_category( const CGAL_Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg>&) {
    return Ctg();
}
template < class I, class Fct, class Ref, class Ptr, class Dist, class Ctg>
inline  Dist*
distance_type( const CGAL_Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg>&) {
    return (Dist*)(0);
}
template < class I, class Fct, class Ref, class Ptr, class Dist, class Ctg>
inline  CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
    const CGAL_Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg>&) {
    return CGAL_Iterator_tag();
}
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //


#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class I, class II, class Fct, class Dist, class Ctg>
#else
template < class I,
           class II,
           class Fct,
           class Dist = typename iterator_traits<I>::difference_type,
           class Ctg  = typename iterator_traits<I>::iterator_category>
#endif
class CGAL_Iterator_const_project {
protected:
    I        nt;    // The internal iterator.
public:
    typedef  I  Iterator;
    typedef  CGAL_Iterator_const_project<I,II,Fct,Dist,Ctg> Self;

    typedef  Ctg                          iterator_category;
    typedef  typename Fct::argument_type  argument_type;
    typedef  typename Fct::result_type    value_type;
    typedef  value_type&                  reference;
    typedef  const value_type&            const_reference;
    typedef  value_type*                  pointer;
    typedef  const value_type*            const_pointer;
    typedef  Dist                         difference_type;

    typedef  const_reference              Ref;
    typedef  const_pointer                Ptr;

    typedef  CGAL_Iterator_project<II,Fct,reference,pointer,Dist,Ctg>
                                          mutable_iterator;

// CREATION
// --------

    CGAL_Iterator_const_project() {}
    CGAL_Iterator_const_project( Iterator j) : nt(j) {}
    CGAL_Iterator_const_project( mutable_iterator j) : nt( &*j) {}
        // : nt( &*(j.current_iterator())) {}

// OPERATIONS Forward Category
// ---------------------------

    Iterator  current_iterator() const { return nt;}
    Ptr       ptr() const {
        Fct fct;
        return &(fct(*nt));                                      //###//
    }

    bool operator==( const Self& i) const {
        return ( nt == i.nt);                                    //###//
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }
    Ref  operator*() const {
        Fct fct;
        return fct(*nt);                                         //###//
    }
#ifndef CGAL_CFG_NO_ARROW_OPERATOR
#ifdef CGAL_CFG_NO_LAZY_INSTANTIATION
    Ptr  operator->() const {
        Fct fct;
        return &(fct(*nt));                                      //###//
    }
#else
    Ptr  operator->() const {
        Fct fct;
        return &(fct(*(nt.operator->())));                       //###//
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
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class D, class Fct, class I, class II, class Dist, class Ctg>
inline
CGAL_Iterator_const_project<I,II,Fct,Dist,Ctg>
operator+( D n, CGAL_Iterator_const_project<I,II,Fct,Dist,Ctg> i) {
    return i += Dist(n);
}

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class I, class II, class Fct, class Dist, class Ctg>
inline  Ctg
iterator_category( const CGAL_Iterator_const_project<I,II,Fct,Dist,Ctg>&) {
    return Ctg();
}
template < class I, class II, class Fct, class Dist, class Ctg>
inline  Dist*
distance_type( const CGAL_Iterator_const_project<I,II,Fct,Dist,Ctg>&) {
    return (Dist*)(0);
}
template < class I, class II, class Fct, class Dist, class Ctg>
inline  CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
    const CGAL_Iterator_const_project<I,II,Fct,Dist,Ctg>&) {
    return CGAL_Iterator_tag();
}
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
#endif // CGAL_ITERATOR_PROJECT_H //
// EOF //
