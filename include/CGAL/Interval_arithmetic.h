// Copyright (c) 1998,1999,2000,2001,2002  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Interval_arithmetic/include/CGAL/Interval_arithmetic.h,v $
// $Revision: 2.142 $ $Date: 2003/10/21 12:17:23 $
// $Name: current_submission $
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_INTERVAL_ARITHMETIC_H
#define CGAL_INTERVAL_ARITHMETIC_H

// This file contains the description of the following classes:
// - Interval_nt<false>  It's a number type that needs the FPU rounding mode
//                       to be set to +inf.  It is also typedef'd to
//                       Interval_nt_advanced for backward compatibility.
// - Interval_nt<true>   Same but it does the rounding mode itself so you
//                       don't have to worry about it.  But it's slower.
//
// Note: When rounding is towards +infinity, to make an operation rounded
// towards -infinity, it's enough to take the opposite of some of the operand,
// and the opposite of the result (see operator+, operator*,...).

#include <CGAL/basic.h>
#include <iostream>
#include <CGAL/FPU.h>

CGAL_BEGIN_NAMESPACE

namespace CGALi {

  struct Unsafe_comparison {};    // Exception class.

  const double Huge_val = HUGE_VAL; // Workaround for G++ 2.95 on Linux.
}

template <bool Protected = true>
class Interval_nt
{
  typedef Interval_nt<Protected>     IA;
  typedef std::pair<double, double>  Pair;
public:
  typedef Tag_false   Has_gcd;
  typedef Tag_true    Has_division;
  typedef Tag_true    Has_sqrt;

  typedef CGALi::Unsafe_comparison unsafe_comparison;

  static unsigned number_of_failures;	// Number of filter failures.

  Interval_nt() {}

  Interval_nt(int i)
    : inf_sup(i, i) {}

  Interval_nt(double d)
    : inf_sup(d, d) {}

  Interval_nt(double i, double s)
    : inf_sup(i, s)
  {
      // VC++ should use instead : (i<=s) || !is_valid(i) || !is_valid(s)
      // Or should I use is_valid() ? or is_valid_or_nan() ?
    CGAL_assertion_msg(!(i>s),
	      " Variable used before being initialized (or CGAL bug)");
  }

  // This copy ctor, normally equivalent to the one created by the compiler,
  // appears to fix a code generation problem with GCC 3.0.4...
  // (see test/IA/gcc_3.0.bug.C).
  Interval_nt(const Interval_nt & i)
    : inf_sup(i.pair()) {}

  Interval_nt(const Pair & p)
    : inf_sup(p) {}

  IA operator-() const { return IA (-sup(), -inf()); }

  IA & operator+= (const IA &d) { return *this = *this + d; }
  IA & operator-= (const IA &d) { return *this = *this - d; }
  IA & operator*= (const IA &d) { return *this = *this * d; }
  IA & operator/= (const IA &d) { return *this = *this / d; }
  
  static void overlap_action() // throw (unsafe_comparison)
  {
    number_of_failures++;
    throw unsafe_comparison();
  }

  // TODO : Maybe I should suppress these : they are useless and risky.

  // The (join, union, ||) operator.
  IA operator|| (const IA & d) const
  {
    return IA(std::min(inf(), d.inf()), std::max(sup(), d.sup()));
  }

  // The (meet, intersection, &&) operator.  Valid if intervals overlap.
  IA operator&& (const IA & d) const
  {
    return IA(std::max(inf(), d.inf()), std::min(sup(), d.sup()));
  }

  bool is_point() const
  {
    return sup() == inf();
  }

  bool is_same (const IA & d) const
  {
    return inf() == d.inf() && sup() == d.sup();
  }

  bool do_overlap (const IA & d) const
  {
    return !(d.inf() > sup() || d.sup() < inf());
  }

  double inf() const { return inf_sup.first; }
  double sup() const { return inf_sup.second; }

  const std::pair<double,double>& pair() const
  {
    return inf_sup;
  }

  static IA largest()
  {
    // G++ 2.95 on Linux has problems with HUGE_VAL in template context.
    // (it's a macro defined by "__extension__ ..." and it gets lost.
    return IA(-CGALi::Huge_val, CGALi::Huge_val);
  } 

  static IA smallest()
  {
    return IA(-CGAL_IA_MIN_DOUBLE, CGAL_IA_MIN_DOUBLE);
  }

private:
  Pair inf_sup;
};

