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
// file          : include/CGAL/triple.h
// package       : Triangulation_3 (1.83)
// revision      : $Revision: 1.9 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIPLE_H
#define CGAL_TRIPLE_H

#include <CGAL/basic.h>
CGAL_BEGIN_NAMESPACE

template <class T1, class T2, class T3>
struct triple 
{
  T1 first;
  T2 second;
  T3 third;

  triple() {}

  triple(const T1& a, const T2& b, const T3& c)
    : first(a), second(b), third(c) 
    {}
};

template <class T1, class T2, class T3>
inline 
triple<T1, T2, T3> make_triple(const T1& x, const T2& y, const T3& z)
{
  return triple<T1, T2, T3>(x, y, z);
}

template <class T1, class T2, class T3>
inline bool operator==(const triple<T1, T2, T3>& x,
		       const triple<T1, T2, T3>& y) 
{ 
  return ( (x.first == y.first) && 
	   (x.second == y.second) && 
	   (x.third == y.third) ); 
}

template <class T1, class T2, class T3>
inline
bool operator<(const triple<T1, T2, T3>& x,
	       const triple<T1, T2, T3>& y)
{ 
  return ( x.first < y.first || 
	   ( (x.first == y.first) && (x.second < y.second) ) ||
	   ( (x.first == y.first) && (x.second == y.second) && 
	                             (x.third < y.third) ) );
}

CGAL_END_NAMESPACE

#endif // CGAL_TRIPLE_H
