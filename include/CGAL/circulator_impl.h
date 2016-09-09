/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// | Support to build own circulators.
// | Extracted from circulator.fw
// | $Revision: 1.9 $
// | $Date: 1997/06/24 06:22:17 $
// | 1997   Lutz Kettner

#ifndef CGAL_CIRCULATOR_IMPL_H
#define CGAL_CIRCULATOR_IMPL_H 1

#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

// #line 3976 "circulator.any"
template < class  S>
class CGAL_Forward_circulator_over_struct
    : public CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>{
public:

// DEFINITION
//
// Given a structure `S' that have a data member of type `S*' that
// realizes a ring like data structure the adaptor
// `CGAL_Forward_circulator_over_struct< S, S* S::* next = &S::next>'
// provides a forward circulator for it. If the structure `S' has
// additionally a second data member of type `S*' that realizes the
// reverse direction the adaptor
// `CGAL_Bidirectional_circulator_over_struct< S, S* S::* next = &S::next,
// S* S::* prev = &S::prev>' provides a bidirectional circulator for it.
// In addition, adaptors for const circulators are provided with the names
// `CGAL_Forward_const_circulator_over_struct< S, S* S::* next = &S::next>'
// and `CGAL_Bidirectional_const_circulator_over_struct< S, S* S::* next =
// &S::next, S* S::* prev = &S::prev>'. A circulator becomes invalid
// whenever the object it refers to gets deleted from the data structure.
//
// As long as default template parameters are not supported the adaptors
// will not provide the member pointer template parameters. The adaptors
// will use the default values. All adaptors have a counterpart with the
// suffix `_mptr' supporting all template parameters, but no default
// settings. As soon as member pointers are supported by our reference
// compilers\footnote{The SGI CC and the Gnu g++ do support member
// pointers in template arguments, the Sun CC does not. The older C++
// standard drafts rule out this application of template arguments, the
// new drafts include it.}, these counterparts can be used.
//
// PARAMETERS
//
// `S' is a structure or class. The public data members of type `S*' which
// form the linked structure are given as member pointers `S* S::* next'
// and `S* S::* prev' . Both have default values `&S::next' and `&S::prev'
// respectively.
//
// Please note that the correct signature for the member pointer argument
// for a const circulator would be `const S* S::*next', but one cannot
// implement a ring structure in this way since member variables cannot be
// overloaded as compared to the member functions that are used in the
// next section for circulators for classes. Thus, the const circulator is
// an easy way to achieve a typesafe read only access to a pointered data
// structure.
//
// TYPES

    typedef S         value_type;
    typedef S&        reference;
    typedef const S&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// CREATION
//
// New creation variable is: `circ'

    CGAL_Forward_circulator_over_struct() {}
        // a circulator `circ' with singular value.

    CGAL_Forward_circulator_over_struct( S* ptr)
        : CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>( ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Forward_circulator_over_struct(
        const CGAL_Forward_circulator_over_struct<S>& c)
        : CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>( c) {}

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Forward_circulator_over_struct<S>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Forward_circulator_over_struct<S>& c
    ) const {
        return !(*this == c);
    }
    S&  operator*() const { return *(S*)_ptr;}

    CGAL_Forward_circulator_over_struct<S>&
    operator++() {
        _ptr = ((S*)_ptr)->next;
        return *this;
    }
    CGAL_Forward_circulator_over_struct<S>
    operator++(int) {
        CGAL_Forward_circulator_over_struct<S> tmp = *this;
        ++*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Forward_circulator_over_struct<S>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline  S* value_type(
        const
    CGAL_Forward_circulator_over_struct<S>&) {
        return ( S*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_circulator_over_struct<S>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_circulator_over_struct<S>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 4078 "circulator.any"
          
};


template < class  S>
class CGAL_Forward_const_circulator_over_struct
    : public CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>{
public:

// TYPES

    typedef S         value_type;
    typedef S&        reference;
    typedef const S&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// CREATION

    CGAL_Forward_const_circulator_over_struct() {}
        // a circulator `circ' with singular value.

    CGAL_Forward_const_circulator_over_struct( const S* ptr)
        : CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>( (void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Forward_const_circulator_over_struct(
        const CGAL_Forward_const_circulator_over_struct<S>& c)
        : CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>( c) {}

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Forward_const_circulator_over_struct<S>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Forward_const_circulator_over_struct<S>& c
    ) const {
        return !(*this == c);
    }
    const S&  operator*() const { return *(S*)_ptr;}

    CGAL_Forward_const_circulator_over_struct<S>&
    operator++() {
        _ptr = ((S*)_ptr)->next;
        return *this;
    }
    CGAL_Forward_const_circulator_over_struct<S>
    operator++(int) {
        CGAL_Forward_const_circulator_over_struct<S> tmp = *this;
        ++*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Forward_const_circulator_over_struct<S>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline  S* value_type(
        const
    CGAL_Forward_const_circulator_over_struct<S>&) {
        return ( S*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_const_circulator_over_struct<S>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_const_circulator_over_struct<S>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 4141 "circulator.any"
          
};


template < class  S>
class CGAL_Bidirectional_circulator_over_struct
    : public CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>{
public:

// TYPES

    typedef S         value_type;
    typedef S&        reference;
    typedef const S&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// CREATION
//
// New creation variable is: `circ'

    CGAL_Bidirectional_circulator_over_struct() {}
        // a circulator `circ' with singular value.

    CGAL_Bidirectional_circulator_over_struct( S* ptr)
        : CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>( ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Bidirectional_circulator_over_struct(
        const CGAL_Bidirectional_circulator_over_struct<S>& c)
        : CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>( c) {}

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Bidirectional_circulator_over_struct<S>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Bidirectional_circulator_over_struct<S>& c
    ) const {
        return !(*this == c);
    }
    S&  operator*() const { return *(S*)_ptr;}

    CGAL_Bidirectional_circulator_over_struct<S>&
    operator++() {
        _ptr = ((S*)_ptr)->next;
        return *this;
    }
    CGAL_Bidirectional_circulator_over_struct<S>
    operator++(int) {
        CGAL_Bidirectional_circulator_over_struct<S> tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_circulator_over_struct<S>&
    operator--() {
        _ptr = ((S*)_ptr)->prev;
        return *this;
    }
    CGAL_Bidirectional_circulator_over_struct<S>
    operator--(int) {
        CGAL_Bidirectional_circulator_over_struct<S> tmp = *this;
        --*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Bidirectional_circulator_over_struct<S>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline  S* value_type(
        const
    CGAL_Bidirectional_circulator_over_struct<S>&) {
        return ( S*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_circulator_over_struct<S>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_circulator_over_struct<S>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 4217 "circulator.any"
          
};


template < class  S>
class CGAL_Bidirectional_const_circulator_over_struct
    : public CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>{
public:

// TYPES

    typedef S         value_type;
    typedef S&        reference;
    typedef const S&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// CREATION

    CGAL_Bidirectional_const_circulator_over_struct() {}
        // a circulator `circ' with singular value.

    CGAL_Bidirectional_const_circulator_over_struct( const S* ptr)
        : CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>( (void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Bidirectional_const_circulator_over_struct(
        const CGAL_Bidirectional_const_circulator_over_struct<S>& c)
        : CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>( c) {}

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Bidirectional_const_circulator_over_struct<S>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Bidirectional_const_circulator_over_struct<S>& c
    ) const {
        return !(*this == c);
    }
    const S&  operator*() const { return *(S*)_ptr;}

    CGAL_Bidirectional_const_circulator_over_struct<S>&
    operator++() {
        _ptr = ((S*)_ptr)->next;
        return *this;
    }
    CGAL_Bidirectional_const_circulator_over_struct<S>
    operator++(int) {
        CGAL_Bidirectional_const_circulator_over_struct<S> tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_const_circulator_over_struct<S>&
    operator--() {
        _ptr = ((S*)_ptr)->prev;
        return *this;
    }
    CGAL_Bidirectional_const_circulator_over_struct<S>
    operator--(int) {
        CGAL_Bidirectional_const_circulator_over_struct<S> tmp = *this;
        --*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Bidirectional_const_circulator_over_struct<S>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline  S* value_type(
        const
    CGAL_Bidirectional_const_circulator_over_struct<S>&) {
        return ( S*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_const_circulator_over_struct<S>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_const_circulator_over_struct<S>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 4291 "circulator.any"
          
};
// #line 113 "circulator.any"
  
// #line 4742 "circulator.any"
template < class  C>
class CGAL_Forward_circulator_over_class
    : public CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>{
public:

// DEFINITION
//
// Given a class `C' that have member functions with return values of type
// `C*' that realizes a ring like data structure the adaptor
// `CGAL_Forward_circulator_over_class< C, C* (C::*next)() = &C::next>'
// provides a forward circulator for it. If the class `C' has additionally
// a second member function that realizes the reverse direction the
// adaptor `CGAL_Bidirectional_circulator_over_class< C, C* (C::*next)() =
// &C::next, C* (C::*prev)() = &C::prev>' provides a bidirectional
// circulator for it. In addition, adaptors for const circulators are
// provided with the names `CGAL_Forward_const_circulator_over_class< C,
// const C* (C::*next)() const = &C::next>' and
// `CGAL_Bidirectional_const_circulator_over_class< C, const C* (C::*next)(
// ) const = &C::next, const C* (C::*prev)() const = &C::prev>'. A
// circulator becomes invalid whenever the object it refers to gets
// deleted from the data structure.
//
// As long as default template parameters are not supported the adaptors
// will not provide the member pointer template parameters. The adaptors
// will use the default values. All adaptors have a counterpart with the
// suffix `_mptr' supporting all template parameters, but no default
// settings. As soon as member pointers are supported by our reference
// compilers\footnote{The SGI CC and the Gnu g++ do support member
// pointers in template arguments, the Sun CC does not. The older C++
// standard drafts rule out this application of template arguments, the
// new drafts include it.}, these counterparts can be used.
//
// PARAMETERS
//
// `C' is a structure or class. The public member functions with return
// type `C*' which form the linked structure are given as member pointers
// `C* (C::*next)()' and `C* (C::*prev)()' . For the const circulators the
// member pointers are of the form `const C* (C::*next)() const' and
// `const C* (C::*prev)() const' . Both have default values `&C::next' and
// `&C::prev' respectively.
//
// TYPES

    typedef C         value_type;
    typedef C&        reference;
    typedef const C&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// New creation variable is: `circ'
//
// CREATION

    CGAL_Forward_circulator_over_class() {}
        // a circulator `circ' with a singular value.

    CGAL_Forward_circulator_over_class( C* ptr)
        : CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>( ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Forward_circulator_over_class(
        const CGAL_Forward_circulator_over_class<C>& c)
        : CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>( c) {}

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Forward_circulator_over_class<C>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Forward_circulator_over_class<C>& c
    ) const {
        return !(*this == c);
    }
    C&  operator*() const { return *(C*)_ptr;}

    CGAL_Forward_circulator_over_class<C>&
    operator++() {
        _ptr = ((C*)_ptr)->next();
        return *this;
    }
    CGAL_Forward_circulator_over_class<C>
    operator++(int) {
        CGAL_Forward_circulator_over_class<C> tmp = *this;
        ++*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Forward_circulator_over_class<C>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline  C* value_type(
        const
    CGAL_Forward_circulator_over_class<C>&) {
        return ( C*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_circulator_over_class<C>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_circulator_over_class<C>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 4840 "circulator.any"
          
};

template < class  C>
class CGAL_Forward_const_circulator_over_class
    : public CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>{
public:
//
// CREATION

    CGAL_Forward_const_circulator_over_class() {}
        // a circulator `circ' with singular value.

    CGAL_Forward_const_circulator_over_class( const C* ptr)
        : CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>( (void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Forward_const_circulator_over_class(
        const CGAL_Forward_const_circulator_over_class<C>& c)
        : CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>( c) {}

// TYPES

    typedef C         value_type;
    typedef C&        reference;
    typedef const C&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

//
// OPERATIONS


    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Forward_const_circulator_over_class<C>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Forward_const_circulator_over_class<C>& c
    ) const {
        return !(*this == c);
    }
    const C&  operator*() const { return *(C*)_ptr;}

    CGAL_Forward_const_circulator_over_class<C>&
    operator++() {
        _ptr = (void*)(((C*)_ptr)->next());
        return *this;
    }
    CGAL_Forward_const_circulator_over_class<C>
    operator++(int) {
        CGAL_Forward_const_circulator_over_class<C> tmp = *this;
        ++*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Forward_const_circulator_over_class<C>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline  C* value_type(
        const
    CGAL_Forward_const_circulator_over_class<C>&) {
        return ( C*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_const_circulator_over_class<C>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_const_circulator_over_class<C>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 4904 "circulator.any"
          
};

template < class  C>
class CGAL_Bidirectional_circulator_over_class
    : public CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>{
public:
//
// TYPES

    typedef C         value_type;
    typedef C&        reference;
    typedef const C&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// New creation variable is: `circ'
//
// CREATION

    CGAL_Bidirectional_circulator_over_class() {}
        // a circulator `circ' with singular value.

    CGAL_Bidirectional_circulator_over_class( C* ptr)
        : CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>( ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Bidirectional_circulator_over_class(
        const CGAL_Bidirectional_circulator_over_class<C>& c)
        : CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>( c) {}

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Bidirectional_circulator_over_class<C>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Bidirectional_circulator_over_class<C>& c
    ) const {
        return !(*this == c);
    }
    C&  operator*() const { return *(C*)_ptr;}

    CGAL_Bidirectional_circulator_over_class<C>&
    operator++() {
        _ptr = ((C*)_ptr)->next();
        return *this;
    }
    CGAL_Bidirectional_circulator_over_class<C>
    operator++(int) {
        CGAL_Bidirectional_circulator_over_class<C> tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_circulator_over_class<C>&
    operator--() {
        _ptr = ((C*)_ptr)->prev();
        return *this;
    }
    CGAL_Bidirectional_circulator_over_class<C>
    operator--(int) {
        CGAL_Bidirectional_circulator_over_class<C> tmp = *this;
        --*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Bidirectional_circulator_over_class<C>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline  C* value_type(
        const
    CGAL_Bidirectional_circulator_over_class<C>&) {
        return ( C*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_circulator_over_class<C>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_circulator_over_class<C>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 4980 "circulator.any"
          
};

template < class  C>
class CGAL_Bidirectional_const_circulator_over_class
    : public CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>{
public:
//
// TYPES

    typedef C         value_type;
    typedef C&        reference;
    typedef const C&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

//
// CREATION

    CGAL_Bidirectional_const_circulator_over_class() {}
        // a circulator `circ' with singular value.

    CGAL_Bidirectional_const_circulator_over_class( const C* ptr)
        : CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>( (void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Bidirectional_const_circulator_over_class(
        const CGAL_Bidirectional_const_circulator_over_class<C>& c)
        : CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>( c) {}

//
// OPERATIONS


    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Bidirectional_const_circulator_over_class<C>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Bidirectional_const_circulator_over_class<C>& c
    ) const {
        return !(*this == c);
    }
    const C&  operator*() const { return *(C*)_ptr;}

    CGAL_Bidirectional_const_circulator_over_class<C>&
    operator++() {
        _ptr = (void*)(((C*)_ptr)->next());
        return *this;
    }
    CGAL_Bidirectional_const_circulator_over_class<C>
    operator++(int) {
        CGAL_Bidirectional_const_circulator_over_class<C> tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_const_circulator_over_class<C>&
    operator--() {
        _ptr = (void*)(((C*)_ptr)->prev());
        return *this;
    }
    CGAL_Bidirectional_const_circulator_over_class<C>
    operator--(int) {
        CGAL_Bidirectional_const_circulator_over_class<C> tmp = *this;
        --*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Bidirectional_const_circulator_over_class<C>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline  C* value_type(
        const
    CGAL_Bidirectional_const_circulator_over_class<C>&) {
        return ( C*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_const_circulator_over_class<C>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_const_circulator_over_class<C>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 5056 "circulator.any"
          
};
// #line 114 "circulator.any"
  
// #line 5508 "circulator.any"
template < class A, class T, class U, class I>
class CGAL_Circulator_over_array
    : public CGAL_Random_access_circulator_ptrbase<T,I>{
    U _size;
    U _i;
public:

// DEFINITION
//
// Given a data structure `A' that provides random access with an index of
// type `U' to its sequence of stored elements of type `T' with a member
// function `access' the adaptor \ccClassTemplateName provides a random
// access circulator for `A'. The corresponding const circulator is
// `CGAL_Const_circulator_over_array< A, T, U, I, const T& (A::* access)(U
// i) const>'. All circulators for an array `a' become invalid whenever
// `a' changes its size (due to deletions or insertions).
//
// PARAMETERS
//
// `A' is a random access data structure and `T' its value type. `U' is
// the unsigned integral type carrying the size of the array and the
// actual index within the container. `I' is the signed integral type used
// as distance type and as index type in the random access circulator. The
// member function `access' is given as a member pointer `T& (A::* access)
// (U i)' or `const T& (A::* access)(U i) const' for the const circulator.
//
// TYPES

    typedef A         Array;
    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef U         size_type;
    typedef I         difference_type;

// New creation variable is: `circ'
//
// CREATION

    CGAL_Circulator_over_array() : _size(0), _i(0) {}
        // a circulator `circ' with singular value.

    CGAL_Circulator_over_array( A& array, U size, U start = 0)
        : CGAL_Random_access_circulator_ptrbase<T,I>( &array),
          _size( size), _i(start) {}
        // a circulator `circ' initialized to refer to the element
        // `(array.*access)(start)'. The circulator `circ' contains a
        // singular value if `start >= size'. Precondition: The
        // expressions `(array.*access)(i)' are valid in the range
        // 0 <= i < `size' .

    CGAL_Circulator_over_array(
        const CGAL_Circulator_over_array<A, T, U, I>& c)
        : CGAL_Random_access_circulator_ptrbase<T,I>( c),
          _size( c._size), _i(c._i) {}

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _i >= _size;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Circulator_over_array< A, T, U, I>& c
    ) const {
        CGAL_assertion( _ptr  == c._ptr);  // do they belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i == c._i;
    }
    bool operator!=(
        const CGAL_Circulator_over_array< A, T, U, I>& c
    ) const {
        return !(*this == c);
    }
    T&  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        return ((A*)_ptr)->operator[](_i);
    }
    CGAL_Circulator_over_array< A, T, U, I>&
    operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        ++ _i;
        if ( _i >= _size)
            _i = 0;
        return *this;
    }
    CGAL_Circulator_over_array< A, T, U, I>
    operator++(int) {
        CGAL_Circulator_over_array< A, T, U, I> tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Circulator_over_array< A, T, U, I>&
    operator--() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        if ( _i <= 0)
            _i = _size - 1;
        else
            -- _i;
        return *this;
    }
    CGAL_Circulator_over_array< A, T, U, I>
    operator--(int) {
        CGAL_Circulator_over_array< A, T, U, I> tmp = *this;
        --*this;
        return tmp;
    }
    CGAL_Circulator_over_array< A, T, U, I>&
    operator+=( I n);

    CGAL_Circulator_over_array< A, T, U, I>
    operator+( I n) const {
        CGAL_Circulator_over_array< A, T, U, I> tmp = *this;
        return tmp += n;
    }
    CGAL_Circulator_over_array< A, T, U, I>&
    operator-=( I n) {
        return operator+=( -n);
    }
    CGAL_Circulator_over_array< A, T, U, I>
    operator-( I n) const {
        CGAL_Circulator_over_array< A, T, U, I> tmp = *this;
        return tmp += -n;
    }
    I
    operator-( const CGAL_Circulator_over_array< A, T, U, I>& c)
               const {
        CGAL_assertion( _ptr  == c._ptr);  // do they belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i - c._i;
    }
    T&  operator[](I n) const {
        CGAL_Circulator_over_array< A, T, U, I> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    // no relational ordering

    // Hack! Probably not working with the official standard, but
    // the official way is not working yet, see below.
    friend inline
    CGAL_Circulator_over_array< A, T, U, I>
    operator+( I n, const
               CGAL_Circulator_over_array< A, T, U, I>& circ) {
        CGAL_Circulator_over_array< A, T, U, I> tmp = circ;
        return tmp += n;
    }
    CGAL_Circulator_over_array<A, T, U, I>
    min_circulator() {
        return CGAL_Circulator_over_array<A, T, U, I>( *((A*)_ptr), _size);
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  I* distance_type(
        const
    CGAL_Circulator_over_array< A, T, U, I>&) {
        return ( I*)(0);
    }
    friend inline  T* value_type(
        const
    CGAL_Circulator_over_array< A, T, U, I>&) {
        return ( T*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(
    CGAL_Circulator_over_array< A, T, U, I>) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Circulator_over_array< A, T, U, I>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 5666 "circulator.any"
          
};

// This is how the friend declaration from above should
// be implemented, however it is not working yet.
/* ...
template < class  A, class  T, class U, class  I>
inline
CGAL_Circulator_over_array< A, T, U, I>
operator+( I n, const
           CGAL_Circulator_over_array< A, T, U, I>& circ) {
    CGAL_Circulator_over_array< A, T, U, I> tmp = circ;
    return tmp += n;
}
... */

template < class A, class T, class U, class I>
CGAL_Circulator_over_array< A, T, U, I>&
CGAL_Circulator_over_array< A, T, U, I>::
operator+=( I n) {
    CGAL_assertion( _ptr != NULL);
    CGAL_assertion( _i < _size);
    _i = CGAL_non_negative_mod( (I)(_i) + n, _size);
    CGAL_assertion( _i < _size);
    return *this;
}

template < class  A, class  T, class U, class  I>
class CGAL_Const_circulator_over_array
    : public CGAL_Random_access_circulator_ptrbase<T,I> {
    U _size;
    U _i;
public:

// TYPES

    typedef A         Array;
    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef U         size_type;
    typedef I         difference_type;

// New creation variable is: `circ'
//
// CREATION

    CGAL_Const_circulator_over_array() : _size(0), _i(0) {}
        // a const circulator `circ' with singular value.

    CGAL_Const_circulator_over_array( const A& array, U size, U start = 0)
        : CGAL_Random_access_circulator_ptrbase<T,I>(
              (void*)(&array)), _size( size), _i(start) {}
        // a const circulator `circ' initialized to refer to the element
        // `(array.*access)(start)'. The circulator `circ' contains a
        // singular value if `start >= size'. Precondition: The
        // expressions `(array.*access)(i)' are valid in the range
        // 0 <= i < `size' .

    CGAL_Const_circulator_over_array(
        const CGAL_Const_circulator_over_array<A, T, U, I>& c)
        : CGAL_Random_access_circulator_ptrbase<T,I>( c),
          _size( c._size), _i(c._i) {}

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _i >= _size;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Const_circulator_over_array< A, T, U, I>& c
    ) const {
        CGAL_assertion( _ptr  == c._ptr);  // do they belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i == c._i;
    }
    bool operator!=(
        const CGAL_Const_circulator_over_array< A, T, U, I>& c
    ) const {
        return !(*this == c);
    }
    const T&  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        return ((const A*)_ptr)->operator[](_i);
    }
    CGAL_Const_circulator_over_array< A, T, U, I>&
    operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        ++ _i;
        if ( _i >= _size)
            _i = 0;
        return *this;
    }
    CGAL_Const_circulator_over_array< A, T, U, I>
    operator++(int) {
        CGAL_Const_circulator_over_array< A, T, U, I> tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Const_circulator_over_array< A, T, U, I>&
    operator--() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        if ( _i <= 0)
            _i = _size - 1;
        else
            -- _i;
        return *this;
    }
    CGAL_Const_circulator_over_array< A, T, U, I>
    operator--(int) {
        CGAL_Const_circulator_over_array< A, T, U, I> tmp = *this;
        --*this;
        return tmp;
    }
    CGAL_Const_circulator_over_array< A, T, U, I>&
    operator+=( I n);

    CGAL_Const_circulator_over_array< A, T, U, I>
    operator+( I n) const {
        CGAL_Const_circulator_over_array< A, T, U, I> tmp = *this;
        return tmp += n;
    }
    CGAL_Const_circulator_over_array< A, T, U, I>&
    operator-=( I n) {
        return operator+=( -n);
    }
    CGAL_Const_circulator_over_array< A, T, U, I>
    operator-( I n) const {
        CGAL_Const_circulator_over_array< A, T, U, I> tmp = *this;
        return tmp += -n;
    }
    I
    operator-( const CGAL_Const_circulator_over_array<A,T,U,I>& c)  const {
        CGAL_assertion( _ptr  == c._ptr);  // do they belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i - c._i;
    }
    const T&  operator[](I n) const {
        CGAL_Const_circulator_over_array< A, T, U, I> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    // no relational ordering

    // Hack! Probably not working with the official standard, but
    // the official way is not working yet, see below.
    friend inline
    CGAL_Const_circulator_over_array< A, T, U, I>
    operator+( I n, const CGAL_Const_circulator_over_array<A,T,U,I>& circ) {
        CGAL_Const_circulator_over_array< A, T, U, I> tmp = circ;
        return tmp += n;
    }
    CGAL_Const_circulator_over_array<A, T, U, I>
    min_circulator() {
        return CGAL_Const_circulator_over_array<A, T, U, I>(
            *((const A*)_ptr), _size);
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  I* distance_type(
        const
    CGAL_Const_circulator_over_array< A, T, U, I>&) {
        return ( I*)(0);
    }
    friend inline  T* value_type(
        const
    CGAL_Const_circulator_over_array< A, T, U, I>&) {
        return ( T*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(
    CGAL_Const_circulator_over_array< A, T, U, I>) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Const_circulator_over_array< A, T, U, I>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 5832 "circulator.any"
          
};

// This is how the friend declaration from above should
// be implemented, however it is not working yet.
/* ...
template < class  A, class  T, class U, class  I>
inline
CGAL_Const_circulator_over_array< A, T, U, I>
operator+( I n, const CGAL_Const_circulator_over_array<A,T,U,I>& circ)
const {
    CGAL_Const_circulator_over_array< A, T, U, I> tmp = circ;
    return tmp += n;
}
... */

template < class A, class T, class U, class I>
CGAL_Const_circulator_over_array< A, T, U, I>&
CGAL_Const_circulator_over_array< A, T, U, I>::
operator+=( I n) {
    CGAL_assertion( _ptr != NULL);
    CGAL_assertion( _i < _size);
    _i = CGAL_non_negative_mod( (I)(_i) + n, _size);
    CGAL_assertion( _i < _size);
    return *this;
}
// #line 115 "circulator.any"
 

// Sun Pro C++ does not understand member pointers in template
// arguments. SGI C++ and Gnu g++ do understand them.
#ifndef CGAL__CIRC_SUNPRO_41
// #line 4339 "circulator.any"
template < class  S, S* S::* next >
class CGAL_Forward_circulator_over_struct_mptr
    : public CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>{
public:

// DEFINITION
//
// Given a structure `S' that have a data member of type `S*' that
// realizes a ring like data structure the adaptor
// `CGAL_Forward_circulator_over_struct< S, S* S::* next = &S::next>'
// provides a forward circulator for it. If the structure `S' has
// additionally a second data member of type `S*' that realizes the
// reverse direction the adaptor
// `CGAL_Bidirectional_circulator_over_struct< S, S* S::* next = &S::next,
// S* S::* prev = &S::prev>' provides a bidirectional circulator for it.
// In addition, adaptors for const circulators are provided with the names
// `CGAL_Forward_const_circulator_over_struct< S, S* S::* next = &S::next>'
// and `CGAL_Bidirectional_const_circulator_over_struct< S, S* S::* next =
// &S::next, S* S::* prev = &S::prev>'. A circulator becomes invalid
// whenever the object it refers to gets deleted from the data structure.
//
// As long as default template parameters are not supported the adaptors
// will not provide the member pointer template parameters. The adaptors
// will use the default values. All adaptors have a counterpart with the
// suffix `_mptr' supporting all template parameters, but no default
// settings. As soon as member pointers are supported by our reference
// compilers\footnote{The SGI CC and the Gnu g++ do support member
// pointers in template arguments, the Sun CC does not. The older C++
// standard drafts rule out this application of template arguments, the
// new drafts include it.}, these counterparts can be used.
//
// PARAMETERS
//
// `S' is a structure or class. The public data members of type `S*' which
// form the linked structure are given as member pointers `S* S::* next'
// and `S* S::* prev' . Both have default values `&S::next' and `&S::prev'
// respectively.
//
// Please note that the correct signature for the member pointer argument
// for a const circulator would be `const S* S::*next', but one cannot
// implement a ring structure in this way since member variables cannot be
// overloaded as compared to the member functions that are used in the
// next section for circulators for classes. Thus, the const circulator is
// an easy way to achieve a typesafe read only access to a pointered data
// structure.
//
// TYPES

    typedef S         value_type;
    typedef S&        reference;
    typedef const S&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// CREATION
//
// New creation variable is: `circ'

    CGAL_Forward_circulator_over_struct_mptr() {}
        // a circulator `circ' with singular value.

    CGAL_Forward_circulator_over_struct_mptr( S* ptr)
        : CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>( ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Forward_circulator_over_struct_mptr(
        const CGAL_Forward_circulator_over_struct_mptr<S,next>& c)
        : CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>( c) {}

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Forward_circulator_over_struct_mptr< S, next>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Forward_circulator_over_struct_mptr< S, next>& c
    ) const {
        return !(*this == c);
    }
    S&  operator*() const { return *(S*)_ptr;}

    CGAL_Forward_circulator_over_struct_mptr< S, next>&
    operator++() {
        _ptr = ((S*)_ptr)->*next;
        return *this;
    }
    CGAL_Forward_circulator_over_struct_mptr< S, next>
    operator++(int) {
        CGAL_Forward_circulator_over_struct_mptr< S, next> tmp = *this;
        ++*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Forward_circulator_over_struct_mptr<S, next>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline  S* value_type(
        const
    CGAL_Forward_circulator_over_struct_mptr<S, next>&) {
        return ( S*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_circulator_over_struct_mptr<S, next>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_circulator_over_struct_mptr<S, next>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 4441 "circulator.any"
          
};

template < class  S, S* S::* next >
class CGAL_Forward_const_circulator_over_struct_mptr
    : public CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>{
public:

// TYPES

    typedef S         value_type;
    typedef S&        reference;
    typedef const S&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// CREATION

    CGAL_Forward_const_circulator_over_struct_mptr() {}
        // a circulator `circ' with singular value.

    CGAL_Forward_const_circulator_over_struct_mptr( const S* ptr)
        : CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>( (void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Forward_const_circulator_over_struct_mptr(
        const CGAL_Forward_const_circulator_over_struct_mptr<S,next>& c)
        : CGAL_Forward_circulator_ptrbase<S,ptrdiff_t>( c) {}

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Forward_const_circulator_over_struct_mptr< S, next>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Forward_const_circulator_over_struct_mptr< S, next>& c
    ) const {
        return !(*this == c);
    }
    const S&  operator*() const { return *(S*)_ptr;}

    CGAL_Forward_const_circulator_over_struct_mptr< S, next>&
    operator++() {
        _ptr = ((S*)_ptr)->*next;
        return *this;
    }
    CGAL_Forward_const_circulator_over_struct_mptr< S, next>
    operator++(int) {
        CGAL_Forward_const_circulator_over_struct_mptr< S, next>
            tmp = *this;
        ++*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Forward_const_circulator_over_struct_mptr<S, next>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline 
                        S* value_type(
        const
    CGAL_Forward_const_circulator_over_struct_mptr<S, next>&) {
        return (
                      S*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_const_circulator_over_struct_mptr<S, next>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_const_circulator_over_struct_mptr<S, next>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 4505 "circulator.any"
          
};

template < class  S, S* S::* next, S* S::* prev >
class CGAL_Bidirectional_circulator_over_struct_mptr
    : public CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>{
public:

// TYPES

    typedef S         value_type;
    typedef S&        reference;
    typedef const S&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// CREATION
//
// New creation variable is: `circ'

    CGAL_Bidirectional_circulator_over_struct_mptr() {}
        // a circulator `circ' with singular value.

    CGAL_Bidirectional_circulator_over_struct_mptr( S* ptr)
        : CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>( ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Bidirectional_circulator_over_struct_mptr(
        const CGAL_Bidirectional_circulator_over_struct_mptr<
            S,next,prev>& c)
        : CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>( c) {}

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Bidirectional_circulator_over_struct_mptr<
            S, next, prev>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Bidirectional_circulator_over_struct_mptr<
            S, next, prev>& c
    ) const {
        return !(*this == c);
    }
    S&  operator*() const { return *(S*)_ptr;}

    CGAL_Bidirectional_circulator_over_struct_mptr< S, next, prev>&
    operator++() {
        _ptr = ((S*)_ptr)->*next;
        return *this;
    }
    CGAL_Bidirectional_circulator_over_struct_mptr< S, next, prev>
    operator++(int) {
        CGAL_Bidirectional_circulator_over_struct_mptr< S, next, prev>
            tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_circulator_over_struct_mptr< S, next, prev>&
    operator--() {
        _ptr = ((S*)_ptr)->*prev;
        return *this;
    }
    CGAL_Bidirectional_circulator_over_struct_mptr< S, next, prev>
    operator--(int) {
        CGAL_Bidirectional_circulator_over_struct_mptr< S, next, prev>
            tmp = *this;
        --*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Bidirectional_circulator_over_struct_mptr<S, next, prev>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline 
                        S* value_type(
        const
    CGAL_Bidirectional_circulator_over_struct_mptr<S, next, prev>&) {
        return (
                      S*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_circulator_over_struct_mptr<S, next, prev>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_circulator_over_struct_mptr<S, next, prev>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 4586 "circulator.any"
          
};


template < class  S, S* S::* next, S* S::* prev >
class CGAL_Bidirectional_const_circulator_over_struct_mptr
    : public CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>{
public:

// TYPES

    typedef S         value_type;
    typedef S&        reference;
    typedef const S&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// CREATION

    CGAL_Bidirectional_const_circulator_over_struct_mptr() {}
        // a circulator `circ' with singular value.

    CGAL_Bidirectional_const_circulator_over_struct_mptr( const S* ptr)
        : CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>( (void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Bidirectional_const_circulator_over_struct_mptr(
        const CGAL_Bidirectional_const_circulator_over_struct_mptr<
            S,next,prev>& c)
        : CGAL_Bidirectional_circulator_ptrbase<S,ptrdiff_t>( c) {}

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Bidirectional_const_circulator_over_struct_mptr<
            S, next, prev>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Bidirectional_const_circulator_over_struct_mptr<
            S, next, prev>& c
    ) const {
        return !(*this == c);
    }
    const S&  operator*() const { return *(S*)_ptr;}

    CGAL_Bidirectional_const_circulator_over_struct_mptr< S, next, prev>&
    operator++() {
        _ptr = ((S*)_ptr)->*next;
        return *this;
    }
    CGAL_Bidirectional_const_circulator_over_struct_mptr< S, next, prev>
    operator++(int) {
        CGAL_Bidirectional_const_circulator_over_struct_mptr< S, next, prev>
            tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_const_circulator_over_struct_mptr< S, next, prev>&
    operator--() {
        _ptr = ((S*)_ptr)->*prev;
        return *this;
    }
    CGAL_Bidirectional_const_circulator_over_struct_mptr< S, next, prev>
    operator--(int) {
        CGAL_Bidirectional_const_circulator_over_struct_mptr<
            S, next, prev> tmp = *this;
        --*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Bidirectional_const_circulator_over_struct_mptr<S, next, prev>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline 
                         S* value_type(
        const
    CGAL_Bidirectional_const_circulator_over_struct_mptr<S, next, prev>&) {
        return (
                       S*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_const_circulator_over_struct_mptr<S, next, prev>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_const_circulator_over_struct_mptr<S, next, prev>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 4666 "circulator.any"
          
};
// #line 120 "circulator.any"
  
// #line 5110 "circulator.any"
template < class  C, C* (C::* next)() >
class CGAL_Forward_circulator_over_class_mptr
    : public CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>{
public:

// DEFINITION
//
// Given a class `C' that have member functions with return values of type
// `C*' that realizes a ring like data structure the adaptor
// `CGAL_Forward_circulator_over_class< C, C* (C::*next)() = &C::next>'
// provides a forward circulator for it. If the class `C' has additionally
// a second member function that realizes the reverse direction the
// adaptor `CGAL_Bidirectional_circulator_over_class< C, C* (C::*next)() =
// &C::next, C* (C::*prev)() = &C::prev>' provides a bidirectional
// circulator for it. In addition, adaptors for const circulators are
// provided with the names `CGAL_Forward_const_circulator_over_class< C,
// const C* (C::*next)() const = &C::next>' and
// `CGAL_Bidirectional_const_circulator_over_class< C, const C* (C::*next)(
// ) const = &C::next, const C* (C::*prev)() const = &C::prev>'. A
// circulator becomes invalid whenever the object it refers to gets
// deleted from the data structure.
//
// As long as default template parameters are not supported the adaptors
// will not provide the member pointer template parameters. The adaptors
// will use the default values. All adaptors have a counterpart with the
// suffix `_mptr' supporting all template parameters, but no default
// settings. As soon as member pointers are supported by our reference
// compilers\footnote{The SGI CC and the Gnu g++ do support member
// pointers in template arguments, the Sun CC does not. The older C++
// standard drafts rule out this application of template arguments, the
// new drafts include it.}, these counterparts can be used.
//
// PARAMETERS
//
// `C' is a structure or class. The public member functions with return
// type `C*' which form the linked structure are given as member pointers
// `C* (C::*next)()' and `C* (C::*prev)()' . For the const circulators the
// member pointers are of the form `const C* (C::*next)() const' and
// `const C* (C::*prev)() const' . Both have default values `&C::next' and
// `&C::prev' respectively.
//
// TYPES

    typedef C         value_type;
    typedef C&        reference;
    typedef const C&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// New creation variable is: `circ'
//
// CREATION

    CGAL_Forward_circulator_over_class_mptr() {}
        // a circulator `circ' with a singular value.

    CGAL_Forward_circulator_over_class_mptr( C* ptr)
        : CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>( ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Forward_circulator_over_class_mptr(
        const CGAL_Forward_circulator_over_class_mptr< C, next>& c)
        : CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>( c) {}

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Forward_circulator_over_class_mptr< C, next>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Forward_circulator_over_class_mptr< C, next>& c
    ) const {
        return !(*this == c);
    }
    C&  operator*() const { return *(C*)_ptr;}

    CGAL_Forward_circulator_over_class_mptr< C, next>&
    operator++() {
        _ptr = (((C*)_ptr)->*next)();
        return *this;
    }
    CGAL_Forward_circulator_over_class_mptr< C, next>
    operator++(int) {
        CGAL_Forward_circulator_over_class_mptr< C, next> tmp = *this;
        ++*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Forward_circulator_over_class_mptr<C, next>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline  C* value_type(
        const
    CGAL_Forward_circulator_over_class_mptr<C, next>&) {
        return ( C*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_circulator_over_class_mptr<C, next>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_circulator_over_class_mptr<C, next>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 5208 "circulator.any"
          
};

template < class  C, CGAL_MEMBER_PTR_CONST C* (C::* next)()
                     CGAL_MEMBER_PTR_CONST >
class CGAL_Forward_const_circulator_over_class_mptr
    : public CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>{
public:
//
// CREATION

    CGAL_Forward_const_circulator_over_class_mptr() {}
        // a circulator `circ' with singular value.

    CGAL_Forward_const_circulator_over_class_mptr( const C* ptr)
        : CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>( (void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Forward_const_circulator_over_class_mptr(
        const CGAL_Forward_const_circulator_over_class_mptr< C, next>& c)
        : CGAL_Forward_circulator_ptrbase<C,ptrdiff_t>( c) {}

// TYPES

    typedef C         value_type;
    typedef C&        reference;
    typedef const C&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

//
// OPERATIONS


    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Forward_const_circulator_over_class_mptr< C, next>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Forward_const_circulator_over_class_mptr< C, next>& c
    ) const {
        return !(*this == c);
    }
    const C&  operator*() const { return *(C*)_ptr;}

    CGAL_Forward_const_circulator_over_class_mptr< C, next>&
    operator++() {
        _ptr = (void*)((((C*)_ptr)->*next)());
        return *this;
    }
    CGAL_Forward_const_circulator_over_class_mptr< C, next>
    operator++(int) {
        CGAL_Forward_const_circulator_over_class_mptr< C, next> tmp = *this;
        ++*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Forward_const_circulator_over_class_mptr<C, next>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline 
                        C* value_type(
        const
    CGAL_Forward_const_circulator_over_class_mptr<C, next>&) {
        return (
                      C*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_const_circulator_over_class_mptr<C, next>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_const_circulator_over_class_mptr<C, next>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 5274 "circulator.any"
          
};

template < class  C, C* (C::* next)(), C* (C::* prev)() >
class CGAL_Bidirectional_circulator_over_class_mptr
    : public CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>{
public:
//
// TYPES

    typedef C         value_type;
    typedef C&        reference;
    typedef const C&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

// New creation variable is: `circ'
//
// CREATION

    CGAL_Bidirectional_circulator_over_class_mptr() {}
        // a circulator `circ' with singular value.

    CGAL_Bidirectional_circulator_over_class_mptr( C* ptr)
        : CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>( ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Bidirectional_circulator_over_class_mptr(
        const CGAL_Bidirectional_circulator_over_class_mptr<C,next,prev>& c)
        : CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>( c) {}

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Bidirectional_circulator_over_class_mptr<C,next,prev>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Bidirectional_circulator_over_class_mptr<C,next,prev>& c
    ) const {
        return !(*this == c);
    }
    C&  operator*() const { return *(C*)_ptr;}

    CGAL_Bidirectional_circulator_over_class_mptr< C, next, prev>&
    operator++() {
        _ptr = (((C*)_ptr)->*next)();
        return *this;
    }
    CGAL_Bidirectional_circulator_over_class_mptr< C, next, prev>
    operator++(int) {
        CGAL_Bidirectional_circulator_over_class_mptr< C, next, prev>
            tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_circulator_over_class_mptr< C, next, prev>&
    operator--() {
        _ptr = (((C*)_ptr)->*prev)();
        return *this;
    }
    CGAL_Bidirectional_circulator_over_class_mptr< C, next, prev>
    operator--(int) {
        CGAL_Bidirectional_circulator_over_class_mptr< C, next, prev>
            tmp = *this;
        --*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Bidirectional_circulator_over_class_mptr<C, next, prev>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline 
                        C* value_type(
        const
    CGAL_Bidirectional_circulator_over_class_mptr<C, next, prev>&) {
        return (
                      C*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_circulator_over_class_mptr<C, next, prev>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_circulator_over_class_mptr<C, next, prev>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 5353 "circulator.any"
          
};

template < class  C, CGAL_MEMBER_PTR_CONST C* (C::* next)()
                                                 CGAL_MEMBER_PTR_CONST,
                     CGAL_MEMBER_PTR_CONST C* (C::* prev)()
                                                 CGAL_MEMBER_PTR_CONST >
class CGAL_Bidirectional_const_circulator_over_class_mptr
    : public CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>{
public:
//
// TYPES

    typedef C         value_type;
    typedef C&        reference;
    typedef const C&  const_reference;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

//
// CREATION

    CGAL_Bidirectional_const_circulator_over_class_mptr() {}
        // a circulator `circ' with singular value.

    CGAL_Bidirectional_const_circulator_over_class_mptr( const C* ptr)
        : CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>( (void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

    CGAL_Bidirectional_const_circulator_over_class_mptr(
        const CGAL_Bidirectional_const_circulator_over_class_mptr<
            C, next, prev>& c)
        : CGAL_Bidirectional_circulator_ptrbase<C,ptrdiff_t>( c) {}

//
// OPERATIONS


    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Bidirectional_const_circulator_over_class_mptr<
            C, next, prev>& c
    ) const {
        return _ptr == c._ptr;
    }
    bool operator!=(
        const CGAL_Bidirectional_const_circulator_over_class_mptr<
            C, next, prev>& c
    ) const {
        return !(*this == c);
    }
    const C&  operator*() const { return *(C*)_ptr;}

    CGAL_Bidirectional_const_circulator_over_class_mptr< C, next, prev>&
    operator++() {
        _ptr = (void*)((((C*)_ptr)->*next)());
        return *this;
    }
    CGAL_Bidirectional_const_circulator_over_class_mptr< C, next, prev>
    operator++(int) {
        CGAL_Bidirectional_const_circulator_over_class_mptr< C, next, prev>
            tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_const_circulator_over_class_mptr< C, next, prev>&
    operator--() {
        _ptr = (void*)((((C*)_ptr)->*prev)());
        return *this;
    }
    CGAL_Bidirectional_const_circulator_over_class_mptr< C, next, prev>
    operator--(int) {
        CGAL_Bidirectional_const_circulator_over_class_mptr< C, next, prev>
            tmp = *this;
        --*this;
        return tmp;
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  ptrdiff_t* distance_type(
        const
    CGAL_Bidirectional_const_circulator_over_class_mptr<C, next, prev>&) {
        return ( ptrdiff_t*)(0);
    }
    friend inline 
                        C* value_type(
        const
    CGAL_Bidirectional_const_circulator_over_class_mptr<C, next, prev>&) {
        return (
                      C*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_const_circulator_over_class_mptr<C, next, prev>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_const_circulator_over_class_mptr<C, next, prev>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 5438 "circulator.any"
          
};
// #line 121 "circulator.any"
  
// #line 5900 "circulator.any"
template < class A, class T, class U, class I, T& (A::*  access)(U i) >
class CGAL_Circulator_over_array_mptr
    : public CGAL_Random_access_circulator_ptrbase<T,I>{
    U _size;
    U _i;
public:

// DEFINITION
//
// Given a data structure `A' that provides random access with an index of
// type `U' to its sequence of stored elements of type `T' with a member
// function `access' the adaptor \ccClassTemplateName provides a random
// access circulator for `A'. The corresponding const circulator is
// `CGAL_Const_circulator_over_array< A, T, U, I, const T& (A::* access)(U
// i) const>'. All circulators for an array `a' become invalid whenever
// `a' changes its size (due to deletions or insertions).
//
// PARAMETERS
//
// `A' is a random access data structure and `T' its value type. `U' is
// the unsigned integral type carrying the size of the array and the
// actual index within the container. `I' is the signed integral type used
// as distance type and as index type in the random access circulator. The
// member function `access' is given as a member pointer `T& (A::* access)
// (U i)' or `const T& (A::* access)(U i) const' for the const circulator.
//
// TYPES

    typedef A         Array;
    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef U         size_type;
    typedef I         difference_type;

// New creation variable is: `circ'
//
// CREATION

    CGAL_Circulator_over_array_mptr() : _size(0), _i(0) {}
        // a circulator `circ' with singular value.

    CGAL_Circulator_over_array_mptr( A& array, U size, U start = 0)
        : CGAL_Random_access_circulator_ptrbase<T,I>( &array),
          _size( size), _i(start) {}
        // a circulator `circ' initialized to refer to the element
        // `(array.*access)(start)'. The circulator `circ' contains a
        // singular value if `start >= size'. Precondition: The
        // expressions `(array.*access)(i)' are valid in the range
        // 0 <= i < `size' .

    CGAL_Circulator_over_array_mptr(
        const CGAL_Circulator_over_array_mptr<A, T, U, I, access>& c)
        : CGAL_Random_access_circulator_ptrbase<T,I>( c),
          _size( c._size), _i(c._i) {}

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _i >= _size;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Circulator_over_array_mptr< A, T, U, I, access>& c
    ) const {
        CGAL_assertion( _ptr  == c._ptr);  // do they belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i == c._i;
    }
    bool operator!=(
        const CGAL_Circulator_over_array_mptr< A, T, U, I, access>& c
    ) const {
        return !(*this == c);
    }
    T&  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        return ( ((A*)_ptr)->*access)(_i);
    }
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>&
    operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        ++ _i;
        if ( _i >= _size)
            _i = 0;
        return *this;
    }
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>
    operator++(int) {
        CGAL_Circulator_over_array_mptr< A, T, U, I, access> tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>&
    operator--() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        if ( _i <= 0)
            _i = _size - 1;
        else
            -- _i;
        return *this;
    }
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>
    operator--(int) {
        CGAL_Circulator_over_array_mptr< A, T, U, I, access> tmp = *this;
        --*this;
        return tmp;
    }
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>&
    operator+=( I n) {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        _i = CGAL_non_negative_mod( (I)(_i) + n, _size);
        CGAL_assertion( _i < _size);
        return *this;
    }

    CGAL_Circulator_over_array_mptr< A, T, U, I, access>
    operator+( I n) const {
        CGAL_Circulator_over_array_mptr< A, T, U, I, access> tmp = *this;
        return tmp += n;
    }
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>&
    operator-=( I n) {
        return operator+=( -n);
    }
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>
    operator-( I n) const {
        CGAL_Circulator_over_array_mptr< A, T, U, I, access> tmp = *this;
        return tmp += -n;
    }
    I
    operator-( const CGAL_Circulator_over_array_mptr< A,T,U,I,access>& c)
               const {
        CGAL_assertion( _ptr  == c._ptr);  // do they belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i - c._i;
    }
    T&  operator[](I n) const {
        CGAL_Circulator_over_array_mptr< A, T, U, I, access> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    // no relational ordering

    // Hack! Probably not working with the official standard, but
    // the official way is not working yet, see below.
    friend inline
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>
    operator+( I n, const
               CGAL_Circulator_over_array_mptr< A,T,U,I,access>& circ) {
        CGAL_Circulator_over_array_mptr< A, T, U, I, access> tmp = circ;
        return tmp += n;
    }
    CGAL_Circulator_over_array_mptr<A, T, U, I, access>
    min_circulator() {
        return CGAL_Circulator_over_array_mptr<A, T, U, I, access>(
            *((A*)_ptr), _size);
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  I* distance_type(
        const
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>&) {
        return ( I*)(0);
    }
    friend inline  T* value_type(
        const
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>&) {
        return ( T*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Circulator_over_array_mptr< A, T, U, I, access>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 6065 "circulator.any"
          
};

// This is how the friend declaration from above should
// be implemented, however it is not working yet.
/* ...
template < class  A, class  T, class U, class  I, T& (A::* access)(U i) >
inline
CGAL_Circulator_over_array_mptr< A, T, U, I, access>
operator+( I n, const
           CGAL_Circulator_over_array_mptr< A, T, U, I, access>& circ) {
    CGAL_Circulator_over_array_mptr< A, T, U, I, access> tmp = circ;
    return tmp += n;
}
... */

/* ... the SGI compiler don't like it here, so it's now inline.
template < class  A, class  T, class U, class  I, T& (A::* access)(U i) >
CGAL_Circulator_over_array_mptr< A, T, U, I, access>&
CGAL_Circulator_over_array_mptr< A, T, U, I, access>::
operator+=( I n) {
    CGAL_assertion( _ptr != NULL);
    CGAL_assertion( _i < _size);
    _i = CGAL_non_negative_mod( (I)(_i) + n, _size);
    CGAL_assertion( _i < _size);
    return *this;
}
... */


template < class  A, class  T, class U, class  I,
           CGAL_MEMBER_PTR_CONST T& (A::* access)(U i)
                                                CGAL_MEMBER_PTR_CONST>
class CGAL_Const_circulator_over_array_mptr
    : public CGAL_Random_access_circulator_ptrbase<T,I> {
    U _size;
    U _i;
public:

// TYPES

    typedef A         Array;
    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef U         size_type;
    typedef I         difference_type;

// New creation variable is: `circ'
//
// CREATION

    CGAL_Const_circulator_over_array_mptr() : _size(0), _i(0) {}
        // a const circulator `circ' with singular value.

    CGAL_Const_circulator_over_array_mptr( const A& array,
                                          U size,
                                          U start = 0)
        : CGAL_Random_access_circulator_ptrbase<T,I>(
              (void*)(&array)), _size( size), _i(start) {}
        // a const circulator `circ' initialized to refer to the element
        // `(array.*access)(start)'. The circulator `circ' contains a
        // singular value if `start >= size'. Precondition: The
        // expressions `(array.*access)(i)' are valid in the range
        // 0 <= i < `size' .

    CGAL_Const_circulator_over_array_mptr(
        const CGAL_Const_circulator_over_array_mptr<A, T, U, I, access>& c)
        : CGAL_Random_access_circulator_ptrbase<T,I>( c),
          _size( c._size), _i(c._i) {}

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return _i >= _size;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>& c
    ) const {
        CGAL_assertion( _ptr  == c._ptr);  // do they belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i == c._i;
    }
    bool operator!=(
        const CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>& c
    ) const {
        return !(*this == c);
    }
    const T&  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        return ( ((const A*)_ptr)->*access)(_i);
    }
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>&
    operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        ++ _i;
        if ( _i >= _size)
            _i = 0;
        return *this;
    }
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>
    operator++(int) {
        CGAL_Const_circulator_over_array_mptr< A,T,U,I,access> tmp = *this;
        ++*this;
        return tmp;
    }
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>&
    operator--() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        if ( _i <= 0)
            _i = _size - 1;
        else
            -- _i;
        return *this;
    }
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>
    operator--(int) {
        CGAL_Const_circulator_over_array_mptr< A,T,U,I,access> tmp = *this;
        --*this;
        return tmp;
    }
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>&
    operator+=( I n) {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        _i = CGAL_non_negative_mod( (I)(_i) + n, _size);
        CGAL_assertion( _i < _size);
        return *this;
    }

    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>
    operator+( I n) const {
        CGAL_Const_circulator_over_array_mptr< A,T,U,I,access> tmp = *this;
        return tmp += n;
    }
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>&
    operator-=( I n) {
        return operator+=( -n);
    }
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>
    operator-( I n) const {
        CGAL_Const_circulator_over_array_mptr< A,T,U,I,access> tmp = *this;
        return tmp += -n;
    }
    I
    operator-( const CGAL_Const_circulator_over_array_mptr< A, T, U, I,
               access>& c)  const {
        CGAL_assertion( _ptr  == c._ptr);  // do they belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i - c._i;
    }
    const T&  operator[](I n) const {
        CGAL_Const_circulator_over_array_mptr< A,T,U,I,access> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    // no relational ordering

    // Hack! Probably not working with the official standard, but
    // the official way is not working yet, see below.
    friend inline
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>
    operator+( I n, const CGAL_Const_circulator_over_array_mptr< A, T, U, I,
                    access>& circ) {
        CGAL_Const_circulator_over_array_mptr< A,T,U,I,access> tmp = circ;
        return tmp += n;
    }
    CGAL_Const_circulator_over_array_mptr<A, T, U, I, access>
    min_circulator() {
        return CGAL_Const_circulator_over_array_mptr<A, T, U, I, access>(
            *((const A*)_ptr), _size);
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline  I* distance_type(
        const
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>&) {
        return ( I*)(0);
    }
    friend inline  T* value_type(
        const
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>&) {
        return ( T*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 6246 "circulator.any"
          
};

// This is how the friend declaration from above should
// be implemented, however it is not working yet.
/* ...
template < class  A, class  T, class U, class  I,
           CGAL_MEMBER_PTR_CONST T& (A::* access)(U i) CGAL_MEMBER_PTR_CONST>
inline
CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>
operator+( I n, const CGAL_Const_circulator_over_array_mptr< A, T, U, I,
                access>& circ) const {
    CGAL_Const_circulator_over_array_mptr< A, T, U, I, access> tmp = circ;
    return tmp += n;
}
... */

/* ... the SGI compiler don't like it here, so it's now inline.
template < class A, class T, class U, class I,
           CGAL_MEMBER_PTR_CONST T& (A::* access)(U i) CGAL_MEMBER_PTR_CONST>
CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>&
CGAL_Const_circulator_over_array_mptr< A, T, U, I, access>::
operator+=( I n) {
    CGAL_assertion( _ptr != NULL);
    CGAL_assertion( _i < _size);
    _i = CGAL_non_negative_mod( (I)(_i) + n, _size);
    CGAL_assertion( _i < _size);
    return *this;
}
... */
// #line 122 "circulator.any"
      
#endif //  CGAL__CIRC_SUNPRO_41 //

#endif // CGAL_CIRCULATOR_IMPL_H //
// EOF //
