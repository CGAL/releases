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
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/LEDA/global.h
// package       : cgal_window (1.0.4)
// revision      : 1.0.3
// revision_date : 25 June 2001
// author(s)     : Matthias Baesken, Algorithmic Solutions
//
// coordinator   : Matthias Baesken, Trier  (<baesken>) 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_WINDOW_GLOBAL_H
#define CGAL_WINDOW_GLOBAL_H

#if defined(CGAL_USE_CGAL_HEADERS)
#include <CGAL/basic.h>
#endif

//------------------------------------------------------------------------------
// global types, constants, and macros
//------------------------------------------------------------------------------

typedef void* GenPtr;    // generic pointer type

#ifndef nil
#define nil 0
#endif


#define	LEDA_PI   3.14159265358979323846
#define	LEDA_PI_2 1.57079632679489661923

//------------------------------------------------------------------------------
// values
//------------------------------------------------------------------------------

#if defined(__USE_VALUES_H__)

#include <values.h>

#else

#include <cfloat>
#include <climits>


#if !defined(MAXINT)
#define MAXINT INT_MAX
#endif

#if !defined(MAXDOUBLE)
#define MAXDOUBLE DBL_MAX
#endif

#endif


//------------------------------------------------------------------------------
// LEDA class 
//------------------------------------------------------------------------------

namespace CGAL {

struct __exportC LEDA {

static const char* copyright_string;
static const char* copyright_window_string;
};

}

#endif
