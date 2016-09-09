// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Conic_misc.h
// package       : Min_ellipse_2 (3.2.3)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Conic_2.aw
// revision      : $Revision: 5.7 $
// revision_date : $Date: 1999/04/19 16:19:47 $
// author(s)     : Bernd Gärtner
//                 Sven Schönherr
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: 2D Conic
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CONIC_MISC_H
#define CONIC_MISC_H

CGAL_BEGIN_NAMESPACE

template < class R>
class Conic_2;


enum Conic_type
{
    HYPERBOLA = -1,
    PARABOLA,
    ELLIPSE
};


typedef CGAL::Bounded_side Convex_side;
const Convex_side ON_CONVEX_SIDE    = CGAL::ON_BOUNDED_SIDE;
const Convex_side ON_NONCONVEX_SIDE = CGAL::ON_UNBOUNDED_SIDE;




double best_value (double *values, int nr_values,
                        double a2, double a1, double a0,
                        double b3, double b2, double b1, double b0)
{
    bool det_positive = false;
    double d, q, max_det = 0.0, det, best;
    for (int i=0; i<nr_values; ++i) {
        double x = values[i];
        d = (a2*x+a1)*x+a0;
        q = ((b3*x+b2)*x+b1)*x+b0;
        det = d*d*d/(q*q);
        if (det > 0.0)
            if (!det_positive || (det > max_det)) {
                max_det = det;
                best = x;
                det_positive = true;
            }
    }
    CGAL_optimisation_precondition (det_positive);
    return best;
}


int solve_cubic (double c3, double c2, double c1, double c0,
                      double &r1, double &r2, double &r3)
{
    if (c3 == 0.0) {
        // quadratic equation
        if (c2 == 0) {
            // linear equation
            CGAL_optimisation_precondition (c1 != 0);
            r1 = -c0/c1;
            return 1;
        }
        double D = c1*c1-4*c2*c0;
        if (D < 0.0)
            // only complex roots
            return 0;
        if (D == 0.0) {
            // one real root
            r1 = -c1/(2.0*c2);
            return 1;
        }
        // two real roots
        r1 = (-c1 + sqrt(D))/(2.0*c2);
        r2 = (-c1 - sqrt(D))/(2.0*c2);
        return 2;
    }

    // cubic equation
    // define the gamma_i
    double g2 = c2/c3,
           g1 = c1/c3,
           g0 = c0/c3;

    // define a, b
    double a  = g1 - g2*g2/3.0,
           b  = 2.0*g2*g2*g2/27.0 - g1*g2/3.0 + g0;

    if (a == 0) {
        // one real root
        r1 = cbrt(-b) - g2/3.0;
        return 1;
    }

    // define D
    double D  = a*a*a/27.0 + b*b/4.0;
    if (D >= 0.0) {
        // real case
        double u = cbrt(-b/2.0 + sqrt(D)),
               alpha = 1.0 - a/(3.0*u*u);
        if (D == 0) {
            // two distinct real roots
            r1 =  u*alpha - g2/3.0;
            r2 =  -0.5*alpha*u - g2/3.0;
            return 2;
        }
        // one real root
        r1 = u*alpha - g2/3.0;
        return 1;
    }
    // complex case
    double r_prime   = sqrt(-a/3),
           phi_prime = acos (-b/(2.0*r_prime*r_prime*r_prime))/3.0,
           u_R       = r_prime * cos (phi_prime),
           u_I       = r_prime * sin (phi_prime);
    // three distinct real roots
    r1 = 2.0*u_R - g2/3.0;
    r2 = -u_R + u_I*sqrt(3.0) - g2/3.0;
    r3 = -u_R - u_I*sqrt(3.0) - g2/3.0;
    return 3;
}



CGAL_END_NAMESPACE

#endif // CONIC_MISC_H

// ===== EOF ==================================================================
