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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Kinetic_data_structures/include/CGAL/Polynomial/internal/Kernel/Isolating_interval.h $
// $Id: Isolating_interval.h 35781 2007-01-24 05:07:04Z drussel $ $Date: 2007-01-24 06:07:04 +0100 (Wed, 24 Jan 2007) $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_POLYNOMIAL_INTERNAL_TO_ISOLATING_INTERVAL_H
#define CGAL_POLYNOMIAL_INTERNAL_TO_ISOLATING_INTERVAL_H

#include <CGAL/Polynomial/basic.h>

//#ifdef CGAL_USE_CORE
#include <CGAL/CORE_BigRat.h>
#include <CGAL/CORE_Expr.h>
//#endif

#include <CGAL/Polynomial/internal/Simple_interval_root.h>

CGAL_POLYNOMIAL_BEGIN_INTERNAL_NAMESPACE

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

  //#ifdef CGAL_USE_CORE
  result_type operator()(const CORE::Expr &r) const {
    double a,b;
    r.doubleInterval(a,b); // do something
    return std::make_pair(typename K::FT(a), typename K::FT(b));
  }
  //#endif

  std::pair<double, double> operator()(double v) const
  {
    return std::make_pair(v,v);
  }
};

CGAL_POLYNOMIAL_END_INTERNAL_NAMESPACE
#endif
