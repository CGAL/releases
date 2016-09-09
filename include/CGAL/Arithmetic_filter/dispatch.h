// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// file          : include/CGAL/Arithmetic_filter/dispatch.h
// package       : Interval_arithmetic (4.58)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2000/06/13 15:07:38 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ARITHMETIC_FILTER_DISPATCH_H
#define CGAL_ARITHMETIC_FILTER_DISPATCH_H

#if !defined( CGAL_ARITHMETIC_FILTER_PREDICATES_BUILTIN_H )
#include <CGAL/Arithmetic_filter/predicates/builtin.h>
#endif

#if defined( CGAL_PREDICATES_SIGN_OF_DETERMINANT_H ) && \
       !defined( CGAL_ARITHMETIC_FILTER_PREDICATES_SIGN_OF_DETERMINANT_H )
#include <CGAL/Arithmetic_filter/predicates/sign_of_determinant.h>
#endif

#if defined( CGAL_PREDICATES_KERNEL_FTC2_H ) && \
   !defined( CGAL_ARITHMETIC_FILTER_PREDICATES_KERNEL_FTC2_H )
#include <CGAL/Arithmetic_filter/predicates/kernel_ftC2.h>
#endif

#if defined( CGAL_PREDICATES_KERNEL_FTC3_H ) && \
       !defined( CGAL_ARITHMETIC_FILTER_PREDICATES_KERNEL_FTC3_H )
#include <CGAL/Arithmetic_filter/predicates/kernel_ftC3.h>
#endif

#if defined( CGAL_REGULAR_TRIANGULATION_FTC2_H ) && \
       !defined( CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC2_H )
#include <CGAL/Arithmetic_filter/predicates/Regular_triangulation_ftC2.h>
#endif

    /*
#if defined( CGAL_REGULAR_TRIANGULATION_RTH2_H ) && \
       !defined( CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_RTH2_H )
#include <CGAL/Arithmetic_filter/predicates/Regular_triangulation_rtH2.h>
#endif
*/

#if defined( CGAL_REGULAR_TRIANGULATION_FTC3_H ) && \
       !defined( CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC3_H )
#include <CGAL/Arithmetic_filter/predicates/Regular_triangulation_ftC3.h>
#endif

    /*
#if defined( CGAL_REGULAR_TRIANGULATION_RTH3_H ) && \
       !defined( CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_RTH3_H )
#include <CGAL/Arithmetic_filter/predicates/Regular_triangulation_rtH3.h>
#endif
*/

#endif // CGAL_ARITHMETIC_FILTER_DISPATCH_H
