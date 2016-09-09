// Copyright(c) 2005  Stanford University (USA).
// All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Kinetic_data_structures/include/CGAL/Polynomial/internal/Kernel/Rational_between_roots.h $
// $Id: Rational_between_roots.h 40016 2007-08-23 15:34:09Z drussel $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_POLYNOMIAL_KERNEL_RATIONAL_BETWEEN_ROOTS_H
#define CGAL_POLYNOMIAL_KERNEL_RATIONAL_BETWEEN_ROOTS_H

#include <CGAL/Polynomial/basic.h>
#include <CGAL/CORE_Expr.h>
#include <CGAL/Polynomial/internal/Simple_interval_root.h>

CGAL_POLYNOMIAL_BEGIN_INTERNAL_NAMESPACE

template <class K>
struct Rational_between_roots
{
  typedef typename K::FT result_type;
  typedef typename K::Root first_argument_type;
  typedef typename K::Root second_argument_type;

  Rational_between_roots(const K& ){}

  template <class T>
  static bool is_minf(T r){
    if (std::numeric_limits<result_type>::has_infinity) return r== -std::numeric_limits<result_type>::infinity();
    else return false;
  }


protected:
  template <class T>
  result_type compute(const T &r0, const T &r1) const {
    result_type ret= CGAL::to_interval(r0).second;
    result_type step=.0000000596046447753906250000000;
    do {
      while (T(ret) >= r1) {
	ret-= step;
      }
      while (T(ret) <= r0) {
	ret += step;
      }
      step/= 2.0;
    } while (T(ret) >= r1 || T(ret) <= r0);
    return ret;
  }

  template <class TK>
  result_type compute(const Simple_interval_root<TK> &r0, const Simple_interval_root<TK> &r1)const  {
    return r0.rational_between(r1);
  }

  
  result_type compute(const double &r0, const double &r1) const {
    if (std::numeric_limits<double>::has_infinity
	&& r1 == std::numeric_limits<double>::infinity()) {
      return 2*r0;
    } else {
      return (r0+r1)/2.0;
    }
  }
  
  result_type compute(const CORE::Expr &r0, const CORE::Expr &r1) const {
    result_type ret= CGAL::to_interval(r0).second;
    result_type step=.0000000596046447753906250000000;
    do {
      while (ret >= r1) {
	ret-= step;
      }
      while (ret <= r0) {
	ret += step;
      }
      step/= 2.0;
    } while (ret >= r1 || ret <= r0);
    return ret;
  }
  
  
public:

  result_type operator()(const first_argument_type &r0, const second_argument_type &r1) const
  {
    return compute(r0, r1);
  }

};

CGAL_POLYNOMIAL_END_INTERNAL_NAMESPACE
#endif
