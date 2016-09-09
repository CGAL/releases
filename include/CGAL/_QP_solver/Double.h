// Copyright (c) 1997-2001  ETH Zurich (Switzerland).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/_QP_solver/include/CGAL/_QP_solver/Double.h,v $
// $Revision: 1.5 $ $Date: 2003/09/18 10:26:43 $
// $Name: current_submission $
//
// Author(s)     : Sven Sch�nherr <sven@inf.ethz.ch>

#ifndef CGAL_GMP_DOUBLE_H
#define CGAL_GMP_DOUBLE_H

#include <CGAL/basic.h>
#include <CGAL/_QP_solver/gmp_double.h>

CGAL_BEGIN_NAMESPACE

template<> struct Number_type_traits<GMP::Double> {
  typedef Tag_false  Has_gcd_tag;
  typedef Tag_true   Has_division_tag;
  typedef Tag_false  Has_sqrt_tag;
};

inline
double
to_double( GMP::Double d) { return d.to_double(); }

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
