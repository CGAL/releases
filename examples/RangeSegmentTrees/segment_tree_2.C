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
// file          : src/examples/RangeSegmentTrees/segment_tree_2.C
// source        : src/examples/RangeSegmentTrees/segment_tree_2.C
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1998/02/03 13:18:50 $
// author(s)     : Gabriele Neyer (neyer@inf.ethz.ch)
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 2-dimensional Segment Trees
// A two dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.
// ============================================================================
#include <CGAL/basic.h>
#include <iostream.h>
#include <CGAL/Segment_tree_k.h>
#include <Tree_Traits.h>
#include <vector.h>
#include <iterator.h>
#include <tempbuf.h>
#include <list.h>

typedef CGAL_Segment_tree_2<Tree_traits_2> Segment_tree_2_type;

int main()
{

  typedef Tree_traits_2::Interval Interval;
  typedef Tree_traits_2::Key Key;
  // definition of the two-dimensional segment tree
  list<Interval> InputList, OutputList, N;


  // insertion of the tree elements into the sequence container
  InputList.push_back(Interval(Key(64, 139), Key(81.3, 921.3)));
  InputList.push_back(Interval(Key(465, 504), Key(499.3, 829.0)));
  InputList.push_back(Interval(Key(288, 875), Key(379.5, 982.7)));
  InputList.push_back(Interval(Key(314, 465), Key(375.1, 711.5)));
 
  // creation of the segment tree
  list<Interval>::iterator first = InputList.begin();
  list<Interval>::iterator last = InputList.end();

  Segment_tree_2_type Segment_tree_2(first,last);

  // perform a window query
  Interval a(Key(45, 500), Key(200.0, 675.1));
  Segment_tree_2.window_query(a,back_inserter(OutputList));

  // output of the querey elements on stdout
  list<Interval>::iterator j = OutputList.begin();
  cerr << "\n window_query (45, 500), (200.0, 675.1)\n";
  while(j!=OutputList.end())
  {
    cerr << (*j).first.first << "-" << (*j).second.first << " " 
	 << (*j).first.second << "-" << (*j).second.second << endl; 
    j++;
  }
  Interval b(Key(320, 900),Key(330.1,910.7));
  Segment_tree_2.enclosing_query(b,back_inserter(N));
  j = N.begin();
  cerr << "\n enclosing_query (320, 900),(330.1,910.7)\n";
  while(j!=N.end())
  {
    cerr << (*j).first.first << "-" << (*j).second.first << " " 
	 << (*j).first.second << "-" << (*j).second.second << endl; 
    j++;
  }
  if(Segment_tree_2.Segment_tree_2->is_valid())
    cerr << "Tree  is valid\n";
  else
    cerr << "Tree is not valid\n";
  return 0; 
}


