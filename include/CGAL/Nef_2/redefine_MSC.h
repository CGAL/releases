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
// file          : include/CGAL/Nef_2/redefine_MSC.h
// package       : Nef_2 (1.18)
// chapter       : Nef Polyhedra
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/12/28 12:55:20 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_REDEFINE_MSC_H
#define CGAL_REDEFINE_MSC_H
#ifdef _MSC_VER

#define RPolynomial_MSC RPMS
#define HalfEdgeDS_default_MSC HDSdMS
#define Nef_polyhedron_2_rep NP2R
#define Nef_polyhedron_2 NP2H
#define In_place_list_iterator Ipli
#define HalfedgeDS_in_place_list_vertex HDSv
#define Filtered_extended_homogeneous FEH
#define Extended_segment Eseg
#define Extended_point Epnt

#endif
#endif //CGAL_REDEFINE_MSC_H
