// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : src/examples/RangeSegmentTrees/range_tree_2.C
// source        : src/examples/RangeSegmentTrees/range_tree_2.C
// revision      : $Revision: 1.5$
// revision_date : $Date: 1998/09/28 19:18:42 $/
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// Implementation: Testprogram for 2-dimensional Range Trees
// A two dimensional Range Tree is defined in this class.
// Ti is the type of each dimension of the tree.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
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


