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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Circulator_on_node.h
// package       : STL_Extension (2.34)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.26 $
// revision_date : $Date: 2001/07/11 09:00:22 $
// author(s)     : Michael Hoffmann
//                 Lutz Kettner
//
// coordinator   : ETH
//
// An circulator built over a linked node structure.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CIRCULATOR_ON_NODE_H
#define CGAL_CIRCULATOR_ON_NODE_H 1
#include <CGAL/circulator.h>

CGAL_BEGIN_NAMESPACE

template < class Node,
           class Next,
           class Prev,
           class Ref = Node&,
           class Ptr = Node*,
           class Ctg = Bidirectional_circulator_tag>
class Circulator_on_node {
protected:
  Ptr      nt;    // The internal node ptr.
public:
  typedef  Circulator_on_node<Node,Next,Prev,Ref,Ptr,Ctg> Self;

  typedef  Ctg                iterator_category;
  typedef  Node               value_type;
  typedef  std::ptrdiff_t     difference_type;
  typedef  std::size_t        size_type;
  typedef  Ref                reference;
  typedef  Ptr                pointer;

  // CREATION
  // --------

  Circulator_on_node() : nt(0) {}
  Circulator_on_node( Ptr p) : nt(p) {}

  // OPERATIONS Forward Category
  // ---------------------------

  Ptr  ptr() const { return nt;}

  bool operator==( CGAL_NULL_TYPE p) const {
    CGAL_assertion( p == 0);
    return ( nt == 0);
  }
  bool  operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
  bool  operator==( const Self& i) const { return ( nt == i.nt); }
  bool  operator!=( const Self& i) const { return !(*this == i); }
  Ref   operator*()  const { return *nt; }
  Ptr   operator->() const { return nt; }
  Self& operator++() {
    Next next;
    nt = next(nt);
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
    Prev prev;
    nt = prev(nt);
    return *this;
  }
  Self  operator--(int) {
    Self tmp = *this;
    --*this;
    return tmp;
  }

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
#ifndef CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
  friend inline  iterator_category
  iterator_category( const Self&) { return iterator_category(); }
  friend inline  value_type*
  value_type( const Self&) { return (value_type*)(0); }
  friend inline  difference_type*
  distance_type( const Self&) { return (difference_type*)(0); }
  friend inline  Circulator_tag
  query_circulator_or_iterator( const Self&) { return Circulator_tag(); }
#endif // CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

CGAL_END_NAMESPACE
#endif // CGAL_CIRCULATOR_ON_NODE_H //
// EOF //
