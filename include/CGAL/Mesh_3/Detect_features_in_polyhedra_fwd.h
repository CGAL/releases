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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_3/include/CGAL/Mesh_3/Detect_features_in_polyhedra_fwd.h $
// $Id: Detect_features_in_polyhedra_fwd.h 60688 2011-01-10 15:43:22Z lrineau $
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : 
//******************************************************************************

#ifndef CGAL_MESH_3_DETECT_FEATURES_IN_POLYHEDRA_FWD_H
#define CGAL_MESH_3_DETECT_FEATURES_IN_POLYHEDRA_FWD_H

namespace CGAL {
namespace Mesh_3 {
  
  template <typename Polyhedron>
  class Detect_features_in_polyhedra;

  template <typename Polyhedron>
  void detect_features(Polyhedron& p);
  
} // end namespace Mesh_3
  
} // end namespace CGAL

#endif // CGAL_MESH_3_DETECT_FEATURES_IN_POLYHEDRA_FWD_H
