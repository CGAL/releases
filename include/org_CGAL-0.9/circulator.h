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

                                 
// | $Revision: 1.9 $
// | $Date: 1997/06/24 06:22:17 $
// | 1997   Lutz Kettner 

#ifndef CGAL_CIRCULATOR_H
#define CGAL_CIRCULATOR_H 1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef _STDDEF_H
#include <stddef.h>
#endif
#ifndef ITERATOR_H
#include <iterator.h>
#endif

// #line 133 "circulator.any"
// CGAL defined Tags.
#ifdef CGAL_STL_HP
#define CGAL__CIRC_STL_HP
#endif
#ifdef CGAL_STL_SGI_WWW
#define CGAL__CIRC_STL_SGI_JUNE_1997
#endif
#ifdef CGAL_STL_SGI_WWW_OLD
#define CGAL__CIRC_STL_SGI_WWW_1996
#endif
#ifdef CGAL_STL_SGI_CC
#define CGAL__CIRC_STL_SGI_CC_1996
#endif
#ifdef CGAL_STL_GCC
#define CGAL__CIRC_STL_GCC
#endif
#ifdef CGAL_STL_WITH_ITERATOR_TRAITS
#define CGAL__CIRC_STL_ITERATOR_TRAITS
#endif
#ifdef CGAL_STL_UNKNOWN
// No idea what to do. No explicit tag support.
#endif

#ifndef CGAL__CIRC_STL_HP
#ifndef CGAL__CIRC_STL_SGI_JUNE_1997
#ifndef CGAL__CIRC_STL_SGI_WWW_1996
#ifndef CGAL__CIRC_STL_SGI_CC_1996
#ifndef CGAL__CIRC_STL_GCC
#ifndef CGAL__CIRC_STL_ITERATOR_TRAITS
#ifndef CGAL_STL_UNKNOWN

   // Try to figure out what STL is used.
#  ifdef __GNUG__
#      define CGAL__CIRC_STL_GCC
#  else // __GNUG__ //
       // Try to distinguish between HP and newest SGI STL (June 1997).
#      include <list.h>
#      ifdef LIST_H
#          ifdef  __sgi
               // Assume that SGI don't use HP STL any more. Then LIST_H
               // indicates an earlier SGI STL delivered with the C++
               // compiler release 7.1.
#              define CGAL__CIRC_STL_SGI_CC_1996
#          else  // __sgi //
               // On non SGI systems assume HP STL as default.
#              define CGAL__CIRC_STL_HP
#          endif // __sgi //
#      else  // LIST_H //
#          ifdef __SGI_STL_LIST_H
               // No else part. If its not the SGI STL, we don't know what
               // it is. Check if partial specialization and iterator
               // traits are supported.
#              ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
#                  define CGAL__CIRC_STL_ITERATOR_TRAITS
#              else  // __STL_CLASS_PARTIAL_SPECIALIZATION //
#                  define CGAL__CIRC_STL_SGI_JUNE_1997
#              endif // __STL_CLASS_PARTIAL_SPECIALIZATION //
#          endif // __SGI_STL_LIST_H //
#      endif // LIST_H //
#  endif // __GNUG__ //

#endif
#endif
#endif
#endif
#endif
#endif
#endif

// Encapsulate GNU g++ 2.7 workarounds hoping they vanishes with 2.8.
#  ifdef __GNUG__
#     if __GNUC__ == 2 && __GNUC_MINOR__ == 7
#         define  CGAL__CIRC_GNUG_27
#     endif
#  endif // __GNUG__ //

// Encapsulate __SUNPRO_CC 4.1 workarounds hoping they vanishes once.
#  ifdef __SUNPRO_CC
#     define  CGAL__CIRC_SUNPRO_41
#  endif // __SUNPRO_CC //    
// #line 73 "circulator.any"
                              

// #line 15 "gnu_workaround.any"
#ifdef __GNUG__
#define CGAL_NULL_TYPE const void*
#else // __GNUG__ //
#define CGAL_NULL_TYPE int
#endif // __GNUG__ //
// #line 75 "circulator.any"
                     
// #line 28 "gnu_workaround.any"
#ifdef __GNUG__
#define CGAL_MEMBER_PTR_CONST
#else
#define CGAL_MEMBER_PTR_CONST const
#endif
// #line 76 "circulator.any"
      

// #line 220 "circulator.any"
struct CGAL_Circulator_tag {};                   // any circulator.
struct CGAL_Iterator_tag {};                     // any iterator.

struct CGAL_Forward_circulator_tag       : public forward_iterator_tag {};
struct CGAL_Bidirectional_circulator_tag : public bidirectional_iterator_tag {};
struct CGAL_Random_access_circulator_tag : public random_access_iterator_tag {};
// #line 78 "circulator.any"
                                                                               
// #line 240 "circulator.any"
template <class T, class Dist>
struct CGAL_Forward_circulator_base : public forward_iterator<T,Dist> {
    typedef CGAL_Forward_circulator_tag iterator_category;
};
template <class T, class Dist>
struct CGAL_Bidirectional_circulator_base
: public bidirectional_iterator<T,Dist> {
    typedef CGAL_Bidirectional_circulator_tag iterator_category;
};
template <class T, class Dist>
struct CGAL_Random_access_circulator_base
: public random_access_iterator<T,Dist> {
    typedef CGAL_Random_access_circulator_tag iterator_category;
};

// variant base classes
// ---------------------
template <class T, class Dist>
class CGAL_Forward_circulator_ptrbase         // forward circulator.
{
    protected:
        void* _ptr;
    public:
        typedef CGAL_Forward_circulator_tag  iterator_category;
        typedef T                           value_type;
        typedef Dist                        difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        CGAL_Forward_circulator_ptrbase()        : _ptr(NULL) {}
        CGAL_Forward_circulator_ptrbase(void* p) : _ptr(p) {}
        CGAL_Forward_circulator_ptrbase(
            const CGAL_Forward_circulator_ptrbase<T,Dist>& b) : _ptr(b._ptr) {}
};
template <class T, class Dist>
class CGAL_Bidirectional_circulator_ptrbase   // bidirectional circulator.
{
    protected:
        void* _ptr;
    public:
        typedef CGAL_Bidirectional_circulator_tag  iterator_category;
        typedef T                           value_type;
        typedef Dist                        difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        CGAL_Bidirectional_circulator_ptrbase()        : _ptr(NULL) {}
        CGAL_Bidirectional_circulator_ptrbase(void* p) : _ptr(p) {}
        CGAL_Bidirectional_circulator_ptrbase(
            const CGAL_Bidirectional_circulator_ptrbase<T,Dist>& b)
                                                      : _ptr(b._ptr) {}
};
template <class T, class Dist>
class CGAL_Random_access_circulator_ptrbase   // random access circulator.
{
    protected:
        void* _ptr;
    public:
        typedef CGAL_Random_access_circulator_tag iterator_category;
        typedef T                           value_type;
        typedef Dist                        difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        CGAL_Random_access_circulator_ptrbase()        : _ptr(NULL) {}
        CGAL_Random_access_circulator_ptrbase(void* p) : _ptr(p) {}
        CGAL_Random_access_circulator_ptrbase(
            const CGAL_Random_access_circulator_ptrbase<T,Dist>& b)
                                                      : _ptr(b._ptr) {}
};
// #line 79 "circulator.any"
  
#ifdef CGAL__CIRC_STL_ITERATOR_TRAITS
// #line 310 "circulator.any"
template <class C>
struct CGAL__Circulator_traits {
    typedef  CGAL_Iterator_tag  category;
};
struct CGAL__Circulator_traits<CGAL_Forward_circulator_tag> {
    typedef  CGAL_Circulator_tag  category;
};
struct CGAL__Circulator_traits<CGAL_Bidirectional_circulator_tag> {
    typedef  CGAL_Circulator_tag  category;
};
struct CGAL__Circulator_traits<CGAL_Random_access_circulator_tag> {
    typedef  CGAL_Circulator_tag  category;
};

template <class C>
struct CGAL_Circulator_traits {
    typedef iterator_traits<C> traits;
    typedef traits::iterator_category iterator_category;
    typedef CGAL__Circulator_traits< iterator_category> C_traits;
    typedef C_traits::category category;
};

