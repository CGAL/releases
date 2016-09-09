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

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>
#include <CGAL/Filtered_kernel.h>

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_layer_show_mouse_coordinates.h>
#include "Qt_layer_show_triangulation.h"
#include "Qt_layer_show_constraineds.h"
#include "Qt_layer_show_points.h"


#include <qobject.h>
#include <qtoolbutton.h>
#include <qtoolbar.h>
#include <qstatusbar.h>
#include <qbuttongroup.h>

typedef double Coord_type;
typedef CGAL::Cartesian<Coord_type>  K11;
typedef CGAL::Filtered_kernel<K11>   Rp;

typedef CGAL::Triangulation_vertex_base_2<Rp>  Vb1;
typedef CGAL::Constrained_triangulation_face_base_2<Rp>
                                                Fb1;
typedef CGAL::Triangulation_data_structure_2<Vb1, Fb1>
                                                TDS1;
typedef CGAL::Exact_predicates_tag               Itag;

typedef CGAL::Constrained_Delaunay_triangulation_2<Rp, TDS1, Itag>
                                                CT1;
typedef CGAL::Constrained_triangulation_plus_2<CT1>      CDT1;
typedef CDT1::Constraint     Constraint;


namespace CGAL {

class Layers_toolbar : public QObject
{
	Q_OBJECT
public:
  Layers_toolbar(Qt_widget *w, QMainWindow *mw, CDT1 *t);
  ~Layers_toolbar()
  {
    delete showT;
    delete showP;
    delete showC;
    delete showMC;
  };
  QToolBar*	toolbar(){return maintoolbar;};

signals:
  void new_object(CGAL::Object);
	
private:
  QToolBar	*maintoolbar;
  QToolButton	*but[10];
  Qt_widget	*widget;
  QMainWindow	*window;
  //Delaunay	*dt;
  QButtonGroup  *button_group;

  int	  nr_of_buttons;
	
  CGAL::Qt_layer_show_triangulation < CDT1>  *showT;  
  CGAL::Qt_layer_show_points < CDT1 >        *showP;  
  CGAL::Qt_layer_show_constraineds < CDT1 >  *showC;  
  CGAL::Qt_layer_mouse_coordinates          *showMC;
};//end class

};//end namespace

#endif
