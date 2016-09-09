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
// file          : examples/RangeSegmentTrees/range_tree_set_2.C
// source        : src/examples/RangeSegmentTrees/range_tree_set_2.C
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
#include <utility>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Range_segment_tree_traits.h>
#include <CGAL/Range_tree_k.h>
#include <vector>
#include <iterator>

typedef CGAL::Cartesian<double> Representation;
typedef CGAL::Range_segment_tree_set_traits_2<Representation> Traits;
typedef CGAL::Range_tree_2<Traits> Range_tree_2_type;

int main()
{
  typedef Traits::Key Key;
  typedef Traits::Interval Interval;
  //  Range_tree_2_type RR;
  std::vector<Key> InputList, OutputList;
  std::vector<Key>::iterator first, last, current;

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

  Key a=Key(4,8.1);
  Key b=Key(5,8.2);
  Interval win=Interval(a,b);


  std::cerr << std::endl << "Window Query: lower left point: (4.0,5.0),";
  std::cerr << "upper right point: (8.1,8.2)" << std::endl;
  Range_tree_2.window_query(win, std::back_inserter(OutputList));
  current=OutputList.begin();

  while(current!=OutputList.end())
  {
    std::cerr << (*current).x()<< "-" << (*current).y() << std::endl;
    current++;
  }

  if(Range_tree_2.CRange_tree_2->is_valid())
    std::cerr << "Tree is valid\n";
  else
    std::cerr << "Tree is not valid\n";

  return 0; 
}


