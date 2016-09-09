// Copyright (c) 2005 Rijksuniversiteit Groningen (Netherlands)
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Skin_surface_3/include/CGAL/make_skin_surface_mesh_3.h $
// $Id: make_skin_surface_mesh_3.h 36161 2007-02-09 21:25:43Z nicokruithof $
// 
//
// Author(s)     : Nico Kruithof <Nico@cs.rug.nl>

#ifndef CGAL_MAKE_SKIN_SURFACE_MESH_3_H
#define CGAL_MAKE_SKIN_SURFACE_MESH_3_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Skin_surface_traits_3.h>
#include <CGAL/Skin_surface_3.h>
#include <CGAL/mesh_skin_surface_3.h>
#include <CGAL/subdivide_skin_surface_mesh_3.h>

#include <CGAL/make_union_of_balls_3.h>

CGAL_BEGIN_NAMESPACE

template <class WP_iterator,
	  class Polyhedron_3>
void make_skin_surface_mesh_3(Polyhedron_3 &p, 
			      WP_iterator begin, WP_iterator end, 
			      double shrink_factor=.5, 
			      int nSubdivisions=0, 
			      bool grow_balls=true)
{
  if (shrink_factor == 1) {
    make_union_of_balls_mesh_3(p,begin,end,nSubdivisions);
  }

  typedef typename WP_iterator::value_type              Weighted_point;
  typedef typename Weighted_point::Point                Point;
  typedef typename Point::R                             K;
  
//   typedef Exact_predicates_inexact_constructions_kernel K;
  typedef Skin_surface_traits_3<K>                      Traits;
  typedef Skin_surface_3<Traits>                        Skin_surface;
  
  Skin_surface skin_surface(begin, end, shrink_factor, grow_balls);

  mesh_skin_surface_3(skin_surface, p);

  subdivide_skin_surface_mesh_3(skin_surface, p, nSubdivisions);
}



CGAL_END_NAMESPACE

#endif // CGAL_MAKE_SKIN_SURFACE_MESH_3_H