template <bool Protected>
unsigned Interval_nt<Protected>::number_of_failures;

template <bool Protected>
inline
bool
operator<(const Interval_nt<Protected> &a, const Interval_nt<Protected> &b)
{
  if (a.sup()  < b.inf()) return true;
  if (a.inf() >= b.sup()) return false;
  a.overlap_action();
  return false;
}

template <bool Protected>
inline
bool
operator>(const Interval_nt<Protected> &a, const Interval_nt<Protected> &b)
{ return b < a; }

template <bool Protected>
inline
bool
operator<=(const Interval_nt<Protected> &a, const Interval_nt<Protected> &b)
{
  if (a.sup() <= b.inf()) return true;
  if (a.inf() >  b.sup()) return false;
  a.overlap_action();
  return false;
}

template <bool Protected>
inline
bool
operator>=(const Interval_nt<Protected> &a, const Interval_nt<Protected> &b)
{ return b <= a; }

template <bool Protected>
inline
bool
operator==(const Interval_nt<Protected> &a, const Interval_nt<Protected> &b)
{
  if (b.inf() >  a.sup() || b.sup() <  a.inf()) return false;
  if (b.inf() == a.sup() && b.sup() == a.inf()) return true;
  a.overlap_action();
  return false;
}

template <bool Protected>
inline
bool
operator!=(const Interval_nt<Protected> &a, const Interval_nt<Protected> &b)
{ return ! (a == b); }

// Mixed operators.

template <bool Protected>
inline
bool
operator<(int a, const Interval_nt<Protected> &b)
{
  if (a < b.inf()) return true;
  if (a >= b.sup()) return false;
  b.overlap_action();
  return false;
}

template <bool Protected>
inline
bool
operator>(int a, const Interval_nt<Protected> &b)
{ return b < a; }

template <bool Protected>
inline
bool
operator<=(int a, const Interval_nt<Protected> &b)
{
  if (a <= b.inf()) return true;
  if (a >  b.sup()) return false;
  b.overlap_action();
  return false;
}

template <bool Protected>
inline
bool
operator>=(int a, const Interval_nt<Protected> &b)
{ return b <= a; }

template <bool Protected>
inline
bool
operator==(int a, const Interval_nt<Protected> &b)
{
  if (b.inf() >  a || b.sup() <  a) return false;
  if (b.inf() == a && b.sup() == a) return true;
  b.overlap_action();
  return false;
}

template <bool Protected>
inline
bool
operator!=(int a, const Interval_nt<Protected> &b)
{ return ! (a == b); }

template <bool Protected>
inline
bool
operator<(const Interval_nt<Protected> &a, int b)
{
  if (a.sup()  < b) return true;
  if (a.inf() >= b) return false;
  a.overlap_action();
  return false;
}

template <bool Protected>
inline
bool
operator>(const Interval_nt<Protected> &a, int b)
{ return b < a; }

template <bool Protected>
inline
bool
operator<=(const Interval_nt<Protected> &a, int b)
{
  if (a.sup() <= b) return true;
  if (a.inf() >  b) return false;
  a.overlap_action();
  return false;
}

template <bool Protected>
inline
bool
operator>=(const Interval_nt<Protected> &a, int b)
{ return b <= a; }

template <bool Protected>
inline
bool
operator==(const Interval_nt<Protected> &a, int b)
{
  if (b >  a.sup() || b <  a.inf()) return false;
  if (b == a.sup() && b == a.inf()) return true;
  a.overlap_action();
  return false;
}

template <bool Protected>
inline
bool
operator!=(const Interval_nt<Protected> &a, int b)
{ return ! (a == b); }


template <bool Protected>
inline
double
to_double (const Interval_nt<Protected> & d)
{
  return (d.sup() + d.inf()) * 0.5;
  // This may overflow...
}

template <bool Protected>
inline
const std::pair<double,double> &
to_interval (const Interval_nt<Protected> & d)
{
  return d.pair();
}


template <bool Protected>
inline
bool
is_valid (const Interval_nt<Protected> & d)
{
#if defined _MSC_VER || defined __sgi || defined __BORLANDC__
  return CGAL::is_valid(d.inf()) && 
    CGAL::is_valid(d.sup()) && 
    d.inf() <= d.sup();
#else
  // The 2 first is_valid() are implicitely done by the 3rd test ;-)
  return d.inf() <= d.sup();
#endif
}

