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
// file          : include/CGAL/triangulation_assertions.h
// package       : Triangulation (3.17)
// source        : web/triangulation.fw
// revision      : $Revision: 1.1.2.7 $
// revision_date : $Date: 1999/03/31 15:43:58 $
// author(s)     : Andreas Fabri
//
// coordinator   : Herve Bronnimann
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGULATION_ASSERTIONS_H
#define CGAL_TRIANGULATION_ASSERTIONS_H



#ifndef CGAL_ASSERTIONS_H
#  include <CGAL/assertions.h>
#endif


// macro definitions
// =================
// assertions
// ----------


#if defined(CGAL_TRIANGULATION_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || defined(NDEBUG)
#  define CGAL_triangulation_assertion(EX) ((void)0)
#  define CGAL_triangulation_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_assertion_code(CODE)
#else
#  define CGAL_triangulation_assertion(EX) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_assertion_msg(EX,MSG) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_assertion_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_ASSERTIONS

#if defined(CGAL_TRIANGULATION_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_TRIANGULATION_CHECK_EXACTNESS) \
  && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_triangulation_exactness_assertion(EX) ((void)0)
#  define CGAL_triangulation_exactness_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_exactness_assertion_code(CODE)
#else
#  define CGAL_triangulation_exactness_assertion(EX) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_exactness_assertion_msg(EX,MSG) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_exactness_assertion_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_ASSERTIONS

#if defined(CGAL_TRIANGULATION_NO_ASSERTIONS) \
  || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_TRIANGULATION_CHECK_EXPENSIVE) \
  && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_triangulation_expensive_assertion(EX) ((void)0)
#  define CGAL_triangulation_expensive_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_expensive_assertion_code(CODE)
#else
#  define CGAL_triangulation_expensive_assertion(EX) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_expensive_assertion_msg(EX,MSG) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_expensive_assertion_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_ASSERTIONS

#if defined(CGAL_TRIANGULATION_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_TRIANGULATION_CHECK_EXACTNESS) \
  && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_TRIANGULATION_CHECK_EXPENSIVE) \
  && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_triangulation_expensive_exactness_assertion(EX) ((void)0)
#  define CGAL_triangulation_expensive_exactness_assertion_msg(EX,MSG) \
   ((void)0)
#  define CGAL_triangulation_expensive_exactness_assertion_code(CODE)
#else
#  define CGAL_triangulation_expensive_exactness_assertion(EX) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_expensive_exactness_assertion_msg(EX,MSG) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_expensive_exactness_assertion_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_ASSERTIONS


// preconditions
// -------------

#if defined(CGAL_TRIANGULATION_NO_PRECONDITIONS) \
  || defined(CGAL_NO_PRECONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_triangulation_precondition(EX) ((void)0)
#  define CGAL_triangulation_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_precondition_code(CODE)
#else
#  define CGAL_triangulation_precondition(EX) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_precondition_msg(EX,MSG) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_precondition_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_PRECONDITIONS

#if defined(CGAL_TRIANGULATION_NO_PRECONDITIONS) \
  || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_TRIANGULATION_CHECK_EXACTNESS) \
  && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_triangulation_exactness_precondition(EX) ((void)0)
#  define CGAL_triangulation_exactness_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_exactness_precondition_code(CODE)
#else
#  define CGAL_triangulation_exactness_precondition(EX) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_exactness_precondition_msg(EX,MSG) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_exactness_precondition_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_PRECONDITIONS

#if defined(CGAL_TRIANGULATION_NO_PRECONDITIONS) \
  || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_TRIANGULATION_CHECK_EXPENSIVE) \
  && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_triangulation_expensive_precondition(EX) ((void)0)
#  define CGAL_triangulation_expensive_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_expensive_precondition_code(CODE)
#else
#  define CGAL_triangulation_expensive_precondition(EX) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_expensive_precondition_msg(EX,MSG) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_expensive_precondition_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_PRECONDITIONS

#if defined(CGAL_TRIANGULATION_NO_PRECONDITIONS) \
  || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_TRIANGULATION_CHECK_EXACTNESS) \
  && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_TRIANGULATION_CHECK_EXPENSIVE) \
  && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#define CGAL_triangulation_expensive_exactness_precondition(EX) \
 ((void)0)
#define CGAL_triangulation_expensive_exactness_precondition_msg(EX,MSG)\
  ((void)0)
#define CGAL_triangulation_expensive_exactness_precondition_code(CODE)
#else
#  define CGAL_triangulation_expensive_exactness_precondition(EX) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_expensive_exactness_precondition_msg(EX,MSG) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define
  CGAL_triangulation_expensive_exactness_precondition_code(CODE) \
  CODE
