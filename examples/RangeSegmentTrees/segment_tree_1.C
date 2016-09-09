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
// file          : src/examples/RangeSegmentTrees/segment_tree_1.C
// source        : src/examples/RangeSegmentTrees/segment_tree_1.C
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1998/02/03 13:18:45 $
// author(s)     : Gabriele Neyer (neyer@inf.ethz.ch)
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 1-dimensional Segment Trees
// A one dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.
// ============================================================================
#include <CGAL/basic.h> 
#include <iostream.h>
#include <Tree_Traits.h>
#include <CGAL/Segment_tree_k.h>
#include <vector.h>
#include <iterator.h>
#include <tempbuf.h>
#include <list.h>
#include <pair.h>

typedef CGAL_Segment_tree_1<Tree_traits_1> Segment_tree_1_type;

int main()
{
  typedef Tree_traits_1::Interval Interval;
  typedef Tree_traits_1::Key Key;
  // definition of the two-dimensional segment tree
  list<Interval> InputList, OutputList, N;

  // insertion of the tree elements into the sequence container
  InputList.push_back(Interval(64, 81));
  InputList.push_back(Interval(465, 499));
  InputList.push_back(Interval(288, 379));
  InputList.push_back(Interval(314, 375));
 
  // creation of the segment tree
  typedef list<Interval>::iterator l_iterator;
  l_iterator first = InputList.begin();
  l_iterator last = InputList.end();

  Segment_tree_1_type Segment_tree_1(first,last);

  // perform a window query
  Interval a(45,200);
  Segment_tree_1.window_query(a,back_inserter(OutputList));

  // output of the querey elements on stdout
  l_iterator j = OutputList.begin();
  cerr << "\n window_query (45,200)\n";
  while(j!=OutputList.end())
  {
    cerr << (*j).first << "-" << (*j++).second << endl;
  }
  Interval b(320, 370);
  Segment_tree_1.enclosing_query(b,back_inserter(N));
  j = N.begin();
  cerr << "\n enclosing_query (320, 370)\n";
  while(j!=N.end())
  {
    cerr << (*j).first << "-" << (*j).second << endl;
    j++;
  }
  if(Segment_tree_1.Segment_tree_1->is_valid())
    cerr << "Tree is valid\n";
  else
    cerr << "Tree is not valid\n";
  return 0; 
}


