//  -*- Mode: c++ -*-
// ============================================================================
// 
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-0.9-I-06 $
// release_date  : $CGAL_Date: 1998/10/03 $
//
// file          : demo/BooleanOperations/include/CGAL/test_bops.h
// source        : demo/BooleanOperations/include/CGAL/test_bops.h
// revision      : $Revision: 0.9.30b $
// revision_date : $Date: Tue Mar 10 12:54:07 MET 1998  $
// author(s)     :            Wolfgang Freiseisen <Wolfgang.Freiseisen@risc.uni-linz.ac.at>
//
// coordinator   : RISC Linz
//           (Wolfgang Freiseisen <wfreisei@risc.uni-linz.ac.at>)
//
// 
// ============================================================================

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
#define Bops_test_arithmetic 2
#endif

#if Bops_test_arithmetic == 1
#   include <CGAL/Rational.h>
    typedef CGAL_Rational TestNum;            /* exact arithmetic */
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