#endif // CGAL_TRIANGULATION_NO_PRECONDITIONS


// postconditions
// --------------

#if defined(CGAL_TRIANGULATION_NO_POSTCONDITIONS) \
  || defined(CGAL_NO_POSTCONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_triangulation_postcondition(EX) ((void)0)
#  define CGAL_triangulation_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_postcondition_code(CODE)
#else
#  define CGAL_triangulation_postcondition(EX) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_postcondition_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_POSTCONDITIONS

#if defined(CGAL_TRIANGULATION_NO_POSTCONDITIONS) 
  || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_TRIANGULATION_CHECK_EXACTNESS) 
  && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_triangulation_exactness_postcondition(EX) ((void)0)
#  define CGAL_triangulation_exactness_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_exactness_postcondition_code(CODE)
#else
#  define CGAL_triangulation_exactness_postcondition(EX) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_exactness_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_exactness_postcondition_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_POSTCONDITIONS

#if defined(CGAL_TRIANGULATION_NO_POSTCONDITIONS) \
  || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_TRIANGULATION_CHECK_EXPENSIVE) \
  && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_triangulation_expensive_postcondition(EX) ((void)0)
#  define CGAL_triangulation_expensive_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_expensive_postcondition_code(CODE)
#else
#  define CGAL_triangulation_expensive_postcondition(EX) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_expensive_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_expensive_postcondition_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_POSTCONDITIONS

#if defined(CGAL_TRIANGULATION_NO_POSTCONDITIONS) \
  || defined(CGAL_NO_POSTCONDITIONS) \
  ||(!defined(CGAL_TRIANGULATION_CHECK_EXACTNESS) \
   && !defined(CGAL_CHECK_EXACTNESS)) \
  ||(!defined(CGAL_TRIANGULATION_CHECK_EXPENSIVE) \
   && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_triangulation_expensive_exactness_postcondition(EX) \
  ((void)0)
#  define \
  CGAL_triangulation_expensive_exactness_postcondition_msg(EX,MSG) \
   ((void)0)
#  define \
  CGAL_triangulation_expensive_exactness_postcondition_code(CODE) CODE
#else
#  define CGAL_triangulation_expensive_exactness_postcondition(EX) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_expensive_exactness_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define \
  CGAL_triangulation_expensive_exactness_postcondition_code(CODE) \
   CODE
#endif // CGAL_TRIANGULATION_NO_POSTCONDITIONS


// warnings
// --------

#if defined(CGAL_TRIANGULATION_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || defined(NDEBUG)
#  define CGAL_triangulation_warning(EX) ((void)0)
#  define CGAL_triangulation_warning_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_warning_code(CODE)
#else
#  define CGAL_triangulation_warning(EX) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_warning_msg(EX,MSG) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_warning_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_WARNINGS

#if defined(CGAL_TRIANGULATION_NO_WARNINGS) 
  || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_TRIANGULATION_CHECK_EXACTNESS) \
  && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_triangulation_exactness_warning(EX) ((void)0)
#  define CGAL_triangulation_exactness_warning_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_exactness_warning_code(CODE)
#else
#  define CGAL_triangulation_exactness_warning(EX) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_exactness_warning_msg(EX,MSG) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_exactness_warning_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_WARNINGS

#if defined(CGAL_TRIANGULATION_NO_WARNINGS) 
  || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_TRIANGULATION_CHECK_EXPENSIVE) 
  && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_triangulation_expensive_warning(EX) ((void)0)
#  define CGAL_triangulation_expensive_warning_msg(EX,MSG) ((void)0)
#  define CGAL_triangulation_expensive_warning_code(CODE)
#else
#  define CGAL_triangulation_expensive_warning(EX) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_expensive_warning_msg(EX,MSG) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_expensive_warning_code(CODE) CODE
#endif // CGAL_TRIANGULATION_NO_WARNINGS

#if defined(CGAL_TRIANGULATION_NO_WARNINGS) 
  || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_TRIANGULATION_CHECK_EXACTNESS) \
  && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_TRIANGULATION_CHECK_EXPENSIVE) \
  && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_triangulation_expensive_exactness_warning(EX) \
  ((void)0)
#  define CGAL_triangulation_expensive_exactness_warning_msg(EX,MSG) \
  ((void)0)
#  define CGAL_triangulation_expensive_exactness_warning_code(CODE)
#else
#  define CGAL_triangulation_expensive_exactness_warning(EX) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_triangulation_expensive_exactness_warning_msg(EX,MSG) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_triangulation_expensive_exactness_warning_code(CODE) \
   CODE
#endif // CGAL_TRIANGULATION_NO_WARNINGS



#endif

