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
// file          : src/examples/RangeSegmentTrees/range_tree_4.C
// source        : src/examples/RangeSegmentTrees/range_tree_4.C
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1998/02/03 13:18:37 $
// author(s)     : Gabriele Neyer (neyer@inf.ethz.ch)
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 4-dimensional Range Trees
// A four dimensional Range Tree is defined in this class.
// Ti is the type of each dimension of the tree.
// ============================================================================
#include <CGAL/basic.h>
#include <iostream.h>
#include <CGAL/Range_tree_k.h>
#include <Tree_Traits.h>
#include <list.h>
#include <iterator.h>

typedef CGAL_Range_tree_4<Tree_traits_4> Range_tree_4_type;

int main()
{
  typedef Tree_traits_4::Key Key;
  typedef Tree_traits_4::Interval Interval;

  list<Key> InputList, OutputList;
  list<Key>::iterator first, last, current;

  InputList.push_back(Key(8,5.1,34, 1.11));
  InputList.push_back(Key(1,1.1,67, 1.23));
  InputList.push_back(Key(3,2.1,56, 1.34));
  InputList.push_back(Key(2,6.1,89, 1.09));
  InputList.push_back(Key(5,4.1,45, 1.009));
  InputList.push_back(Key(4,8.1,76, 1.98));
  InputList.push_back(Key(7,7.1,87, 1.333));
  InputList.push_back(Key(6,3.1,78, 1.45));

  first = InputList.begin();
  last = InputList.end();

  Range_tree_4_type Range_tree_4(first,last);

  Interval win(Interval(Key(4,8.1,45, 1.12),Key(5,8.2,89, 1.99)));

  cerr << "\n Window Query:(4,8.1,45, 1.12), (5,8.2,89, 1.99)\n";
  Range_tree_4.window_query(win, back_inserter(OutputList));
  current=OutputList.begin();

  while(current!=OutputList.end())
  {
    cerr << (*current).key_1<< "-" <<  (*current).key_2 << "-" 
	 <<  (*current).key_3 << (*current).key_4 << endl;
    current++;
  }

  if(Range_tree_4.Range_tree_4->is_valid())
    cerr << "Tree is valid\n";
  else
    cerr << "Tree is not valid\n";

  return 0;
}


