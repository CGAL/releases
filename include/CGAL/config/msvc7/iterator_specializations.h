// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// file          : include/CGAL/config/msvc7/iterator_specializations.h
// package       : wininst (2.1.15)
// author(s)     : 
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// coordinator   : 
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ITER_VC7
#define CGAL_ITER_VC7
#include <iterator>
#include <CGAL/config/msvc7/stl_iterator_base.h>
namespace std {
template<class C__> inline
typename iterator_traits<C__>::iterator_category
_Iter_cat(const C__&)
  {
    typedef typename iterator_traits<C__>::iterator_category c;
    return c();
  }

template <class _Iter> inline 
typename iterator_traits<_Iter>::difference_type*
  _Dist_type(const _Iter&)
  {
    typedef typename iterator_traits<_Iter>::difference_type _diff_type;
    return static_cast<_diff_type*>(0);
  }

template <class _Iter> inline 
typename iterator_traits<_Iter>::value_type*
  _Val_type(const _Iter&)
{
  typedef typename iterator_traits<_Iter>::value_type _value_type;
  return static_cast<_value_type*>(0);
}


}
#endif // CGAL_ITER_VC7
