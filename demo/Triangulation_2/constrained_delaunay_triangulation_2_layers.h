// Copyright (c) 1997-2002  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Triangulation_2/demo/Triangulation_2/constrained_delaunay_triangulation_2_layers.h $
// $Id: constrained_delaunay_triangulation_2_layers.h 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Radu Ursu


#ifndef CGAL_TRIANGULATION_2_CONSTRAINED_LAYERS_H
#define CGAL_TRIANGULATION_2_CONSTRAINED_LAYERS_H


#include <CGAL/IO/Qt_widget_layer.h>
#include <CGAL/IO/Qt_widget_Triangulation_2.h>

template <class T>
class Qt_layer_show_constraints : public CGAL::Qt_widget_layer {
public:
  typedef typename T::Edge            Edge;
  typedef typename T::Finite_edges_iterator
                                      Finite_edges_iterator;

  Qt_layer_show_constraints(T &t) : tr(t){};

  void draw()
  {
    Finite_edges_iterator it = tr.finite_edges_begin();
    *widget << CGAL::RED << CGAL::LineWidth(2);
    while(it != tr.finite_edges_end()) {
      if(tr.is_constrained(*it))
        *widget << tr.segment(it);
      ++it;
    }
  };
private:
  T	&tr;

};//end class

template <class T>
class Qt_layer_show_points : public CGAL::Qt_widget_layer {
public:
  typedef typename T::Point           Point;
  typedef typename T::Segment         Segment;
  typedef typename T::Vertex          Vertex;
  typedef typename T::Vertex_iterator	Vertex_iterator;

  Qt_layer_show_points(T &t) : tr(t){};

  void draw()
  {
    Vertex_iterator it = tr.vertices_begin(),
		beyond = tr.vertices_end();
    *widget << CGAL::GREEN << CGAL::PointSize (3)
		<< CGAL::PointStyle (CGAL::DISC);
    while(it != beyond) {
      *widget << (*it).point();
      ++it;
    }
  };
private:
  T	&tr;

};//end class

template <class T>
class Qt_layer_show_triangulation : public CGAL::Qt_widget_layer
{
public:

  Qt_layer_show_triangulation(T &t) : tr(t){};


  void draw()
  {
    *widget << CGAL::BLUE;
    *widget << tr;
  };

private:
  T &tr;
};//end class


#endif