template <bool Protected>
inline
bool
is_finite (const Interval_nt<Protected> & d)
{
  return CGAL::is_finite(d.inf()) && CGAL::is_finite(d.sup());
}

template <bool Protected>
inline
io_Operator
io_tag (const Interval_nt<Protected> &)
{
  return io_Operator();
}

template <bool Protected>
std::ostream & operator<< (std::ostream &os, const Interval_nt<Protected> & I )
{
  return os << "[" << I.inf() << ";" << I.sup() << "]";
}

template <bool Protected>
std::istream & operator>> (std::istream &is, Interval_nt<Protected> & I)
{
    double d;
    is >> d;
    I = d;
    return is;
}


typedef Interval_nt<false> Interval_nt_advanced;  // for back-compatibility


template <bool Protected>
inline
Interval_nt<Protected>
operator+ (const Interval_nt<Protected> &a, const Interval_nt<Protected> & b)
{
  Protect_FPU_rounding<Protected> P;
  return Interval_nt<Protected> (-CGAL_IA_SUB(-a.inf(), b.inf()),
                                  CGAL_IA_ADD(a.sup(), b.sup()));
}

template <bool Protected>
inline
Interval_nt<Protected>
operator+ (double a, const Interval_nt<Protected> & b)
{
  return Interval_nt<Protected>(a)+b;
}

template <bool Protected>
inline
Interval_nt<Protected>
operator+ (const Interval_nt<Protected> & a, double b)
{
  return a+Interval_nt<Protected>(b);
}

template <bool Protected>
inline
Interval_nt<Protected>
operator+ (int a, const Interval_nt<Protected> & b)
{
  return Interval_nt<Protected>(a)+b;
}

template <bool Protected>
inline
Interval_nt<Protected>
operator+ (const Interval_nt<Protected> & a, int b)
{
  return a+Interval_nt<Protected>(b);
}

template <bool Protected>
inline
Interval_nt<Protected>
operator- (const Interval_nt<Protected> &a, const Interval_nt<Protected> & b)
{
  Protect_FPU_rounding<Protected> P;
  return Interval_nt<Protected>(-CGAL_IA_SUB(b.sup(), a.inf()),
                                 CGAL_IA_SUB(a.sup(), b.inf()));
}

template <bool Protected>
inline
Interval_nt<Protected>
operator- (double a, const Interval_nt<Protected> & b)
{
  return Interval_nt<Protected>(a)-b;
}

template <bool Protected>
inline
Interval_nt<Protected>
operator- (const Interval_nt<Protected> & a, double b)
{
  return a-Interval_nt<Protected>(b);
}

template <bool Protected>
inline
Interval_nt<Protected>
operator- (int a, const Interval_nt<Protected> & b)
{
  return Interval_nt<Protected>(a)-b;
}

template <bool Protected>
inline
Interval_nt<Protected>
operator- (const Interval_nt<Protected> & a, int b)
{
  return a-Interval_nt<Protected>(b);
}

