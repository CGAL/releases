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
// file          : include/CGAL/Circulator_on_node.h
// package       : STL_Extension (2.6)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/04/07 18:31:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// An circulator built over a linked node structure.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CIRCULATOR_ON_NODE_H
#define CGAL_CIRCULATOR_ON_NODE_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

CGAL_BEGIN_NAMESPACE

#ifdef CGAL_CFG_NO_DEFAULT_PREVIOUS_TEMPLATE_ARGUMENTS
template < class Node, class Next, class Prev, class Ref, class Ptr,
           class Ctg>
#else
template < class Node,
           class Next,
           class Prev,
           class Ref = Node&,
           class Ptr = Node*,
           class Ctg = Bidirectional_circulator_tag>
#endif
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
        CGAL_assertion( p == NULL);
        return ( nt == NULL);
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
    friend inline  iterator_category
    iterator_category( const Self&) { return iterator_category(); }
    friend inline  value_type*
    value_type( const Self&) { return (value_type*)(0); }
    friend inline  difference_type*
    distance_type( const Self&) { return (difference_type*)(0); }
    friend inline  Circulator_tag
    query_circulator_or_iterator( const Self&) { return Circulator_tag(); }
#endif // CGAL_CFG_NO_ITERATOR_TRAITS //
};

CGAL_END_NAMESPACE
#endif // CGAL_CIRCULATOR_ON_NODE_H //
// EOF //
