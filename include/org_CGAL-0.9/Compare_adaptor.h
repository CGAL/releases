/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/

// file  : include/CGAL/Compare_adaptor.h
// source: include/CGAL/Compare_adaptor.h
// author: Gabriele Neyer

#ifndef __CGAL_Compare_adaptor__
#define __CGAL_Compare_adaptor__
#include <CGAL/predicates_on_points_2.h>

template <class _Point>
class CGAL_Point_key_compare_2
{
 public:
  typedef _Point T1;
  typedef _Point T2;

  class Compare1{
  public:
    
    bool operator()(T1 p1, T1 p2)
    {
      if(CGAL_SMALLER == CGAL_compare_x(p1,p2))
	return true;
      else 
	return false;
    }
  };
  class Compare2{
  public:
    bool operator()(T2 p1, T2 p2)
    {
      if(CGAL_SMALLER == CGAL_compare_y(p1,p2))
	return true;
      else 
	return false;
    }
  };
  typedef Compare1 C1;
  typedef Compare2 C2;
  
  bool c1(T1 p1, T1 p2) const
  {  return C1()(p1,p2);}
  bool c2(T2 p1, T2 p2) const
  {  return C2()(p1,p2);}
};


#endif