template <bool Protected>
#ifndef CGAL_IA_NO_INLINE
inline
#endif
Interval_nt<Protected>
operator* (const Interval_nt<Protected> &a, const Interval_nt<Protected> & b)
{
  typedef Interval_nt<Protected> IA;
  Protect_FPU_rounding<Protected> P;
  if (a.inf() >= 0.0)					// e>=0
  {
    // b>=0     [a.inf()*b.inf(); a.sup()*b.sup()]
    // b<=0     [a.sup()*b.inf(); a.inf()*b.sup()]
    // b~=0     [a.sup()*b.inf(); a.sup()*b.sup()]
    double aa = a.inf(), bb = a.sup();
    if (b.inf() < 0.0)
    {
	aa = bb;
	if (b.sup() < 0.0)
	    bb = a.inf();
    }
    return IA(-CGAL_IA_MUL(aa, -b.inf()), CGAL_IA_MUL(bb, b.sup()));
  }
  else if (a.sup()<=0.0)				// e<=0
  {
    // b>=0     [a.inf()*b.sup(); a.sup()*b.inf()]
    // b<=0     [a.sup()*b.sup(); a.inf()*b.inf()]
    // b~=0     [a.inf()*b.sup(); a.inf()*b.inf()]
    double aa = a.sup(), bb = a.inf();
    if (b.inf() < 0.0)
    {
	aa=bb;
	if (b.sup() < 0.0)
	    bb=a.sup();
    }
    return IA(-CGAL_IA_MUL(bb, -b.sup()), CGAL_IA_MUL(aa, b.inf()));
  }
  else						// 0 \in [inf();sup()]
  {
    if (b.inf()>=0.0)				// d>=0
      return IA(-CGAL_IA_MUL(-a.inf(), b.sup()),
                 CGAL_IA_MUL(a.sup(), b.sup()));
    if (b.sup()<=0.0)				// d<=0
      return IA(-CGAL_IA_MUL(a.sup(), -b.inf()),
                 CGAL_IA_MUL(a.inf(), b.inf()));
        					// 0 \in d
    double tmp1 = CGAL_IA_MUL(-a.inf(),  b.sup());
    double tmp2 = CGAL_IA_MUL( a.sup(), -b.inf());
    double tmp3 = CGAL_IA_MUL( a.inf(),  b.inf());
    double tmp4 = CGAL_IA_MUL( a.sup(),  b.sup());
    return IA(-std::max(tmp1,tmp2), std::max(tmp3,tmp4));
  }
}

template <bool Protected>
inline
Interval_nt<Protected>
operator* (double a, const Interval_nt<Protected> & b)
{
  return Interval_nt<Protected>(a)*b;
}

template <bool Protected>
inline
Interval_nt<Protected>
operator* (const Interval_nt<Protected> & a, double b)
{
  return a*Interval_nt<Protected>(b);
}

template <bool Protected>
inline
Interval_nt<Protected>
operator* (int a, const Interval_nt<Protected> & b)
{
  return Interval_nt<Protected>(a)*b;
}

template <bool Protected>
inline
Interval_nt<Protected>
operator* (const Interval_nt<Protected> & a, int b)
{
  return a*Interval_nt<Protected>(b);
}

template <bool Protected>
#ifndef CGAL_IA_NO_INLINE
inline
#endif
Interval_nt<Protected>
operator/ (const Interval_nt<Protected> &a, const Interval_nt<Protected> & b)
{
  typedef Interval_nt<Protected> IA;
  Protect_FPU_rounding<Protected> P;
  if (b.inf() > 0.0)				// b>0
  {
    // e>=0	[a.inf()/b.sup(); a.sup()/b.inf()]
    // e<=0	[a.inf()/b.inf(); a.sup()/b.sup()]
    // e~=0	[a.inf()/b.inf(); a.sup()/b.inf()]
    double aa = b.sup(), bb = b.inf();
    if (a.inf() < 0.0)
    {
	aa = bb;
	if (a.sup() < 0.0)
	    bb = b.sup();
    };
    return IA(-CGAL_IA_DIV(-a.inf(), aa), CGAL_IA_DIV(a.sup(), bb));
  }
  else if (b.sup()<0.0)			// b<0
  {
    // e>=0	[a.sup()/b.sup(); a.inf()/b.inf()]
    // e<=0	[a.sup()/b.inf(); a.inf()/b.sup()]
    // e~=0	[a.sup()/b.sup(); a.inf()/b.sup()]
    double aa = b.sup(), bb = b.inf();
    if (a.inf() < 0.0)
    {
	bb = aa;
	if (a.sup() < 0.0)
	    aa = b.inf();
    };
    return IA(-CGAL_IA_DIV(-a.sup(), aa), CGAL_IA_DIV(a.inf(), bb));
  }
  else					// b~0
    return IA::largest();
	   // We could do slightly better -> [0;HUGE_VAL] when b.sup()==0,
	   // but is this worth ?
}

template <bool Protected>
inline
Interval_nt<Protected>
operator/ (double a, const Interval_nt<Protected> & b)
{
  return Interval_nt<Protected>(a)/b;
}

template <bool Protected>
inline
Interval_nt<Protected>
operator/ (const Interval_nt<Protected> & a, double b)
{
  return a/Interval_nt<Protected>(b);
}

template <bool Protected>
inline
Interval_nt<Protected>
operator/ (int a, const Interval_nt<Protected> & b)
{
  return Interval_nt<Protected>(a)/b;
}

