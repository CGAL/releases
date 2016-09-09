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


// file  : include/CGAL/Range_tree_Point_2.h
// source: include/CGAL/Range_tree_Point_2.h
// author: Gabriele Neyer
// $Revision: 1.2 $
// $Date: 1997/05/21 14:54:09 $

#ifndef __CGAL_Range_tree_Point_2__
#define __CGAL_Range_tree_Point_2__

#include <CGAL/Point_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Range_tree_d.h>
#include <CGAL/Compare_adaptor.h>
#include <CGAL/Member_function_pointer.h>


#ifdef CGAL_TEMPLATE_FUNCTION_POINTER_WORKAROUND

// Interface as it is expected for one layer of a Range Tree
template<class _Data, class _Window, class _Key,  
         class _Window_left_func, 
         class _Window_right_func, class _Compare>
class CGAL_tree_point_Point_2_interface
{
 public:
  typedef _Data Data;
  typedef _Window Window;
  typedef _Key Key;
  typedef _Compare Compare;
  
  _Key get_key(_Data dt)
    const {return dt;}
  _Key get_left(_Window dt)
    const {return (dt.*_Window_left_func::member())();}
  _Key get_right(_Window dt)
    const {return (dt.*_Window_right_func::member())();}

  static bool comp(_Key const& key1, _Key const& key2)
    {return _Compare()(key1, key2);} 
  static bool key_comp(_Data const& data1, _Data const& data2)
    {return _Compare()(data1,data2);}
};

#else


// Interface as it is expected for one layer of a Range Tree
template<class _Data, class _Window, class _Key, 
 _Key (_Window::*_Window_left_func)() const,
 _Key (_Window::*_Window_right_func)() const, class _Compare>
class CGAL_tree_point_interface
{
 public:
  typedef _Data Data;
  typedef _Window Window;
  typedef _Key Key;
  typedef _Compare Compare;
  
  _Key get_key(_Data dt)
    const {return dt;}
  _Key get_left(_Window dt)
    const {return (dt.*_Window_left_func)();}
  _Key get_right(_Window dt)
    const {return (dt.*_Window_right_func)();}

  static bool comp(_Key const& key1, _Key const& key2) 
    {return _Compare()(key1, key2);} 
  static bool key_comp(_Data const& data1, _Data const& data2)
    {
      return _Compare()(d1,d2);
    }
};

#endif


//-------------------------------------------------------------------
// A two dimensional Range Tree is defined in this class.
// Ti is the type of each dimension of the tree.

template <class _R>
class CGAL_Range_tree_Point_2
{ 
public:
  typedef _R R;
  typedef CGAL_Point_2<R> Point_2;
  typedef CGAL_Iso_rectangle_2<R> Interval_2;
  typedef CGAL_Point_key_compare_2<Point_2> Compare;

   CGAL_Member_function_pointer(low_key1_ptr, Interval_2, Point_2, min)
   CGAL_Member_function_pointer(high_key1_ptr, Interval_2, Point_2, max)

  typedef CGAL_tree_point_Point_2_interface<Point_2, Interval_2, Point_2, 
     CGAL_Use_member_function_pointer(low_key1_ptr, Interval_2, Point_2, min),
     CGAL_Use_member_function_pointer(high_key1_ptr, Interval_2, Point_2, max),
   Compare::C1> I1;

  typedef CGAL_tree_point_Point_2_interface<Point_2, Interval_2, Point_2, 
   CGAL_Use_member_function_pointer(low_key1_ptr, Interval_2, Point_2, min),
   CGAL_Use_member_function_pointer(high_key1_ptr, Interval_2, Point_2, max),
   Compare::C2> I2;


  typedef CGAL_tree_anchor<Point_2, Interval_2> Tree_anchor_type;
  Tree_anchor_type *Tree_anchor;

  typedef CGAL_Range_tree_d<Point_2, Interval_2, I2> Range_tree_1_type;
  Range_tree_1_type *Range_tree_1;

  typedef CGAL_Range_tree_d<Point_2, Interval_2, I1> Range_tree_2_type;
  Range_tree_2_type *Range_tree_2;

  CGAL_Range_tree_Point_2()
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
  }
 CGAL_Range_tree_Point_2(list<Point_2>::iterator& first, 
			 list<Point_2>::iterator& last)  {
   Tree_anchor = new Tree_anchor_type;
   Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
   Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
   (*Range_tree_2).make_tree(first,last);
  }
#ifdef stlvector
  CGAL_Range_tree_Point_2(vector<Point_2>::iterator& first, 
			  vector<Point_2>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    (*Range_tree_2).make_tree(first,last);
  }
#endif
#ifdef carray
  CGAL_Range_tree_Point_2(Point_2 * first, 
			  Point_2 * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    (*Range_tree_2).make_tree(first,last);
  }
#endif

  bool make_tree(list<Point_2>::iterator& first, 
		 list<Point_2>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    return (*Range_tree_2).make_tree(first,last);
  }
#ifdef stlvector
  bool make_tree(vector<Point_2>::iterator& first, 
		 vector<Point_2>::iterator& last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    return (*Range_tree_2).make_tree(first,last);
  }
#endif
#ifdef carray
  bool make_tree(Point_2 * first, 
		 Point_2 * last)
  {
    Tree_anchor = new Tree_anchor_type;
    Range_tree_1 = new Range_tree_1_type(*Tree_anchor);
    Range_tree_2 = new Range_tree_2_type(*Range_tree_1);
    return (*Range_tree_2).make_tree(first,last);
  }
#endif
  
  void window_query(Interval_2 const &win,  
                    back_insert_iterator<list<Point_2> > result)
  {
    (*Range_tree_2).window_query(win, result);
  }
  void window_query(Interval_2 const &win,  
                    back_insert_iterator<vector<Point_2> > result)
  {
    (*Range_tree_2).window_query(win, result);
  }
#ifdef carray
  void window_query(Interval_2 const &win,  
                    Point_2 *result)
  {
    (*Range_tree_2).window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  void window_query(Interval_2 const &win,  
                    ostream_iterator<Point_2> result)
  {
    (*Range_tree_2).window_query(win, result);
  }
#endif

  ~CGAL_Range_tree_Point_2()
  {
    delete Range_tree_1;  
    delete Range_tree_2;
    delete Tree_anchor;
  }
};

#endif
