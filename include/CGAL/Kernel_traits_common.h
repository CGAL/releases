// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Kernel_traits_common.h
// package       : Kernel_basic (3.53)
// revision      : $Revision: 1.21 $
// revision_date : $Date: 2001/07/20 10:15:18 $
// author(s)     : Herve Bronnimann, Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// This file is intentionally not protected for re-inclusion.
// It's aimed at being included from within a kernel traits class, this
// way we share more code.

#define CGAL_Kernel_pred(X,Y,Z) typedef X Y; Y Z() const { return Y(); }
#define CGAL_Kernel_cons(X,Y,Z) CGAL_Kernel_pred(X,Y,Z)
#define CGAL_Kernel_pred2(W,X,Y,Z) typedef W,X Y; Y Z() const { return Y(); }
#define CGAL_Kernel_cons2(W,X,Y,Z) CGAL_Kernel_pred2(W,X,Y,Z)

#include <CGAL/Kernel/interface_macros.h>
