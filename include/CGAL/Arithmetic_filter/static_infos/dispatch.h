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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.3
// release_date  : 2001, August 13
// 
// file          : include/CGAL/Arithmetic_filter/static_infos/dispatch.h
// package       : Interval_arithmetic (4.114)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/10/07 12:50:59 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ARITHMETIC_FILTER_STATIC_INFOS_DISPATCH_H
#define CGAL_ARITHMETIC_FILTER_STATIC_INFOS_DISPATCH_H

#include <CGAL/Arithmetic_filter/static_infos/predicates/builtin.h>
#include <CGAL/Arithmetic_filter/static_infos/predicates/sign_of_determinant.h>

#include <CGAL/Arithmetic_filter/static_infos/predicates/kernel_ftC2.h>
#include <CGAL/Arithmetic_filter/static_infos/predicates/kernel_ftC3.h>
// #include <CGAL/Arithmetic_filter/static_infos/predicates_on_rtH2.h>
// #include <CGAL/Arithmetic_filter/static_infos/predicates_on_rtH3.h>

#include <CGAL/Arithmetic_filter/static_infos/predicates/Regular_triangulation_ftC2.h>
#include <CGAL/Arithmetic_filter/static_infos/predicates/Regular_triangulation_ftC3.h>
// #include <CGAL/Arithmetic_filter/static_infos/predicates/Regular_triangulation_rtH2.h>
// #include <CGAL/Arithmetic_filter/static_infos/predicates/Regular_triangulation_rtH3.h>

#endif // CGAL_ARITHMETIC_FILTER_STATIC_INFOS_DISPATCH_H
