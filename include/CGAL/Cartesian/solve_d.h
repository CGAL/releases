// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Cartesian/solve_d.h
// package       : Cd (1.14)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/20 21:55:04 $
// author(s)     : Andreas.Fabri
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_CARTESIAN_SOLVE_D_H
#define CGAL_CARTESIAN_CARTESIAN_SOLVE_D_H

#include <CGAL/Cartesian/redefine_names_d.h>
#include <CGAL/solve.h>
#include <CGAL/Cartesian/Vector_d.h>

CGAL_BEGIN_NAMESPACE

template <class R>
void solve (const VectorCd<R CGAL_CTAG> &v0,
            const VectorCd<R CGAL_CTAG> &v1,
            const VectorCd<R CGAL_CTAG> &v2,
            const VectorCd<R CGAL_CTAG> &d,
            typename R::FT &alpha, typename R::FT &beta, typename R::FT &gamma)
{
  solve(v0.cartesian(0), v0.cartesian(1), v0.cartesian(2),
        v1.cartesian(0), v1.cartesian(1), v1.cartesian(2),
        v2.cartesian(0), v2.cartesian(1), v2.cartesian(2),
        d.cartesian(0),  d.cartesian(1),  d.cartesian(2),
        alpha, beta, gamma);
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_CARTESIAN_SOLVE_D_H
