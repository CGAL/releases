// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Interval_base.h
// package       : Interval_arithmetic (4.141)
// revision      : $Revision: 1.15 $
// revision_date : $Date: 2002/04/15 20:23:20 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_INTERVAL_BASE_H
#define CGAL_INTERVAL_BASE_H

// This file contains the description of the Interval_base class, which is used
// by the number types Interval_nt<>.

#include <CGAL/basic.h>
#include <CGAL/double.h>

CGAL_BEGIN_NAMESPACE

struct Interval_base
{
  typedef Interval_base IA;
  struct unsafe_comparison {};		// Exception class.
  static unsigned number_of_failures;	// Number of filter failures.
  static const IA Smallest, Largest;	// Useful constant intervals.

  Interval_base () {}

  // This copy ctor, normally equivalent to the one created by the compiler,
  // appears to fix a code generation problem with GCC 3.0.4...
  // (see test/IA/gcc_3.0.bug.C).
  Interval_base (const Interval_base &i)
    : inf_(i.inf_), sup_(i.sup_) {}

  Interval_base (const double d)
    : inf_(d), sup_(d) {}

  Interval_base (const double i, const double s)
    : inf_(i), sup_(s)
  {
      // VC++ should use instead : (i<=s) || !is_valid(i) || !is_valid(s)
      // Or should I use is_valid() ? or is_valid_or_nan() ?
    CGAL_assertion_msg(!(i>s),
	      " Variable used before being initialized (or CGAL bug)");
  }

  static void overlap_action() // throw (unsafe_comparison)
  {
    number_of_failures++;
    throw unsafe_comparison();
  }

  bool operator<  (const IA &d) const
  {
    if (sup_  < d.inf_) return true;
    if (inf_ >= d.sup_) return false;
    overlap_action();
    return false;
  }

  bool operator>  (const IA &d) const
  {
    return d < *this;
  }

  bool operator<= (const IA &d) const
  {
    if (sup_ <= d.inf_) return true;
    if (inf_ >  d.sup_) return false;
    overlap_action();
    return false;
  }

  bool operator>= (const IA &d) const
  {
    return d <= *this;
  }

  bool operator== (const IA &d) const
  {
    if (d.inf_ >  sup_ || d.sup_  < inf_) return false;
    if (d.inf_ == sup_ && d.sup_ == inf_) return true;
    overlap_action();
    return false;
  }

  bool operator!= (const IA &d) const
  {
    return !(*this == d);
  }

  bool is_point() const
  {
    return sup_ == inf_;
  }

  bool is_same (const IA & d) const
  {
    return inf_ == d.inf_ && sup_ == d.sup_;
  }

  bool do_overlap (const IA & d) const
  {
    return !(d.inf_ > sup_ || d.sup_ < inf_);
  }

  double inf() const { return inf_; }
  double sup() const { return sup_; }

// protected:
  double inf_, sup_;	// "inf_" stores the lower bound, "sup_" the upper.
};

inline
Interval_base
to_interval (const Interval_base & d)
{
  return d;
}

// We put all the to_interval() of the builtin types here, because of #include
// circular dependencies otherwise.
inline
Interval_base
to_interval (const double & d)
{
  return Interval_base(d);
}

inline
Interval_base
to_interval (const float & f)
{
  return Interval_base(double(f));
}

inline
Interval_base
to_interval (const int & i)
{
  return Interval_base(double(i));
}

inline
Interval_base
to_interval (const short & s)
{
  return Interval_base(double(s));
}

inline
Interval_base
to_interval (const long & l)
{
  // actually we would like to compare number of mantissa bits,
  // this seems to be a sufficient approximation
  CGAL_assertion( sizeof(double) > sizeof(long) );
  // need something else for 64 bits longs.
  return Interval_base(double(l));
}

// to_interval(long long) is in Interval_arithmetic.h

inline
double
to_double (const Interval_base & d)
{
  return (d.sup_ + d.inf_) * 0.5;
  // This may overflow...
}

inline
bool
is_valid (const Interval_base & d)
{
#if defined _MSC_VER || defined __sgi || defined __BORLANDC__
  return CGAL::is_valid(d.inf_) && CGAL::is_valid(d.sup_) && d.inf_ <= d.sup_;
#else
  // The 2 first is_valid() are implicitely done by the 3rd test ;-)
  return d.inf_ <= d.sup_;
#endif
}

inline
bool
is_finite (const Interval_base & d)
{
  return CGAL::is_finite(d.inf_) && CGAL::is_finite(d.sup_);
}

inline
io_Operator
io_tag (const Interval_base &)
{
  return io_Operator();
}

std::ostream & operator<< (std::ostream &, const Interval_base &);
std::istream & operator>> (std::istream &, Interval_base &);

CGAL_END_NAMESPACE

#endif // CGAL_INTERVAL_BASE_H
