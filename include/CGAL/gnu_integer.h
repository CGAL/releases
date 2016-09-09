// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.1
// release_date  : 2000, January 11
// 
// source        : Gnu_Integer.fw
// file          : include/CGAL/gnu_integer.h
// package       : Number_types (2.7.1)
// revision      : 2.7.1
// revision_date : 04 Dec 1999 
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

CGAL_BEGIN_NAMESPACE

inline
bool
is_finite(const Integer &)
{ return true; }

inline
bool
is_valid(const Integer &)
{ return true; }

inline
double
to_double(const Integer & i)
{ return i.as_double(); }

inline
Number_tag
number_type_tag(const Integer& )
{ return Number_tag(); }

inline
io_Operator
io_tag(const Integer& )
{ return io_Operator(); }

CGAL_END_NAMESPACE

#endif // CGAL_GNU_INTEGER_H
