// Copyright (c) 1999,2000,2003  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/Interval_arithmetic/include/CGAL/Lazy_exact_nt.h,v $
// $Revision: 2.75 $ $Date: 2003/10/21 12:17:24 $
// $Name: current_submission $
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_LAZY_EXACT_NT_H
#define CGAL_LAZY_EXACT_NT_H

#include <CGAL/basic.h>
#include <CGAL/tags.h>
#include <CGAL/number_utils.h>
#include <CGAL/number_utils_classes.h>
#include <CGAL/Number_type_traits.h>
#include <CGAL/Interval_arithmetic.h>
#include <CGAL/Handle.h>
#include <CGAL/misc.h>

/*
 * This file contains the definition of the number type Lazy_exact_nt<ET>,
 * where ET is an exact number type (must provide the exact operations needed).
 *
 * Lazy_exact_nt<ET> provides a DAG-based lazy evaluation, like LEDA's real,
 * Core's Expr, LEA's lazy rationals...
 *
 * The values are first approximated using Interval_base.
 * The exactness is provided when needed by ET.
 *
 * Lazy_exact_nt<ET> is just a handle to the abstract base class
 * Lazy_exact_rep which has pure virtual methods .approx() and .exact().
 * From this class derives one class per operation, with one constructor.
 *
 * The DAG is managed by :
 * - Handle and Rep.
 * - virtual functions to denote the various operators (instead of an enum).
 *
 * Other packages with vaguely similar design : APU, MetaCGAL, LOOK.
 */

/*
 * TODO :
 * - Generalize it for constructions at the kernel level.
 * - Interval rafinement functionnality ?
 * - Separate the handle and the representation(s) in 2 files (?)
 *   maybe not a good idea, better if everything related to one operation is
 *   close together.
 * - Add a CT template parameter like Filtered_exact_nt<> ?
 * - Add a string constant to provide an expression string (a la MetaCGAL) ?
 *   // virtual ostream operator<<() const = 0; // or string, like Core ?
 * - Have a template-expression (?) thing that evaluates a temporary element,
 *   and allocates stuff in memory only when really needs to convert to the
 *   NT.  (cf gmp++, and maybe other things, Blitz++, Synaps...)
 */

/*
 * Interface of the rep classes:
 * - .approx()      returns Interval_nt<> (assumes rounding=nearest).
 *                  [ only called from the handle, and declared in the base ]
 * - .exact()       returns ET, if not already done, computes recursively
 *
 * - .rafine_approx()  later we can do that (having a birthdate like LOOK ?).
 *                     could use update_approx().
 */

CGAL_BEGIN_NAMESPACE

template <typename ET> class Lazy_exact_nt;

// Abstract base representation class
template <typename ET>
struct Lazy_exact_rep : public Rep
{
  Interval_nt<true> in; // could be const, except for rafinement ? or mutable ?
  ET *et; // mutable as well ?

  Lazy_exact_rep (const Interval_nt<true> & i)
      : in(i), et(NULL) {}

private:
  Lazy_exact_rep (const Lazy_exact_rep&) { abort(); } // cannot be copied.
public:

  const Interval_nt<true>& approx() const
  {
      return in;
  }

  const ET & exact()
  {
      if (et==NULL)
          update_exact();
      return *et;
  }

  virtual void update_approx() = 0;  // Not used anymore...  at the moment :)
  virtual void update_exact() = 0;
  virtual ~Lazy_exact_rep () { delete et; };
};

// int constant
template <typename ET>
struct Lazy_exact_Int_Cst : public Lazy_exact_rep<ET>
{
  Lazy_exact_Int_Cst (int i)
      : Lazy_exact_rep<ET>(double(i)) {}

  void update_approx() { CGAL_assertion(false); }
  void update_exact()  { this->et = new ET((int)this->in.inf()); }
};

// double constant
template <typename ET>
struct Lazy_exact_Cst : public Lazy_exact_rep<ET>
{
  Lazy_exact_Cst (double d)
      : Lazy_exact_rep<ET>(d) {}

  void update_approx() { CGAL_assertion(false); }
  void update_exact()  { this->et = new ET(this->in.inf()); }
};

// Exact constant
template <typename ET>
struct Lazy_exact_Ex_Cst : public Lazy_exact_rep<ET>
{
  Lazy_exact_Ex_Cst (const ET & e)
      : Lazy_exact_rep<ET>(to_interval(e))
  {
    this->et = new ET(e);
  }

