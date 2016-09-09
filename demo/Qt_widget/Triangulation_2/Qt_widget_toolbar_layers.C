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
// file          : src/Qt_widget_toolbar_layers.C
// package       : Qt_widget
// author(s)     : Ursu Radu
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// coordinator   : Laurent Rineau
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifdef CGAL_USE_QT

#include "Qt_widget_toolbar_layers.h"

// icons
#include <CGAL/IO/pixmaps/points.xpm>
#include <CGAL/IO/pixmaps/nearest_vertex.xpm>
#include <CGAL/IO/pixmaps/voronoi.xpm>
#include <CGAL/IO/pixmaps/triangulation.xpm>
#include <CGAL/IO/pixmaps/mouse_coord.xpm>


namespace CGAL {
  Layers_toolbar::Layers_toolbar(Qt_widget *w, QMainWindow *mw, Delaunay *t) : 
    dt(t), nr_of_buttons(0)
  {
    showT   = new Qt_layer_show_triangulation< Delaunay >(*t);
    showV   = new Qt_layer_show_voronoi< Delaunay >(*t);
    showP   = new Qt_layer_show_points< Delaunay >(*t);
    showNV  = new Qt_layer_nearest_vertex< Delaunay >(*t);
    showMC  = new Qt_layer_mouse_coordinates(*mw);

    //set the widget
    widget = w;
    window = mw;
    window->statusBar();

    widget->attach(showT);
    widget->attach(showV);
    widget->attach(showNV);
    widget->attach(showP);
    widget->attach(showMC);
    showNV->deactivate();
    

    maintoolbar = new QToolBar("tools", mw, QMainWindow::Top, TRUE, "Tools");
		
    but[0] = new QToolButton(maintoolbar, "triangulation");
    but[0]->setPixmap(QPixmap( (const char**)triangulation_xpm ));
    but[1] = new QToolButton(maintoolbar, "voronoi");
    but[1]->setPixmap(QPixmap( (const char**)voronoi_xpm ));
    but[2] = new QToolButton(maintoolbar, "nearest_vertex");
    but[2]->setPixmap(QPixmap( (const char**)nearest_vertex_xpm ));
    but[3] = new QToolButton(maintoolbar, "vertices");
    but[3]->setPixmap(QPixmap( (const char**)points_xpm ));
    but[4] = new QToolButton(maintoolbar, "mouse_coord");
    but[4]->setPixmap(QPixmap( (const char**)mouse_coord_xpm ));
		
    nr_of_buttons = 5;
	  button_group = new QButtonGroup(0, "nonexclusive");
    for(int i =0; i<nr_of_buttons; i++)
    {
      but[i]->setToggleButton(TRUE);
      but[i]->toggle();
      button_group->insert(but[i]);
    }
    but[2]->toggle();
    connect(button_group, SIGNAL(clicked(int)),
          widget, SLOT(redraw()));
    
    connect(but[0], SIGNAL(stateChanged(int)),
        showT, SLOT(stateChanged(int)));
    connect(but[1], SIGNAL(stateChanged(int)),
        showV, SLOT(stateChanged(int)));
    connect(but[2], SIGNAL(stateChanged(int)),
        showNV, SLOT(stateChanged(int)));
    connect(but[3], SIGNAL(stateChanged(int)),
        showP, SLOT(stateChanged(int)));
    connect(but[4], SIGNAL(stateChanged(int)),
        showMC, SLOT(stateChanged(int)));



  }
  
}//end namespace

#include "Qt_widget_toolbar_layers.moc"

#endif
