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
// file          : src/examples/RangeSegmentTrees/range_tree_3.C
// source        : src/examples/RangeSegmentTrees/range_tree_3.C
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1998/02/03 13:18:34 $
// author(s)     : Gabriele Neyer (neyer@inf.ethz.ch)
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 3-dimensional Range Trees
// A three dimensional Range Tree is defined in this class.
// Ti is the type of each dimension of the tree.
// ============================================================================
#include <CGAL/basic.h>

#include <iostream.h>
#include <Tree_Traits.h>
#include "../include/CGAL/Range_tree_k.h"
#include <list.h>
#include <iterator.h>
#include <pair.h>

typedef CGAL_Range_tree_3<Tree_traits_3> Range_tree_3_type;

int main()
{
  typedef Tree_traits_3::Key Key;
  typedef Tree_traits_3::Interval Interval;

  list<Key> InputList, OutputList;
  list<Key>::iterator first, last, current;

  InputList.push_back(Key(8,5.1,34));
  InputList.push_back(Key(1,1.1,67));
  InputList.push_back(Key(3,2.1,56));
  InputList.push_back(Key(2,6.1,89));
  InputList.push_back(Key(5,4.1,45));
  InputList.push_back(Key(4,8.1,76));
  InputList.push_back(Key(7,7.1,87));
  InputList.push_back(Key(6,3.1,78));

  first = InputList.begin();
  last = InputList.end();

  Range_tree_3_type Range_tree_3(first,last);

  Interval win(Interval(Key(4,8.1,45),Key(5,8.2,89)));

  cerr << "\n Window Query:(4,8.1,45),(5,8.2,89)\n";
  Range_tree_3.window_query(win, back_inserter(OutputList));
  current=OutputList.begin();

  while(current!=OutputList.end())
  {
    cerr << (*current).key_1<< "-" <<  (*current).key_2<< "-" 
	 << (*current).key_3 << endl;
    current++;
  }

  if(Range_tree_3.Range_tree_3->is_valid())
    cerr << "Tree is valid\n";
  else
    cerr << "Tree is not valid\n";


  return 0;
}
















