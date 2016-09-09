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
// file          : src/examples/RangeSegmentTrees/range_tree_set_2.C
// source        : src/examples/RangeSegmentTrees/range_tree_set_2.C
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1998/02/03 13:18:42 $
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
#include <pair.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Range_segment_tree_traits.h>
#include <CGAL/Range_tree_k.h>
#include <vector.h>
#include <iterator.h>

typedef CGAL_Cartesian<double> Rep;
typedef CGAL_Range_segment_tree_set_traits_2<Rep> Traits;
typedef CGAL_Range_tree_2<Traits> Range_tree_2_type;

int main()
{
  typedef Traits::Key Key;
  typedef Traits::Interval Interval;
  Range_tree_2_type RR;
  vector<Key> InputList, OutputList;
  vector<Key>::iterator first, last, current;

  InputList.push_back(Key(8,5.1));
  InputList.push_back(Key(1,1.1));
  InputList.push_back(Key(3,2.1));
  InputList.push_back(Key(2,6.1));
  InputList.push_back(Key(5,4.1));
  InputList.push_back(Key(4,8.1));
  InputList.push_back(Key(7,7.1));
  InputList.push_back(Key(6,3.1));

  first = InputList.begin();
  last = InputList.end();

  Range_tree_2_type Range_tree_2(first,last);

  Interval win(Interval(Key(4,8.1),Key(5,8.2)));

  cerr << "\n Window Query: lower left point: (4.0,5.0), 
              upper right point: (8.1,8.2) \n";
  Range_tree_2.window_query(win, back_inserter(OutputList));
  current=OutputList.begin();

  while(current!=OutputList.end())
  {
    cerr << (*current).x()<< "-" << (*current).y() << endl;
    current++;
  }

  if(Range_tree_2.Range_tree_2->is_valid())
    cerr << "Tree is valid\n";
  else
    cerr << "Tree is not valid\n";

  return 0; 
}


