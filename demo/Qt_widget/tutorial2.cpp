// Copyright (c) 2002-2004,2007  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Qt_widget/demo/Qt_widget/tutorial2.cpp $
// $Id: tutorial2.cpp 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Mariette Yvinec <Mariette.Yvinec@sophia.inria.fr>

#include <CGAL/basic.h>

#ifndef CGAL_USE_QT
#include <iostream>
int main(int, char*){
  std::cout << "Sorry, this demo needs QT..." << std::endl; return 0;}
#else
#include <CGAL/Cartesian.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/IO/Qt_widget_Triangulation_2.h>
#include <CGAL/IO/Qt_widget.h>
#include <qapplication.h>
#include <qmainwindow.h>

typedef CGAL::Cartesian<double>             K;
typedef K::Point_2                          Point_2;
typedef CGAL::Delaunay_triangulation_2<K>   Delaunay;

Delaunay dt;

class My_window : public QMainWindow {
  Q_OBJECT
public:
  My_window(int x, int y)
  {
    widget = new CGAL::Qt_widget(this);
    widget->resize(x,y);
    widget->set_window(0, x, 0, y);

    connect(widget, SIGNAL(redraw_on_back()),
	   this, SLOT(redraw_win()));

    connect(widget, SIGNAL(s_mousePressEvent(QMouseEvent*)),
	    this, SLOT(mousePressEvent(QMouseEvent*)));

    setCentralWidget(widget);
  };
private slots:
  void redraw_win()
  {
    *widget << dt;
  }

  void mousePressEvent(QMouseEvent *e)
  {
    dt.insert(Point_2(widget->x_real(e->x()), widget->y_real(e->y())));
    widget->redraw();
  }

private: // private data member
  CGAL::Qt_widget* widget;
};

//moc_source_file : tutorial2.cpp
#include "tutorial2.moc"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );
    My_window *w = new My_window(400,400);
    app.setMainWidget( w);
    w->show();
    return app.exec();
}
#endif
