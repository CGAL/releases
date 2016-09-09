// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Width_default_traits_3.h
// package       : Width_3 (1.13)
// chapter       : Geometric Optimisation
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/07/12 05:59:08 $
//
// author(s)     : Thomas Herrmann, Lutz Kettner
// coordinator   : ETH Zuerich (Bernd Gaertner)
//
// implementation: 3D Width of a Point Set
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_WIDTH_DEFAULT_TRAITS_3_H
#define CGAL_WIDTH_DEFAULT_TRAITS_3_H

#include <CGAL/Convex_hull_traits_3.h>

CGAL_BEGIN_NAMESPACE

template <class Kernel_>
class Width_default_traits_3 {
public:
    typedef Kernel_                      Kernel;
    typedef typename Kernel::RT          RT;
    typedef typename Kernel::Point_3     Point_3;
    typedef typename Kernel::Plane_3     Plane_3;
    typedef typename Kernel::Vector_3    Vector_3;
    typedef Convex_hull_traits_3<Kernel> ChullTraits;

    RT get_hx( const Point_3& p) const { return p.hx(); }
    RT get_hy( const Point_3& p) const { return p.hy(); }
    RT get_hz( const Point_3& p) const { return p.hz(); }
    RT get_hw( const Point_3& p) const { return p.hw(); }
    void get_point_coordinates( const Point_3& p, 
                                RT& px, RT& py, RT& pz, RT& ph) const {
        px = get_hx(p);
        py = get_hy(p);
        pz = get_hz(p);
        ph = get_hw(p);
    }
    RT get_a( const Plane_3& f) const { return f.a(); }
    RT get_b( const Plane_3& f) const { return f.b(); }
    RT get_c( const Plane_3& f) const { return f.c(); }
    RT get_d( const Plane_3& f) const { return f.d(); }
    void get_plane_coefficients( const Plane_3& f, 
                                 RT& a, RT& b, RT& c, RT& d) const {
        a = get_a(f);
        b = get_b(f);
        c = get_c(f);
        d = get_d(f);
    }
    
    Point_3 make_point( const RT& hx, const RT& hy, 
                        const RT& hz, const RT& hw) const  {
        return Point_3(hx,hy,hz,hw);
    }
    Plane_3 make_plane( const RT& a, const RT& b, 
                        const RT& c, const RT& d) const {
        return Plane_3(a,b,c,d);
    }
    Vector_3 make_vector( const RT& a, const RT& b, const RT& c) const {
        return Vector_3(a,b,c);
    }
};

CGAL_END_NAMESPACE

#endif //CGAL_WIDTH_DEFAULT_TRAITS_3_H
