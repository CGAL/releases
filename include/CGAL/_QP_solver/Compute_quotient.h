// ======================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

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
// file          : include/CGAL/_QP_solver/Compute_quotient.h
// package       : _QP_solver (0.9.3)
//
// revision      : 0.1
// revision_date : 2000/08/09
//
// author(s)     : Sven Sch�nherr
// coordinator   : ETH Z�rich (Bernd G�rtner)
//
// implementation: compute quotient function class
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_COMPUTE_QUOTIENT_H
#define CGAL_COMPUTE_QUOTIENT_H

#include <CGAL/Quotient.h>
#include <functional>

CGAL_BEGIN_NAMESPACE

template < class NT >
struct Compute_quotient {
    typedef  NT                         argument1_type;
    typedef  NT                         argument2_type;
    typedef  CGAL::Quotient<NT>         result_type;

    result_type  operator () ( const NT& numer, const NT& denom) const
        { return result_type( numer, denom); }
};

CGAL_END_NAMESPACE
  
#endif

// ===== EOF ==================================================================
