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


// file  : include/CGAL/Segment_tree_pre.h
// source: include/CGAL/Segment_tree_pre.h
// author: Gabriele Neyer
// $Revision: 1.2 $
// $Date: 1997/06/16 13:41:12 $

#ifndef __CGAL_Segment_tree_pre__
#define __CGAL_Segment_tree_pre__

// Predefined k-dimensional Segment Trees (k=1..4) 
// The trees can either be templated with d arbitrary types
// (e.g., CGAL_Segment_tree_3) 
// or with an unary type for each dimension
// (e.g., CGAL_Segment_tree_uni_4).
// The container class and sequence container class as well as the 
// data accessors are defined in these classes.

#include <iostream.h>
#include <iterator.h>
#include <list.h>
#include <CGAL/Tree_base.h>
#include <CGAL/Tree_traits.h>
#include <CGAL/Segment_tree_d.h>

template <class _Traits_1>
class CGAL_Segment_tree_1
{ 
public:
  typedef _Traits_1 Traits;
  typedef _Traits_1::Key Key;
  typedef _Traits_1::Interval Interval;
  typedef _Traits_1::Key_1 Key_1;
  typedef _Traits_1::key_1 key_1;
  typedef _Traits_1::low_1 low_1;
  typedef _Traits_1::high_1 high_1;
  typedef _Traits_1::compare_1 compare_1;

  typedef CGAL_tree_interval_traits<Interval, Interval, 
  Key_1,  low_1, high_1, low_1, 
  high_1, compare_1> I1; 


  typedef CGAL_tree_anchor<Interval, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef CGAL_Segment_tree_d<Interval, Interval, I1> Segment_tree_1_type;
  Segment_tree_1_type * Segment_tree_1;


  CGAL_Segment_tree_1()
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
  }
  
  typedef list<Interval>::iterator l_iterator;
  CGAL_Segment_tree_1(l_iterator& first, 
		     l_iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
   (*Segment_tree_1).make_tree(first,last);
  }
#ifdef stlvector
  typedef v_iterator v_iterator;
  CGAL_Segment_tree_1(v_iterator& first, 
		      v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    (*Segment_tree_1).make_tree(first,last);
  }
#endif
#ifdef carray
  CGAL_Segment_tree_1(Interval * first, 
		      Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    (*Segment_tree_1).make_tree(first,last);
  }
