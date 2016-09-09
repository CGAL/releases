// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/Range_tree_k.h
// package       : Range_segment_trees (1.8)
// source        : include/CGAL/Range_tree_k.h
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1998/02/03 13:15:03 $
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef __CGAL_Range_tree_k__
#define __CGAL_Range_tree_k__

// Predefined k-dimensional Range Trees (k=1..4) 
// The trees can either be templated with d arbitrary types
// (e.g., CGAL_Range_tree_3) 
// or with an unary type for each dimension
// (e.g., CGAL_Range_tree_uni_4).
// The container class and sequence container class as well as the 
// interfaces are defined in these classes.

#include <iostream.h>
#include <iterator.h>
#include "Tree_base.h"
#include "Tree_traits.h"
#include "Range_tree_d.h"

//-------------------------------------------------------------------
// A one dimensional Range Tree is defined in this class.
// Ti is the type of each dimension of the tree.

template <class _Traits_1>
class CGAL_Range_tree_1
{ 

public:
  typedef _Traits_1 Traits;
  typedef typename _Traits_1::Key Key;
  typedef typename _Traits_1::Interval Interval;
  typedef typename _Traits_1::Key_1 Key_1;
  typedef typename _Traits_1::key_1 key_1;
  typedef typename _Traits_1::low_1 low_1;
  typedef typename _Traits_1::high_1 high_1;
  typedef typename _Traits_1::compare_1 compare_1;

  typedef CGAL_tree_point_traits<Key, Interval, Key_1, key_1, low_1, 
  high_1, compare_1> I1;

  typedef CGAL_tree_anchor<Key, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef CGAL_Range_tree_d<Key, Interval, I1> Range_tree_1_type;
  Range_tree_1_type * Range_tree_1;

  CGAL_Range_tree_1()
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
  }
  typedef list<Key>::iterator L_iterator;
 CGAL_Range_tree_1(list<Key>::iterator& first, 
		   list<Key>::iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
   (*Range_tree_1).make_tree(first,last);
  }
#ifdef stlvector
  typedef vector<Key>::iterator V_iterator;
  CGAL_Range_tree_1(V_iterator& first, 
		    V_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    (*Range_tree_1).make_tree(first,last);
  }
#endif
#ifdef carray
  CGAL_Range_tree_1(Key * first, 
		    Key * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    (*Range_tree_1).make_tree(first,last);
  }
