// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/dd_geo/debug.h
// package       : Convex_hull_3 (2.6)
// source        : LEP dd_geo_kernel
// revision      : 2.1
// revision_date : 
// author(s)     : Kurt Mehlhorn
//                 Michael Seel
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
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


