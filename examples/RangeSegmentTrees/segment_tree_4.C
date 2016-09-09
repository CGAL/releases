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
// file          : src/examples/RangeSegmentTrees/segment_tree_4.C
// source        : src/examples/RangeSegmentTrees/segment_tree_4.C
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1998/02/03 13:18:55 $
// author(s)     : Gabriele Neyer (neyer@inf.ethz.ch)
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 4-dimensional Segment Trees
// A four dimensional Segment Tree is defined in this class.
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

typedef CGAL_Segment_tree_4<Tree_traits_4> Segment_tree_4_type;

int main()
{

  typedef Tree_traits_4::Interval Interval;
  typedef Tree_traits_4::Key Key;
  // definition of the two-dimensional segment tree
  list<Interval> InputList, OutputList, N;

  // insertion of the tree elements into the sequence container
  InputList.push_back(Interval(Key(1, 4, 5, 2.5), Key(2,5,7, 4.7)));
  InputList.push_back(Interval(Key(2,6.7,5, 3.5), Key(4,6.9, 8, 7.9)));
  InputList.push_back(Interval(Key(2,4.55, 8, 5.5), Key(5, 7.88, 10, 9.9)));
  InputList.push_back(Interval(Key(2, 4.66, 5, 4.6), Key(6, 8.99, 8, 8.4)));
 
  // creation of the segment tree
  list<Interval>::iterator first = InputList.begin();
  list<Interval>::iterator last = InputList.end();

  Segment_tree_4_type Segment_tree_4(first,last);

  // perform a window query
  Interval a(Key(3,4.88, 6, 5.4), Key(6, 8.999, 9, 8.6));
  Segment_tree_4.window_query(a,back_inserter(OutputList));

  // output of the querey elements on stdout
  list<Interval>::iterator j = OutputList.begin();
  cerr << "\n window_query (3,4.88, 6, 5.4),(6, 8.999, 9, 8.6)\n";
  while(j!=OutputList.end())
  {
    cerr << (*j).first.key_1 << "," << (*j).first.key_2 << ", " 
	 << (*j).first.key_3 << ", " << (*j).first.key_4 << "-" 
	 << (*j).second.key_1 << "," << (*j).second.key_2 << ", " 
	 << (*j).second.key_3 << " , " <<  (*j).second.key_4 << endl;
    j++;
  }
  Interval b(Key(2,6.8,9, 5.9),Key(3,7,10, 6.7));
  Segment_tree_4.enclosing_query(b,back_inserter(N));
  j = N.begin();
  cerr << "\n enclosing_query (2,6.8,9, 5.9), (3,7,10, 6.7)\n";
  while(j!=N.end())
  {
    cerr << (*j).first.key_1 << "," << (*j).first.key_2 << ", " 
	 << (*j).first.key_3 << ", " << (*j).first.key_4 << "-" 
	 << (*j).second.key_1 << "," << (*j).second.key_2 << ", " 
	 << (*j).second.key_3 << " , " <<  (*j).second.key_4 << endl;
    j++;
  }
  if(Segment_tree_4.Segment_tree_4->is_valid())
    cerr << "Tree  is valid\n";
  else
    cerr << "Tree is not valid\n";
  return 0; 
}


