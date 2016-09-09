// Copyright (c) 1999,2003,2004  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/_QP_solver/include/CGAL/_QP_solver/Double.h,v $
// $Revision: 1.10 $ $Date: 2004/09/21 06:48:05 $
// $Name:  $
//
// Author(s)     : Sven Schoenherr <sven@inf.ethz.ch>

#ifndef CGAL_GMP_DOUBLE_H
#define CGAL_GMP_DOUBLE_H

#include <CGAL/basic.h>
#include <CGAL/_QP_solver/gmp_double.h>

CGAL_BEGIN_NAMESPACE

template<> struct Number_type_traits<GMP::Double> {
  typedef Tag_false  Has_gcd;
  typedef Tag_true   Has_division;
  typedef Tag_false  Has_sqrt;

  typedef Tag_false  Has_exact_ring_operations;
  typedef Tag_false  Has_exact_division;
  typedef Tag_false  Has_exact_sqrt;
};

using GMP::to_double;

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
