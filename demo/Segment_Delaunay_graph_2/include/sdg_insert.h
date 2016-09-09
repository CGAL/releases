// Copyright (c) 2004,2005  INRIA Sophia-Antipolis (France) and
// Notre Dame University (U.S.A.).  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Segment_Delaunay_graph_2/demo/Segment_Delaunay_graph_2/include/sdg_insert.h $
// $Id: sdg_insert.h 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>

#ifndef SDG_INSERT_H
#define SDG_INSERT_H


template<class SDG, class Point>
typename SDG::Vertex_handle
insert_point(SDG& sdg, const Point& p)
{
  return sdg.insert(p);
}

template<class SDG, class Point>
typename SDG::Vertex_handle
insert_segment(SDG& sdg, const Point& p1, const Point& p2)
{
  return sdg.insert(p1, p2);
}

template<class SDG, class Point>
typename SDG::Vertex_handle
insert_segment(SDG& sdg, const Point& p1, const Point& p2,
	       typename SDG::Vertex_handle v)
{
  return sdg.insert(p1, p2, v);
}


template<class SDG, class Polygon>
typename SDG::Vertex_handle
insert_polygon(SDG& sdg, const Polygon& pgn)
{
  typename SDG::Vertex_handle v;
  int psize = pgn.size();
  for (int i = 0; i < psize; i++ ) {
    v = sdg.insert( pgn[i], pgn[(i+1)%psize] );
  }
  return v;
}



#endif // SDG_INSERT_H
