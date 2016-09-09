// Copyright (c) 2006  GeometryFactory (France). All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Surface_mesh_simplification/include/CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Edge_length_cost.h $
// $Id: Edge_length_cost.h 50078 2009-06-25 15:12:52Z fcacciola $
//
// Author(s)     : Fernando Cacciola <fernando.cacciola@geometryfactory.com>
//
#ifndef CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_EDGE_LENGHT_COST_H
#define CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_EDGE_LENGHT_COST_H

#include <CGAL/Surface_mesh_simplification/Detail/Common.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Edge_profile.h>

CGAL_BEGIN_NAMESPACE

namespace Surface_mesh_simplification
{

//
// Edge-length cost: the squared length of the collapsing edge
//
template<class ECM_>
class Edge_length_cost
{
  
public:
    
  typedef ECM_ ECM ;
  
  typedef Edge_profile<ECM> Profile ;
  
  typedef typename halfedge_graph_traits<ECM>::Point Point ;
  
  typedef typename Kernel_traits<Point>::Kernel Kernel ;

  typedef typename Kernel::FT FT ;
  
  typedef optional<FT> result_type ;
  
public:

  Edge_length_cost() {}
  
  result_type operator()( Profile const& aProfile, optional<Point> const& /*aPlacement*/ ) const
  {
    return result_type(squared_distance(aProfile.p0(),aProfile.p1()));
  }
  
};


} // namespace Surface_mesh_simplification


CGAL_END_NAMESPACE

#endif // CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_EDGE_LENGHT_COST_H
// EOF //
 
