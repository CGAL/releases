// Copyright (c) 2005  Stanford University (USA).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kinetic_data_structures/include/CGAL/Polynomial/internal/Kernel/Isolating_interval.h $
// $Id: Isolating_interval.h 56668 2010-06-09 08:45:58Z sloriot $ $Date: 2010-06-09 10:45:58 +0200 (Wed, 09 Jun 2010) $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_POLYNOMIAL_INTERNAL_TO_ISOLATING_INTERVAL_H
#define CGAL_POLYNOMIAL_INTERNAL_TO_ISOLATING_INTERVAL_H

#include <CGAL/Polynomial/basic.h>

#ifdef CGAL_USE_CORE
#include <CGAL/CORE_BigRat.h>
#include <CGAL/CORE_Expr.h>
#endif

#include <CGAL/Polynomial/internal/Simple_interval_root.h>

namespace CGAL { namespace POLYNOMIAL { namespace internal {

//! Compute the sign after a root.

template <class K>
class To_isolating_interval
{
public:
  To_isolating_interval(){  }

  typedef typename std::pair<typename K::FT, typename K::FT> result_type;
  typedef typename K::Root argument_type;

  template <class T>
  const result_type& operator()(const Simple_interval_root<T> &v) const
  {
    return v.isolating_interval();
  }

#ifdef CGAL_USE_CORE
  result_type operator()(const CORE::Expr &r) const {
    double a,b;
    r.doubleInterval(a,b); // do something
    return std::make_pair(typename K::FT(a), typename K::FT(b));
  }
#endif

  std::pair<double, double> operator()(double v) const
  {
    return std::make_pair(v,v);
  }
};

} } } //namespace CGAL::POLYNOMIAL::internal
#endif