template <bool Protected>
inline
Interval_nt<Protected>
operator/ (const Interval_nt<Protected> & a, int b)
{
  return a/Interval_nt<Protected>(b);
}

template <bool Protected>
inline
Interval_nt<Protected>
sqrt (const Interval_nt<Protected> & d)
{
  Protect_FPU_rounding<Protected> P;  // not optimal here.
  // sqrt([+a,+b]) => [sqrt(+a);sqrt(+b)]
  // sqrt([-a,+b]) => [0;sqrt(+b)] => assumes roundoff error.
  // sqrt([-a,-b]) => [0;sqrt(-b)] => assumes user bug (unspecified result).
  FPU_set_cw(CGAL_FE_DOWNWARD);
  double i = (d.inf() > 0.0) ? CGAL_IA_SQRT(d.inf()) : 0.0;
  FPU_set_cw(CGAL_FE_UPWARD);
  return Interval_nt<Protected>(i, CGAL_IA_SQRT(d.sup()));
}

#ifndef CGAL_CFG_MATCHING_BUG_2
template <bool Protected>
inline
Interval_nt<Protected>
min (const Interval_nt<Protected> & d, const Interval_nt<Protected> & e)
{
  return Interval_nt<Protected>(std::min(d.inf(), e.inf()),
		                std::min(d.sup(), e.sup()));
}

template <bool Protected>
inline
Interval_nt<Protected>
max (const Interval_nt<Protected> & d, const Interval_nt<Protected> & e)
{
  return Interval_nt<Protected>(std::max(d.inf(), e.inf()),
		                std::max(d.sup(), e.sup()));
}

#else

inline
Interval_nt<false>
min (const Interval_nt<false> & d, const Interval_nt<false> & e)
{
  return Interval_nt<false>(min(d.inf(), e.inf()),min(d.sup(), e.sup()));
}

inline
Interval_nt<false>
max (const Interval_nt<false> & d, const Interval_nt<false> & e)
{
  return Interval_nt<false>(max(d.inf(), e.inf()),max(d.sup(), e.sup()));
}

inline
Interval_nt<true>
min (const Interval_nt<true> & d, const Interval_nt<true> & e)
{
  return Interval_nt<true>(min(d.inf(), e.inf()),min(d.sup(), e.sup()));
}

inline
Interval_nt<true>
max (const Interval_nt<true> & d, const Interval_nt<true> & e)
{
  return Interval_nt<true>(max(d.inf(), e.inf()),max(d.sup(), e.sup()));
}

#endif // CGAL_CFG_MATCHING_BUG_2

#ifndef CGAL_CFG_MATCHING_BUG_2
template <bool Protected>
inline
Interval_nt<Protected>
square (const Interval_nt<Protected> & d)
{
  Protect_FPU_rounding<Protected> P;
  if (d.inf()>=0.0)
      return Interval_nt<Protected>(-CGAL_IA_MUL(d.inf(), -d.inf()),
	                             CGAL_IA_MUL(d.sup(), d.sup()));
  if (d.sup()<=0.0)
      return Interval_nt<Protected>(-CGAL_IA_MUL(d.sup(), -d.sup()),
	     	                     CGAL_IA_MUL(d.inf(), d.inf()));
  return Interval_nt<Protected>(0.0, CGAL_IA_SQUARE(std::max(-d.inf(),
							     d.sup())));
}

template <bool Protected>
inline
Interval_nt<Protected>
abs (const Interval_nt<Protected> & d)
{
  if (d.inf() >= 0.0) return d;
  if (d.sup() <= 0.0) return -d;
  return Interval_nt<Protected>(0.0, std::max(-d.inf(), d.sup()));
}

template <bool Protected>
inline
Sign
sign (const Interval_nt<Protected> & d)
{
  if (d.inf() > 0.0) return POSITIVE;
  if (d.sup() < 0.0) return NEGATIVE;
  if (d.inf() == d.sup()) return ZERO;
  Interval_nt<Protected>::overlap_action();
  return ZERO;
}

