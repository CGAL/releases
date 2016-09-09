// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Fixed_precision_nt.h
// package       : Fixed_precision_nt (1.7)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1998/11/27 11:37:28 $
// author(s)     : Olivier Devillers
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_FIXED_PRECISION_NT_H
#define CGAL_FIXED_PRECISION_NT_H

#include <iostream.h>
#ifndef CGAL_TAGS_H
#include <CGAL/tags.h>
#endif // CGAL_TAGS_H
#include <CGAL/config.h>
#include <CGAL/enum.h>


// CGAL_Fixed_precision_nt implement 24 bits integers using float
// The user has to initiate a multiplicator factor to be applied to
// original data.

class CGAL_Fixed_precision_nt
{
private:
  float _value;          // value of the number
  
public:
  // constructors
  CGAL_Fixed_precision_nt();
  CGAL_Fixed_precision_nt(const CGAL_Fixed_precision_nt&);
  CGAL_Fixed_precision_nt(double);
  CGAL_Fixed_precision_nt(int);
  //access functions
  double to_double();
  float  to_float();
  // NT requirements
  CGAL_Fixed_precision_nt operator= (const CGAL_Fixed_precision_nt&);
  CGAL_Fixed_precision_nt operator+=(const CGAL_Fixed_precision_nt&);
  CGAL_Fixed_precision_nt operator-=(const CGAL_Fixed_precision_nt&);
  CGAL_Fixed_precision_nt operator*=(const CGAL_Fixed_precision_nt&);
  CGAL_Fixed_precision_nt operator/=(const CGAL_Fixed_precision_nt&);
  // access and parametrization of static members
  static bool init(float);
  static float unit_value();
  static float upper_bound();
  static void perturb_incircle();
  static void unperturb_incircle();
  static bool is_perturbed_incircle();
  static void perturb_insphere();
  static void unperturb_insphere();
  static bool is_perturbed_insphere();
};

// ======================================================================
//--------- access fonctions
// ======================================================================

inline double CGAL_Fixed_precision_nt::to_double() {return (double) _value;}

inline float  CGAL_Fixed_precision_nt::to_float()  {return _value;}

inline double CGAL_to_double(CGAL_Fixed_precision_nt f) {return f.to_double();}

// ======================================================================
//--------- geometric predicates
// ======================================================================


//template <>
CGAL_Orientation CGAL_orientationC2(
  CGAL_Fixed_precision_nt x0, CGAL_Fixed_precision_nt y0,
  CGAL_Fixed_precision_nt x1, CGAL_Fixed_precision_nt y1,
  CGAL_Fixed_precision_nt x2, CGAL_Fixed_precision_nt y2);

//template <>
CGAL_Oriented_side CGAL_side_of_oriented_circleC2 (
  CGAL_Fixed_precision_nt x0, CGAL_Fixed_precision_nt y0,
  CGAL_Fixed_precision_nt x1, CGAL_Fixed_precision_nt y1,
  CGAL_Fixed_precision_nt x2, CGAL_Fixed_precision_nt y2,
  CGAL_Fixed_precision_nt x3, CGAL_Fixed_precision_nt y3);

//template <>
CGAL_Orientation CGAL_orientationC3(  
  CGAL_Fixed_precision_nt x0, CGAL_Fixed_precision_nt y0,
  CGAL_Fixed_precision_nt z0,
  CGAL_Fixed_precision_nt x1, CGAL_Fixed_precision_nt y1,
  CGAL_Fixed_precision_nt z1,
  CGAL_Fixed_precision_nt x2, CGAL_Fixed_precision_nt y2,
  CGAL_Fixed_precision_nt z2,
  CGAL_Fixed_precision_nt x3, CGAL_Fixed_precision_nt y3,
  CGAL_Fixed_precision_nt z3);

//template <>
CGAL_Oriented_side CGAL_side_of_oriented_sphereC3 (
  CGAL_Fixed_precision_nt x0, CGAL_Fixed_precision_nt y0,
  CGAL_Fixed_precision_nt z0,
  CGAL_Fixed_precision_nt x1, CGAL_Fixed_precision_nt y1,
  CGAL_Fixed_precision_nt z1,
  CGAL_Fixed_precision_nt x2, CGAL_Fixed_precision_nt y2,
  CGAL_Fixed_precision_nt z2,
  CGAL_Fixed_precision_nt x3, CGAL_Fixed_precision_nt y3,
  CGAL_Fixed_precision_nt z3,
  CGAL_Fixed_precision_nt x4, CGAL_Fixed_precision_nt y4,
  CGAL_Fixed_precision_nt z4);



// ======================================================================
//--------- NT requirement
// ======================================================================

// only numbers between -B24 and B24 are authorized
// except overflow only valid fixed are constructed
bool CGAL_is_valid(CGAL_Fixed_precision_nt);
bool CGAL_is_finite(CGAL_Fixed_precision_nt);

bool  operator==(CGAL_Fixed_precision_nt a, CGAL_Fixed_precision_nt b);
bool  operator!=(CGAL_Fixed_precision_nt a, CGAL_Fixed_precision_nt b);
bool  operator<(CGAL_Fixed_precision_nt a, CGAL_Fixed_precision_nt b);
bool  operator>(CGAL_Fixed_precision_nt a, CGAL_Fixed_precision_nt b);
bool  operator<=(CGAL_Fixed_precision_nt a, CGAL_Fixed_precision_nt b);
bool  operator>=(CGAL_Fixed_precision_nt a, CGAL_Fixed_precision_nt b);

CGAL_Fixed_precision_nt  
operator+(CGAL_Fixed_precision_nt a, CGAL_Fixed_precision_nt b);
CGAL_Fixed_precision_nt  
operator-(CGAL_Fixed_precision_nt a, CGAL_Fixed_precision_nt b);
CGAL_Fixed_precision_nt  
operator*(CGAL_Fixed_precision_nt a, CGAL_Fixed_precision_nt b);
CGAL_Fixed_precision_nt  
operator-( CGAL_Fixed_precision_nt b);
CGAL_Fixed_precision_nt  
operator/(CGAL_Fixed_precision_nt a, CGAL_Fixed_precision_nt b);

// ======================================================================
//--------- non official NT requirement IO
// ======================================================================

ostream &operator<<(ostream &os, CGAL_Fixed_precision_nt a);
istream &operator>>(istream &is, CGAL_Fixed_precision_nt a);

// ======================================================================
//--------- non official mysterious NT requirement
// ======================================================================

inline CGAL_Number_tag CGAL_number_type_tag(CGAL_Fixed_precision_nt)
{ return CGAL_Number_tag(); }

inline CGAL_io_Operator CGAL_io_tag(CGAL_Fixed_precision_nt)
{ return CGAL_io_Operator(); }



#ifdef CGAL_INTERVAL_ARITHMETIC_H
#include <CGAL/Interval_arithmetic/IA_Fixed.h>
#endif // CGAL_INTERVAL_ARITHMETIC_H


#endif // CGAL_FIXED_PRECISION_NT_H.

