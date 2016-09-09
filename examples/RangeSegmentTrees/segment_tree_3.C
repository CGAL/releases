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
// file          : src/examples/RangeSegmentTrees/segment_tree_3.C
// source        : src/examples/RangeSegmentTrees/segment_tree_3.C
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1998/02/03 13:18:52 $
// author(s)     : Gabriele Neyer (neyer@inf.ethz.ch)
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 3-dimensional Segment Trees
// A three dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.
// ============================================================================
#include <CGAL/basic.h>
#include <iostream.h>
#include <CGAL/Segment_tree_k.h>
#include <CGAL/Segment_tree_k.h>
#include <Tree_Traits.h>
#include <vector.h>
#include <iterator.h>
#include <tempbuf.h>
#include <list.h>

typedef CGAL_Segment_tree_3<Tree_traits_3> Segment_tree_3_type;

int main()
{
  typedef Tree_traits_3::Interval Interval;
  typedef Tree_traits_3::Key Key;
  // definition of the two-dimensional segment tree
  list<Interval> InputList, OutputList, N;

  // insertion of the tree elements into the sequence container
  InputList.push_back(Interval(Key(1, 3, 5), Key(2,5,7)));
  InputList.push_back(Interval(Key(2,6.7,5), Key(4,6.9, 8)));
  InputList.push_back(Interval(Key(2,4.55, 8), Key(5, 7.88, 10)));
  InputList.push_back(Interval(Key(2, 4.66, 5), Key(6, 8.99, 8)));
 
  // creation of the segment tree
  list<Interval>::iterator first = InputList.begin();
  list<Interval>::iterator last = InputList.end();

  Segment_tree_3_type Segment_tree_3(first,last);

  // perform a window query
  Interval a(Key(3,4.88, 6), Key(6, 8.999, 9));
  Segment_tree_3.window_query(a,back_inserter(OutputList));

  // output of the querey elements on stdout
  list<Interval>::iterator j = OutputList.begin();
  cerr << "\n window_query (3,4.88, 6),(6, 8.999, 9)\n";
  while(j!=OutputList.end())
  {
    cerr << (*j).first.key_1 << "," << (*j).first.key_2 << ", " 
	 << (*j).first.key_3 << "-" << (*j).second.key_1 << "," 
	 << (*j).second.key_2 << ", " << (*j).second.key_3 << endl;
    j++;
  }
  Interval b(Key(2,6.8,9),Key(3,7,10));
  Segment_tree_3.enclosing_query(b,back_inserter(N));
  j = N.begin();
  cerr << "\n enclosing_query(2,6.8,9),(3,7,10)\n";
  while(j!=N.end())
  {
    cerr << (*j).first.key_1 << "," << (*j).first.key_2 << ", " 
	 << (*j).first.key_3 << "-" << (*j).second.key_1 << "," 
	 << (*j).second.key_2 << ", " << (*j).second.key_3 << endl;
    j++;
  }
  if(Segment_tree_3.Segment_tree_3->is_valid())
    cerr << "Tree is valid\n";
  else
    cerr << "Tree is not valid\n";
  return 0;
}


