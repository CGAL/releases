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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Triangulation_2/demo/Triangulation_2/constrained_delaunay_triangulation_2_toolbar.h $
// $Id: constrained_delaunay_triangulation_2_toolbar.h 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Radu Ursu


#ifndef CGAL_QT_WIDGET_TOOLBAR_H
#define CGAL_QT_WIDGET_TOOLBAR_H

#include "constrained_cgal_types.h"
// TODO: check if some of those includes shouldn't be in the .C file
#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_get_segment.h>
#include <CGAL/IO/Qt_widget_get_point.h>
#include <CGAL/IO/Qt_widget_get_polygon.h>


#include <qobject.h>
#include <qtoolbutton.h>
#include <qtoolbar.h>
#include <qmainwindow.h>
#include <qbuttongroup.h>

class Tools_toolbar : public QToolBar
{
  Q_OBJECT
public:
  Tools_toolbar(CGAL::Qt_widget *w, QMainWindow *mw, CDT *t);
private:
  QToolButton        *but[10];
  CGAL::Qt_widget    *widget;
  QButtonGroup       *button_group;
  void               addToolButton(QToolButton *b);
  int                nr_of_buttons;

  CGAL::Qt_widget_get_segment<K2>            segmentbut;
  CGAL::Qt_widget_get_point<K2>              pointbut;
  CGAL::Qt_widget_get_polygon<Cgal_Polygon>  polygonbut;
};//end class

#endif
