// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Static_filters/Orientation_2.h
// package       : Interval_arithmetic (4.141)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2002/01/28 17:13:55 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_STATIC_FILTERS_ORIENTATION_2_H
#define CGAL_STATIC_FILTERS_ORIENTATION_2_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Filtered_exact.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Profile_counter.h>
// #include <CGAL/Static_filter_error.h> // Only used to precompute constants

CGAL_BEGIN_NAMESPACE

template < class R > class Static_filters;
template < class Pt, class Or2 > class SF_Coplanar_orientation_3;

template <class Point>
class SF_Orientation_2
{
  double _static_epsilon;

  // Computes the epsilon for Orientation_2.
  static double ori_2()
  {
    typedef Static_filter_error F;
    F t1 = F(1)-F(1);         // First translation
    F det = det2x2_by_formula(t1, t1,
                              t1, t1); // Full det
    double err = det.error();
    std::cerr << "*** epsilon for Orientation_2 = " << err << std::endl;
    return err;
  }

  static const double epsilon; // = 3.55271e-15; // ori_2();

protected:

  template < class R >
  friend class Static_filters;

  template < class Pt, class Or2 >
  friend class SF_Coplanar_orientation_3;

  // These operations are reserved to Static_filters<>, because the context of
  // a predicate is linked to the one of the Static_filter<> it is a member of.
  SF_Orientation_2(const SF_Orientation_2 &s)
      : _static_epsilon(s._static_epsilon) {}

  SF_Orientation_2 & operator=(const SF_Orientation_2 &s)
  {
      _static_epsilon = s._static_epsilon;
      return *this;
  }

  SF_Orientation_2()
  {
      _static_epsilon = HUGE_VAL;
  }

public:
  typedef Orientation result_type;

  void update(double dx, double dy)
  {
      _static_epsilon = dx*dy*epsilon;
  }

  Orientation operator()(const Point &p, const Point &q, const Point &r) const
  {
    return opti_orientationC2(to_double(p.x()), to_double(p.y()),
	                      to_double(q.x()), to_double(q.y()),
	                      to_double(r.x()), to_double(r.y()));
  }

private:

  typedef Simple_cartesian<Filtered_exact<double, MP_Float> >::Point_2 P;

  Orientation
  opti_orientationC2(double px, double py,
                     double qx, double qy,
		     double rx, double ry) const
  {
    CGAL_PROFILER(calls, "Orientation_2 calls")

    double pqx = qx-px;
    double pqy = qy-py;
    double prx = rx-px;
    double pry = ry-py;

    double det = det2x2_by_formula(pqx, pqy,
                                   prx, pry);

    // Fully static filter first.
    if (det >  _static_epsilon) return POSITIVE;
    if (det < -_static_epsilon) return NEGATIVE;

    CGAL_PROFILER(st_fail, "Orientation_2 static failures")

    // Then semi-static filter.
    double maxx = fabs(px);
    if (maxx < fabs(qx)) maxx = fabs(qx);
    if (maxx < fabs(rx)) maxx = fabs(rx);
    double maxy = fabs(py);
    if (maxy < fabs(qy)) maxy = fabs(qy);
    if (maxy < fabs(ry)) maxy = fabs(ry);
    double eps = epsilon*maxx*maxy;

    if (det > eps)  return POSITIVE;
    if (det < -eps) return NEGATIVE;

    CGAL_PROFILER(fail, "Orientation_2 semi-static failures")

    Orientation oooo = orientation(P(px,py), P(qx,qy), P(rx,ry));
    if (oooo == ZERO) {
	CGAL_PROFILER(det_is_null, "Orientation_2 det_is_null")
    }
    return oooo;
  }

};

template <class Point>
const double SF_Orientation_2<Point>::epsilon = 3.55271e-15;

CGAL_END_NAMESPACE

#endif // CGAL_STATIC_FILTERS_ORIENTATION_2_H
