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

// Source: orientation_predicatesH3.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef ORIENTATION_PREDICATESH3_H
#define ORIENTATION_PREDICATESH3_H

#include <CGAL/PVDH3.h>

template < class FT, class RT>
CGAL_Orientation
CGAL_orientation( const CGAL_PointH3<FT,RT>& p,
                  const CGAL_PointH3<FT,RT>& q,
                  const CGAL_PointH3<FT,RT>& r,
                  const CGAL_PointH3<FT,RT>& s)
{
 RT det = - p.hw()*(  q.hx()*( r.hy()*s.hz() - r.hz()*s.hy() )
                    - r.hx()*( q.hy()*s.hz() - q.hz()*s.hy() )
                    + s.hx()*( q.hy()*r.hz() - q.hz()*r.hy() ) )
          + q.hw()*(  p.hx()*( r.hy()*s.hz() - r.hz()*s.hy() )
                    - r.hx()*( p.hy()*s.hz() - p.hz()*s.hy() )
                    + s.hx()*( p.hy()*r.hz() - p.hz()*r.hy() ) )
          - r.hw()*(  p.hx()*( q.hy()*s.hz() - q.hz()*s.hy() )
                    - q.hx()*( p.hy()*s.hz() - p.hz()*s.hy() )
                    + s.hx()*( p.hy()*q.hz() - p.hz()*q.hy() ) )
          + s.hw()*(  p.hx()*( q.hy()*r.hz() - q.hz()*r.hy() )
                    - q.hx()*( p.hy()*r.hz() - p.hz()*r.hy() )
                    + r.hx()*( p.hy()*q.hz() - p.hz()*q.hy() ) ) ;

 if (det == RT(0.0))
 {
    return CGAL_COPLANAR;
 }
 else
 {
    return det < RT(0.0) ? CGAL_POSITIVE : CGAL_NEGATIVE;
           // switched, because the determinant above has the 1-row at the end
 }
}

template < class FT, class RT>
bool
CGAL_positive_oriented( const CGAL_PointH3<FT,RT>& p,
                        const CGAL_PointH3<FT,RT>& q,
                        const CGAL_PointH3<FT,RT>& r,
                        const CGAL_PointH3<FT,RT>& s)
{
 return (CGAL_orientation(p,q,r,s) == CGAL_POSITIVE);
}

template < class FT, class RT>
bool
CGAL_negative_oriented( const CGAL_PointH3<FT,RT>& p,
                        const CGAL_PointH3<FT,RT>& q,
                        const CGAL_PointH3<FT,RT>& r,
                        const CGAL_PointH3<FT,RT>& s)
{
 return (CGAL_orientation(p,q,r,s) == CGAL_NEGATIVE);
}

template < class FT, class RT>
bool
CGAL_coplanar( const CGAL_PointH3<FT,RT>& p,
               const CGAL_PointH3<FT,RT>& q,
               const CGAL_PointH3<FT,RT>& r,
               const CGAL_PointH3<FT,RT>& s)
{
 return (CGAL_orientation(p,q,r,s) == CGAL_COPLANAR);
}

#endif // ORIENTATION_PREDICATESH3_H
