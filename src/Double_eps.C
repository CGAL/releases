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

// Source: Double_eps.C
// Author: Andreas.Fabri@sophia.inria.fr

#include <CGAL/misc.h>
#include <LEDA/basic.h>
#include <CGAL/Double_eps.h>

double CGAL_Double_eps::_eps = 0.0;


double CGAL_set_eps(double eps)
  {
    double e = CGAL_Double_eps::_eps;
    CGAL_Double_eps::_eps = eps;
    return e;
  }

CGAL_Double_eps sqrt(const CGAL_Double_eps &de)
  {
    return CGAL_Double_eps(sqrt(de.d()));
  }

ostream  &operator<<(ostream& os, const CGAL_Double_eps &de)
  {
    os << de.d();
    return os;
  }

