// ======================================================================
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
// file          : include/CGAL/number_utils_classes.h
// package       : Number_types (4.57)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2002/03/21 16:44:55 $
// author(s)     : Michael Hoffmann
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
//           
//                 slight modification of Michael's 1.1 version
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// to be included by number_utils.h

#ifndef CGAL_NUMBER_UTILS_CLASSES_H
#define CGAL_NUMBER_UTILS_CLASSES_H 1

#ifndef CGAL_CONFIG_H
#include <CGAL/config.h>
#endif // CGAL_CONFIG_H

#include <algorithm>
#include <CGAL/functional_base.h>

CGAL_BEGIN_NAMESPACE

template < class NT >
struct Is_zero :public CGAL_STD::unary_function< NT, bool > {
  typedef Arity_tag< 1 > Arity;
  bool operator()( const NT& x) const
  { return CGAL_NTS is_zero( x); }
};

template < class NT >
struct Is_one :public CGAL_STD::unary_function< NT, bool > {
  typedef Arity_tag< 1 > Arity;
  bool operator()( const NT& x) const
  { return CGAL_NTS is_one( x); }
};

template < class NT >
struct Is_negative :public CGAL_STD::unary_function< NT, bool > {
  typedef Arity_tag< 1 > Arity;
  bool operator()( const NT& x) const
  { return CGAL_NTS is_negative( x); }
};

template < class NT >
struct Is_positive :public CGAL_STD::unary_function< NT, bool > {
  typedef Arity_tag< 1 > Arity;
  bool operator()( const NT& x) const
  { return CGAL_NTS is_positive( x); }
};

// Sign would result in a name clash with enum.h
template < class NT >
struct Sgn :public CGAL_STD::unary_function< NT, int > {
  typedef Arity_tag< 1 > Arity;
  Sign operator()( const NT& x) const
  { return CGAL_NTS sign( x); }
};

template < class NT >
struct Abs :public CGAL_STD::unary_function< NT, NT > {
  typedef Arity_tag< 1 > Arity;
  NT operator()( const NT& x) const
  { return CGAL_NTS abs( x); }
};

template < class NT, class Compare = std::less< NT > >
struct Min :public CGAL_STD::binary_function< NT, NT, NT > {
  typedef Arity_tag< 2 > Arity;
  Min() {}
  Min(const Compare& c_) : c(c_) {}
  NT operator()( const NT& x, const NT& y) const
  { return min( x, y, c); }
protected:
  Compare c;
};

template < class NT, class Compare = std::less< NT > >
struct Max :public CGAL_STD::binary_function< NT, NT, NT > {
  typedef Arity_tag< 2 > Arity;
  Max() {}
  Max(const Compare& c_) : c(c_) {}
  NT operator()( const NT& x, const NT& y) const
  { return max( x, y, c); }
protected:
  Compare c;
};

template < class NT >
struct Compare
  :public CGAL_STD::binary_function< NT, NT, Comparison_result > {
  typedef Arity_tag< 2 > Arity;

  Comparison_result
  operator()( const NT& x, const NT& y) const
  { return CGAL_NTS compare( x, y); }
};

template < class NT >
struct Square : public CGAL_STD::unary_function< NT, NT > {
  typedef Arity_tag< 1 > Arity;

  NT
  operator()( const NT& x) const
  { return CGAL_NTS square( x ); }
};

template < class NT >
struct Sqrt : public CGAL_STD::unary_function< NT, NT > {
  typedef Arity_tag< 1 > Arity;

  NT
  operator()( const NT& x) const
  { return CGAL_NTS sqrt( x ); }
};

template < class NT >
struct Div : public CGAL_STD::binary_function< NT, NT, NT > {
  typedef Arity_tag< 2 > Arity;

  NT
  operator()( const NT& x, const NT& y) const
  { return CGAL_NTS div( x, y ); }
};

template < class NT >
struct Gcd : public CGAL_STD::binary_function< NT, NT, NT > {
  typedef Arity_tag< 2 > Arity;

  NT
  operator()( const NT& x, const NT& y) const
  { return CGAL_NTS gcd( x, y ); }
};

CGAL_END_NAMESPACE

#endif // CGAL_NUMBER_UTILS_CLASSES_H