  void update_approx() { CGAL_assertion(false); }
  void update_exact()  { CGAL_assertion(false); }
};

// Construction from a Lazy_exact_nt<ET1> (which keeps the lazyness).
template <typename ET, typename ET1>
struct Lazy_lazy_exact_Cst : public Lazy_exact_rep<ET>
{
  Lazy_lazy_exact_Cst (const Lazy_exact_nt<ET1> &x)
      : Lazy_exact_rep<ET>(x.approx()), l(x) {}

  void update_approx() { CGAL_assertion(false); }
  void update_exact()  { this->et = new ET(l.exact()); }

  Lazy_exact_nt<ET1> l;
};


// Unary  operations: abs, sqrt, square.
// Binary operations: +, -, *, /, min, max.

// Base unary operation
template <typename ET>
struct Lazy_exact_unary : public Lazy_exact_rep<ET>
{
  const Lazy_exact_nt<ET> op1;

  Lazy_exact_unary (const Interval_nt<true> &i, const Lazy_exact_nt<ET> &a)
      : Lazy_exact_rep<ET>(i), op1(a) {}
};

// Base binary operation
template <typename ET>
struct Lazy_exact_binary : public Lazy_exact_unary<ET>
{
  const Lazy_exact_nt<ET> op2;

  Lazy_exact_binary (const Interval_nt<true> &i,
		     const Lazy_exact_nt<ET> &a, const Lazy_exact_nt<ET> &b)
      : Lazy_exact_unary<ET>(i, a), op2(b) {}
};

// Here we could use a template class for all operations (STL provides
// function objects plus, minus, multiplies, divides...).  But it would require
// a template template parameter, and GCC 2.95 seems to crash easily with them.

// Macro for unary operations
#define CGAL_LAZY_UNARY_OP(OP, NAME)                                 \
template <typename ET>                                               \
struct NAME : public Lazy_exact_unary<ET>                            \
{                                                                    \
  NAME (const Lazy_exact_nt<ET> &a)                                  \
      : Lazy_exact_unary<ET>(OP(a.approx()), a) {}                   \
                                                                     \
  void update_approx() { this->in = OP(this->op1.approx()); }        \
  void update_exact()  { this->et = new ET(OP(this->op1.exact())); } \
};

CGAL_LAZY_UNARY_OP(CGAL::opposite,  Lazy_exact_Opp)
CGAL_LAZY_UNARY_OP(CGAL_NTS abs,    Lazy_exact_Abs)
CGAL_LAZY_UNARY_OP(CGAL_NTS square, Lazy_exact_Square)
CGAL_LAZY_UNARY_OP(CGAL::sqrt,      Lazy_exact_Sqrt)

// A macro for +, -, * and /
#define CGAL_LAZY_BINARY_OP(OP, NAME)                                 \
template <typename ET>                                                \
struct NAME : public Lazy_exact_binary<ET>                            \
{                                                                     \
  NAME (const Lazy_exact_nt<ET> &a, const Lazy_exact_nt<ET> &b)       \
    : Lazy_exact_binary<ET>(a.approx() OP b.approx(), a, b) {}        \
                                                                      \
  void update_approx()                                                \
  {                                                                   \
    this->in = this->op1.approx() OP this->op2.approx();              \
  }                                                                   \
  void update_exact()                                                 \
  {                                                                   \
    this->et = new ET(this->op1.exact() OP this->op2.exact());        \
  }                                                                   \
};

CGAL_LAZY_BINARY_OP(+, Lazy_exact_Add)
CGAL_LAZY_BINARY_OP(-, Lazy_exact_Sub)
CGAL_LAZY_BINARY_OP(*, Lazy_exact_Mul)
CGAL_LAZY_BINARY_OP(/, Lazy_exact_Div)

// Minimum
template <typename ET>
struct Lazy_exact_Min : public Lazy_exact_binary<ET>
{
  Lazy_exact_Min (const Lazy_exact_nt<ET> &a, const Lazy_exact_nt<ET> &b)
    : Lazy_exact_binary<ET>(min(a.approx(), b.approx()), a, b) {}

  void update_approx()
  {
    this->in = min(this->op1.approx(), this->op2.approx());
  }
  void update_exact()
  {
    this->et = new ET(min(this->op1.exact(), this->op2.exact()));
  }
};

