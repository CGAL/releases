// Copyright (c) 2005-2008 Fernando Luis Cacciola Carballal. All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Straight_skeleton_2/include/CGAL/Straight_skeleton_items_2.h $
// $Id: Straight_skeleton_items_2.h 41533 2008-01-11 15:46:07Z fcacciola $
// 
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_STRAIGHT_SKELETON_ITEMS_2_H
#define CGAL_STRAIGHT_SKELETON_ITEMS_2_H 1

#include <CGAL/Straight_skeleton_vertex_base_2.h>
#include <CGAL/Straight_skeleton_halfedge_base_2.h>
#include <CGAL/Straight_skeleton_face_base_2.h>

CGAL_BEGIN_NAMESPACE

class Straight_skeleton_items_2
{
public:

  template<class Refs, class Traits>
  struct Vertex_wrapper
  {
    typedef typename Traits::RT RT ;
    typedef typename Traits::Point_2 Point ;
    typedef Straight_skeleton_vertex_base_2 < Refs, Point, RT > Vertex; 
  };
  
  template<class Refs, class Traits> 
  struct Halfedge_wrapper
  {
    typedef typename Traits::Segment_2 Segment ;
    typedef Straight_skeleton_halfedge_base_2 < Refs, Segment > Halfedge; 
  };
  
  template<class Refs, class Traits> 
  struct Face_wrapper 
  {
    typedef Straight_skeleton_face_base_2 < Refs > Face; 
  } ;
};

CGAL_END_NAMESPACE

#endif // CGAL_STRAIGHT_SKELETON_ITEMS_2_H //
// EOF //
 
