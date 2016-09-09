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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.2-branch/Principal_component_analysis/demo/Principal_component_analysis/linear_least_squares_fitting_toolbar.h $
// $Id: linear_least_squares_fitting_toolbar.h 29803 2006-03-29 08:21:25Z afabri $
// 
//
// Author(s)     : Andreas Fabri


#ifndef MIN_CIRCLE_2_TOOLBAR_H
#define MIN_CIRCLE_2_TOOLBAR_H

#include <CGAL/Cartesian.h>


#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_get_point.h>

#include <qobject.h>
#include <qtoolbutton.h>
#include <qtoolbar.h>
#include <qbuttongroup.h>
#include <qmainwindow.h>

typedef CGAL::Cartesian<double>	  Rp;
typedef Rp::Point_2		  Point_2;

class Tools_toolbar : public QToolBar
{
  Q_OBJECT
public:
  Tools_toolbar(CGAL::Qt_widget *w, QMainWindow *mw, std::list<Point_2> *l1);
  ~Tools_toolbar(){};
private:
  QToolButton     *but[10];
  QButtonGroup    *button_group;
  CGAL::Qt_widget *widget;
  int             nr_of_buttons;

  CGAL::Qt_widget_get_point<Rp>  pointbut;

};//end class

#endif
