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
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/LEDA/sys/win32.h
// package       : cgal_window (1.0.8)
// revision      : 1.0
// revision_date : 20 June 2001
// author(s)     : Matthias Baesken, Algorithmic Solutions
//
// coordinator   : Matthias Baesken, Trier  (<baesken>) 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_WINDOW_SYS_WIN32_H
#define CGAL_WINDOW_SYS_WIN32_H

#if !defined(__win32__)
#define __win32__
#endif


#define LITTLE_ENDIAN_MACHINE


#if defined(__BORLANDC__)

// turn of some warnings
#pragma option -w-inl -w-ccc -w-aus -w-eff -w-par -w-rch

#define __HAS_EXPLICIT_KEYWORD__
#define __explicit explicit

#if __BORLANDC__ < 0x540
#define NO_STATIC_DATA_MEMBER
#define __ALL_MEMBERS_INSTANT__
#define __typename
#define __temp_friend_decl
#else
#define __HAS_TYPENAME_KEYWORD__
#define __typename typename
#define __temp_friend_decl <>
#define __HAS_MEMBER_TEMPLATES__
#endif

#define __temp_func_inline


#include <float.h>
/*
static int leda_init_fpu()
{ _control87(PC_53,MCW_PC);
  _control87(63U,MCW_EM);
  return 0;
}

static int setdouble_ieee_for_bcc = leda_init_fpu();
*/
#endif



#if defined(_MSC_VER)


// turn off some warnings

// exception handling turned off when using std headers
#pragma warning(disable:4530)

// no matching delete operator (in presence of -GX)
#pragma warning(disable:4291)

// missing dll-interface
#pragma warning(disable:4251)
#pragma warning(disable:4275)


#define __HAS_MEMBER_TEMPLATES__
#define __HAS_EXPLICIT_KEYWORD__
#define __explicit explicit
#define __temp_friend_decl
#define __temp_func_inline


#define __HAS_TYPENAME_KEYWORD__
#define __typename typename


#include <float.h>
/*
inline int leda_init_fpu() 
{ _control87(_PC_53,_MCW_PC);
  return 0; 
}

static int setdouble_ieee_for_msc = leda_init_fpu();
*/
#endif



//------------------------------------------------------------------------------
//  DLL definitions
//------------------------------------------------------------------------------


#define __exportC
#define __exportF
#define __exportD


#define _exportC
#define _exportF
#define _exportD


#endif
