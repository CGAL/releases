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


// Source: orientation_predicatesH3.h
// Author: Stefan Schirra

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
