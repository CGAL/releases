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
// source        : Int.fw
// file          : include/CGAL/int.h
// package       : Number_types (2.1.5)
// revision      : 2.1.5
// revision_date : 09 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_INT_H
#define CGAL_INT_H

#ifndef CGAL_NUMBER_TYPE_TAGS_H
#include <CGAL/number_type_tags.h>
#endif // CGAL_NUMBER_TYPE_TAGS_H

// int

CGAL_BEGIN_NAMESPACE


inline
double
to_double(int i)
{ return (double)i; }

inline
Number_tag
number_type_tag(int)
{ return Number_tag(); }

inline
bool
is_finite(int)
{ return true; }

inline
bool
is_valid(int)
{ return true; }

inline
io_Operator
io_tag(int)
{ return io_Operator(); }

// long

inline
double
to_double(long int i)
{ return (double)i; }

inline
Number_tag
number_type_tag(long int)
{ return Number_tag(); }

inline
bool
is_finite(long int)
{ return true; }

inline
bool
is_valid(long int)
{ return true; }

inline
io_Operator
io_tag(long int)
{ return io_Operator(); }

// short

inline
double
to_double(short int i)
{ return (double)i; }

inline
Number_tag
number_type_tag(short int)
{ return Number_tag(); }

inline
bool
is_finite(short int)
{ return true; }

inline
bool
is_valid(short int)
{ return true; }

inline
io_Operator
io_tag(short int)
{ return io_Operator(); }

// long long

#ifdef LONG_LONG

inline
double
to_double(long long i)
{ return (double)i; }

inline
Number_tag
number_type_tag(long long)
{ return Number_tag(); }

inline
bool
is_finite(long long)
{ return true; }

inline
bool
is_valid(long long)
{ return true; }
#endif // LONG_LONG

// io_tags for unsigned types
inline
io_Operator
io_tag(unsigned char)
{ return io_Operator(); }

inline
io_Operator
io_tag(unsigned short)
{ return io_Operator(); }

inline
io_Operator
io_tag(unsigned int)
{ return io_Operator(); }

inline
io_Operator
io_tag(unsigned long)
{ return io_Operator(); }

CGAL_END_NAMESPACE


#endif // CGAL_INT_H
