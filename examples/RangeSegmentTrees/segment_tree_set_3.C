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
// file          : src/examples/RangeSegmentTrees/segment_tree_set_3.C
// source        : src/examples/RangeSegmentTrees/segment_tree_set_3.C
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1998/02/03 13:19:05 $
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
#include <CGAL/Cartesian.h>
#include <CGAL/Point_3.h>
#include <pair.h>
#include <vector.h>
#include <iterator.h>
#include <tempbuf.h>
#include <list.h>
#include <CGAL/Segment_tree_k.h>
#include <CGAL/Range_segment_tree_traits.h>

typedef CGAL_Cartesian<double> Rep;
typedef CGAL_Range_segment_tree_set_traits_3<Rep> Traits;
typedef CGAL_Segment_tree_3<Traits > Segment_tree_3_type;

int main()
{
  typedef Traits::Interval Interval;
  typedef Traits::Key Key;
  // definition of the two-dimensional segment tree
  list<Interval> InputList, OutputList, N;

  // insertion of the tree elements into the sequence container
  InputList.push_back(Interval(Key(1,5,7), Key(2,7,9)));
  InputList.push_back(Interval(Key(2,7,6), Key(3,8,9)));
  InputList.push_back(Interval(Key(6,9,5), Key(9,13,8)));
  InputList.push_back(Interval(Key(1,3,4), Key(3,9,8)));
 
  // creation of the segment tree
  list<Interval>::iterator first = InputList.begin();
  list<Interval>::iterator last = InputList.end();

  Segment_tree_3_type Segment_tree_3(first,last);

  // perform a window query
  Interval a(Key(3,6,5), Key(7,12,8));
  Segment_tree_3.window_query(a,back_inserter(OutputList));

  // output of the querey elements on stdout
  list<Interval>::iterator j = OutputList.begin();
  cerr << "\n window_query (3,6,5),(7,12,8) \n";
  while(j!=OutputList.end())
  {
    cerr << (*j).first.x() << "," << (*j).first.y() << "," << (*j).first.z() 
	 <<", " << (*j).second.x() << "," << (*j).second.y() << "," 
	 << (*j).second.z() << endl; 
    j++;
  }
  Interval b(Key(6,10,7),Key(7,11,8));
  Segment_tree_3.enclosing_query(b,back_inserter(N));
  j = N.begin();
  cerr << "\n enclosing_query (6,10,7), (7,11,8)\n";
  while(j!=N.end())
  {
    cerr << (*j).first.x() << "," << (*j).first.y() << "," << (*j).first.z() 
	 <<", " << (*j).second.x() << "," << (*j).second.y() << "," 
	 << (*j).second.z() << endl; 
    j++;
  }
  if(Segment_tree_3.Segment_tree_3->is_valid())
    cerr << "Tree is valid\n";
  else
    cerr << "Tree is not valid\n";
  return 0;
}