// Maximum
template <typename ET>
struct Lazy_exact_Max : public Lazy_exact_binary<ET>
{
  Lazy_exact_Max (const Lazy_exact_nt<ET> &a, const Lazy_exact_nt<ET> &b)
    : Lazy_exact_binary<ET>(max(a.approx(), b.approx()), a, b) {}

  void update_approx()
  {
    this->in = max(this->op1.approx(), this->op2.approx());
  }
  void update_exact()
  {
    this->et = new ET(max(this->op1.exact(), this->op2.exact()));
  }
};


// The real number type, handle class
template <typename ET>
class Lazy_exact_nt : public Handle
{
public :
  typedef typename Number_type_traits<ET>::Has_gcd      Has_gcd;
  typedef typename Number_type_traits<ET>::Has_division Has_division;
  typedef typename Number_type_traits<ET>::Has_sqrt     Has_sqrt;

  typedef Lazy_exact_nt<ET> Self;
  typedef Lazy_exact_rep<ET> Self_rep;

  // Lazy_exact_nt () {} // Handle is not such a nice stuff...  at the moment.

  Lazy_exact_nt (Self_rep *r)
  { PTR = r; }

  // Operations
  Lazy_exact_nt (double d)
  { PTR = new Lazy_exact_Cst<ET>(d); }

  Lazy_exact_nt (int i = 0)
  { PTR = new Lazy_exact_Int_Cst<ET>(i); }

  Lazy_exact_nt (const ET & e)
  { PTR = new Lazy_exact_Ex_Cst<ET>(e); }

  template <class ET1>
  Lazy_exact_nt (const Lazy_exact_nt<ET1> &x)
  { PTR = new Lazy_lazy_exact_Cst<ET, ET1>(x); }

  Self operator- () const
  { return new Lazy_exact_Opp<ET>(*this); }

  const Interval_nt<true>& approx() const
  { return ptr()->approx(); }

  Interval_nt<false> interval() const
  { 
    const Interval_nt<true>& i = ptr()->approx();
    return Interval_nt<false>(i.inf(), i.sup());
  }

  Interval_nt_advanced approx_adv() const
  { return ptr()->approx(); }

  const ET & exact() const
  { return ptr()->exact(); }

private:
  Self_rep * ptr() const { return (Self_rep*) PTR; }
};

template <typename ET>
bool
operator<(const Lazy_exact_nt<ET>& a, const Lazy_exact_nt<ET>& b)
{
  try
  {
    return a.approx() < b.approx();
  }
  catch (Interval_nt<false>::unsafe_comparison)
  {
    // std::cerr << "Interval filter failure (<)" << std::endl;
    return a.exact() < b.exact();
  }
}

template <typename ET>
bool
operator==(const Lazy_exact_nt<ET>& a, const Lazy_exact_nt<ET>& b)
{
  try
  {
    return a.approx() == b.approx();
  }
  catch (Interval_nt<false>::unsafe_comparison)
  {
    // std::cerr << "Interval filter failure (==)" << std::endl;
    return a.exact() == b.exact();
  }
}

template <typename ET>
inline
bool
operator>(const Lazy_exact_nt<ET>& a, const Lazy_exact_nt<ET>& b)
{ return b < a; }

template <typename ET>
inline
bool
operator<=(const Lazy_exact_nt<ET>& a, const Lazy_exact_nt<ET>& b)
{ return ! (b < a); }

template <typename ET>
inline
bool
operator>=(const Lazy_exact_nt<ET>& a, const Lazy_exact_nt<ET>& b)
{ return ! (a < b); }

template <typename ET>
inline
bool
operator!=(const Lazy_exact_nt<ET>& a, const Lazy_exact_nt<ET>& b)
{ return ! (a == b); }


// Mixed operators with int.
template <typename ET>
bool
operator<(int a, const Lazy_exact_nt<ET>& b)
{
  try {
    return a < b.approx();
  }
  catch (Interval_nt<false>::unsafe_comparison) {
    return a < b.exact();
  }
}

template <typename ET>
bool
operator<(const Lazy_exact_nt<ET>& a, int b)
{
  try {
    return a.approx() < b;
  }
  catch (Interval_nt<false>::unsafe_comparison) {
    return a.exact() < b;
  }
}

