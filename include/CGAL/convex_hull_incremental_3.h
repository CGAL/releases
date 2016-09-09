// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/convex_hull_incremental_3.h
// package       : Convex_hull_3 (2.41)
// revision      : $Revision: 1.3 $ 
// revision_date : $Date: 2002/05/06 07:37:30 $
// author(s)     : Stefan Schirra
//               : Michael Seel
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CONVEX_HULL_INCREMENTAL_3_H
#define CGAL_CONVEX_HULL_INCREMENTAL_3_H

#include <CGAL/Convex_hull_d.h>
#include <CGAL/Convex_hull_d_traits_3.h>
#include <CGAL/Convex_hull_d_to_polyhedron_3.h>

CGAL_BEGIN_NAMESPACE
template <class InputIterator, class Polyhedron>
void
convex_hull_incremental_3(InputIterator first, InputIterator beyond, 
                                     Polyhedron& P, 
                                     bool test_correctness = false)
{
  typedef typename Polyhedron::Traits       PolyTraits;
  typedef typename PolyTraits::Kernel         K;
  typedef Convex_hull_d_traits_3<K>           ChullTraits;
  typedef Convex_hull_d< ChullTraits >        ChullType;

  ChullType CH(3);
  for ( ; first != beyond ; ++first)  CH.insert(*first);
  if ( test_correctness ) CGAL_assertion(CH.is_valid());
  CGAL::convex_hull_d_to_polyhedron_3(CH,P);
}
CGAL_END_NAMESPACE

#endif // CGAL_CONVEX_HULL_INCREMENTAL_3_H
