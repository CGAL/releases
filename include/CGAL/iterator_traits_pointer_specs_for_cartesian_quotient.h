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
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/iterator_traits_pointer_specs_for_cartesian_quotient.h
// package       : Kernel_basic (3.53)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/01/09 18:54:37 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_ITERATOR_TRAITS_POINTER_SPECS_FOR_CARTESIAN_QUOTIENT_H
#define CGAL_ITERATOR_TRAITS_POINTER_SPECS_FOR_CARTESIAN_QUOTIENT_H

// to be included in Quotient.h

#ifdef CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT
#ifdef CGAL_CARTESIAN_H
CGAL_ITERATOR_TRAITS_POINTER_SPEC_2C( CGAL::Quotient<int> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_3C( CGAL::Quotient<int> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_DC( CGAL::Quotient<int> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_2C( CGAL::Quotient<long> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_3C( CGAL::Quotient<long> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_DC( CGAL::Quotient<long> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_2C( CGAL::Quotient<float> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_3C( CGAL::Quotient<float> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_DC( CGAL::Quotient<float> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_2C( CGAL::Quotient<double> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_3C( CGAL::Quotient<double> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_DC( CGAL::Quotient<double> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_2C( CGAL::Quotient<leda_real> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_3C( CGAL::Quotient<leda_real> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_DC( CGAL::Quotient<leda_real> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_2C( CGAL::Quotient<leda_integer> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_3C( CGAL::Quotient<leda_integer> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_DC( CGAL::Quotient<leda_integer> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_2C( CGAL::Quotient<CGAL::Gmpz> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_3C( CGAL::Quotient<CGAL::Gmpz> )
CGAL_ITERATOR_TRAITS_POINTER_SPEC_DC( CGAL::Quotient<CGAL::Gmpz> )

CGAL_ITERATOR_TRAITS_POINTER_SPECC2( CGAL::Quotient<int> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC3( CGAL::Quotient<int> )
CGAL_ITERATOR_TRAITS_POINTER_SPECCD( CGAL::Quotient<int> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC2( CGAL::Quotient<long> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC3( CGAL::Quotient<long> )
CGAL_ITERATOR_TRAITS_POINTER_SPECCD( CGAL::Quotient<long> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC2( CGAL::Quotient<float> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC3( CGAL::Quotient<float> )
CGAL_ITERATOR_TRAITS_POINTER_SPECCD( CGAL::Quotient<float> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC2( CGAL::Quotient<double> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC3( CGAL::Quotient<double> )
CGAL_ITERATOR_TRAITS_POINTER_SPECCD( CGAL::Quotient<double> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC2( CGAL::Quotient<leda_real> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC3( CGAL::Quotient<leda_real> )
CGAL_ITERATOR_TRAITS_POINTER_SPECCD( CGAL::Quotient<leda_real> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC2( CGAL::Quotient<leda_integer> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC3( CGAL::Quotient<leda_integer> )
CGAL_ITERATOR_TRAITS_POINTER_SPECCD( CGAL::Quotient<leda_integer> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC2( CGAL::Quotient<CGAL::Gmpz> )
CGAL_ITERATOR_TRAITS_POINTER_SPECC3( CGAL::Quotient<CGAL::Gmpz> )
CGAL_ITERATOR_TRAITS_POINTER_SPECCD( CGAL::Quotient<CGAL::Gmpz> )

#endif // CGAL_CARTESIAN_H
#endif // CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT

#endif // CGAL_ITERATOR_TRAITS_POINTER_SPECS_FOR_CARTESIAN_QUOTIENT_H