template <typename ET>
bool
operator==(int a, const Lazy_exact_nt<ET>& b)
{
  try {
    return a == b.approx();
  }
  catch (Interval_nt<false>::unsafe_comparison) {
    return a == b.exact();
  }
}

template <typename ET>
inline
bool
operator==(const Lazy_exact_nt<ET>& a, int b)
{ return b == a; }

template <typename ET>
inline
bool
operator>(int a, const Lazy_exact_nt<ET>& b)
{ return b < a; }

template <typename ET>
inline
bool
operator>(const Lazy_exact_nt<ET>& a, int b)
{ return b < a; }

template <typename ET>
inline
bool
operator<=(int a, const Lazy_exact_nt<ET>& b)
{ return ! (b < a); }

template <typename ET>
inline
bool
operator<=(const Lazy_exact_nt<ET>& a, int b)
{ return ! (b < a); }

template <typename ET>
inline
bool
operator>=(int a, const Lazy_exact_nt<ET>& b)
{ return ! (a < b); }

template <typename ET>
inline
bool
operator>=(const Lazy_exact_nt<ET>& a, int b)
{ return ! (a < b); }

template <typename ET>
inline
bool
operator!=(int a, const Lazy_exact_nt<ET>& b)
{ return ! (a == b); }

template <typename ET>
inline
bool
operator!=(const Lazy_exact_nt<ET>& a, int b)
{ return ! (b == a); }


template <typename ET>
Lazy_exact_nt<ET>
operator+(const Lazy_exact_nt<ET>& a, const Lazy_exact_nt<ET>& b)
{ return new Lazy_exact_Add<ET>(a, b); }

template <typename ET>
Lazy_exact_nt<ET>
operator-(const Lazy_exact_nt<ET>& a, const Lazy_exact_nt<ET>& b)
{ return new Lazy_exact_Sub<ET>(a, b); }

template <typename ET>
Lazy_exact_nt<ET>
operator*(const Lazy_exact_nt<ET>& a, const Lazy_exact_nt<ET>& b)
{ return new Lazy_exact_Mul<ET>(a, b); }

template <typename ET>
Lazy_exact_nt<ET>
operator/(const Lazy_exact_nt<ET>& a, const Lazy_exact_nt<ET>& b)
{ return new Lazy_exact_Div<ET>(a, b); }

// mixed operators
template <typename ET>
Lazy_exact_nt<ET>
operator+(const Lazy_exact_nt<ET>& a, int b)
{ return new Lazy_exact_Add<ET>(a, b); }

template <typename ET>
Lazy_exact_nt<ET>
operator-(const Lazy_exact_nt<ET>& a, int b)
{ return new Lazy_exact_Sub<ET>(a, b); }

template <typename ET>
Lazy_exact_nt<ET>
operator*(const Lazy_exact_nt<ET>& a, int b)
{ return new Lazy_exact_Mul<ET>(a, b); }

template <typename ET>
Lazy_exact_nt<ET>
operator/(const Lazy_exact_nt<ET>& a, int b)
{ return new Lazy_exact_Div<ET>(a, b); }

template <typename ET>
Lazy_exact_nt<ET>
operator+(int a, const Lazy_exact_nt<ET>& b)
{ return new Lazy_exact_Add<ET>(a, b); }

template <typename ET>
Lazy_exact_nt<ET>
operator-(int a, const Lazy_exact_nt<ET>& b)
{ return new Lazy_exact_Sub<ET>(a, b); }

template <typename ET>
Lazy_exact_nt<ET>
operator*(int a, const Lazy_exact_nt<ET>& b)
{ return new Lazy_exact_Mul<ET>(a, b); }

template <typename ET>
Lazy_exact_nt<ET>
operator/(int a, const Lazy_exact_nt<ET>& b)
{ return new Lazy_exact_Div<ET>(a, b); }


template <typename ET>
inline
double
to_double(const Lazy_exact_nt<ET> & a)
{
    return CGAL::to_double(a.approx());
}

template <typename ET>
inline
std::pair<double,double>
to_interval(const Lazy_exact_nt<ET> & a)
{
    return a.approx().pair();
}

#ifndef CGAL_CFG_MATCHING_BUG_2
template <typename ET>
inline
Sign
sign(const Lazy_exact_nt<ET> & a)
{
  try
  {
    return CGAL_NTS sign(a.approx());
  }
  catch (Interval_nt<false>::unsafe_comparison)
  {
    // std::cerr << "Interval filter failure (sign)" << std::endl;
    return CGAL_NTS sign(a.exact());
  }
}

