// ============================================================================
//
// Copyright (c) 1997, 1998, 1999, 2000 The CGAL Consortium

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
// file          : functional_base.h
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// package       : $CGAL_Package: STL_Extension $
// source        : stl_extension.fw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/07/11 09:00:29 $
// author(s)     : Michael Hoffmann
//                 Lutz Kettner
//
// coordinator   : ETH
//
// Basics for CGAL Functors.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_FUNCTIONAL_BASE_H
#define CGAL_FUNCTIONAL_BASE_H 1

#include <functional>

namespace CGAL {

// +----------------------------------------------------------------------+
// | Defining a Functors Arity (== #arguments)
// +----------------------------------------------------------------------+

template < int i > struct Arity_tag { enum { arity = i }; };
// use to deduce arity of functors
// --> allows binding std functors
template < class T >
struct Arity_traits {
  typedef typename T::Arity Arity;
};

#ifndef _MSC_VER
#ifndef CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION

// --------------------------------------------------------------------
// specializations for std functors:
//

template < class T >
struct Arity_traits< std::plus< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::minus< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::multiplies< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::divides< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::modulus< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::negate< T > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T >
struct Arity_traits< std::equal_to< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::not_equal_to< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::greater< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::less< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::greater_equal< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::less_equal< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::logical_and< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::logical_or< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::logical_not< T > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T >
struct Arity_traits< std::unary_negate< T > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T >
struct Arity_traits< std::binary_negate< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::binder1st< T > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T >
struct Arity_traits< std::binder2nd< T > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2 >
struct Arity_traits< std::pointer_to_unary_function< T1, T2 > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2, class T3 >
struct Arity_traits< std::pointer_to_binary_function< T1, T2, T3 > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T1, class T2 >
struct Arity_traits< std::mem_fun_t< T1, T2 > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2, class T3 >
struct Arity_traits< std::mem_fun1_t< T1, T2, T3 > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T1, class T2 >
struct Arity_traits< std::mem_fun_ref_t< T1, T2 > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2, class T3 >
struct Arity_traits< std::mem_fun1_ref_t< T1, T2, T3 > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T1, class T2 >
struct Arity_traits< std::const_mem_fun_t< T1, T2 > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2, class T3 >
struct Arity_traits< std::const_mem_fun1_t< T1, T2, T3 > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T1, class T2 >
struct Arity_traits< std::const_mem_fun_ref_t< T1, T2 > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2, class T3 >
struct Arity_traits< std::const_mem_fun1_ref_t< T1, T2, T3 > > {
  typedef Arity_tag< 2 > Arity;
};

#endif // ! CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION
#endif // ! _MSC_VER

} // namespace CGAL

#endif // CGAL_FUNCTIONAL_BASE_H
// EOF //
