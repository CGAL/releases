//  -*- Mode: c++ -*-
// ============================================================================
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
// file          : demo/BooleanOperations/include/CGAL/test_float_bops.h
// source        : demo/BooleanOperations/include/CGAL/test_float_bops.h
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:29:01 MET 1998  $
// author(s)     :                        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef TEST_FLOAT_BOPS_H
#define TEST_FLOAT_BOPS_H

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Homogeneous.h>


#include <list>
#include <CGAL/boolean_operations_2.h>
#include <iostream>
//#include <CGAL/IO/ostream.h>

#ifndef Bops_test_arithmetic
#define Bops_test_arithmetic 4
#endif

#if Bops_test_arithmetic == 1
#   include <CGAL/Rational.h>
    typedef Rational TestNum;            /* exact arithmetic */
#endif

#if Bops_test_arithmetic == 2
    typedef Quotient<long int> TestNum;  /* exact but (very) finite */
#endif

#if Bops_test_arithmetic == 4
//#   include <CGAL/Double.h> // was used up to CGAL-I-0.9.03
#   include <CGAL/double.h>
    typedef double TestNum;             /* inexact arithmetic */
#endif

#ifdef BOPS_HOMOGENEOUS
  typedef Homogeneous<TestNum>  R_type;
#else
  typedef Cartesian<TestNum>  R_type;
#endif

typedef Point_2<R_type>           Point_2;
typedef Segment_2<R_type>         Segment_2;
typedef Triangle_2<R_type>        Triangle_2;
typedef Iso_rectangle_2<R_type>   Iso_rectangle_2;
typedef list< Point_2 >                Container;
//typedef vector< Point_2 >              Container;
typedef Polygon_2< Polygon_traits_2<R_type>, Container >  Polygon_2;

#include "CGAL/test_float_bops_io.h"

#endif  // TEST_FLOAT_BOPS_H
