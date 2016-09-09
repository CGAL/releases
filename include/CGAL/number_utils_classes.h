// ======================================================================
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/number_utils_classes.h
// package       : Number_types (1.2.8)
// source        : 
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1997/12/15 11:59:58 $
// author(s)     : Michael Hoffmann
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

// to be included by number_utils.h

#ifndef CGAL_NUMBER_UTILS_CLASSES_H
#define CGAL_NUMBER_UTILS_CLASSES_H 1

#include <function.h>

template < class NT >
struct CGAL_Is_zero : public unary_function< NT, bool > {
  bool operator()( const NT& x) const
  { return CGAL_is_zero( x); }
};

template < class NT >
struct CGAL_Is_one : public unary_function< NT, bool > {
  bool operator()( const NT& x) const
  { return CGAL_is_one( x); }
};

template < class NT >
struct CGAL_Is_negative : public unary_function< NT, bool > {
  bool operator()( const NT& x) const
  { return CGAL_is_negative( x); }
};

template < class NT >
struct CGAL_Is_positive : public unary_function< NT, bool > {
  bool operator()( const NT& x) const
  { return CGAL_is_positive( x); }
};

// CGAL_Sign would result in a name clash with enum.h
template < class NT >
struct CGAL_Sgn : public unary_function< NT, int > {
  int operator()( const NT& x) const
  { return CGAL_sign( x); }
};

template < class NT >
struct CGAL_Lexicographical_sign
  : public binary_function< NT, NT, int > {

  int operator()( const NT& x, const NT& y) const
  { return CGAL_lexicographical_sign( x, y); }
};

template < class NT >
struct CGAL_Abs : public unary_function< NT, NT > {
  NT operator()( const NT& x) const
  { return CGAL_abs( x); }
};

template < class NT >
struct CGAL_Min : public binary_function< NT, NT, NT > {
  NT operator()( const NT& x, const NT& y) const
  { return CGAL_min( x, y); }
};

template < class NT >
struct CGAL_Max : public binary_function< NT, NT, NT > {
  NT operator()( const NT& x, const NT& y) const
  { return CGAL_max( x, y); }
};

template < class NT >
struct CGAL_Compare
  : public binary_function< NT, NT, CGAL_Comparison_result > {

  CGAL_Comparison_result
  operator()( const NT& x, const NT& y) const
  { return CGAL_compare( x, y); }
};

#endif
