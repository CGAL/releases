//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//


// Source: rational_rotation.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

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


 if (dy > dx )
 {
     CGAL_swap (sin,cos);
 }

 if (dx < NT0)
 {
     cos = - cos;
 }

 if (dy < NT0)
 {
     sin = - sin;
 }

 sin_num = sin;
 cos_num = cos;
 denom   = den;
}


#endif // CGAL_RATIONAL_ROTATION_H
