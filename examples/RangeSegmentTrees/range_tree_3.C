// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : examples/RangeSegmentTrees/range_tree_3.C
// source        : src/examples/RangeSegmentTrees/range_tree_3.C
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 2001/07/26 07:48:02 $/
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 3-dimensional Range Trees
// A three dimensional Range Tree is defined in this class.
// Ti is the type of each dimension of the tree.
//
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#include <CGAL/basic.h>

#include <iostream>
#include <CGAL/Range_tree_k.h>
#include "include/Tree_Traits.h"
#include <list>
#include <iterator>
#include <utility>

typedef CGAL::Range_tree_3<CGAL::Tree_traits_3> Range_tree_3_type;

//prevention of a MSVC compiler bug:
CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(CGAL::tuple_3);


int main()
{
  typedef CGAL::Tree_traits_3::Key Key;
  typedef CGAL::Tree_traits_3::Interval Interval;

  std::list<Key> InputList, OutputList;
  std::list<Key>::iterator first, last, current;

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
  Key a=Key(4,8.1,45);
  Key b=Key(5,8.2,89);
  Interval win=Interval(a,b);

  std::cerr << "\n Window Query:(4,8.1,45),(5,8.2,89)\n";
  Range_tree_3.window_query(win, std::back_inserter(OutputList));
  current=OutputList.begin();

  while(current!=OutputList.end())
  {
    std::cerr << (*current).key_1<< "-" <<  (*current).key_2<< "-" 
	 << (*current).key_3 << std::endl;
    current++;
  }

  if(Range_tree_3.CRange_tree_3->is_valid())
    std::cerr << "Tree is valid\n";
  else
    std::cerr << "Tree is not valid\n";

  return 0;
}
















