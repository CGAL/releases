// ============================================================================
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/int.h
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_INT_H
#define CGAL_INT_H

#ifndef CGAL_NUMBER_TYPE_TAGS_H
#include <CGAL/number_type_tags.h>
#endif // CGAL_NUMBER_TYPE_TAGS_H

// int

inline
double
CGAL_to_double(int i)
{ return (double)i; }

inline
CGAL_Number_tag
CGAL_number_type_tag(int)
{ return CGAL_Number_tag(); }

inline
bool
CGAL_is_finite(int)
{ return true; }

inline
bool
CGAL_is_valid(int)
{ return true; }

inline
CGAL_io_Operator
CGAL_io_tag(int)
{ return CGAL_io_Operator(); }

// long

inline
double
CGAL_to_double(long int i)
{ return (double)i; }

inline
CGAL_Number_tag
CGAL_number_type_tag(long int)
{ return CGAL_Number_tag(); }

inline
bool
CGAL_is_finite(long int)
{ return true; }

inline
bool
CGAL_is_valid(long int)
{ return true; }

inline
CGAL_io_Operator
CGAL_io_tag(long int)
{ return CGAL_io_Operator(); }

// short

inline
double
CGAL_to_double(short int i)
{ return (double)i; }

inline
CGAL_Number_tag
CGAL_number_type_tag(short int)
{ return CGAL_Number_tag(); }

inline
bool
CGAL_is_finite(short int)
{ return true; }

inline
bool
CGAL_is_valid(short int)
{ return true; }

inline
CGAL_io_Operator
CGAL_io_tag(short int)
{ return CGAL_io_Operator(); }

// long long

#ifdef CGAL_LONG_LONG

inline
double
CGAL_to_double(long long i)
{ return (double)i; }

inline
CGAL_Number_tag
CGAL_number_type_tag(long long)
{ return CGAL_Number_tag(); }

inline
bool
CGAL_is_finite(long long)
{ return true; }

inline
bool
CGAL_is_valid(long long)
{ return true; }
#endif // CGAL_LONG_LONG

#endif // CGAL_INT_H
