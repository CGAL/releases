// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// This file is part of an example program for CGAL.  This example
// program may be used, distributed and modified without limitation.

// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : examples/RangeSegmentTrees/range_tree_map_2.C
// source        : src/examples/RangeSegmentTrees/range_tree_map_2.C
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 2001/07/26 07:48:02 $/
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 2-dimensional Range Trees
// A two dimensional Range Tree is defined in this class.
// Ti is the type of each dimension of the tree.
//
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <CGAL/basic.h> 
#include <iostream>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <utility>
#include <CGAL/Range_segment_tree_traits.h>
#include <CGAL/Range_tree_k.h>
#include <vector>
#include <iterator>


//MSVC compiler bug prevention
typedef std::pair<CGAL::Point_2<CGAL::Cartesian<double> >,char> Pair002;
CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(Pair002);

typedef CGAL::Cartesian<double> Representation;
typedef CGAL::Range_tree_map_traits_2<Representation, char> Traits;
typedef CGAL::Range_tree_2<Traits> Range_tree_2_type;

int main()
{
  typedef Traits::Key Key;
  typedef Traits::Pure_key Pure_key;
  typedef Traits::Interval Interval;


  std::vector<Key> InputList, OutputList;
  std::vector<Key>::iterator first, last, current;

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

  Pure_key a=Pure_key(4,8.1);
  Pure_key b=Pure_key(5,8.2);
  Interval win=Interval(a,b);

  std::cerr << "\n Window Query:(4,8.1),(5,8.2)\n";
  Range_tree_2.window_query(win, std::back_inserter(OutputList));
  current=OutputList.begin();

  while(current!=OutputList.end())
  {
    std::cerr << (*current).first.x()<< "-" << (*current).first.y() << " +char= " 
	 << (*current).second << std::endl;
    current++;
  }
  if(Range_tree_2.CRange_tree_2->is_valid())
    std::cerr << "Tree is valid\n";
  else
    std::cerr << "Tree is not valid\n";
  return 0; 
}


