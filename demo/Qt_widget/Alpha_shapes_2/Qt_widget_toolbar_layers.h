// ============================================================================
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
// file          : include/CGAL/IO/Qt_widget_toolbar_layers.h
// package       : Qt_widget
// author(s)     : Radu Ursu
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// coordinator   : Laurent Rineau
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_QT_WIDGET_TOOLBAR_LAYERS_H
#define CGAL_QT_WIDGET_TOOLBAR_LAYERS_H

//CGAL
#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Alpha_shape_vertex_base_2.h>
#include <CGAL/Alpha_shape_face_base_2.h>
#include <CGAL/Alpha_shape_euclidean_traits_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Alpha_shape_face_base_2.h>
#include <CGAL/Alpha_shape_2.h>

//Qt_widget
#include <CGAL/IO/Qt_widget.h>

//Qt_widget_layer
#include "Qt_layer_show_triangulation.h"
#include "Qt_layer_show_voronoi.h"
#include "Qt_layer_show_points.h"
#include <CGAL/IO/Qt_layer_show_mouse_coordinates.h>

//Qt
#include <qobject.h>
#include <qtoolbutton.h>
#include <qtoolbar.h>
#include <qstatusbar.h>
#include <qbuttongroup.h>

typedef double Coord_type;
typedef CGAL::Cartesian<Coord_type>  Rp;
typedef CGAL::Alpha_shape_euclidean_traits_2<Rp> Gt;
typedef CGAL::Alpha_shape_vertex_base_2<Gt>	  Vb;
typedef CGAL::Triangulation_face_base_2<Gt>	  Df;
typedef CGAL::Alpha_shape_face_base_2<Gt, Df>	  Fb;
typedef CGAL::Triangulation_default_data_structure_2<Gt,Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<Gt,Tds> Delaunay;

namespace CGAL {

class Layers_toolbar : public QObject
{
	Q_OBJECT
public:
	Layers_toolbar(Qt_widget *w, QMainWindow *mw, Delaunay *t);

	QToolBar*	toolbar(){return maintoolbar;};


private:
	QToolBar      *maintoolbar;
	
  QToolButton   *but[10];
  QButtonGroup  *button_group;
	Qt_widget     *widget;
	QMainWindow   *window;
	//Delaunay      *dt;
	
	int			nr_of_buttons;
	

	CGAL::Qt_layer_show_triangulation < Delaunay >  *showT;
	CGAL::Qt_layer_show_voronoi < Delaunay >        *showV;
	CGAL::Qt_layer_show_points < Delaunay >         *showP;
	CGAL::Qt_layer_mouse_coordinates                *showMC;
};//end class

};//end namespace

#endif
