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

// Source: determinant.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_DETERMINANT_H
#define CGAL_DETERMINANT_H





template <class FT>
FT
CGAL_det2x2_by_formula( const FT& a, const FT& b,
                        const FT& c, const FT& d)
{
return (   a*d - b*c );
}


template <class FT>
FT
CGAL_det3x3_by_formula( const FT& a, const FT& b, const FT& c,
                        const FT& d, const FT& e, const FT& f,
                        const FT& g, const FT& h, const FT& i )
{
return (   a*(e*i - f*h)
         - d*(b*i - c*h)
         + g*(b*f - c*e) );
}


template <class FT>
FT
CGAL_det4x4_by_formula( const FT& a, const FT& b, const FT& c, const FT& d,
                        const FT& e, const FT& f, const FT& g, const FT& h,
                        const FT& i, const FT& j, const FT& k, const FT& l,
                        const FT& m, const FT& n, const FT& o, const FT& p )
{
return (  a * CGAL_det3x3_by_formula( f, g, h,
                                      j, k, l,
                                      n, o, p )
        - e * CGAL_det3x3_by_formula( b, c, d,
                                      j, k, l,
                                      n, o, p )
        + i * CGAL_det3x3_by_formula( b, c, d,
                                      f, g, h,
                                      n, o, p )
        - m * CGAL_det3x3_by_formula( b, c, d,
                                      f, g, h,
                                      j, k, l ) );
}


#endif