template <class C>
CGAL_Circulator_traits<C>::category
CGAL_query_circulator_or_iterator( const C&) {
    return CGAL_Circulator_traits<C>::category();
}

template <class C>
struct CGAL__Iterator_from_circulator_traits {
};
struct CGAL__Iterator_from_circulator_traits< CGAL_Forward_circulator_tag> {
    typedef  forward_iterater_tag  iterator_category;
};
struct CGAL__Iterator_from_circulator_traits<
    CGAL_Bidirectional_circulator_tag> {
    typedef  bidirectional_iterater_tag  iterator_category;
};
struct CGAL__Iterator_from_circulator_traits<
    CGAL_Random_access_circulator_tag> {
    typedef  random_access_iterater_tag  iterator_category;
};

template <class C>
struct CGAL__Circulator_from_iterator_traits {
};
struct CGAL__Circulator_from_iterator_traits< forward_iterater_tag> {
    typedef  CGAL_Forward_circulator_tag  iterator_category;
};
struct CGAL__Circulator_from_iterator_traits< bidirectional_iterater_tag> {
    typedef  CGAL_Bidirectional_circulator_tag  iterator_category;
};
struct CGAL__Circulator_from_iterator_traits< random_access_iterater_tag> {
    typedef  CGAL_Random_access_circulator_tag  iterator_category;
};    
// #line 81 "circulator.any"
      
#else  // CGAL__CIRC_STL_ITERATOR_TRAITS //
// #line 368 "circulator.any"
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
// #line 83 "circulator.any"
 
#endif // CGAL__CIRC_STL_ITERATOR_TRAITS //
// #line 445 "circulator.any"
// variant base classes
// --------------------
// The normal base classes are handled automatically through inheritance.

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

#if defined(CGAL__CIRC_GNUG_27) || defined(CGAL__CIRC_SUNPRO_41)
// Not necessary with __SUNPRO 4.2.
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
#endif  // CGAL__CIRC_GNUG_27 || CGAL__CIRC_SUNPRO_41 //    
// #line 85 "circulator.any"
                                                          
// #line 486 "circulator.any"
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

#if defined(CGAL__CIRC_GNUG_27) || defined(CGAL__CIRC_SUNPRO_41)
// Not necessary with __SUNPRO 4.2.
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
#endif  // CGAL__CIRC_GNUG_27 || CGAL__CIRC_SUNPRO_41 //    
// #line 86 "circulator.any"
                                                          
// #line 6349 "circulator.any"
#  ifndef CGAL__CIRC_STL_ITERATOR_TRAITS
#      ifdef CGAL__CIRC_STL_SGI_JUNE_1997
// #line 6363 "circulator.any"
#ifndef __STL_NON_TYPE_TMPL_PARAM_BUG
template <class T, class Ref, size_t BufSiz>
struct __deque_iterator;
template <class T, class Ref, size_t BufSiz> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __deque_iterator<T, Ref, BufSiz>&){
    return CGAL_Iterator_tag();
}
#else /* __STL_NON_TYPE_TMPL_PARAM_BUG */
template <class T, class Ref>
struct __deque_iterator;
template <class T, class Ref> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __deque_iterator<T, Ref>&){
    return CGAL_Iterator_tag();
}
#endif /* __STL_NON_TYPE_TMPL_PARAM_BUG */

template <class Value, class Key, class HashFcn,
          class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_iterator;
template< class V, class K, class HF, class ExK, class EqK, class All>
inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
        const __hashtable_iterator<V, K, HF, ExK, EqK, All>&){
    return CGAL_Iterator_tag();
}
template <class Value, class Key, class HashFcn,
          class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_const_iterator;
template< class V, class K, class HF, class ExK, class EqK, class All>
inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
        const __hashtable_const_iterator<V, K, HF, ExK, EqK, All>&){
    return CGAL_Iterator_tag();
}

template<class T, class Ref>
struct __list_iterator;
template< class T, class Ref> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __list_iterator<T,Ref>&){
    return CGAL_Iterator_tag();
}

template<class CharT, class Alloc> class __rope_iterator;
template< class T, class Alloc> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __rope_iterator<T,Alloc>&){
    return CGAL_Iterator_tag();
}
template<class CharT, class Alloc> class __rope_const_iterator;
template< class T, class Alloc> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __rope_const_iterator<T,Alloc>&){
    return CGAL_Iterator_tag();
}

template <class T, class Ref>
struct __slist_iterator;
template< class T, class Ref> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __slist_iterator<T,Ref>&){
    return CGAL_Iterator_tag();
}

template <class Value, class Ref>
struct __rb_tree_iterator;
template< class V, class Ref> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __rb_tree_iterator<V,Ref>&) {
    return CGAL_Iterator_tag();
}
// #line 6351 "circulator.any"
 
#      endif // CGAL__CIRC_STL_SGI_JUNE_1997 //
#      ifdef CGAL__CIRC_STL_SGI_WWW_1996
// #line 6441 "circulator.any"
template <class T>
struct __deque_iterator;
template <class T> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __deque_iterator<T>&){
    return CGAL_Iterator_tag();
}
template <class T>
struct __deque_const_iterator;
template <class T> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __deque_const_iterator<T>&){
    return CGAL_Iterator_tag();
}

template <class Value, class Key, class HashFcn,
          class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_iterator;
template< class V, class K, class HF, class ExK, class EqK, class All>
inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
        const __hashtable_iterator<V, K, HF, ExK, EqK, All>&){
    return CGAL_Iterator_tag();
}
template <class Value, class Key, class HashFcn,
          class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_const_iterator;
template< class V, class K, class HF, class ExK, class EqK, class All>
inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
        const __hashtable_const_iterator<V, K, HF, ExK, EqK, All>&){
    return CGAL_Iterator_tag();
}

template<class T>
struct __list_iterator;
template< class T> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __list_iterator<T>&){
    return CGAL_Iterator_tag();
}
template<class T>
struct __list_const_iterator;
template< class T> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __list_const_iterator<T>&){
    return CGAL_Iterator_tag();
}

template <class Value>
struct __rb_tree_iterator;
template< class V> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __rb_tree_iterator<V>&) {
    return CGAL_Iterator_tag();
}
template <class Value>
struct __rb_tree_const_iterator;
template< class V> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator( const __rb_tree_const_iterator<V>&) {
    return CGAL_Iterator_tag();
}
// #line 6354 "circulator.any"
 
#      endif // CGAL__CIRC_STL_SGI_WWW_1996 //
#      ifdef CGAL__CIRC_STL_SGI_CC_1996
// #line 6509 "circulator.any"
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

#if defined(SGI_STL_HASHTABLE_H)
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

#if defined(TREE_H)
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
// #line 6357 "circulator.any"
                   
#      endif // CGAL__CIRC_STL_SGI_CC_1996 //
#  endif // CGAL__CIRC_STL_ITERATOR_TRAITS //
// #line 87 "circulator.any"
                                            
// #line 541 "circulator.any"
/* A function that asserts a specific compile time tag */
/* forcing its two arguments to have equal type.       */
/* It is encapsulated with #ifdef since it will be defined also elsewhere. */
#ifndef CGAL_ASSERT_COMPILE_TIME_TAG
#define CGAL_ASSERT_COMPILE_TIME_TAG 1
template< class Tag>
inline void CGAL_assertion_compile_time_tag( Tag, Tag) {}
#endif

