// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/IO/Triangulation_geomview_ostream_3.h
// package       : Triangulation_3 (1.114)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/12/17 17:01:13 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_TRIANGULATION_GEOMVIEW_OSTREAM_3_H
#define CGAL_IO_TRIANGULATION_GEOMVIEW_OSTREAM_3_H

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/Triangulation_3.h>

// TODO :
// - Check the correctness when dimension < 3.
// - Use the stream color instead of built-in constant/random.
// - If interfaces were more similar, we could think of sharing 2d and 3d ?

CGAL_BEGIN_NAMESPACE

// This one is to show the edges of a 3D triangulation.
template < class GT, class TDS >
void
show_triangulation_edges(Geomview_stream &gv, const Triangulation_3<GT,TDS> &T)
{
  // Header.
  gv.set_ascii_mode();
  gv << "(geometry " << gv.get_new_id("triangulationedge")
     << " {appearance {}{ SKEL \n"
     << T.number_of_vertices() << T.number_of_finite_edges() << "\n";

  // Finite vertices coordinates.
  std::map<typename Triangulation_3<GT, TDS>::Vertex_handle, int> V;
  int inum = 0;
  for( typename Triangulation_3<GT, TDS>::Finite_vertices_iterator
      vit = T.finite_vertices_begin(); vit != T.finite_vertices_end(); ++vit) {
    V[&*vit] = inum++;
    gv << vit->point() << "\n";
  }
  
  // Finite edges indices.
  for( typename Triangulation_3<GT, TDS>::Finite_edges_iterator
	  eit = T.finite_edges_begin(); eit != T.finite_edges_end(); ++eit) {
      gv << 2
         << V[(*eit).first->vertex((*eit).second)]
         << V[(*eit).first->vertex((*eit).third)]
         << "\n"; // without color.
      // << 4 << drand48() << drand48() << drand48() << 1.0; // random color.
  }
}

// This one outputs the facets.
template < class GT, class TDS >
void
show_triangulation_faces(Geomview_stream &gv, const Triangulation_3<GT,TDS> &T)
{
  // Header.
  gv.set_binary_mode();
  gv << "(geometry " << gv.get_new_id("triangulation")
     << " {appearance {}{ OFF BINARY\n"
     << T.number_of_vertices() << T.number_of_finite_facets() << 0;

  // Finite vertices coordinates.
  std::map<typename Triangulation_3<GT, TDS>::Vertex_handle, int> V;
  int inum = 0;
  for( typename Triangulation_3<GT, TDS>::Finite_vertices_iterator
      vit = T.finite_vertices_begin(); vit != T.finite_vertices_end(); ++vit) {
    V[&*vit] = inum++;
    gv << vit->point();
  }
  
  // Finite facets indices.
  for( typename Triangulation_3<GT, TDS>::Finite_facets_iterator
	  fit = T.finite_facets_begin(); fit != T.finite_facets_end(); ++fit) {
      gv << 3;
      for (int i=0; i<4; i++)
          if (i != (*fit).second)
	      gv << V[(*fit).first->vertex(i)];
      gv << 0; // without color.
      // gv << 4 << drand48() << drand48() << drand48() << 1.0; // random color
  }
}

template < class GT, class TDS >
Geomview_stream&
operator<<( Geomview_stream &gv, const Triangulation_3<GT,TDS> &T)
{
    bool ascii_bak = gv.get_ascii_mode();
    bool raw_bak = gv.set_raw(true);

    if (gv.get_wired())
        show_triangulation_edges(gv, T);
    else
        show_triangulation_faces(gv, T);

    // Footer.
    gv << "}})";

    gv.set_raw(raw_bak);
    gv.set_ascii_mode(ascii_bak);
    return gv;
}

CGAL_END_NAMESPACE

#endif // CGAL_IO_TRIANGULATION_GEOMVIEW_OSTREAM_3_H
