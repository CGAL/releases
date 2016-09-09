 
// Source: Double_eps.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_DOUBLE_EPS_H
#define CGAL_DOUBLE_EPS_H

#include <CGAL/doublefield.h>
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
    return _d < de._d;
  }

  bool operator>(const CGAL_Double_eps &de) const
  {
    return _d > de._d;
  }

  bool operator<=(const CGAL_Double_eps &de) const
  {
    return _d <= de._d;
  }

  bool operator>=(const CGAL_Double_eps &de) const
  {
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

extern double CGAL_set_eps(double eps);

#include <stream.h>
extern ostream  &operator<<(ostream& os, const CGAL_Double_eps &);
 


#endif  // CGAL_DOUBLE_EPS_H