template <class C> inline
void CGAL_assertion_circulator( const C &c) {
    CGAL_assertion_compile_time_tag( CGAL_Circulator_tag(),
                                CGAL_query_circulator_or_iterator( c));
}
template <class I> inline
void CGAL_assertion_iterator( const I &i) {
    CGAL_assertion_compile_time_tag( CGAL_Iterator_tag(),
                                CGAL_query_circulator_or_iterator( i));
}
template <class I> inline
void CGAL_assertion_input_category( const I &i) {
    CGAL_assertion_compile_time_tag( input_iterator_tag(),
                                iterator_category( i));
}
template <class I> inline
void CGAL_assertion_output_category( const I &i) {
    CGAL_assertion_compile_time_tag( output_iterator_tag(),
                                iterator_category( i));
}
template <class IC> inline
void CGAL_assertion_forward_category( const IC &ic) {
    CGAL_assertion_compile_time_tag( forward_iterator_tag(),
                                iterator_category( ic));
}
template <class IC> inline
void CGAL_assertion_bidirectional_category( const IC &ic) {
    CGAL_assertion_compile_time_tag( bidirectional_iterator_tag(),
                                iterator_category( ic));
}
template <class IC> inline
void CGAL_assertion_random_access_category( const IC &ic) {
    CGAL_assertion_compile_time_tag( random_access_iterator_tag(),
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
void CGAL_assertion_is_at_least_input_category( const I& i) {
     CGAL__Has_to_be_at_least(input_iterator_tag(), iterator_category(i));
}
template <class I> inline
void CGAL_assertion_is_at_least_output_category( const I& i) {
     CGAL__Has_to_be_at_least(output_iterator_tag(), iterator_category(i));
}
template <class IC> inline
void CGAL_assertion_is_at_least_forward_category( const IC& ic) {
     CGAL__Has_to_be_at_least(forward_iterator_tag(), iterator_category(ic));
}
template <class IC> inline
void CGAL_assertion_is_at_least_bidirectional_category( const IC& ic) {
     CGAL__Has_to_be_at_least(bidirectional_iterator_tag(),
                             iterator_category(ic)) ;
}
template <class IC> inline
void CGAL_assertion_is_at_least_random_access_category( const IC& ic) {
     CGAL__Has_to_be_at_least(random_access_iterator_tag(),
                             iterator_category(ic));
}
// #line 88 "circulator.any"
 

// #line 897 "circulator.any"
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
void CGAL_assertion_circulator_or_iterator( const IC &ic){
    CGAL_assertion_compile_time_tag(
        CGAL_Circulator_or_iterator_tag(),
        CGAL_check_circulator_or_iterator(
            CGAL_query_circulator_or_iterator( ic)
        )
    );
}

#define CGAL_For_all( ic1, ic2) \
    for ( bool CGAL__circ_loop_flag = ! CGAL_is_empty_range( ic1, ic2); \
          CGAL__circ_loop_flag; \
          CGAL__circ_loop_flag = ((++ic1) != (ic2)) )

#define CGAL_For_all_backwards( ic1, ic2) \
    for ( bool CGAL__circ_loop_flag = ! CGAL_is_empty_range( ic1, ic2); \
          CGAL__circ_loop_flag; \
          CGAL__circ_loop_flag = ((ic1) != (--ic2)) )

// Note: these macros are superfluous now. See the more natural macros above.
// (Note that the macros below avoids problems with dangling else's.)
#define CGAL__For_all_old( ic1, ic2, body) \
    if ( CGAL_is_empty_range( ic1, ic2)); \
    else { \
        do \
            body \
        while ((++ic1) != (ic2)); \
    }
#define CGAL__For_all_backwards_old( ic1, ic2, body) \
    if ( CGAL_is_empty_range( ic1, ic2)); \
    else { \
        do \
            body \
        while ((ic1) != (--ic2)); \
    }
// #line 90 "circulator.any"
     

// #line 771 "circulator.any"
template <class C> inline
size_t
CGAL__min_circulator_size(const C& c) {
    CGAL_assertion_circulator(c);
    CGAL_assertion_random_access_category(c);
    size_t n = 0;
    if ( c != NULL) {
        n = (c-1) - c + 1;
        CGAL_assertion(n > 0);
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
    return CGAL__min_circulator_size( c.min_circulator());
}

template <class C> inline
size_t CGAL_circulator_size(const C& c) {
    return CGAL__circulator_size( c, iterator_category(c));
}
// #line 824 "circulator.any"
template<class I, class U> inline
I CGAL_non_negative_mod(I n, U m) {
    CGAL_assertion( m > 0);
    #if (-1 % 3) > 0
        n = n % m;
    #else
    if (n < 0)
        n = - (( - n - 1) % m) + m - 1;
    else
        n = n % m;
    #endif
    CGAL_assertion( n >= 0);
    return n;
}
// #line 92 "circulator.any"

// #line 1014 "circulator.any"
template < class  C>
class CGAL_Forward_iterator_from_circulator
    : public forward_iterator< C::value_type, C::difference_type> {
private:
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// TYPES

    typedef  C  Circulator;

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
        CGAL_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=( const CGAL_Forward_iterator_from_circulator<C>& i)
    const {
        return !(*this == i);
    }
    C::reference  operator*() const {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
        return *current;
    }
    CGAL_Forward_iterator_from_circulator<C>&
    operator++() {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
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
    Circulator  current_circulator() const { return current;}
};

template < class  C>
class CGAL_Forward_const_iterator_from_circulator
    : public forward_iterator< C::value_type, C::difference_type> {
private:
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// TYPES

    typedef  C  Circulator;

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
        CGAL_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=(
            const CGAL_Forward_const_iterator_from_circulator<C>& i) const {
        return !(*this == i);
    }
    C::const_reference  operator*() const {
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
        return *current;
    }
    CGAL_Forward_const_iterator_from_circulator<C>&
    operator++() {
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
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
    Circulator  current_circulator() const { return current;}
};

template < class  C>
class CGAL_Bidirectional_iterator_from_circulator
    : public bidirectional_iterator< C::value_type, C::difference_type> {
private:
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// TYPES

    typedef  C  Circulator;

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
        CGAL_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=(
            const CGAL_Bidirectional_iterator_from_circulator<C>& i) const {
        return !(*this == i);
    }
    C::reference  operator*() const {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
        return *current;
    }
    CGAL_Bidirectional_iterator_from_circulator<C>&
    operator++() {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
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
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
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
    Circulator  current_circulator() const { return current;}
};

template < class  C>
class CGAL_Bidirectional_const_iterator_from_circulator
    : public bidirectional_iterator< C::value_type, C::difference_type> {
private:
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// TYPES

    typedef  C  Circulator;

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
        CGAL_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=( const
            CGAL_Bidirectional_const_iterator_from_circulator<C>& i) const {
        return !(*this == i);
    }
    C::const_reference  operator*() const {
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
        return *current;
    }
    CGAL_Bidirectional_const_iterator_from_circulator<C>&
    operator++() {
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
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
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
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
    Circulator  current_circulator() const { return current;}
};

template < class  C>
class CGAL_Random_access_iterator_from_circulator
    : public random_access_iterator< C::value_type, C::difference_type> {
private:
    // The anchor is normalized to be a minimal circulator.
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// TYPES

    typedef  C  Circulator;

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
        CGAL_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=(
            const CGAL_Random_access_iterator_from_circulator<C>& i) const {
        return !(*this == i);
    }
    C::reference  operator*() const {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
        return *current;
    }
    CGAL_Random_access_iterator_from_circulator<C>&
    operator++() {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
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
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
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
    operator+=( C::difference_type n) {
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
        if ( n < 0 && current == *anchor)  // We are leaving the anchor.
            --winding;
        current += n;
        if ( n > 0 && current == *anchor)  // Back again at the anchor.
            ++winding;
        return *this;
    }
    CGAL_Random_access_iterator_from_circulator<C>
    operator+( C::difference_type n) const {
        CGAL_Random_access_iterator_from_circulator<C> tmp = *this;
        return tmp += n;
    }
    CGAL_Random_access_iterator_from_circulator<C>&
    operator-=( C::difference_type n) {
        return operator+=( -n);
    }
    CGAL_Random_access_iterator_from_circulator<C>
    operator-( C::difference_type n) const {
        CGAL_Random_access_iterator_from_circulator<C> tmp = *this;
        return tmp += -n;
    }
    #if !defined(CGAL__CIRC_GNUG_27) && !defined(CGAL__CIRC_SUNPRO_41)
    C::difference_type
    operator-(
            const CGAL_Random_access_iterator_from_circulator<C>& i) const;
    #else
    C::difference_type
    operator-(
            const CGAL_Random_access_iterator_from_circulator<C>& i) const {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
        CGAL_assertion( anchor  == i.anchor);
        if ( winding != i.winding) {
            C::difference_type s = CGAL__min_circulator_size( *anchor);
            return   (current - *anchor) - (i.current - *anchor)
                   + s * (winding - i.winding);
        }
        return (current - *anchor) - (i.current - *anchor);
    }
    #endif

    C::reference  operator[](C::difference_type n) const {
        CGAL_Random_access_iterator_from_circulator<C> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    bool
    operator<( const
            CGAL_Random_access_iterator_from_circulator<C>& i) const {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
        CGAL_assertion( anchor  == i.anchor);
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
    Circulator  current_circulator() const { return current;}
};

template < class Dist, class  C>
CGAL_Random_access_iterator_from_circulator<C>
operator+( Dist n,
           const CGAL_Random_access_iterator_from_circulator<C>& circ) {
    CGAL_Random_access_iterator_from_circulator<C> tmp = circ;
    return tmp += n;
}

#if !defined(CGAL__CIRC_GNUG_27) && !defined(CGAL__CIRC_SUNPRO_41)
template < class  C>
C::difference_type
CGAL_Random_access_iterator_from_circulator<C>::
operator-( const CGAL_Random_access_iterator_from_circulator<C>& i) const {
    CGAL_assertion( anchor  != NULL);
    CGAL_assertion( current != NULL);
    CGAL_assertion( anchor  == i.anchor);
    if ( winding != i.winding) {
        C::difference_type s = CGAL__min_circulator_size( *anchor);
        return   (current - *anchor) - (i.current - *anchor)
               + s * (winding - i.winding);
    }
    return (current - *anchor) - (i.current - *anchor);
}
#endif


template < class  C>
class CGAL_Random_access_const_iterator_from_circulator
    : public random_access_iterator< C::value_type, C::difference_type> {
private:
    // The anchor is normalized to be a minimal circulator.
    const C*  anchor;
    C         current;
    int       winding;
public:
//
// TYPES

    typedef  C  Circulator;

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
        CGAL_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
        return !(*this == i);
    }
    C::const_reference  operator*() const {
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
        return *current;
    }
    CGAL_Random_access_const_iterator_from_circulator<C>&
    operator++() {
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
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
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
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
    operator+=( C::difference_type n) {
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
        if ( n < 0 && current == *anchor)  // We are leaving the anchor.
            --winding;
        current += n;
        if ( n > 0 && current == *anchor)  // Back again at the anchor.
            ++winding;
        return *this;
    }
    CGAL_Random_access_const_iterator_from_circulator<C>
    operator+( C::difference_type n) const {
        CGAL_Random_access_const_iterator_from_circulator<C> tmp = *this;
        return tmp += n;
    }
    CGAL_Random_access_const_iterator_from_circulator<C>&
    operator-=( C::difference_type n) {
        return operator+=( -n);
    }
    CGAL_Random_access_const_iterator_from_circulator<C>
    operator-( C::difference_type n) const {
        CGAL_Random_access_const_iterator_from_circulator<C> tmp = *this;
        return tmp += -n;
    }
    #if !defined(CGAL__CIRC_GNUG_27) && !defined(CGAL__CIRC_SUNPRO_41)
    C::difference_type
    operator-( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const;
    #else
    C::difference_type
    operator-( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
        CGAL_assertion( anchor  == i.anchor);
        if ( winding != i.winding) {
            C::difference_type s = CGAL__min_circulator_size( *anchor);
            return   (current - *anchor) - (i.current - *anchor)
                   + s * (winding - i.winding);
        }
        return (current - *anchor) - (i.current - *anchor);
    }
    #endif

    C::const_reference  operator[](C::difference_type n) const {
        CGAL_Random_access_const_iterator_from_circulator<C> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    bool
    operator<( const
            CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
        CGAL_assertion( anchor  == i.anchor);
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
    Circulator  current_circulator() const { return current;}
};

template < class Dist, class  C>
CGAL_Random_access_const_iterator_from_circulator<C>
operator+( Dist n, const
           CGAL_Random_access_const_iterator_from_circulator<C>& circ) {
    CGAL_Random_access_const_iterator_from_circulator<C> tmp = circ;
    return tmp += n;
}

#if !defined(CGAL__CIRC_GNUG_27) && !defined(CGAL__CIRC_SUNPRO_41)
template < class  C>
C::difference_type
CGAL_Random_access_const_iterator_from_circulator<C>::
operator-( const
        CGAL_Random_access_const_iterator_from_circulator<C>& i) const {
    CGAL_assertion( anchor  != NULL);
    CGAL_assertion( current != NULL);
    CGAL_assertion( anchor  == i.anchor);
    if ( winding != i.winding) {
        C::difference_type s = CGAL__min_circulator_size( *anchor);
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

typedef C  Circulator;
typedef CGAL_Forward_const_iterator_from_circulator<C>  const_iterator;
typedef CGAL_Forward_iterator_from_circulator<C>        iterator;

typedef C::value_type       value_type;
typedef C::reference        reference;
typedef C::const_reference  const_reference;
typedef C::size_type        size_type;
typedef C::difference_type    difference_type;

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
    
// #line 64 "gnu_workaround.any"
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
// #line 1728 "circulator.any"
          
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

typedef C  Circulator;
typedef CGAL_Bidirectional_iterator_from_circulator<C>       iterator;
typedef CGAL_Bidirectional_const_iterator_from_circulator<C> const_iterator;

typedef C::value_type       value_type;
typedef C::reference        reference;
typedef C::const_reference  const_reference;
typedef C::size_type        size_type;
typedef C::difference_type    difference_type;

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
    
// #line 64 "gnu_workaround.any"
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
// #line 1786 "circulator.any"
          
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
        : anchor(c.min_circulator()) {}
        // the resulting iterators will have a singular value if the
        // circulator `c' is singular.

    CGAL_Random_access_container_from_circulator(
        // The anchor is normalized to be a minimal circulator.
        const CGAL_Random_access_container_from_circulator<C>& i)
        : anchor(i.anchor.min_circulator()) {}
//
// TYPES

typedef C  Circulator;
typedef CGAL_Random_access_iterator_from_circulator<C>       iterator;
typedef CGAL_Random_access_const_iterator_from_circulator<C> const_iterator;

typedef C::value_type       value_type;
typedef C::reference        reference;
typedef C::const_reference  const_reference;
typedef C::size_type        size_type;
typedef C::difference_type    difference_type;

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
    
// #line 64 "gnu_workaround.any"
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
// #line 1847 "circulator.any"
          
};

#ifdef CGAL__CIRC_STL_ITERATOR_TRAITS

template < class  C, class Ref>
class CGAL_Iterator_from_circulator {
private:
    // The anchor is normalized to be a minimal circulator.
    const C*  anchor;
    C         current;
    int       winding;

    typedef  iterator_traits<C>                               _traits;
    typedef  typename  _traits::iterator_category             _Iter_cat;
    typedef  CGAL__Iterator_from_circulator_traits<_Iter_cat>  __traits;

public:
//
// TYPES

    typedef  C  Circulator;
    typedef typename __traits::iterator_category iterator_category
    typedef typename _traits::value_type         value_type;
    typedef typename _traits::difference_type    difference_type;
    typedef typename _traits::pointer            pointer;
    typedef typename _traits::reference          reference;

//
// CREATION

    CGAL_Iterator_from_circulator() : anchor(0), winding(0) {}

    CGAL_Iterator_from_circulator( const C* circ, int n)
        : anchor( circ), current( *circ), winding(n) {}

    CGAL_Iterator_from_circulator(
            const CGAL_Iterator_from_circulator<C,Ref>& c)
        : anchor(c.anchor), current(c.current), winding(c.winding) {}
//
// OPERATIONS

    bool operator==( const CGAL_Iterator_from_circulator<C,Ref>& i) const {
        CGAL_assertion( anchor == i.anchor);  // same anchor?
        return ( current == i.current) && ( winding == i.winding);
    }
    bool operator!=( const CGAL_Iterator_from_circulator<C,Ref>& i) const {
        return !(*this == i);
    }
    Ref  operator*() const {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
        return *current;
    }
    CGAL_Iterator_from_circulator<C,Ref>&
    operator++() {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
        ++current;
        if ( current == *anchor)
            ++winding;
        return *this;
    }
    CGAL_Iterator_from_circulator<C,Ref>
    operator++(int) {
        CGAL_Iterator_from_circulator<C,Ref> tmp = *this;
        ++*this;
        return tmp;
    }

    CGAL_Iterator_from_circulator<C,Ref>&
    operator--() {
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
        if ( current == *anchor)
            --winding;
        --current;
        return *this;
    }
    CGAL_Iterator_from_circulator<C,Ref>
    operator--(int) {
        CGAL_Iterator_from_circulator<C,Ref> tmp = *this;
        --*this;
        return tmp;
    }

    CGAL_Iterator_from_circulator<C,Ref>&
    operator+=( difference_type n) {
        CGAL_assertion( anchor != NULL);
        CGAL_assertion( current != NULL);
        if ( n < 0 && current == *anchor)  // We are leaving the anchor.
            --winding;
        current += n;
        if ( n > 0 && current == *anchor)  // Back again at the anchor.
            ++winding;
        return *this;
    }
    CGAL_Iterator_from_circulator<C,Ref>
    operator+( difference_type n) const {
        CGAL_Iterator_from_circulator<C,Ref> tmp = *this;
        return tmp += n;
    }
    CGAL_Iterator_from_circulator<C,Ref>&
    operator-=( difference_type n) {
        return operator+=( -n);
    }
    CGAL_Iterator_from_circulator<C,Ref>
    operator-( difference_type n) const {
        CGAL_Iterator_from_circulator<C,Ref> tmp = *this;
        return tmp += -n;
    }
    #if !defined(CGAL__CIRC_GNUG_27) && !defined(CGAL__CIRC_SUNPRO_41)
    difference_type
    operator-( const CGAL_Iterator_from_circulator<C,Ref>& i) const;
    #else
    difference_type
    operator-( const CGAL_Iterator_from_circulator<C,Ref>& i) const {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
        CGAL_assertion( anchor  == i.anchor);
        if ( winding != i.winding) {
            difference_type s = CGAL__min_circulator_size( *anchor);
            return   (current - *anchor) - (i.current - *anchor)
                   + s * (winding - i.winding);
        }
        return (current - *anchor) - (i.current - *anchor);
    }
    #endif

    Ref  operator[](difference_type n) const {
        CGAL_Iterator_from_circulator<C,Ref> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    bool
    operator<( const CGAL_Iterator_from_circulator<C,Ref>& i) const {
        CGAL_assertion( anchor  != NULL);
        CGAL_assertion( current != NULL);
        CGAL_assertion( anchor  == i.anchor);
        return (     (winding < i.winding)
                 || (    (winding == i.winding)
                      && (current - *anchor) < (i.current - *anchor)
                    )
               );
    }
    bool
    operator>( const CGAL_Iterator_from_circulator<C,Ref>& i) const {
        return i < *this;
    }
    bool
    operator<=( const CGAL_Iterator_from_circulator<C,Ref>& i) const {
        return !(i < *this);
    }
    bool
    operator>=( const CGAL_Iterator_from_circulator<C,Ref>& i) const {
        return !(*this < i);
    }
    Circulator  current_circulator() const { return current;}
};

template < class Dist, class  C, class Ref>
CGAL_Iterator_from_circulator<C,Ref>
operator+( Dist n,
           const CGAL_Iterator_from_circulator<C,Ref>& circ) {
    CGAL_Iterator_from_circulator<C,Ref> tmp = circ;
    return tmp += n;
}

#if !defined(CGAL__CIRC_GNUG_27) && !defined(CGAL__CIRC_SUNPRO_41)
template < class  C, class Ref>
difference_type
CGAL_Iterator_from_circulator<C,Ref>::
operator-( const CGAL_Iterator_from_circulator<C,Ref>& i) const {
    CGAL_assertion( anchor  != NULL);
    CGAL_assertion( current != NULL);
    CGAL_assertion( anchor  == i.anchor);
    if ( winding != i.winding) {
        difference_type s = CGAL__min_circulator_size( *anchor);
        return   (current - *anchor) - (i.current - *anchor)
               + s * (winding - i.winding);
    }
    return (current - *anchor) - (i.current - *anchor);
}
#endif


template < class  C >
class CGAL_Container_from_circulator {
private:
    C anchor;
public:
//
// CREATION

    CGAL_Container_from_circulator() {}
        // the resulting iterators will have a singular value.

    CGAL_Container_from_circulator(const C& c)
        // The anchor is normalized to be a minimal circulator.
        : anchor(c.min_circulator()) {}
        // the resulting iterators will have a singular value if the
        // circulator `c' is singular.

    CGAL_Container_from_circulator(
        // The anchor is normalized to be a minimal circulator.
        const CGAL_Container_from_circulator<C>& i)
        : anchor(i.anchor.min_circulator()) {}
//
// TYPES

typedef C  Circulator;

typedef C::value_type       value_type;
typedef C::reference        reference;
typedef C::const_reference  const_reference;
typedef C::size_type        size_type;
typedef C::difference_type    difference_type;

typedef CGAL_Iterator_from_circulator< C, value_type&>       iterator;
typedef CGAL_Iterator_from_circulator< C, const value_type&> const_iterator;
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
};
#endif // CGAL__CIRC_STL_ITERATOR_TRAITS //
// #line 93 "circulator.any"
                                          
// #line 3080 "circulator.any"
template < class  C>
class CGAL_Forward_circulator_from_container
    : public  CGAL_Forward_circulator_ptrbase<
            C::value_type, C::difference_type> {
private:
    C::iterator  i;
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

    CGAL_Forward_circulator_from_container( C* c)
        :  CGAL_Forward_circulator_ptrbase<
              C::value_type, C::difference_type>(c),
           i(c->begin()) {}

    CGAL_Forward_circulator_from_container( C* c,
                                                 C::iterator _i)
        :  CGAL_Forward_circulator_ptrbase<
              C::value_type, C::difference_type>(c),
           i(_i) {}

    CGAL_Forward_circulator_from_container(
        const CGAL_Forward_circulator_from_container<C>& c)
        :  CGAL_Forward_circulator_ptrbase<
              C::value_type, C::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef C                     Container;
    typedef C::iterator           iterator;
    typedef C::const_iterator     const_iterator;
    typedef C::value_type         value_type;
    typedef C::reference          reference;
    typedef C::const_reference    const_reference;
    typedef C::size_type          size_type;
    typedef C::difference_type    difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((C*)_ptr)->begin()==((C*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Forward_circulator_from_container
                           <C>& c) const {
        return i == c.i;
    }
    bool operator!=( const CGAL_Forward_circulator_from_container
                           <C>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((C*)_ptr)->end());
        return *i;
    }
    CGAL_Forward_circulator_from_container<C>&
    operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((C*)_ptr)->end());
        ++i;
        if ( i == ((C*)_ptr)->end())
            i = ((C*)_ptr)->begin();
        return *this;
    }
    CGAL_Forward_circulator_from_container<C>
    operator++(int) {
        CGAL_Forward_circulator_from_container<C> tmp= *this;
        ++*this;
        return tmp;
    }
    iterator  current_iterator() const { return i;}
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline C::difference_type* distance_type(
        const
    CGAL_Forward_circulator_from_container<C>&) {
        return (C::difference_type*)(0);
    }
    friend inline C::value_type* value_type(
        const
    CGAL_Forward_circulator_from_container<C>&) {
        return (C::value_type*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_circulator_from_container<C>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_circulator_from_container<C>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 3179 "circulator.any"
          
};

template < class  C>
class CGAL_Forward_const_circulator_from_container
    : public  CGAL_Forward_circulator_ptrbase<
            C::value_type, C::difference_type> {
private:
    C::const_iterator  i;
public:
//
// CREATION

    CGAL_Forward_const_circulator_from_container() {}

    CGAL_Forward_const_circulator_from_container( const C* c)
        :  CGAL_Forward_circulator_ptrbase<
              C::value_type, C::difference_type>((void*)c),
           i(c->begin()) {}

    CGAL_Forward_const_circulator_from_container( const C* c,
                                             C::const_iterator _i)
        :  CGAL_Forward_circulator_ptrbase<
              C::value_type, C::difference_type>((void*)c),
           i(_i) {}

    CGAL_Forward_const_circulator_from_container(
        const
        CGAL_Forward_const_circulator_from_container<C>& c)
        :  CGAL_Forward_circulator_ptrbase<
              C::value_type, C::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef C                     Container;
    typedef C::iterator           iterator;
    typedef C::const_iterator     const_iterator;
    typedef C::value_type         value_type;
    typedef C::reference          reference;
    typedef C::const_reference    const_reference;
    typedef C::size_type          size_type;
    typedef C::difference_type    difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((const C*)_ptr)->begin()
                 ==((const C*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Forward_const_circulator_from_container
                           <C>& c) const {
        return i == c.i;
    }
    bool operator!=( const CGAL_Forward_const_circulator_from_container
                           <C>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((const C*)_ptr)->end());
        return *i;
    }
    CGAL_Forward_const_circulator_from_container<C>&
    operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((const C*)_ptr)->end());
        ++i;
        if ( i == ((const C*)_ptr)->end())
            i = ((const C*)_ptr)->begin();
        return *this;
    }
    CGAL_Forward_const_circulator_from_container<C>
    operator++(int) {
        CGAL_Forward_const_circulator_from_container<C>
            tmp= *this;
        ++*this;
        return tmp;
    }
    const_iterator  current_iterator() const { return i;}
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline C::difference_type* distance_type(
        const
    CGAL_Forward_const_circulator_from_container<C>&) {
        return (C::difference_type*)(0);
    }
    friend inline C::value_type* value_type(
        const
    CGAL_Forward_const_circulator_from_container<C>&) {
        return (C::value_type*)(0);
    }
    friend inline forward_iterator_tag iterator_category(
    CGAL_Forward_const_circulator_from_container<C>) {
        return forward_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Forward_const_circulator_from_container<C>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 3268 "circulator.any"
          
};


template < class  C>
class CGAL_Bidirectional_circulator_from_container
    : public  CGAL_Bidirectional_circulator_ptrbase<
            C::value_type, C::difference_type> {
private:
    C::iterator  i;
public:
//
// CREATION

    CGAL_Bidirectional_circulator_from_container() {}

    CGAL_Bidirectional_circulator_from_container( C* c)
        :  CGAL_Bidirectional_circulator_ptrbase<
              C::value_type, C::difference_type>(c),
           i(c->begin()) {}

    CGAL_Bidirectional_circulator_from_container( C* c,
                                                 C::iterator _i)
        :  CGAL_Bidirectional_circulator_ptrbase<
              C::value_type, C::difference_type>(c),
           i(_i) {}

    CGAL_Bidirectional_circulator_from_container(
        const CGAL_Bidirectional_circulator_from_container<C>& c)
        :  CGAL_Bidirectional_circulator_ptrbase<
              C::value_type, C::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef C                     Container;
    typedef C::iterator           iterator;
    typedef C::const_iterator     const_iterator;
    typedef C::value_type         value_type;
    typedef C::reference          reference;
    typedef C::const_reference    const_reference;
    typedef C::size_type          size_type;
    typedef C::difference_type    difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((C*)_ptr)->begin()==((C*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Bidirectional_circulator_from_container
                           <C>& c) const {
        return i == c.i;
    }
    bool operator!=( const CGAL_Bidirectional_circulator_from_container
                           <C>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((C*)_ptr)->end());
        return *i;
    }
    CGAL_Bidirectional_circulator_from_container<C>&
    operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((C*)_ptr)->end());
        ++i;
        if ( i == ((C*)_ptr)->end())
            i = ((C*)_ptr)->begin();
        return *this;
    }
    CGAL_Bidirectional_circulator_from_container<C>
    operator++(int) {
        CGAL_Bidirectional_circulator_from_container<C> tmp= *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_circulator_from_container<C>&
    operator--() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((C*)_ptr)->end());
        if ( i == ((C*)_ptr)->begin())
            i = ((C*)_ptr)->end();
        --i;
        return *this;
    }
    CGAL_Bidirectional_circulator_from_container<C>
    operator--(int) {
        CGAL_Bidirectional_circulator_from_container<C> tmp = *this;
        --*this;
        return tmp;
    }
    iterator  current_iterator() const { return i;}
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline C::difference_type* distance_type(
        const
    CGAL_Bidirectional_circulator_from_container<C>&) {
        return (C::difference_type*)(0);
    }
    friend inline C::value_type* value_type(
        const
    CGAL_Bidirectional_circulator_from_container<C>&) {
        return (C::value_type*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_circulator_from_container<C>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_circulator_from_container<C>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 3369 "circulator.any"
          
};

template < class  C>
class CGAL_Bidirectional_const_circulator_from_container
    : public  CGAL_Bidirectional_circulator_ptrbase<
            C::value_type, C::difference_type> {
private:
    C::const_iterator  i;
public:
//
// CREATION

    CGAL_Bidirectional_const_circulator_from_container() {}

    CGAL_Bidirectional_const_circulator_from_container( const C* c)
        :  CGAL_Bidirectional_circulator_ptrbase<
              C::value_type, C::difference_type>((void*)c),
           i(c->begin()) {}

    CGAL_Bidirectional_const_circulator_from_container( const C* c,
                                             C::const_iterator _i)
        :  CGAL_Bidirectional_circulator_ptrbase<
              C::value_type, C::difference_type>((void*)c),
           i(_i) {}

    CGAL_Bidirectional_const_circulator_from_container(
        const
        CGAL_Bidirectional_const_circulator_from_container<C>& c)
        :  CGAL_Bidirectional_circulator_ptrbase<
              C::value_type, C::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef C                     Container;
    typedef C::iterator           iterator;
    typedef C::const_iterator     const_iterator;
    typedef C::value_type         value_type;
    typedef C::reference          reference;
    typedef C::const_reference    const_reference;
    typedef C::size_type          size_type;
    typedef C::difference_type    difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((const C*)_ptr)->begin()
                 ==((const C*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Bidirectional_const_circulator_from_container
                           <C>& c) const {
        return i == c.i;
    }
    bool operator!=(const CGAL_Bidirectional_const_circulator_from_container
                           <C>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((const C*)_ptr)->end());
        return *i;
    }
    CGAL_Bidirectional_const_circulator_from_container<C>&
    operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((const C*)_ptr)->end());
        ++i;
        if ( i == ((const C*)_ptr)->end())
            i = ((const C*)_ptr)->begin();
        return *this;
    }
    CGAL_Bidirectional_const_circulator_from_container<C>
    operator++(int) {
        CGAL_Bidirectional_const_circulator_from_container<C>
            tmp= *this;
        ++*this;
        return tmp;
    }
    CGAL_Bidirectional_const_circulator_from_container<C>&
    operator--() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((const C*)_ptr)->end());
        if ( i == ((const C*)_ptr)->begin())
            i = ((const C*)_ptr)->end();
        --i;
        return *this;
    }
    CGAL_Bidirectional_const_circulator_from_container<C>
    operator--(int) {
        CGAL_Bidirectional_const_circulator_from_container<C>
            tmp = *this;
        --*this;
        return tmp;
    }
    const_iterator  current_iterator() const { return i;}
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline C::difference_type* distance_type(
        const
    CGAL_Bidirectional_const_circulator_from_container<C>&) {
        return (C::difference_type*)(0);
    }
    friend inline C::value_type* value_type(
        const
    CGAL_Bidirectional_const_circulator_from_container<C>&) {
        return (C::value_type*)(0);
    }
    friend inline bidirectional_iterator_tag iterator_category(
    CGAL_Bidirectional_const_circulator_from_container<C>) {
        return bidirectional_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Bidirectional_const_circulator_from_container<C>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 3474 "circulator.any"
          
};


template < class  C>
class CGAL_Random_access_circulator_from_container
    : public  CGAL_Random_access_circulator_ptrbase<
            C::value_type, C::difference_type> {
private:
    C::iterator  i;
public:
//
// CREATION

    CGAL_Random_access_circulator_from_container() {}

    CGAL_Random_access_circulator_from_container( C* c)
        :  CGAL_Random_access_circulator_ptrbase<
              C::value_type, C::difference_type>(c),
           i(c->begin()) {}

    CGAL_Random_access_circulator_from_container( C* c,
                                                 C::iterator _i)
        :  CGAL_Random_access_circulator_ptrbase<
              C::value_type, C::difference_type>(c),
           i(_i) {}

    CGAL_Random_access_circulator_from_container(
        const CGAL_Random_access_circulator_from_container<C>& c)
        :  CGAL_Random_access_circulator_ptrbase<
              C::value_type, C::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef C                     Container;
    typedef C::iterator           iterator;
    typedef C::const_iterator     const_iterator;
    typedef C::value_type         value_type;
    typedef C::reference          reference;
    typedef C::const_reference    const_reference;
    typedef C::size_type          size_type;
    typedef C::difference_type    difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((C*)_ptr)->begin()==((C*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Random_access_circulator_from_container
                           <C>& c) const {
        return i == c.i;
    }
    bool operator!=( const CGAL_Random_access_circulator_from_container
                           <C>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((C*)_ptr)->end());
        return *i;
    }
    CGAL_Random_access_circulator_from_container<C>&
    operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((C*)_ptr)->end());
        ++i;
        if ( i == ((C*)_ptr)->end())
            i = ((C*)_ptr)->begin();
        return *this;
    }
    CGAL_Random_access_circulator_from_container<C>
    operator++(int) {
        CGAL_Random_access_circulator_from_container<C> tmp= *this;
        ++*this;
        return tmp;
    }

    CGAL_Random_access_circulator_from_container<C>&
    operator--() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((C*)_ptr)->end());
        if ( i == ((C*)_ptr)->begin())
            i = ((C*)_ptr)->end();
        --i;
        return *this;
    }
    CGAL_Random_access_circulator_from_container<C>
    operator--(int) {
        CGAL_Random_access_circulator_from_container<C> tmp = *this;
        --*this;
        return tmp;
    }

    #if !defined(CGAL__CIRC_GNUG_27) && !defined(CGAL__CIRC_SUNPRO_41)
    CGAL_Random_access_circulator_from_container<C>&
    operator+=( difference_type n);
    #else
    CGAL_Random_access_circulator_from_container<C>&
    operator+=( difference_type n) {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((C*)_ptr)->end());

        C::difference_type j    = i - ((C*)_ptr)->begin();
        C::difference_type size = ((C*)_ptr)->size();
        CGAL_assertion( j    >= 0);
        CGAL_assertion( size >= 0);
        j = CGAL_non_negative_mod( j + n, size);
        CGAL_assertion( j >= 0);
        CGAL_assertion( j < size);
        i = ((C*)_ptr)->begin() + j;
        return *this;
    }
    #endif

    CGAL_Random_access_circulator_from_container<C>
    operator+( difference_type n) const {
        CGAL_Random_access_circulator_from_container<C> tmp = *this;
        return tmp += n;
    }
    CGAL_Random_access_circulator_from_container<C>&
    operator-=( difference_type n) {
        return operator+=( -n);
    }
    CGAL_Random_access_circulator_from_container<C>
    operator-( difference_type n) const {
        CGAL_Random_access_circulator_from_container<C> tmp = *this;
        return tmp += -n;
    }
    difference_type
    operator-( const CGAL_Random_access_circulator_from_container<
                   C>& c) const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( c._ptr != NULL);
        return i - c.i;
    }
    reference  operator[](difference_type n) const {
        CGAL_Random_access_circulator_from_container<C> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }

    friend inline
    CGAL_Random_access_circulator_from_container<C>
    operator+( difference_type n, const
               CGAL_Random_access_circulator_from_container<C>& c) {
        CGAL_Random_access_circulator_from_container<C> tmp = c;
        return tmp += n;
    }
    iterator  current_iterator() const { return i;}

    CGAL_Random_access_circulator_from_container<C>
    min_circulator() const {
        return CGAL_Random_access_circulator_from_container<C>((C*)_ptr);
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline C::difference_type* distance_type(
        const
    CGAL_Random_access_circulator_from_container<C>&) {
        return (C::difference_type*)(0);
    }
    friend inline C::value_type* value_type(
        const
    CGAL_Random_access_circulator_from_container<C>&) {
        return (C::value_type*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(
    CGAL_Random_access_circulator_from_container<C>) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Random_access_circulator_from_container<C>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 3637 "circulator.any"
          
};

#if !defined(CGAL__CIRC_GNUG_27) && !defined(CGAL__CIRC_SUNPRO_41)
template < class C>
CGAL_Random_access_circulator_from_container<C>&
CGAL_Random_access_circulator_from_container<C>::
operator+=( C::difference_type n) {
    CGAL_assertion( _ptr != NULL);
    CGAL_assertion( i != ((C*)_ptr)->end());

    C::difference_type j    = i - ((C*)_ptr)->begin();
    C::difference_type size = ((C*)_ptr)->size();
    CGAL_assertion( j    >= 0);
    CGAL_assertion( size >= 0);
    j = CGAL_non_negative_mod( j + n, size);
    CGAL_assertion( j >= 0);
    CGAL_assertion( j < size);
    i = ((C*)_ptr)->begin() + j;
    return *this;
}
#endif


template < class  C>
class CGAL_Random_access_const_circulator_from_container
    : public  CGAL_Random_access_circulator_ptrbase<
            C::value_type, C::difference_type> {
private:
    C::const_iterator  i;
public:
//
// CREATION

    CGAL_Random_access_const_circulator_from_container() {}

    CGAL_Random_access_const_circulator_from_container( const C* c)
        :  CGAL_Random_access_circulator_ptrbase<
              C::value_type, C::difference_type>((void*)c),
           i(c->begin()) {}

    CGAL_Random_access_const_circulator_from_container( const C* c,
                                             C::const_iterator _i)
        :  CGAL_Random_access_circulator_ptrbase<
              C::value_type, C::difference_type>((void*)c),
           i(_i) {}

    CGAL_Random_access_const_circulator_from_container(
        const
        CGAL_Random_access_const_circulator_from_container<C>& c)
        :  CGAL_Random_access_circulator_ptrbase<
              C::value_type, C::difference_type>(c._ptr),
           i(c.i) {}
//
// TYPES

    typedef C                     Container;
    typedef C::iterator           iterator;
    typedef C::const_iterator     const_iterator;
    typedef C::value_type         value_type;
    typedef C::reference          reference;
    typedef C::const_reference    const_reference;
    typedef C::size_type          size_type;
    typedef C::difference_type    difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        return    (_ptr == NULL)
               || (((const C*)_ptr)->begin()
                 ==((const C*)_ptr)->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==(
        const CGAL_Random_access_const_circulator_from_container
                           <C>& c) const {
        return i == c.i;
    }
    bool operator!=(const CGAL_Random_access_const_circulator_from_container
                           <C>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((const C*)_ptr)->end());
        return *i;
    }
    CGAL_Random_access_const_circulator_from_container<C>&
    operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((const C*)_ptr)->end());
        ++i;
        if ( i == ((const C*)_ptr)->end())
            i = ((const C*)_ptr)->begin();
        return *this;
    }
    CGAL_Random_access_const_circulator_from_container<C>
    operator++(int) {
        CGAL_Random_access_const_circulator_from_container<C>
            tmp= *this;
        ++*this;
        return tmp;
    }

    CGAL_Random_access_const_circulator_from_container<C>&
    operator--() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((const C*)_ptr)->end());
        if ( i == ((const C*)_ptr)->begin())
            i = ((const C*)_ptr)->end();
        --i;
        return *this;
    }
    CGAL_Random_access_const_circulator_from_container<C>
    operator--(int) {
        CGAL_Random_access_const_circulator_from_container<C>
            tmp = *this;
        --*this;
        return tmp;
    }

    #if !defined(CGAL__CIRC_GNUG_27) && !defined(CGAL__CIRC_SUNPRO_41)
    CGAL_Random_access_const_circulator_from_container<C>&
    operator+=( difference_type n);
    #else
    CGAL_Random_access_const_circulator_from_container<C>&
    operator+=( difference_type n) {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( i != ((const C*)_ptr)->end());

        C::difference_type j    = i - ((const C*)_ptr)
                                                ->begin();
        C::difference_type size = ((const C*)_ptr)->size();
        CGAL_assertion( j    >= 0);
        CGAL_assertion( size >= 0);
        j = CGAL_non_negative_mod( j + n, size);
        CGAL_assertion( j >= 0);
        CGAL_assertion( j < size);
        i = ((const C*)_ptr)->begin() + j;
        return *this;
    }
    #endif

    CGAL_Random_access_const_circulator_from_container<C>
    operator+( difference_type n) const {
        CGAL_Random_access_const_circulator_from_container<C>
            tmp = *this;
        return tmp += n;
    }
    CGAL_Random_access_const_circulator_from_container<C>&
    operator-=( difference_type n) {
        return operator+=( -n);
    }
    CGAL_Random_access_const_circulator_from_container<C>
    operator-( difference_type n) const {
        CGAL_Random_access_const_circulator_from_container<C>
            tmp = *this;
        return tmp += -n;
    }
    difference_type
    operator-( const CGAL_Random_access_const_circulator_from_container<
                   C>& c) const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( c._ptr != NULL);
        return i - c.i;
    }
    const_reference  operator[](difference_type n) const {
        CGAL_Random_access_const_circulator_from_container<C>
            tmp = *this;
        tmp += n;
        return tmp.operator*();
    }

    friend inline
    CGAL_Random_access_const_circulator_from_container<C>
    operator+( difference_type n, const
               CGAL_Random_access_const_circulator_from_container<
                   C>& c) {
        CGAL_Random_access_const_circulator_from_container<C>
            tmp = c;
        return tmp += n;
    }
    const_iterator  current_iterator() const { return i;}

    CGAL_Random_access_const_circulator_from_container<C>
    min_circulator() const {
        return CGAL_Random_access_const_circulator_from_container<C>
                   ((const C*)_ptr);
    }
    
// #line 41 "gnu_workaround.any"
    #ifdef __GNUG__
    friend inline C::difference_type* distance_type(
        const
    CGAL_Random_access_const_circulator_from_container<C>&) {
        return (C::difference_type*)(0);
    }
    friend inline C::value_type* value_type(
        const
    CGAL_Random_access_const_circulator_from_container<C>&) {
        return (C::value_type*)(0);
    }
    friend inline random_access_iterator_tag iterator_category(
    CGAL_Random_access_const_circulator_from_container<C>) {
        return random_access_iterator_tag();
    }
    friend inline CGAL_Circulator_tag CGAL_query_circulator_or_iterator(
    CGAL_Random_access_const_circulator_from_container<C>) {
        return CGAL_Circulator_tag();
    }
    #endif
// #line 3832 "circulator.any"
          
};

#if !defined(CGAL__CIRC_GNUG_27) && !defined(CGAL__CIRC_SUNPRO_41)
template < class C>
CGAL_Random_access_const_circulator_from_container<C>&
CGAL_Random_access_const_circulator_from_container<C>::
operator+=( C::difference_type n) {
    CGAL_assertion( _ptr != NULL);
    CGAL_assertion( i != ((const C*)_ptr)->end());

    C::difference_type j    = i - ((const C*)_ptr)
                                            ->begin();
    C::difference_type size = ((const C*)_ptr)->size();
    CGAL_assertion( j    >= 0);
    CGAL_assertion( size >= 0);
    j = CGAL_non_negative_mod( j + n, size);
    CGAL_assertion( j >= 0);
    CGAL_assertion( j < size);
    i = ((const C*)_ptr)->begin() + j;
    return *this;
}
#endif
// #line 94 "circulator.any"
      
// #line 2306 "circulator.any"
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

    typedef I         iterator;
    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        CGAL_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Forward_circulator_from_iterator<I, T, Size,
                     Dist>& c) const {
        CGAL_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Forward_circulator_from_iterator<I, T, Size,
                     Dist>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_assertion( current != _end);
        return *current;
    }
    CGAL_Forward_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_assertion( current != _end);
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
    iterator  current_iterator() const { return current;}
    
// #line 41 "gnu_workaround.any"
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
// #line 2401 "circulator.any"
          
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

    typedef I         iterator;
    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        CGAL_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Forward_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        CGAL_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Forward_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_assertion( current != _end);
        return *current;
    }
    CGAL_Forward_const_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_assertion( current != _end);
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
    iterator  current_iterator() const { return current;}
    
