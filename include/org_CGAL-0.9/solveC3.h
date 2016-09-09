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


// Source: solveC3.h
// Author: Andreas Fabri


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
