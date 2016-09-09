// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Triangulation_utils_3.h
// package       : Triangulation_3 (1.114)
// revision      : $Revision: 1.23 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_UTILS_3_H
#define CGAL_TRIANGULATION_UTILS_3_H

#include <CGAL/basic.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

struct Triangulation_utils_3
{
  static const char tab_next_around_edge[4][4];

  static int ccw(int i)
    {
      CGAL_triangulation_precondition( i >= 0 && i < 3 );
      return (i==2) ? 0 : i+1;
    }
  
  static int cw(int i)
    {
      CGAL_triangulation_precondition( i >= 0 && i < 3 );
      return (i==0) ? 2 : i-1;
    }

  static int next_around_edge(const int i, const int j)
  {
    // index of the next cell when turning around the
    // oriented edge vertex(i) vertex(j) in 3d
    CGAL_triangulation_precondition( ( i >= 0 && i < 4 ) &&
		                     ( j >= 0 && j < 4 ) &&
		                     ( i != j ) );
    return tab_next_around_edge[i][j];
  }

  static unsigned int random_value, count, val;

  // rand_4() outputs pseudo random unsigned ints < 4.
  // We compute random 16 bit values, that we slice/shift to make it faster.
  static unsigned int rand_4()
  {
      if (count==0)
      {
          count = 16;
          random_value = (421 * random_value + 2073) % 32749;
          val = random_value;
      }
      count--;
      unsigned int ret = val & 3;
      val = val >> 1;
      return ret;
  }

  static unsigned int rand_3()
  {
      unsigned int i = rand_4();
      return i==3 ? 0 : i;
  }
};

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_UTILS_3_H
