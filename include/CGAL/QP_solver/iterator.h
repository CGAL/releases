// Copyright (c) 1997-2007  ETH Zurich (Switzerland).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/QP_solver/include/CGAL/QP_solver/iterator.h $
// $Id: iterator.h 38453 2007-04-27 00:34:44Z gaertner $
// 
//
// Author(s)     : Sven Schoenherr
//                 Bernd Gaertner <gaertner@inf.ethz.ch>
//                 Franz Wessendorp 
//                 Kaspar Fischer

#ifndef CGAL_QP_SOLVER_ITERATOR_H
#define CGAL_QP_SOLVER_ITERATOR_H

#include <CGAL/basic.h>
#include <CGAL/QP_solver/basic.h>
#include <map>

CGAL_BEGIN_NAMESPACE

// this is a const iterator that - given a key_type value n - returns
// a data_type value; if the map contains an item with key n, its
// data_type value is returned; otherwise, a default value (to be
// provided during construction) is returned  
template < typename Map>
class Fake_random_access_const_iterator
{  
public:
  // types
  typedef  std::random_access_iterator_tag    iterator_category;
  typedef  typename Map::difference_type      difference_type;
  typedef  typename Map::mapped_type          value_type;
  typedef  const value_type*                  pointer;
  typedef  const value_type&                  reference;
  
  typedef  Fake_random_access_const_iterator  Self;
  typedef  difference_type                    Diff;
  typedef  value_type                         Val;

  // construction
  Fake_random_access_const_iterator ( )
    : map (0), key (0), d()
  {}

  Fake_random_access_const_iterator (const Map* m, const Val& v = Val())
    : map (m), key (0), d (v)
  { }
  
  const Val&  operator *  ( ) const { return at(key); }
  const Val*  operator -> ( ) const { return &at(key); }
  
  // equality operator
  bool       operator == ( const Self& x) const { return ( key==x.key); }
  bool       operator != ( const Self& x) const { return ( key!=x.key); }
  
  // forward operations
  // ------------------
  Self&      operator ++ (    ) {                   ++key; return *this; }
  Self       operator ++ ( int) { Self tmp = *this; ++key; return tmp;   }
  
  // bidirectional operations
  // ------------------------
  Self&      operator -- (    ) {                   --key; return *this; }
  Self       operator -- ( int) { Self tmp = *this; --key; return tmp;   }
  
  // random access operations
  // ------------------------
  // access
  const Val& operator [] ( Diff i) const { return at(i); }
  
  // less operator
  bool       operator <  ( const Self& x) const { return ( key < x.key);}
  
  // arithmetic operations
  Self&      operator += ( Diff n) { key += n; return *this; }
  Self&      operator -= ( Diff n) { key -= n; return *this; }
  
  Self       operator +  ( Diff n) const { Self tmp = *this; return tmp+=n; }
  Self       operator -  ( Diff n) const { Self tmp = *this; return tmp-=n; }
  
  Diff       operator -  ( const Self& x) const { return key - x.key; }
  
private:
  const Map* map; 
  Diff key;
  Val d;

  const Val& at (Diff n) const {
    CGAL_qpe_precondition (map != 0);
    typename Map::const_iterator i = map->find (n);
    if (i != map->end())
      return i->second;
    else
      return d;
  }
}; 


// this is a random access iterator that is dereferenced by applying
// a fixed operation to its difference from a fixed Diff value
// -----------------------------------------------------------------

template <class Diff, class Op>
class Transform_diff_const_iterator {
public:
  // types
  typedef  std::random_access_iterator_tag    iterator_category;
  typedef  Diff                               difference_type;
  typedef  typename Op::result_type           value_type;
  typedef  const value_type*                  pointer;
  typedef  const value_type&                  reference;
  
  typedef  Transform_diff_const_iterator      Self;
  typedef  value_type                         Val;

  // construction
  Transform_diff_const_iterator ( )
    : base_diff(), diff(), op(), val()
  {}

  Transform_diff_const_iterator (Diff n, Op operation = Op())
    : base_diff(n), diff(n), op(operation), val()
  { }
  
  const Val&  operator *  ( ) const { val = op(diff-base_diff); return val; }
  
  // equality operator
  bool       operator == ( const Self& x) const { return ( diff==x.diff); }
  bool       operator != ( const Self& x) const { return ( diff!=x.diff); }
  
  // forward operations
  // ------------------
  Self&      operator ++ (    ) {                   ++diff; return *this; }
  Self       operator ++ ( int) { Self tmp = *this; ++diff; return tmp;   }
  
  // bidirectional operations
  // ------------------------
  Self&      operator -- (    ) {                   --diff; return *this; }
  Self       operator -- ( int) { Self tmp = *this; --diff; return tmp;   }
  
  // random access operations
  // ------------------------
  // access
  const Val& operator [] ( Diff i) const { val= op(i-base_diff); return val; }
  
  // less operator
  bool       operator <  ( const Self& x) const { return ( diff < x.diff);}
  
  // arithmetic operations
  Self&      operator += ( Diff n) { diff += n; return *this; }
  Self&      operator -= ( Diff n) { diff -= n; return *this; }
  
  Self       operator +  ( Diff n) const { Self tmp = *this; return tmp+=n; }
  Self       operator -  ( Diff n) const { Self tmp = *this; return tmp-=n; }
  
  Diff       operator -  ( const Self& x) const { return diff - x.diff; }
  
private:
  Diff base_diff;
  Diff diff;
  Op op;
  mutable Val val;
};
 

CGAL_END_NAMESPACE

#endif // CGAL_QP_SOLVER_ITERATOR_H

// ===== EOF ==================================================================
