// Copyright (c) 2008  INRIA Sophia-Antipolis (France), ETH Zurich (Switzerland).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/AABB_tree/include/CGAL/AABB_drawing_traits.h $
// $Id: AABB_drawing_traits.h 51129 2009-08-07 18:57:08Z palliez $
//
//
// Author(s)     :  Camille Wormser, Pierre Alliez

#ifndef CGAL_AABB_DRAWING_TRAITS_H
#define CGAL_AABB_DRAWING_TRAITS_H

#include <CGAL/Bbox_3.h>

namespace CGAL {

template<typename Primitive, typename Node>
struct AABB_drawing_traits
{
  typedef CGAL::Bbox_3 Bbox;
  bool go_further() { return true; }

  bool intersection(const int&, const Primitive&)
  {
    return true;
  }

  bool do_intersect(const int&, // unused
                    const Node& node)
  {
    gl_draw(node.bbox());
    return true;
  }

  // draw bbox
  static void gl_draw(const Bbox& bb)
  {
    ::glBegin(GL_LINES);
    gl_draw_edge(bb.xmin(), bb.ymin(), bb.zmin(),
                 bb.xmax(), bb.ymin(), bb.zmin());
    gl_draw_edge(bb.xmin(), bb.ymin(), bb.zmin(),
                 bb.xmin(), bb.ymax(), bb.zmin());
    gl_draw_edge(bb.xmin(), bb.ymin(), bb.zmin(),
                 bb.xmin(), bb.ymin(), bb.zmax());

    gl_draw_edge(bb.xmax(), bb.ymin(), bb.zmin(),
                 bb.xmax(), bb.ymax(), bb.zmin());
    gl_draw_edge(bb.xmax(), bb.ymin(), bb.zmin(),
                 bb.xmax(), bb.ymin(), bb.zmax());

    gl_draw_edge(bb.xmin(), bb.ymax(), bb.zmin(),
                 bb.xmax(), bb.ymax(), bb.zmin());
    gl_draw_edge(bb.xmin(), bb.ymax(), bb.zmin(),
                 bb.xmin(), bb.ymax(), bb.zmax());

    gl_draw_edge(bb.xmin(), bb.ymin(), bb.zmax(),
                 bb.xmax(), bb.ymin(), bb.zmax());
    gl_draw_edge(bb.xmin(), bb.ymin(), bb.zmax(),
                 bb.xmin(), bb.ymax(), bb.zmax());

    gl_draw_edge(bb.xmax(), bb.ymax(), bb.zmax(),
                 bb.xmin(), bb.ymax(), bb.zmax());
    gl_draw_edge(bb.xmax(), bb.ymax(), bb.zmax(),
                 bb.xmax(), bb.ymin(), bb.zmax());
    gl_draw_edge(bb.xmax(), bb.ymax(), bb.zmax(),
                 bb.xmax(), bb.ymax(), bb.zmin());
    ::glEnd();
  }

  static void gl_draw_edge(double px, double py, double pz,
                           double qx, double qy, double qz)
  {
    ::glVertex3d(px,py,pz);
    ::glVertex3d(qx,qy,qz);
  }
}; // AABB_drawing_traits

} // end namespace CGAL

#endif // CGAL_AABB_DRAWING_TRAITS_H
