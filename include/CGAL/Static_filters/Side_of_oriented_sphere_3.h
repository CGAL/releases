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
// $Source: /CVSROOT/CGAL/Packages/Interval_arithmetic/include/CGAL/Static_filters/Side_of_oriented_sphere_3.h,v $
// $Revision: 1.11 $ $Date: 2003/10/21 12:17:46 $
// $Name: current_submission $
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_STATIC_FILTERS_SIDE_OF_ORIENTED_SPHERE_3_H
#define CGAL_STATIC_FILTERS_SIDE_OF_ORIENTED_SPHERE_3_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Filtered_exact.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Profile_counter.h>
// #include <CGAL/Static_filter_error.h> // Only used to precompute constants

CGAL_BEGIN_NAMESPACE

template <class Point>
class SF_Side_of_oriented_sphere_3
{
  double _static_epsilon;

  // Computes the epsilon for In_sphere_3.
  static double sph_3()
  {
    typedef CGAL::Static_filter_error F;
    F t1 = F(1)-F(1);         // First translation
    F sq = t1*t1+t1*t1+t1*t1; // squares
    F det = det4x4_by_formula(t1, t1, t1, sq,
                              t1, t1, t1, sq,
                              t1, t1, t1, sq,
                              t1, t1, t1, sq); // Full det
    double err = det.error();
    std::cerr << "*** epsilon for In_sphere_3 = " << err << std::endl;
    return err;
  }

  static const double epsilon; // = 3.6664e-12; // sph_3();

protected:

  template < class R >
  friend class Static_filters;

  // These operations are reserved to Static_filters<>, because the context of
  // a predicate is linked to the one of the Static_filter<> it is a member of.
  SF_Side_of_oriented_sphere_3(const SF_Side_of_oriented_sphere_3 &s)
      : _static_epsilon(s._static_epsilon) {}

  SF_Side_of_oriented_sphere_3& operator=(const SF_Side_of_oriented_sphere_3&s)
  {
      _static_epsilon = s._static_epsilon;
      return *this;
  }
  
  SF_Side_of_oriented_sphere_3()
  {
      _static_epsilon = HUGE_VAL;
  }

public:
  typedef Oriented_side result_type;

  void update(double dx, double dy, double dz)
  {
      _static_epsilon = epsilon*dx*dy*dz*2*(dx*dx+dy*dy+dz*dz);
  }

  Oriented_side operator()(const Point &p, const Point &q, const Point &r,
	                   const Point &s, const Point &t) const
  {
    return opti_in_sphereC3(
	    to_double(p.x()), to_double(p.y()), to_double(p.z()),
            to_double(q.x()), to_double(q.y()), to_double(q.z()),
	    to_double(r.x()), to_double(r.y()), to_double(r.z()),
	    to_double(s.x()), to_double(s.y()), to_double(s.z()),
	    to_double(t.x()), to_double(t.y()), to_double(t.z()));
  }

