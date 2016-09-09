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
// file          : include/CGAL/Tree_assertions.h
// package       : SearchStructures (2.60)
// source        : include/CGAL/Tree_assertions.h
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 2001/07/26 07:48:03 $
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
//
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_TREE_ASSERTIONS_H
#define CGAL_TREE_ASSERTIONS_H

#ifndef CGAL_ASSERTIONS_H
#  include <CGAL/assertions.h>
#endif


// macro definitions
// =================
// assertions
// ----------


#if defined(CGAL_TREE_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || defined(NDEBUG)
#  define CGAL_Tree_assertion(EX) ((void)0)
#  define CGAL_Tree_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_assertion_code(CODE)
#else
#  define CGAL_Tree_assertion(EX) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_assertion_msg(EX,MSG) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_assertion_code(CODE) CODE
#endif // CGAL_TREE_NO_ASSERTIONS

#if defined(CGAL_TREE_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_TREE_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_Tree_exactness_assertion(EX) ((void)0)
#  define CGAL_Tree_exactness_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_exactness_assertion_code(CODE)
#else
#  define CGAL_Tree_exactness_assertion(EX) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_exactness_assertion_msg(EX,MSG) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_exactness_assertion_code(CODE) CODE
#endif // CGAL_TREE_NO_ASSERTIONS

#if defined(CGAL_TREE_NO_ASSERTIONS) \
  || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_TREE_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_Tree_expensive_assertion(EX) ((void)0)
#  define CGAL_Tree_expensive_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_expensive_assertion_code(CODE)
#else
#  define CGAL_Tree_expensive_assertion(EX) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_expensive_assertion_msg(EX,MSG) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_expensive_assertion_code(CODE) CODE
#endif // CGAL_TREE_NO_ASSERTIONS

#if defined(CGAL_TREE_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_TREE_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_TREE_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_Tree_expensive_exactness_assertion(EX) ((void)0)
#  define CGAL_Tree_expensive_exactness_assertion_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_expensive_exactness_assertion_code(CODE)
#else
#  define CGAL_Tree_expensive_exactness_assertion(EX) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_expensive_exactness_assertion_msg(EX,MSG) \
   ((EX)?((void)0):assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_expensive_exactness_assertion_code(CODE) CODE
#endif // CGAL_TREE_NO_ASSERTIONS


// preconditions
// -------------

#if defined(CGAL_TREE_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_Tree_precondition(EX) ((void)0)
#  define CGAL_Tree_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_precondition_code(CODE)
#else
#  define CGAL_Tree_precondition(EX) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_precondition_msg(EX,MSG) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_precondition_code(CODE) CODE
#endif // CGAL_TREE_NO_PRECONDITIONS

#if defined(CGAL_TREE_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_TREE_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_Tree_exactness_precondition(EX) ((void)0)
#  define CGAL_Tree_exactness_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_exactness_precondition_code(CODE)
#else
#  define CGAL_Tree_exactness_precondition(EX) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_exactness_precondition_msg(EX,MSG) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_exactness_precondition_code(CODE) CODE
#endif // CGAL_TREE_NO_PRECONDITIONS

#if defined(CGAL_TREE_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_TREE_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_Tree_expensive_precondition(EX) ((void)0)
#  define CGAL_Tree_expensive_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_expensive_precondition_code(CODE)
#else
#  define CGAL_Tree_expensive_precondition(EX) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_expensive_precondition_msg(EX,MSG) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_expensive_precondition_code(CODE) CODE
#endif // CGAL_TREE_NO_PRECONDITIONS

#if defined(CGAL_TREE_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_TREE_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_TREE_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_Tree_expensive_exactness_precondition(EX) ((void)0)
#  define CGAL_Tree_expensive_exactness_precondition_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_expensive_exactness_precondition_code(CODE)
#else
#  define CGAL_Tree_expensive_exactness_precondition(EX) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_expensive_exactness_precondition_msg(EX,MSG) \
   ((EX)?((void)0):precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_expensive_exactness_precondition_code(CODE) CODE
#endif // CGAL_TREE_NO_PRECONDITIONS


// postconditions
// --------------

#if defined(CGAL_TREE_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_Tree_postcondition(EX) ((void)0)
#  define CGAL_Tree_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_postcondition_code(CODE)
#else
#  define CGAL_Tree_postcondition(EX) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_postcondition_code(CODE) CODE
#endif // CGAL_TREE_NO_POSTCONDITIONS

#if defined(CGAL_TREE_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_TREE_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_Tree_exactness_postcondition(EX) ((void)0)
#  define CGAL_Tree_exactness_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_exactness_postcondition_code(CODE)
#else
#  define CGAL_Tree_exactness_postcondition(EX) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_exactness_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_exactness_postcondition_code(CODE) CODE
#endif // CGAL_TREE_NO_POSTCONDITIONS

#if defined(CGAL_TREE_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_TREE_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_Tree_expensive_postcondition(EX) ((void)0)
#  define CGAL_Tree_expensive_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_expensive_postcondition_code(CODE)
#else
#  define CGAL_Tree_expensive_postcondition(EX) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_expensive_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_expensive_postcondition_code(CODE) CODE
#endif // CGAL_TREE_NO_POSTCONDITIONS

#if defined(CGAL_TREE_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_TREE_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_TREE_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_Tree_expensive_exactness_postcondition(EX) ((void)0)
#  define CGAL_Tree_expensive_exactness_postcondition_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_expensive_exactness_postcondition_code(CODE)
#else
#  define CGAL_Tree_expensive_exactness_postcondition(EX) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_expensive_exactness_postcondition_msg(EX,MSG) \
   ((EX)?((void)0):postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_expensive_exactness_postcondition_code(CODE) CODE
#endif // CGAL_TREE_NO_POSTCONDITIONS


// warnings
// --------

#if defined(CGAL_TREE_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || defined(NDEBUG)
#  define CGAL_Tree_warning(EX) ((void)0)
#  define CGAL_Tree_warning_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_warning_code(CODE)
#else
#  define CGAL_Tree_warning(EX) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_warning_msg(EX,MSG) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_warning_code(CODE) CODE
#endif // CGAL_TREE_NO_WARNINGS

#if defined(CGAL_TREE_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_TREE_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_Tree_exactness_warning(EX) ((void)0)
#  define CGAL_Tree_exactness_warning_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_exactness_warning_code(CODE)
#else
#  define CGAL_Tree_exactness_warning(EX) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_exactness_warning_msg(EX,MSG) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_exactness_warning_code(CODE) CODE
#endif // CGAL_TREE_NO_WARNINGS

#if defined(CGAL_TREE_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_TREE_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_Tree_expensive_warning(EX) ((void)0)
#  define CGAL_Tree_expensive_warning_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_expensive_warning_code(CODE)
#else
#  define CGAL_Tree_expensive_warning(EX) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_expensive_warning_msg(EX,MSG) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_expensive_warning_code(CODE) CODE
#endif // CGAL_TREE_NO_WARNINGS

#if defined(CGAL_TREE_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_TREE_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_TREE_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_Tree_expensive_exactness_warning(EX) ((void)0)
#  define CGAL_Tree_expensive_exactness_warning_msg(EX,MSG) ((void)0)
#  define CGAL_Tree_expensive_exactness_warning_code(CODE)
#else
#  define CGAL_Tree_expensive_exactness_warning(EX) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, 0))
#  define CGAL_Tree_expensive_exactness_warning_msg(EX,MSG) \
   ((EX)?((void)0):warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_Tree_expensive_exactness_warning_code(CODE) CODE
#endif // CGAL_TREE_NO_WARNINGS


#endif
