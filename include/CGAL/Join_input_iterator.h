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
// file          : include/CGAL/Join_input_iterator.h
// package       : STL_Extension (2.6)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/04/07 18:31:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Join_input_iterator.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_JOIN_INPUT_ITERATOR_H
#define CGAL_JOIN_INPUT_ITERATOR_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

CGAL_BEGIN_NAMESPACE

template < class I1, class  Creator >
class Join_input_iterator_1 {
       // the join of one iterator `i1'. Applies `Creator' with
       // one argument `*i1'. `value_type' is equal to
       // `Creator::result_type'.
public:
    typedef Join_input_iterator_1<I1,Creator>  Self;
    typedef std::input_iterator_tag            iterator_category;
    typedef typename Creator::result_type      value_type;
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    typedef std::ptrdiff_t                     difference_type;
#else
    typedef std::iterator_traits<I1>           ITraits;
    typedef typename ITraits::difference_type  difference_type;
#endif
    typedef  const value_type&                 reference;
    typedef  const value_type*                 pointer;

protected:
    I1          j1;    // The 1st internal iterator.
    value_type  val;   // The current (internal) value.

public:
// CREATION
// --------

    Join_input_iterator_1() {}
    Join_input_iterator_1( I1 i1) : j1(i1), val(Creator()(*j1)) {}

// OPERATIONS Forward Category
// ---------------------------

    I1  current_iterator1() const { return j1;}

