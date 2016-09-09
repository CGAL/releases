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
// file          : include/CGAL/Iterator_identity.h
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

#ifndef CGAL_ITERATOR_IDENTITY_H
#define CGAL_ITERATOR_IDENTITY_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

CGAL_BEGIN_NAMESPACE

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class I, class Ref, class Ptr, class Val, class Dist, class Ctg>
#else
template < class I,
           class Ref  = typename std::iterator_traits<I>::reference,
           class Ptr  = typename std::iterator_traits<I>::pointer,
           class Val  = typename std::iterator_traits<I>::value_type,
           class Dist = typename std::iterator_traits<I>::difference_type,
           class Ctg = typename std::iterator_traits<I>::iterator_category>
#endif
class Iterator_identity {
private:
    I        nt;    // The internal iterator.
public:
    typedef I      Iterator;
    typedef Iterator_identity<I,Ref,Ptr,Val,Dist,Ctg>   Self;
    typedef Ctg    iterator_category;
    typedef Val    value_type;
    typedef Dist   difference_type;
    typedef Ref    reference;
    typedef Ptr    pointer;

// CREATION
// --------

    Iterator_identity() {}
    Iterator_identity( Iterator j) : nt(j) {}

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
    Ptr  operator->() const {
        return nt.operator->();                                  //###//
    }
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
    friend inline  Iterator_tag
    query_circulator_or_iterator( const Self&) {
        return Iterator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class D, class I, class Ref, class Ptr, class Val,
           class Dist, class Ctg>
inline
Iterator_identity<I,Ref,Ptr,Val,Dist,Ctg>
operator+( D n, Iterator_identity<I,Ref,Ptr,Val,Dist,Ctg> i) {
    return i += Dist(n);
}

CGAL_END_NAMESPACE
#endif // CGAL_ITERATOR_IDENTITY_H //
// EOF //
