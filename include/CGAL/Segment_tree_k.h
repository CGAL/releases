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
// file          : include/CGAL/Segment_tree_k.h
// package       : SearchStructures (2.3)
// source        : include/CGAL/Segment_tree_pre.h
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1998/02/03 13:15:15 $
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef __CGAL_Segment_tree_pre__
#define __CGAL_Segment_tree_pre__

// Predefined k-dimensional Segment Trees (k=1..4) 
// The trees can either be templated with d arbitrary types
// (e.g., Segment_tree_3) 
// or with an unary type for each dimension
// (e.g., Segment_tree_uni_4).
// The container class and sequence container class as well as the 
// data accessors are defined in these classes.

#include <iostream>
#include <iterator>
#include <list>
#include <CGAL/Tree_base.h>
#include <CGAL/Tree_traits.h>
#include <CGAL/Segment_tree_d.h>
CGAL_BEGIN_NAMESPACE

template <class _Traits_1>
class Segment_tree_1
{ 
public:
  typedef  _Traits_1 Traits;
  typedef typename _Traits_1::Key Key;
  typedef typename _Traits_1::Interval Interval;
  typedef typename _Traits_1::Key_1 Key_1;
  typedef typename _Traits_1::key_1 key_1;
  typedef typename _Traits_1::low_1 low_1;
  typedef typename _Traits_1::high_1 high_1;
  typedef typename _Traits_1::compare_1 compare_1;

  typedef tree_interval_traits<Interval, Interval, 
  Key_1,  low_1, high_1, low_1, 
  high_1, compare_1> I1; 


  typedef tree_anchor<Interval, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef Segment_tree_d<Interval, Interval, I1> Segment_tree_1_type;
  Segment_tree_1_type * CSegment_tree_1;


  Segment_tree_1()
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
  }
  
  typedef std::list<Interval>::iterator l_iterator;
  Segment_tree_1(l_iterator& first, 
		     l_iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
   (*CSegment_tree_1).make_tree(first,last);
  }
#ifdef stlvector
  typedef v_iterator v_iterator;
  Segment_tree_1(v_iterator& first, 
		      v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    (*CSegment_tree_1).make_tree(first,last);
  }
#endif
#ifdef carray
  Segment_tree_1(Interval * first, 
		      Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    (*CSegment_tree_1).make_tree(first,last);
  }
#endif

  bool make_tree(l_iterator& first, 
		 l_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    return (*CSegment_tree_1).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(v_iterator& first, 
		 v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    return (*CSegment_tree_1).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Interval * first, 
		 Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    return (*CSegment_tree_1).make_tree(first,last);
  }
#endif
  
  std::back_insert_iterator<std::list<Interval> > 
    window_query(Interval const &win,  
		 std::back_insert_iterator<std::list<Interval> > result)
  {
    return (*CSegment_tree_1).window_query(win, result);
  }
  std::back_insert_iterator<std::vector<Interval> > 
    window_query(Interval const &win,  
		 std::back_insert_iterator<std::vector<Interval> > result)
  {
    return (*CSegment_tree_1).window_query(win, result);
  }
#ifdef carray
  Interval * window_query(Interval const &win,  
			  Interval *result)
  {
    return (*CSegment_tree_1).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Interval> window_query(Interval const &win,  
						     ostream_iterator<Interval> result)
  {
    return (*CSegment_tree_1).window_query(win, result);
  }
#endif
  
  std::back_insert_iterator<std::list<Interval> > 
    enclosing_query(Interval const &win,  
		    std::back_insert_iterator<std::list<Interval> > result)
  {
    return (*CSegment_tree_1).enclosing_query(win, result);
  }
  std::back_insert_iterator<std::vector<Interval> >
    enclosing_query(Interval const &win,  
                    std::back_insert_iterator<std::vector<Interval> > result)
  {
    return (*CSegment_tree_1).enclosing_query(win, result);
  }
#ifdef carray
  Interval * enclosing_query(Interval const &win,  
			     Interval *result)
  {
    return (*CSegment_tree_1).enclosing_query(win, result);
  }
#endif

#ifdef ostreamiterator
  ostream_iterator<Interval> 
    enclosing_query(Interval const &win,  
		    ostream_iterator<Interval> result)
  {
    return (*CSegment_tree_1).enclosing_query(win, result);
  }
#endif

  ~Segment_tree_1()
  {
    if (CSegment_tree_1!=0)
      delete CSegment_tree_1;
    CSegment_tree_1=0;
    if (Tree_anchor!=0)
      delete Tree_anchor;
    Tree_anchor=0;
  }
};


//-------------------------------------------------------------------
// A two dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.

template <class _Traits_2>
class Segment_tree_2
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

  typedef std::list<Interval>::iterator l_iterator;
  typedef std::vector<Interval>::iterator v_iterator;

  typedef tree_interval_traits<Interval, Interval, 
  Key_1,  low_1,  high_1, 
  low_1,  high_1, compare_1> I1; 

  typedef tree_interval_traits<Interval, Interval, 
  Key_2,  low_2,  high_2, 
  low_2,  high_2, compare_2> I2; 

  typedef tree_anchor<Interval, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef Segment_tree_d<Interval, Interval, I2> Segment_tree_1_type;
  Segment_tree_1_type * CSegment_tree_1;

  typedef Segment_tree_d<Interval, Interval, I1> Segment_tree_2_type;
  Segment_tree_2_type *CSegment_tree_2;

  Segment_tree_2()
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
  }
  Segment_tree_2(l_iterator& first, 
		   l_iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
   CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
   (*CSegment_tree_2).make_tree(first,last);
  }
