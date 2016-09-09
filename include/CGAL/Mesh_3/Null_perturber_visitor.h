// Copyright (c) 2010 INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_3/include/CGAL/Mesh_3/Null_perturber_visitor.h $
// $Id: Null_perturber_visitor.h 57256 2010-07-01 08:27:03Z stayeb $
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : 
//******************************************************************************

#ifndef CGAL_MESH_3_NULL_PERTURBER_VISITOR_H
#define CGAL_MESH_3_NULL_PERTURBER_VISITOR_H

#include <cstddef>

namespace CGAL {
namespace Mesh_3 {

template < typename C3T3 >
class Null_perturber_visitor
{
  typedef typename C3T3::Triangulation    Tr;
  typedef typename Tr::Geom_traits::FT    FT;
  
public:
  void bound_reached(const FT&) {}
  void end_of_perturbation_iteration(std::size_t) {}
};

} // end namespace Mesh_3
} // end namespace CGAL

#endif // CGAL_MESH_3_NULL_PERTURBER_VISITOR_H