template <bool Protected>
inline
Comparison_result
compare (const Interval_nt<Protected> & d, const Interval_nt<Protected> & e)
{
  if (d.inf() > e.sup()) return LARGER;
  if (e.inf() > d.sup()) return SMALLER;
  if (e.inf() == d.sup() && d.inf() == e.sup()) return EQUAL;
  Interval_nt<Protected>::overlap_action();
  return EQUAL;
}
#else // CGAL_CFG_MATCHING_BUG_2
// For crappy "compilers", we have to define complete overloaded functions.
// First we overload for true.
inline
Interval_nt<true>
square (const Interval_nt<true> & d)
{
  Protect_FPU_rounding<true> P;
  if (d.inf()>=0.0)
      return Interval_nt<true>(-CGAL_IA_MUL(d.inf(), -d.inf()),
	                        CGAL_IA_MUL(d.sup(), d.sup()));
  if (d.sup()<=0.0)
      return Interval_nt<true>(-CGAL_IA_MUL(d.sup(), -d.sup()),
	                        CGAL_IA_MUL(d.inf(), d.inf()));
  return Interval_nt<true>(0.0, CGAL_IA_SQUARE(std::max(-d.inf(), d.sup())));
}

inline
Interval_nt<true>
abs (const Interval_nt<true> & d)
{
  if (d.inf() >= 0.0) return d;
  if (d.sup() <= 0.0) return -d;
  return Interval_nt<true>(0.0, std::max(-d.inf(), d.sup()));
}

inline
Sign
sign (const Interval_nt<true> & d)
{
  if (d.inf() > 0.0) return POSITIVE;
  if (d.sup() < 0.0) return NEGATIVE;
  if (d.inf() == d.sup()) return ZERO;
  Interval_nt<true>::overlap_action();
  return ZERO;
}

inline
Comparison_result
compare (const Interval_nt<true> & d, const Interval_nt<true> & e)
{
  if (d.inf() > e.sup()) return LARGER;
  if (e.inf() > d.sup()) return SMALLER;
  if (e.inf() == d.sup() && d.inf() == e.sup()) return EQUAL;
  Interval_nt<true>::overlap_action();
  return EQUAL;
}

// Then we overload for false.
inline
Interval_nt<false>
square (const Interval_nt<false> & d)
{
  Protect_FPU_rounding<false> P;
  if (d.inf()>=0.0)
      return Interval_nt<false>(-CGAL_IA_MUL(d.inf(), -d.inf()),
	                         CGAL_IA_MUL(d.sup(), d.sup()));
  if (d.sup()<=0.0)
      return Interval_nt<false>(-CGAL_IA_MUL(d.sup(), -d.sup()),
	                         CGAL_IA_MUL(d.inf(), d.inf()));
  return Interval_nt<false>(0.0, CGAL_IA_SQUARE(std::max(-d.inf(), d.sup())));
}

inline
Interval_nt<false>
abs (const Interval_nt<false> & d)
{
  if (d.inf() >= 0.0) return d;
  if (d.sup() <= 0.0) return -d;
  return Interval_nt<false>(0.0, std::max(-d.inf(), d.sup()));
}

inline
Sign
sign (const Interval_nt<false> & d)
{
  if (d.inf() > 0.0) return POSITIVE;
  if (d.sup() < 0.0) return NEGATIVE;
  if (d.inf() == d.sup()) return ZERO;
  Interval_nt<false>::overlap_action();
  return ZERO;
}

inline
Comparison_result
compare (const Interval_nt<false> & d, const Interval_nt<false> & e)
{
  if (d.inf() > e.sup()) return LARGER;
  if (e.inf() > d.sup()) return SMALLER;
  if (e.inf() == d.sup() && d.inf() == e.sup()) return EQUAL;
  Interval_nt<false>::overlap_action();
  return EQUAL;
}
#endif // CGAL_CFG_MATCHING_BUG_2

inline
std::pair<double,double>
to_interval (const long & l)
{
#ifndef __BORLANDC__ // The stupid Borland compiler generates warnings...
  if (sizeof(double) > sizeof(long)) {
    // On 64bit platforms, a long doesn't fit exactly in a double.
    // Well, a perfect fix would be to use std::numeric_limits<>, but...
    Protect_FPU_rounding<true> P(CGAL_FE_TONEAREST);
    Interval_nt<false> approx ((double) l);
    FPU_set_cw(CGAL_FE_UPWARD);
    approx += Interval_nt<false>::smallest();
    return approx.pair();
  }
  else
#endif
    return std::pair<double,double>(l,l);
}

CGAL_END_NAMESPACE

#endif // CGAL_INTERVAL_ARITHMETIC_H
