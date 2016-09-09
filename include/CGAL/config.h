// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/config.h
// author(s)     : Wieger Wesselink 
//                 Michael Hoffmann
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_CONFIG_H
#define CGAL_CONFIG_H

#define CGAL_VERSION 1.0
#define CGAL_VERSION_NR 1001010000

//----------------------------------------------------------------------//
//             include platform specific workaround flags (CGAL_CFG_...)
//----------------------------------------------------------------------//

#include <CGAL/compiler_config.h>

//----------------------------------------------------------------------//
//             do some post processing for the flags
//----------------------------------------------------------------------//

#ifdef CGAL_CFG_NO_TYPENAME
#define typename
#endif

#ifdef CGAL_CFG_NO_EXPLICIT
#define explicit
#endif

#ifdef CGAL_CFG_NO_NAMESPACE
#define CGAL_USING_NAMESPACE_STD
#else
#define CGAL_USING_NAMESPACE_STD using namespace std;
#endif

#ifdef CGAL_USE_NAMESPACE
#define CGAL_NAMESPACE_BEGIN namespace CGAL {
#define CGAL_NAMESPACE_END }
#else
#define CGAL_NAMESPACE_BEGIN
#define CGAL_NAMESPACE_END
#endif

// unset the flag CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS if it is
// just the missing typename keyword that gives problems
#ifdef CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS
#ifndef CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS_NO_TYPENAME
#undef CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS
#endif
#endif

// unset the flag CGAL_CFG_RETURN_TYPE_BUG_1 if it is
// just the missing typename keyword that gives problems
#ifdef CGAL_CFG_RETURN_TYPE_BUG_1
#ifndef CGAL_CFG_RETURN_TYPE_BUG_1_NO_TYPENAME
#undef CGAL_CFG_RETURN_TYPE_BUG_1
#endif
#endif

// unset the flag CGAL_CFG_INCOMPLETE_TYPE_BUG_4 if it is
// just the missing typename keyword that gives problems
#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_4
#ifndef CGAL_CFG_INCOMPLETE_TYPE_BUG_4_NO_TYPENAME
#undef CGAL_CFG_INCOMPLETE_TYPE_BUG_4
#endif
#endif

#ifdef CGAL_CFG_NO_TEMPLATE_FRIEND_DISTINCTION
#define CGAL_NULL_TMPL_ARGS
#else
#define CGAL_NULL_TMPL_ARGS <>
#endif

#ifdef CGAL_CFG_NO_EXPLICIT_CLASS_TEMPLATE_SPECIALISATION
#define CGAL_TEMPLATE_NULL
#else
#define CGAL_TEMPLATE_NULL template <>
#endif

//----------------------------------------------------------------------//
//             include separate workaround files
//----------------------------------------------------------------------//

#include <CGAL/workaround_return_type.h>
#include <CGAL/workaround_casts.h>
#include <CGAL/workaround_stl.h>

//----------------------------------------------------------------------//
//             definition of type bool
//----------------------------------------------------------------------//

// if there is no built-in bool and LEDA is used, we use the bool from
// LEDA - This might give a conflict with an STL that also defines its
// bool - We decided for LEDA bool, because editing an STL .h-file is
// easier than recompiling LEDA (you would need the LEDA source files)
// If LEDA is not used, we use the bool from STL.
#ifdef CGAL_CFG_NO_BUILTIN_BOOL
#if ( defined(CGAL_USE_LEDA) && !defined(CGAL_NO_LEDA_BOOL) )
#include <LEDA/basic.h>
#else
#include <pair.h>
#endif // CGAL_USE_LEDA
#endif // CGAL_CFG_NO_BUILTIN_BOOL

#endif // CGAL_CONFIG_H
