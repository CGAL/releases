/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: determinant.h
// Author: Stefan Schirra

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
