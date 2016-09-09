// Copyright (c) 2001,2004  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/Interval_arithmetic/include/CGAL/Static_filters/Orientation_2.h,v $
// $Revision: 1.27 $ $Date: 2004/11/18 14:25:52 $
// $Name:  $
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_STATIC_FILTERS_ORIENTATION_2_H
#define CGAL_STATIC_FILTERS_ORIENTATION_2_H

#include <CGAL/Profile_counter.h>
#include <CGAL/Static_filter_error.h>

CGAL_BEGIN_NAMESPACE

template < typename K_base >
class SF_Orientation_2
  : public K_base::Orientation_2
{
  typedef typename K_base::Point_2          Point_2;
  typedef typename K_base::Orientation_2    Base;

public:

  Orientation
  operator()(const Point_2 &p, const Point_2 &q, const Point_2 &r) const
  {
      CGAL_PROFILER("Orientation_2 calls");

      double px, py, qx, qy, rx, ry;

      if (fit_in_double(p.x(), px) && fit_in_double(p.y(), py) &&
          fit_in_double(q.x(), qx) && fit_in_double(q.y(), qy) &&
          fit_in_double(r.x(), rx) && fit_in_double(r.y(), ry))
      {
          CGAL_PROFILER("Orientation_2 semi-static attempts");

          double pqx = qx - px;
          double pqy = qy - py;
          double prx = rx - px;
          double pry = ry - py;

          double det = det2x2_by_formula(pqx, pqy,
                                         prx, pry);

          // Then semi-static filter.
          double maxx = fabs(pqx);
          if (maxx < fabs(prx)) maxx = fabs(prx);
          double maxy = fabs(pqy);
          if (maxy < fabs(pry)) maxy = fabs(pry);
          double eps = 8.8872057372592758e-16 * maxx * maxy;

          // Protect against underflow in the computation of eps.
          if (maxx < 1e-146 || maxy < 1e-146) {
            if (maxx == 0 || maxy == 0)
              return ZERO;
          }
          else {
            if (det > eps)  return POSITIVE;
            if (det < -eps) return NEGATIVE;
          }

          CGAL_PROFILER("Orientation_2 semi-static failures");
      }

      return Base::operator()(p, q, r);
  }

  // Computes the epsilon for Orientation_2.
  static double compute_epsilon()
  {
    typedef Static_filter_error F;
    F t1 = F(1, F::ulp()/2);         // First translation
    F det = det2x2_by_formula(t1, t1,
                              t1, t1); // Full det
    double err = det.error();
    std::cerr << "*** epsilon for Orientation_2 = " << err << std::endl;
    return err;
  }
};

CGAL_END_NAMESPACE

#endif // CGAL_STATIC_FILTERS_ORIENTATION_2_H