// #line 41 "gnu_workaround.any"
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
// #line 2478 "circulator.any"
          
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

    typedef I         iterator;
    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        CGAL_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Bidirectional_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        CGAL_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Bidirectional_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_assertion( current != _end);
        return *current;
    }
    CGAL_Bidirectional_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_assertion( current != _end);
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
        CGAL_assertion( current != _end);
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
    iterator  current_iterator() const { return current;}
    
// #line 41 "gnu_workaround.any"
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
// #line 2571 "circulator.any"
          
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

    typedef I         iterator;
    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        CGAL_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Bidirectional_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        CGAL_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Bidirectional_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_assertion( current != _end);
        return *current;
    }
    CGAL_Bidirectional_const_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_assertion( current != _end);
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
        CGAL_assertion( current != _end);
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
    iterator  current_iterator() const { return current;}
    
// #line 41 "gnu_workaround.any"
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
// #line 2664 "circulator.any"
          
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

    typedef I         iterator;
    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        CGAL_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Random_access_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        CGAL_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Random_access_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        return !(*this == c);
    }
    reference  operator*() const {
        CGAL_assertion( current != _end);
        return *current;
    }
    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_assertion( current != _end);
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
        CGAL_assertion( current != _end);
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
        CGAL_assertion((_begin == i._begin) && (_end == i._end));
        return current - i.current;
    }
    reference  operator[](Dist n) const {
        CGAL_Random_access_circulator_from_iterator< I, T, Size,
                         Dist> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    iterator  current_iterator() const { return current;}

    CGAL_Random_access_circulator_from_iterator< I, T, Size, Dist>
    min_circulator() const {
        return CGAL_Random_access_circulator_from_iterator< I, T,
                   Size, Dist>( _begin, _end);
    }
    
// #line 41 "gnu_workaround.any"
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
// #line 2794 "circulator.any"
          
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
    CGAL_assertion( current != _end);

    Dist i    = current - _begin;
    Dist size = _end    - _begin;
    CGAL_assertion( i    >= 0);
    CGAL_assertion( size >= 0);
    i = CGAL_non_negative_mod( i + n, size);
    CGAL_assertion( i >= 0);
    CGAL_assertion( i < size);
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

    typedef I         iterator;
    typedef T         value_type;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef Size      size_type;
    typedef Dist      difference_type;

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == NULL);
        CGAL_assertion((_end == _begin) || (current != _end));
        return _end == _begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const {
        return !(*this == p);
    }
    bool operator==( const CGAL_Random_access_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        CGAL_assertion((_begin == c._begin) && (_end == c._end));
        return current == c.current;
    }
    bool operator!=( const CGAL_Random_access_const_circulator_from_iterator
                           <I, T, Size, Dist>& c) const {
        return !(*this == c);
    }
    const_reference  operator*() const {
        CGAL_assertion( current != _end);
        return *current;
    }
    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>&
    operator++() {
        CGAL_assertion( current != _end);
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
        CGAL_assertion( current != _end);
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
        CGAL_assertion((_begin == i._begin) && (_end == i._end));
        return current - i.current;
    }
    const_reference  operator[](Dist n) const {
        CGAL_Random_access_const_circulator_from_iterator< I, T, Size,
                         Dist> tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    iterator  current_iterator() const { return current;}

    CGAL_Random_access_const_circulator_from_iterator< I, T, Size, Dist>
    min_circulator() const {
        return CGAL_Random_access_const_circulator_from_iterator< I, T,
                   Size, Dist>( _begin, _end);
    }
    
// #line 41 "gnu_workaround.any"
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
// #line 2952 "circulator.any"
          
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
    CGAL_assertion( current != _end);

    Dist i    = current - _begin;
    Dist size = _end    - _begin;
    CGAL_assertion( i    >= 0);
    CGAL_assertion( size >= 0);
    i = CGAL_non_negative_mod( i + n, size);
    CGAL_assertion( i >= 0);
    CGAL_assertion( i < size);
    current = _begin + i;
    return *this;
}
// #line 95 "circulator.any"
 

#endif // CGAL_CIRCULATOR_H //
// EOF //
