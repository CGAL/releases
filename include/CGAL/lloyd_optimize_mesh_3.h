// Copyright (c) 2009 INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Mesh_3/include/CGAL/lloyd_optimize_mesh_3.h $
// $Id: lloyd_optimize_mesh_3.h 53413 2009-12-15 13:19:38Z stayeb $
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : lloyd_optimize_mesh_3 function definition.
//******************************************************************************

#ifndef CGAL_LLOYD_OPTIMIZE_MESH_3_H
#define CGAL_LLOYD_OPTIMIZE_MESH_3_H

#include <CGAL/Mesh_3/global_parameters.h>
#include <CGAL/Mesh_3/Mesh_global_optimizer.h>
#include <CGAL/Mesh_3/Lloyd_move.h>
#include <CGAL/Mesh_3/Triangulation_sizing_field.h>
#include <CGAL/Mesh_3/Mesh_sizing_field.h>
#include <CGAL/Mesh_optimization_return_code.h>

namespace CGAL {

namespace parameters { namespace default_values {
  const double lloyd_freeze_ratio = 0.01;
  const double lloyd_convergence_ratio = 0.02;
} } // end namespace parameters::default_values


  
BOOST_PARAMETER_FUNCTION(
  (Mesh_optimization_return_code),
  lloyd_optimize_mesh_3,
  parameters::tag,
  (required (in_out(c3t3),*) (domain,*) )
  (optional
    (time_limit_, *, 0 )
    (max_iteration_number_, *, 0 )
    (convergence_, *, parameters::default_values::lloyd_convergence_ratio )
    (freeze_bound_, *, parameters::default_values::lloyd_freeze_ratio )
  )
)
{
  return lloyd_optimize_mesh_3_impl(c3t3, domain,
                                    time_limit_, max_iteration_number_,
                                    convergence_, freeze_bound_);
} 

  
  
template <typename C3T3, typename MeshDomain> 
Mesh_optimization_return_code
lloyd_optimize_mesh_3_impl(C3T3& c3t3,
                           const MeshDomain& domain,
                           const double time_limit,
                           std::size_t max_iteration_number,
                           const double convergence,
                           const double freeze_bound)
{
  typedef typename C3T3::Triangulation  Tr;
  typedef typename Tr::Geom_traits      Gt;
  
  typedef Mesh_3::Mesh_sizing_field<Tr>               Sizing;
  typedef typename Mesh_3::Lloyd_move<C3T3,Sizing>    Move;
  
  typedef typename
    Mesh_3::Mesh_global_optimizer<C3T3,MeshDomain,Move> Lloyd_optimizer;
  
  // Create optimizer
  Lloyd_optimizer opt (c3t3,domain,freeze_bound,convergence);
  
  // Set max time
  opt.set_time_limit(time_limit);
  
  // 1000 iteration max to avoid infinite loops
  if ( 0 == max_iteration_number )
    max_iteration_number = 1000;
  
  // Launch optimization
  return opt(max_iteration_number);
}
  
  
}  // end namespace CGAL


#endif // CGAL_LLOYD_OPTIMIZE_MESH_3_H
