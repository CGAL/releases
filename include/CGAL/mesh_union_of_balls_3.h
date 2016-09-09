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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Skin_surface_3/include/CGAL/mesh_union_of_balls_3.h $
// $Id: mesh_union_of_balls_3.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Nico Kruithof <Nico@cs.rug.nl>

#ifndef CGAL_MESH_UNION_OF_BALLS_3_H
#define CGAL_MESH_UNION_OF_BALLS_3_H

#include <CGAL/mesh_skin_surface_3.h>

namespace CGAL {

template <class UnionOfBalls_3, class Polyhedron>
void mesh_union_of_balls_3(UnionOfBalls_3 const &union_of_balls, Polyhedron &p)
{
  union_of_balls.mesh_surface_3(p);
}

} //namespace CGAL

#endif // CGAL_MESH_UNION_OF_BALLS_3_H
