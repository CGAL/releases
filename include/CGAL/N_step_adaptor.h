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
// file          : include/CGAL/N_step_adaptor.h
// package       : STL_Extension (2.6)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/04/07 18:31:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// An iterator/circulator adaptor doing n-steps per increment.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_N_STEP_ADAPTOR_H
#define CGAL_N_STEP_ADAPTOR_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

CGAL_BEGIN_NAMESPACE

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template < class I, int N, class Ref, class Ptr,
           class Val, class Dist, class Ctg>
#else
template < class I,
           int N,
           class Ref  = typename std::iterator_traits<I>::reference,
           class Ptr  = typename std::iterator_traits<I>::pointer,
           class Val  = typename std::iterator_traits<I>::value_type,
           class Dist = typename std::iterator_traits<I>::difference_type,
           class Ctg = typename std::iterator_traits<I>::iterator_category>
#endif
class N_step_adaptor {
protected:
    I        nt;    // The internal iterator.
public:
    typedef I                                        Iterator;
    typedef N_step_adaptor<I,N,Ref,Ptr,Val,Dist,Ctg> Self;
    typedef Ctg                                      iterator_category;
    typedef Val                                      value_type;
    typedef Dist                                     difference_type;
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    typedef Ref                                      reference;
    typedef Ptr                                      pointer;
#else
    typedef typename std::iterator_traits<I>::reference reference;
    typedef typename std::iterator_traits<I>::pointer   pointer;
#endif
    // Special for circulators.
    typedef _Circulator_size_traits<iterator_category,I> C_S_Traits;
    typedef typename  C_S_Traits::size_type              size_type;

// CREATION
// --------

    N_step_adaptor() {}
    N_step_adaptor( Iterator j) : nt(j) {}

// OPERATIONS Forward Category
// ---------------------------

    // Circulator stuff.
    typedef  I  Circulator;
    Circulator  current_circulator() const { return nt;}

    Iterator  current_iterator() const { return nt;}
    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return ( nt == NULL);
    }
    bool  operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool  operator==( const Self& i) const { return ( nt == i.nt); }
    bool  operator!=( const Self& i) const { return !(*this == i); }
    Ref   operator*()  const { return *nt; }
    Ptr   operator->() const { return nt.operator->(); }
    Self& operator++() {
        std::advance( nt, N);
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
        std::advance( nt, -N);
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }

// OPERATIONS Random Access Category
// ---------------------------------

    Self  min_circulator() const { return Self( nt.min_circulator()); }
    Self& operator+=( difference_type n) {
        nt += difference_type(N * n);
        return *this;
    }
    Self  operator+( difference_type n) const {
        Self tmp = *this;
        tmp.nt += difference_type(N * n);
        return tmp;
    }
#ifdef CGAL_CFG_NO_CONSTANTS_IN_FUNCTION_TEMPLATES
    friend inline
    Self
    operator+( difference_type n, Self i) {
        i = i + n;
        return i;
    }
#endif // CGAL_CFG_NO_CONSTANTS_IN_FUNCTION_TEMPLATES //
    Self& operator-=( difference_type n) {
        return operator+=( -n);
    }
    Self  operator-( difference_type n) const {
        Self tmp = *this;
        return tmp += -n;
    }
    difference_type  operator-( const Self& i) const { return (nt-i.nt)/N;}
    Ref  operator[]( difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    bool operator<( const Self& i) const { return ( nt < i.nt); }
    bool operator>( const Self& i) const { return i < *this; }
    bool operator<=( const Self& i) const { return !(i < *this); }
    bool operator>=( const Self& i) const { return !(*this < i); }
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    friend inline  iterator_category
    iterator_category( const Self&) { return iterator_category(); }
    friend inline  value_type*
    value_type( const Self&) { return (value_type*)(0); }
    friend inline  difference_type*
    distance_type( const Self&) { return (difference_type*)(0); }
    typedef _Circulator_traits<iterator_category> C_Traits;
    typedef typename  C_Traits::category  category;
    friend inline  category
    query_circulator_or_iterator( const Self&) { return category(); }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};
#ifndef CGAL_CFG_NO_CONSTANTS_IN_FUNCTION_TEMPLATES
template < class D, class I, int N, class Ref, class Ptr,
           class Val, class Dist, class Ctg>
inline
N_step_adaptor<I,N,Ref,Ptr,Val,Dist,Ctg>
operator+( D n, N_step_adaptor<I,N,Ref,Ptr,Val,Dist,Ctg> i) {
    return i += Dist(n);
}
#endif // CGAL_CFG_NO_CONSTANTS_IN_FUNCTION_TEMPLATES //

CGAL_END_NAMESPACE
#endif // CGAL_N_STEP_ADAPTOR_H //
// EOF //
