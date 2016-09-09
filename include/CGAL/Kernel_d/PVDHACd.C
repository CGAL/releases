// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// file          : include/CGAL/Kernel_d/PVDHACd.C
// package       : Kernel_d (0.9.68)
// chapter       : Basic
//
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2002/03/18 20:33:58 $
//
// author(s)     : Michael Seel
// coordinator   : Susan Hert
//
// implementation: implementation inclusion
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#if defined(CGAL_POINTCD_H) && defined(CGAL_VECTORCD_H) && \
    defined(CGAL_DIRECTIONCD_H) && defined(CGAL_HYPERPLANECD_H) && \
    defined(CGAL_AFF_TRANSFORMATIONCD_H) && !defined(CGAL_PVDHACD_C)
#define CGAL_PVDHACD_C

#include <CGAL/Kernel_d/PointCd.C>
#include <CGAL/Kernel_d/VectorCd.C>
#include <CGAL/Kernel_d/DirectionCd.C> 
#include <CGAL/Kernel_d/HyperplaneCd.C>
#include <CGAL/Kernel_d/Aff_transformationCd.C>

#endif //CGAL_PVDHACD_C