#ifdef stlvector
  Segment_tree_2(v_iterator& first, 
		    v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    (*CSegment_tree_2).make_tree(first,last);
  }
#endif
#ifdef carray
  Segment_tree_2(Interval * first, 
		    Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    (*CSegment_tree_2).make_tree(first,last);
  }
#endif

  bool make_tree(l_iterator& first, 
		 l_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    return (*CSegment_tree_2).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(v_iterator& first, 
		 v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    return (*CSegment_tree_2).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Interval * first, 
		 Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    return (*CSegment_tree_2).make_tree(first,last);
  }
#endif
  
  std::back_insert_iterator<std::list<Interval> >  
    window_query(Interval const &win,  
		 std::back_insert_iterator<std::list<Interval> > result)
  {
    return (*CSegment_tree_2).window_query(win, result);
  }
  std::back_insert_iterator<std::vector<Interval> >  
    window_query(Interval const &win,  
		 std::back_insert_iterator<std::vector<Interval> > result)
  {
    return (*CSegment_tree_2).window_query(win, result);
  }
#ifdef carray
  Interval * 
    window_query(Interval const &win,  
		 Interval *result)
  {
    return (*CSegment_tree_2).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Interval>  
    window_query(Interval const &win,  
		 ostream_iterator<Interval> result)
  {
    return (*CSegment_tree_2).window_query(win, result);
  }
#endif
  
  std::back_insert_iterator<std::list<Interval> >  
    enclosing_query(Interval const &win,  
                    std::back_insert_iterator<std::list<Interval> > result)
  {
    return (*CSegment_tree_2).enclosing_query(win, result);
  }
  std::back_insert_iterator<std::vector<Interval> >  
    enclosing_query(Interval const &win,  
                    std::back_insert_iterator<std::vector<Interval> > result)
  {
    return (*CSegment_tree_2).enclosing_query(win, result);
  }
#ifdef carray
  Interval * 
    enclosing_query(Interval const &win,  
                    Interval *result)
  {
    return (*CSegment_tree_2).enclosing_query(win, result);
  }
#endif

#ifdef ostreamiterator
  ostream_iterator<Interval>  
    enclosing_query(Interval const &win,  
		    ostream_iterator<Interval> result)
  {
    return (*CSegment_tree_2).enclosing_query(win, result);
  }
#endif

  ~Segment_tree_2()
  {
    if (CSegment_tree_2!=0)
      delete CSegment_tree_2;
    CSegment_tree_2=0;
    if (CSegment_tree_1!=0)
      delete CSegment_tree_1;
    CSegment_tree_1=0;
    if (Tree_anchor!=0)
      delete Tree_anchor;
    Tree_anchor=0;
  }
};


//-------------------------------------------------------------------
// A three dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.
template <class _Traits_3>
class Segment_tree_3
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

  typedef std::list<Interval>::iterator l_iterator;
  typedef std::vector<Interval>::iterator v_iterator;

  typedef tree_interval_traits<Interval, Interval,
  Key_1,  low_1, high_1, 
  low_1, high_1,  compare_1> I1; 

  typedef tree_interval_traits<Interval, Interval, 
  Key_2,  low_2, high_2, 
  low_2, high_2,  compare_2> I2;


  typedef tree_interval_traits<Interval, Interval, 
  Key_3, low_3, high_3, 
  low_3, high_3,  compare_3> I3;


  typedef tree_anchor<Interval, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef Segment_tree_d<Interval, Interval, I3> Segment_tree_1_type;
  Segment_tree_1_type * CSegment_tree_1;

  typedef Segment_tree_d<Interval, Interval, I2> Segment_tree_2_type;
  Segment_tree_2_type *CSegment_tree_2;

  typedef Segment_tree_d<Interval, Interval, I1> Segment_tree_3_type;
  Segment_tree_3_type *CSegment_tree_3;

  Segment_tree_3()
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
  }
  Segment_tree_3(l_iterator& first, 
		     l_iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
   CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
   CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
   (*CSegment_tree_3).make_tree(first,last);
  }
