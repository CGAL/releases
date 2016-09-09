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
// file          : examples/RangeSegmentTrees/segment_tree_2.C
// source        : src/examples/RangeSegmentTrees/segment_tree_2.C
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 2001/07/26 07:48:02 $/
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 2-dimensional Segment Trees
// A two dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.
//
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#include <CGAL/basic.h>
#include <iostream>
#include <CGAL/Segment_tree_k.h>
#include "include/Tree_Traits.h"
#include <vector>
#include <iterator>
#include <list>

typedef CGAL::Segment_tree_2<CGAL::Tree_traits_2> Segment_tree_2_type;

int main()
{

  typedef CGAL::Tree_traits_2::Interval Interval;
  typedef CGAL::Tree_traits_2::Key Key;
  // definition of the two-dimensional segment tree
  std::list<Interval> InputList, OutputList, N;


  // insertion of the tree elements into the sequence container
  InputList.push_back(Interval(Key(64, 139), Key(81.3, 921.3)));
  InputList.push_back(Interval(Key(465, 504), Key(499.3, 829.0)));
  InputList.push_back(Interval(Key(288, 875), Key(379.5, 982.7)));
  InputList.push_back(Interval(Key(314, 465), Key(375.1, 711.5)));
 
  // creation of the segment tree
  std::list<Interval>::iterator first = InputList.begin();
  std::list<Interval>::iterator last = InputList.end();

  Segment_tree_2_type Segment_tree_2(first,last);

  // perform a window query
  Interval a(Key(45, 500), Key(200.0, 675.1));
  Segment_tree_2.window_query(a,std::back_inserter(OutputList));

  // output of the querey elements on stdout
  std::list<Interval>::iterator j = OutputList.begin();
  std::cerr << "\n window_query (45, 500), (200.0, 675.1)\n";
  while(j!=OutputList.end())
  {
    std::cerr << (*j).first.first << "-" << (*j).second.first << " " 
	 << (*j).first.second << "-" << (*j).second.second << std::endl; 
    j++;
  }
  Interval b(Key(320, 900),Key(330.1,910.7));
  Segment_tree_2.enclosing_query(b,std::back_inserter(N));
  j = N.begin();
  std::cerr << "\n enclosing_query (320, 900),(330.1,910.7)\n";
  while(j!=N.end())
  {
    std::cerr << (*j).first.first << "-" << (*j).second.first << " " 
	 << (*j).first.second << "-" << (*j).second.second << std::endl; 
    j++;
  }
  if(Segment_tree_2.CSegment_tree_2->is_valid())
    std::cerr << "Tree  is valid\n";
  else
    std::cerr << "Tree is not valid\n";
  return 0; 
}


