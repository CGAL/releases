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

// Source: solveC3.h
// Author: Andreas.Fabri@sophia.inria.fr


#ifndef CGAL_SOLVEC3_H
#define CGAL_SOLVEC3_H

#include <CGAL/solve.h>
#include <CGAL/VectorC3.h>


template <class FT>
void CGAL_solve (const CGAL_VectorC3<FT> &v0,
                 const CGAL_VectorC3<FT> &v1,
                 const CGAL_VectorC3<FT> &v2,
                 const CGAL_VectorC3<FT> &d,
                 FT &alpha, FT &beta, FT &gamma)
{
  CGAL_solve(v0.x(), v0.y(), v0.z(),
             v1.x(), v1.y(), v1.z(),
             v2.x(), v2.y(), v2.z(),
             d.x(),  d.y(),  d.z(),
             alpha, beta, gamma);
}


#endif // CGAL_SOLVEC3_H