template <typename ET>
inline
Comparison_result
compare(const Lazy_exact_nt<ET> & a, const Lazy_exact_nt<ET> & b)
{
  try
  {
    return CGAL_NTS compare(a.approx(), b.approx());
  }
  catch (Interval_nt<false>::unsafe_comparison)
  {
    // std::cerr << "Interval filter failure (compare)" << std::endl;
    return CGAL_NTS compare(a.exact(), b.exact());
  }
}

template <typename ET>
inline
Lazy_exact_nt<ET>
abs(const Lazy_exact_nt<ET> & a)
{ return new Lazy_exact_Abs<ET>(a); }

template <typename ET>
inline
Lazy_exact_nt<ET>
square(const Lazy_exact_nt<ET> & a)
{ return new Lazy_exact_Square<ET>(a); }

#endif // CGAL_CFG_MATCHING_BUG_2

template <typename ET>
inline
Lazy_exact_nt<ET>
sqrt(const Lazy_exact_nt<ET> & a)
{ return new Lazy_exact_Sqrt<ET>(a); }

#ifndef CGAL_CFG_MATCHING_BUG_2
template <typename ET>
inline
Lazy_exact_nt<ET>
min(const Lazy_exact_nt<ET> & a, const Lazy_exact_nt<ET> & b)
{ return new Lazy_exact_Min<ET>(a, b); }

template <typename ET>
inline
Lazy_exact_nt<ET>
max(const Lazy_exact_nt<ET> & a, const Lazy_exact_nt<ET> & b)
{ return new Lazy_exact_Max<ET>(a, b); }
#endif // CGAL_CFG_MATCHING_BUG_2

template <typename ET>
std::ostream &
operator<< (std::ostream & os, const Lazy_exact_nt<ET> & a)
{ return os << CGAL::to_double(a); }

template <typename ET>
std::istream &
operator>> (std::istream & is, Lazy_exact_nt<ET> & a)
{
  ET e;
  is >> e;
  a = e;
  return is;
}

template <typename ET>
inline
Lazy_exact_nt<ET> &
operator+=(Lazy_exact_nt<ET> & a, const Lazy_exact_nt<ET> & b)
{ return a = a + b; }

template <typename ET>
inline
Lazy_exact_nt<ET> &
operator-=(Lazy_exact_nt<ET> & a, const Lazy_exact_nt<ET> & b)
{ return a = a - b; }

template <typename ET>
inline
Lazy_exact_nt<ET> &
operator*=(Lazy_exact_nt<ET> & a, const Lazy_exact_nt<ET> & b)
{ return a = a * b; }

template <typename ET>
inline
Lazy_exact_nt<ET> &
operator/=(Lazy_exact_nt<ET> & a, const Lazy_exact_nt<ET> & b)
{ return a = a / b; }

template <typename ET>
inline
Lazy_exact_nt<ET> &
operator+=(Lazy_exact_nt<ET> & a, int b)
{ return a = a + b; }

template <typename ET>
inline
Lazy_exact_nt<ET> &
operator-=(Lazy_exact_nt<ET> & a, int b)
{ return a = a - b; }

template <typename ET>
inline
Lazy_exact_nt<ET> &
operator*=(Lazy_exact_nt<ET> & a, int b)
{ return a = a * b; }

template <typename ET>
inline
Lazy_exact_nt<ET> &
operator/=(Lazy_exact_nt<ET> & a, int b)
{ return a = a / b; }

template <typename ET>
inline
bool
is_finite(const Lazy_exact_nt<ET> & a)
{
  return is_finite(a.approx()) || is_finite(a.exact());
}

template <typename ET>
inline
bool
is_valid(const Lazy_exact_nt<ET> & a)
{
  return is_valid(a.approx()) || is_valid(a.exact());
}

template <typename ET>
inline
io_Operator
io_tag (const Lazy_exact_nt<ET>&)
{ return io_Operator(); }
 
#ifndef CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION
template <typename ET>
struct converter<ET, Lazy_exact_nt<ET> >
{
    static inline ET do_it (const Lazy_exact_nt<ET> & z)
    {
        return z.exact();
    }
};
#endif

CGAL_END_NAMESPACE

#endif // CGAL_LAZY_EXACT_NT_H
