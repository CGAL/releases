// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/bops_assertions.h
// package       : bops (2.1.5)
// source        : include/CGAL/bops_assertions.h
// revision      : $Revision: WIP $
// revision_date : $Date: Wed Dec  9 13:28:49 MET 1998  $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

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

Look at http://www.cs.ruu.nl/CGAL/ for more information.
Please send any bug reports and comments to cgal@cs.ruu.nl

*/


#ifndef CGAL_BOPS_ASSERTIONS_H
#define CGAL_BOPS_ASSERTIONS_H

#ifndef CGAL_ASSERTIONS_H
#  include <CGAL/assertions.h>
#endif


// macro definitions
// =================
// assertions
// ----------


#if defined(CGAL_BOPS_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || defined(NDEBUG)
#  define CGAL_bops_assertion(EX) ((void)0)
#  define CGAL_bops_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_bops_assertion_code(CODE)
#else
#  define CGAL_bops_assertion(EX) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_assertion_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_assertion_code(CODE) CODE
#endif // CGAL_BOPS_NO_ASSERTIONS

#if defined(CGAL_BOPS_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_BOPS_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_bops_exactness_assertion(EX) ((void)0)
#  define CGAL_bops_exactness_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_bops_exactness_assertion_code(CODE)
#else
#  define CGAL_bops_exactness_assertion(EX) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_exactness_assertion_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_exactness_assertion_code(CODE) CODE
#endif // CGAL_BOPS_NO_ASSERTIONS

#if defined(CGAL_BOPS_NO_ASSERTIONS) \
  || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_BOPS_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_bops_expensive_assertion(EX) ((void)0)
#  define CGAL_bops_expensive_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_bops_expensive_assertion_code(CODE)
#else
#  define CGAL_bops_expensive_assertion(EX) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_expensive_assertion_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_expensive_assertion_code(CODE) CODE
#endif // CGAL_BOPS_NO_ASSERTIONS

#if defined(CGAL_BOPS_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_BOPS_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_BOPS_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_bops_expensive_exactness_assertion(EX) ((void)0)
#  define CGAL_bops_expensive_exactness_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_bops_expensive_exactness_assertion_code(CODE)
#else
#  define CGAL_bops_expensive_exactness_assertion(EX) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_expensive_exactness_assertion_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_expensive_exactness_assertion_code(CODE) CODE
#endif // CGAL_BOPS_NO_ASSERTIONS


// preconditions
// -------------

#if defined(CGAL_BOPS_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_bops_precondition(EX) ((void)0)
#  define CGAL_bops_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_bops_precondition_code(CODE)
#else
#  define CGAL_bops_precondition(EX) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_precondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_precondition_code(CODE) CODE
#endif // CGAL_BOPS_NO_PRECONDITIONS

#if defined(CGAL_BOPS_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_BOPS_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_bops_exactness_precondition(EX) ((void)0)
#  define CGAL_bops_exactness_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_bops_exactness_precondition_code(CODE)
#else
#  define CGAL_bops_exactness_precondition(EX) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_exactness_precondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_exactness_precondition_code(CODE) CODE
#endif // CGAL_BOPS_NO_PRECONDITIONS

#if defined(CGAL_BOPS_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_BOPS_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_bops_expensive_precondition(EX) ((void)0)
#  define CGAL_bops_expensive_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_bops_expensive_precondition_code(CODE)
#else
#  define CGAL_bops_expensive_precondition(EX) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_expensive_precondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_expensive_precondition_code(CODE) CODE
#endif // CGAL_BOPS_NO_PRECONDITIONS

#if defined(CGAL_BOPS_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_BOPS_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_BOPS_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_bops_expensive_exactness_precondition(EX) ((void)0)
#  define CGAL_bops_expensive_exactness_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_bops_expensive_exactness_precondition_code(CODE)
#else
#  define CGAL_bops_expensive_exactness_precondition(EX) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_expensive_exactness_precondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_expensive_exactness_precondition_code(CODE) CODE
#endif // CGAL_BOPS_NO_PRECONDITIONS


// postconditions
// --------------

#if defined(CGAL_BOPS_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_bops_postcondition(EX) ((void)0)
#  define CGAL_bops_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_bops_postcondition_code(CODE)
#else
#  define CGAL_bops_postcondition(EX) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_postcondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_postcondition_code(CODE) CODE
#endif // CGAL_BOPS_NO_POSTCONDITIONS

#if defined(CGAL_BOPS_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_BOPS_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_bops_exactness_postcondition(EX) ((void)0)
#  define CGAL_bops_exactness_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_bops_exactness_postcondition_code(CODE)
#else
#  define CGAL_bops_exactness_postcondition(EX) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_exactness_postcondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_exactness_postcondition_code(CODE) CODE
#endif // CGAL_BOPS_NO_POSTCONDITIONS

#if defined(CGAL_BOPS_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_BOPS_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_bops_expensive_postcondition(EX) ((void)0)
#  define CGAL_bops_expensive_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_bops_expensive_postcondition_code(CODE)
#else
#  define CGAL_bops_expensive_postcondition(EX) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_expensive_postcondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_expensive_postcondition_code(CODE) CODE
#endif // CGAL_BOPS_NO_POSTCONDITIONS

#if defined(CGAL_BOPS_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_BOPS_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_BOPS_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_bops_expensive_exactness_postcondition(EX) ((void)0)
#  define CGAL_bops_expensive_exactness_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_bops_expensive_exactness_postcondition_code(CODE)
#else
#  define CGAL_bops_expensive_exactness_postcondition(EX) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_expensive_exactness_postcondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_expensive_exactness_postcondition_code(CODE) CODE
#endif // CGAL_BOPS_NO_POSTCONDITIONS


// warnings
// --------

#if defined(CGAL_BOPS_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || defined(NDEBUG)
#  define CGAL_bops_warning(EX) ((void)0)
#  define CGAL_bops_warning_msg(EX,MSG) ((void)0)
#  define CGAL_bops_warning_code(CODE)
#else
#  define CGAL_bops_warning(EX) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_warning_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_warning_code(CODE) CODE
#endif // CGAL_BOPS_NO_WARNINGS

#if defined(CGAL_BOPS_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_BOPS_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_bops_exactness_warning(EX) ((void)0)
#  define CGAL_bops_exactness_warning_msg(EX,MSG) ((void)0)
#  define CGAL_bops_exactness_warning_code(CODE)
#else
#  define CGAL_bops_exactness_warning(EX) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_exactness_warning_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_exactness_warning_code(CODE) CODE
#endif // CGAL_BOPS_NO_WARNINGS

#if defined(CGAL_BOPS_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_BOPS_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_bops_expensive_warning(EX) ((void)0)
#  define CGAL_bops_expensive_warning_msg(EX,MSG) ((void)0)
#  define CGAL_bops_expensive_warning_code(CODE)
#else
#  define CGAL_bops_expensive_warning(EX) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_expensive_warning_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_expensive_warning_code(CODE) CODE
#endif // CGAL_BOPS_NO_WARNINGS

#if defined(CGAL_BOPS_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_BOPS_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_BOPS_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_bops_expensive_exactness_warning(EX) ((void)0)
#  define CGAL_bops_expensive_exactness_warning_msg(EX,MSG) ((void)0)
#  define CGAL_bops_expensive_exactness_warning_code(CODE)
#else
#  define CGAL_bops_expensive_exactness_warning(EX) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_bops_expensive_exactness_warning_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_bops_expensive_exactness_warning_code(CODE) CODE
#endif // CGAL_BOPS_NO_WARNINGS


#endif
