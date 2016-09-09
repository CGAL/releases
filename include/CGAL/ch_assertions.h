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
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/ch_assertions.h
// package       : Convex_hull_2 (3.34)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/12/05 15:16:12 $
// author(s)     : script by Geert-Jan Giezeman and Sven Schönherr 
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================




// macro definitions
// =================
// assertions
// ----------


#if defined(CGAL_CH_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || defined(NDEBUG)
#  define CGAL_ch_assertion(EX) ((void)0)
#  define CGAL_ch_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_ch_assertion_code(CODE)
#else
#  define CGAL_ch_assertion(EX) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_assertion_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_assertion_code(CODE) CODE
#endif // CH_NO_ASSERTIONS

#if defined(CGAL_CH_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_CH_CHECK_EXACTNESS) && !defined(CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_ch_exactness_assertion(EX) ((void)0)
#  define CGAL_ch_exactness_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_ch_exactness_assertion_code(CODE)
#else
#  define CGAL_ch_exactness_assertion(EX) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_exactness_assertion_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_exactness_assertion_code(CODE) CODE
#endif // CH_NO_ASSERTIONS

#if defined(CGAL_CH_NO_ASSERTIONS) \
  || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_CH_CHECK_EXPENSIVE) && !defined(CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_ch_expensive_assertion(EX) ((void)0)
#  define CGAL_ch_expensive_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_ch_expensive_assertion_code(CODE)
#else
#  define CGAL_ch_expensive_assertion(EX) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_expensive_assertion_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_expensive_assertion_code(CODE) CODE
#endif // CH_NO_ASSERTIONS

#if defined(CGAL_CH_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_CH_CHECK_EXACTNESS) && !defined(CHECK_EXACTNESS))\
  || (!defined(CGAL_CH_CHECK_EXPENSIVE) && !defined(CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_ch_expensive_exactness_assertion(EX) ((void)0)
#  define CGAL_ch_expensive_exactness_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_ch_expensive_exactness_assertion_code(CODE)
#else
#  define CGAL_ch_expensive_exactness_assertion(EX) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_expensive_exactness_assertion_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_expensive_exactness_assertion_code(CODE) CODE
#endif // CH_NO_ASSERTIONS


// preconditions
// -------------

#if defined(CGAL_CH_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_ch_precondition(EX) ((void)0)
#  define CGAL_ch_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_ch_precondition_code(CODE)
#else
#  define CGAL_ch_precondition(EX) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_precondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_precondition_code(CODE) CODE
#endif // CH_NO_PRECONDITIONS

#if defined(CGAL_CH_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_CH_CHECK_EXACTNESS) && !defined(CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_ch_exactness_precondition(EX) ((void)0)
#  define CGAL_ch_exactness_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_ch_exactness_precondition_code(CODE)
#else
#  define CGAL_ch_exactness_precondition(EX) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_exactness_precondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_exactness_precondition_code(CODE) CODE
#endif // CH_NO_PRECONDITIONS

#if defined(CGAL_CH_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_CH_CHECK_EXPENSIVE) && !defined(CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_ch_expensive_precondition(EX) ((void)0)
#  define CGAL_ch_expensive_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_ch_expensive_precondition_code(CODE)
#else
#  define CGAL_ch_expensive_precondition(EX) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_expensive_precondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_expensive_precondition_code(CODE) CODE
#endif // CH_NO_PRECONDITIONS

#if defined(CGAL_CH_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_CH_CHECK_EXACTNESS) && !defined(CHECK_EXACTNESS))\
  || (!defined(CGAL_CH_CHECK_EXPENSIVE) && !defined(CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_ch_expensive_exactness_precondition(EX) ((void)0)
#  define CGAL_ch_expensive_exactness_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_ch_expensive_exactness_precondition_code(CODE)
#else
#  define CGAL_ch_expensive_exactness_precondition(EX) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_expensive_exactness_precondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_expensive_exactness_precondition_code(CODE) CODE
#endif // CH_NO_PRECONDITIONS


// postconditions
// --------------

#if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_ch_postcondition(EX) ((void)0)
#  define CGAL_ch_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_ch_postcondition_code(CODE)
#else
#  define CGAL_ch_postcondition(EX) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_postcondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__,MSG))
#  define CGAL_ch_postcondition_code(CODE) CODE
#endif // CH_NO_POSTCONDITIONS

#if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_CH_CHECK_EXACTNESS) && !defined(CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_ch_exactness_postcondition(EX) ((void)0)
#  define CGAL_ch_exactness_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_ch_exactness_postcondition_code(CODE)
#else
#  define CGAL_ch_exactness_postcondition(EX) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_exactness_postcondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__,MSG))
#  define CGAL_ch_exactness_postcondition_code(CODE) CODE
#endif // CH_NO_POSTCONDITIONS

#if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_CH_CHECK_EXPENSIVE) && !defined(CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_ch_expensive_postcondition(EX) ((void)0)
#  define CGAL_ch_expensive_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_ch_expensive_postcondition_code(CODE)
#else
#  define CGAL_ch_expensive_postcondition(EX) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_expensive_postcondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__,MSG))
#  define CGAL_ch_expensive_postcondition_code(CODE) CODE
#endif // CH_NO_POSTCONDITIONS

#if defined(CGAL_CH_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_CH_CHECK_EXACTNESS) && !defined(CHECK_EXACTNESS))\
  || (!defined(CGAL_CH_CHECK_EXPENSIVE) && !defined(CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_ch_expensive_exactness_postcondition(EX) ((void)0)
#  define CGAL_ch_expensive_exactness_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_ch_expensive_exactness_postcondition_code(CODE)
#else
#  define CGAL_ch_expensive_exactness_postcondition(EX) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_expensive_exactness_postcondition_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__,MSG))
#  define CGAL_ch_expensive_exactness_postcondition_code(CODE) CODE
#endif // CH_NO_POSTCONDITIONS


// warnings
// --------

#if defined(CGAL_CH_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || defined(NDEBUG)
#  define CGAL_ch_warning(EX) ((void)0)
#  define CGAL_ch_warning_msg(EX,MSG) ((void)0)
#  define CGAL_ch_warning_code(CODE)
#else
#  define CGAL_ch_warning(EX) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_warning_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_warning_code(CODE) CODE
#endif // CH_NO_WARNINGS

#if defined(CGAL_CH_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_CH_CHECK_EXACTNESS) && !defined(CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_ch_exactness_warning(EX) ((void)0)
#  define CGAL_ch_exactness_warning_msg(EX,MSG) ((void)0)
#  define CGAL_ch_exactness_warning_code(CODE)
#else
#  define CGAL_ch_exactness_warning(EX) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_exactness_warning_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_exactness_warning_code(CODE) CODE
#endif // CH_NO_WARNINGS

#if defined(CGAL_CH_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_CH_CHECK_EXPENSIVE) && !defined(CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_ch_expensive_warning(EX) ((void)0)
#  define CGAL_ch_expensive_warning_msg(EX,MSG) ((void)0)
#  define CGAL_ch_expensive_warning_code(CODE)
#else
#  define CGAL_ch_expensive_warning(EX) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_expensive_warning_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_expensive_warning_code(CODE) CODE
#endif // CH_NO_WARNINGS

#if defined(CGAL_CH_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_CH_CHECK_EXACTNESS) && !defined(CHECK_EXACTNESS))\
  || (!defined(CGAL_CH_CHECK_EXPENSIVE) && !defined(CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_ch_expensive_exactness_warning(EX) ((void)0)
#  define CGAL_ch_expensive_exactness_warning_msg(EX,MSG) ((void)0)
#  define CGAL_ch_expensive_exactness_warning_code(CODE)
#else
#  define CGAL_ch_expensive_exactness_warning(EX) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_ch_expensive_exactness_warning_msg(EX,MSG) \
   ((EX)?((void)0): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_ch_expensive_exactness_warning_code(CODE) CODE
#endif // CH_NO_WARNINGS


