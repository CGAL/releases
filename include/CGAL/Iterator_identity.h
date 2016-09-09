// ======================================================================
//
// Copyright (c) 1997, 1998, 1999, 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Iterator_identity.h
// package       : STL_Extension (2.57)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.41 $
// revision_date : $Date: 2002/03/28 15:24:26 $
// author(s)     : Michael Hoffmann
//                 Lutz Kettner
//
// coordinator   : ETH
//
// An iterator adaptor for the identity function.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ITERATOR_IDENTITY_H
#define CGAL_ITERATOR_IDENTITY_H 1
#include <CGAL/circulator.h>

CGAL_BEGIN_NAMESPACE

#if defined(CGAL_CFG_NO_ITERATOR_TRAITS) && \
!defined(CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT)
template < class I, class Ref, class Ptr, class Val, class Dist, class Ctg>
#else
template < class I,
           class Ref  = CGAL_TYPENAME_MSVC_NULL
                        std::iterator_traits<I>::reference,
           class Ptr  = CGAL_TYPENAME_MSVC_NULL
                        std::iterator_traits<I>::pointer,
           class Val  = CGAL_TYPENAME_MSVC_NULL
                        std::iterator_traits<I>::value_type,
           class Dist = CGAL_TYPENAME_MSVC_NULL
                        std::iterator_traits<I>::difference_type,
           class Ctg = CGAL_TYPENAME_MSVC_NULL
                        std::iterator_traits<I>::iterator_category>
#endif
class Iterator_identity {
protected:
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
#ifndef CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
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
#endif // CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class I, class Ref, class Ptr, class Val,
           class Dist, class Ctg>
inline
Iterator_identity<I,Ref,Ptr,Val,Dist,Ctg>
operator+( Dist n, Iterator_identity<I,Ref,Ptr,Val,Dist,Ctg> i)
{ return i += n; }

CGAL_END_NAMESPACE
#endif // CGAL_ITERATOR_IDENTITY_H //
// EOF //
