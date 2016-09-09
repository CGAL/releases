// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Interval_arithmetic.h
// package       : Interval_arithmetic (4.15)
// revision      : $Revision: 2.65 $
// revision_date : $Date: 1999/05/07 11:15:39 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_INTERVAL_ARITHMETIC_H
#define CGAL_INTERVAL_ARITHMETIC_H

// This file contains the description of the two classes:
// - Interval_nt_advanced  (do the FPU rounding mode changes yourself)
// - Interval_nt           ("plug-in" version, derived from the other one)
//
// The differences are:
// - The second one is slower.
// - The first one supposes the rounding mode is set -> +infinity before
// nearly all operations, and might set it -> +infinity when leaving, whereas
// the second leaves the rounding -> nearest.
//
// Note: When rounding is towards +infinity, to make an operation rounded
// towards -infinity, it's enough to take the opposite of some of the operand,
// and the opposite of the result (see operator+, operator*,...).

#include <CGAL/basic.h>
#include <CGAL/Interval_arithmetic/_FPU.h>	// FPU rounding mode functions.

// Some useful constants

// Smallest interval strictly containing zero.
#define CGAL_IA_SMALLEST (Interval_nt_advanced(-CGAL_IA_MIN_DOUBLE, \
                                                CGAL_IA_MIN_DOUBLE))
// [-inf;+inf]
#define CGAL_IA_LARGEST (Interval_nt_advanced(-HUGE_VAL, HUGE_VAL))

CGAL_BEGIN_NAMESPACE

struct Interval_nt_advanced
{
  typedef Interval_nt_advanced IA;
  typedef struct {} unsafe_comparison;	// Exception class.
  static unsigned number_of_failures;	// Counts the number of failures.

  void overlap_action() const // This should be runtime customisable. FIXME
#ifndef CGAL_IA_NO_EXCEPTION
      throw (unsafe_comparison)
  { number_of_failures++;  throw unsafe_comparison(); }
#else
  {
#if !defined(CGAL_IA_NO_WARNINGS) && !defined(CGAL_NO_WARNINGS)
     CGAL_warning_msg(false, " Comparison between overlapping intervals");
#endif
  }
#endif // CGAL_IA_NO_EXCEPTION

  // The constructors.
  Interval_nt_advanced()
#ifndef CGAL_NO_ASSERTIONS
      : _inf(1), _sup(-1) // Buggy interval to detect use before definition.
#endif
      {}

  // To stop constant propagation, I need these CGAL_IA_FORCE_TO_DOUBLE(),
  // and this one is not specific to Intel.
  // Ideally, the good ones (0.0*x ...) should be enabled...

  Interval_nt_advanced(const double d)
      : _inf(d), _sup(d) {}
//   { _inf = _sup = CGAL_IA_FORCE_TO_DOUBLE(d); }

  Interval_nt_advanced(const double i, const double s)
      : _inf(i), _sup(s)
  {
      CGAL_assertion_msg(i<=s," Variable used before being initialized ?");
#if 0
      _inf = CGAL_IA_FORCE_TO_DOUBLE(i);
      _sup = CGAL_IA_FORCE_TO_DOUBLE(s);
#endif
  }

#if 1
  // The copy constructors/assignment: useless.
  // The default ones are ok, but these are faster...
  Interval_nt_advanced(const IA & d)
      : _inf(d._inf), _sup(d._sup) {}

  IA & operator=(const IA & d)
  { _inf = d._inf; _sup = d._sup; return *this; }
#endif

  // The operators.
  IA  operator+(const IA & d) const
  {
#ifdef CGAL_IA_DEBUG
      CGAL_assertion(FPU_get_cw() == FPU_cw_up);
#endif
      return IA (-CGAL_IA_FORCE_TO_DOUBLE(-_inf - d._inf),
	          CGAL_IA_FORCE_TO_DOUBLE( _sup + d._sup));
  }
  // { return IA  (d) += *this; }

  IA  operator-(const IA & d) const
  {
#ifdef CGAL_IA_DEBUG
      CGAL_assertion(FPU_get_cw() == FPU_cw_up);
#endif
      return IA (-CGAL_IA_FORCE_TO_DOUBLE(d._sup - _inf),
	          CGAL_IA_FORCE_TO_DOUBLE(_sup - d._inf));
  }

  // Those 2 ones could be made not inlined.
  IA  operator*	(const IA & d) const;
  IA  operator/	(const IA & d) const;

