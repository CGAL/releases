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


// file  : include/CGAL/Segment_tree_Iso_rectangle_2.h
// source: include/CGAL/Segment_tree_Iso_rectangle_2.h
// author: Gabriele Neyer
// $Revision: 1.2 $
// $Date: 1997/05/21 14:54:12 $

#ifndef __CGAL_Segment_tree_Iso_rectangle_2__
#define __CGAL_Segment_tree_Iso_rectangle_2__

#include <CGAL/Point_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Segment_tree_d.h>
#include <CGAL/Compare_adaptor.h>
#include <CGAL/Member_function_pointer.h>


#ifdef CGAL_TEMPLATE_FUNCTION_POINTER_WORKAROUND
// Interface as it is expected for one layer of a Segment Tree
template<class _Data, class _Key,  
         class _Data_left_func, class _Data_right_func, 
	 class _Compare>
class CGAL_tree_interval_Iso_rectangle_2_interface{
 public:
  typedef _Data Data;
  typedef _Data Window;
  typedef _Key Key;
  typedef _Compare Compare;

  _Key get_left(_Data dt)
    const {return (dt.*_Data_left_func::member())();}
  _Key get_right(_Data dt)
    const {return (dt.*_Data_right_func::member())();}
  _Key get_left_win(_Data dt)
    const {return (dt.*_Data_left_func::member())();}
  _Key get_right_win(_Data dt)
    const {return (dt.*_Data_right_func::member())();}
  static bool comp(_Key const& key1, _Key const& key2)
    {return _Compare()(key1, key2);} 
};

#else
// Interface as it is expected for one layer of a Segment Tree
template<class _Data, class _Key,  
  _Key (_Data::*_Data_left_func)() const, 
  _Key (_Data::*_Data_right_func)() const,
  class _Compare>
class CGAL_tree_interval_Iso_rectangle_2_interface{
 public:
  typedef _Data Data;
  typedef _Data Window;
  typedef _Key Key;
  typedef _Compare Compare;
  
  _Key get_left(_Data dt)
    const {return (dt.*_Data_left_func)();}
  _Key get_right(_Data dt)
    const {return (dt.*_Data_right_func)();}
  _Key get_left_win(_Data dt)
    const {return (dt.*_Data_left_func)();}
  _Key get_right_win(_Data dt)
    const {return (dt.*_Data_right_func)();}

  static bool comp(_Key const& key1, _Key const& key2) 
    {return _Compare()(key1, key2);} 
};
#endif


//-------------------------------------------------------------------
// A two dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.

template <class _R>
class CGAL_Segment_tree_Iso_rectangle_2
{ 
public:
  typedef _R R;
  typedef CGAL_Iso_rectangle_2<R> Interval_2;
  typedef CGAL_Point_2<R> Point_2;
  typedef CGAL_Point_key_compare_2<Point_2> Compare;

  CGAL_Member_function_pointer(low_key_ptr, Interval_2, Point_2, min)
  CGAL_Member_function_pointer(high_key_ptr, Interval_2, Point_2, max)

  typedef CGAL_tree_interval_Iso_rectangle_2_interface<Interval_2, Point_2, 
    CGAL_Use_member_function_pointer(low_key_ptr, Interval_2, Interval_2::T1, low_1),
    CGAL_Use_member_function_pointer(high_key_ptr, Interval_2, Interval_2::T1, high_1),
    Compare::C1> I1; 

  typedef CGAL_tree_interval_Iso_rectangle_2_interface<Interval_2, Point_2, 
    CGAL_Use_member_function_pointer(low_key_ptr, Interval_2, Interval_2::T1, low_1),
    CGAL_Use_member_function_pointer(high_key_ptr, Interval_2, Interval_2::T1, high_1),
    Compare::C2> I2; 



  typedef CGAL_tree_anchor<Interval_2, Interval_2> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef CGAL_Segment_tree_d<Interval_2, Interval_2, I2> Segment_tree_1_type;
  Segment_tree_1_type * Segment_tree_1;

  typedef CGAL_Segment_tree_d<Interval_2, Interval_2, I1> Segment_tree_2_type;
  Segment_tree_2_type *Segment_tree_2;


  CGAL_Segment_tree_Iso_rectangle_2()
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
  }

 CGAL_Segment_tree_Iso_rectangle_2(list<Interval_2>::iterator& first, 
		   list<Interval_2>::iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
   Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
   (*Segment_tree_2).make_tree(first,last);
  }
#ifdef stlvector
  CGAL_Segment_tree_Iso_rectangle_2(vector<Interval_2>::iterator& first, 
		    vector<Interval_2>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    (*Segment_tree_2).make_tree(first,last);
  }
#endif
#ifdef carray
  CGAL_Segment_tree_Iso_rectangle_2(Interval_2 * first, 
		    Interval_2 * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    (*Segment_tree_2).make_tree(first,last);
  }
#endif

  bool make_tree(list<Interval_2>::iterator& first, 
		 list<Interval_2>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    return (*Segment_tree_2).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(vector<Interval_2>::iterator& first, 
		 vector<Interval_2>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    return (*Segment_tree_2).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Interval_2 * first, 
		 Interval_2 * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Segment_tree_1 = new Segment_tree_1_type(*Tree_anchor);
    Segment_tree_2 = new Segment_tree_2_type(*Segment_tree_1);
    return (*Segment_tree_2).make_tree(first,last);
  }
#endif
  
  void window_query(Interval_2 const &win,  
                    back_insert_iterator<list<Interval_2> > result)
  {
    (*Segment_tree_2).window_query(win, result);
  }
  void window_query(Interval_2 const &win,  
                    back_insert_iterator<vector<Interval_2> > result)
  {
    (*Segment_tree_2).window_query(win, result);
  }
#ifdef carray
  void window_query(Interval_2 const &win,  
                    Interval_2 *result)
  {
    (*Segment_tree_2).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  void window_query(Interval_2 const &win,  
                    ostream_iterator<Interval_2> result)
  {
    (*Segment_tree_2).window_query(win, result);
  }
#endif
  
  void enclosing_query(Interval_2 const &win,  
                    back_insert_iterator<list<Interval_2> > result)
  {
    (*Segment_tree_2).enclosing_query(win, result);
  }
  void enclosing_query(Interval_2 const &win,  
                    back_insert_iterator<vector<Interval_2> > result)
  {
    (*Segment_tree_2).enclosing_query(win, result);
  }
#ifdef carray
  void enclosing_query(Interval_2 const &win,  
                    Interval_2 *result)
  {
    (*Segment_tree_2).enclosing_query(win, result);
  }
#endif

#ifdef ostreamiterator
  void enclosing_query(Interval_2 const &win,  
		       ostream_iterator<Interval_2> result)
  {
    (*Segment_tree_2).enclosing_query(win, result);
  }
#endif
  ~CGAL_Segment_tree_Iso_rectangle_2()
  {
    delete Segment_tree_2;
    delete Segment_tree_1;
    delete Tree_anchor;
  }

};

#endif
