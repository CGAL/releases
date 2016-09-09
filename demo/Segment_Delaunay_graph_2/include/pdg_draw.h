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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Segment_Delaunay_graph_2/demo/Segment_Delaunay_graph_2/include/pdg_draw.h $
// $Id: pdg_draw.h 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>


#ifndef PDG_DRAW_H
#define PDG_DRAW_H



template<class T, class Widget>
void draw_diagram(Widget& widget, const T& sdg)
{
  widget << CGAL::BLUE;
#if !defined (__POWERPC__)
  widget << CGAL::PointSize(3);
  widget << CGAL::LineWidth(3);
#endif

  typename T::Finite_edges_iterator eit = sdg.finite_edges_begin();
  for (; eit != sdg.finite_edges_end(); ++eit) {
    if ( eit->first->vertex( sdg.cw(eit->second) )->info() !=
	 eit->first->vertex( sdg.ccw(eit->second) )->info() ) {
      sdg.draw_dual_edge(*eit, widget);
    }
#if 0
    Site_2 p = eit->first->vertex(  cw(eit->second) )->site();
    Site_2 q = eit->first->vertex( ccw(eit->second) )->site();

    bool is_endpoint_of_seg =
      ( p.is_segment() && q.is_point() &&
	is_endpoint_of_segment(q, p) ) ||
      ( p.is_point() && q.is_segment() &&
	is_endpoint_of_segment(p, q) );

    if ( !is_endpoint_of_seg ) {
      sdg.draw_dual_edge(*eit, widget);
    }
#endif
  }
}




#endif // PDG_DRAW_H
