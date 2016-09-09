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
// file          : src/examples/RangeSegmentTrees/range_tree_map_2.C
// source        : src/examples/RangeSegmentTrees/range_tree_map_2.C
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1998/02/03 13:18:39 $
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
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <pair.h>
#include <CGAL/Range_segment_tree_traits.h>
#include <CGAL/Range_tree_k.h>
#include <vector.h>
#include <iterator.h>

typedef CGAL_Cartesian<double> Rep;
typedef CGAL_Range_tree_map_traits_2<Rep, char> Traits;
typedef CGAL_Range_tree_2<Traits> Range_tree_2_type;

int main()
{
  typedef Traits::Key Key;
  typedef Traits::Pure_key Pure_key;
  typedef Traits::Interval Interval;


  vector<Key> InputList, OutputList;
  vector<Key>::iterator first, last, current;

  InputList.push_back(Key(Pure_key(8,5.1), 'a'));
  InputList.push_back(Key(Pure_key(1,1.1), 'b'));
  InputList.push_back(Key(Pure_key(3,2.1), 'c'));
  InputList.push_back(Key(Pure_key(2,6.1), 'd'));
  InputList.push_back(Key(Pure_key(5,4.1), 'e'));
  InputList.push_back(Key(Pure_key(4,8.1), 'f'));
  InputList.push_back(Key(Pure_key(7,7.1), 'g'));
  InputList.push_back(Key(Pure_key(6,3.1), 'h'));

  first = InputList.begin();
  last = InputList.end();

  Range_tree_2_type Range_tree_2(first,last);

  Interval win(Interval(Pure_key(4,8.1),Pure_key(5,8.2)));

  cerr << "\n Window Query:(4,8.1),(5,8.2)\n";
  Range_tree_2.window_query(win, back_inserter(OutputList));
  current=OutputList.begin();

  while(current!=OutputList.end())
  {
    cerr << (*current).first.x()<< "-" << (*current).first.y() << " +char= " 
	 << (*current).second << endl;
    current++;
  }
  if(Range_tree_2.Range_tree_2->is_valid())
    cerr << "Tree is valid\n";
  else
    cerr << "Tree is not valid\n";
  return 0; 
}