  IA  operator-() const { return IA (-_sup, -_inf); }

  IA & operator+= (const IA & d);
  IA & operator-= (const IA & d);
  IA & operator*= (const IA & d);
  IA & operator/= (const IA & d);

  // For speed.
  IA  operator* (const double d) const;
  IA  operator/ (const double d) const;

  bool operator< (const IA & d) const
  {
    if (_sup  < d._inf) return true;
    if (_inf >= d._sup) return false;
    overlap_action();
    return false;
  }

  bool operator<= (const IA & d) const
  {
    if (_sup <= d._inf) return true;
    if (_inf >  d._sup) return false;
    overlap_action();
    return false;
  }
  
  bool operator== (const IA & d) const
  {
    if (d._inf >  _sup || d._sup  < _inf) return false;
    if (d._inf == _sup && d._sup == _inf) return true;
    overlap_action();
    return false;
  }

  bool operator>  (const IA & d) const { return  (d <  *this); }
  bool operator>= (const IA & d) const { return  (d <= *this); }
  bool operator!= (const IA & d) const { return !(d == *this); }

  bool is_same (const IA & d) const
  { return (_inf == d._inf) && (_sup == d._sup); }

  bool is_point() const { return (_sup == _inf); }

  bool overlap (const IA & d) const
  { return !(d._inf > _sup || d._sup < _inf); }

  double inf() const { return _inf; }
  double sup() const { return _sup; }
  double lower_bound() const { return _inf; } // Kept for backward
  double upper_bound() const { return _sup; } // compatibility

  // The (join, union, ||) operator.
  IA operator|| (const IA & d) const
  { return IA(std::min(_inf,d._inf), std::max(_sup,d._sup)); }
  // The (meet, intersection, &&) operator.  Valid if intervals overlap.
  IA operator&& (const IA & d) const
  { return IA(std::max(_inf,d._inf), std::min(_sup,d._sup)); }

protected:
  double _inf, _sup;	// "_inf" stores the lower bound, "_sup" the upper.
};

inline
Interval_nt_advanced
Interval_nt_advanced::operator* (const Interval_nt_advanced & d) const
{
#ifdef CGAL_IA_DEBUG
      CGAL_assertion(FPU_get_cw() == FPU_cw_up);
#endif
  if (_inf>=0)					// this>=0
  {
      // d>=0     [_inf*d._inf; _sup*d._sup]
      // d<=0     [_sup*d._inf; _inf*d._sup]
      // d~=0     [_sup*d._inf; _sup*d._sup]
    double a = _inf, b = _sup;
    if (d._inf < 0)
    {
	a=b;
	if (d._sup < 0)
	    b=_inf;
    }

    return IA (-CGAL_IA_FORCE_TO_DOUBLE(a*-d._inf),
	        CGAL_IA_FORCE_TO_DOUBLE(b*d._sup));
  }
  else if (_sup<=0)				// this<=0
  {
      // d>=0     [_inf*d._sup; _sup*d._inf]
      // d<=0     [_sup*d._sup; _inf*d._inf]
      // d~=0     [_inf*d._sup; _inf*d._inf]
    double a = _sup, b = _inf;
    if (d._inf < 0)
    {
	a=b;
	if (d._sup < 0)
	    b=_sup;
    }
    return IA (-CGAL_IA_FORCE_TO_DOUBLE(b*-d._sup),
	        CGAL_IA_FORCE_TO_DOUBLE(a*d._inf));
  }
  else						// 0 \in [_inf;_sup]
  {
    if (d._inf>=0)				// d>=0
      return IA (-CGAL_IA_FORCE_TO_DOUBLE((-_inf)*d._sup),
	          CGAL_IA_FORCE_TO_DOUBLE(_sup*d._sup));
    if (d._sup<=0)				// d<=0
      return IA (-CGAL_IA_FORCE_TO_DOUBLE(_sup*-d._inf),
	          CGAL_IA_FORCE_TO_DOUBLE(_inf*d._inf));
        					// 0 \in d
    double tmp1 = CGAL_IA_FORCE_TO_DOUBLE((-_inf)*d._sup);
    double tmp2 = CGAL_IA_FORCE_TO_DOUBLE(_sup*-d._inf);
    double tmp3 = CGAL_IA_FORCE_TO_DOUBLE(_inf*d._inf);
    double tmp4 = CGAL_IA_FORCE_TO_DOUBLE(_sup*d._sup);
    return IA (-std::max(tmp1,tmp2), std::max(tmp3,tmp4));
  };
}

