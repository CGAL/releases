/******************************************************************
 * Core Library Version 1.6, June 2003
 * Copyright (c) 1995-2002 Exact Computation Project
 * 
 * File: RealRep.h
 *
 * Synopsis: Internal Representation for Real
 *
 * Written by 
 *       Koji Ouchi <ouchi@simulation.nyu.edu>
 *       Chee Yap <yap@cs.nyu.edu>
 *       Chen Li <chenli@cs.nyu.edu>
 *       Zilin Du <zilin@cs.nyu.edu>
 *       Sylvain Pion <pion@cs.nyu.edu> 
 *
 * WWW URL: http://cs.nyu.edu/exact/
 * Email: exact@cs.nyu.edu
 *
 * $Id: RealRep.h,v 1.3 2003/08/06 12:59:28 afabri Exp $
 *****************************************************************/

#include <CORE/CoreImpl.h>
#include <CORE/CoreAux.h>
#include <CORE/BigFloat.h>
#include <CORE/MemoryPool.h>

#ifndef CORE_REALREP_H
#define CORE_REALREP_H

CORE_BEGIN_NAMESPACE
template <class T>
class Realbase_for;

typedef Realbase_for<long>     RealLong;
typedef Realbase_for<double>   RealDouble;
typedef Realbase_for<BigInt>   RealBigInt;
typedef Realbase_for<BigRat>   RealBigRat;
typedef Realbase_for<BigFloat> RealBigFloat;

//  forward reference
class Real;

/// \class RealRep 
/// \brief The internal representation of Real
class RealRep
{
public:
  /// reference counter
  unsigned refCount;
  
  /// most Significant Bit
  /** DEFINITION: MSB(0)=-\infty.  When E is not 0, and real, we define MSB(E)
      to be the natural number m such that 2^{m} <= |E| < 2^{m+1}. Hence, 
      MSB(E) is equal to floor(log_2(|E|)).  Intuitively, MSB is the position
      of the most significant bit in a binary rational representation of |E|.
      Thus, the bit before the binary point is considered to be position 0, 
      the the bit after the binary point is position -1.  Thus,
               ... b_2 b_1 b_0.b_{-1} b_{-2} ...
      E.g., MSB(1) = 0,
            MSB(1/2) = MSB((0.1)_2) = -1
	    MSB(1/4) = MSB((0.01)_2) = -2.
	    MSB(2) = MSB(3) = 1, MSB(4) = 2.
      Hence, if E is a non-zero integer, MSB(E) is equal to bitlength(|E|)-1.
      We also need upper and lower bounds on MSB(E).  This is defined to be
      any numbers lMSB(E) and uMSB(E) such that  lMSB(E) <= MSB(E) <= uMSB(E).
      THIS implies the following inequality:
            2^{lMSB(E)} <= |E| < 2^{1+uMSB(E)}.
      When E is an interval (e.g., BigFloat with non-zero error), then MSB(E)
      is not defined, but uMSB(E) and lMSB(E) is defined as follows:
      Assume E = [a, b].
         If 0 <  a <= b, then    lMSB(E) <= MSB(a) <= MSB(b) <= uMSB(E)
	 If a <= b <  0, then    lMSB(E) <= MSB(b) <= MSB(a) <= uMSB(E)
         If a <= 0 <= b, then    lMSB(E) = MSB(0) = -\infty
                                 uMSB(E) >=  max( MSB(a), MSB(b) ) */
  extLong mostSignificantBit;
  
  /// \name Constructor and Destructor
  //@{
  /// Constructor
  RealRep() : refCount(1) {}
  /// Destructor
  virtual ~RealRep() {}
  //@}
 
  /// \name Cast Operators
  //@{
  virtual operator double() const = 0;
  virtual operator float() const = 0;
  virtual operator long() const = 0;
  virtual operator int() const = 0;
  virtual BigInt BigIntValue() const = 0;
  virtual BigRat BigRatValue() const = 0;
  virtual BigFloat BigFloatValue() const = 0;
  /// convert to \c string
  /** give decimal string representation */
  // Joaquin Grech 31/5/2003
  virtual std::string toString(long prec, bool sci) const = 0;
  
  //@}
  
  /// \name Approximation
  //@{
  virtual Real approx(const extLong&, const extLong&) const = 0;
  //@}
 
  /// \name unary minus
  //@{
  virtual Real operator -() const = 0;
  //@}
  
  /// \name addition
  //@{
  virtual Real operator +(const Real&) const = 0;
  virtual Real addLong(const RealLong&) const = 0;
  virtual Real addDouble(const RealDouble&) const = 0;
  virtual Real addBigInt(const RealBigInt&) const = 0;
  virtual Real addBigFloat(const RealBigFloat&) const = 0;
  virtual Real addBigRat(const RealBigRat&) const = 0;
  //@}

