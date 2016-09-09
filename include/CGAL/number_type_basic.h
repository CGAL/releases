// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/number_type_basic.h
// package       : Number_types (4.57)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2002/03/28 15:10:07 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_NUMBER_TYPE_BASIC_H
#define CGAL_NUMBER_TYPE_BASIC_H

#define CGAL_PI 3.14159265358979323846

#define CGAL_NTS CGAL::NTS::

#if ((__GNUC__ == 2) && (__GNUC_MINOR__ == 95))
#include <cmath>
#endif

// CGAL uses std::min and std::max
// (see ISO C++ 25.3.7, page 562),
// if feasible

#include <algorithm>

CGAL_BEGIN_NAMESPACE

#if !defined CGAL_CFG_USING_USING_BUG && !defined CGAL_CFG_RETURN_TYPE_BUG

using std::min;
using std::max;

#else

template <class NT>
inline
NT
// const NT&
min(const NT& x, const NT& y)
{ return (y < x) ? y : x; }

template <class NT, class Comp>
inline
NT
// const NT&
min(const NT& x, const NT& y, const Comp& c)
{ return c(x, y) ? x : y; }

template <class NT>
inline
NT
// const NT&
max(const NT& x, const NT& y)
{ return (x < y) ? y : x; }

template <class NT, class Comp>
inline
NT
// const NT&
max(const NT& x, const NT& y, const Comp& c)
{ return c(x, y) ? y : x; }

#endif

CGAL_END_NAMESPACE

#include <CGAL/Number_type_traits.h>
#include <CGAL/number_utils.h>
#include <CGAL/number_utils_classes.h>
#include <CGAL/double.h>
#include <CGAL/float.h>
#include <CGAL/int.h>
#include <CGAL/Interval_arithmetic.h>

#endif // CGAL_NUMBER_TYPE_BASIC_H
