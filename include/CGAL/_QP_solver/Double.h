// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-2.2-I-51 $
// release_date  : $CGAL_Date: 2000/10/01 $
//
// file          : include/CGAL/_QP_solver/Double.h
// package       : _QP_solver (0.9)
// maintainer    : Sven Sch�nherr <sven@inf.ethz.ch>
//
// revision      : 0.1
// revision_date : 2000/08/09 00:00:00
//
// author(s)     : Sven Sch�nherr
// coordinator   : ETH Z�rich (Bernd G�rtner <gaertner@inf.ethz.ch>)
//
// implementation: requirements for CGAL number types
// ======================================================================

#ifndef CGAL_GMP_DOUBLE_H
#define CGAL_GMP_DOUBLE_H

#include <CGAL/basic.h>
#include <CGAL/_QP_solver/gmp_double.h>

CGAL_BEGIN_NAMESPACE

inline
double
to_double( GMP::Double d) { return d.to_double(); }

inline
Number_tag
number_type_tag( GMP::Double) { return Number_tag(); }

inline
bool is_finite( GMP::Double) { return true; }

inline
bool is_valid( GMP::Double) { return true; }

inline
io_Operator
io_tag(GMP::Double)
{ return io_Operator(); }

CGAL_END_NAMESPACE

#endif // CGAL_GMP_DOUBLE_H

// ===== EOF ==================================================================
