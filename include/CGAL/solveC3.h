// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/solveC3.h
// package       : C3 (2.1.5)
// source        : web/solveC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:39 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SOLVEC3_H
#define CGAL_SOLVEC3_H

#ifndef CGAL_SOLVE_H
#include <CGAL/solve.h>
#endif // CGAL_SOLVE_H
#ifndef CGAL_VECTORC3_H
#include <CGAL/VectorC3.h>
#endif // CGAL_VECTORC3_H

CGAL_BEGIN_NAMESPACE


template <class FT>
void solve (const VectorC3<FT> &v0,
            const VectorC3<FT> &v1,
            const VectorC3<FT> &v2,
            const VectorC3<FT> &d,
            FT &alpha, FT &beta, FT &gamma)
{
  solve(v0.x(), v0.y(), v0.z(),
        v1.x(), v1.y(), v1.z(),
        v2.x(), v2.y(), v2.z(),
        d.x(),  d.y(),  d.z(),
        alpha, beta, gamma);
}


CGAL_END_NAMESPACE

#endif // CGAL_SOLVEC3_H
