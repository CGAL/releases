// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : examples/RangeSegmentTrees/segment_tree_1.C
// source        : src/examples/RangeSegmentTrees/segment_tree_1.C
// revision      : $Revision: 1.5$
// revision_date : $Date: 1998/09/28 19:18:42 $/
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 1-dimensional Segment Trees
// A one dimensional Segment Tree is defined in this class.
// Ti is the type of each dimension of the tree.
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
#include <CGAL/basic.h> 
#include <iostream>
#include "include/Tree_Traits.h"
#include <CGAL/Segment_tree_k.h>
#include <vector>
#include <iterator>
#include <list>
#include <utility>

typedef CGAL::Segment_tree_1<CGAL::Tree_traits_1> SSegment_tree_1_type;

int main()
{
  typedef CGAL::Tree_traits_1::Interval Interval;
  typedef CGAL::Tree_traits_1::Key Key;
  // definition of the one-dimensional segment tree
  std::list<Interval> InputList, OutputList, N;

  // insertion of the tree elements into the sequence container
  InputList.push_back(Interval(64, 81));
  InputList.push_back(Interval(465, 499));
  InputList.push_back(Interval(288, 379));
  InputList.push_back(Interval(314, 375));
 
  // creation of the segment tree
  typedef std::list<Interval>::iterator l_iterator;
  l_iterator first = InputList.begin();
  l_iterator last = InputList.end();

  SSegment_tree_1_type segment_tree_1(first,last);

  // perform a window query
  Interval a(45,200);
  segment_tree_1.window_query(a,std::back_inserter(OutputList));

  // output of the querey elements on stdout
  l_iterator j = OutputList.begin();
  std::cerr << "\n window_query (45,200)\n";
  while(j!=OutputList.end())
  {
    std::cerr << (*j).first << "-" << (*j).second << std::endl;
    j++;
  }
  Interval b(320, 370);
  segment_tree_1.enclosing_query(b,std::back_inserter(N));
  j = N.begin();
  std::cerr << "\n enclosing_query (320, 370)\n";
  while(j!=N.end())
  {
    std::cerr << (*j).first << "-" << (*j).second << std::endl;
    j++;
  }
  if(segment_tree_1.CSegment_tree_1->is_valid())
    std::cerr << "Tree is valid\n";
  else
    std::cerr << "Tree is not valid\n";
  return 0; 
}