    bool operator==( const Self& i) const { return ( j1 == i.j1); }
    bool operator!=( const Self& i) const { return !(*this == i); }
    reference  operator*()    const { return val; }
    pointer    operator->()   const { return &val; }
    Self& operator++() {
        ++j1;
        val = Creator()(*j1);
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
    friend inline  std::input_iterator_tag
    iterator_category( const Self&){
        return std::input_iterator_tag();
    }
    friend inline  difference_type*
    distance_type( const Self&) {
        return (difference_type*)(0);
    }
    friend inline  Iterator_tag
    query_circulator_or_iterator( const Self&) {
        return Iterator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class I1, class I2, class  Creator >
class Join_input_iterator_2 {
       // the join of two iterators `i1' and `i2'. Applies `Creator' with
       // two arguments `*i1' and `*i2'. `value_type' is equal to
       // `Creator::result_type'.
public:
    typedef Join_input_iterator_2<I1,I2,Creator> Self;

    typedef std::input_iterator_tag              iterator_category;
    typedef typename Creator::result_type        value_type;
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    typedef std::ptrdiff_t                       difference_type;
#else
    typedef std::iterator_traits<I1>             ITraits;
    typedef typename ITraits::difference_type    difference_type;
#endif
    typedef const value_type&                    reference;
    typedef const value_type*                    pointer;

protected:
    I1          j1;    // The 1st internal iterator.
    I2          j2;    // The 2nd internal iterator.
    value_type  val;   // The current (internal) value.

public:
// CREATION
// --------

    Join_input_iterator_2() {}
    Join_input_iterator_2( I1 i1, I2 i2)
        : j1(i1), j2(i2), val(Creator()(*j1,*j2)) {}

// OPERATIONS Forward Category
// ---------------------------

    I1  current_iterator1() const { return j1;}
    I2  current_iterator2() const { return j2;}

    bool operator==( const Self& i) const {
        return ( j1 == i.j1 && j2 == i.j2);
    }
    bool operator!=( const Self& i) const { return !(*this == i); }
    reference operator*() const { return val; }
    pointer   operator->() const { return &val; }
    Self& operator++() {
        ++j1;
        ++j2;
        val = Creator()(*j1,*j2);
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
    friend inline  std::input_iterator_tag
    iterator_category( const Self&){
        return std::input_iterator_tag();
    }
    friend inline  difference_type*
    distance_type( const Self&) {
        return (difference_type*)(0);
    }
    friend inline  Iterator_tag
    query_circulator_or_iterator( const Self&) {
        return Iterator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class I1, class I2, class I3, class  Creator >
class Join_input_iterator_3 {
       // the join of two iterators `i1' up to `i3'. Applies `Creator' with
       // three arguments `*i1' up to `*i3'. `value_type' is equal to
       // `Creator::result_type'.
public:
    typedef Join_input_iterator_3<I1,I2,I3,Creator> Self;

    typedef std::input_iterator_tag                 iterator_category;
    typedef typename Creator::result_type           value_type;
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    typedef std::ptrdiff_t                          difference_type;
#else
    typedef std::iterator_traits<I1>                ITraits;
    typedef typename ITraits::difference_type       difference_type;
#endif
    typedef const value_type&                       reference;
    typedef const value_type*                       pointer;

protected:
    I1          j1;    // The 1st internal iterator.
    I2          j2;    // The 2nd internal iterator.
    I3          j3;    // The 3rd internal iterator.
    value_type  val;   // The current (internal) value.

public:
// CREATION
// --------

    Join_input_iterator_3() {}
    Join_input_iterator_3( I1 i1, I2 i2, I3 i3)
        : j1(i1), j2(i2), j3(i3), val(Creator()(*j1,*j2,*j3)) {}

// OPERATIONS Forward Category
// ---------------------------

    I1  current_iterator1() const { return j1;}
    I2  current_iterator2() const { return j2;}
    I3  current_iterator3() const { return j3;}

    bool operator==( const Self& i) const {
        return ( j1 == i.j1 && j2 == i.j2 && j3 == i.j3);
    }
    bool operator!=( const Self& i) const { return !(*this == i); }
    reference operator*() const { return val; }
    pointer   operator->() const { return &val; }
    Self& operator++() {
        ++j1;
        ++j2;
        ++j3;
        val = Creator()(*j1,*j2,*j3);
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
    friend inline  std::input_iterator_tag
    iterator_category( const Self&){
        return std::input_iterator_tag();
    }
    friend inline  difference_type*
    distance_type( const Self&) {
        return (difference_type*)(0);
    }
    friend inline  Iterator_tag
    query_circulator_or_iterator( const Self&) {
        return Iterator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class I1, class I2, class I3, class I4, class  Creator >
class Join_input_iterator_4 {
       // the join of two iterators `i1' up to `i4'. Applies `Creator' with
       // four arguments `*i1' up to `*i4'. `value_type' is equal to
       // `Creator::result_type'.
public:
    typedef Join_input_iterator_4<I1,I2,I3,I4,Creator> Self;

    typedef std::input_iterator_tag             iterator_category;
    typedef typename Creator::result_type       value_type;
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    typedef std::ptrdiff_t                      difference_type;
#else
    typedef std::iterator_traits<I1>            ITraits;
    typedef typename ITraits::difference_type   difference_type;
#endif
    typedef const value_type&                   reference;
    typedef const value_type*                   pointer;

protected:
    I1          j1;    // The 1st internal iterator.
    I2          j2;    // The 2nd internal iterator.
    I3          j3;    // The 3rd internal iterator.
    I4          j4;    // The 4th internal iterator.
    value_type  val;   // The current (internal) value.

public:
// CREATION
// --------

    Join_input_iterator_4() {}
    Join_input_iterator_4( I1 i1, I2 i2, I3 i3, I4 i4)
        : j1(i1), j2(i2), j3(i3), j4(i4), val(Creator()(*j1,*j2,*j3,*j4)){}

// OPERATIONS Forward Category
// ---------------------------

    I1  current_iterator1() const { return j1;}
    I2  current_iterator2() const { return j2;}
    I3  current_iterator3() const { return j3;}
    I4  current_iterator4() const { return j4;}

    bool operator==( const Self& i) const {
        return ( j1 == i.j1 &&
                 j2 == i.j2 &&
                 j3 == i.j3 &&
                 j4 == i.j4);
    }
    bool operator!=( const Self& i) const { return !(*this == i); }
    reference operator*() const { return val; }
    pointer   operator->() const { return &val; }
    Self& operator++() {
        ++j1;
        ++j2;
        ++j3;
        ++j4;
        val = Creator()(*j1,*j2,*j3,*j4);
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
    friend inline  std::input_iterator_tag
    iterator_category( const Self&){
        return std::input_iterator_tag();
    }
    friend inline  difference_type*
    distance_type( const Self&) {
        return (difference_type*)(0);
    }
    friend inline  Iterator_tag
    query_circulator_or_iterator( const Self&) {
        return Iterator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class I1, class I2, class I3, class I4, class I5,
           class  Creator >
class Join_input_iterator_5 {
       // the join of two iterators `i1' up to `i5'. Applies `Creator' with
       // five arguments `*i1' up to `*i5'. `value_type' is equal to
       // `Creator::result_type'.
public:
    typedef Join_input_iterator_5<I1,I2,I3,I4,I5,Creator> Self;

    typedef std::input_iterator_tag             iterator_category;
    typedef typename Creator::result_type       value_type;
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
    typedef std::ptrdiff_t                      difference_type;
#else
    typedef std::iterator_traits<I1>            ITraits;
    typedef typename ITraits::difference_type   difference_type;
#endif
    typedef const value_type&                   reference;
    typedef const value_type*                   pointer;

protected:
    I1          j1;    // The 1st internal iterator.
    I2          j2;    // The 2nd internal iterator.
    I3          j3;    // The 3rd internal iterator.
    I4          j4;    // The 4th internal iterator.
    I5          j5;    // The 5th internal iterator.
    value_type  val;   // The current (internal) value.

public:
// CREATION
// --------

    Join_input_iterator_5() {}
    Join_input_iterator_5( I1 i1, I2 i2, I3 i3, I4 i4, I5 i5)
        : j1(i1), j2(i2), j3(i3), j4(i4), j5(i5),
          val(Creator()(*j1,*j2,*j3,*j4,*j5)) {}

// OPERATIONS Forward Category
// ---------------------------

    I1  current_iterator1() const { return j1;}
    I2  current_iterator2() const { return j2;}
    I3  current_iterator3() const { return j3;}
    I4  current_iterator4() const { return j4;}
    I5  current_iterator5() const { return j5;}

    bool operator==( const Self& i) const {
        return ( j1 == i.j1 &&
                 j2 == i.j2 &&
                 j3 == i.j3 &&
                 j4 == i.j4 &&
                 j5 == i.j5);
    }
    bool operator!=( const Self& i) const { return !(*this == i); }
    reference operator*() const { return val; }
    pointer   operator->() const { return &val; }
    Self& operator++() {
        ++j1;
        ++j2;
        ++j3;
        ++j4;
        ++j5;
        val = Creator()(*j1,*j2,*j3,*j4,*j5);
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
    friend inline  std::input_iterator_tag
    iterator_category( const Self&){
        return std::input_iterator_tag();
    }
    friend inline  difference_type*
    distance_type( const Self&) {
        return (difference_type*)(0);
    }
    friend inline  Iterator_tag
    query_circulator_or_iterator( const Self&) {
        return Iterator_tag();
    }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

CGAL_END_NAMESPACE
#endif // CGAL_JOIN_INPUT_ITERATOR_H //
// EOF //
