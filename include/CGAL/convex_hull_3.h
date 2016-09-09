// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/convex_hull_3.h
// package       : Convex_hull_3 (2.6)
// source        : chull_traits.lw
// revision      : 2.3  
// revision_date : 01 Feb 2000
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CONVEX_HULL_3_H
#define CGAL_CONVEX_HULL_3_H

#include <CGAL/dd_geo/chull_traits_3.h>
#include <CGAL/dd_geo/chull_support_3.h>

CGAL_BEGIN_NAMESPACE
template <class InputIterator, class Polyhedron>
void
convex_hull_3( InputIterator first, InputIterator beyond, Polyhedron& P)
{
  typedef typename Polyhedron::Traits       PolyTraits;
  typedef typename Polyhedron::Halfedge_data_structure
                                            HDS;
  typedef typename PolyTraits::R            R;
  typedef typename PolyTraits::Point        Point;
  typedef chull_traits_3<R>                 ChullTraits;
#ifndef CGAL_CFG_NO_DEFAULT_TEMPLATE_ARGUMENTS
  typedef chull< ChullTraits >              ChullType;
#else
  typedef Plane_3<R>                        Plane;
  typedef chull< ChullTraits, Point, Plane> ChullType;
#endif // CGAL_CFG_NO_DEFAULT_TEMPLATE_ARGUMENTS

  ChullType CH(3);
  for ( ; first != beyond ; ++first)  CH.insert(*first);

#ifndef DDGEO_STL_ITERATORS
  GRAPH<Point,int> G; 
  d3_surface_map( CH, G);
  G.compute_faces();
  Build_polyhedron_from_GRAPH< HDS>  polyhedron_maker( G );
#else
  Build_polyhedron_from_chull< HDS, ChullType>  polyhedron_maker( CH);
#endif // DDGEO_STL_ITERATORS
  Polyhedron P_local;
  P_local.delegate( polyhedron_maker );
  P = P_local;
}
CGAL_END_NAMESPACE

#endif // CGAL_CONVEX_HULL_3_H
