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
// file          : src/examples/RangeSegmentTrees/range_tree_1.C
// source        : src/examples/RangeSegmentTrees/range_tree_1.C
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1998/02/03 13:18:29 $
// author(s)     : Gabriele Neyer (neyer@inf.ethz.ch)
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 1-dimensional Range Trees
// A two dimensional Range Tree is defined in this class.
// Ti is the type of each dimension of the tree.
// ============================================================================

#include <CGAL/basic.h> 

#include <iostream.h>
#include <CGAL/Range_tree_k.h>
#include <Tree_Traits.h>
#include <vector.h>
#include <iterator.h>
#include <pair.h>


typedef CGAL_Range_tree_1<Tree_traits_1> Range_tree_1_type;

int main()
{

  typedef Tree_traits_1::Key Key;
  typedef Tree_traits_1::Interval Interval;
  vector<Key> InputList, OutputList;
  vector<Key>::iterator first, last, current;

  InputList.push_back(8.0);
  InputList.push_back(1.0);
  InputList.push_back(3.9);
  InputList.push_back(2.0);
  InputList.push_back(5.0);
  InputList.push_back(4.8);
  InputList.push_back(7.7);
  InputList.push_back(6.8);

  first = InputList.begin();
  last = InputList.end();

  Range_tree_1_type Range_tree_1(first,last);

  Interval win(Interval(4.6, 6.8));

  cerr << "\n Window Query (4.6, 6.8) \n";
  Range_tree_1.window_query(win, back_inserter(OutputList));
  current=OutputList.begin();

  while(current!=OutputList.end())
  {
    cerr << (*current) << endl;
    current++;
  }

  if(Range_tree_1.Range_tree_1->is_valid())
    cerr << "Tree is valid\n";
  else
    cerr << "Tree is not valid\n";

  return 0; 
}


