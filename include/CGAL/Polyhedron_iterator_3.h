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
// file          : include/CGAL/Polyhedron_iterator_3.h
// package       : Polyhedron (1.11)
// chapter       : $CGAL_Chapter: 3D-Polyhedral Surfaces $
// source        : polyhedron.fw
// revision      : $Revision: 1.9 $
// revision_date : $Date: 1998/07/10 00:52:49 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Iterator and Circulator for Polyhedral Surfaces.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_POLYHEDRON_ITERATOR_3_H
#define CGAL_POLYHEDRON_ITERATOR_3_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

// Define shorter names to please linker (g++/egcs)
#define CGAL__Polyhedron_iterator                CGAL__PhI
#define CGAL__Polyhedron_const_iterator          CGAL__PhCI
#define CGAL__Polyhedron_edge_iterator           CGAL__PhEI
#define CGAL__Polyhedron_halfedge_const_iterator CGAL__PhHCI
#define CGAL__Polyhedron_facet_circ              CGAL__PhFC
#define CGAL__Polyhedron_facet_const_circ        CGAL__PhFCC
#define CGAL__Polyhedron_vertex_circ             CGAL__PhVC
#define CGAL__Polyhedron_vertex_const_circ       CGAL__PhVCC

// The following two iterators are similar to CGAL_Iterator_project
// and CGAL_Iterator_const_project, but they implement the arrow
// operator -> in any case. This is here possible since the elements
// a polyhedron consists of are always classes with members.

template < class I, class Val, class Dist, class Ctg>
class CGAL__Polyhedron_iterator {
protected:
    I        nt;    // The internal iterator.
public:
    typedef  I  Iterator;
    typedef  CGAL__Polyhedron_iterator<I,Val,Dist,Ctg> Self;

    typedef  Ctg                          iterator_category;
    typedef  Val                          value_type;
    typedef  Val&                         Ref;
    typedef  Val*                         Ptr;
    typedef  value_type&                  reference;
    typedef  const value_type&            const_reference;
    typedef  value_type*                  pointer;
    typedef  const value_type*            const_pointer;
    typedef  Dist                         difference_type;


// CREATION
// --------

    CGAL__Polyhedron_iterator() {}
    CGAL__Polyhedron_iterator( I j) : nt(j) {}
    // CGAL__Polyhedron_iterator( Ptr p) : nt(p) {}

// OPERATIONS Forward Category
// ---------------------------

    Iterator  current_iterator() const { return nt;}
    Ptr       ptr() const {
        return (Ptr)(&(*nt));
    }

    bool operator==( const Self& i) const {
        return ( nt == i.nt);
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }
    Ref  operator*() const {
        return (Ref)(*nt);
    }
    Ptr  operator->() const {
        return (Ptr)(&(*nt));
    }
    Self& operator++() {
        ++nt;
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
        --nt;
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
        nt += n;
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
        return nt - i.nt;
    }
    Ref  operator[]( difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    bool operator<( const Self& i) const {
        return ( nt < i.nt);
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
};

template < class D, class I, class Val, class Dist, class Ctg>
inline
CGAL__Polyhedron_iterator<I,Val,Dist,Ctg>
operator+( D n, CGAL__Polyhedron_iterator<I,Val,Dist,Ctg> i) {
    return i += Dist(n);
}

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class I, class Val, class Dist, class Ctg>
inline  Ctg
iterator_category( const CGAL__Polyhedron_iterator<I,Val,Dist,Ctg>&){
    return Ctg();
}
template < class I, class Val, class Dist, class Ctg>
inline  Val*
value_type( const CGAL__Polyhedron_iterator<I,Val,Dist,Ctg>&) {
    return (Val*)(0);
}
template < class I, class Val, class Dist, class Ctg>
inline  Dist*
distance_type( const CGAL__Polyhedron_iterator<I,Val,Dist,Ctg>&) {
    return (Dist*)(0);
}
template < class I, class Val, class Dist, class Ctg>
inline  CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
    const CGAL__Polyhedron_iterator<I,Val,Dist,Ctg>&)
{
    return CGAL_Iterator_tag();
}
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //


template < class I, class II, class Val, class Dist, class Ctg>
class CGAL__Polyhedron_const_iterator {
protected:
    I        nt;    // The internal iterator.
public:
    typedef  I  Iterator;
    typedef  CGAL__Polyhedron_const_iterator<I,II,Val,Dist,Ctg> Self;

    typedef  Ctg                          iterator_category;
    typedef  Val                          value_type;
    typedef  value_type&                  reference;
    typedef  const value_type&            const_reference;
    typedef  value_type*                  pointer;
    typedef  const value_type*            const_pointer;
    typedef  Dist                         difference_type;

