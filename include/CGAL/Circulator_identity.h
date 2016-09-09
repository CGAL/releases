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
// file          : include/CGAL/Circulator_identity.h
// package       : STL_Extension (1.17)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.12 $
// revision_date : $Date: 1998/10/08 14:35:33 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// An circulator adaptor for the identity function.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CIRCULATOR_IDENTITY_H
#define CGAL_CIRCULATOR_IDENTITY_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

#ifdef CGAL_CFG_NO_DEFAULT_PREVIOUS_TEMPLATE_ARGUMENTS
template < class C, class Ref, class Ptr>
#else
template < class C,
           class Ref = typename C::reference,
           class Ptr = typename C::pointer>
#endif
class CGAL_Circulator_identity {
private:
    C        nt;    // The internal circulator.
public:
    typedef C  Circulator;
    typedef CGAL_Circulator_identity<C,Ref,Ptr> Self;

    typedef typename  C::iterator_category   iterator_category;
    typedef typename  C::value_type          value_type;
    typedef typename  C::difference_type     difference_type;
    typedef typename  C::size_type           size_type;
    typedef typename  C::reference           reference;
    typedef typename  C::const_reference     const_reference;
    typedef typename  C::pointer             pointer;
    typedef typename  C::const_pointer       const_pointer;

// CREATION
// --------

    CGAL_Circulator_identity() {}
    CGAL_Circulator_identity( Circulator j) : nt(j) {}

// OPERATIONS Forward Category
// ---------------------------

    Circulator  current_circulator() const { return nt;}

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return ( nt == NULL);                                    //###//
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
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
    Self  min_circulator() const {
        return Self( nt.min_circulator());                       //###//
    }
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
    friend inline  CGAL_Circulator_tag
    CGAL_query_circulator_or_iterator( const Self&) {
        return CGAL_Circulator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class Dist, class C, class Ref, class Ptr>
inline
CGAL_Circulator_identity<C,Ref,Ptr>
operator+( Dist n, CGAL_Circulator_identity<C,Ref,Ptr> i) {
    return i += n;
}
#endif // CGAL_CIRCULATOR_IDENTITY_H //
// EOF //
