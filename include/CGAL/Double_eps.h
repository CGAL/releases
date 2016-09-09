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

// Source: Double_eps.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_DOUBLE_EPS_H
#define CGAL_DOUBLE_EPS_H

#include <math.h>
#include <CGAL/Double.h>
#include <CGAL/number_utils.h>


class CGAL_Double_eps
{
friend double CGAL_set_eps(double eps);
public:
  CGAL_Double_eps()
    : _d(0.0)
  {}

  CGAL_Double_eps(double d)
    : _d(d)
  {}

  double d() const
  {
    return _d;
  }

  double eps() const
  {
    return _eps;
  }

  operator double() const
  {
    return _d;
  }

  CGAL_Double_eps operator+(const CGAL_Double_eps &de) const
  {
    return CGAL_Double_eps(_d + de._d);
  }

  CGAL_Double_eps operator-(const CGAL_Double_eps &de) const
  {
    return CGAL_Double_eps(_d - de._d);
  }

  CGAL_Double_eps operator-() const
  {
    return CGAL_Double_eps(-_d);
  }

  CGAL_Double_eps operator*(const CGAL_Double_eps &de) const
  {
    return CGAL_Double_eps(_d * de._d);
  }

  CGAL_Double_eps operator/(const CGAL_Double_eps &de) const
  {
    return CGAL_Double_eps(_d / de._d);
  }

  bool operator==(const CGAL_Double_eps &de) const
  {
    return CGAL_abs(_d - de._d) <= _eps;
  }

  bool operator!=(const CGAL_Double_eps &de) const
  {
    return !(*this == de);
  }

  bool operator<(const CGAL_Double_eps &de) const
  {
    if (*this == de) {
      return false;
    }
    return _d < de._d;
  }

  bool operator>(const CGAL_Double_eps &de) const
  {
    if (*this == de) {
      return false;
    }
    return _d > de._d;
  }

  bool operator<=(const CGAL_Double_eps &de) const
  {
    if (*this == de) {
      return true;
    }
    return _d <= de._d;
  }

  bool operator>=(const CGAL_Double_eps &de) const
  {
    if (*this == de) {
      return true;
    }
    return _d >= de._d;
  }

private:
  double _d;
  static double _eps;
};

inline bool CGAL_is_valid(const CGAL_Double_eps &de)
  {
    return CGAL_is_valid(de.d());
  }

inline bool CGAL_is_finite(const CGAL_Double_eps &de)
  {
    return CGAL_is_finite(de.d());
  }

inline double CGAL_to_double(const CGAL_Double_eps &de)
  {
    return de.d();
  }

inline CGAL_Double_eps CGAL_numerator(const CGAL_Double_eps &d)
{
  return d;
}

inline CGAL_Double_eps CGAL_denominator(const CGAL_Double_eps &)
{
  return CGAL_Double_eps(1.0);
}

inline CGAL_Number_tag CGAL_number_type_tag(const CGAL_Double_eps &)
{
  return CGAL_Number_tag();
}

extern double CGAL_set_eps(double eps);

#include <iostream.h>
extern ostream  &operator<<(ostream& os, const CGAL_Double_eps &);


#endif  // CGAL_DOUBLE_EPS_H

