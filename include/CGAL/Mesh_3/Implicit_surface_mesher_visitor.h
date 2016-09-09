// Copyright (c) 2005-2006  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Mesh_3/include/CGAL/Mesh_3/Implicit_surface_mesher_visitor.h $
// $Id: Implicit_surface_mesher_visitor.h 43145 2008-05-12 20:29:42Z lrineau $
//
//
// Author(s)     : Laurent Rineau

#ifndef CGAL_MESH_3_IMPLICIT_SURFACE_MESHER_VISITOR_H
#define CGAL_MESH_3_IMPLICIT_SURFACE_MESHER_VISITOR_H

#include <CGAL/Mesh_2/Output_stream.h>

namespace CGAL {

  namespace Mesh_3 {

    template <
      typename Tr,
      typename Previous_level
      >
    class Visitor_for_surface {
      Previous_level* previous;

    public:
      typedef typename Tr::Vertex_handle Vertex_handle;

      typedef Previous_level Previous_visitor;

      Visitor_for_surface(Previous_visitor* p)
        : previous(p) {}

      template <typename E, typename P>
      void before_conflicts(E, P) const {}


      template <typename E, typename P, typename Z>
      void before_insertion(E, P, Z) const {}

      void after_insertion(const Vertex_handle& v)
      {
//         if(v->point().surface_index() == 0)
//         {
//           CGAL_MESHES_OUTPUT_STREAM << "?";
//           v->point().set_surface_index(1);
//         }
// 	CGAL_MESHES_OUTPUT_STREAM << v->point().surface_index();
      }

      template <typename E, typename P, typename Z>
      void after_no_insertion(E, P, Z) const {}

      Previous_visitor& previous_level()
      {
        return *previous;
      }

    }; // end class Visitor_for_surface

 }  // end namespace Mesh_3

}  // end namespace CGAL

#endif // CGAL_MESH_3_IMPLICIT_SURFACE_MESHER_VISITOR_H
