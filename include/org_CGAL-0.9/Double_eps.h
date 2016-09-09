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


// Source: Double_eps.h
// Author: Andreas Fabri

#ifndef CGAL_DOUBLE_EPS_H
#define CGAL_DOUBLE_EPS_H

#include <CGAL/Double.h>
#include <CGAL/number_utils.h>


class CGAL_Double_eps
{
friend double CGAL_set_eps(double eps);
friend istream& operator>>(istream&, CGAL_Double_eps& );
friend ostream& operator<<(ostream&, const CGAL_Double_eps& );

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

  CGAL_Double_eps&  operator+=(const CGAL_Double_eps &de)
  {
    _d += de._d;
    return *this;
  }

  CGAL_Double_eps&  operator-=(const CGAL_Double_eps &de)
  {
    _d -= de._d;
    return *this;
  }

  CGAL_Double_eps&  operator*=(const CGAL_Double_eps &de)
  {
    _d *= de._d;
    return *this;
  }

  CGAL_Double_eps&  operator/=(const CGAL_Double_eps &de)
  {
    _d /= de._d;
    return *this;
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

inline CGAL_io_Operator CGAL_io_tag(const CGAL_Double_eps &)
{
  return CGAL_io_Operator();
}

extern double CGAL_set_eps(double eps);

#include <iostream.h>
extern ostream  &operator<<(ostream& os, const CGAL_Double_eps &);


#endif  // CGAL_DOUBLE_EPS_H

