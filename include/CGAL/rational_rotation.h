// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/rational_rotation.h
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_RATIONAL_ROTATION_H
#define CGAL_RATIONAL_ROTATION_H

template < class NT >
void
CGAL_rational_rotation_approximation( const NT &  dirx,     // dir.x()
                                      const NT &  diry,     // dir.y()
                                            NT &  sin_num,  // return
                                            NT &  cos_num,  // return
                                            NT &  denom,    // return
                                      const NT &  eps_num,  // quality_bound
                                      const NT &  eps_den )
{
  const NT& n   = eps_num;
  const NT& d   = eps_den;
  const NT  NT0 = NT(0)  ;
  const NT  NT1 = NT(1)  ;
  CGAL_kernel_precondition( n > NT0 );
  CGAL_kernel_precondition( d > NT0 );
  NT & sin = sin_num;
  NT & cos = cos_num;
  NT & den = denom;
  NT   dx = CGAL_abs(dirx);
  NT   dy = CGAL_abs(diry);
  NT   sq_hypotenuse = dx*dx + dy*dy;
  NT   common_part;
  NT   diff_part;
  NT   rhs;
  bool lower_ok;
  bool upper_ok;

  if (dy > dx)
  {
     CGAL_swap (dx,dy);
  }
  // approximate sin = dy / sqrt(sq_hypotenuse)
  // if ( dy / sqrt(sq_hypotenuse) < n/d )
  if (dy * dy * d * d < sq_hypotenuse * n * n)
  {
      cos = NT1;
      sin = NT0;
      den = NT1;
  }
  else
  {
      NT  p;
      NT  q;
      NT  p0 = NT0;
      NT  q0 = NT1;
      NT  p1 = NT1;
      NT  q1 = NT1;

      for(;;)
      {
          p = p0 + p1;
          q = q0 + q1;
          sin = NT(2)*p*q;
          den = p*p + q*q;

          // sanity check for approximation
          //        sin/den < dy/sqrt(hypotenuse) + n/d
          //    &&  sin/den > dy/sqrt(hypotenuse) - n/d
          // ===    sin/den - n/d  <   dy/sqrt(sq_hypotenuse)
          //    &&  sin/den + n/d  >   dy/sqrt(sq_hypotenuse)
          // ===    (sin^2 d^2 + n^2 den^2)sq_hypotenuse - 2... < dy^2 d^2 den^2
          //    &&  (sin^2 d^2 + n^2 den^2)sq_hypotenuse + 2... > dy^2 d^2 den^2

          common_part = (sin*sin*d*d + n*n*den*den)*sq_hypotenuse;
          diff_part   = NT(2)*n*sin*d*den*sq_hypotenuse;
          rhs         = dy*dy*d*d*den*den;

          upper_ok    = (common_part - diff_part < rhs);
          lower_ok    = (common_part + diff_part > rhs);

          if ( lower_ok && upper_ok )
          {
             // if ( (p*p)%2 + (q*q)%2 > NT1)
             // {
             //     sin = p*q;
             //     cos = (q*q - p*p)/2;    // exact division
             //     den = (p*p + q*q)/2;    // exact division
             // }
             // else
             // {
                    cos = q*q - p*p;
             // }

             break;
          }
          else
          {
              // if ( dy/sqrt(sq_hypotenuse) < sin/den )
              if ( dy*dy*den*den < sin*sin*sq_hypotenuse )
              {
                  p1 = p;
                  q1 = q;
              }
              else
              {
                  p0 = p;
                  q0 = q;
              }
          }
      } // for(;;)
  }
  dx = dirx;
  dy = diry;


  if (dy > dx ) { CGAL_swap (sin,cos); }

  if (dx < NT0) { cos = - cos; }

  if (dy < NT0) { sin = - sin; }

  sin_num = sin;
  cos_num = cos;
  denom   = den;
}


#endif // CGAL_RATIONAL_ROTATION_H
