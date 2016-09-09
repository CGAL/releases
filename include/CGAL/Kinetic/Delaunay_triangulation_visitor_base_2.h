// Copyright (c) 2005  Stanford University (USA).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Kinetic_data_structures/include/CGAL/Kinetic/Delaunay_triangulation_visitor_base_2.h $
// $Id: Delaunay_triangulation_visitor_base_2.h 36134 2007-02-09 00:39:39Z drussel $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_KINETIC_DELAUNAY_TRIANGULATION_2_WATCHER_BASE_H
#define CGAL_KINETIC_DELAUNAY_TRIANGULATION_2_WATCHER_BASE_H
#include <CGAL/Kinetic/basic.h>

CGAL_KINETIC_BEGIN_NAMESPACE

struct Delaunay_triangulation_visitor_base_2
{
    Delaunay_triangulation_visitor_base_2(){}
  
  template <class Point_key>
  void pre_insert_vertex(Point_key ) {
    }

    template <class Vertex_handle>
    void post_insert_vertex(Vertex_handle ) {
    }

    template <class Vertex_handle>
    void pre_remove_vertex(Vertex_handle ) {
    }


    template <class Point_key>
    void post_remove_vertex(Point_key ) {
    }

    template <class Vertex_handle>
    void change_vertex(Vertex_handle ) {
    }

    template <class Face_handle> 
    void create_face(Face_handle ) {
    }

    template <class Face_handle>
    void destroy_face(Face_handle ) {
    }


    template <class E>
    void pre_flip(E) {

    }
    template <class E>
    void post_flip(E) {

    }

  template <class P>
  bool filter_certificate(P a, P b, P c) const {
    return true;
  }
  template <class P>
  bool filter_certificate(P a, P b, P c, P d) const {
    return true;
  }
};

CGAL_KINETIC_END_NAMESPACE
#endif
