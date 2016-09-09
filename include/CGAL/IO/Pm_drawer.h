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
// file          : include/CGAL/IO/Pm_drawer.h
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

#ifndef CGAL_IO_PM_DRAWER_H
#define CGAL_IO_PM_DRAWER_H

#ifndef CGAL_PROTECT_IOSTREAM
#include <iostream>
#define CGAL_PROTECT_IOSTREAM
#endif

#ifndef CGAL_PROTECT_CSTDDEF
#include <cstddef>
#define CGAL_PROTECT_CSTDDEF
#endif

CGAL_BEGIN_NAMESPACE


template <class PM_, class Window_>
class Pm_drawer {
public:

  typedef   PM_                                  PM;
  typedef typename PM::Vertex_iterator           Vertex_iterator;
  typedef typename PM::Halfedge_iterator         Halfedge_iterator;
  typedef typename PM::Face_iterator             Face_iterator;
  typedef typename PM::Vertex_const_iterator     Vertex_const_iterator;
  typedef typename PM::Halfedge_const_iterator   Halfedge_const_iterator;
  typedef typename PM::Face_const_iterator       Face_const_iterator;

  typedef typename PM::Vertex_handle             Vertex_handle;
  typedef typename PM::Halfedge_handle           Halfedge_handle;
  typedef typename PM::Face_handle               Face_handle;
  typedef typename PM::Vertex_const_handle       Vertex_const_handle;
  typedef typename PM::Halfedge_const_handle     Halfedge_const_handle;  
  typedef typename PM::Face_const_handle         Face_const_handle;

  typedef Window_   Window;

  Pm_drawer   (Window& w)  { m_window = &w; }
  
  Window&  window()    { return *m_window; }
   
  
  //void draw_vertex_attributes(const Point& p) {}
  
  void draw_vertex(Vertex_handle v) {
    window() << v->point();
  }
  
  void draw_vertex(Vertex_const_handle v) {
    window() << v->point();
  }
  //void draw_halfedge_attributes(const Curve& cv) {}
  
  void draw_halfedge(Halfedge_handle h) {
    window() << h->curve();
  }
  
  void draw_halfedge(Halfedge_const_handle h) {
    window() << h->curve();
  }

  void draw_face(Face_handle f) {}
  
  void draw_face(Face_const_handle f) {}
  
  void draw_vertices(Vertex_iterator Vertices_begin,
                     Vertex_iterator Vertices_end)
  {
    for (Vertex_iterator v_iter = Vertices_begin; v_iter !=  Vertices_end;
         v_iter++)
      draw_vertex(v_iter);
  }

  void draw_vertices(Vertex_const_iterator Vertices_begin,
                     Vertex_const_iterator Vertices_end)
  {
    for (Vertex_const_iterator v_iter = Vertices_begin; v_iter != Vertices_end;
         v_iter++)
      draw_vertex(v_iter);
  }
   
  void draw_halfedges(Halfedge_iterator Halfedges_begin,
                      Halfedge_iterator Halfedges_end)
  {
    for (Halfedge_iterator h_iter = Halfedges_begin; h_iter != Halfedges_end;
         h_iter++)
      draw_halfedge(h_iter);
  }

  void draw_halfedges(Halfedge_const_iterator Halfedges_begin,
                      Halfedge_const_iterator Halfedges_end)
  {
    for (Halfedge_const_iterator h_iter = Halfedges_begin;
         h_iter != Halfedges_end; h_iter++)
      draw_halfedge(h_iter);
  }
  
  void draw_faces(Face_iterator Faces_begin, Face_iterator Faces_end) {
    for (Face_iterator f_iter = Faces_begin; f_iter != Faces_end; f_iter++)
      draw_face(f_iter);
  }

  void draw_faces(Face_const_iterator Faces_begin,
                  Face_const_iterator Faces_end)
  {
    for (Face_const_iterator f_iter = Faces_begin; f_iter != Faces_end;
         f_iter++)
      draw_face(f_iter);
  }

protected:
  Window         *m_window;
};

CGAL_END_NAMESPACE

#endif  // CGAL_IO_PM_DRAWER_H 
