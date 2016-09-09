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
// source        : Gnu_Integer.fw
// file          : include/CGAL/gnu_integer.h
// package       : Number_types (1.2.8)
// revision      : 1.2.8
// revision_date : 01 Jul 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_GNU_INTEGER_H
#define CGAL_GNU_INTEGER_H

#ifndef CGAL_PROTECT_INTEGER_H
#include <Integer.h>
#define CGAL_PROTECT_INTEGER_H
#endif // CGAL_PROTECT_INTEGER_H

inline
bool
CGAL_is_finite(const Integer &)
{ return true; }

inline
bool
CGAL_is_valid(const Integer &)
{ return true; }

inline
double
CGAL_to_double(const Integer & i)
{ return i.as_double(); }

inline
CGAL_Number_tag
CGAL_number_type_tag(const Integer& )
{ return CGAL_Number_tag(); }

inline
CGAL_io_Operator
CGAL_io_tag(const Integer& )
{ return CGAL_io_Operator(); }
#endif // CGAL_GNU_INTEGER_H
