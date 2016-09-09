// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-0.9-I-01 $
// release_date  : $CGAL_Date: 1997/08/21 $
//
// file          : src/examples/RangeSegmentTrees/segment_tree_set_2.C
// source        : src/examples/RangeSegmentTrees/segment_tree_set_2.C
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1998/02/03 13:19:00 $
// author(s)     : Gabriele Neyer (neyer@inf.ethz.ch)
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 2-dimensional Segment Trees
// Example for the construction of a two dimensional segment tree.
// The data type of the first dimension is double and for the second 
// dimension double. 
// The elements that should be stored in the tree are pushed into
// a list. Then a two dimensional segment tree is created and a 
// window query is performed.
// ============================================================================
#include <CGAL/basic.h>
#include <iostream.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <pair.h>
#include <vector.h>
#include <iterator.h>
#include <tempbuf.h>
#include <list.h>
#include <CGAL/Segment_tree_k.h>
#include <CGAL/Range_segment_tree_traits.h>

typedef CGAL_Cartesian<double> Rep;
typedef CGAL_Range_segment_tree_set_traits_2<Rep> Traits;
typedef CGAL_Segment_tree_2<Traits > Segment_tree_2_type;

int main()
{
  typedef Traits::Interval Interval;
  typedef Traits::Key Key;
  // definition of the two-dimensional segment tree
  list<Interval> InputList, OutputList, N;

  // insertion of the tree elements into the sequence container
  InputList.push_back(Interval(Key(1,5), Key(2,7)));
  InputList.push_back(Interval(Key(2,7), Key(3,8)));
  InputList.push_back(Interval(Key(6,9), Key(9,13)));
  InputList.push_back(Interval(Key(1,3), Key(3,9)));
 
  // creation of the segment tree
  list<Interval>::iterator first = InputList.begin();
  list<Interval>::iterator last = InputList.end();

  Segment_tree_2_type Segment_tree_2(first,last);

  // perform a window query
  Interval a(Key(3,6), Key(7,12));
  Segment_tree_2.window_query(a,back_inserter(OutputList));

  // output of the querey elements on stdout
  list<Interval>::iterator j = OutputList.begin();
  cerr << "\n window_query (3,6), (7,12)\n";
  while(j!=OutputList.end())
  {
    cerr << (*j).first.x() << "-" << (*j).second.x() << " " 
	 << (*j).first.y() << "-" << (*j).second.y() << endl; 
    j++;
  }
  cerr << "\n enclosing_query (6,10),(7,11) \n";
  Interval b(Key(6,10),Key(7,11));
  Segment_tree_2.enclosing_query(b,back_inserter(N));
  j = N.begin();
  cerr << "\n enclosing_query (6,10),(7,11) \n";
  while(j!=N.end())
  {
    cerr << (*j).first.x() << "-" << (*j).second.x() << " " 
	 << (*j).first.y() << "-" << (*j).second.y() << endl; 
    j++;
  }
  if(Segment_tree_2.Segment_tree_2->is_valid())
    cerr << "Tree is valid\n";
  else
    cerr << "Tree is not valid\n";
  return 0;
}


