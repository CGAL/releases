// Source: rational.C
// Author: Andreas.Fabri@sophia.inria.fr

#include <CGAL/Rational.h>

double CGAL_to_double(const CGAL_Rational &r)
{
  //  return r.numerator().todouble()/r.denominator().todouble();
  return r.todouble();
}

bool CGAL_is_finite(const CGAL_Rational &)
{
  return true;
}

bool CGAL_is_valid(const CGAL_Rational &)
{
  return true;
}
