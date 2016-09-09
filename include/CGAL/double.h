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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : Double.fw
// file          : include/CGAL/double.h
// package       : Number_types (1.2.8)
// revision      : 1.2.8
// revision_date : 01 Jul 1998 
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef DOUBLECOMP_H
#define DOUBLECOMP_H 1

#ifndef CGAL_TAGS_H
#include <CGAL/tags.h>
#endif // CGAL_TAGS_H
#include <CGAL/config.h>
#ifndef CGAL_PROTECT_MATH_H
#include <math.h>
#define CGAL_PROTECT_MATH_H
#endif // CGAL_PROTECT_MATH_H

inline
double
CGAL_to_double(double d)
{ return d; }

/*
inline double CGAL_abs(double d)
{ return fabs(d); }
*/

/*  Is this used ? XXX
inline
double
CGAL_numerator(double d)
{ return d; }

inline
double
CGAL_denominator(double)
{ return 1.0; }
*/

inline
CGAL_Number_tag
CGAL_number_type_tag(double)
{ return CGAL_Number_tag(); }

extern
bool
CGAL_is_finite(double d);

extern
bool
CGAL_is_valid(double d);

inline
CGAL_io_Operator
CGAL_io_tag(double)
{ return CGAL_io_Operator(); }

#endif // CGAL_DOUBLE_H