inline
Interval_nt_advanced
Interval_nt_advanced::operator* (const double d) const
{
#ifdef CGAL_IA_DEBUG
      CGAL_assertion(FPU_get_cw() == FPU_cw_up);
#endif
  return (d>=0) ? IA (-CGAL_IA_FORCE_TO_DOUBLE(d*-_inf),
	               CGAL_IA_FORCE_TO_DOUBLE(d*_sup))
     		: IA (-CGAL_IA_FORCE_TO_DOUBLE(d*-_sup),
		       CGAL_IA_FORCE_TO_DOUBLE(d*_inf));
}

inline
Interval_nt_advanced
Interval_nt_advanced::operator/ (const double d) const
{
#ifdef CGAL_IA_DEBUG
      CGAL_assertion(FPU_get_cw() == FPU_cw_up);
#endif
  if (d>0) return IA (-CGAL_IA_FORCE_TO_DOUBLE((-_inf)/d),
	               CGAL_IA_FORCE_TO_DOUBLE(_sup/d));
  if (d<0) return IA (-CGAL_IA_FORCE_TO_DOUBLE((-_sup)/d),
	               CGAL_IA_FORCE_TO_DOUBLE(_inf/d));
  return CGAL_IA_LARGEST;
}

inline
bool
operator< (const double d, const Interval_nt_advanced & t)
{ return t>d; }

inline
bool
operator<= (const double d, const Interval_nt_advanced & t)
{ return t>=d; }

inline
bool
operator> (const double d, const Interval_nt_advanced & t)
{ return t<d; }

inline
bool
operator>= (const double d, const Interval_nt_advanced & t)
{ return t<=d; }

inline
bool
operator== (const double d, const Interval_nt_advanced & t)
{ return t==d; }

inline
bool
operator!= (const double d, const Interval_nt_advanced & t)
{ return t!=d; }

inline
Interval_nt_advanced
operator+ (const double d, const Interval_nt_advanced & t)
{ return t+d; }

inline
Interval_nt_advanced
operator- (const double d, const Interval_nt_advanced & t)
{ return -(t-d); }

inline
Interval_nt_advanced
operator* (const double d, const Interval_nt_advanced & t)
{ return t*d; }

inline
Interval_nt_advanced
operator/ (const double d, const Interval_nt_advanced & t)
{
#ifdef CGAL_IA_DEBUG
      CGAL_assertion(FPU_get_cw() == FPU_cw_up);
#endif
  if (t.inf() <= 0 && t.sup() >= 0) // t~0
      return CGAL_IA_LARGEST;

  return (d>=0) ? Interval_nt_advanced(-CGAL_IA_FORCE_TO_DOUBLE(d/-t.sup()),
	 				CGAL_IA_FORCE_TO_DOUBLE(d/t.inf()))
                : Interval_nt_advanced(-CGAL_IA_FORCE_TO_DOUBLE(d/-t.inf()),
					CGAL_IA_FORCE_TO_DOUBLE(d/t.sup()));
}

inline
Interval_nt_advanced
Interval_nt_advanced::operator/ (const Interval_nt_advanced & d) const
{
#ifdef CGAL_IA_DEBUG
      CGAL_assertion(FPU_get_cw() == FPU_cw_up);
#endif
  if (d._inf>0)				// d>0
  {
      // this>=0	[_inf/d._sup; _sup/d._inf]
      // this<=0	[_inf/d._inf; _sup/d._sup]
      // this~=0	[_inf/d._inf; _sup/d._inf]
    double a = d._sup, b = d._inf;
    if (_inf<0)
    {
	a=b;
	if (_sup<0)
	    b=d._sup;
    };
    return IA(-CGAL_IA_FORCE_TO_DOUBLE((-_inf)/a),
	       CGAL_IA_FORCE_TO_DOUBLE(_sup/b));
  }
  else if (d._sup<0)			// d<0
  {
      // this>=0	[_sup/d._sup; _inf/d._inf]
      // this<=0	[_sup/d._inf; _inf/d._sup]
      // this~=0	[_sup/d._sup; _inf/d._sup]
    double a = d._sup, b = d._inf;
    if (_inf<0)
    {
	b=a;
	if (_sup<0)
	    a=d._inf;
    };
    return IA(-CGAL_IA_FORCE_TO_DOUBLE((-_sup)/a),
	       CGAL_IA_FORCE_TO_DOUBLE(_inf/b));
  }
  else					// d~0
    return CGAL_IA_LARGEST; // IA (-HUGE_VAL, HUGE_VAL);
	   // We could do slightly better -> [0;HUGE_VAL] when d._sup==0,
	   // but is this worth ?
}

