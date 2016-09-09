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
// file          : include/CGAL/Arr_2_default_dcel.h
// package       : Arrangement (2.52)
// author(s)     : Iddo Hanniel
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_ARR_2_DEFAULT_DCEL_H
#define CGAL_ARR_2_DEFAULT_DCEL_H

#ifndef CGAL_PM_DEFAULT_DCEL_H
#include <CGAL/Pm_default_dcel.h>
#endif

#ifndef ARR_2_BASES_H
#include <CGAL/Arr_2_bases.h>
#endif

CGAL_BEGIN_NAMESPACE


///////////////////////////////////////////////////////////////
//               DEFAULT DCEL
///////////////////////////////////////////////////////////////

template <class Traits>
class Arr_2_default_dcel
  : public Pm_dcel<
Arr_2_vertex_base<typename Traits::Point>,
Arr_2_halfedge_base<Arr_base_node<typename Traits::X_curve> >,
Arr_2_face_base
> 
{
public:  // CREATION
  
  Arr_2_default_dcel() {}
  
};



CGAL_END_NAMESPACE

#endif










