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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Skin_surface_3/include/CGAL/Marching_tetrahedra_observer_default_3.h $
// $Id: Marching_tetrahedra_observer_default_3.h 43854 2008-06-27 13:06:20Z nicokruithof $
// 
//
// Author(s)     : Nico Kruithof <Nico@cs.rug.nl>

#ifndef CGAL_MARCHING_TETRAHEDRA_OBSERVER_DEFAULT_3_H
#define CGAL_MARCHING_TETRAHEDRA_OBSERVER_DEFAULT_3_H

#include <CGAL/basic.h>

CGAL_BEGIN_NAMESPACE

template <class Vertex_iterator, 
	  class Cell_iterator,
	  class Polyhedron_3>
class Marching_tetrahedra_observer_default_3 {
public:
  typedef Polyhedron_3                        Polyhedron;
  
  typedef Cell_iterator                       T_Cell_iterator;
  typedef typename Polyhedron::Vertex_handle  Polyhedron_vertex_handle; 
  typedef typename Polyhedron::Facet_handle   Polyhedron_facet_handle; 

  Marching_tetrahedra_observer_default_3() {
  }

  Marching_tetrahedra_observer_default_3(
    const  Marching_tetrahedra_observer_default_3& traits2) {
  }

  void after_vertex_insertion(
    T_Cell_iterator,  int, int,
    Polyhedron_vertex_handle) {
  }
  
  void after_facet_insertion(
    T_Cell_iterator,
    Polyhedron_facet_handle) {
  }

};

CGAL_END_NAMESPACE

#endif // CGAL_MARCHING_TETRAHEDRA_OBSERVER_DEFAULT_3_H
