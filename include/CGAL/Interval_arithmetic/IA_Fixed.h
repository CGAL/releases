// ======================================================================
//
// Copyright (c) 1998,1999,2000 The CGAL Consortium

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
// file          : include/CGAL/Interval_arithmetic/IA_Fixed.h
// package       : Interval_arithmetic (4.58)
// revision      : $Revision: 2.19 $
// revision_date : $Date: 2000/09/01 16:43:21 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IA_FIXED_H
#define CGAL_IA_FIXED_H

CGAL_BEGIN_NAMESPACE

// Fixed is in fact a float => trivial conversion.

#if 0
inline
Interval_base
to_interval (const Fixed_precision_nt & z)
{
  return CGAL::to_double(z);
}
#endif

inline
Interval_nt_advanced
convert_from_to (const Interval_nt_advanced&, const Fixed_precision_nt & z)
{
    return CGAL::to_double(z);
}

template <>
struct converter<Interval_nt_advanced,Fixed_precision_nt>
{
    static inline Interval_nt_advanced do_it (const Fixed_precision_nt & z)
    { return CGAL::to_double(z); }
};

CGAL_END_NAMESPACE

#endif // CGAL_IA_FIXED_H