inline
Interval_nt_advanced &
Interval_nt_advanced::operator+= (const Interval_nt_advanced & d)
{ return *this = *this + d; }

inline
Interval_nt_advanced &
Interval_nt_advanced::operator-= (const Interval_nt_advanced & d)
{ return *this = *this - d; }

inline
Interval_nt_advanced &
Interval_nt_advanced::operator*= (const Interval_nt_advanced & d)
{ return *this = *this * d; }

inline
Interval_nt_advanced &
Interval_nt_advanced::operator/= (const Interval_nt_advanced & d)
{ return *this = *this / d; }

inline
Interval_nt_advanced
sqrt (const Interval_nt_advanced & d)
{
  // sqrt([+a,+b]) => [sqrt(+a);sqrt(+b)]
  // sqrt([-a,+b]) => [0;sqrt(+b)] => assumes roundoff error.
  // sqrt([-a,-b]) => [0;sqrt(-b)] => assumes user bug (unspecified result).
  FPU_set_cw(FPU_cw_down);
  double i = (d.inf()>0) ? CGAL_IA_FORCE_TO_DOUBLE(std::sqrt(d.inf())) : 0;
  FPU_set_cw(FPU_cw_up);
  return Interval_nt_advanced(i, CGAL_IA_FORCE_TO_DOUBLE(std::sqrt(d.sup())));
}

inline
Interval_nt_advanced
square (const Interval_nt_advanced & d)
{
#ifdef CGAL_IA_DEBUG
      CGAL_assertion(FPU_get_cw() == FPU_cw_up);
#endif
  if (d.inf()>=0)
      return Interval_nt_advanced(-CGAL_IA_FORCE_TO_DOUBLE(d.inf()*-d.inf()),
	     			   CGAL_IA_FORCE_TO_DOUBLE(d.sup()*d.sup()));
  if (d.sup()<=0)
      return Interval_nt_advanced(-CGAL_IA_FORCE_TO_DOUBLE(d.sup()*-d.sup()),
	     			   CGAL_IA_FORCE_TO_DOUBLE(d.inf()*d.inf()));
  return Interval_nt_advanced(0.0,
	  CGAL_IA_FORCE_TO_DOUBLE(square(std::max(-d.inf(), d.sup()))));
}

inline
double
to_double (const Interval_nt_advanced & d)
{ return (d.sup()+d.inf())*.5; }

inline
bool
is_valid (const Interval_nt_advanced & d)
{ return is_valid(d.inf()) && is_valid(d.sup()) && d.inf() <= d.sup(); }

inline
bool
is_finite (const Interval_nt_advanced & d)
{ return is_finite(d.inf()) && is_finite(d.sup()); }

inline
Sign
sign (const Interval_nt_advanced & d)
{
  if (d.inf() > 0) return POSITIVE;
  if (d.sup() < 0) return NEGATIVE;
  if (d.inf() == d.sup()) return ZERO;
  d.overlap_action();
  return ZERO;
}

inline
Comparison_result
compare (const Interval_nt_advanced & d, const Interval_nt_advanced & e)
{
  if (d.inf() > e.sup()) return LARGER;
  if (e.inf() > d.sup()) return SMALLER;
  if (e.inf() == d.sup() && d.inf() == e.sup()) return EQUAL;
  d.overlap_action();
  return EQUAL;
}

inline
Interval_nt_advanced
abs (const Interval_nt_advanced & d)
{
  if (d.inf() >= 0) return d;
  if (d.sup() <= 0) return -d;
  return Interval_nt_advanced(0, std::max(-d.inf(), d.sup()));
}

inline
Interval_nt_advanced
min (const Interval_nt_advanced & d, const Interval_nt_advanced & e)
{
  return Interval_nt_advanced(std::min(d.inf(), e.inf()),
			      std::min(d.sup(), e.sup()));
}

