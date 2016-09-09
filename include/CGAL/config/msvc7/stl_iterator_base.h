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
// file          : include/CGAL/config/msvc7/stl_iterator_base.h
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


#ifndef CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC
#include <iterator>
// #include <utility>

#define CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(T)                    \
namespace std {                                                        \
    template <>                                                        \
    struct iterator_traits<const T*> {                                 \
	typedef random_access_iterator_tag iterator_category;          \
	typedef T                          value_type;                 \
	typedef ptrdiff_t                  difference_type;            \
	typedef const T*                   pointer;                    \
	typedef const T&                   reference;                  \
    };                                                                 \
    template <>                                                        \
    struct iterator_traits<T*> {                                       \
	typedef random_access_iterator_tag iterator_category;          \
	typedef T                          value_type;                 \
	typedef ptrdiff_t                  difference_type;            \
	typedef T*                         pointer;                    \
	typedef T&                         reference;                  \
    };                                                                 \
}

// add more stuff accoring to taste...
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(bool)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(float)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(double)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(char)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(int)
namespace std {
    template <>                                                        \
    struct iterator_traits<const void*> {                                 \
	typedef random_access_iterator_tag iterator_category;          \
	typedef ptrdiff_t                  difference_type;            \
	typedef const void*                   pointer;                    \
    };                                                                 \
    template <>                                                        \
    struct iterator_traits<void*> {                                       \
	typedef random_access_iterator_tag iterator_category;          \
	typedef ptrdiff_t                  difference_type;            \
	typedef void*                         pointer;                    \
    };                                                                 \
}

  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(unsigned short)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(unsigned int)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(unsigned char)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(signed char)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(void*)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(bool*)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(float*)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(double*)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(char*)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(int*)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(unsigned int*)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(unsigned char*)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(signed char*)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(unsigned short*)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(void**)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(bool**)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(float**)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(double**)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(char**)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(int**)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(unsigned int**)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(unsigned char**)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(signed char**)
  CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(unsigned short**)

#endif

