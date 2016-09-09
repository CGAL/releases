// Copyright (c) 2002  Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Largest_empty_rect_2/demo/Largest_empty_rect_2/Qt_widget_toolbar.h $
// $Id: Qt_widget_toolbar.h 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Radu Ursu


#ifndef CGAL_QT_WIDGET_TOOLBAR_H
#define CGAL_QT_WIDGET_TOOLBAR_H

#include "cgal_types.h"

// TODO: check if some of those includes shouldn't be in the .C file
#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_get_point.h>
#include "Qt_widget_move_list_point.h"

#include <qobject.h>
#include <qtoolbutton.h>
#include <qtoolbar.h>
#include <qbuttongroup.h>
#include <qmainwindow.h>


typedef double Cd;
typedef CGAL::Cartesian<Cd> RP;
class Tools_toolbar : public QToolBar
{
  Q_OBJECT
public:
  Tools_toolbar(CGAL::Qt_widget *w, QMainWindow *mw, std::list<Point_2> *l1);
  ~Tools_toolbar(){};

signals:
  void new_object(CGAL::Object);

private:
  QToolButton     *but[10];
  QButtonGroup    *button_group;
  CGAL::Qt_widget *widget;
  int             nr_of_buttons;

  CGAL::Qt_widget_get_point<RP>  pointbut;
  Qt_widget_move_list_point<RP>  move_deletebut;
};//end class

#endif
