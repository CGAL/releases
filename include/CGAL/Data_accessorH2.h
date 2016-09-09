// ======================================================================
//
// Copyright (c) 1999,2001 The CGAL Consortium

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
// file          : include/CGAL/Data_accessorH2.h
// package       : H2 (2.37)
// revision      : $Revision: 1.1 $
// revision_date : $Date: 2001/02/13 11:10:17 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_DATA_ACCESSORH2_H
#define CGAL_DATA_ACCESSORH2_H

#include <CGAL/PointH2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
class Data_accessorH2
{
public:
    typedef  typename R::FT FT;
    typedef  typename R::RT RT;
    typedef  PointH2<R>      Point;

    RT  get_hx( Point const& p) const { return( p.hx()); }
    RT  get_hy( Point const& p) const { return( p.hy()); }
    RT  get_hw( Point const& p) const { return( p.hw()); }

    void
    get( Point const& p, RT& hx, RT& hy, RT& hw) const
    {
        hx = get_hx( p);
        hy = get_hy( p);
        hw = get_hw( p);
    }

    void
    set( Point& p, RT const& hx, RT const& hy, RT const& hw) const
    {
        p = Point( hx, hy, hw);
    }
};

CGAL_END_NAMESPACE

#endif // CGAL_DATA_ACCESSORH2_H