  /// \name subtraction
  //@{
  virtual Real operator -(const Real&) const = 0;
  virtual Real subLong(const RealLong&) const = 0;
  virtual Real subDouble(const RealDouble&) const = 0;
  virtual Real subBigInt(const RealBigInt&) const = 0;
  virtual Real subBigFloat(const RealBigFloat&) const = 0;
  virtual Real subBigRat(const RealBigRat&) const = 0;
  //@}

  /// \name multiplication
  //@{
  virtual Real operator *(const Real&) const = 0;
  virtual Real mulLong(const RealLong&) const = 0;
  virtual Real mulDouble(const RealDouble&) const = 0;
  virtual Real mulBigInt(const RealBigInt&) const = 0;
  virtual Real mulBigFloat(const RealBigFloat&) const = 0;
  virtual Real mulBigRat(const RealBigRat&) const = 0;
  //@}  
  
  /// \name division
  //@{
  // virtual Real operator /(const Real&) const;
  virtual Real div(const Real&, const extLong&) const = 0;
  virtual Real divLong(const RealLong&, const extLong&) const = 0;
  virtual Real divDouble(const RealDouble&, const extLong&) const = 0;
  virtual Real divBigInt(const RealBigInt&, const extLong&) const = 0;
  virtual Real divBigFloat(const RealBigFloat&, const extLong&) const = 0;
  virtual Real divBigRat(const RealBigRat&, const extLong&) const = 0;
  //@}

  /// \name squareroot
  //@{
  virtual Real sqrt(const extLong&) const = 0;
  // sqrt with initial approximation
  virtual Real sqrt(const extLong&, const BigFloat &) const = 0; 
  //@}

  /// \name equality
  //@{
  virtual bool operator ==(const Real&) const = 0;
  virtual bool eqlLong(const RealLong&) const = 0;
  virtual bool eqlDouble(const RealDouble&) const = 0;
  virtual bool eqlBigInt(const RealBigInt&) const = 0;
  virtual bool eqlBigFloat(const RealBigFloat&) const = 0;
  virtual bool eqlBigRat(const RealBigRat&) const = 0;
  //@}
  
  /// \name smaller than
  //@{
  virtual bool operator <(const Real&) const = 0;
  virtual bool grtLong(const RealLong&) const = 0;
  virtual bool grtDouble(const RealDouble&) const = 0;
  virtual bool grtBigInt(const RealBigInt&) const = 0;
  virtual bool grtBigFloat(const RealBigFloat&) const = 0;
  virtual bool grtBigRat(const RealBigRat&) const = 0;
  //@}
  
  //  builtin functions
  //@{
  virtual bool    isExact() const = 0;
  virtual void ULV_E(extLong &up, extLong &lp, extLong &v2p, extLong &v2m,
		     extLong &v5p, extLong &v5m) const = 0;
  virtual extLong flrLgErr() const = 0;
  virtual extLong clLgErr() const = 0;
  virtual bool    isZeroIn() const = 0;
  virtual unsigned long degree() const = 0;
  virtual unsigned long length() const = 0;
  virtual unsigned long height() const = 0;
  virtual int sgn() const = 0;
  //@}
  //  I/O Stream
  //@{
  virtual std::ostream& operator <<(std::ostream&) const = 0;
  //@}
}; //class RealRep


template <class T>
class Realbase_for : public RealRep
{
public:
  CORE_MEMORY(Realbase_for)

  /// Kernel
  T ker;
  
  /// \name Constructor and Destructor
  //@{
  /// Constructor
  Realbase_for(const T&);
  /// Destructor
  ~Realbase_for() {}
  //@}
  
  /// Access to ker
  const T& get_ker() const { return ker; }

  /// \name cast operators
  //@{
  operator double() const;
  operator float() const;
  operator long() const;
  operator int() const;
  BigInt BigIntValue() const;
  BigRat BigRatValue() const;
  BigFloat BigFloatValue() const;
  virtual std::string toString(long prec, bool sci) const;
  //@}

  /// \name approximation
  //@{
  Real approx(const extLong&, const extLong&) const;
  //@}
  
  /// \name unary minus
  //@{
  Real operator -() const;
  //@}
  
  /// \name addition
  //@{
  Real operator +(const Real&) const;
  Real addLong(const RealLong&) const;
  Real addDouble(const RealDouble&) const;
  Real addBigInt(const RealBigInt&) const;
  Real addBigFloat(const RealBigFloat&) const;
  Real addBigRat(const RealBigRat&) const;
  //@}
  
