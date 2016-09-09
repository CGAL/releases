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
// file          : src/examples/RangeSegmentTrees/segment_tree_map_2.C
// source        : src/examples/RangeSegmentTrees/segment_tree_map_2.C
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1998/02/03 13:18:57 $
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
typedef CGAL_Segment_tree_map_traits_2<Rep, char> Traits;
typedef CGAL_Segment_tree_2<Traits > Segment_tree_2_type;

int main()
{
#ifdef grgr
  typedef Traits::Interval Interval;
  typedef Traits::Pure_interval Pure_interval;
  typedef Traits::Key Key;
  // definition of the two-dimensional segment tree
  list<Interval> InputList, OutputList, N;


  // insertion of the tree elements into the sequence container
  InputList.push_back(Interval(Pure_interval(Key(1,5), Key(2,7)),'a'));
  InputList.push_back(Interval(Pure_interval(Key(2,7), Key(3,8)),'b'));
  InputList.push_back(Interval(Pure_interval(Key(6,9), Key(9,13)), 'c'));
  InputList.push_back(Interval(Pure_interval(Key(1,3), Key(3,9)),'d'));
 
  // creation of the segment tree
  list<Interval>::iterator first = InputList.begin();
  list<Interval>::iterator last = InputList.end();

  Segment_tree_2_type Segment_tree_2(first,last);

  // perform a window query
  Interval a(Pure_interval(Key(3,6), Key(7,12)),'e');
  Segment_tree_2.window_query(a,back_inserter(OutputList));

  // output of the querey elements on stdout
  list<Interval>::iterator j = OutputList.begin();
  cerr << "\n window_query (3,6),(7,12)\n";
  while(j!=OutputList.end())
  {
    cerr << (*j).first.first.x() << "-" << (*j).first.second.x() << " " 
	 << (*j).first.first.y() << "-" << (*j).first.second.y() << endl; 
    j++;
  }
  Interval b(Pure_interval(Key(6,10),Key(7,11)), 'f');
  Segment_tree_2.enclosing_query(b,back_inserter(N));
  j = N.begin();
  cerr << "\n enclosing_query 6,10,7,11\n";
  while(j!=N.end())
  {
    cerr << (*j).first.first.x() << "-" << (*j).first.second.x() << " " 
	 << (*j).first.first.y() << "-" << (*j).first.second.y() << endl; 
    j++;
  }
  if(Segment_tree_2.Segment_tree_2->is_valid())
    cerr << "Tree  is valid\n";
  else
    cerr << "Tree is not valid\n";
#endif
  return 0; 
}


