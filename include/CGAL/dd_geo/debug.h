// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/dd_geo/debug.h
// package       : Convex_hull_3 (1.1.3)
// source        : LEP dd_geo_kernel
// revision      : 2.1
// revision_date : 
// author(s)     : Kurt Mehlhorn
//                 Michael Seel
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
/*******************************************************************************
+
+  LEP dd_geokernel 2.1
+
+  This file is part of the research version of a LEDA extension package,
+  that can be used free of charge in academic research and teaching. 
+  Any commercial use of this software requires a commercial license,
+  which is distributed by the Algorithmic Solutions GmbH, 
+  Postfach 151101, 66041 Saarbruecken, FRG (fax +49 681 31104).
+
+  Copyright (c) 1997-1998  by  Max-Planck-Institut fuer Informatik
+  Im Stadtwald, 66123 Saarbruecken, Germany     
+  All rights reserved.
+ 
*******************************************************************************/

//#ifndef LEDA_DEBUG_H
//#define LEDA_DEBUG_H

#include <LEDA/stream.h>

#undef TRACE
#undef TRACEN
#undef TRACEV
#undef CTRACE
#undef CTRACEN
#undef ASSERT

#ifdef _DEBUG
#define TRACE(t)   cerr << " " << t  
#else
#define TRACE(t) 
#endif

#ifdef _DEBUG
#define TRACEV(t)   cout << " " << #t << " = " << (t)  << endl
#else
#define TRACEV(t) 
#endif

#ifdef _DEBUG
#define TRACEN(t)   cerr << " " << t << "\n"
#else
#define TRACEN(t) 
#endif

#ifdef _DEBUG
#define CTRACE(b,t)  if(b) cerr << " " << t; else cerr << " 0"
#else
#define CTRACE(b,t) 
#endif

#ifdef _DEBUG
#define CTRACEN(b,t)  if(b) cerr << " " << t << "\n"; else cerr << " 0\n"
#else
#define CTRACEN(b,t) 
#endif

#ifndef _ASSERT
#define  ASSERT(cond,fstr) 
#else
#define ASSERT(cond,fstr)   \
  if (!(cond)) {       \
    cerr << "   ASSERT:   " << #fstr << endl; \
    cerr << "   COND:     " << #cond << endl; \
    cerr << "   POSITION: " << __FILE__ << " at line " << __LINE__ << endl; \
    abort();           \
  }
#endif


//#endif //LEDA_DEBUG_H


