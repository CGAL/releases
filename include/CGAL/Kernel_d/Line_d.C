// ======================================================================
//
// Copyright (c) 2000,2001 The CGAL Consortium

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
// file          : include/CGAL/Kernel_d/Line_d.C
// package       : Kernel_d (0.9.68)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2002/03/18 20:33:56 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_LINE_D_C
#define CGAL_LINE_D_C
CGAL_BEGIN_NAMESPACE

template <class R> 
Line_d<R> Segment_d<R>::supporting_line() const
{ CGAL_assertion_msg((!is_degenerate()), 
  "Segment_d::supporting_line(): degenerate segment cannot be converted.");
  return Line_d<R>(Base(*this)); 
} 

template <class R>
Line_d<R> Ray_d<R>::supporting_line() const
{ return Line_d<R>(Base(*this)); } 

CGAL_END_NAMESPACE
#endif //CGAL_LINE_D_C