  Oriented_side
  opti_in_sphereC3(double px, double py, double pz,
                   double qx, double qy, double qz,
		   double rx, double ry, double rz,
		   double sx, double sy, double sz,
		   double tx, double ty, double tz) const
  {
    CGAL_PROFILER("In_sphere_3 calls");

    double ptx = px - tx;
    double pty = py - ty;
    double ptz = pz - tz;
    double pt2 = CGAL_NTS square(ptx) + CGAL_NTS square(pty)
	+ CGAL_NTS square(ptz);
    double qtx = qx - tx;
    double qty = qy - ty;
    double qtz = qz - tz;
    double qt2 = CGAL_NTS square(qtx) + CGAL_NTS square(qty)
	+ CGAL_NTS square(qtz);
    double rtx = rx - tx;
    double rty = ry - ty;
    double rtz = rz - tz;
    double rt2 = CGAL_NTS square(rtx) + CGAL_NTS square(rty)
	+ CGAL_NTS square(rtz);
    double stx = sx - tx;
    double sty = sy - ty;
    double stz = sz - tz;
    double st2 = CGAL_NTS square(stx) + CGAL_NTS square(sty)
	+ CGAL_NTS square(stz);
    double det = det4x4_by_formula(ptx,pty,ptz,pt2,
                                   rtx,rty,rtz,rt2,
                                   qtx,qty,qtz,qt2,
                                   stx,sty,stz,st2);

#if 1
    // Try a fully static bound first, when possible.
    if (det >  _static_epsilon) return ON_POSITIVE_SIDE;
    if (det < -_static_epsilon) return ON_NEGATIVE_SIDE;
#endif

    CGAL_PROFILER("In_sphere_3 static failures");

#if 1
    // We compute the semi-static bound.
    double maxx = fabs(px);
    if (maxx < fabs(qx)) maxx = fabs(qx);
    if (maxx < fabs(rx)) maxx = fabs(rx);
    if (maxx < fabs(sx)) maxx = fabs(sx);
    if (maxx < fabs(tx)) maxx = fabs(tx);
    double maxy = fabs(py);
    if (maxy < fabs(qy)) maxy = fabs(qy);
    if (maxy < fabs(ry)) maxy = fabs(ry);
    if (maxy < fabs(sy)) maxy = fabs(sy);
    if (maxy < fabs(ty)) maxy = fabs(ty);
    double maxz = fabs(pz);
    if (maxz < fabs(qz)) maxz = fabs(qz);
    if (maxz < fabs(rz)) maxz = fabs(rz);
    if (maxz < fabs(sz)) maxz = fabs(sz);
    if (maxz < fabs(tz)) maxz = fabs(tz);
    // maybe we can do better for the next one...
    double tt = tx*tx + ty*ty + tz*tz;
    double max2 = px*px + py*py + pz*pz;
    double qq = qx*qx + qy*qy + qz*qz;
    double rr = rx*rx + ry*ry + rz*rz;
    double ss = sx*sx + sy*sy + sz*sz;
    if (max2 < qq) max2 = qq;
    if (max2 < rr) max2 = rr;
    if (max2 < ss) max2 = ss;
    double eps = epsilon*maxx*maxy*maxz*(max2+tt);

    if (det >  eps) return ON_POSITIVE_SIDE;
    if (det < -eps) return ON_NEGATIVE_SIDE;

    CGAL_PROFILER("In_sphere_3 semi-static failures");
#endif

#if 1
    // This predicate is different from Orientation_3 in that all arguments are
    // local.  Thus the differences have a big probability to have been exact,
    // and helps a lot in reducing the bound of the last column.

    if (diff_was_exact(px, tx, ptx) &&
        diff_was_exact(py, ty, pty) &&
        diff_was_exact(pz, tz, ptz) &&
        diff_was_exact(qx, tx, qtx) &&
        diff_was_exact(qy, ty, qty) &&
        diff_was_exact(qz, tz, qtz) &&
        diff_was_exact(rx, tx, rtx) &&
        diff_was_exact(ry, ty, rty) &&
        diff_was_exact(rz, tz, rtz) &&
        diff_was_exact(sx, tx, stx) &&
        diff_was_exact(sy, ty, sty) &&
        diff_was_exact(sz, tz, stz))
    {
        CGAL_PROFILER("In_sphere_3 exact diffs");

        double max2 = ptx*ptx + pty*pty + ptz*ptz;
        double qq = qtx*qtx + qty*qty + qtz*qtz;
        double rr = rtx*rtx + rty*rty + rtz*rtz;
        double ss = stx*stx + sty*sty + stz*stz;
        if (max2 < qq) max2 = qq;
        if (max2 < rr) max2 = rr;
        if (max2 < ss) max2 = ss;
        // maxx, maxy, maxz can be based on ptx and co directly, now...
        double maxx = fabs(ptx);
        if (maxx < fabs(qtx)) maxx = fabs(qtx);
        if (maxx < fabs(rtx)) maxx = fabs(rtx);
        if (maxx < fabs(stx)) maxx = fabs(stx);
        double maxy = fabs(pty);
        if (maxy < fabs(qty)) maxy = fabs(qty);
        if (maxy < fabs(rty)) maxy = fabs(rty);
        if (maxy < fabs(sty)) maxy = fabs(sty);
        double maxz = fabs(ptz);
        if (maxz < fabs(qtz)) maxz = fabs(qtz);
        if (maxz < fabs(rtz)) maxz = fabs(rtz);
        if (maxz < fabs(stz)) maxz = fabs(stz);
        double eps = epsilon*maxx*maxy*maxz*max2;

        if (det >  eps) return ON_POSITIVE_SIDE;
        if (det < -eps) return ON_NEGATIVE_SIDE;
        CGAL_PROFILER("In_sphere_3 step2 failures");
    }
#endif
    CGAL_PROFILER("In_sphere_3 step3");

    typedef Simple_cartesian<Filtered_exact<double, MP_Float> > K;
    typedef K::Point_3 P;

    Oriented_side oooo = side_of_oriented_sphere(P(px,py,pz), P(qx,qy,qz),
	                         P(rx,ry,rz), P(sx,sy,sz), P(tx,ty,tz));
    if (oooo == ON_ORIENTED_BOUNDARY) {
        CGAL_PROFILER("In_sphere_3 is_null");
    }
    return oooo;
  }
};

template <class Point>
const double SF_Side_of_oriented_sphere_3<Point>::epsilon = 3.6664e-12;

CGAL_END_NAMESPACE

#endif // CGAL_STATIC_FILTERS_SIDE_OF_ORIENTED_SPHERE_3_H