inline
Interval_nt_advanced
max (const Interval_nt_advanced & d, const Interval_nt_advanced & e)
{
  return Interval_nt_advanced(std::max(d.inf(), e.inf()),
			      std::max(d.sup(), e.sup()));
}

inline
std::ostream &
operator<< (std::ostream & os, const Interval_nt_advanced & d)
{ return os << "[" << d.inf() << ";" << d.sup() << "]"; }

inline
std::istream &
operator>> (std::istream & is, Interval_nt_advanced & ia)
{
    double d;
    is >> d;
    ia = d;
    return is;
}


// The non-advanced class.

struct Interval_nt : public Interval_nt_advanced
{
  typedef Interval_nt IA;

  // Constructors are identical.
  Interval_nt()
      {}
  Interval_nt(const double d)
      : Interval_nt_advanced(d) {}
  Interval_nt(const double a, const double b)
      : Interval_nt_advanced(a,b) {}

  // Private constructor for casts. (remade public)
  Interval_nt(const Interval_nt_advanced &d)
      : Interval_nt_advanced(d) {}

  IA operator-() const 
    { return IA(-_sup, -_inf); }

  // The member functions that have to be protected against rounding mode.
  IA operator+(const IA & d) const;
  IA operator-(const IA & d) const;
  IA operator*(const IA & d) const;
  IA operator/(const IA & d) const;

  IA operator*(const double d) const;
  IA operator/(const double d) const;

  IA & operator+=(const IA & d);
  IA & operator-=(const IA & d);
  IA & operator*=(const IA & d);
  IA & operator/=(const IA & d);
};


inline
Interval_nt
abs (const Interval_nt & d)
{ return abs((Interval_nt_advanced) d); }

inline
Interval_nt
min (const Interval_nt & d, const Interval_nt & e)
{ return min((Interval_nt_advanced) d, (Interval_nt_advanced) e); }

inline
Interval_nt
max (const Interval_nt & d, const Interval_nt & e)
{ return max((Interval_nt_advanced) d, (Interval_nt_advanced) e); }

// Here we use the GNU extension of "Named return value".

#ifdef __GNUG__
#  define CGAL_NAMED_RETURN_VALUE_OPT_1 return tmp;
#  define CGAL_NAMED_RETURN_VALUE_OPT_2
#  define CGAL_NAMED_RETURN_VALUE_OPT_3
#else
#  define CGAL_NAMED_RETURN_VALUE_OPT_1
#  define CGAL_NAMED_RETURN_VALUE_OPT_2 Interval_nt tmp;
#  define CGAL_NAMED_RETURN_VALUE_OPT_3 return tmp;
#endif

inline
Interval_nt
Interval_nt::operator+ (const Interval_nt & d) const
CGAL_NAMED_RETURN_VALUE_OPT_1
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  CGAL_NAMED_RETURN_VALUE_OPT_2
  tmp._inf = -CGAL_IA_FORCE_TO_DOUBLE(-_inf - d._inf);
  tmp._sup =  CGAL_IA_FORCE_TO_DOUBLE(_sup + d._sup);
  FPU_set_cw(backup);
  CGAL_NAMED_RETURN_VALUE_OPT_3
}

inline
Interval_nt
Interval_nt::operator- (const Interval_nt & d) const
CGAL_NAMED_RETURN_VALUE_OPT_1
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  CGAL_NAMED_RETURN_VALUE_OPT_2
  tmp._inf = -CGAL_IA_FORCE_TO_DOUBLE(d._sup - _inf);
  tmp._sup =  CGAL_IA_FORCE_TO_DOUBLE(_sup - d._inf);
  FPU_set_cw(backup);
  CGAL_NAMED_RETURN_VALUE_OPT_3
}

inline
Interval_nt
Interval_nt::operator* (const Interval_nt & d) const
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  Interval_nt tmp ( Interval_nt_advanced::operator*(d) );
  FPU_set_cw(backup);
  return tmp;
}

inline
Interval_nt
Interval_nt::operator* (const double d) const
CGAL_NAMED_RETURN_VALUE_OPT_1
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  CGAL_NAMED_RETURN_VALUE_OPT_2
  if (d>=0) {
      tmp._inf = -CGAL_IA_FORCE_TO_DOUBLE(_inf*-d);
      tmp._sup =  CGAL_IA_FORCE_TO_DOUBLE(_sup*d);
  } else {
      tmp._inf = -CGAL_IA_FORCE_TO_DOUBLE(_sup*-d);
      tmp._sup =  CGAL_IA_FORCE_TO_DOUBLE(_inf*d);
  }
  FPU_set_cw(backup);
  CGAL_NAMED_RETURN_VALUE_OPT_3
}

