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


// Source: basic_constructions_2.h
// Author: Sven Schoenherr

#ifndef CGAL_BASIC_CONSTRUCTIONS_2_H
#define CGAL_BASIC_CONSTRUCTIONS_2_H 1

#ifdef CGAL_HOMOGENEOUS_H
#  include <CGAL/basic_constructionsH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#  include <CGAL/basic_constructionsC2.h>
#endif // CGAL_CARTESIAN_H

template < class R > inline
CGAL_Point_2<R>
CGAL_midpoint( CGAL_Point_2<R> const& p,
               CGAL_Point_2<R> const& q )
{
    return( CGAL_midpoint( CGAL_static_cast( R::Point_2 const&, p),
                           CGAL_static_cast( R::Point_2 const&, q)));
}

template < class R > inline
CGAL_Point_2<R>
CGAL_circumcenter( CGAL_Point_2<R> const& p,
                   CGAL_Point_2<R> const& q,
                   CGAL_Point_2<R> const& r)
{
    return( CGAL_circumcenter( CGAL_static_cast( R::Point_2 const&, p),
                               CGAL_static_cast( R::Point_2 const&, q),
                               CGAL_static_cast( R::Point_2 const&, r)));
}

#endif // CGAL_BASIC_CONSTRUCTIONS_2_H
