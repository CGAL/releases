// ======================================================================
//
// Copyright (c) 1997, 1998, 1999, 2000 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/N_step_adaptor_derived.h
// package       : STL_Extension (2.21)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2000/09/15 13:05:13 $
// author(s)     : Michael Hoffmann
//                 Lutz Kettner
//
//
// An iterator/circulator adaptor doing n-steps per increment.
// coordinator   : ?
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_N_STEP_ADAPTOR_DERIVED_H
#define CGAL_N_STEP_ADAPTOR_DERIVED_H 1
#include <CGAL/circulator.h>

CGAL_BEGIN_NAMESPACE

template < class I, int N>
class N_step_adaptor_derived : public I {
public:
    typedef I                               Iterator;
    typedef I                               Circulator;
    typedef N_step_adaptor_derived<I,N>     Self;
    typedef typename I::iterator_category   iterator_category;
    typedef typename I::value_type          value_type;
    typedef typename I::difference_type     difference_type;
    typedef typename I::reference           reference;
    typedef typename I::pointer             pointer;
    // Special for circulators.
    typedef I_Circulator_size_traits<iterator_category,I> C_S_Traits;
    typedef typename  C_S_Traits::size_type               size_type;

// CREATION
// --------

    N_step_adaptor_derived() {}
    N_step_adaptor_derived( Iterator j) : I(j) {}

    template <class II>
    N_step_adaptor_derived( const N_step_adaptor_derived<II,N>& j)
        : I( j.current_iterator()) {}

// OPERATIONS Forward Category
// ---------------------------

    Circulator current_circulator() const { return *this;}
    Iterator   current_iterator()   const { return *this;}

    Self& operator++() {
        std::advance( (I&)*this, N);
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
        std::advance( (I&)*this, -N);
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }

// OPERATIONS Random Access Category
// ---------------------------------

    Self  min_circulator() const { return Self( I::min_circulator()); }
    Self& operator+=( difference_type n) {
        I::operator+=( difference_type(N * n));
        return *this;
    }
    Self  operator+( difference_type n) const {
        Self tmp = *this;
        tmp += n;
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
    difference_type  operator-( const Self& i) const {
        return (I::operator-(i)) / N;
    }
    reference  operator[]( difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
#ifndef CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
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
#endif // CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};
#ifndef CGAL_CFG_NO_CONSTANTS_IN_FUNCTION_TEMPLATES
template < class I, int N>
inline
N_step_adaptor_derived<I,N>
operator+( typename N_step_adaptor_derived<I,N>::difference_type n,
           N_step_adaptor_derived<I,N> i)
{ return i += n; }
#endif // CGAL_CFG_NO_CONSTANTS_IN_FUNCTION_TEMPLATES //

CGAL_END_NAMESPACE
#endif // CGAL_N_STEP_ADAPTOR_DERIVED_H //
// EOF //