  /// \name subtraction
  //@{
  Real operator -(const Real&) const;
  Real subLong(const RealLong&) const;
  Real subDouble(const RealDouble&) const;
  Real subBigInt(const RealBigInt&) const;
  Real subBigFloat(const RealBigFloat&) const;
  Real subBigRat(const RealBigRat&) const;
  //@}
  
  /// \name multiplication
  //@{
  Real operator *(const Real&) const;
  Real mulLong(const RealLong&) const;
  Real mulDouble(const RealDouble&) const;
  Real mulBigInt(const RealBigInt&) const;
  Real mulBigFloat(const RealBigFloat&) const;
  Real mulBigRat(const RealBigRat&) const;
  //@}

  /// \name division
  //@{
  Real div(const Real&, const extLong&) const;
  Real divLong(const RealLong&, const extLong&) const;
  Real divDouble(const RealDouble&, const extLong&) const;
  Real divBigInt(const RealBigInt&, const extLong&) const;
  Real divBigFloat(const RealBigFloat&, const extLong&) const;
  Real divBigRat(const RealBigRat&, const extLong&) const;
  //@}
  
  /// \name squareroot
  //@{
  Real sqrt(const extLong&) const;
  Real sqrt(const extLong&,  const BigFloat&) const;
  //@}
  
  /// \name equality
  //@{
  bool operator ==(const Real&) const;
  bool eqlLong(const RealLong&) const;
  bool eqlDouble(const RealDouble&) const;
  bool eqlBigInt(const RealBigInt&) const;
  bool eqlBigFloat(const RealBigFloat&) const;
  bool eqlBigRat(const RealBigRat&) const;
  //@}
  
  /// \name smaller-than
  //@{
  bool operator <(const Real&) const;
  bool grtLong(const RealLong&) const;
  bool grtDouble(const RealDouble&) const;
  bool grtBigInt(const RealBigInt&) const;
  bool grtBigFloat(const RealBigFloat&) const;
  bool grtBigRat(const RealBigRat&) const;
  //@}
  
  /// \name builtin functions
  //@{
  bool    isExact() const;
  void ULV_E(extLong &up, extLong &lp, extLong &v2p, extLong &v2m,
	     extLong &v5p, extLong &v5m) const;
  extLong flrLgErr() const;
  extLong clLgErr() const;
  bool    isZeroIn() const; 
  unsigned long degree() const;
  unsigned long length() const;
  unsigned long height() const;
  int sgn() const;
  //@}

  /// \name I/O stream
  //@{
  std::ostream& operator <<(std::ostream& o) const
{
  o << ker;
  return o;
};
  //@}
};

// The constructors of Realbase_for<> are specialized.
template <>
inline
Realbase_for<long>::Realbase_for(const long &l)
  : ker(l)
{
  mostSignificantBit = ((ker != 0) ? extLong(flrLg(ker)) : CORE_negInfty); 
  //  This computes the bit length of "ker" minus 1,
  //  i.e., floor(log_2(|ker|)) .
}

template <>
inline
Realbase_for<double>::Realbase_for(const double& d)
  : ker(d)
{
  mostSignificantBit = BigFloat(ker).MSB();
}

template <>
inline Realbase_for<BigInt>::Realbase_for(const BigInt& I)
  : ker(I)
{
  mostSignificantBit = (sign(ker)? extLong(floorLg(ker)) : CORE_negInfty);
}

template <>
inline
Realbase_for<BigFloat>::Realbase_for(const BigFloat& B)
  : ker(B)
{
  mostSignificantBit = ker.MSB();
}

template <>
inline
Realbase_for<BigRat>::Realbase_for(const BigRat& R)
 : ker(R)
{
  // MSB of a rational x/y is given by floorLg(|x/y|)
  BigInt x = ker.numerator();
  BigInt y = ker.denominator();
  if (ker.sign()) {
    mostSignificantBit = extLong(floorLg(x) - floorLg(y));
    x.abs();
    if ((y << mostSignificantBit.asLong()) > x) 
      mostSignificantBit = mostSignificantBit - 1;
  } else
    mostSignificantBit = CORE_negInfty;
  /*
  mostSignificantBit = ker.sign() ? \
       extLong(floorLg(x) - floorLg(y)) : CORE_negInfty;

  // This gives us an approximation to msb that could off by 1 in
  // one direction.  So we next adjust for this possibility:
  // The exact value of msb(x/y) is given by
  //   y.2^msb <= x < y.2^{msb+1}.

  // 5/16/02: fixed a bug in logic (Pion/Zilin/Chee)
  x.abs();
  if ((y << mostSignificantBit.asLong()) > x) 
       mostSignificantBit = mostSignificantBit - 1;
  */
}

CORE_END_NAMESPACE
#endif
