// Copyright (c) 2001  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/Interval_arithmetic/include/CGAL/Static_filters/Orientation_3.h,v $
// $Revision: 1.10 $ $Date: 2003/10/21 12:17:45 $
// $Name: current_submission $
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_STATIC_FILTERS_ORIENTATION_3_H
#define CGAL_STATIC_FILTERS_ORIENTATION_3_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Filtered_exact.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Profile_counter.h>
// #include <CGAL/Static_filter_error.h> // Only used to precompute constants

CGAL_BEGIN_NAMESPACE

template <class Point>
class SF_Orientation_3
{
  double _static_epsilon;

  // Computes the epsilon for Orientation_3.
  static double ori_3()
  {
    typedef Static_filter_error F;
    F t1 = F(1)-F(1);         // First translation
    F det = det3x3_by_formula(t1, t1, t1,
                              t1, t1, t1,
                              t1, t1, t1); // Full det
    double err = det.error();
    std::cerr << "*** epsilon for Orientation_3 = " << err << std::endl;
    return err;
  }

  static const double epsilon; // = 3.90799e-14; // ori_3();

protected:

  template < class R >
  friend class Static_filters;

  // These operations are reserved to Static_filters<>, because the context of
  // a predicate is linked to the one of the Static_filter<> it is a member of.
  SF_Orientation_3(const SF_Orientation_3 &s)
      : _static_epsilon(s._static_epsilon) {}

  SF_Orientation_3 & operator=(const SF_Orientation_3 &s)
  {
      _static_epsilon = s._static_epsilon;
      return *this;
  }

  SF_Orientation_3()
  {
      _static_epsilon = HUGE_VAL;
  }

public:
  typedef Orientation result_type;

  void update(double dx, double dy, double dz)
  {
      _static_epsilon = dx*dy*dz*epsilon;
  }

  Orientation operator()(const Point &p, const Point &q,
                         const Point &r, const Point &s) const
  {
    return opti_orientationC3(
	    to_double(p.x()), to_double(p.y()), to_double(p.z()),
	    to_double(q.x()), to_double(q.y()), to_double(q.z()),
	    to_double(r.x()), to_double(r.y()), to_double(r.z()),
	    to_double(s.x()), to_double(s.y()), to_double(s.z()));
  }

private:

  Orientation
  opti_orientationC3(double px, double py, double pz,
                     double qx, double qy, double qz,
		     double rx, double ry, double rz,
		     double sx, double sy, double sz) const
  {
    CGAL_PROFILER("Orientation_3 calls");

    double pqx = qx-px;
    double pqy = qy-py;
    double pqz = qz-pz;
    double prx = rx-px;
    double pry = ry-py;
    double prz = rz-pz;
    double psx = sx-px;
    double psy = sy-py;
    double psz = sz-pz;

    double det = det3x3_by_formula(pqx, pqy, pqz,
                                   prx, pry, prz,
                                   psx, psy, psz);

#if 1
    // Fully static filter first.
    if (det >  _static_epsilon) return POSITIVE;
    if (det < -_static_epsilon) return NEGATIVE;
#endif

    CGAL_PROFILER("Orientation_3 static failures");

#if 1
    // Then semi-static filter.
    double maxx = fabs(px);
    if (maxx < fabs(qx)) maxx = fabs(qx);
    if (maxx < fabs(rx)) maxx = fabs(rx);
    if (maxx < fabs(sx)) maxx = fabs(sx);
    double maxy = fabs(py);
    if (maxy < fabs(qy)) maxy = fabs(qy);
    if (maxy < fabs(ry)) maxy = fabs(ry);
    if (maxy < fabs(sy)) maxy = fabs(sy);
    double maxz = fabs(pz);
    if (maxz < fabs(qz)) maxz = fabs(qz);
    if (maxz < fabs(rz)) maxz = fabs(rz);
    if (maxz < fabs(sz)) maxz = fabs(sz);
    double eps = epsilon*maxx*maxy*maxz;

    if (det > eps)  return POSITIVE;
    if (det < -eps) return NEGATIVE;

    CGAL_PROFILER("Orientation_3 semi-static failures");
#endif

    // Experiments showed that there's practically no benefit for testing when
    // the initial substractions were done exactly.  In most cases where the
    // first filter fails, the determinant is null.  Most of those cases are
    // caught by the IA filter, but not by a second stage semi-static filter,
    // because in most cases one of the coefficient is null, and IA takes
    // advantage of this, though it's going through an inexact temporary
    // computation (which is zeroed later).

    typedef Simple_cartesian<Filtered_exact<double, MP_Float> > K;
    typedef K::Point_3 P;

    Orientation oooo = orientation(P(px,py,pz), P(qx,qy,qz),
	                           P(rx,ry,rz), P(sx,sy,sz));
    if (oooo == ZERO) {
        CGAL_PROFILER("Orientation_3 det_is_null");
    }
    return oooo;
  }

};

template <class Point>
const double SF_Orientation_3<Point>::epsilon = 3.90799e-14;

CGAL_END_NAMESPACE

#endif // CGAL_STATIC_FILTERS_ORIENTATION_3_H
