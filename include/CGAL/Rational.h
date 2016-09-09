// Source: Rational.h
// Author: Andreas.Fabri@sophia.inria.fr
#ifndef CGAL_RATIONAL_H
#define CGAL_RATIONAL_H

#include <LEDA/rational.h>

typedef rational CGAL_Rational;

/*
class  CGAL_Rational : public rational
{
public:
  CGAL_Rational()
  {}

 CGAL_Rational(double d)
   : rational(d)
  {}

  CGAL_Rational(int i)
   : rational(i)
  {}

  CGAL_Rational(int m, int n)
   : rational(m, n)
  {}

  CGAL_Rational(integer a)
   : rational(a)
  {}

  CGAL_Rational(integer a, integer b)
   : rational(a, b)
  {}

};
*/
extern double CGAL_to_double(const CGAL_Rational &r);

extern bool CGAL_is_finite(const CGAL_Rational &);

extern bool CGAL_is_valid(const CGAL_Rational &);
#endif  // CGAL_RATIONAL_H
