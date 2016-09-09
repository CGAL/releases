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


//  14.10.1996   Lutz Kettner

                                                                             

#ifndef CGAL_CIRCULATOR_H
#define CGAL_CIRCULATOR_H 1

#ifndef _STDDEF_H
#include <stddef.h>
#endif

#ifndef CGAL_UTILS_H
#include <CGAL/utils.h>
#endif

 
#ifdef __GNUG__
#define CGAL_NULL_TYPE const void*
#else // __GNUG__ //
#define CGAL_NULL_TYPE int
#endif // __GNUG__ //
 
#ifdef __GNUG__
#define CGAL_MEMBER_PTR_CONST
#else
#define CGAL_MEMBER_PTR_CONST const
#endif
 


 
struct CGAL_Circulator_tag {};                   // any circulator.
struct CGAL_Iterator_tag {};                     // any iterator.
 
                                                                
 
template <class T, class Dist>   struct CGAL_Forward_circulator_base {};
template <class T, class Dist>   struct CGAL_Bidirectional_circulator_base {};
template <class T, class Dist>   struct CGAL_Random_access_circulator_base {};

// variant base classes
// ---------------------
template <class T, class Dist>
class CGAL_Forward_circulator_ptrbase {         // forward circulator.
    protected:
        void* _ptr;
    public:
        CGAL_Forward_circulator_ptrbase()        : _ptr(NULL) {}
        CGAL_Forward_circulator_ptrbase(void* p) : _ptr(p) {}
        CGAL_Forward_circulator_ptrbase(
            const CGAL_Forward_circulator_ptrbase<T,Dist>& b) : _ptr(b._ptr) {}
};
template <class T, class Dist>
class CGAL_Bidirectional_circulator_ptrbase {   // bidirectional circulator.
    protected:
        void* _ptr;
    public:
        CGAL_Bidirectional_circulator_ptrbase()        : _ptr(NULL) {}
        CGAL_Bidirectional_circulator_ptrbase(void* p) : _ptr(p) {}
        CGAL_Bidirectional_circulator_ptrbase(
            const CGAL_Bidirectional_circulator_ptrbase<T,Dist>& b)
                                                      : _ptr(b._ptr) {}
};
template <class T, class Dist>
class CGAL_Random_access_circulator_ptrbase {   // random access circulator.
    protected:
        void* _ptr;
    public:
        CGAL_Random_access_circulator_ptrbase()        : _ptr(NULL) {}
        CGAL_Random_access_circulator_ptrbase(void* p) : _ptr(p) {}
        CGAL_Random_access_circulator_ptrbase(
            const CGAL_Random_access_circulator_ptrbase<T,Dist>& b)
                                                      : _ptr(b._ptr) {}
};
 
  
#ifdef __KCC
#include <iterator.h>
#else
// Forward declarations for STL iterators and tags.
// Include <iterator.h> when really using them.
// ------------------------------------------------
struct forward_iterator_tag;
struct bidirectional_iterator_tag;
struct random_access_iterator_tag;

template <class T, class Distance> struct input_iterator;
struct output_iterator;
template <class T, class Distance> struct forward_iterator;
template <class T, class Distance> struct bidirectional_iterator;
template <class T, class Distance> struct random_access_iterator;
#endif // __KCC

// Circulators
// -----------
template< class T, class D> inline
forward_iterator_tag
iterator_category( const CGAL_Forward_circulator_base<T,D>&){
    return forward_iterator_tag();
}
template< class T, class D> inline
bidirectional_iterator_tag
iterator_category( const CGAL_Bidirectional_circulator_base<T,D>&){
    return bidirectional_iterator_tag();
}
template< class T, class D> inline
random_access_iterator_tag
iterator_category( const CGAL_Random_access_circulator_base<T,D>&){
    return random_access_iterator_tag();
}

// variant base classes
// --------------------
template< class T, class D> inline
forward_iterator_tag
iterator_category(  const CGAL_Forward_circulator_ptrbase<T,D>&){
    return forward_iterator_tag();
}
template< class T, class D> inline
bidirectional_iterator_tag
iterator_category(  const CGAL_Bidirectional_circulator_ptrbase<T,D>&){
    return bidirectional_iterator_tag();
}
template< class T, class D> inline
random_access_iterator_tag
iterator_category(  const CGAL_Random_access_circulator_ptrbase<T,D>&){
    return random_access_iterator_tag();
}
 
 
 
// Iterators
// ---------
template< class T, class D> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const input_iterator<T,D>&){
    return CGAL_Iterator_tag();
}
inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(  const output_iterator&){
    return CGAL_Iterator_tag();
}
template< class T, class D>   inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(  const forward_iterator<T,D>&){
    return CGAL_Iterator_tag();
}
template< class T, class D>   inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(  const bidirectional_iterator<T,D>&){
    return CGAL_Iterator_tag();
}
template< class T, class D>   inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(  const random_access_iterator<T,D>&){
    return CGAL_Iterator_tag();
}
template< class T>   inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const T*){
    return CGAL_Iterator_tag();
}

// Circulators
// -----------
template< class T, class D> inline
CGAL_Circulator_tag
CGAL_query_circulator_or_iterator(
        const CGAL_Random_access_circulator_base<T,D>&){
    return CGAL_Circulator_tag();
}
template< class T, class D> inline
CGAL_Circulator_tag
CGAL_query_circulator_or_iterator(
        const CGAL_Forward_circulator_base<T,D>&){
    return CGAL_Circulator_tag();
}
template< class T, class D> inline
CGAL_Circulator_tag
CGAL_query_circulator_or_iterator(
        const CGAL_Bidirectional_circulator_base<T,D>&){
    return CGAL_Circulator_tag();
}

// variant base classes
// --------------------
template< class T, class D> inline
CGAL_Circulator_tag
CGAL_query_circulator_or_iterator(
        const CGAL_Random_access_circulator_ptrbase<T,D>&){
    return CGAL_Circulator_tag();
}
template< class T, class D> inline
CGAL_Circulator_tag
CGAL_query_circulator_or_iterator(
        const CGAL_Forward_circulator_ptrbase<T,D>&){
    return CGAL_Circulator_tag();
}
template< class T, class D> inline
CGAL_Circulator_tag
CGAL_query_circulator_or_iterator(
       const CGAL_Bidirectional_circulator_ptrbase<T,D>&){
    return CGAL_Circulator_tag();
}
 
 
 
template <class T, class Dist> inline
T* value_type( const CGAL_Forward_circulator_base<T,Dist>&) {
    return (T*)(0);
}
template <class T, class Dist> inline
T* value_type( const CGAL_Bidirectional_circulator_base<T,Dist>&) {
    return (T*)(0);
}
template <class T, class Dist> inline
T* value_type( const CGAL_Random_access_circulator_base<T,Dist>&) {
    return (T*)(0);
}
template <class T, class Dist> inline
T* value_type( const CGAL_Forward_circulator_ptrbase<T,Dist>&) {
    return (T*)(0);
}
template <class T, class Dist> inline
T* value_type( const CGAL_Bidirectional_circulator_ptrbase<T,Dist>&) {
    return (T*)(0);
}
template <class T, class Dist> inline
T* value_type( const CGAL_Random_access_circulator_ptrbase<T,Dist>&) {
    return (T*)(0);
}
template <class T, class Dist> inline
Dist* distance_type( const CGAL_Forward_circulator_base<T,Dist>&) {
    return (Dist*)(0);
}
template <class T, class Dist> inline
Dist* distance_type( const CGAL_Bidirectional_circulator_base<T,Dist>&) {
    return (Dist*)(0);
}
template <class T, class Dist> inline
Dist* distance_type( const CGAL_Random_access_circulator_base<T,Dist>&) {
    return (Dist*)(0);
}
template <class T, class Dist> inline
Dist* distance_type( const CGAL_Forward_circulator_ptrbase<T,Dist>&) {
    return (Dist*)(0);
}
template <class T, class Dist> inline
Dist* distance_type( const CGAL_Bidirectional_circulator_ptrbase<T,Dist>&) {
    return (Dist*)(0);
}
template <class T, class Dist> inline
Dist* distance_type( const CGAL_Random_access_circulator_ptrbase<T,Dist>&) {
    return (Dist*)(0);
}
 
 
 
/* A function that asserts a specific compile time tag */
/* forcing its two arguments to have equal type.       */
/* It is encapsulated with #ifdef since it will be defined also elsewhere. */
#ifndef CGAL_ASSERT_COMPILE_TIME_TAG
#define CGAL_ASSERT_COMPILE_TIME_TAG 1
template< class Tag>
inline void CGAL_kernel_assertion_compile_time_tag( Tag, Tag) {}
#endif

template <class C> inline
void CGAL_kernel_assertion_circulator( const C &c) {
    CGAL_kernel_assertion_compile_time_tag( CGAL_Circulator_tag(),
                                CGAL_query_circulator_or_iterator( c));
}
template <class I> inline
void CGAL_kernel_assertion_iterator( const I &i) {
    CGAL_kernel_assertion_compile_time_tag( CGAL_Iterator_tag(),
                                CGAL_query_circulator_or_iterator( i));
}
template <class I> inline
void CGAL_kernel_assertion_input_category( const I &i) {
    CGAL_kernel_assertion_compile_time_tag( input_iterator_tag(),
                                iterator_category( i));
}
template <class I> inline
void CGAL_kernel_assertion_output_category( const I &i) {
    CGAL_kernel_assertion_compile_time_tag( output_iterator_tag(),
                                iterator_category( i));
}
template <class IC> inline
void CGAL_kernel_assertion_forward_category( const IC &ic) {
    CGAL_kernel_assertion_compile_time_tag( forward_iterator_tag(),
                                iterator_category( ic));
}
template <class IC> inline
void CGAL_kernel_assertion_bidirectional_category( const IC &ic) {
    CGAL_kernel_assertion_compile_time_tag( bidirectional_iterator_tag(),
                                iterator_category( ic));
}
template <class IC> inline
void CGAL_kernel_assertion_random_access_category( const IC &ic) {
    CGAL_kernel_assertion_compile_time_tag( random_access_iterator_tag(),
                                iterator_category( ic));
}

