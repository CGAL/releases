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

// Source: Rational.h
// Author: Andreas.Fabri@sophia.inria.fr
#ifndef CGAL_RATIONAL_H
#define CGAL_RATIONAL_H

#include <CGAL/misc.h>
#include <LEDA/rational.h>

#include <LEDA/REDEFINE_NAMES.h>
typedef rational CGAL_Rational;
#include <LEDA/UNDEFINE_NAMES.h>

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
