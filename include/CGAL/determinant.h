// Source: determinant.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_DETERMINANT_H
#define CGAL_DETERMINANT_H




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
