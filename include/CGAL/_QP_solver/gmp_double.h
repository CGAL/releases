// ======================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

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
// file          : include/CGAL/_QP_solver/gmp_double.h
// package       : _QP_solver (0.9.7)
//
// revision      : 0.1
// revision_date : 2000/08/09
//
// author(s)     : Sven Sch�nherr
// coordinator   : ETH Z�rich (Bernd G�rtner)
//
// implementation: arbitra. precise floating-point type based on GMP's integers
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef GMP_DOUBLE_H
#define GMP_DOUBLE_H

// includes
#include <CGAL/_QP_solver/gmp_integer.h>
#include <iostream>
#include <cmath>

namespace GMP {

// Class declaration
// =================
class Double;

// Function declaration
// ====================
inline std::ostream&  operator << ( std::ostream&, const Double&);


// Class interface
// ===============
class Double {
  public:
    // types
    typedef  GMP::Integer  Mantissa;
    typedef  long          Exponent;

    // construction
    Double( );
    Double( const Double&);
    Double( int);
    Double( double);
    Double( const Mantissa&, const Exponent&);

    // comparisons
    bool  operator == ( const Double&) const;
    bool  operator != ( const Double&) const;
    bool  operator <  ( const Double&) const;
    bool  operator >  ( const Double&) const;
    bool  operator <= ( const Double&) const;
    bool  operator >= ( const Double&) const;

    // arithmetic operations
    Double  operator - ( ) const;

    Double  operator + ( const Double&) const;
    Double  operator - ( const Double&) const;
    Double  operator * ( const Double&) const;
    Double  operator / ( const Double&) const;

    // arithmetic assignment operations
    Double&  operator += ( const Double&);
    Double&  operator -= ( const Double&);
    Double&  operator *= ( const Double&);
    Double&  operator /= ( const Double&);

    // shift operations
    Double  operator << ( unsigned long) const;
    Double  operator >> ( unsigned long) const;
    
    // shift assignment operations
    Double&  operator <<= ( unsigned long);
    Double&  operator >>= ( unsigned long);
    
    // sign function
    int  sign( ) const;

    // conversion function
    double  to_double( ) const;

    // access functions to the internal representation
    const Mantissa&  mantissa( ) const;
    const Exponent&  exponent( ) const;

    // normalization
    bool  is_normal( ) const;
    void  normalize( );

