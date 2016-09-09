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
// file          : examples/RangeSegmentTrees/segment_tree_set_2.C
// source        : src/examples/RangeSegmentTrees/segment_tree_set_2.C
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 2001/07/26 07:48:02 $/
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 2-dimensional Segment Trees
// Example for the construction of a two dimensional segment tree.
// The data type of the first dimension is double and for the second 
// dimension double. 
// The elements that should be stored in the tree are pushed into
// a list. Then a two dimensional segment tree is created and a 
// window query is performed.
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
#include <vector>
#include <iterator>
#include <list>
#include <CGAL/Segment_tree_k.h>
#include <CGAL/Range_segment_tree_traits.h>

typedef CGAL::Cartesian<double> Representation;
typedef CGAL::Range_segment_tree_set_traits_2<Representation> Traits;
typedef CGAL::Segment_tree_2<Traits > Segment_tree_2_type;

int main()
{
  typedef Traits::Interval Interval;
  typedef Traits::Key Key;
  // definition of the two-dimensional segment tree
  std::list<Interval> InputList, OutputList, N;

  // insertion of the tree elements into the sequence container
  InputList.push_back(Interval(Key(1,5), Key(2,7)));
  InputList.push_back(Interval(Key(2,7), Key(3,8)));
  InputList.push_back(Interval(Key(6,9), Key(9,13)));
  InputList.push_back(Interval(Key(1,3), Key(3,9)));
 
  // creation of the segment tree
  std::list<Interval>::iterator first = InputList.begin();
  std::list<Interval>::iterator last = InputList.end();

  Segment_tree_2_type Segment_tree_2(first,last);

  // perform a window query
  Interval a=Interval(Key(3,6), Key(7,12));
  Segment_tree_2.window_query(a,std::back_inserter(OutputList));

  // output of the querey elements on stdout
  std::list<Interval>::iterator j = OutputList.begin();
  std::cerr << "\n window_query (3,6), (7,12)\n";
  while(j!=OutputList.end())
  {
    std::cerr << (*j).first.x() << "-" << (*j).second.x() << " " 
	 << (*j).first.y() << "-" << (*j).second.y() << std::endl; 
    j++;
  }
  std::cerr << "\n enclosing_query (6,10),(7,11) \n";
  Interval b=Interval(Key(6,10),Key(7,11));
  Segment_tree_2.enclosing_query(b,std::back_inserter(N));
  j = N.begin();
  std::cerr << "\n enclosing_query (6,10),(7,11) \n";
  while(j!=N.end())
  {
    std::cerr << (*j).first.x() << "-" << (*j).second.x() << " " 
	 << (*j).first.y() << "-" << (*j).second.y() << std::endl; 
    j++;
  }
  if(Segment_tree_2.CSegment_tree_2->is_valid())
    std::cerr << "Tree is valid\n";
  else
    std::cerr << "Tree is not valid\n";
  return 0;
}


