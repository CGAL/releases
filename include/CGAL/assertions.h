

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
// file          : include/CGAL/assertions.h
// package       : Kernel_basic (1.2)
// source        : assertions.fw
// author(s)     : Geert-Jan Giezeman and Sven Schönherr
//
// coordinator   :  MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_ASSERTIONS_H
#define CGAL_ASSERTIONS_H

// types
// =====

enum CGAL_Failure_behaviour { CGAL_ABORT, CGAL_EXIT, CGAL_CONTINUE
//           TODO:          , CGAL_EXIT_WITH_SUCCESS  
};

// function declarations
// =====================
// failure functions
// -----------------
void CGAL_assertion_fail      ( const char*, const char*, int, const char*);
void CGAL_precondition_fail   ( const char*, const char*, int, const char*);
void CGAL_postcondition_fail  ( const char*, const char*, int, const char*);

// warning function
// ----------------
void CGAL_warning_fail( const char*, const char*, int, const char*);


// macro definitions
// =================
// assertions
// ----------


#if defined(CGAL_KERNEL_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || defined(NDEBUG)
#  define CGAL_assertion(EX) ((void)0)
#  define CGAL_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_assertion_code(CODE)
#else
#  define CGAL_assertion(EX) \
   ((EX)?((void)0):CGAL_assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_assertion_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_assertion_code(CODE) CODE
#endif // CGAL_KERNEL_NO_ASSERTIONS

#if defined(CGAL_KERNEL_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_KERNEL_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_exactness_assertion(EX) ((void)0)
#  define CGAL_exactness_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_exactness_assertion_code(CODE)
#else
#  define CGAL_exactness_assertion(EX) \
   ((EX)?((void)0):CGAL_assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_exactness_assertion_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_exactness_assertion_code(CODE) CODE
#endif // CGAL_KERNEL_NO_ASSERTIONS

#if defined(CGAL_KERNEL_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_KERNEL_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE))\
  || defined(NDEBUG)
#  define CGAL_expensive_assertion(EX) ((void)0)
#  define CGAL_expensive_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_expensive_assertion_code(CODE)
#else
#  define CGAL_expensive_assertion(EX) \
   ((EX)?((void)0):CGAL_assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_expensive_assertion_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_expensive_assertion_code(CODE) CODE
#endif // CGAL_KERNEL_NO_ASSERTIONS

#if defined(CGAL_KERNEL_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_KERNEL_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_KERNEL_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE))\
  || defined(NDEBUG)
#  define CGAL_expensive_exactness_assertion(EX) ((void)0)
#  define CGAL_expensive_exactness_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_expensive_exactness_assertion_code(CODE)
#else
#  define CGAL_expensive_exactness_assertion(EX) \
   ((EX)?((void)0):CGAL_assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_expensive_exactness_assertion_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_expensive_exactness_assertion_code(CODE) CODE
#endif // CGAL_KERNEL_NO_ASSERTIONS


// preconditions
// -------------

#if defined(CGAL_KERNEL_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_precondition(EX) ((void)0)
#  define CGAL_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_precondition_code(CODE)
#else
#  define CGAL_precondition(EX) \
   ((EX)?((void)0):CGAL_precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_precondition_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_precondition_code(CODE) CODE
#endif // CGAL_KERNEL_NO_PRECONDITIONS

#if defined(CGAL_KERNEL_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_KERNEL_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_exactness_precondition(EX) ((void)0)
#  define CGAL_exactness_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_exactness_precondition_code(CODE)
#else
#  define CGAL_exactness_precondition(EX) \
   ((EX)?((void)0):CGAL_precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_exactness_precondition_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_exactness_precondition_code(CODE) CODE
#endif // CGAL_KERNEL_NO_PRECONDITIONS

#if defined(CGAL_KERNEL_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_KERNEL_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE))\
  || defined(NDEBUG)
#  define CGAL_expensive_precondition(EX) ((void)0)
#  define CGAL_expensive_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_expensive_precondition_code(CODE)
#else
#  define CGAL_expensive_precondition(EX) \
   ((EX)?((void)0):CGAL_precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_expensive_precondition_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_expensive_precondition_code(CODE) CODE
#endif // CGAL_KERNEL_NO_PRECONDITIONS

#if defined(CGAL_KERNEL_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_KERNEL_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_KERNEL_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE))\
  || defined(NDEBUG)
#  define CGAL_expensive_exactness_precondition(EX) ((void)0)
#  define CGAL_expensive_exactness_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_expensive_exactness_precondition_code(CODE)
#else
#  define CGAL_expensive_exactness_precondition(EX) \
   ((EX)?((void)0):CGAL_precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_expensive_exactness_precondition_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_expensive_exactness_precondition_code(CODE) CODE
#endif // CGAL_KERNEL_NO_PRECONDITIONS


// postconditions
// --------------

#if defined(CGAL_KERNEL_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_postcondition(EX) ((void)0)
#  define CGAL_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_postcondition_code(CODE)
#else
#  define CGAL_postcondition(EX) \
   ((EX)?((void)0):CGAL_postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_postcondition_code(CODE) CODE
#endif // CGAL_KERNEL_NO_POSTCONDITIONS

#if defined(CGAL_KERNEL_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_KERNEL_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_exactness_postcondition(EX) ((void)0)
#  define CGAL_exactness_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_exactness_postcondition_code(CODE)
#else
#  define CGAL_exactness_postcondition(EX) \
   ((EX)?((void)0):CGAL_postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_exactness_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_exactness_postcondition_code(CODE) CODE
#endif // CGAL_KERNEL_NO_POSTCONDITIONS

#if defined(CGAL_KERNEL_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_KERNEL_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE))\
  || defined(NDEBUG)
#  define CGAL_expensive_postcondition(EX) ((void)0)
#  define CGAL_expensive_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_expensive_postcondition_code(CODE)
#else
#  define CGAL_expensive_postcondition(EX) \
   ((EX)?((void)0):CGAL_postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_expensive_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_expensive_postcondition_code(CODE) CODE
#endif // CGAL_KERNEL_NO_POSTCONDITIONS

#if defined(CGAL_KERNEL_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_KERNEL_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_KERNEL_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE))\
  || defined(NDEBUG)
#  define CGAL_expensive_exactness_postcondition(EX) ((void)0)
#  define CGAL_expensive_exactness_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_expensive_exactness_postcondition_code(CODE)
#else
#  define CGAL_expensive_exactness_postcondition(EX) \
   ((EX)?((void)0):CGAL_postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_expensive_exactness_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_expensive_exactness_postcondition_code(CODE) CODE
#endif // CGAL_KERNEL_NO_POSTCONDITIONS


// warnings
// --------

#if defined(CGAL_KERNEL_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || defined(NDEBUG)
#  define CGAL_warning(EX) ((void)0)
#  define CGAL_warning_msg(EX,MSG) ((void)0)
#  define CGAL_warning_code(CODE)
#else
#  define CGAL_warning(EX) \
   ((EX)?((void)0):CGAL_warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_warning_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_warning_code(CODE) CODE
#endif // CGAL_KERNEL_NO_WARNINGS

#if defined(CGAL_KERNEL_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_KERNEL_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_exactness_warning(EX) ((void)0)
#  define CGAL_exactness_warning_msg(EX,MSG) ((void)0)
#  define CGAL_exactness_warning_code(CODE)
#else
#  define CGAL_exactness_warning(EX) \
   ((EX)?((void)0):CGAL_warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_exactness_warning_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_exactness_warning_code(CODE) CODE
#endif // CGAL_KERNEL_NO_WARNINGS

#if defined(CGAL_KERNEL_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_KERNEL_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE))\
  || defined(NDEBUG)
#  define CGAL_expensive_warning(EX) ((void)0)
#  define CGAL_expensive_warning_msg(EX,MSG) ((void)0)
#  define CGAL_expensive_warning_code(CODE)
#else
#  define CGAL_expensive_warning(EX) \
   ((EX)?((void)0):CGAL_warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_expensive_warning_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_expensive_warning_code(CODE) CODE
#endif // CGAL_KERNEL_NO_WARNINGS

#if defined(CGAL_KERNEL_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_KERNEL_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_KERNEL_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE))\
  || defined(NDEBUG)
#  define CGAL_expensive_exactness_warning(EX) ((void)0)
#  define CGAL_expensive_exactness_warning_msg(EX,MSG) ((void)0)
#  define CGAL_expensive_exactness_warning_code(CODE)
#else
#  define CGAL_expensive_exactness_warning(EX) \
   ((EX)?((void)0):CGAL_warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_expensive_exactness_warning_msg(EX,MSG) \
   ((EX)?((void)0):CGAL_warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_expensive_exactness_warning_code(CODE) CODE
#endif // CGAL_KERNEL_NO_WARNINGS


// failure handler declarations
// ==========================
// failure handler
// ---------------
typedef
    void
    (*CGAL_Failure_function)(
        const char*, const char*, const char*, int, const char*);

CGAL_Failure_function
CGAL_set_error_handler( CGAL_Failure_function handler);

CGAL_Failure_function
CGAL_set_warning_handler( CGAL_Failure_function handler);

// failure behaviour handler
// -------------------------
CGAL_Failure_behaviour
CGAL_set_error_behaviour(CGAL_Failure_behaviour eb);

CGAL_Failure_behaviour
CGAL_set_warning_behaviour(CGAL_Failure_behaviour eb);

#endif // CGAL_ASSERTIONS_H

