// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/IO/write_pm.h
// package       : Planar_map (5.113)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Eti Ezra
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_WRITE_PM_H
#define CGAL_IO_WRITE_PM_H 

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#include <iostream>

#ifndef CGAL_PLANAR_MAP_2_H
#include <CGAL/Planar_map_2.h>
#endif

#ifndef CGAL_INVERSE_INDEX_H
#include <CGAL/Inverse_index.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class PM, class Writer>
void write_pm(const PM & pm, Writer & writer, std::ostream &)
{
  // Print header. write #vertices, #halfedges, #faces.
  writer.write_title("Begin Planar Map");
  writer.write_comment("Number of vertices halfedges and faces in Planar map");
  writer.write_pm_vhf_sizes(pm.number_of_vertices(),
                            pm.number_of_halfedges(),
                            pm.number_of_faces());

  writer.write_comment("vertices", pm.number_of_vertices());
  writer.write_vertices(pm.vertices_begin(), pm.vertices_end());
  
  writer.write_comment("halfedges", pm.number_of_halfedges());
  writer.write_halfedges(pm.halfedges_begin(), pm.halfedges_end());

  writer.write_comment("faces", pm.number_of_faces());
  writer.write_faces(pm.faces_begin(), pm.faces_end());
  
  writer.write_title("End Planar Map");
  //writer.write_footer();
}

CGAL_END_NAMESPACE

#endif
