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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Mesh_3/include/CGAL/Mesh_3/Mesher_3.h $
// $Id: Mesher_3.h 52705 2009-10-23 10:27:15Z stayeb $
//
//
// Author(s)     : Laurent Rineau, Stephane Tayeb
//
//******************************************************************************
// File Description :
// Implements a mesher_3 with two mesher levels : one for facets and one for
// tets.
//******************************************************************************

#ifndef CGAL_MESH_3_MESHER_3_H
#define CGAL_MESH_3_MESHER_3_H

#ifdef CGAL_MESH_3_VERBOSE
#define CGAL_MESHER_3_SCAN_VERBOSE
#endif


#include<CGAL/Mesh_3/Refine_facets_3.h>
#include<CGAL/Mesh_3/Refine_cells_3.h>
#include <CGAL/Mesh_3/Refine_tets_visitor.h>
#include <CGAL/Surface_mesher/Surface_mesher_visitor.h>

#include <CGAL/Timer.h>

#include <boost/format.hpp>

namespace CGAL {
  
namespace Mesh_3 {
    
    
// Class Mesher_3
//
template<class C3T3, class MeshCriteria, class MeshDomain>
class Mesher_3
{
public:
  // Self
  typedef Mesher_3<C3T3, MeshCriteria, MeshDomain> Self;
  
  typedef typename C3T3::Triangulation Triangulation;
  
  //-------------------------------------------------------
  // Mesher_levels
  //-------------------------------------------------------
  /// Facets mesher level
  typedef Mesh_3::Refine_facets_3<
      Triangulation,
      typename MeshCriteria::Facet_criteria,
      MeshDomain,
      C3T3,
      Null_mesher_level>                            Facets_level;
  
  /// Cells mesher level
  typedef Mesh_3::Refine_cells_3<
      Triangulation,
      typename MeshCriteria::Cell_criteria,
      MeshDomain,
      C3T3,
      Facets_level>                                 Cells_level;
  
  //-------------------------------------------------------
  // Visitors
  //-------------------------------------------------------
  /// Facets visitor : to update cells when refining surface
  typedef tets::Refine_facets_visitor<
      Triangulation,
      Cells_level,
      Null_mesh_visitor>                            Facets_visitor;
  
  /// Cells visitor : to update surface (restore restricted Delaunay)
  /// when refining cells
  typedef Surface_mesher::Visitor<
      Triangulation,
      Facets_level,
      Facets_visitor>                               Cells_visitor;
  
  /// Constructor
  Mesher_3(C3T3&               c3t3,
           const MeshDomain&   domain,
           const MeshCriteria& criteria);
  
  /// Destructor
  ~Mesher_3() { };
  
  /// Launch mesh refinement
  double refine_mesh();
  
private:
  /// Meshers
  Null_mesher_level null_mesher_;
  Facets_level facets_mesher_;
  Cells_level cells_mesher_;
  
  /// Visitors
  Null_mesh_visitor null_visitor_;
  Facets_visitor facets_visitor_;
  Cells_visitor cells_visitor_;
  
  /// The container of the resulting mesh
  C3T3& r_c3t3_;
  
private:
  // Disabled copy constructor
  Mesher_3(const Self& src);
  // Disabled assignment operator
  Self& operator=(const Self& src);
  
};  // end class Mesher_3
    
    
    
template<class C3T3, class MC, class MD>
Mesher_3<C3T3,MC,MD>::Mesher_3(C3T3& c3t3,
                               const MD& domain,
                               const MC& criteria)
: null_mesher_()
, facets_mesher_(c3t3.triangulation(),
                 criteria.facet_criteria(),
                 domain,
                 null_mesher_,
                 c3t3)
, cells_mesher_(c3t3.triangulation(),
                criteria.cell_criteria(),
                domain,
                facets_mesher_,
                c3t3)
, null_visitor_()
, facets_visitor_(&cells_mesher_, &null_visitor_)
, cells_visitor_(&facets_mesher_, &facets_visitor_)
, r_c3t3_(c3t3)
{
#ifdef CGAL_MESHER_3_SCAN_VERBOSE
  std::cerr << "Start scan... ";
#endif
  facets_mesher_.scan_triangulation();
  cells_mesher_.scan_triangulation();
#ifdef CGAL_MESHER_3_SCAN_VERBOSE
  std::cerr << "end scan. [";
  std::cerr << "Bad facets:" << facets_mesher_.size() << "] [";
  std::cerr << "Bad tets:" << cells_mesher_.size() << "]\n\n";
#endif
}



template<class C3T3, class MC, class MD>
double
Mesher_3<C3T3,MC,MD>::refine_mesh()
{
  CGAL::Timer timer;
  timer.start();
  
#ifndef CGAL_MESH_3_VERBOSE
  cells_mesher_.refine(cells_visitor_);
#else
  const Triangulation& r_tr = r_c3t3_.triangulation();
  int nbsteps = 0;
  
  std::cerr << "Refining...\n";
  std::cerr << "Legende of the following line: "
            << "(#vertices,#steps," << cells_mesher_.debug_info_header()
            << ")\n";
  std::cerr << "(" << r_tr.number_of_vertices() << ","
            << nbsteps << "," << cells_mesher_.debug_info() << ")";

  while ( ! cells_mesher_.is_algorithm_done() )
  {
    cells_mesher_.one_step(cells_visitor_);
    std::cerr
        << boost::format("\r             \r"
                     "(%1%,%2%,%3%) (%|4$.1f| vertices/s)")
        % r_tr.number_of_vertices()
        % nbsteps % cells_mesher_.debug_info()
        % (nbsteps / timer.time());
    ++nbsteps;
  }
  std::cerr << std::endl;
  std::cerr << "Total refining time: " << timer.time() << "s" << std::endl;
  std::cerr << std::endl;
#endif
  
  timer.stop();
  return timer.time();
}
    
}  // end namespace Mesh_3
  
}  // end namespace CGAL


#endif // CGAL_MESH_3_MESHER_3_H