// The assert at-least-category functions use the following
// functions to resolve properly. Note the proper order of the
// arguments: 1st is the to be type, 2nd is the actual type.
inline void CGAL__Has_to_be_at_least(input_iterator_tag,input_iterator_tag){}
inline void CGAL__Has_to_be_at_least(input_iterator_tag,forward_iterator_tag){}
inline void CGAL__Has_to_be_at_least(input_iterator_tag,
                                        bidirectional_iterator_tag){}
inline void CGAL__Has_to_be_at_least(input_iterator_tag,
                                        random_access_iterator_tag){}

inline void CGAL__Has_to_be_at_least(output_iterator_tag,output_iterator_tag){}
inline void CGAL__Has_to_be_at_least(output_iterator_tag,forward_iterator_tag){}
inline void CGAL__Has_to_be_at_least(output_iterator_tag,
                                        bidirectional_iterator_tag){}
inline void CGAL__Has_to_be_at_least(output_iterator_tag,
                                        random_access_iterator_tag){}

inline void CGAL__Has_to_be_at_least(forward_iterator_tag,
                                        forward_iterator_tag){}
inline void CGAL__Has_to_be_at_least(forward_iterator_tag,
                                        bidirectional_iterator_tag){}
inline void CGAL__Has_to_be_at_least(forward_iterator_tag,
                                        random_access_iterator_tag){}

inline void CGAL__Has_to_be_at_least(bidirectional_iterator_tag,
                                        bidirectional_iterator_tag){}
inline void CGAL__Has_to_be_at_least(bidirectional_iterator_tag,
                                        random_access_iterator_tag){}

inline void CGAL__Has_to_be_at_least(random_access_iterator_tag,
                                        random_access_iterator_tag){}

// The is-at-least assertions.
template <class I> inline
void CGAL_kernel_assertion_is_at_least_input_category( const I& i) {
     CGAL__Has_to_be_at_least(input_iterator_tag(), iterator_category(i));
}
template <class I> inline
void CGAL_kernel_assertion_is_at_least_output_category( const I& i) {
     CGAL__Has_to_be_at_least(output_iterator_tag(), iterator_category(i));
}
template <class IC> inline
void CGAL_kernel_assertion_is_at_least_forward_category( const IC& ic) {
     CGAL__Has_to_be_at_least(forward_iterator_tag(), iterator_category(ic));
}
template <class IC> inline
void CGAL_kernel_assertion_is_at_least_bidirectional_category( const IC& ic) {
     CGAL__Has_to_be_at_least(bidirectional_iterator_tag(),
                             iterator_category(ic)) ;
}
template <class IC> inline
void CGAL_kernel_assertion_is_at_least_random_access_category( const IC& ic) {
     CGAL__Has_to_be_at_least(random_access_iterator_tag(),
                             iterator_category(ic));
}
 
 
 
#ifdef __sgi
#if 0 // AF

#ifdef DEQUE_H
template< class T, class Alloc> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const deque<T,Alloc>::iterator&){
    return CGAL_Iterator_tag();
}
template< class T, class Alloc> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const deque<T,Alloc>::const_iterator&){
    return CGAL_Iterator_tag();
}
#endif // DEQUE_H //

#ifdef SGI_STL_HASHTABLE_H
template< class V, class K, class HF, class ExK, class EqK, class All>
inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
        const hashtable<V, K, HF, ExK, EqK, All>::iterator&){
    return CGAL_Iterator_tag();
}
template< class V, class K, class HF, class ExK, class EqK, class All>
inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
        const hashtable<V, K, HF, ExK, EqK, All>::const_iterator&){
    return CGAL_Iterator_tag();
}
#endif // SGI_STL_HASHTABLE_H //

#ifdef LIST_H
template< class T, class Alloc> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const list<T,Alloc>::iterator&){
    return CGAL_Iterator_tag();
}
template< class T, class Alloc> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const list<T,Alloc>::const_iterator&){
    return CGAL_Iterator_tag();
}
#endif // LIST_H //

#ifdef TREE_H
template< class K, class V, class KoV, class Cmp, class Alloc> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
        const rb_tree<K,V,KoV,Cmp,Alloc>::iterator&){
    return CGAL_Iterator_tag();
}
template< class K, class V, class KoV, class Cmp, class Alloc> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
        const rb_tree<K,V,KoV,Cmp,Alloc>::const_iterator&){
    return CGAL_Iterator_tag();
}
#endif // TREE_H //
#endif // AF
#endif // __sgi//
 
                 

 
template< class C> inline
bool CGAL__is_empty_range( const C& c1, const C&, CGAL_Circulator_tag){
    return c1 == NULL;
}

template< class I> inline
bool CGAL__is_empty_range( const I& i1, const I& i2, CGAL_Iterator_tag){
    return i1 == i2;
}

template< class IC> inline
bool CGAL_is_empty_range( const IC& ic1, const IC& ic2){
    // is `true' if the range [`ic1, ic2') is empty, `false' otherwise.
    // Precondition: `T' is either a circulator or an iterator type. The
    // range [`ic1, ic2') is valid.
    return CGAL__is_empty_range( ic1,
                                ic2,
                                CGAL_query_circulator_or_iterator( ic1));
}

struct CGAL_Circulator_or_iterator_tag {};  // any circulator or iterator.

inline
CGAL_Circulator_or_iterator_tag
CGAL_check_circulator_or_iterator( CGAL_Circulator_tag ){
    return CGAL_Circulator_or_iterator_tag();
}
inline
CGAL_Circulator_or_iterator_tag
CGAL_check_circulator_or_iterator( CGAL_Iterator_tag ){
    return CGAL_Circulator_or_iterator_tag();
}

template< class IC> inline
void CGAL_kernel_assertion_circulator_or_iterator( const IC &ic){
    CGAL_kernel_assertion_compile_time_tag(
        CGAL_Circulator_or_iterator_tag(),
        CGAL_check_circulator_or_iterator(
            CGAL_query_circulator_or_iterator( ic)
        )
    );
}
 
 

 
template <class C>
C CGAL_find_minimal_circulator(C c) {
    CGAL_kernel_assertion_circulator(c);
    CGAL_kernel_assertion_random_access_category(c);
    if ( c == NULL)
        return c;
    // c is searching forwards, d is searching backwards.
    C d = c;
    d--;
    while(true) {
        if ( (c-1) - c >= 0)
            return c;
        CGAL_kernel_assertion( c != d);
        ++c;
        if ( (d-1) - d >= 0)
            return d;
        CGAL_kernel_assertion( c != d);
        --d;
    }
}
 
template <class C> inline
size_t
CGAL__min_circulator_size(const C& c) {
    CGAL_kernel_assertion_circulator(c);
    CGAL_kernel_assertion_random_access_category(c);
    size_t n = 0;
    if ( c != NULL) {
        n = (c-1) - c + 1;
        CGAL_kernel_assertion(n > 0);
    }
    return n;
}

template <class C>
size_t CGAL__circulator_size(const C& c, forward_iterator_tag) {
    // Simply count.
    if ( c == NULL)
        return 0;
    size_t n = 0;
    C      d = c;
    do {
        ++n;
        ++d;
    } while( c != d);
    return n;
}
template <class C> inline
size_t CGAL__circulator_size(const C& c, bidirectional_iterator_tag) {
    return CGAL__circulator_size( c, forward_iterator_tag());
}
template <class C>
size_t CGAL__circulator_size(const C& c, random_access_iterator_tag) {
    return CGAL__min_circulator_size( CGAL_find_minimal_circulator(c));
}

template <class C> inline
size_t CGAL_circulator_size(const C& c) {
    return CGAL__circulator_size( c, iterator_category(c));
}
 
