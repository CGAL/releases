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
// file          : include/CGAL/Iterator_project.h
// package       : STL_Extension (2.21)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.14 $
// revision_date : $Date: 2000/09/15 13:05:12 $
// author(s)     : Michael Hoffmann
//                 Lutz Kettner
//
//
// An iterator adaptor performing a projection on the value type.
// coordinator   : ?
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ITERATOR_PROJECT_H
#define CGAL_ITERATOR_PROJECT_H 1
#include <CGAL/circulator.h>

CGAL_BEGIN_NAMESPACE

#if defined(CGAL_CFG_NO_ITERATOR_TRAITS) && \
!defined(CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT)
template < class I, class Fct, class Ref, class Ptr, class Dist, class Ctg>
#else
template < class I,
           class Fct,
           class Ref  = typename std::iterator_traits<I>::reference,
           class Ptr  = typename std::iterator_traits<I>::pointer,
           class Dist = typename std::iterator_traits<I>::difference_type,
           class Ctg = typename std::iterator_traits<I>::iterator_category>
#endif
class Iterator_project {
protected:
  I        nt;    // The internal iterator.
public:
  typedef  I  Iterator;
  typedef  Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg> Self;

  typedef  Ctg                          iterator_category;
  typedef  typename Fct::argument_type  argument_type;
  typedef  typename Fct::result_type    value_type;
  typedef  Ref                          reference;
  typedef  Ptr                          pointer;
  typedef  Dist                         difference_type;


  // CREATION
  // --------

  Iterator_project() {}
  Iterator_project( I j) : nt(j) {}

  // OPERATIONS Forward Category
  // ---------------------------

  Iterator  current_iterator() const { return nt;}
  Ptr       ptr() const {
    Fct fct;
    return &(fct(*nt));
  }
  bool  operator==( const Self& i) const { return ( nt == i.nt); }
  bool  operator!=( const Self& i) const { return !(*this == i); }
  Ref   operator*()  const { return *ptr(); }
  Ptr   operator->() const { return ptr(); }
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
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
  friend inline  value_type*
  value_type( const Self&) { return (value_type*)(0); }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class Fct, class I, class Ref, class Ptr,
           class Dist, class Ctg>
inline
Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg>
operator+( Dist n, Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg> i)
{ return i += n; }

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
#ifndef CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
template < class I, class Fct, class Ref, class Ptr, class Dist, class Ctg>
inline  Ctg
iterator_category( const Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg>&) {
  return Ctg();
}
template < class I, class Fct, class Ref, class Ptr, class Dist, class Ctg>
inline  Dist*
distance_type( const Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg>&) {
  return (Dist*)(0);
}
template < class I, class Fct, class Ref, class Ptr, class Dist, class Ctg>
inline  Iterator_tag
query_circulator_or_iterator(
  const Iterator_project<I,Fct,Ref,Ptr,Dist,Ctg>&) {
  return Iterator_tag();
}
#endif // CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //


#if defined(CGAL_CFG_NO_ITERATOR_TRAITS) && \
!defined(CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT)
template < class I, class II, class Fct, class Dist, class Ctg>
#else
template < class I,
           class II,
           class Fct,
           class Dist = typename std::iterator_traits<I>::difference_type,
           class Ctg = typename std::iterator_traits<I>::iterator_category>
#endif
class Iterator_const_project {
protected:
  I        nt;    // The internal iterator.
public:
  typedef  I  Iterator;
  typedef  Iterator_const_project<I,II,Fct,Dist,Ctg> Self;

  typedef  Ctg                          iterator_category;
  typedef  typename Fct::argument_type  argument_type;
  typedef  typename Fct::result_type    value_type;
  typedef  const value_type&            reference;
  typedef  const value_type*            pointer;
  typedef  Dist                         difference_type;

  typedef  reference                    Ref;
  typedef  pointer                      Ptr;

  typedef  Iterator_project<II,Fct,value_type&,value_type*,Dist,Ctg>
    mutable_iterator;

  // CREATION
  // --------

  Iterator_const_project() {}
  Iterator_const_project( Iterator j) : nt(j) {}
  Iterator_const_project( mutable_iterator j) : nt( &*j) {}

  // OPERATIONS Forward Category
  // ---------------------------

  Iterator  current_iterator() const { return nt;}
  Ptr       ptr() const {
    Fct fct;
    return &(fct(*nt));
  }

  bool  operator==( const Self& i) const { return ( nt == i.nt); }
  bool  operator!=( const Self& i) const { return !(*this == i); }
  Ref   operator*()  const { return *ptr(); }
  Ptr   operator->() const { return ptr(); }
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
#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
#ifndef CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
  friend inline  value_type*
  value_type( const Self&) { return (value_type*)(0); }
#endif // CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

template < class Fct, class I, class II, class Dist, class Ctg>
inline
Iterator_const_project<I,II,Fct,Dist,Ctg>
operator+( Dist n, Iterator_const_project<I,II,Fct,Dist,Ctg> i)
{ return i += n; }

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
#ifndef CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
template < class I, class II, class Fct, class Dist, class Ctg>
inline  Ctg
iterator_category( const Iterator_const_project<I,II,Fct,Dist,Ctg>&) {
  return Ctg();
}
template < class I, class II, class Fct, class Dist, class Ctg>
inline  Dist*
distance_type( const Iterator_const_project<I,II,Fct,Dist,Ctg>&) {
  return (Dist*)(0);
}
template < class I, class II, class Fct, class Dist, class Ctg>
inline  Iterator_tag
query_circulator_or_iterator(
  const Iterator_const_project<I,II,Fct,Dist,Ctg>&) {
  return Iterator_tag();
}
#endif // CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //

CGAL_END_NAMESPACE
#endif // CGAL_ITERATOR_PROJECT_H //
// EOF //
