// Copyright (c) 2011 GeometryFactory Sarl (France)
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL: https://github.com/CGAL/cgal/blob/v5.1.4/Filtered_kernel/include/CGAL/internal/Static_filters/Equal_3.h $
// $Id: Equal_3.h 52164b1 2019-10-19T15:34:59+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Andreas Fabri


#ifndef CGAL_INTERNAL_STATIC_FILTERS_EQUAL_3_H
#define CGAL_INTERNAL_STATIC_FILTERS_EQUAL_3_H

#include <CGAL/Bbox_3.h>
#include <CGAL/Profile_counter.h>
#include <CGAL/internal/Static_filters/tools.h>
#include <cmath>
#include <iostream>

namespace CGAL {

namespace internal {

namespace Static_filters_predicates {


template < typename K_base >
class Equal_3
  : public K_base::Equal_3
{
  typedef typename K_base::Point_3   Point_3;
  typedef typename K_base::Vector_3  Vector_3;
  typedef typename K_base::Equal_3   Base;

public:

  typedef typename Base::result_type  result_type;


#ifndef CGAL_CFG_MATCHING_BUG_6
  using Base::operator();
#else // CGAL_CFG_MATCHING_BUG_6
  template <typename T>
  result_type
  operator()(const T& t1, const T& t2) const
  {
    return Base()(t1,t2);
  }
#endif // CGAL_CFG_MATCHING_BUG_6


  result_type operator()(const Point_3 &p, const Point_3& q) const
  {
    CGAL_BRANCH_PROFILER(std::string("semi-static attempts/calls to   : ") +
                         std::string(CGAL_PRETTY_FUNCTION), tmp);

    Get_approx<Point_3> get_approx; // Identity functor for all points
                                    // but lazy points
    double px, py, pz, qx, qy, qz;

    if (fit_in_double(get_approx(p).x(), px) && fit_in_double(get_approx(p).y(), py) &&
        fit_in_double(get_approx(p).z(), pz) &&
        fit_in_double(get_approx(q).x(), qx) && fit_in_double(get_approx(q).y(), qy) &&
        fit_in_double(get_approx(q).z(), qz) )
    {
      CGAL_BRANCH_PROFILER_BRANCH(tmp);
      return px == qx && py == qy && pz == qz;
    }
    return Base::operator()(p, q);
  }


  result_type operator()(const Vector_3 &p, const Vector_3& q) const
  {
    CGAL_BRANCH_PROFILER(std::string("semi-static attempts/calls to   : ") +
                         std::string(CGAL_PRETTY_FUNCTION), tmp);

    Get_approx<Vector_3> get_approx; // Identity functor for all points
                                     // but lazy points
    double px, py, pz, qx, qy, qz;

    if (fit_in_double(get_approx(p).x(), px) && fit_in_double(get_approx(p).y(), py) &&
        fit_in_double(get_approx(p).z(), pz) &&
        fit_in_double(get_approx(q).x(), qx) && fit_in_double(get_approx(q).y(), qy) &&
        fit_in_double(get_approx(q).z(), qz) )
    {
      CGAL_BRANCH_PROFILER_BRANCH(tmp);
      return px == qx && py == qy && pz == qz;
    }
    return Base::operator()(p, q);
  }

}; // end class Equal_3

} // end namespace Static_filters_predicates

} // end namespace internal

} // end namespace CGAL

#endif  // CGAL_INTERNAL_STATIC_FILTERS_EQUAL_3_H
