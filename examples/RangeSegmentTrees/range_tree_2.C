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
// file          : src/examples/RangeSegmentTrees/range_tree_2.C
// source        : src/examples/RangeSegmentTrees/range_tree_2.C
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1998/02/03 13:18:32 $
// author(s)     : Gabriele Neyer (neyer@inf.ethz.ch)
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 2-dimensional Range Trees
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

typedef CGAL_Range_tree_2<Tree_traits_2> Range_tree_2_type;

int main()
{
  typedef Tree_traits_2::Key Key;
  typedef Tree_traits_2::Interval Interval;

  vector<Key> InputList, OutputList;
  typedef vector<Key>::iterator V_iterator;
  V_iterator first, last, current;

  int i,j;
  j= 100;
  int first_key=1, second_key=3;
  for(i=1;i<j;i++)
  {
    InputList.push_back(Key(first_key++,second_key++));
  }

  first = InputList.begin();
  last = InputList.end();
  cerr << InputList.size();

  Range_tree_2_type *Range_tree_2 = new Range_tree_2_type(first,last);

  Interval win(Interval(Key(4,8.1),Key(5,8.2)));

  cerr << "\n Window Query: \n";
  Range_tree_2->window_query(win, back_inserter(OutputList));
  current=OutputList.begin();

  while(current!=OutputList.end())
  {
    cerr << (*current).first<< "-" << (*current).second << endl;
    current++;
  }

  if(Range_tree_2->Range_tree_2->is_valid())
    cerr << "Tree is valid\n";
  else
    cerr << "Tree is not valid\n";

  return 0; 
}


