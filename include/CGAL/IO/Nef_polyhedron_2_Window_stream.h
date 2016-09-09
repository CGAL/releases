// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// file          : include/CGAL/IO/Nef_polyhedron_2_Window_stream.h
// package       : Nef_2 (1.18)
// chapter       : Nef Polyhedra
//
// source        : nef_2d/Nef_polyhedron_2.lw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/11/07 16:30:53 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// implementation: Nef polyhedra in the plane
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef NEF_POLYHEDRON_2_WINDOW_STREAM_H
#define NEF_POLYHEDRON_2_WINDOW_STREAM_H

#include <CGAL/Nef_polyhedron_2.h>
#include <CGAL/Nef_2/PM_visualizor.h>

CGAL_BEGIN_NAMESPACE

static long frame_default = 100;
static bool show_triangulation = false;

template <typename T>
CGAL::Window_stream& operator<<(CGAL::Window_stream& ws, 
const Nef_polyhedron_2<T>& P)
{
  typedef Nef_polyhedron_2<T> Polyhedron;
  typedef typename T::RT RT;
  typedef typename T::Standard_RT Standard_RT;
  typedef typename Polyhedron::Topological_explorer TExplorer;
  typedef typename Polyhedron::Point            Point;
  typedef typename Polyhedron::Line             Line;
  typedef CGAL::PM_BooleColor<TExplorer> BooleColor;
  typedef CGAL::PM_visualizor<TExplorer,T,BooleColor> Visualizor;

  TExplorer D = P.explorer();
  const T& E = Nef_polyhedron_2<T>::EK;

  Standard_RT frame_radius = frame_default;
  E.determine_frame_radius(D.points_begin(),D.points_end(),frame_radius);
  RT::set_R(frame_radius);
  Visualizor PMV(ws,D); PMV.draw_map();
  if (show_triangulation) {
    P.init_locator();
    Visualizor V(ws,P.locator().triangulation());
    V.draw_skeleton(CGAL::BLUE);
  }  

  return ws;
}


CGAL_END_NAMESPACE

#endif // NEF_POLYHEDRON_2_WINDOW_STREAM_H


