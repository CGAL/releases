// Copyright (c) 2002  ETH Zurich (Switzerland).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Min_quadrilateral_2/demo/Min_quadrilateral_2/Qt_widget_toolbar_layers.h $
// $Id: Qt_widget_toolbar_layers.h 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Radu Ursu

#ifndef CGAL_QT_WIDGET_TOOLBAR_LAYERS_H
#define CGAL_QT_WIDGET_TOOLBAR_LAYERS_H

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/IO/Qt_widget.h>
#include <qmainwindow.h>
#include "min_quadrilateral_layers.h"

#include <qobject.h>
#include <qmainwindow.h>
#include <qtoolbutton.h>
#include <qtoolbar.h>
#include <qstatusbar.h>
#include <qbuttongroup.h>

typedef double Coord_type;
typedef CGAL::Cartesian<Coord_type>  Rp;
typedef Rp::Point_2   Point_2;

class Layers_toolbar : public QToolBar
{
  Q_OBJECT
public:
  Layers_toolbar(CGAL::Qt_widget *w, QMainWindow *mw,
		 std::list<Point_2> *l_of_p);
  ~Layers_toolbar()
  {
    delete showP;
    delete showPL;
    delete showLS;
    delete showR;
  };

private:
  QToolButton     *but[10];
  CGAL::Qt_widget *widget;
  QMainWindow     *window;
  QButtonGroup    *button_group;
  int             nr_of_buttons;

  Qt_layer_show_points<Rp>          *showP;
  Qt_layer_show_parallelogram<Rp>   *showPL;
  Qt_layer_show_strip<Rp>           *showLS;
  Qt_layer_show_rectangle<Rp>       *showR;
};//end class

#endif
