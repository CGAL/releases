// Copyright (c) 2006-2009 INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Mesh_3/include/CGAL/Mesh_triangulation_3.h $
// $Id: Mesh_triangulation_3.h 52705 2009-10-23 10:27:15Z stayeb $
//
//
// Author(s)     : Laurent Rineau, Stephane Tayeb


#ifndef CGAL_MESH_TRIANGULATION_3_H
#define CGAL_MESH_TRIANGULATION_3_H

#include <CGAL/Kernel_traits.h>

#include <CGAL/Regular_triangulation_3.h>
#include <CGAL/Regular_triangulation_filtered_traits_3.h>
#include <CGAL/Regular_triangulation_euclidean_traits_3.h>
#include <CGAL/Mesh_3/Robust_weighted_circumcenter_filtered_traits_3.h>

#include <CGAL/Mesh_vertex_base_3.h>
#include <CGAL/Mesh_cell_base_3.h>

namespace CGAL {
  
  namespace details {
    
    template<typename K>
    struct Mesh_geom_traits_generator
    {
    private:
      typedef Robust_weighted_circumcenter_filtered_traits_3<K>
        Geom_traits;
      
    public:
      typedef Geom_traits type;
      typedef type Type;
    };  // end struct Mesh_geom_traits_generator
    
  }  // end namespace details
  
  
// Struct Mesh_triangulation_3
//
template<class MD, class K=typename Kernel_traits<MD>::Kernel>
struct Mesh_triangulation_3
  {
private:
  typedef typename details::Mesh_geom_traits_generator<K>::type Geom_traits;
  typedef Mesh_vertex_base_3<Geom_traits, MD>                   Vertex_base;
  typedef Mesh_cell_base_3<Geom_traits, MD>                     Cell_base;
  typedef Triangulation_data_structure_3<Vertex_base,Cell_base> Tds;
  typedef Regular_triangulation_3<Geom_traits, Tds>             Triangulation;
  
public:
  typedef Triangulation type;
  typedef type Type;
};  // end struct Mesh_triangulation_3



}  // end namespace CGAL

#endif // CGAL_MESH_TRIANGULATION_3_H

