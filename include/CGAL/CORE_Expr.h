// Copyright (c) 2002  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/Number_types/include/CGAL/CORE_Expr.h,v $
// $Revision: 1.13 $ $Date: 2003/10/21 12:21:40 $
// $Name: current_submission $
//
// Author(s)     : Sylvain Pion
 
#ifndef CGAL_CORE_EXPR_H
#define CGAL_CORE_EXPR_H

#include <CGAL/basic.h>
#include <CGAL/Number_type_traits.h>
#include <CGAL/Interval_arithmetic.h>

#include <utility>

#define CORE_LEVEL 4
#include <CORE/CORE.h>

CGAL_BEGIN_NAMESPACE

template <>
struct Number_type_traits<CORE::Expr> {
  typedef Tag_false Has_gcd;
  typedef Tag_true  Has_division;
  typedef Tag_true  Has_sqrt;
};

inline
double
to_double(const CORE::Expr & e)
{ return e.doubleValue(); }

inline
CORE::Expr
sqrt(const CORE::Expr & e)
{ return CORE::sqrt(e); }

inline
bool
is_finite(const CORE::Expr &)
{ return true; }

inline
bool
is_valid(const CORE::Expr &)
{ return true; }

inline
io_Operator
io_tag(const CORE::Expr &)
{ return io_Operator(); }

inline
Sign
sign(const CORE::Expr& e)
{ return (Sign) e.sign(); }

inline
Comparison_result
compare(const CORE::Expr& e1, const CORE::Expr& e2)
{
  return Comparison_result(e1.cmp(e2));
}

// Should not be inline, but, well...
inline
std::pair<double,double>
to_interval (const CORE::Expr & e)
{
  std::pair<double,double> result;
  e.doubleInterval(result.first, result.second);
  return result;
}

CGAL_END_NAMESPACE

#endif // CGAL_CORE_EXPR_H
