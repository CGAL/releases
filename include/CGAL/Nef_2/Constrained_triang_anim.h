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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Nef_2/Constrained_triang_anim.h
// package       : Nef_2 (0.9.25)
// chapter       : Nef Polyhedra
//
// source        : nef_2d/Constrained_triang.lw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/07/16 12:47:20 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// implementation: Constrained triangulation of a plane map
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_PM_CONSTR_TRIANG_ANIM_H
#define CGAL_PM_CONSTR_TRIANG_ANIM_H

#include <CGAL/Nef_2/PM_visualizor.h>

CGAL_BEGIN_NAMESPACE

template <class GT>
class Constrained_triang_anim {

  CGAL::Window_stream _W;
public:
  typedef CGAL::Window_stream   VDEVICE;
  typedef typename GT::GEOMETRY GEOM;
  typedef typename GT::Base     PMDEC;
  typedef typename PMDEC::Point Point;

  Constrained_triang_anim() : _W(400,400) 
  { _W.set_show_coordinates(true); _W.init(-120,120,-120,5); _W.display(); }
  VDEVICE& device() { return _W; } 

void post_init_animation(GT& gpst)
{ 
  PM_visualizor<PMDEC,GEOM> V(_W,gpst);
  V.point(V.target(gpst.e_search)) = Point(-120,0);
  // to draw we have to embed the virtual search vertex
  V.draw_skeleton(CGAL::BLUE);
  _W.read_mouse();
}

void pre_event_animation(GT& gpst)
{ }

void post_event_animation(GT& gpst)
{ PM_visualizor<PMDEC,GEOM> V(_W,gpst);
  V.draw_ending_bundle(gpst.event,CGAL::GREEN);
  _W.read_mouse();
}

void post_completion_animation(GT& gpst)
{ _W.clear();
  PM_visualizor<PMDEC,GEOM> V(_W,gpst);
  V.draw_skeleton(CGAL::BLACK);
  _W.read_mouse(); }

};

CGAL_END_NAMESPACE
#endif // CGAL_PM_CONSTR_TRIANG_ANIM_H

