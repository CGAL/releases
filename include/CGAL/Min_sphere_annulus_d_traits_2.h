// Copyright (c) 1997-2001  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Min_sphere_d/include/CGAL/Min_sphere_annulus_d_traits_2.h $
// $Id: Min_sphere_annulus_d_traits_2.h 37871 2007-04-03 13:14:58Z afabri $
// 
//
// Author(s)     : Sven Schoenherr <sven@inf.ethz.ch>

#ifndef CGAL_MIN_SPHERE_ANNULUS_D_TRAITS_2_H
#define CGAL_MIN_SPHERE_ANNULUS_D_TRAITS_2_H

// includes
#  include <CGAL/Optimisation/Access_dimension_2.h>
#  include <CGAL/Optimisation/Access_coordinates_begin_2.h>
#  include <CGAL/Optimisation/Construct_point_2.h>

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class K_, class ET_ = typename K_::RT,
                     class NT_ = typename K_::RT >
class Min_sphere_annulus_d_traits_2;

// Class interface
// ===============
template < class K_, class ET_, class NT_>
class Min_sphere_annulus_d_traits_2 {
  public:
    // self
    typedef  K_                         K;
    typedef  ET_                        ET;
    typedef  NT_                        NT;
    typedef  Min_sphere_annulus_d_traits_2<K,ET,NT>
                                        Self;

    // types
    typedef  typename K::Point_2        Point_d;

    typedef  typename K::Rep_tag        Rep_tag;

    typedef  typename K::RT             RT;
    typedef  typename K::FT             FT;

    typedef  CGAL::Access_dimension_2<K>      Access_dimension_d;
    typedef  CGAL::Access_coordinates_begin_2<K>
                                        Access_coordinates_begin_d;

    // this does not (yet) work:
    // typedef  typename K::Construct_point_2    Construct_point_d;
    typedef  _Construct_point_2<K>       Construct_point_d;

    // creation
    Min_sphere_annulus_d_traits_2( ) { }
    Min_sphere_annulus_d_traits_2( const Min_sphere_annulus_d_traits_2<K_,ET_,NT_>&) {}

    // operations
    Access_dimension_d
    access_dimension_d_object( ) const
        { return Access_dimension_d(); }

    Access_coordinates_begin_d
    access_coordinates_begin_d_object( ) const
        { return Access_coordinates_begin_d(); }

    Construct_point_d
    construct_point_d_object( ) const
        { return Construct_point_d(); }
};

CGAL_END_NAMESPACE

#endif // CGAL_MIN_SPHERE_ANNULUS_D_TRAITS_2_H

// ===== EOF ==================================================================
