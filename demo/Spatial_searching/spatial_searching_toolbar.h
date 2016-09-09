// Copyright (c) 2002  Utrecht University (The Netherlands).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Spatial_searching/demo/Spatial_searching/spatial_searching_toolbar.h $
// $Id: spatial_searching_toolbar.h 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Radu Ursu


#ifndef MIN_SPATIAL_SEARCHING_TOOLBAR_H
#define MIN_SPATIAL_SEARCHING_TOOLBAR_H

#include "cgal_types.h"
#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_get_point.h>
#include <CGAL/IO/Qt_widget_get_iso_rectangle.h>
#include <CGAL/IO/Qt_widget_get_circle.h>
#include "Qt_widget_move_list_point.h"


#include <qobject.h>
#include <qtoolbutton.h>
#include <qtoolbar.h>
#include <qbuttongroup.h>
#include <qmainwindow.h>

class Tools_toolbar : public QToolBar
{
  Q_OBJECT
public:
  Tools_toolbar(CGAL::Qt_widget *w, QMainWindow *mw, std::vector<Point_2> *l1);
  ~Tools_toolbar(){};
private:
  QToolButton     *but[10];
  QButtonGroup    *button_group;
  CGAL::Qt_widget *widget;
  int             nr_of_buttons;

  CGAL::Qt_widget_get_point<R>         point_layer;
  CGAL::Qt_widget_get_iso_rectangle<R> iso_r_layer;
  CGAL::Qt_widget_get_circle<R>        circle_layer;
  Qt_widget_move_list_point<R>         edit_layer;
};//end class

#endif