#endif

  bool make_tree(l_iterator& first, 
		 l_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    return (*Segment_tree_1).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(v_iterator& first, 
		 v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    return (*Segment_tree_1).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Interval * first, 
		 Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    return (*Segment_tree_1).make_tree(first,last);
  }
#endif
  
  back_insert_iterator<list<Interval> > 
    window_query(Interval const &win,  
		 back_insert_iterator<list<Interval> > result)
  {
    return (*Segment_tree_1).window_query(win, result);
  }
  back_insert_iterator<vector<Interval> > 
    window_query(Interval const &win,  
		 back_insert_iterator<vector<Interval> > result)
  {
    return (*Segment_tree_1).window_query(win, result);
  }
#ifdef carray
  Interval * window_query(Interval const &win,  
			  Interval *result)
  {
    return (*Segment_tree_1).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Interval> window_query(Interval const &win,  
						     ostream_iterator<Interval> result)
  {
    return (*Segment_tree_1).window_query(win, result);
  }
#endif
  
  back_insert_iterator<list<Interval> > 
    enclosing_query(Interval const &win,  
		    back_insert_iterator<list<Interval> > result)
  {
    return (*Segment_tree_1).enclosing_query(win, result);
  }
  back_insert_iterator<vector<Interval> >
    enclosing_query(Interval const &win,  
                    back_insert_iterator<vector<Interval> > result)
  {
    return (*Segment_tree_1).enclosing_query(win, result);
  }
#ifdef carray
  Interval * enclosing_query(Interval const &win,  
			     Interval *result)
  {
    return (*Segment_tree_1).enclosing_query(win, result);
  }
#endif

#ifdef ostreamiterator
  ostream_iterator<Interval> 
    enclosing_query(Interval const &win,  
		    ostream_iterator<Interval> result)
  {
    return (*Segment_tree_1).enclosing_query(win, result);
  }
#endif

  ~CGAL_Segment_tree_1()
  {
    delete Segment_tree_1;
    delete Tree_anchor;
  }

};


//-------------------------------------------------------------------
// A two dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.

template <class _Traits_2>
class CGAL_Segment_tree_2
{ 
public:
  typedef _Traits_2 Traits;
  typedef _Traits_2::Key Key;
  typedef _Traits_2::Interval Interval;
  typedef _Traits_2::Key_2 Key_2;
  typedef _Traits_2::Key_1 Key_1;
  typedef _Traits_2::key_1 key_1;
  typedef _Traits_2::key_2 key_2;
  typedef _Traits_2::low_1 low_1;
  typedef _Traits_2::high_1 high_1;
  typedef _Traits_2::low_2 low_2;
  typedef _Traits_2::high_2 high_2;
  typedef _Traits_2::compare_1 compare_1;
  typedef _Traits_2::compare_2 compare_2;

  typedef list<Interval>::iterator l_iterator;
  typedef vector<Interval>::iterator v_iterator;

  typedef CGAL_tree_interval_traits<Interval, Interval, 
  Key_1,  low_1,  high_1, 
  low_1,  high_1, compare_1> I1; 

  typedef CGAL_tree_interval_traits<Interval, Interval, 
  Key_2,  low_2,  high_2, 
  low_2,  high_2, compare_2> I2; 

  typedef CGAL_tree_anchor<Interval, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef CGAL_Segment_tree_d<Interval, Interval, I2> Segment_tree_1_type;
  Segment_tree_1_type * Segment_tree_1;

  typedef CGAL_Segment_tree_d<Interval, Interval, I1> Segment_tree_2_type;
  Segment_tree_2_type *Segment_tree_2;

  CGAL_Segment_tree_2()
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
  }
 CGAL_Segment_tree_2(l_iterator& first, 
		   l_iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
   Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
   (*Segment_tree_2).make_tree(first,last);
  }
#ifdef stlvector
  CGAL_Segment_tree_2(v_iterator& first, 
		    v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    (*Segment_tree_2).make_tree(first,last);
  }
#endif
#ifdef carray
  CGAL_Segment_tree_2(Interval * first, 
		    Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    (*Segment_tree_2).make_tree(first,last);
  }
#endif

  bool make_tree(l_iterator& first, 
		 l_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    return (*Segment_tree_2).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(v_iterator& first, 
		 v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    return (*Segment_tree_2).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Interval * first, 
		 Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    return (*Segment_tree_2).make_tree(first,last);
  }
#endif
  
  back_insert_iterator<list<Interval> >  
    window_query(Interval const &win,  
		 back_insert_iterator<list<Interval> > result)
  {
    return (*Segment_tree_2).window_query(win, result);
  }
  back_insert_iterator<vector<Interval> >  
    window_query(Interval const &win,  
		 back_insert_iterator<vector<Interval> > result)
  {
    return (*Segment_tree_2).window_query(win, result);
  }
#ifdef carray
  Interval * 
    window_query(Interval const &win,  
		 Interval *result)
  {
    return (*Segment_tree_2).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Interval>  
    window_query(Interval const &win,  
		 ostream_iterator<Interval> result)
  {
    return (*Segment_tree_2).window_query(win, result);
  }
#endif
  
  back_insert_iterator<list<Interval> >  
    enclosing_query(Interval const &win,  
                    back_insert_iterator<list<Interval> > result)
  {
    return (*Segment_tree_2).enclosing_query(win, result);
  }
  back_insert_iterator<vector<Interval> >  
    enclosing_query(Interval const &win,  
                    back_insert_iterator<vector<Interval> > result)
  {
    return (*Segment_tree_2).enclosing_query(win, result);
  }
#ifdef carray
  Interval * 
    enclosing_query(Interval const &win,  
                    Interval *result)
  {
    return (*Segment_tree_2).enclosing_query(win, result);
  }
#endif

#ifdef ostreamiterator
  ostream_iterator<Interval>  
    enclosing_query(Interval const &win,  
		    ostream_iterator<Interval> result)
  {
    return (*Segment_tree_2).enclosing_query(win, result);
  }
#endif

  ~CGAL_Segment_tree_2()
  {
    delete Segment_tree_2;
    delete Segment_tree_1;
    delete Tree_anchor;
  }
};


//-------------------------------------------------------------------
// A three dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.
template <class _Traits_3>
class CGAL_Segment_tree_3
{ 
public:
  typedef _Traits_3 Traits;
  typedef _Traits_3::Key Key;
  typedef _Traits_3::Interval Interval;
  typedef _Traits_3::Key_1 Key_1;
  typedef _Traits_3::Key_2 Key_2;
  typedef _Traits_3::Key_3 Key_3;
  typedef _Traits_3::key_1 key_1;
  typedef _Traits_3::key_2 key_2;
  typedef _Traits_3::key_3 key_3;
  typedef _Traits_3::low_1 low_1;
  typedef _Traits_3::high_1 high_1;
  typedef _Traits_3::low_2 low_2;
  typedef _Traits_3::high_2 high_2;
  typedef _Traits_3::low_3 low_3;
  typedef _Traits_3::high_3 high_3;
  typedef _Traits_3::compare_1 compare_1;
  typedef _Traits_3::compare_2 compare_2;
  typedef _Traits_3::compare_3 compare_3;

  typedef list<Interval>::iterator l_iterator;
  typedef vector<Interval>::iterator v_iterator;

  typedef CGAL_tree_interval_traits<Interval, Interval,
  Key_1,  low_1, high_1, 
  low_1, high_1,  compare_1> I1; 

  typedef CGAL_tree_interval_traits<Interval, Interval, 
  Key_2,  low_2, high_2, 
  low_2, high_2,  compare_2> I2;


  typedef CGAL_tree_interval_traits<Interval, Interval, 
  Key_3, low_3, high_3, 
  low_3, high_3,  compare_3> I3;


  typedef CGAL_tree_anchor<Interval, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef CGAL_Segment_tree_d<Interval, Interval, I3> Segment_tree_1_type;
  Segment_tree_1_type * Segment_tree_1;

  typedef CGAL_Segment_tree_d<Interval, Interval, I2> Segment_tree_2_type;
  Segment_tree_2_type *Segment_tree_2;

  typedef CGAL_Segment_tree_d<Interval, Interval, I1> Segment_tree_3_type;
  Segment_tree_3_type *Segment_tree_3;

  CGAL_Segment_tree_3()
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
  }
 CGAL_Segment_tree_3(l_iterator& first, 
		     l_iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
   Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
   Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
   (*Segment_tree_3).make_tree(first,last);
  }
#ifdef stlvector
  CGAL_Segment_tree_3(v_iterator& first, 
		    v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
    (*Segment_tree_3).make_tree(first,last);
  }
#endif
#ifdef carray
  CGAL_Segment_tree_3(Interval * first, 
		    Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
    (*Segment_tree_3).make_tree(first,last);
  }
#endif

  bool make_tree(l_iterator& first, 
		 l_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
    return (*Segment_tree_3).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(v_iterator& first, 
		 v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
    return (*Segment_tree_3).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Interval * first, 
		 Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
    return (*Segment_tree_3).make_tree(first,last);
  }
#endif
  
  back_insert_iterator<list<Interval> >  
    window_query(Interval const &win,  
		 back_insert_iterator<list<Interval> > result)
  {
    return (*Segment_tree_3).window_query(win, result);
  }
  back_insert_iterator<vector<Interval> >  
    window_query(Interval const &win,  
		 back_insert_iterator<vector<Interval> > result)
  {
    return (*Segment_tree_3).window_query(win, result);
  }
#ifdef carray
  Interval * 
    window_query(Interval const &win,  
		 Interval *result)
  {
    return (*Segment_tree_3).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Interval>  
    window_query(Interval const &win,  
		 ostream_iterator<Interval> result)
  {
    return (*Segment_tree_3).window_query(win, result);
  }
#endif
  
  back_insert_iterator<list<Interval> >  
    enclosing_query(Interval const &win,  
                    back_insert_iterator<list<Interval> > result)
  {
    return (*Segment_tree_3).enclosing_query(win, result);
  }
  back_insert_iterator<vector<Interval> >  
    enclosing_query(Interval const &win,  
                    back_insert_iterator<vector<Interval> > result)
  {
    return (*Segment_tree_3).enclosing_query(win, result);
  }
#ifdef carray
  Interval * 
    enclosing_query(Interval const &win,  
                    Interval *result)
  {
    return (*Segment_tree_3).enclosing_query(win, result);
  }
#endif

#ifdef ostreamiterator
  ostream_iterator<Interval>  
    enclosing_query(Interval const &win,  
		    ostream_iterator<Interval> result)
  {
    return (*Segment_tree_3).enclosing_query(win, result);
  }
#endif

  ~CGAL_Segment_tree_3()
  {
    delete Segment_tree_3;
    delete Segment_tree_2;
    delete Segment_tree_1;
    delete Tree_anchor;
  }
};


//-------------------------------------------------------------------
// A three dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.
template <class _Traits_4>
class CGAL_Segment_tree_4
{ 
public:
  typedef _Traits_4 Traits;
  typedef _Traits_4::Key Key;
  typedef _Traits_4::Interval Interval;
  typedef _Traits_4::Key_1 Key_1;
  typedef _Traits_4::Key_2 Key_2;
  typedef _Traits_4::Key_3 Key_3;
  typedef _Traits_4::Key_4 Key_4;
  typedef _Traits_4::key_1 key_1;
  typedef _Traits_4::key_2 key_2;
  typedef _Traits_4::key_4 key_4;
  typedef _Traits_4::key_3 key_3;
  typedef _Traits_4::low_1 low_1;
  typedef _Traits_4::high_1 high_1;
  typedef _Traits_4::low_2 low_2;
  typedef _Traits_4::high_2 high_2;
  typedef _Traits_4::low_3 low_3;
  typedef _Traits_4::high_3 high_3;
  typedef _Traits_4::low_4 low_4;
  typedef _Traits_4::high_4 high_4;
  typedef _Traits_4::compare_1 compare_1;
  typedef _Traits_4::compare_2 compare_2;
  typedef _Traits_4::compare_3 compare_3;
  typedef _Traits_4::compare_4 compare_4;

  typedef list<Interval>::iterator l_iterator;
  typedef vector<Interval>::iterator v_iterator;

  typedef CGAL_tree_interval_traits<Interval, Interval, 
  Key_1, low_1,  high_1, low_1,
  high_1,  compare_1> I1;

  typedef CGAL_tree_interval_traits<Interval, Interval, 
  Key_2, low_2,  high_2,  low_2,
  high_2,  compare_2> I2; 


  typedef CGAL_tree_interval_traits<Interval, Interval, 
  Key_3, low_3,  high_3,  low_3,
  high_3,  compare_3> I3; 


  typedef CGAL_tree_interval_traits<Interval, Interval, 
  Key_4,   low_4,  high_4,  low_4,
  high_4,  compare_4> I4; 


  typedef CGAL_tree_anchor<Interval, Interval> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef CGAL_Segment_tree_d<Interval, Interval, I4> Segment_tree_1_type;
  Segment_tree_1_type * Segment_tree_1;

  typedef CGAL_Segment_tree_d<Interval, Interval, I3> Segment_tree_2_type;
  Segment_tree_2_type *Segment_tree_2;

  typedef CGAL_Segment_tree_d<Interval, Interval, I2> Segment_tree_3_type;
  Segment_tree_3_type *Segment_tree_3;

  typedef CGAL_Segment_tree_d<Interval, Interval, I1> Segment_tree_4_type;
  Segment_tree_4_type *Segment_tree_4;

  CGAL_Segment_tree_4()
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
    Segment_tree_4 = new Segment_tree_4_type(*Segment_tree_3);
  }
 CGAL_Segment_tree_4(l_iterator& first, 
		     l_iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
   Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
   Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
   Segment_tree_4 = new Segment_tree_4_type(*Segment_tree_3);
   (*Segment_tree_4).make_tree(first,last);
  }
#ifdef stlvector
  CGAL_Segment_tree_4(v_iterator& first, 
		    v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
    Segment_tree_4 = new Segment_tree_4_type(*Segment_tree_3);
    (*Segment_tree_4).make_tree(first,last);
  }
#endif
#ifdef carray
  CGAL_Segment_tree_4(Interval * first, 
		    Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
    Segment_tree_4 = new Segment_tree_4_type(*Segment_tree_3);
    (*Segment_tree_4).make_tree(first,last);
  }
#endif

  bool make_tree(l_iterator& first, 
		 l_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
    Segment_tree_4 = new Segment_tree_4_type(*Segment_tree_3);
    return (*Segment_tree_4).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(v_iterator& first, 
		 v_iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
    Segment_tree_4 = new Segment_tree_4_type(*Segment_tree_3);
    return (*Segment_tree_4).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Interval * first, 
		 Interval * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    Segment_tree_3 = new Segment_tree_3_type(*Segment_tree_2);
    Segment_tree_4 = new Segment_tree_4_type(*Segment_tree_3);
    return (*Segment_tree_4).make_tree(first,last);
  }
#endif
  
  back_insert_iterator<list<Interval> >  
    window_query(Interval const &win,  
		 back_insert_iterator<list<Interval> > result)
  {
    return (*Segment_tree_4).window_query(win, result);
  }
  back_insert_iterator<vector<Interval> >  
    window_query(Interval const &win,  
		 back_insert_iterator<vector<Interval> > result)
  {
    return (*Segment_tree_4).window_query(win, result);
  }
#ifdef carray
  Interval * 
    window_query(Interval const &win,  
		 Interval *result)
  {
    return (*Segment_tree_4).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  ostream_iterator<Interval>  
    window_query(Interval const &win,  
		 ostream_iterator<Interval> result)
  {
    return (*Segment_tree_4).window_query(win, result);
  }
#endif
  
  back_insert_iterator<list<Interval> >  
    enclosing_query(Interval const &win,  
                    back_insert_iterator<list<Interval> > result)
  {
    return (*Segment_tree_4).enclosing_query(win, result);
  }
  back_insert_iterator<vector<Interval> >  
    enclosing_query(Interval const &win,  
                    back_insert_iterator<vector<Interval> > result)
  {
    return (*Segment_tree_4).enclosing_query(win, result);
  }
#ifdef carray
  Interval * 
    enclosing_query(Interval const &win,  
                    Interval *result)
  {
    return (*Segment_tree_4).enclosing_query(win, result);
  }
#endif

#ifdef ostreamiterator
  ostream_iterator<Interval>  
    enclosing_query(Interval const &win,  
		    ostream_iterator<Interval> result)
  {
    return (*Segment_tree_4).enclosing_query(win, result);
  }
#endif

  ~CGAL_Segment_tree_4()
  {
    delete Segment_tree_4;
    delete Segment_tree_2;
    delete Segment_tree_1;
    delete Tree_anchor;
  }
};

#endif