#ifdef stlvector
  Segment_tree_3(v_iterator& first, 
		    v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
    (*CSegment_tree_3).make_tree(first,last);
  }
#endif
#ifdef carray
  Segment_tree_3(Interval * first, 
		    Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
    (*CSegment_tree_3).make_tree(first,last);
  }
#endif

  bool make_tree(l_iterator& first, 
		 l_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
    return (*CSegment_tree_3).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(v_iterator& first, 
		 v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
    return (*CSegment_tree_3).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Interval * first, 
		 Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
    return (*CSegment_tree_3).make_tree(first,last);
  }
#endif
  
  std::back_insert_iterator<std::list<Interval> >  
    window_query(Interval const &win,  
		 std::back_insert_iterator<std::list<Interval> > result)
  {
    return (*CSegment_tree_3).window_query(win, result);
  }
  std::back_insert_iterator<std::vector<Interval> >  
    window_query(Interval const &win,  
		 std::back_insert_iterator<std::vector<Interval> > result)
  {
    return (*CSegment_tree_3).window_query(win, result);
  }
#ifdef carray
  Interval * 
    window_query(Interval const &win,  
		 Interval *result)
  {
    return (*CSegment_tree_3).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Interval>  
    window_query(Interval const &win,  
		 ostream_iterator<Interval> result)
  {
    return (*CSegment_tree_3).window_query(win, result);
  }
#endif
  
  std::back_insert_iterator<std::list<Interval> >  
    enclosing_query(Interval const &win,  
                    std::back_insert_iterator<std::list<Interval> > result)
  {
    return (*CSegment_tree_3).enclosing_query(win, result);
  }
  std::back_insert_iterator<std::vector<Interval> >  
    enclosing_query(Interval const &win,  
                    std::back_insert_iterator<std::vector<Interval> > result)
  {
    return (*CSegment_tree_3).enclosing_query(win, result);
  }
#ifdef carray
  Interval * 
    enclosing_query(Interval const &win,  
                    Interval *result)
  {
    return (*CSegment_tree_3).enclosing_query(win, result);
  }
#endif

#ifdef ostreamiterator
  ostream_iterator<Interval>  
    enclosing_query(Interval const &win,  
		    ostream_iterator<Interval> result)
  {
    return (*CSegment_tree_3).enclosing_query(win, result);
  }
#endif

  ~Segment_tree_3()
  {
    if (CSegment_tree_3!=0)
      delete CSegment_tree_3;
    CSegment_tree_3=0;
    if (CSegment_tree_2!=0)
      delete CSegment_tree_2;
    CSegment_tree_2=0;
    if (CSegment_tree_1!=0)
      delete CSegment_tree_1;
    CSegment_tree_1=0;
    if (Tree_anchor!=0)
      delete Tree_anchor;
    Tree_anchor=0;
  }
};


//-------------------------------------------------------------------
// A three dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.
template <class _Traits_4>
class Segment_tree_4
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

  typedef std::list<Interval>::iterator l_iterator;
  typedef std::vector<Interval>::iterator v_iterator;

  typedef tree_interval_traits<Interval, Interval, 
  Key_1, low_1,  high_1, low_1,
  high_1,  compare_1> I1;

  typedef tree_interval_traits<Interval, Interval, 
  Key_2, low_2,  high_2,  low_2,
  high_2,  compare_2> I2; 


  typedef tree_interval_traits<Interval, Interval, 
  Key_3, low_3,  high_3,  low_3,
  high_3,  compare_3> I3; 


  typedef tree_interval_traits<Interval, Interval, 
  Key_4,   low_4,  high_4,  low_4,
  high_4,  compare_4> I4; 


  typedef tree_anchor<Interval, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef Segment_tree_d<Interval, Interval, I4> Segment_tree_1_type;
  Segment_tree_1_type * CSegment_tree_1;

  typedef Segment_tree_d<Interval, Interval, I3> Segment_tree_2_type;
  Segment_tree_2_type *CSegment_tree_2;

  typedef Segment_tree_d<Interval, Interval, I2> Segment_tree_3_type;
  Segment_tree_3_type *CSegment_tree_3;

  typedef Segment_tree_d<Interval, Interval, I1> Segment_tree_4_type;
  Segment_tree_4_type *CSegment_tree_4;

  Segment_tree_4()
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
    CSegment_tree_4 = new Segment_tree_4_type(*CSegment_tree_3);
  }
  Segment_tree_4(l_iterator& first, 
		     l_iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
   CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
   CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
   CSegment_tree_4 = new Segment_tree_4_type(*CSegment_tree_3);
   (*CSegment_tree_4).make_tree(first,last);
  }
