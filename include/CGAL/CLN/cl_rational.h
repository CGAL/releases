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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/CLN/cl_rational.h
// package       : CLN (2.0)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2000/06/25 18:42:00 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CL_RATIONAL_H
#define CGAL_CL_RATIONAL_H

#include <CGAL/CLN/common.h>
#include <cl_rational.h>
#include <cl_rational_io.h>

CGAL_BEGIN_NAMESPACE

// Requirements.

inline double	to_double	(const cl_RA &I) { return cl_double_approx(I); }

// Specialized utilities.

namespace NTS {

inline bool is_negative		(const cl_RA &I) { return minusp(I); } 
inline bool is_positive		(const cl_RA &I) { return plusp(I); }
inline bool is_zero		(const cl_RA &I) { return zerop(I); }
inline Comparison_result compare (const cl_RA &I, const cl_RA &J)
{ return Comparison_result(cl_compare(I,J)); }

} // namespace NTS

CGAL_END_NAMESPACE

// #ifdef CGAL_INTERVAL_ARITHMETIC_H
// #include <CGAL/Interval_arithmetic/IA_cl_rational.h>
// #endif

#endif // CGAL_CL_RATIONAL_H
