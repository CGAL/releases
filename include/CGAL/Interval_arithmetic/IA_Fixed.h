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
// file          : include/CGAL/Interval_arithmetic/IA_Fixed.h
// package       : Interval_arithmetic (4.15)
// revision      : $Revision: 2.9 $
// revision_date : $Date: 1999/04/13 15:48:16 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IA_FIXED_H
#define CGAL_IA_FIXED_H

CGAL_BEGIN_NAMESPACE

// The Fixed is in fact a float => trivial conversion.

inline
Interval_nt_advanced
convert_from_to (const Interval_nt_advanced&, const Fixed_precision_nt & z)
{
    return to_double(z);
}

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
struct converter<Interval_nt_advanced,Fixed_precision_nt>
{
    static inline Interval_nt_advanced do_it (const Fixed_precision_nt & z)
    { return to_double(z); }
};
#endif // CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION


CGAL_END_NAMESPACE

#endif	 // CGAL_IA_FIXED_H