#ifdef stlvector
  Segment_tree_4(v_iterator& first, 
		    v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
    CSegment_tree_4 = new Segment_tree_4_type(*CSegment_tree_3);
    (*CSegment_tree_4).make_tree(first,last);
  }
#endif
#ifdef carray
  Segment_tree_4(Interval * first, 
		    Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
    CSegment_tree_4 = new Segment_tree_4_type(*CSegment_tree_3);
    (*CSegment_tree_4).make_tree(first,last);
  }
#endif

  bool make_tree(l_iterator& first, 
		 l_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
    CSegment_tree_4 = new Segment_tree_4_type(*CSegment_tree_3);
    return (*CSegment_tree_4).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(v_iterator& first, 
		 v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
    CSegment_tree_4 = new Segment_tree_4_type(*CSegment_tree_3);
    return (*CSegment_tree_4).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Interval * first, 
		 Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    CSegment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    CSegment_tree_2 = new Segment_tree_2_type(*CSegment_tree_1);
    CSegment_tree_3 = new Segment_tree_3_type(*CSegment_tree_2);
    CSegment_tree_4 = new Segment_tree_4_type(*CSegment_tree_3);
    return (*CSegment_tree_4).make_tree(first,last);
  }
#endif
  
  std::back_insert_iterator<std::list<Interval> >  
    window_query(Interval const &win,  
		 std::back_insert_iterator<std::list<Interval> > result)
  {
    return (*CSegment_tree_4).window_query(win, result);
  }
  std::back_insert_iterator<std::vector<Interval> >  
    window_query(Interval const &win,  
		 std::back_insert_iterator<std::vector<Interval> > result)
  {
    return (*CSegment_tree_4).window_query(win, result);
  }
#ifdef carray
  Interval * 
    window_query(Interval const &win,  
		 Interval *result)
  {
    return (*CSegment_tree_4).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Interval>  
    window_query(Interval const &win,  
		 ostream_iterator<Interval> result)
  {
    return (*CSegment_tree_4).window_query(win, result);
  }
#endif
  
  std::back_insert_iterator<std::list<Interval> >  
    enclosing_query(Interval const &win,  
                    std::back_insert_iterator<std::list<Interval> > result)
  {
    return (*CSegment_tree_4).enclosing_query(win, result);
  }
  std::back_insert_iterator<std::vector<Interval> >  
    enclosing_query(Interval const &win,  
                    std::back_insert_iterator<std::vector<Interval> > result)
  {
    return (*CSegment_tree_4).enclosing_query(win, result);
  }
#ifdef carray
  Interval * 
    enclosing_query(Interval const &win,  
                    Interval *result)
  {
    return (*CSegment_tree_4).enclosing_query(win, result);
  }
#endif

#ifdef ostreamiterator
  ostream_iterator<Interval>  
    enclosing_query(Interval const &win,  
		    ostream_iterator<Interval> result)
  {
    return (*CSegment_tree_4).enclosing_query(win, result);
  }
#endif

  ~Segment_tree_4()
  {
    if (CSegment_tree_4!=0)
      delete CSegment_tree_4;
    CSegment_tree_4=0;
    if (CSegment_tree_3!=0)
      delete CSegment_tree_3;
    CSegment_tree_3=0;
    if (CSegment_tree_2!=0)
      delete CSegment_tree_2;
    CSegment_tree_2=0;
    if (CSegment_tree_1!=0)
      delete CSegment_tree_1;
    CSegment_tree_1=0;
    if (Tree_anchor!=0)
      delete Tree_anchor;
    Tree_anchor=0;
  }
};
CGAL_END_NAMESPACE
#endif