template<class I, class U> inline
I CGAL_non_negative_mod(I n, U m) {
    CGAL_kernel_assertion( m > 0);
    #if (-1 % 3) > 0
        n = n % m;
    #else
    if (n < 0)
        n = - (( - n - 1) % m) + m - 1;
    else
        n = n % m;
    #endif
    CGAL_kernel_assertion( n >= 0);
    return n;
}
 

 
template < class  C>
class CGAL_Forward_iterator_from_circulator
    : public forward_iterator< C::value_type, C::distance_type> {
private:
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// CREATION

    CGAL_Forward_iterator_from_circulator() : anchor(0), winding(0) {}

    CGAL_Forward_iterator_from_circulator( const C* circ, int n)
        : anchor( circ), current( *circ), winding(n) {}

    CGAL_Forward_iterator_from_circulator(
            const CGAL_Forward_iterator_from_circulator<C>& c)
        : anchor(c.anchor), current(c.current), winding(c.winding) {}

//
// OPERATIONS

    bool operator==( const CGAL_Forward_iterator_from_circulator<C>& i)
    const {
        CGAL_kernel_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=( const CGAL_Forward_iterator_from_circulator<C>& i)
    const {
        return !(*this == i);
    }
    C::reference  operator*() const {
        CGAL_kernel_assertion( anchor  != NULL);
        CGAL_kernel_assertion( current != NULL);
        return *current;
    }
    CGAL_Forward_iterator_from_circulator<C>&
    operator++() {
        CGAL_kernel_assertion( anchor  != NULL);
        CGAL_kernel_assertion( current != NULL);
        if ( current == *anchor)
            ++winding;
        ++current;
        return *this;
    }
    CGAL_Forward_iterator_from_circulator<C>
    operator++(int) {
        CGAL_Forward_iterator_from_circulator<C> tmp = *this;
        ++*this;
        return tmp;
    }
};

template < class  C>
class CGAL_Forward_const_iterator_from_circulator
    : public forward_iterator< C::value_type, C::distance_type> {
private:
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// CREATION

    CGAL_Forward_const_iterator_from_circulator() : anchor(0), winding(0) {}

    CGAL_Forward_const_iterator_from_circulator( const C* circ, int n)
        : anchor( circ), current( *circ), winding(n) {}

    CGAL_Forward_const_iterator_from_circulator(
            const CGAL_Forward_const_iterator_from_circulator<C>& c)
        : anchor(c.anchor), current(c.current), winding(c.winding) {}
//
// OPERATIONS

    bool operator==(
            const CGAL_Forward_const_iterator_from_circulator<C>& i) const {
        CGAL_kernel_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=(
            const CGAL_Forward_const_iterator_from_circulator<C>& i) const {
        return !(*this == i);
    }
    C::const_reference  operator*() const {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        return *current;
    }
    CGAL_Forward_const_iterator_from_circulator<C>&
    operator++() {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        if ( current == *anchor)
            ++winding;
        ++current;
        return *this;
    }
    CGAL_Forward_const_iterator_from_circulator<C>
    operator++(int) {
        CGAL_Forward_const_iterator_from_circulator<C> tmp = *this;
        ++*this;
        return tmp;
    }
};

template < class  C>
class CGAL_Bidirectional_iterator_from_circulator
    : public bidirectional_iterator< C::value_type, C::distance_type> {
private:
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// CREATION

    CGAL_Bidirectional_iterator_from_circulator() : anchor(0), winding(0) {}

    CGAL_Bidirectional_iterator_from_circulator( const C* circ, int n)
        : anchor( circ), current( *circ), winding(n) {}

    CGAL_Bidirectional_iterator_from_circulator(
             const CGAL_Bidirectional_iterator_from_circulator<C>& c)
        : anchor(c.anchor), current(c.current), winding(c.winding) {}
//
// OPERATIONS

    bool operator==(
            const CGAL_Bidirectional_iterator_from_circulator<C>& i) const {
        CGAL_kernel_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=(
            const CGAL_Bidirectional_iterator_from_circulator<C>& i) const {
        return !(*this == i);
    }
    C::reference  operator*() const {
        CGAL_kernel_assertion( anchor  != NULL);
        CGAL_kernel_assertion( current != NULL);
        return *current;
    }
    CGAL_Bidirectional_iterator_from_circulator<C>&
    operator++() {
        CGAL_kernel_assertion( anchor  != NULL);
        CGAL_kernel_assertion( current != NULL);
        if ( current == *anchor)
            ++winding;
        ++current;
        return *this;
    }
    CGAL_Bidirectional_iterator_from_circulator<C>
    operator++(int) {
        CGAL_Bidirectional_iterator_from_circulator<C> tmp = *this;
        ++*this;
        return tmp;
    }

    CGAL_Bidirectional_iterator_from_circulator<C>&
    operator--() {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        --current;
        if ( current == *anchor)
            --winding;
        return *this;
    }
    CGAL_Bidirectional_iterator_from_circulator<C>
    operator--(int) {
        CGAL_Bidirectional_iterator_from_circulator<C> tmp = *this;
        --*this;
        return tmp;
    }
};

template < class  C>
class CGAL_Bidirectional_const_iterator_from_circulator
    : public bidirectional_iterator< C::value_type, C::distance_type> {
private:
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// CREATION

    CGAL_Bidirectional_const_iterator_from_circulator()
        : anchor(0), winding(0) {}

    CGAL_Bidirectional_const_iterator_from_circulator(const C* circ, int n)
        : anchor( circ), current( *circ), winding(n) {}

    CGAL_Bidirectional_const_iterator_from_circulator(
            const CGAL_Bidirectional_const_iterator_from_circulator<C>& c)
        : anchor(c.anchor), current(c.current), winding(c.winding) {}
//
// OPERATIONS

    bool operator==( const
            CGAL_Bidirectional_const_iterator_from_circulator<C>& i) const {
        CGAL_kernel_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=( const
            CGAL_Bidirectional_const_iterator_from_circulator<C>& i) const {
        return !(*this == i);
    }
    C::const_reference  operator*() const {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        return *current;
    }
    CGAL_Bidirectional_const_iterator_from_circulator<C>&
    operator++() {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        if ( current == *anchor)
            ++winding;
        ++current;
        return *this;
    }
    CGAL_Bidirectional_const_iterator_from_circulator<C>
    operator++(int) {
        CGAL_Bidirectional_const_iterator_from_circulator<C> tmp = *this;
        ++*this;
        return tmp;
    }

    CGAL_Bidirectional_const_iterator_from_circulator<C>&
    operator--() {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        --current;
        if ( current == *anchor)
            --winding;
        return *this;
    }
    CGAL_Bidirectional_const_iterator_from_circulator<C>
    operator--(int) {
        CGAL_Bidirectional_const_iterator_from_circulator<C> tmp = *this;
        --*this;
        return tmp;
    }
};

template < class  C>
class CGAL_Random_access_iterator_from_circulator
    : public random_access_iterator< C::value_type, C::distance_type> {
private:
    // The anchor is normalized to be a minimal circulator.
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// CREATION

    CGAL_Random_access_iterator_from_circulator() : anchor(0), winding(0) {}

    CGAL_Random_access_iterator_from_circulator( const C* circ, int n)
        : anchor( circ), current( *circ), winding(n) {}

    CGAL_Random_access_iterator_from_circulator(
            const CGAL_Random_access_iterator_from_circulator<C>& c)
        : anchor(c.anchor), current(c.current), winding(c.winding) {}
//
// OPERATIONS

    bool operator==(
            const CGAL_Random_access_iterator_from_circulator<C>& i) const {
        CGAL_kernel_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=(
            const CGAL_Random_access_iterator_from_circulator<C>& i) const {
        return !(*this == i);
    }
    C::reference  operator*() const {
        CGAL_kernel_assertion( anchor  != NULL);
        CGAL_kernel_assertion( current != NULL);
        return *current;
    }
    CGAL_Random_access_iterator_from_circulator<C>&
    operator++() {
        CGAL_kernel_assertion( anchor  != NULL);
        CGAL_kernel_assertion( current != NULL);
        ++current;
        if ( current == *anchor)
            ++winding;
        return *this;
    }
    CGAL_Random_access_iterator_from_circulator<C>
    operator++(int) {
        CGAL_Random_access_iterator_from_circulator<C> tmp = *this;
        ++*this;
        return tmp;
    }

    CGAL_Random_access_iterator_from_circulator<C>&
    operator--() {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        if ( current == *anchor)
            --winding;
        --current;
        return *this;
    }
    CGAL_Random_access_iterator_from_circulator<C>
    operator--(int) {
        CGAL_Random_access_iterator_from_circulator<C> tmp = *this;
        --*this;
        return tmp;
    }

    CGAL_Random_access_iterator_from_circulator<C>&
    operator+=( C::distance_type n) {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        if ( n < 0 && current == *anchor)  // We are leaving the anchor.
            --winding;
        current += n;
        if ( n > 0 && current == *anchor)  // Back again at the anchor.
            ++winding;
        return *this;
    }
    CGAL_Random_access_iterator_from_circulator<C>
    operator+( C::distance_type n) const {
        CGAL_Random_access_iterator_from_circulator<C> tmp = *this;
        return tmp += n;
    }
    CGAL_Random_access_iterator_from_circulator<C>&
    operator-=( C::distance_type n) {
        return operator+=( -n);
    }
    CGAL_Random_access_iterator_from_circulator<C>
    operator-( C::distance_type n) const {
        CGAL_Random_access_iterator_from_circulator<C> tmp = *this;
        return tmp += -n;
    }
    #if !defined(__GNUG__) && !defined(__SUNPRO_CC)
    C::distance_type
    operator-(
            const CGAL_Random_access_iterator_from_circulator<C>& i) const;
    #else
    C::distance_type
    operator-(
            const CGAL_Random_access_iterator_from_circulator<C>& i) const {
        CGAL_kernel_assertion( anchor  != NULL);
        CGAL_kernel_assertion( current != NULL);
        CGAL_kernel_assertion( anchor  == i.anchor);
        if ( winding != i.winding) {
            C::distance_type s = CGAL__min_circulator_size( *anchor);
            return   (current - *anchor) - (i.current - *anchor)
                   + s * (winding - i.winding);
        }
        return (current - *anchor) - (i.current - *anchor);
    }
    #endif

    C::reference  operator[](C::distance_type n) const {
        CGAL_Random_access_iterator_from_circulator<C> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    bool
    operator<( const
            CGAL_Random_access_iterator_from_circulator<C>& i) const {
        CGAL_kernel_assertion( anchor  != NULL);
        CGAL_kernel_assertion( current != NULL);
        CGAL_kernel_assertion( anchor  == i.anchor);
        return (     (winding < i.winding)
                 || (    (winding == i.winding)
                      && (current - *anchor) < (i.current - *anchor)
                    )
               );
    }
    bool
    operator>(
            const CGAL_Random_access_iterator_from_circulator<C>& i) const {
        return i < *this;
    }
    bool
    operator<=(
            const CGAL_Random_access_iterator_from_circulator<C>& i) const {
        return !(i < *this);
    }
    bool
    operator>=(
            const CGAL_Random_access_iterator_from_circulator<C>& i) const {
        return !(*this < i);
    }
};

template < class Dist, class  C>
CGAL_Random_access_iterator_from_circulator<C>
operator+( Dist n,
           const CGAL_Random_access_iterator_from_circulator<C>& circ) {
    CGAL_Random_access_iterator_from_circulator<C> tmp = circ;
    return tmp += n;
}

#if !defined(__GNUG__) && !defined(__SUNPRO_CC)
template < class  C>
C::distance_type
CGAL_Random_access_iterator_from_circulator<C>::
operator-( const CGAL_Random_access_iterator_from_circulator<C>& i) const {
    CGAL_kernel_assertion( anchor  != NULL);
    CGAL_kernel_assertion( current != NULL);
    CGAL_kernel_assertion( anchor  == i.anchor);
    if ( winding != i.winding) {
        C::distance_type s = CGAL__min_circulator_size( *anchor);
        return   (current - *anchor) - (i.current - *anchor)
               + s * (winding - i.winding);
    }
    return (current - *anchor) - (i.current - *anchor);
}
#endif


template < class  C>
class CGAL_Random_access_const_iterator_from_circulator
    : public random_access_iterator< C::value_type, C::distance_type> {
private:
    // The anchor is normalized to be a minimal circulator.
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// CREATION

    CGAL_Random_access_const_iterator_from_circulator()
        : anchor(0), winding(0) {}

    CGAL_Random_access_const_iterator_from_circulator( const C* circ, int n)
        : anchor( circ), current( *circ), winding(n) {}

    CGAL_Random_access_const_iterator_from_circulator(
            const CGAL_Random_access_const_iterator_from_circulator<C>& c)
        : anchor(c.anchor), current(c.current), winding(c.winding) {}
//
// OPERATIONS

    bool operator==( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
        CGAL_kernel_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
        return !(*this == i);
    }
    C::const_reference  operator*() const {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        return *current;
    }
    CGAL_Random_access_const_iterator_from_circulator<C>&
    operator++() {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        ++current;
        if ( current == *anchor)
            ++winding;
        return *this;
    }
    CGAL_Random_access_const_iterator_from_circulator<C>
    operator++(int) {
        CGAL_Random_access_const_iterator_from_circulator<C> tmp = *this;
        ++*this;
        return tmp;
    }

    CGAL_Random_access_const_iterator_from_circulator<C>&
    operator--() {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        if ( current == *anchor)
            --winding;
        --current;
        return *this;
    }
    CGAL_Random_access_const_iterator_from_circulator<C>
    operator--(int) {
        CGAL_Random_access_const_iterator_from_circulator<C> tmp = *this;
        --*this;
        return tmp;
    }

    CGAL_Random_access_const_iterator_from_circulator<C>&
    operator+=( C::distance_type n) {
        CGAL_kernel_assertion( anchor != NULL);
        CGAL_kernel_assertion( current != NULL);
        if ( n < 0 && current == *anchor)  // We are leaving the anchor.
            --winding;
        current += n;
        if ( n > 0 && current == *anchor)  // Back again at the anchor.
            ++winding;
        return *this;
    }
    CGAL_Random_access_const_iterator_from_circulator<C>
    operator+( C::distance_type n) const {
        CGAL_Random_access_const_iterator_from_circulator<C> tmp = *this;
        return tmp += n;
    }
    CGAL_Random_access_const_iterator_from_circulator<C>&
    operator-=( C::distance_type n) {
        return operator+=( -n);
    }
    CGAL_Random_access_const_iterator_from_circulator<C>
    operator-( C::distance_type n) const {
        CGAL_Random_access_const_iterator_from_circulator<C> tmp = *this;
        return tmp += -n;
    }
    #if !defined(__GNUG__) && !defined(__SUNPRO_CC)
    C::distance_type
    operator-( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const;
    #else
    C::distance_type
    operator-( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
        CGAL_kernel_assertion( anchor  != NULL);
        CGAL_kernel_assertion( current != NULL);
        CGAL_kernel_assertion( anchor  == i.anchor);
        if ( winding != i.winding) {
            C::distance_type s = CGAL__min_circulator_size( *anchor);
            return   (current - *anchor) - (i.current - *anchor)
                   + s * (winding - i.winding);
        }
        return (current - *anchor) - (i.current - *anchor);
    }
    #endif

    C::const_reference  operator[](C::distance_type n) const {
        CGAL_Random_access_const_iterator_from_circulator<C> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    bool
    operator<( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
        CGAL_kernel_assertion( anchor  != NULL);
        CGAL_kernel_assertion( current != NULL);
        CGAL_kernel_assertion( anchor  == i.anchor);
        return (     (winding < i.winding)
                 || (    (winding == i.winding)
                      && (current - *anchor) < (i.current - *anchor)
                    )
               );
    }
    bool
    operator>( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
        return i < *this;
    }
    bool
    operator<=( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
        return !(i < *this);
    }
    bool
    operator>=( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
        return !(*this < i);
    }
};

template < class Dist, class  C>
CGAL_Random_access_const_iterator_from_circulator<C>
operator+( Dist n, const
           CGAL_Random_access_const_iterator_from_circulator<C>& circ) {
    CGAL_Random_access_const_iterator_from_circulator<C> tmp = circ;
    return tmp += n;
}

#if !defined(__GNUG__) && !defined(__SUNPRO_CC)
template < class  C>
C::distance_type
CGAL_Random_access_const_iterator_from_circulator<C>::
operator-( const
        CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
    CGAL_kernel_assertion( anchor  != NULL);
    CGAL_kernel_assertion( current != NULL);
    CGAL_kernel_assertion( anchor  == i.anchor);
    if ( winding != i.winding) {
        C::distance_type s = CGAL__min_circulator_size( *anchor);
        return   (current - *anchor) - (i.current - *anchor)
               + s * (winding - i.winding);
    }
    return (current - *anchor) - (i.current - *anchor);
}
#endif


template < class  C >
class CGAL_Forward_container_from_circulator {
private:
    C anchor;
public:

// DEFINITION
//
// The adaptor CGAL_Forward_container_from_circulator<C> is a class that
// converts any circulator type `C' to a kind of containerclass, i.e. a
// class that provides an iterator and a const iterator type and two
// member functions -- begin() and end() -- that return the appropriate
// forward iterators. In analogy to STL container classes these member
// functions return a const iterator in the case that the container itself
// is constant and a mutable iterator otherwise.
//
// For CGAL_Forward_container_from_circulator<C> the circulator has to
// fulfill at least the requirements for a forward circulator. The similar
// adaptor `CGAL_Bidirectional_container_from_circulator<C>' requires a
// bidirectional circulator to provide bidirectional iterators and the
// adaptor `CGAL_Random_access_container_from_circulator<C>' requires a
// random access circulator to provide random access iterators. In this
// case the adaptor implements a total ordering relation that is currently
// not required for random access circulators. The total order is based on
// the difference value from all circulators to the circulator given at
// construction time. The difference value is a consistent ordering as
// stated in the requirements for random access circulators.
//
// PARAMETERS
//
// `C' is the appropriate circulator type.
//
// CREATION
//
// New creation variable is: `adaptor'

    CGAL_Forward_container_from_circulator() {}
        // the resulting iterators will have a singular value.

    CGAL_Forward_container_from_circulator(const C& c) : anchor(c) {}
        // the resulting iterators will have a singular value if the
        // circulator `c' is singular.

    CGAL_Forward_container_from_circulator(
        const CGAL_Forward_container_from_circulator<C>& i)
        : anchor(i.anchor) {}
//
// TYPES

typedef CGAL_Forward_const_iterator_from_circulator<C>  const_iterator;
typedef CGAL_Forward_iterator_from_circulator<C>        iterator;

typedef C::value_type       value_type;
typedef C::reference        reference;
typedef C::const_reference  const_reference;
typedef C::size_type        size_type;
typedef C::distance_type    difference_type;

//
// OPERATIONS

    iterator begin() {
        // the start iterator.
        return iterator( &anchor, 0);
    }

    const_iterator begin() const {
        // the start const iterator.
        return const_iterator( &anchor, 0);
    }

    iterator end() {
        // the past-the-end iterator.
        return anchor == NULL ?  iterator( &anchor, 0)
                              :  iterator( &anchor, 1);
    }
    const_iterator end() const {
        // the past-the-end const iterator.
        return anchor == NULL ?  const_iterator( &anchor, 0)
                              :  const_iterator( &anchor, 1);
    }
    
 
    #ifdef __GNUG__
    friend inline difference_type* distance_type(const iterator&) {
        return (difference_type*)(0);
    }
    friend inline value_type* value_type(const iterator&) {
        return (value_type*)(0);
    }
    friend inline forward_iterator_tag iterator_category(iterator) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Iterator_tag CGAL_query_circulator_or_iterator(iterator) {
        return CGAL_Iterator_tag();
    }
    
    friend inline difference_type* distance_type(const const_iterator&) {
        return (difference_type*)(0);
    }
    friend inline value_type* value_type(const const_iterator&) {
        return (value_type*)(0);
    }
    friend inline forward_iterator_tag iterator_category(const_iterator) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Iterator_tag CGAL_query_circulator_or_iterator(
            const_iterator) {
        return CGAL_Iterator_tag();
    }
    #endif
 
          
};


template < class  C >
class CGAL_Bidirectional_container_from_circulator {
private:
    C anchor;
public:
//
// CREATION

    CGAL_Bidirectional_container_from_circulator() {}
        // the resulting iterators will have a singular value.

    CGAL_Bidirectional_container_from_circulator(const C& c) : anchor(c) {}
        // the resulting iterators will have a singular value if the
        // circulator `c' is singular.

    CGAL_Bidirectional_container_from_circulator(
        const CGAL_Bidirectional_container_from_circulator<C>& i)
        : anchor(i.anchor) {}
//
// TYPES

typedef CGAL_Bidirectional_iterator_from_circulator<C>       iterator;
typedef CGAL_Bidirectional_const_iterator_from_circulator<C> const_iterator;

typedef C::value_type       value_type;
typedef C::reference        reference;
typedef C::const_reference  const_reference;
typedef C::size_type        size_type;
typedef C::distance_type    difference_type;

//
// OPERATIONS

    iterator begin() {
        // the start iterator.
        return iterator( &anchor, 0);
    }

    const_iterator begin() const {
        // the start const iterator.
        return const_iterator( &anchor, 0);
    }

    iterator end() {
        // the past-the-end iterator.
        return anchor == NULL ?  iterator( &anchor, 0)
                              :  iterator( &anchor, 1);
    }
    const_iterator end() const {
        // the past-the-end const iterator.
        return anchor == NULL ?  const_iterator( &anchor, 0)
                              :  const_iterator( &anchor, 1);
    }
    
 
    #ifdef __GNUG__
    friend inline difference_type* distance_type(const iterator&) {
        return (difference_type*)(0);
    }
    friend inline value_type* value_type(const iterator&) {
        return (value_type*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(iterator) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Iterator_tag CGAL_query_circulator_or_iterator(iterator) {
        return CGAL_Iterator_tag();
    }
    
    friend inline difference_type* distance_type(const const_iterator&) {
        return (difference_type*)(0);
    }
    friend inline value_type* value_type(const const_iterator&) {
        return (value_type*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(const_iterator) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Iterator_tag CGAL_query_circulator_or_iterator(
            const_iterator) {
        return CGAL_Iterator_tag();
    }
    #endif
 
          
};


template < class  C >
class CGAL_Random_access_container_from_circulator {
private:
    C anchor;
public:
//
// CREATION

    CGAL_Random_access_container_from_circulator() {}
        // the resulting iterators will have a singular value.

    CGAL_Random_access_container_from_circulator(const C& c)
        // The anchor is normalized to be a minimal circulator.
        : anchor(CGAL_find_minimal_circulator(c)) {}
        // the resulting iterators will have a singular value if the
        // circulator `c' is singular.

    CGAL_Random_access_container_from_circulator(
        // The anchor is normalized to be a minimal circulator.
        const CGAL_Random_access_container_from_circulator<C>& i)
        : anchor(CGAL_find_minimal_circulator(i.anchor)) {}
//
// TYPES

typedef CGAL_Random_access_iterator_from_circulator<C>       iterator;
typedef CGAL_Random_access_const_iterator_from_circulator<C> const_iterator;

typedef C::value_type       value_type;
typedef C::reference        reference;
typedef C::const_reference  const_reference;
typedef C::size_type        size_type;
typedef C::distance_type    difference_type;

//
// OPERATIONS

    iterator begin() {
        // the start iterator.
        return iterator( &anchor, 0);
    }

    const_iterator begin() const {
        // the start const iterator.
        return const_iterator( &anchor, 0);
    }

    iterator end() {
        // the past-the-end iterator.
        return anchor == NULL ?  iterator( &anchor, 0)
                              :  iterator( &anchor, 1);
    }
    const_iterator end() const {
        // the past-the-end const iterator.
        return anchor == NULL ?  const_iterator( &anchor, 0)
                              :  const_iterator( &anchor, 1);
    }
    
 
    #ifdef __GNUG__
    friend inline difference_type* distance_type(const iterator&) {
        return (difference_type*)(0);
    }
    friend inline value_type* value_type(const iterator&) {
        return (value_type*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(iterator) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Iterator_tag CGAL_query_circulator_or_iterator(iterator) {
        return CGAL_Iterator_tag();
    }
    
    friend inline difference_type* distance_type(const const_iterator&) {
        return (difference_type*)(0);
    }
    friend inline value_type* value_type(const const_iterator&) {
        return (value_type*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(const_iterator) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Iterator_tag CGAL_query_circulator_or_iterator(
            const_iterator) {
        return CGAL_Iterator_tag();
    }
    #endif
 
          
};
 
  
 
template < class  Container>
class CGAL_Forward_circulator_from_container
    : public  CGAL_Forward_circulator_ptrbase<
            Container::value_type, Container::difference_type> {
private:
    Container::iterator  i;
public:

// DEFINITION
//
// The adaptor CGAL_Forward_circulator_from_container<C> is a class that
// provides a forward circulator for a container C as specified by the
// STL. The iterators belonging to the container C are supposed to be at
// least forward iterators. The adaptor for bidirectional circulators is
// `CGAL_Bidirectional_circulator_from_container<C>' and
// `CGAL_Random_access_circulator_from_container<C>' for random access
// circulators. Appropriate const circulators are also available.
//
// PARAMETERS
//
// `C' is the container type. The container is supposed to conform to the
// STL requirements for container (i.e. to have a `begin()' and an `end()'
// iterator as well as the local types `value_type', `size_type()', and
// `difference_type').
//
// CREATION

    CGAL_Forward_circulator_from_container() {}

    CGAL_Forward_circulator_from_container( Container* c)
        :  CGAL_Forward_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c),
           i(c->begin()) {}

    CGAL_Forward_circulator_from_container( Container* c,
                                                 Container::iterator _i)
        :  CGAL_Forward_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c),
           i(_i) {}

    CGAL_Forward_circulator_from_container(
        const CGAL_Forward_circulator_from_container<Container>& c)
        :  CGAL_Forward_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef Container::value_type         value_type;
    typedef Container::reference          reference;
    typedef Container::const_reference    const_reference;
    typedef Container::size_type          size_type;
    typedef Container::difference_type    distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((Container*)_ptr)->begin()==((Container*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Forward_circulator_from_container
                           <Container>& c) const {
        return i == c.i;
    }
    bool operator!=( const CGAL_Forward_circulator_from_container
                           <Container>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((Container*)_ptr)->end());
        return *i;
    }
    CGAL_Forward_circulator_from_container<Container>&
    operator++() {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((Container*)_ptr)->end());
        ++i;
        if ( i == ((Container*)_ptr)->end())
            i = ((Container*)_ptr)->begin();
        return *this;
    }
    CGAL_Forward_circulator_from_container<Container>
    operator++(int) {
        CGAL_Forward_circulator_from_container<Container> tmp= *this;
        ++*this;
        return tmp;
    }
    
 
    #ifdef __GNUG__
    friend inline Container::difference_type* distance_type(
        const
    CGAL_Forward_circulator_from_container<Container>&) {
        return (Container::difference_type*)(0);
    }
    friend inline Container::value_type* value_type(
        const
    CGAL_Forward_circulator_from_container<Container>&) {
        return (Container::value_type*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_circulator_from_container<Container>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_circulator_from_container<Container>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};

template < class  Container>
class CGAL_Forward_const_circulator_from_container
    : public  CGAL_Forward_circulator_ptrbase<
            Container::value_type, Container::difference_type> {
private:
    Container::const_iterator  i;
public:
//
// CREATION

    CGAL_Forward_const_circulator_from_container() {}

    CGAL_Forward_const_circulator_from_container( const Container* c)
        :  CGAL_Forward_circulator_ptrbase<
              Container::value_type, Container::difference_type>((void*)c),
           i(c->begin()) {}

    CGAL_Forward_const_circulator_from_container( const Container* c,
                                             Container::const_iterator _i)
        :  CGAL_Forward_circulator_ptrbase<
              Container::value_type, Container::difference_type>((void*)c),
           i(_i) {}

    CGAL_Forward_const_circulator_from_container(
        const
        CGAL_Forward_const_circulator_from_container<Container>& c)
        :  CGAL_Forward_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef Container::value_type         value_type;
    typedef Container::reference          reference;
    typedef Container::const_reference    const_reference;
    typedef Container::size_type          size_type;
    typedef Container::difference_type    distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((const Container*)_ptr)->begin()
                 ==((const Container*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Forward_const_circulator_from_container
                           <Container>& c) const {
        return i == c.i;
    }
    bool operator!=( const CGAL_Forward_const_circulator_from_container
                           <Container>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((const Container*)_ptr)->end());
        return *i;
    }
    CGAL_Forward_const_circulator_from_container<Container>&
    operator++() {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((const Container*)_ptr)->end());
        ++i;
        if ( i == ((const Container*)_ptr)->end())
            i = ((const Container*)_ptr)->begin();
        return *this;
    }
    CGAL_Forward_const_circulator_from_container<Container>
    operator++(int) {
        CGAL_Forward_const_circulator_from_container<Container>
            tmp= *this;
        ++*this;
        return tmp;
    }
    
 
    #ifdef __GNUG__
    friend inline Container::difference_type* distance_type(
        const
    CGAL_Forward_const_circulator_from_container<Container>&) {
        return (Container::difference_type*)(0);
    }
    friend inline Container::value_type* value_type(
        const
    CGAL_Forward_const_circulator_from_container<Container>&) {
        return (Container::value_type*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_const_circulator_from_container<Container>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_const_circulator_from_container<Container>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};


template < class  Container>
class CGAL_Bidirectional_circulator_from_container
    : public  CGAL_Bidirectional_circulator_ptrbase<
            Container::value_type, Container::difference_type> {
private:
    Container::iterator  i;
public:
//
// CREATION

    CGAL_Bidirectional_circulator_from_container() {}

    CGAL_Bidirectional_circulator_from_container( Container* c)
        :  CGAL_Bidirectional_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c),
           i(c->begin()) {}

    CGAL_Bidirectional_circulator_from_container( Container* c,
                                                 Container::iterator _i)
        :  CGAL_Bidirectional_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c),
           i(_i) {}

    CGAL_Bidirectional_circulator_from_container(
        const CGAL_Bidirectional_circulator_from_container<Container>& c)
        :  CGAL_Bidirectional_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef Container::value_type         value_type;
    typedef Container::reference          reference;
    typedef Container::const_reference    const_reference;
    typedef Container::size_type          size_type;
    typedef Container::difference_type    distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((Container*)_ptr)->begin()==((Container*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Bidirectional_circulator_from_container
                           <Container>& c) const {
        return i == c.i;
    }
    bool operator!=( const CGAL_Bidirectional_circulator_from_container
                           <Container>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((Container*)_ptr)->end());
        return *i;
    }
    CGAL_Bidirectional_circulator_from_container<Container>&
    operator++() {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((Container*)_ptr)->end());
        ++i;
        if ( i == ((Container*)_ptr)->end())
            i = ((Container*)_ptr)->begin();
        return *this;
    }
    CGAL_Bidirectional_circulator_from_container<Container>
    operator++(int) {
        CGAL_Bidirectional_circulator_from_container<Container> tmp= *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_circulator_from_container<Container>&
    operator--() {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((Container*)_ptr)->end());
        if ( i == ((Container*)_ptr)->begin())
            i = ((Container*)_ptr)->end();
        --i;
        return *this;
    }
    CGAL_Bidirectional_circulator_from_container<Container>
    operator--(int) {
        CGAL_Bidirectional_circulator_from_container<Container> tmp = *this;
        --*this;
        return tmp;
    }
    
 
    #ifdef __GNUG__
    friend inline Container::difference_type* distance_type(
        const
    CGAL_Bidirectional_circulator_from_container<Container>&) {
        return (Container::difference_type*)(0);
    }
    friend inline Container::value_type* value_type(
        const
    CGAL_Bidirectional_circulator_from_container<Container>&) {
        return (Container::value_type*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_circulator_from_container<Container>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_circulator_from_container<Container>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};

template < class  Container>
class CGAL_Bidirectional_const_circulator_from_container
    : public  CGAL_Bidirectional_circulator_ptrbase<
            Container::value_type, Container::difference_type> {
private:
    Container::const_iterator  i;
public:
//
// CREATION

    CGAL_Bidirectional_const_circulator_from_container() {}

    CGAL_Bidirectional_const_circulator_from_container( const Container* c)
        :  CGAL_Bidirectional_circulator_ptrbase<
              Container::value_type, Container::difference_type>((void*)c),
           i(c->begin()) {}

    CGAL_Bidirectional_const_circulator_from_container( const Container* c,
                                             Container::const_iterator _i)
        :  CGAL_Bidirectional_circulator_ptrbase<
              Container::value_type, Container::difference_type>((void*)c),
           i(_i) {}

    CGAL_Bidirectional_const_circulator_from_container(
        const
        CGAL_Bidirectional_const_circulator_from_container<Container>& c)
        :  CGAL_Bidirectional_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef Container::value_type         value_type;
    typedef Container::reference          reference;
    typedef Container::const_reference    const_reference;
    typedef Container::size_type          size_type;
    typedef Container::difference_type    distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((const Container*)_ptr)->begin()
                 ==((const Container*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Bidirectional_const_circulator_from_container
                           <Container>& c) const {
        return i == c.i;
    }
    bool operator!=(const CGAL_Bidirectional_const_circulator_from_container
                           <Container>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((const Container*)_ptr)->end());
        return *i;
    }
    CGAL_Bidirectional_const_circulator_from_container<Container>&
    operator++() {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((const Container*)_ptr)->end());
        ++i;
        if ( i == ((const Container*)_ptr)->end())
            i = ((const Container*)_ptr)->begin();
        return *this;
    }
    CGAL_Bidirectional_const_circulator_from_container<Container>
    operator++(int) {
        CGAL_Bidirectional_const_circulator_from_container<Container>
            tmp= *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_const_circulator_from_container<Container>&
    operator--() {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((const Container*)_ptr)->end());
        if ( i == ((const Container*)_ptr)->begin())
            i = ((const Container*)_ptr)->end();
        --i;
        return *this;
    }
    CGAL_Bidirectional_const_circulator_from_container<Container>
    operator--(int) {
        CGAL_Bidirectional_const_circulator_from_container<Container>
            tmp = *this;
        --*this;
        return tmp;
    }
    
 
    #ifdef __GNUG__
    friend inline Container::difference_type* distance_type(
        const
    CGAL_Bidirectional_const_circulator_from_container<Container>&) {
        return (Container::difference_type*)(0);
    }
    friend inline Container::value_type* value_type(
        const
    CGAL_Bidirectional_const_circulator_from_container<Container>&) {
        return (Container::value_type*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_const_circulator_from_container<Container>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_const_circulator_from_container<Container>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};


template < class  Container>
class CGAL_Random_access_circulator_from_container
    : public  CGAL_Random_access_circulator_ptrbase<
            Container::value_type, Container::difference_type> {
private:
    Container::iterator  i;
public:
//
// CREATION

    CGAL_Random_access_circulator_from_container() {}

    CGAL_Random_access_circulator_from_container( Container* c)
        :  CGAL_Random_access_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c),
           i(c->begin()) {}

    CGAL_Random_access_circulator_from_container( Container* c,
                                                 Container::iterator _i)
        :  CGAL_Random_access_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c),
           i(_i) {}

    CGAL_Random_access_circulator_from_container(
        const CGAL_Random_access_circulator_from_container<Container>& c)
        :  CGAL_Random_access_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef Container::value_type         value_type;
    typedef Container::reference          reference;
    typedef Container::const_reference    const_reference;
    typedef Container::size_type          size_type;
    typedef Container::difference_type    distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((Container*)_ptr)->begin()==((Container*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Random_access_circulator_from_container
                           <Container>& c) const {
        return i == c.i;
    }
    bool operator!=( const CGAL_Random_access_circulator_from_container
                           <Container>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((Container*)_ptr)->end());
        return *i;
    }
    CGAL_Random_access_circulator_from_container<Container>&
    operator++() {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((Container*)_ptr)->end());
        ++i;
        if ( i == ((Container*)_ptr)->end())
            i = ((Container*)_ptr)->begin();
        return *this;
    }
    CGAL_Random_access_circulator_from_container<Container>
    operator++(int) {
        CGAL_Random_access_circulator_from_container<Container> tmp= *this;
        ++*this;
        return tmp;
    }

    CGAL_Random_access_circulator_from_container<Container>&
    operator--() {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((Container*)_ptr)->end());
        if ( i == ((Container*)_ptr)->begin())
            i = ((Container*)_ptr)->end();
        --i;
        return *this;
    }
    CGAL_Random_access_circulator_from_container<Container>
    operator--(int) {
        CGAL_Random_access_circulator_from_container<Container> tmp = *this;
        --*this;
        return tmp;
    }

    #if !defined(__GNUG__) && !defined(__SUNPRO_CC)
    CGAL_Random_access_circulator_from_container<Container>&
    operator+=( distance_type n);
    #else
    CGAL_Random_access_circulator_from_container<Container>&
    operator+=( distance_type n) {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((Container*)_ptr)->end());

        Container::difference_type j    = i - ((Container*)_ptr)->begin();
        Container::difference_type size = ((Container*)_ptr)->size();
        CGAL_kernel_assertion( j    >= 0);
        CGAL_kernel_assertion( size >= 0);
        j = CGAL_non_negative_mod( j + n, size);
        CGAL_kernel_assertion( j >= 0);
        CGAL_kernel_assertion( j < size);
        i = ((Container*)_ptr)->begin() + j;
        return *this;
    }
    #endif

    CGAL_Random_access_circulator_from_container<Container>
    operator+( distance_type n) const {
        CGAL_Random_access_circulator_from_container<Container> tmp = *this;
        return tmp += n;
    }
    CGAL_Random_access_circulator_from_container<Container>&
    operator-=( distance_type n) {
        return operator+=( -n);
    }
    CGAL_Random_access_circulator_from_container<Container>
    operator-( distance_type n) const {
        CGAL_Random_access_circulator_from_container<Container> tmp = *this;
        return tmp += -n;
    }
    distance_type
    operator-( const CGAL_Random_access_circulator_from_container<
                   Container>& c) const {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( c._ptr != NULL);
        return i - c.i;
    }
    reference  operator[](distance_type n) const {
        CGAL_Random_access_circulator_from_container<Container> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }

    friend inline
    CGAL_Random_access_circulator_from_container<Container>
    operator+( distance_type n, const
               CGAL_Random_access_circulator_from_container<Container>& c) {
        CGAL_Random_access_circulator_from_container<Container> tmp = c;
        return tmp += n;
    }
    
 
    #ifdef __GNUG__
    friend inline Container::difference_type* distance_type(
        const
    CGAL_Random_access_circulator_from_container<Container>&) {
        return (Container::difference_type*)(0);
    }
    friend inline Container::value_type* value_type(
        const
    CGAL_Random_access_circulator_from_container<Container>&) {
        return (Container::value_type*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(
    CGAL_Random_access_circulator_from_container<Container>) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Random_access_circulator_from_container<Container>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};

#if !defined(__GNUG__) && !defined(__SUNPRO_CC)
template < class Container>
CGAL_Random_access_circulator_from_container<Container>&
CGAL_Random_access_circulator_from_container<Container>::
operator+=( Container::difference_type n) {
    CGAL_kernel_assertion( _ptr != NULL);
    CGAL_kernel_assertion( i != ((Container*)_ptr)->end());

    Container::difference_type j    = i - ((Container*)_ptr)->begin();
    Container::difference_type size = ((Container*)_ptr)->size();
    CGAL_kernel_assertion( j    >= 0);
    CGAL_kernel_assertion( size >= 0);
    j = CGAL_non_negative_mod( j + n, size);
    CGAL_kernel_assertion( j >= 0);
    CGAL_kernel_assertion( j < size);
    i = ((Container*)_ptr)->begin() + j;
    return *this;
}
#endif


template < class  Container>
class CGAL_Random_access_const_circulator_from_container
    : public  CGAL_Random_access_circulator_ptrbase<
            Container::value_type, Container::difference_type> {
private:
    Container::const_iterator  i;
public:
//
// CREATION

    CGAL_Random_access_const_circulator_from_container() {}

    CGAL_Random_access_const_circulator_from_container( const Container* c)
        :  CGAL_Random_access_circulator_ptrbase<
              Container::value_type, Container::difference_type>((void*)c),
           i(c->begin()) {}

    CGAL_Random_access_const_circulator_from_container( const Container* c,
                                             Container::const_iterator _i)
        :  CGAL_Random_access_circulator_ptrbase<
              Container::value_type, Container::difference_type>((void*)c),
           i(_i) {}

    CGAL_Random_access_const_circulator_from_container(
        const
        CGAL_Random_access_const_circulator_from_container<Container>& c)
        :  CGAL_Random_access_circulator_ptrbase<
              Container::value_type, Container::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef Container::value_type         value_type;
    typedef Container::reference          reference;
    typedef Container::const_reference    const_reference;
    typedef Container::size_type          size_type;
    typedef Container::difference_type    distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((const Container*)_ptr)->begin()
                 ==((const Container*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Random_access_const_circulator_from_container
                           <Container>& c) const {
        return i == c.i;
    }
    bool operator!=(const CGAL_Random_access_const_circulator_from_container
                           <Container>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((const Container*)_ptr)->end());
        return *i;
    }
    CGAL_Random_access_const_circulator_from_container<Container>&
    operator++() {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((const Container*)_ptr)->end());
        ++i;
        if ( i == ((const Container*)_ptr)->end())
            i = ((const Container*)_ptr)->begin();
        return *this;
    }
    CGAL_Random_access_const_circulator_from_container<Container>
    operator++(int) {
        CGAL_Random_access_const_circulator_from_container<Container>
            tmp= *this;
        ++*this;
        return tmp;
    }

    CGAL_Random_access_const_circulator_from_container<Container>&
    operator--() {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((const Container*)_ptr)->end());
        if ( i == ((const Container*)_ptr)->begin())
            i = ((const Container*)_ptr)->end();
        --i;
        return *this;
    }
    CGAL_Random_access_const_circulator_from_container<Container>
    operator--(int) {
        CGAL_Random_access_const_circulator_from_container<Container>
            tmp = *this;
        --*this;
        return tmp;
    }

    #if !defined(__GNUG__) && !defined(__SUNPRO_CC)
    CGAL_Random_access_const_circulator_from_container<Container>&
    operator+=( distance_type n);
    #else
    CGAL_Random_access_const_circulator_from_container<Container>&
    operator+=( distance_type n) {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( i != ((const Container*)_ptr)->end());

        Container::difference_type j    = i - ((const Container*)_ptr)
                                                ->begin();
        Container::difference_type size = ((const Container*)_ptr)->size();
        CGAL_kernel_assertion( j    >= 0);
        CGAL_kernel_assertion( size >= 0);
        j = CGAL_non_negative_mod( j + n, size);
        CGAL_kernel_assertion( j >= 0);
        CGAL_kernel_assertion( j < size);
        i = ((const Container*)_ptr)->begin() + j;
        return *this;
    }
    #endif

    CGAL_Random_access_const_circulator_from_container<Container>
    operator+( distance_type n) const {
        CGAL_Random_access_const_circulator_from_container<Container>
            tmp = *this;
        return tmp += n;
    }
    CGAL_Random_access_const_circulator_from_container<Container>&
    operator-=( distance_type n) {
        return operator+=( -n);
    }
    CGAL_Random_access_const_circulator_from_container<Container>
    operator-( distance_type n) const {
        CGAL_Random_access_const_circulator_from_container<Container>
            tmp = *this;
        return tmp += -n;
    }
    distance_type
    operator-( const CGAL_Random_access_const_circulator_from_container<
                   Container>& c) const {
        CGAL_kernel_assertion( _ptr != NULL);
        CGAL_kernel_assertion( c._ptr != NULL);
        return i - c.i;
    }
    const_reference  operator[](distance_type n) const {
        CGAL_Random_access_const_circulator_from_container<Container>
            tmp = *this;
        tmp += n;
        return tmp.operator*();
    }

    friend inline
    CGAL_Random_access_const_circulator_from_container<Container>
    operator+( distance_type n, const
               CGAL_Random_access_const_circulator_from_container<
                   Container>& c) {
        CGAL_Random_access_const_circulator_from_container<Container>
            tmp = c;
        return tmp += n;
    }
    
 
    #ifdef __GNUG__
    friend inline Container::difference_type* distance_type(
        const
    CGAL_Random_access_const_circulator_from_container<Container>&) {
        return (Container::difference_type*)(0);
    }
    friend inline Container::value_type* value_type(
        const
    CGAL_Random_access_const_circulator_from_container<Container>&) {
        return (Container::value_type*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(
    CGAL_Random_access_const_circulator_from_container<Container>) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Random_access_const_circulator_from_container<Container>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};

#if !defined(__GNUG__) && !defined(__SUNPRO_CC)
template < class Container>
CGAL_Random_access_const_circulator_from_container<Container>&
CGAL_Random_access_const_circulator_from_container<Container>::
operator+=( Container::difference_type n) {
    CGAL_kernel_assertion( _ptr != NULL);
    CGAL_kernel_assertion( i != ((const Container*)_ptr)->end());

    Container::difference_type j    = i - ((const Container*)_ptr)
                                            ->begin();
    Container::difference_type size = ((const Container*)_ptr)->size();
    CGAL_kernel_assertion( j    >= 0);
    CGAL_kernel_assertion( size >= 0);
    j = CGAL_non_negative_mod( j + n, size);
    CGAL_kernel_assertion( j >= 0);
    CGAL_kernel_assertion( j < size);
    i = ((const Container*)_ptr)->begin() + j;
    return *this;
}
#endif
 
      
 
template < class I, class T, class Size, class Dist>
class CGAL_Forward_circulator_from_iterator
    : public CGAL_Forward_circulator_base<T,Dist> {
private:
    I _begin;
    I _end;
    I current;
public:

// DEFINITION
//
// The adaptor CGAL_Forward_circulator_from_iterator< I, T,  Size, Dist>
// is a class that converts two iterators, a begin and a past-the-end
// value, to a forward circulator. The iterators are supposed to be at
// least forward iterators. The adaptor for bidirectional circulators is
// `CGAL_Bidirectional_circulator_from_iterator< I, T, Size, Dist>' and
// for random access circulators it is
// `CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>'.
// Appropriate const circulators are also available.
//
// PARAMETERS
//
// `I' is the appropriate iterator type, `T' its value type, `Size' the
// unsigned integral value to hold the possible number of items in a
// sequence, and `Dist' is a signed integral value, the distance type
// between two iterators of the same sequence.
//
// CREATION
//
// New creation variable is: `adaptor'

    CGAL_Forward_circulator_from_iterator()
        : _begin(I()), _end(I()), current(I()) {}
        // a circulator `adaptor' with a singular value.

    CGAL_Forward_circulator_from_iterator( const I& begin, const I& end)
        : _begin( begin), _end( end), current( begin) {}
        // a circulator `adaptor' initialized to refer to the element
        // `*begin' in a range [`begin' ,`end' ). The circulator `adaptor'
        // contains a singular value if `begin==end'.

    CGAL_Forward_circulator_from_iterator(
        const CGAL_Forward_circulator_from_iterator<I,T,Size,Dist>& c)
        : _begin( c._begin), _end( c._end), current( c.current) {}
//
// TYPES

    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        CGAL_kernel_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Forward_circulator_from_iterator<I, T, Size,
                     Dist>& c) const {
        CGAL_kernel_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Forward_circulator_from_iterator<I, T, Size,
                     Dist>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_kernel_assertion( current != _end);
        return *current;
    }
    CGAL_Forward_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_kernel_assertion( current != _end);
        ++current;
        if ( current == _end)
            current = _begin;
        return *this;
    }
    CGAL_Forward_circulator_from_iterator< I, T, Size, Dist>
    operator++(int) {
        CGAL_Forward_circulator_from_iterator< I, T, Size, Dist> tmp= *this;
        ++*this;
        return tmp;
    }
    
 
    #ifdef __GNUG__
    friend inline  Dist* distance_type(
        const
    CGAL_Forward_circulator_from_iterator<I, T, Size, Dist>&) {
        return ( Dist*)(0);
    }
    friend inline T* value_type(
        const
    CGAL_Forward_circulator_from_iterator<I, T, Size, Dist>&) {
        return (T*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_circulator_from_iterator<I, T, Size, Dist>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_circulator_from_iterator<I, T, Size, Dist>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};


template < class  I, class  T, class   Size, class  Dist >
class CGAL_Forward_const_circulator_from_iterator
    : public CGAL_Forward_circulator_base<T,Dist> {
private:
    I _begin;
    I _end;
    I current;
public:
//
// CREATION

    CGAL_Forward_const_circulator_from_iterator()
        : _begin(I()), _end(I()), current(I()) {}

    CGAL_Forward_const_circulator_from_iterator( const I& begin,
                                                const I& end)
        : _begin( begin), _end( end), current( begin) {}

    CGAL_Forward_const_circulator_from_iterator(
        const CGAL_Forward_const_circulator_from_iterator<I,T,Size,Dist>& c)
        : _begin( c._begin), _end( c._end), current( c.current) {}
//
// TYPES

    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        CGAL_kernel_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Forward_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        CGAL_kernel_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Forward_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_kernel_assertion( current != _end);
        return *current;
    }
    CGAL_Forward_const_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_kernel_assertion( current != _end);
        ++current;
        if ( current == _end)
            current = _begin;
        return *this;
    }
    CGAL_Forward_const_circulator_from_iterator< I, T, Size, Dist>
    operator++(int) {
        CGAL_Forward_const_circulator_from_iterator< I, T, Size, Dist>
            tmp= *this;
        ++*this;
        return tmp;
    }
    
 
    #ifdef __GNUG__
    friend inline  Dist* distance_type(
        const
    CGAL_Forward_const_circulator_from_iterator<I, T, Size, Dist>&) {
        return ( Dist*)(0);
    }
    friend inline T* value_type(
        const
    CGAL_Forward_const_circulator_from_iterator<I, T, Size, Dist>&) {
        return (T*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_const_circulator_from_iterator<I, T, Size, Dist>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_const_circulator_from_iterator<I, T, Size, Dist>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};


template < class  I, class  T, class   Size, class  Dist >
class CGAL_Bidirectional_circulator_from_iterator
    : public CGAL_Bidirectional_circulator_base<T,Dist> {
private:
    I _begin;
    I _end;
    I current;
public:
//
// CREATION

    CGAL_Bidirectional_circulator_from_iterator()
        : _begin(I()), _end(I()), current(I()) {}

    CGAL_Bidirectional_circulator_from_iterator( const I& begin,
                                                const I& end)
        : _begin( begin), _end( end), current( begin) {}

    CGAL_Bidirectional_circulator_from_iterator(
        const CGAL_Bidirectional_circulator_from_iterator<I,T,Size,Dist>& c)
        : _begin( c._begin), _end( c._end), current( c.current) {}
//
// TYPES

    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        CGAL_kernel_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Bidirectional_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        CGAL_kernel_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Bidirectional_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_kernel_assertion( current != _end);
        return *current;
    }
    CGAL_Bidirectional_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_kernel_assertion( current != _end);
        ++current;
        if ( current == _end)
            current = _begin;
        return *this;
    }
    CGAL_Bidirectional_circulator_from_iterator< I, T, Size, Dist>
    operator++(int) {
        CGAL_Bidirectional_circulator_from_iterator< I, T, Size,
                Dist> tmp= *this;
        ++*this;
        return tmp;
    }

    CGAL_Bidirectional_circulator_from_iterator< I, T, Size, Dist>&
    operator--() {
        CGAL_kernel_assertion( current != _end);
        if ( current == _begin)
            current = _end;
        --current;
        return *this;
    }
    CGAL_Bidirectional_circulator_from_iterator< I, T, Size, Dist>
    operator--(int) {
        CGAL_Bidirectional_circulator_from_iterator< I, T, Size,
               Dist> tmp = *this;
        --*this;
        return tmp;
    }
    
 
    #ifdef __GNUG__
    friend inline  Dist* distance_type(
        const
    CGAL_Bidirectional_circulator_from_iterator<I, T, Size, Dist>&) {
        return ( Dist*)(0);
    }
    friend inline T* value_type(
        const
    CGAL_Bidirectional_circulator_from_iterator<I, T, Size, Dist>&) {
        return (T*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_circulator_from_iterator<I, T, Size, Dist>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_circulator_from_iterator<I, T, Size, Dist>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};

template < class  I, class  T, class   Size, class  Dist >
class CGAL_Bidirectional_const_circulator_from_iterator
    : public CGAL_Bidirectional_circulator_base<T,Dist> {
private:
    I _begin;
    I _end;
    I current;
public:
//
// CREATION

    CGAL_Bidirectional_const_circulator_from_iterator()
        : _begin(I()), _end(I()), current(I()) {}

    CGAL_Bidirectional_const_circulator_from_iterator( const I& begin,
                                                      const I& end)
        : _begin( begin), _end( end), current( begin) {}

    CGAL_Bidirectional_const_circulator_from_iterator(
        const CGAL_Bidirectional_const_circulator_from_iterator<
            I,T,Size,Dist>& c)
        : _begin( c._begin), _end( c._end), current( c.current) {}
//
// TYPES

    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        CGAL_kernel_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Bidirectional_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        CGAL_kernel_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Bidirectional_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_kernel_assertion( current != _end);
        return *current;
    }
    CGAL_Bidirectional_const_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_kernel_assertion( current != _end);
        ++current;
        if ( current == _end)
            current = _begin;
        return *this;
    }
    CGAL_Bidirectional_const_circulator_from_iterator< I, T, Size, Dist>
    operator++(int) {
        CGAL_Bidirectional_const_circulator_from_iterator< I, T, Size,
                Dist> tmp= *this;
        ++*this;
        return tmp;
    }

    CGAL_Bidirectional_const_circulator_from_iterator< I, T, Size, Dist>&
    operator--() {
        CGAL_kernel_assertion( current != _end);
        if ( current == _begin)
            current = _end;
        --current;
        return *this;
    }
    CGAL_Bidirectional_const_circulator_from_iterator< I, T, Size, Dist>
    operator--(int) {
        CGAL_Bidirectional_const_circulator_from_iterator< I, T, Size,
               Dist> tmp = *this;
        --*this;
        return tmp;
    }
    
 
    #ifdef __GNUG__
    friend inline  Dist* distance_type(
        const
    CGAL_Bidirectional_const_circulator_from_iterator<I, T, Size, Dist>&) {
        return ( Dist*)(0);
    }
    friend inline T* value_type(
        const
    CGAL_Bidirectional_const_circulator_from_iterator<I, T, Size, Dist>&) {
        return (T*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_const_circulator_from_iterator<I, T, Size, Dist>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_const_circulator_from_iterator<I, T, Size, Dist>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};

template < class  I, class  T, class   Size, class  Dist >
class CGAL_Random_access_circulator_from_iterator
    : public CGAL_Random_access_circulator_base<T,Dist> {
private:
    I _begin;
    I _end;
    I current;
public:
//
// CREATION

    CGAL_Random_access_circulator_from_iterator()
        : _begin(I()), _end(I()), current(I()) {}

    CGAL_Random_access_circulator_from_iterator( const I& begin,
                                                const I& end)
        : _begin( begin), _end( end), current( begin) {}

    CGAL_Random_access_circulator_from_iterator(
        const CGAL_Random_access_circulator_from_iterator<I,T,Size,Dist>& c)
        : _begin( c._begin), _end( c._end), current( c.current) {}
//
// TYPES

    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        CGAL_kernel_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Random_access_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        CGAL_kernel_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Random_access_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_kernel_assertion( current != _end);
        return *current;
    }
    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_kernel_assertion( current != _end);
        ++current;
        if ( current == _end)
            current = _begin;
        return *this;
    }
    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>
    operator++(int) {
        CGAL_Random_access_circulator_from_iterator< I, T, Size,
                Dist> tmp= *this;
        ++*this;
        return tmp;
    }

    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>&
    operator--() {
        CGAL_kernel_assertion( current != _end);
        if ( current == _begin)
            current = _end;
        --current;
        return *this;
    }
    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>
    operator--(int) {
        CGAL_Random_access_circulator_from_iterator< I, T, Size,
               Dist> tmp = *this;
        --*this;
        return tmp;
    }

    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>&
    operator+=( Dist n);

    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>
    operator+( Dist n) const {
        CGAL_Random_access_circulator_from_iterator< I, T, Size,
                 Dist> tmp = *this;
        return tmp += n;
    }
    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>&
    operator-=( Dist n) {
        return operator+=( -n);
    }
    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>
    operator-( Dist n) const {
        CGAL_Random_access_circulator_from_iterator< I, T, Size,
                  Dist> tmp = *this;
        return tmp += -n;
    }
    Dist
    operator-( const CGAL_Random_access_circulator_from_iterator<
                     I, T, Size, Dist>& i) const {
        CGAL_kernel_assertion((_begin == i._begin) && (_end == i._end));
        return current - i.current;
    }
    reference  operator[](Dist n) const {
        CGAL_Random_access_circulator_from_iterator< I, T, Size,
                         Dist> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    
 
    #ifdef __GNUG__
    friend inline  Dist* distance_type(
        const
    CGAL_Random_access_circulator_from_iterator<I, T, Size, Dist>&) {
        return ( Dist*)(0);
    }
    friend inline T* value_type(
        const
    CGAL_Random_access_circulator_from_iterator<I, T, Size, Dist>&) {
        return (T*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(
    CGAL_Random_access_circulator_from_iterator<I, T, Size, Dist>) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Random_access_circulator_from_iterator<I, T, Size, Dist>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};

template < class I, class  T, class Size, class Dist> inline
CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>
operator+( Dist n, const
    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>& circ) {
    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>
        tmp = circ;
    return tmp += n;
}

template < class I, class  T, class Size, class Dist>
CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>&
CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>::
operator+=( Dist n) {
    CGAL_kernel_assertion( current != _end);

    Dist i    = current - _begin;
    Dist size = _end    - _begin;
    CGAL_kernel_assertion( i    >= 0);
    CGAL_kernel_assertion( size >= 0);
    i = CGAL_non_negative_mod( i + n, size);
    CGAL_kernel_assertion( i >= 0);
    CGAL_kernel_assertion( i < size);
    current = _begin + i;
    return *this;
}


template < class  I, class  T, class   Size, class  Dist >
class CGAL_Random_access_const_circulator_from_iterator
    : public CGAL_Random_access_circulator_base<T,Dist> {
private:
    I _begin;
    I _end;
    I current;
public:
//
// CREATION

    CGAL_Random_access_const_circulator_from_iterator()
        : _begin(I()), _end(I()), current(I()) {}

    CGAL_Random_access_const_circulator_from_iterator( const I& begin,
                                                      const I& end)
        : _begin( begin), _end( end), current( begin) {}

    CGAL_Random_access_const_circulator_from_iterator(
        const CGAL_Random_access_const_circulator_from_iterator<
            I,T,Size,Dist>& c)
        : _begin( c._begin), _end( c._end), current( c.current) {}
//
// TYPES

    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      distance_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_kernel_assertion( p == NULL);
        CGAL_kernel_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Random_access_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        CGAL_kernel_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Random_access_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_kernel_assertion( current != _end);
        return *current;
    }
    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_kernel_assertion( current != _end);
        ++current;
        if ( current == _end)
            current = _begin;
        return *this;
    }
    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>
    operator++(int) {
        CGAL_Random_access_const_circulator_from_iterator< I, T, Size,
                Dist> tmp= *this;
        ++*this;
        return tmp;
    }

    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>&
    operator--() {
        CGAL_kernel_assertion( current != _end);
        if ( current == _begin)
            current = _end;
        --current;
        return *this;
    }
    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>
    operator--(int) {
        CGAL_Random_access_const_circulator_from_iterator< I, T, Size,
               Dist> tmp = *this;
        --*this;
        return tmp;
    }

    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>&
    operator+=( Dist n);

    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>
    operator+( Dist n) const {
        CGAL_Random_access_const_circulator_from_iterator< I, T, Size,
                 Dist> tmp = *this;
        return tmp += n;
    }
    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>&
    operator-=( Dist n) {
        return operator+=( -n);
    }
    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>
    operator-( Dist n) const {
        CGAL_Random_access_const_circulator_from_iterator< I, T, Size,
                  Dist> tmp = *this;
        return tmp += -n;
    }
    Dist
    operator-( const CGAL_Random_access_const_circulator_from_iterator<
                     I, T, Size, Dist>& i) const {
        CGAL_kernel_assertion((_begin == i._begin) && (_end == i._end));
        return current - i.current;
    }
    const_reference  operator[](Dist n) const {
        CGAL_Random_access_const_circulator_from_iterator< I, T, Size,
                         Dist> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    
 
    #ifdef __GNUG__
    friend inline  Dist* distance_type(
        const
    CGAL_Random_access_const_circulator_from_iterator<I, T, Size, Dist>&) {
        return ( Dist*)(0);
    }
    friend inline T* value_type(
        const
    CGAL_Random_access_const_circulator_from_iterator<I, T, Size, Dist>&) {
        return (T*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(
    CGAL_Random_access_const_circulator_from_iterator<I, T, Size, Dist>) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Random_access_const_circulator_from_iterator<I, T, Size, Dist>) {
        return CGAL_Circulator_tag();
    }
    #endif
 
          
};

template < class I, class  T, class Size, class Dist> inline
CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>
operator+( Dist n, const
    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>&
    circ) {
    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>
        tmp = circ;
    return tmp += n;
}

template < class I, class  T, class Size, class Dist>
CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>&
CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>::
operator+=( Dist n) {
    CGAL_kernel_assertion( current != _end);

    Dist i    = current - _begin;
    Dist size = _end    - _begin;
    CGAL_kernel_assertion( i    >= 0);
    CGAL_kernel_assertion( size >= 0);
    i = CGAL_non_negative_mod( i + n, size);
    CGAL_kernel_assertion( i >= 0);
    CGAL_kernel_assertion( i < size);
    current = _begin + i;
    return *this;
}
 
 

#endif // CGAL_CIRCULATOR_H //
// EOF //