inline
Interval_nt
operator+ (const double d, const Interval_nt & t)
{ return t+d; }

inline
Interval_nt
operator- (const double d, const Interval_nt & t)
{ return -(t-d); }

inline
Interval_nt
operator* (const double d, const Interval_nt & t)
{ return t*d; }

inline
Interval_nt
Interval_nt::operator/ (const Interval_nt & d) const
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  Interval_nt tmp ( Interval_nt_advanced::operator/(d) );
  FPU_set_cw(backup);
  return tmp;
}

inline
Interval_nt
operator/ (const double d, const Interval_nt & t)
{ return Interval_nt(d)/t; }

inline
Interval_nt
Interval_nt::operator/ (const double d) const
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  Interval_nt tmp ( Interval_nt_advanced::operator/(d) );
  FPU_set_cw(backup);
  return tmp;
}

inline
Interval_nt &
Interval_nt::operator+= (const Interval_nt & d)
{ return *this = *this + d; }

inline
Interval_nt &
Interval_nt::operator-= (const Interval_nt & d)
{ return *this = *this - d; }

inline
Interval_nt &
Interval_nt::operator*= (const Interval_nt & d)
{ return *this = *this * d; }

inline
Interval_nt &
Interval_nt::operator/= (const Interval_nt & d)
{ return *this = *this / d; }

inline
Interval_nt
sqrt (const Interval_nt & d)
{
  FPU_CW_t backup = FPU_get_cw();
  Interval_nt tmp = sqrt( (Interval_nt_advanced) d);
  FPU_set_cw(backup);
  return tmp;
}

inline
Interval_nt
square (const Interval_nt & d)
{
  FPU_CW_t backup = FPU_get_cw();
  FPU_set_cw(FPU_cw_up);
  Interval_nt tmp = square( (Interval_nt_advanced) d);
  FPU_set_cw(backup);
  return tmp;
}


// The undocumented tags.

inline
io_Operator
io_tag (const Interval_nt_advanced &)
{ return io_Operator(); }

inline
Number_tag
number_type_tag (Interval_nt_advanced)
{ return Number_tag(); }



// Finally we deal with the convert_to<Interval_nt_advanced>(NT)
// functions from other NTs, when necessary.
// convert_to<Interval_nt>() is templated below.
//
// For the builtin types (well, all those that can be casted to double
// exactly), the template in misc.h is enough.

CGAL_END_NAMESPACE

#ifdef CGAL_GMPZ_H
#include <CGAL/Interval_arithmetic/IA_Gmpz.h>
#endif

#ifdef CGAL_BIGFLOAT_H
#include <CGAL/Interval_arithmetic/IA_leda_bigfloat.h>
#endif

#ifdef CGAL_INTEGER_H
#include <CGAL/Interval_arithmetic/IA_leda_integer.h>
#endif

#ifdef CGAL_REAL_H
#include <CGAL/Interval_arithmetic/IA_leda_real.h>
#endif

#ifdef CGAL_RATIONAL_H
#include <CGAL/Interval_arithmetic/IA_leda_rational.h>
#endif

#ifdef CGAL_FIXED_PRECISION_NT_H
#include <CGAL/Interval_arithmetic/IA_Fixed.h>
#endif

#ifdef CGAL_QUOTIENT_H
#include <CGAL/Interval_arithmetic/IA_Quotient.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class FT>
inline
Interval_nt
convert_from_to (const Interval_nt&, const FT & z)
{
    FPU_CW_t backup = FPU_get_cw();
    FPU_set_cw(FPU_cw_up);
    Interval_nt tmp(convert_from_to(Interval_nt_advanced(), z));
    FPU_set_cw(backup);
    return tmp;
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template <class FT>
inline
Interval_nt
convert_to (const FT & z)
{
    FPU_CW_t backup = FPU_get_cw();
    FPU_set_cw(FPU_cw_up);
    Interval_nt tmp(convert_to<Interval_nt_advanced>(z));
    FPU_set_cw(backup);
    return tmp;
}
#endif // CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION

CGAL_END_NAMESPACE

#endif // CGAL_INTERVAL_ARITHMETIC_H