    typedef  const_reference              Ref;
    typedef  const_pointer                Ptr;

    typedef  CGAL__Polyhedron_iterator<II,Val,Dist,Ctg>  mutable_iterator;

// CREATION
// --------

    CGAL__Polyhedron_const_iterator() {}
    CGAL__Polyhedron_const_iterator( Iterator j) : nt(j) {}
    // CGAL__Polyhedron_const_iterator( Ptr p) : nt(p) {}
    CGAL__Polyhedron_const_iterator( mutable_iterator j) : nt( &*j) {}

// OPERATIONS Forward Category
// ---------------------------

    Iterator  current_iterator() const { return nt;}
    Ptr       ptr() const {
        return (Ptr)(&(*nt));
    }

    bool operator==( const Self& i) const {
        return ( nt == i.nt);
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }
    Ref  operator*() const {
        return (Ref)(*nt);
    }
    Ptr  operator->() const {
        return (Ptr)(&(*nt));
    }
    Self& operator++() {
        ++nt;
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
        --nt;
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
        nt += n;
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
        return nt - i.nt;
    }
    Ref  operator[]( difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    bool operator<( const Self& i) const {
        return ( nt < i.nt);
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

template < class D, class I, class II, class Val, class Dist, class Ctg>
inline
CGAL__Polyhedron_const_iterator<I,II,Val,Dist,Ctg>
operator+( D n, CGAL__Polyhedron_const_iterator<I,II,Val,Dist,Ctg> i) {
    return i += Dist(n);
}

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class I, class II, class Val, class Dist, class Ctg>
inline  Ctg
iterator_category(
    const CGAL__Polyhedron_const_iterator<I,II,Val,Dist,Ctg>&){
    return Ctg();
}
template < class I, class II, class Val, class Dist, class Ctg>
inline  Val*
value_type( const CGAL__Polyhedron_const_iterator<I,II,Val,Dist,Ctg>&) {
    return (Val*)(0);
}
template < class I, class II, class Val, class Dist, class Ctg>
inline  Dist*
distance_type( const CGAL__Polyhedron_const_iterator<I,II,Val,Dist,Ctg>&) {
    return (Dist*)(0);
}
template < class I, class II, class Val, class Dist, class Ctg>
inline  CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
    const CGAL__Polyhedron_const_iterator<I,II,Val,Dist,Ctg>&)
{
    return CGAL_Iterator_tag();
}
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
template < class It, class Val, class Dist, class Ctg>
class CGAL__Polyhedron_edge_iterator : public It {
protected:
    //It        nt;    // The internal iterator, inherited from It..
public:
    typedef  It  Base;
    typedef  CGAL__Polyhedron_edge_iterator<It,Val,Dist,Ctg> Self;

    typedef  Ctg                                     iterator_category;
    typedef  Val                                     value_type;
    typedef  Dist                                    difference_type;

    typedef  value_type&                             reference;
    typedef  value_type*                             pointer;
    typedef  const value_type&                       const_reference;
    typedef  const value_type*                       const_pointer;

// CREATION
// --------

    CGAL__Polyhedron_edge_iterator() {}
    CGAL__Polyhedron_edge_iterator( It j) : It(j) {}

// OPERATIONS Forward Category
// ---------------------------

    It  current_iterator() const { return It(*this);}

    Self& operator++() {
        It::operator++();
        It::operator++();
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
        It::operator--();
        It::operator--();
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
        It::operator+=( n << 1);
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
        return (It::operator-(i)) >> 1;
    }
#endif // CGAL_CFG_NO_LAZY_INSTANTIATION //
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    friend inline  iterator_category
    iterator_category( const Self&) {
        return iterator_category();
    }
    friend inline  value_type*
    value_type( const Self&) {
        return (value_type*)(0);
    }
    friend inline  difference_type*
    distance_type( const Self&) {
        return (difference_type*)(0);
    }
    friend inline CGAL_Iterator_tag
    CGAL_query_circulator_or_iterator( const Self&) {
        return CGAL_Iterator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};
template < class D, class It, class Val, class Dist, class Ctg>
inline
CGAL__Polyhedron_edge_iterator<It,Val,Dist,Ctg>
operator+( D n, CGAL__Polyhedron_edge_iterator<It,Val,Dist,Ctg> i) {
    return i += Dist(n);
}
// This one is special for SunPro:
#ifdef __SUNPRO_CC
template < class I, class II, class C1, class C2, class Val,
           class Dist, class Ctg>
class CGAL__Polyhedron_halfedge_const_iterator {
protected:
    I        nt;    // The internal iterator.
public:
    typedef  I  Iterator;
    typedef  CGAL__Polyhedron_halfedge_const_iterator<I,II,C1,C2,
             Val,Dist,Ctg>                Self;

    typedef  Ctg                          iterator_category;
    typedef  Val                          value_type;
    typedef  value_type&                  reference;
    typedef  const value_type&            const_reference;
    typedef  value_type*                  pointer;
    typedef  const value_type*            const_pointer;
    typedef  Dist                         difference_type;

    typedef  const_reference              Ref;
    typedef  const_pointer                Ptr;

    typedef  CGAL__Polyhedron_iterator<II,Val,Dist,Ctg>  mutable_iterator;

// CREATION
// --------

    CGAL__Polyhedron_halfedge_const_iterator() {}
    CGAL__Polyhedron_halfedge_const_iterator( Iterator j) : nt(j) {}
    // CGAL__Polyhedron_halfedge_const_iterator( Ptr p) : nt(p) {}
    CGAL__Polyhedron_halfedge_const_iterator( mutable_iterator j)
        : nt( &*j) {}
    CGAL__Polyhedron_halfedge_const_iterator( C1 c1) : nt( &*c1) {}
    CGAL__Polyhedron_halfedge_const_iterator( C2 c2) : nt( &*c2) {}


// OPERATIONS Forward Category
// ---------------------------

    Iterator  current_iterator() const { return nt;}
    Ptr       ptr() const {
        return (Ptr)(&(*nt));
    }

    bool operator==( const Self& i) const {
        return ( nt == i.nt);
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }
    Ref  operator*() const {
        return (Ref)(*nt);
    }
    Ptr  operator->() const {
        return (Ptr)(&(*nt));
    }
    Self& operator++() {
        ++nt;
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
        --nt;
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
        nt += n;
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
        return nt - i.nt;
    }
    Ref  operator[]( difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    bool operator<( const Self& i) const {
        return ( nt < i.nt);
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

template < class D, class Val, class I, class II, class C1, class C2,
           class Dist, class Ctg>
inline
CGAL__Polyhedron_halfedge_const_iterator<I,II,C1,C2,Val,Dist,Ctg>
operator+( D n, CGAL__Polyhedron_halfedge_const_iterator<
           I,II,C1,C2,Val,Dist,Ctg> i) {
    return i += Dist(n);
}
#endif // __SUNPRO_CC //
template < class Node, class It, class Ctg>
class CGAL__Polyhedron_facet_circ : public It {
    // Ptr      nt;    // The internal node ptr inherited from It.
public:
    typedef  It  Base;
    typedef  CGAL__Polyhedron_facet_circ<Node,It,Ctg> Self;

    typedef  Ctg                iterator_category;
    typedef  Node               value_type;
    typedef  ptrdiff_t          difference_type;
    typedef  size_t             size_type;
    typedef  value_type&        reference;
    typedef  const value_type&  const_reference;
    typedef  value_type*        pointer;
    typedef  const value_type*  const_pointer;


// CREATION
// --------

    CGAL__Polyhedron_facet_circ() : It(0) {}
    //CGAL__Polyhedron_facet_circ( pointer p) : It(p) {}
    CGAL__Polyhedron_facet_circ( It i) : It(i) {}

// OPERATIONS Forward Category
// ---------------------------

    pointer  ptr() const { return & It::operator*();}

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return It::operator==( It(NULL));
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const Self& i) const {
        return  It::operator==(i);
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }

    Self& operator++() {
        nt = (*nt).next();
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
        nt = (*nt).prev();
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    friend inline  iterator_category
    iterator_category( const Self&) {
        return iterator_category();
    }
    friend inline  value_type*
    value_type( const Self&) {
        return (value_type*)(0);
    }
    friend inline  difference_type*
    distance_type( const Self&) {
        return (difference_type*)(0);
    }
    friend inline  CGAL_Circulator_tag
    CGAL_query_circulator_or_iterator( const Self&) {
        return CGAL_Circulator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};


template < class Node, class It, class Ctg>
class CGAL__Polyhedron_facet_const_circ : public It {
    // Ptr      nt;    // The internal node ptr inherited from It.
public:
    typedef  It  Base;
    typedef  CGAL__Polyhedron_facet_const_circ<Node,It,Ctg> Self;

    typedef  Ctg                iterator_category;
    typedef  Node               value_type;
    typedef  ptrdiff_t          difference_type;
    typedef  size_t             size_type;
    typedef  value_type&        reference;
    typedef  const value_type&  const_reference;
    typedef  value_type*        pointer;
    typedef  const value_type*  const_pointer;

// CREATION
// --------

    CGAL__Polyhedron_facet_const_circ() : It(0) {}
    CGAL__Polyhedron_facet_const_circ( const_pointer p) : It(p) {}
    CGAL__Polyhedron_facet_const_circ( It i) : It(i) {}

// OPERATIONS Forward Category
// ---------------------------

    const_pointer  ptr() const { return & It::operator*();}

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return It::operator==( It(NULL));
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const Self& i) const {
        return  It::operator==(i);
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }

    Self& operator++() {
        nt = (*nt).next();
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
        nt = (*nt).prev();
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    friend inline  iterator_category
    iterator_category( const Self&) {
        return iterator_category();
    }
    friend inline  value_type*
    value_type( const Self&) {
        return (value_type*)(0);
    }
    friend inline  difference_type*
    distance_type( const Self&) {
        return (difference_type*)(0);
    }
    friend inline  CGAL_Circulator_tag
    CGAL_query_circulator_or_iterator( const Self&) {
        return CGAL_Circulator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};
template < class Node, class It, class Ctg>
class CGAL__Polyhedron_vertex_circ : public It {
    // Ptr      nt;    // The internal node ptr inherited from It.
public:
    typedef  It  Base;
    typedef  CGAL__Polyhedron_vertex_circ<Node,It,Ctg> Self;

    typedef  Ctg                iterator_category;
    typedef  Node               value_type;
    typedef  ptrdiff_t          difference_type;
    typedef  size_t             size_type;
    typedef  value_type&        reference;
    typedef  const value_type&  const_reference;
    typedef  value_type*        pointer;
    typedef  const value_type*  const_pointer;

// CREATION
// --------

    CGAL__Polyhedron_vertex_circ() : It(0) {}
    //CGAL__Polyhedron_vertex_circ( pointer p) : It(p) {}
    CGAL__Polyhedron_vertex_circ( It i) : It(i) {}

// OPERATIONS Forward Category
// ---------------------------

    pointer  ptr() const { return & It::operator*();}

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return It::operator==( It(NULL));
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const Self& i) const {
        return  It::operator==(i);
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }

    Self& operator++() {
        nt = (*nt).next()->opposite();
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
        nt = (*nt).opposite()->prev();
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    friend inline  iterator_category
    iterator_category( const Self&) {
        return iterator_category();
    }
    friend inline  value_type*
    value_type( const Self&) {
        return (value_type*)(0);
    }
    friend inline  difference_type*
    distance_type( const Self&) {
        return (difference_type*)(0);
    }
    friend inline  CGAL_Circulator_tag
    CGAL_query_circulator_or_iterator( const Self&) {
        return CGAL_Circulator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};


template < class Node, class It, class Ctg>
class CGAL__Polyhedron_vertex_const_circ : public It {
    // Ptr      nt;    // The internal node ptr inherited from It.
public:
    typedef  It  Base;
    typedef  CGAL__Polyhedron_vertex_const_circ<Node,It,Ctg> Self;

    typedef  Ctg                iterator_category;
    typedef  Node               value_type;
    typedef  ptrdiff_t          difference_type;
    typedef  size_t             size_type;
    typedef  value_type&        reference;
    typedef  const value_type&  const_reference;
    typedef  value_type*        pointer;
    typedef  const value_type*  const_pointer;

// CREATION
// --------

    CGAL__Polyhedron_vertex_const_circ() : It(0) {}
    CGAL__Polyhedron_vertex_const_circ( const_pointer p) : It(p) {}
    CGAL__Polyhedron_vertex_const_circ( It i) : It(i) {}

// OPERATIONS Forward Category
// ---------------------------

    const_pointer  ptr() const { return & It::operator*();}

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return It::operator==( It(NULL));
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const Self& i) const {
        return  It::operator==(i);
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }

    Self& operator++() {
        nt = (*nt).next()->opposite();
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
        nt = (*nt).opposite()->prev();
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    friend inline  iterator_category
    iterator_category( const Self&) {
        return iterator_category();
    }
    friend inline  value_type*
    value_type( const Self&) {
        return (value_type*)(0);
    }
    friend inline  difference_type*
    distance_type( const Self&) {
        return (difference_type*)(0);
    }
    friend inline  CGAL_Circulator_tag
    CGAL_query_circulator_or_iterator( const Self&) {
        return CGAL_Circulator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class T>
struct CGAL_Polyhedron_circulator_traits {};

struct CGAL_Polyhedron_circulator_traits<CGAL_Tag_true> {
    typedef CGAL_Bidirectional_circulator_tag  iterator_category;
};

struct CGAL_Polyhedron_circulator_traits<CGAL_Tag_false> {
    typedef CGAL_Forward_circulator_tag  iterator_category;
};    
#endif // CGAL_POLYHEDRON_ITERATOR_3_H //
// EOF //
