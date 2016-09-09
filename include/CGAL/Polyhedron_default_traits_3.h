// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Polyhedron_default_traits_3.h
// package       : Polyhedron (1.14)
// chapter       : $CGAL_Chapter: 3D-Polyhedral Surfaces $
// source        : polyhedron.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1998/10/09 13:32:07 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Default Traits for Polyhedral Surfaces in CGAL.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_POLYHEDRON_DEFAULT_TRAITS_3_H
#define CGAL_POLYHEDRON_DEFAULT_TRAITS_3_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_POINT_3_H
#include <CGAL/Point_3.h>
#endif
#ifndef CGAL_VECTOR_3_H
#include <CGAL/Vector_3.h>
#endif
#ifndef CGAL_PLANE_3_H
#include <CGAL/Plane_3.h>
#endif

template < class Rep >
class CGAL_Polyhedron_default_traits_3 {
public:
    typedef Rep                   R;
    typedef CGAL_Point_3<Rep>     Point;
    typedef CGAL_Vector_3<Rep>    Normal;
    typedef CGAL_Plane_3<Rep>     Plane;
    void reverse_normal( Normal& normal) const {
        normal = - normal;
    }
    void reverse_plane( Plane& plane) const {
        plane  = plane.opposite();
    }
    //Normal get_normal( const Plane& plane) const {
    //    return plane.orthogonal_vector();
    //}
};
#endif // CGAL_POLYHEDRON_DEFAULT_TRAITS_3_H //
// EOF //
