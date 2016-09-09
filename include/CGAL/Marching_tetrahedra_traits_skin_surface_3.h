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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Skin_surface_3/include/CGAL/Marching_tetrahedra_traits_skin_surface_3.h $
// $Id: Marching_tetrahedra_traits_skin_surface_3.h 43854 2008-06-27 13:06:20Z nicokruithof $
// 
//
// Author(s)     : Nico Kruithof <Nico@cs.rug.nl>

#ifndef CGAL_MARCHING_TETRAHEDRA_TRAITS_SKIN_SURFACE_3_H
#define CGAL_MARCHING_TETRAHEDRA_TRAITS_SKIN_SURFACE_3_H

#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Modifier_base.h>
#include <CGAL/Cartesian_converter.h>

CGAL_BEGIN_NAMESPACE 

/// NGHK: Is the converter needed or do we just use the Cartesian_converter
template <class SkinSurface_3,
	  class Vertex_iterator, 
	  class Cell_iterator,
	  class HalfedgeDS>
class Marching_tetrahedra_traits_skin_surface_3 {
public:
  typedef HalfedgeDS                                   Halfedge_DS;

  typedef typename HalfedgeDS::Traits::Point_3         HDS_point;
  typedef typename HDS_point::R::RT                    HDS_RT;

  typedef typename SkinSurface_3::Bare_point           Skin_point;

  Marching_tetrahedra_traits_skin_surface_3(const SkinSurface_3 &ss_3) 
    : ss_3(ss_3) {}

  // These two functions are required by the marching tetrahedra algorithm
  Sign sign(const Cell_iterator ch, int i) const {
    return ss_3.sign(ch->vertex(i));
  }
  HDS_point intersection(Cell_iterator const ch, int i, int j) const {
    // Precondition: ch is not an infinite cell: their surface is not set
    Skin_point p;
    ss_3.intersect(ch, i, j, p);
    
    return 
      Cartesian_converter<typename Skin_point::R, typename HDS_point::R>()(p);
  }

  const SkinSurface_3 &ss_3;
};

CGAL_END_NAMESPACE 

#endif // CGAL_MARCHING_TETRAHEDRA_TRAITS_SKIN_SURFACE_3_H