  private:
    // data members
    Mantissa  m;
    Exponent  e;
};

// ============================================================================

// Class implementation
// ====================

// normalization
// -------------

// is normalized?
inline
bool
Double::
is_normal( ) const
{
    return ( m.zeros() == 0);
}

// normalize
inline
void
Double::
normalize( )
{
    if ( m == 0)
	e = 0;
    else {
	int zeros = m.zeros();
	m >>= zeros;
	e  += zeros;
    }
}


// construction
// ------------

// default constructor
inline
Double::
Double( )
  : e( 0)
{ }

// copy constructor
inline
Double::
Double( const Double& d)
    : m( d.m), e( d.e)
{ }

// constructor (int)
inline
Double::
Double( int i)
    : m( i), e( 0)
{ }

// constructor (double)
inline
Double::
Double( double d)
{
    if ( d == 0.0)
	e = 0;
    else {
	int exp;
	double x = frexp( d, &exp);
	m = Mantissa( ldexp( x, 53));
	e = exp-53;
	normalize();
    }
}

// constructor (mantissa, exponent)
inline
Double::
Double( const Mantissa& mantissa, const Exponent& exponent)
    : m( mantissa), e( exponent)
{
    normalize();
}


// comparisons
// -----------

// equal
inline
bool
Double::
operator == ( const Double& d) const
{ 
    if ( e < d.e) return (   m                == ( d.m << ( d.e - e)));
    if ( e > d.e) return ( ( m << ( e - d.e)) ==   d.m               );
    return ( m == d.m);
}

// not equal
inline
bool
Double::
operator != ( const Double& d) const
{ 
    return !( *this == d);
}

// less
inline
bool
Double::
operator < ( const Double& d) const
{
    if ( e < d.e) return (   m                < ( d.m << ( d.e - e)));
    if ( e > d.e) return ( ( m << ( e - d.e)) <   d.m               );
    return ( m < d.m);
}

// greater
inline
bool
Double::
operator > ( const Double& d) const
{
    return ( d < *this);
}

// less equal
inline
bool
Double::
operator <= ( const Double& d) const
{
    return !( d < *this);
}

// greater equal
inline
bool
Double::
operator >= ( const Double& d) const
{
    return !( *this < d);
}


// arithmetic operations
// ---------------------

// unary minus
inline
Double
Double::
operator - ( ) const
{
    return Double( -m, e);
}

// addition
inline
Double
Double::
operator + ( const Double& d) const
{
    if ( e < d.e) return Double( m + ( d.m << ( d.e - e)), e);
    if ( e > d.e) return Double( ( m << ( e - d.e)) + d.m, d.e);
    return Double( m + d.m, e);
}

// subtraction
inline
Double
Double::
operator - ( const Double& d) const
{
    if ( e < d.e) return Double( m - ( d.m << ( d.e - e)), e);
    if ( e > d.e) return Double( ( m << ( e - d.e)) - d.m, d.e);
    return Double( m - d.m, e);
}

// multiplication
inline
Double
Double::
operator * ( const Double& d) const
{
    return Double( m * d.m, e + d.e);
}

// division (without remainder)
inline
Double
Double::
operator / ( const Double& d) const
{
    // only correct if division result is representable
    // as a Double and both operands are normalized
    if ( ! d.is_normal()) const_cast<Double&>( d).normalize();
    if ( !   is_normal()) const_cast<Double*>( this)->normalize();
    return Double( m / d.m, e - d.e);
}


// arithmetic assignment operations
// --------------------------------

// addition assignment
inline
Double&
Double::
operator += ( const Double& d)
{
    if ( e < d.e) {
	m += ( d.m << ( d.e - e));
	return *this; }
    if ( e > d.e) {
	m = ( m << ( e - d.e)) + d.m;
	e = d.e;
	return *this; }
    // e == d.e
    m += d.m;
    return *this;
}

// subtraction assignment
inline
Double&
Double::
operator -= ( const Double& d)
{
    if ( e < d.e) {
	m -= ( d.m << ( d.e - e));
	return *this; }
    if ( e > d.e) {
	m = ( m << ( e - d.e)) - d.m;
	e = d.e;
	return *this; }
    // e == d.e
    m -= d.m;
    return *this;
}

// multiplication assignment
inline
Double&
Double::
operator *= ( const Double& d)
{
    m *= d.m;
    e += d.e;
    return *this;
}

// division assignment
inline
Double&
Double::
operator /= ( const Double& d)
{
    // only correct if division result is representable
    // as a Double and both operands are normalized
    if ( ! d.is_normal()) const_cast<Double&>( d).normalize();
    if ( !   is_normal())                         normalize();
    m /= d.m;
    e -= d.e;
    return *this;
}


// shift operations
// ----------------

// left shift
inline
Double
Double::
operator << ( unsigned long i) const
{
    return Double( m, e+i);
}

// right shift
inline
Double
Double::
operator >> ( unsigned long i) const
{
    return Double( m, e-i);
}

    
// shift assignment operations
// ---------------------------

// left shift assignment
inline
Double&
Double::
operator <<= ( unsigned long i)
{
    e += i;
    return *this;
}

// right shift assignment
inline
Double&
Double::
operator >>= ( unsigned long i)
{
    e -= i;
    return *this;
}


// sign function
// -------------
inline
int
Double::
sign( ) const
{
    return m.sign();
}


// conversion functions
// --------------------

// conversion to double
inline
double
Double::
to_double( ) const
{
    return ldexp( m.to_double(), e);
}


// access functions to the internal representation
// -----------------------------------------------

// mantissa
inline
const Double::Mantissa&
Double::
mantissa( ) const
{
    return m;
}

// exponent
inline
const Double::Exponent&
Double::
exponent( ) const
{
    return e;
}


// I/O
// ---

// output operator
inline
std::ostream&
operator << ( std::ostream& out, const Double& d)
{
    out << "( " << d.mantissa() << ", " << d.exponent() << ')';
    return out;
}


}; // namespace GMP

#endif // GMP_DOUBLE_H

// ===== EOF ==================================================================