#endif

  bool make_tree(list<Key>::iterator& first, 
		 list<Key>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    return (*Range_tree_1).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(V_iterator& first, 
		 V_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    return (*Range_tree_1).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Key * first, 
		 Key * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    return (*Range_tree_1).make_tree(first,last);
  }
#endif
  
  back_insert_iterator<list<Key> >  
    window_query(Interval const &win,  
		 back_insert_iterator<list<Key> > result)
  {
    return (*Range_tree_1).window_query(win, result);
  }
  back_insert_iterator<vector<Key> >  
    window_query(Interval const &win,  
		 back_insert_iterator<vector<Key> > result)
  {
    return (*Range_tree_1).window_query(win, result);
  }
#ifdef carray
  Key * 
    window_query(Interval const &win,  
		 Key *result)
  {
    return (*Range_tree_1).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Key>  
    window_query(Interval const &win,  
		 ostream_iterator<Key> result)
  {
    return (*Range_tree_1).window_query(win, result);
  }
#endif

  ~CGAL_Range_tree_1()
  {
    if (Range_tree_1!=(Range_tree_1_type *)0)
      delete Range_tree_1;
    Range_tree_1=(Range_tree_1_type *)0;
    if (Tree_anchor!=(Tree_anchor_type *)0)
      delete Tree_anchor;
    Tree_anchor=(Tree_anchor_type *)0;
  }
};


//-------------------------------------------------------------------
// A two dimensional Range Tree is defined in this class.
// Ti is the type of each dimension of the tree.

template <class _Traits_2>
class CGAL_Range_tree_2
{ 

public:
  typedef _Traits_2 Traits;
  typedef typename _Traits_2::Key Key;
  typedef typename _Traits_2::Interval Interval;
  typedef typename _Traits_2::Key_2 Key_2;
  typedef typename _Traits_2::Key_1 Key_1;
  typedef typename _Traits_2::key_1 key_1;
  typedef typename _Traits_2::key_2 key_2;
  typedef typename _Traits_2::low_1 low_1;
  typedef typename _Traits_2::high_1 high_1;
  typedef typename _Traits_2::low_2 low_2;
  typedef typename _Traits_2::high_2 high_2;
  typedef typename _Traits_2::compare_1 compare_1;
  typedef typename _Traits_2::compare_2 compare_2;


  typedef CGAL_tree_point_traits<Key, Interval, 
  Key_1, key_1, low_1, high_1, 
  compare_1> I1;

  typedef CGAL_tree_point_traits<Key, Interval, 
  Key_2,   key_2, low_2, high_2, 
  compare_2> I2;


  typedef CGAL_tree_anchor<Key, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef CGAL_Range_tree_d<Key, Interval, I2> Range_tree_1_type;
  Range_tree_1_type * Range_tree_1;

  typedef CGAL_Range_tree_d<Key, Interval, I1> Range_tree_2_type;
  Range_tree_2_type *Range_tree_2;


  CGAL_Range_tree_2()
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
  }
typedef list<Key>::iterator Literator;
 CGAL_Range_tree_2(Literator& first, 
		   Literator& last)  {
   Tree_anchor = new Tree_anchor_type;
   Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
   Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
   (*Range_tree_2).make_tree(first,last);
  }
#ifdef stlvector
typedef vector<Key>::iterator Viterator
  CGAL_Range_tree_2(Viterator& first, 
		    Viterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    (*Range_tree_2).make_tree(first,last);
  }
#endif
#ifdef carray
  CGAL_Range_tree_2(Key * first, 
		    Key * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    (*Range_tree_2).make_tree(first,last);
  }
#endif
  bool make_tree(Literator& first, 
		 Literator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    return (*Range_tree_2).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(Viterator& first, 
		 Viterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    return (*Range_tree_2).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Key * first, 
		 Key * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    return (*Range_tree_2).make_tree(first,last);
  }
#endif
  
  back_insert_iterator<list<Key> >  
    window_query(Interval const &win,  
		 back_insert_iterator<list<Key> > result)
  {
    return (*Range_tree_2).window_query(win, result);
  }
  back_insert_iterator<vector<Key> >  
    window_query(Interval const &win,  
		 back_insert_iterator<vector<Key> > result)
  {
    return (*Range_tree_2).window_query(win, result);
  }
#ifdef carray
  Key * 
    window_query(Interval const &win,  
		 Key *result)
  {
    return (*Range_tree_2).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Key>  
    window_query(Interval const &win,  
		 ostream_iterator<Key> result)
  {
    return (*Range_tree_2).window_query(win, result);
  }
#endif

  ~CGAL_Range_tree_2()
  {
    if (Range_tree_2!=(Range_tree_2_type *)0)
      delete Range_tree_2;
    Range_tree_2=(Range_tree_2_type *)0;
    if (Range_tree_1!=(Range_tree_1_type *)0)
      delete Range_tree_1;
    Range_tree_1=(Range_tree_1_type *)0;
    if (Tree_anchor!=(Tree_anchor_type *)0)
      delete Tree_anchor;
    Tree_anchor=(Tree_anchor_type *)0;
  }
};

//-------------------------------------------------------------------
// A three dimensional Range Tree is defined in this class.
// Ti is the type of each dimension of the tree.
template <class _Traits_3>
class CGAL_Range_tree_3
{ 
public:
  typedef _Traits_3 Traits;
  typedef typename _Traits_3::Key Key;
  typedef typename _Traits_3::Interval Interval;
  typedef typename _Traits_3::Key_1 Key_1;
  typedef typename _Traits_3::Key_2 Key_2;
  typedef typename _Traits_3::Key_3 Key_3;
  typedef typename _Traits_3::key_1 key_1;
  typedef typename _Traits_3::key_2 key_2;
  typedef typename _Traits_3::key_3 key_3;
  typedef typename _Traits_3::low_1 low_1;
  typedef typename _Traits_3::high_1 high_1;
  typedef typename _Traits_3::low_2 low_2;
  typedef typename _Traits_3::high_2 high_2;
  typedef typename _Traits_3::low_3 low_3;
  typedef typename _Traits_3::high_3 high_3;
  typedef typename _Traits_3::compare_1 compare_1;
  typedef typename _Traits_3::compare_2 compare_2;
  typedef typename _Traits_3::compare_3 compare_3;

  typedef CGAL_tree_point_traits<Key, Interval, Key_1,
  key_1, low_1, high_1, compare_1> I1;

  typedef CGAL_tree_point_traits<Key, Interval, Key_2,
  key_2, low_2, high_2, compare_2> I2;

  typedef CGAL_tree_point_traits<Key, Interval, Key_3, 
  key_3, low_3, high_3, compare_3> I3;

  typedef CGAL_tree_anchor<Key, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef CGAL_Range_tree_d<Key, Interval, I3> Range_tree_1_type;
  Range_tree_1_type * Range_tree_1;

  typedef CGAL_Range_tree_d<Key, Interval, I2> Range_tree_2_type;
  Range_tree_2_type * Range_tree_2;

  typedef CGAL_Range_tree_d<Key, Interval, I1> Range_tree_3_type;
  Range_tree_3_type *Range_tree_3;

  CGAL_Range_tree_3()
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
  }
 CGAL_Range_tree_3(list<Key>::iterator& first, 
		   list<Key>::iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
   Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
   Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
   (*Range_tree_3).make_tree(first,last);
  }
#ifdef stlvector
  CGAL_Range_tree_3(vector<Key>::iterator& first, 
		    vector<Key>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
    (*Range_tree_3).make_tree(first,last);
  }
#endif
#ifdef carray
  CGAL_Range_tree_3(Key * first, 
		    Key * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
    (*Range_tree_3).make_tree(first,last);
  }
#endif

  bool make_tree(list<Key>::iterator& first, 
		 list<Key>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
    return (*Range_tree_3).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(vector<Key>::iterator& first, 
		 vector<Key>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
    return (*Range_tree_3).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Key * first, 
		 Key * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
    return (*Range_tree_3).make_tree(first,last);
  }
#endif
  
  back_insert_iterator<list<Key> >  
    window_query(Interval const &win,  
		 back_insert_iterator<list<Key> > result)
  {
    return (*Range_tree_3).window_query(win, result);
  }
  back_insert_iterator<vector<Key> >  
    window_query(Interval const &win,  
		 back_insert_iterator<vector<Key> > result)
  {
    return (*Range_tree_3).window_query(win, result);
  }
#ifdef carray
  Key * 
    window_query(Interval const &win,  
		 Key *result)
  {
    return (*Range_tree_3).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Key>  
    window_query(Interval const &win,  
		 ostream_iterator<Key> result)
  {
    return (*Range_tree_3).window_query(win, result);
  }
#endif

  ~CGAL_Range_tree_3()
  {
    if (Range_tree_3!=(Range_tree_3_type *)0)
      delete Range_tree_3;
    Range_tree_3=(Range_tree_3_type *)0;
    if (Range_tree_2!=(Range_tree_2_type *)0)
      delete Range_tree_2;
    Range_tree_2=(Range_tree_2_type *)0;
    if (Range_tree_1!=(Range_tree_1_type *)0)
      delete Range_tree_1;
    Range_tree_1=(Range_tree_1_type *)0;
    if (Tree_anchor!=(Tree_anchor_type *)0)
      delete Tree_anchor;
    Tree_anchor=(Tree_anchor_type *)0;
  }
};


//-------------------------------------------------------------------
// A three dimensional Range Tree is defined in this class.
// Ti is the type of each dimension of the tree.

template <class _Traits_4>
class CGAL_Range_tree_4
{ 
public:
  typedef _Traits_4 Traits;
  typedef typename _Traits_4::Key Key;
  typedef typename _Traits_4::Interval Interval;
  typedef typename _Traits_4::Key_1 Key_1;
  typedef typename _Traits_4::Key_2 Key_2;
  typedef typename _Traits_4::Key_3 Key_3;
  typedef typename _Traits_4::Key_4 Key_4;
  typedef typename _Traits_4::key_1 key_1;
  typedef typename _Traits_4::key_2 key_2;
  typedef typename _Traits_4::key_4 key_4;
  typedef typename _Traits_4::key_3 key_3;
  typedef typename _Traits_4::low_1 low_1;
  typedef typename _Traits_4::high_1 high_1;
  typedef typename _Traits_4::low_2 low_2;
  typedef typename _Traits_4::high_2 high_2;
  typedef typename _Traits_4::low_3 low_3;
  typedef typename _Traits_4::high_3 high_3;
  typedef typename _Traits_4::low_4 low_4;
  typedef typename _Traits_4::high_4 high_4;
  typedef typename _Traits_4::compare_1 compare_1;
  typedef typename _Traits_4::compare_2 compare_2;
  typedef typename _Traits_4::compare_3 compare_3;
  typedef typename _Traits_4::compare_4 compare_4;

  typedef CGAL_tree_point_traits<Key, Interval, Key_1,
  key_1, low_1, high_1, compare_1> I1;  

  typedef CGAL_tree_point_traits<Key, Interval, Key_2,
  key_2, low_2, high_2, compare_2> I2;  

  typedef CGAL_tree_point_traits<Key, Interval, Key_3,
  key_3, low_3, high_3, compare_3> I3;  

  typedef CGAL_tree_point_traits<Key, Interval, Key_4, 
  key_4, low_4, high_4, compare_4> I4;  

  typedef CGAL_tree_anchor<Key, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef CGAL_Range_tree_d<Key, Interval, I4> Range_tree_1_type;
  Range_tree_1_type * Range_tree_1;

  typedef CGAL_Range_tree_d<Key, Interval, I3> Range_tree_2_type;
  Range_tree_2_type * Range_tree_2;

  typedef CGAL_Range_tree_d<Key, Interval, I2> Range_tree_3_type;
  Range_tree_3_type *Range_tree_3;

  typedef CGAL_Range_tree_d<Key, Interval, I1> Range_tree_4_type;
  Range_tree_4_type *Range_tree_4;

  CGAL_Range_tree_4()
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
    Range_tree_4 = new Range_tree_4_type(*Range_tree_3);
  }
 CGAL_Range_tree_4(list<Key>::iterator& first, 
		   list<Key>::iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
   Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
   Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
   Range_tree_4 = new Range_tree_4_type(*Range_tree_3);
   (*Range_tree_4).make_tree(first,last);
  }
#ifdef stlvector
  CGAL_Range_tree_4(vector<Key>::iterator& first, 
		    vector<Key>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
    Range_tree_4 = new Range_tree_4_type(*Range_tree_3);
    (*Range_tree_4).make_tree(first,last);
  }
#endif
#ifdef carray
  CGAL_Range_tree_4(Key * first, 
		    Key * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
    Range_tree_4 = new Range_tree_4_type(*Range_tree_3);
    (*Range_tree_4).make_tree(first,last);
  }
#endif

  bool make_tree(list<Key>::iterator& first, 
		 list<Key>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
    Range_tree_4 = new Range_tree_4_type(*Range_tree_3);
    return (*Range_tree_4).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(vector<Key>::iterator& first, 
		 vector<Key>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
    Range_tree_4 = new Range_tree_4_type(*Range_tree_3);
    return (*Range_tree_4).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Key * first, 
		 Key * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    Range_tree_3 = new Range_tree_3_type(*Range_tree_2);
    Range_tree_4 = new Range_tree_4_type(*Range_tree_3);
    return (*Range_tree_4).make_tree(first,last);
  }
#endif
  
  back_insert_iterator<list<Key> >  
    window_query(Interval const &win,  
		 back_insert_iterator<list<Key> > result)
  {
    return (*Range_tree_4).window_query(win, result);
  }
  back_insert_iterator<vector<Key> >  
    window_query(Interval const &win,  
		 back_insert_iterator<vector<Key> > result)
  {
    return (*Range_tree_4).window_query(win, result);
  }
#ifdef carray
  Key * 
    window_query(Interval const &win,  
		 Key *result)
  {
    return (*Range_tree_4).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Key>  
    window_query(Interval const &win,  
		 ostream_iterator<Key> result)
  {
    return (*Range_tree_4).window_query(win, result);
  }
#endif

  ~CGAL_Range_tree_4()
  {
    if (Range_tree_4!=(Range_tree_4_type *)0)
      delete Range_tree_4;
    Range_tree_4=(Range_tree_4_type *)0;
    if (Range_tree_3!=(Range_tree_3_type *)0)
      delete Range_tree_3;
    Range_tree_3=(Range_tree_3_type *)0;
    if (Range_tree_2!=(Range_tree_2_type *)0)
      delete Range_tree_2;
    Range_tree_2=(Range_tree_2_type *)0;
    if (Range_tree_1!=(Range_tree_1_type *)0)
      delete Range_tree_1;
    Range_tree_1=(Range_tree_1_type *)0;
    if (Tree_anchor!=(Tree_anchor_type *)0)
      delete Tree_anchor;
    Tree_anchor=(Tree_anchor_type *)0;
  }
};
#endif



