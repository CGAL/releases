// ======================================================================
//
// Copyright (c) 1997-2002 The CGAL Consortium

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
// file          : include/CGAL/Nef_2/iterator_tools.h
// package       : Nef_2 (1.18)
// chapter       : Nef Polyhedra
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2002/03/07 11:25:52 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_ITERATORTOOLS_H
#define CGAL_ITERATORTOOLS_H

#include <CGAL/basic.h>
#include <CGAL/circulator.h>

CGAL_BEGIN_NAMESPACE

template <typename Iter, typename Move> 
class CircFromIt : public Iter {
    // Ptr  node;    // The internal node ptr inherited from It.
    typedef CircFromIt<Iter,Move> Self;
public:
    typedef typename Iter::iterator_category Icategory;
    typedef I_Circulator_from_iterator_traits<Icategory> CTraits;
    typedef typename CTraits::iterator_category iterator_category;

    CircFromIt() : Iter(0) {}
    CircFromIt(Iter i) : Iter(i) {}

// OPERATIONS Forward Category
// ---------------------------

    bool operator==( CGAL_NULL_TYPE p ) const {
      CGAL_assertion( p == NULL );
      return Iter::operator==( Iter(NULL) );
    }
    bool operator!=( CGAL_NULL_TYPE p ) const {
      return !(*this == p);
    }
    bool operator==( const Self& i ) const {
      return Iter::operator==(i);
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }

    Self& operator++() {
      Move move;
      move.forward(*this);
      return *this;
    }
    Self  operator++(int) {
      CircFromIt tmp = *this;
      ++*this;
      return tmp;
    }

// OPERATIONS Bidirectional Category
// ---------------------------------

    Self& operator--() {
      Move move;
      move.backward(*this);
      return *this;
    }
    Self  operator--(int) {
      CircFromIt tmp = *this;
      --*this;
      return tmp;
    }

};

template <typename Iter, typename Pnt> 
class PntItFromVertIt : public Iter {
public:
  typedef PntItFromVertIt<Iter,Pnt> Self;
  typedef Iter Base;
  typedef Pnt  value_type;
  typedef const Pnt* pointer;
  typedef const Pnt& reference;

  PntItFromVertIt() : Base() {}
  PntItFromVertIt(Iter it) : Base(it) {}
  PntItFromVertIt(const Self& it) : Base(it) {}

  reference operator*() const 
  { return Base::operator*().point(); }
  pointer operator->() const 
  { return &(operator*()); }
  Self& operator++() { return (Self&)Base::operator++(); }
  Self operator++(int) { Self tmp=*this; ++*this; return tmp; }

};

template <class H>
std::string PH(H h)
{ if (h == H()) return "nil"; return h->debug(); }

CGAL_END_NAMESPACE
#endif // CGAL_ITERATORTOOLS_H
