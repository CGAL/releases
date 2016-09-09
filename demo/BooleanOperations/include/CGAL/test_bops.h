//  -*- Mode: c++ -*-
// ============================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : demo/BooleanOperations/include/CGAL/test_bops.h
// source        : demo/BooleanOperations/include/CGAL/test_bops.h
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:29:00 MET 1998  $
// author(s)     :                        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef TEST_BOPS_H
#define TEST_BOPS_H

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Homogeneous.h>
#include <list.h>

//#define CGAL__BOPS_DEBUG_ON
//#define CGAL__DCEL_DEBUG_ON
//#define CGAL__DCEL__V2E_DEBUG_ON
//#define CGAL__INTERSECTING_POLYGONS_DEBUG_ON

#include <CGAL/boolean_operations_2.h>
#include <iostream.h>
//#include <CGAL/IO/ostream.h>

#ifndef Bops_test_arithmetic
#define Bops_test_arithmetic 1
#endif

#if Bops_test_arithmetic == 1
#   include <CGAL/leda_rational.h>
    typedef leda_rational TestNum;            /* exact arithmetic */
#endif

#if Bops_test_arithmetic == 2
#   include <CGAL/Quotient.h>
    typedef CGAL_Quotient<long int> TestNum;  /* exact but (very) finite */
#endif

#if Bops_test_arithmetic == 4
//#   include <CGAL/Double.h>
#   include <CGAL/double.h>
    typedef double TestNum;             /* inexact arithmetic */
#endif

#ifdef CGAL_BOPS_HOMOGENEOUS
#   include <CGAL/Quotient.h>
  typedef CGAL_Homogeneous<TestNum>  R_type;
#else
  typedef CGAL_Cartesian<TestNum>  R_type;
#endif

typedef CGAL_Point_2<R_type>           Point_2;
typedef CGAL_Segment_2<R_type>         Segment_2;
typedef CGAL_Triangle_2<R_type>        Triangle_2;
typedef CGAL_Iso_rectangle_2<R_type>   Iso_rectangle_2;
typedef list< Point_2 >                Container;
//typedef vector< Point_2 >              Container;
typedef CGAL_Polygon_2< CGAL_Polygon_traits_2<R_type>, Container >  Polygon_2;

#include "CGAL/test_bops_io.h"

#endif  // TEST_BOPS_H
