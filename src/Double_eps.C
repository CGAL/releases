 
// Source: Double_eps.C
// Author: Andreas.Fabri@sophia.inria.fr

#include <LEDA/basic.h>
#include <CGAL/Double_eps.h>

double CGAL_Double_eps::_eps = 0.0;


double CGAL_set_eps(double eps)
  {
    double e = CGAL_Double_eps::_eps;
    CGAL_Double_eps::_eps = eps;
    return e;
  }

ostream  &operator<<(ostream& os, const CGAL_Double_eps &de)
  {
    os << de.d();
    return os;
  }

