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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Min_quadrilateral_2/demo/Min_quadrilateral_2/min_quadrilateral_2.cpp $
// $Id: min_quadrilateral_2.cpp 45454 2008-09-09 21:42:42Z lrineau $
//
//
// Author(s)     : Radu Ursu

#include <CGAL/basic.h>


#include <fstream>
#include <stack>
#include <set>
#include <string>

//CGAL
#include <CGAL/Cartesian.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/Polygon_2.h>

//Qt_widget
#include "Qt_widget_toolbar.h"
#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_standard_toolbar.h>
#include <CGAL/IO/Qt_help_window.h>
#include <CGAL/IO/Qt_widget_layer.h>
#include "Qt_widget_toolbar_layers.h"
#include <CGAL/IO/pixmaps/demoicon.xpm>

//Qt
#include <qplatinumstyle.h>
#include <qapplication.h>
#include <qmainwindow.h>
#include <qstatusbar.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qtoolbutton.h>
#include <qtoolbar.h>
#include <qfiledialog.h>
#include <qtimer.h>

//typedefs CGAL
typedef double Coord_type;
typedef CGAL::Cartesian<Coord_type>   Rep;
typedef CGAL::Point_2<Rep>	      Point_2;
typedef CGAL::Segment_2<Rep>	      Segment;



const QString my_title_string("Minimum Enclosed Quadrilateral with"
			      " CGAL Qt_widget");

//global flags and variables
int current_state;
std::list<Point_2>	  list_of_points;



class MyWindow : public QMainWindow
{
  Q_OBJECT
public:
  MyWindow(int w, int h){
    widget = new CGAL::Qt_widget(this);
    setCentralWidget(widget);

    //create a timer for checking if somthing changed
    QTimer *timer = new QTimer( this );
    connect( timer, SIGNAL(timeout()),
           this, SLOT(timer_done()) );
    timer->start( 200, FALSE );

    // file menu
    QPopupMenu * file = new QPopupMenu( this );
    menuBar()->insertItem( "&File", file );
    file->insertItem("&New", this, SLOT(new_instance()), CTRL+Key_N);
    file->insertItem("New &Window", this, SLOT(new_window()), CTRL+Key_W);
    file->insertSeparator();
    file->insertItem("Printer", widget, SLOT(print_to_ps()), CTRL+Key_P);
    file->insertSeparator();
    file->insertItem( "&Close", this, SLOT(close()), CTRL+Key_X );
    file->insertItem( "&Quit", qApp, SLOT( closeAllWindows() ), CTRL+Key_Q );

    // drawing menu
    QPopupMenu * draw = new QPopupMenu( this );
    menuBar()->insertItem( "&Draw", draw );
    draw->insertItem("&Generate points", this,
		SLOT(gen_points()), CTRL+Key_G );

    // help menu
    QPopupMenu * help = new QPopupMenu( this );
    menuBar()->insertItem( "&Help", help );
    help->insertItem("How To", this, SLOT(howto()), Key_F1);
    help->insertSeparator();
    help->insertItem("&About", this, SLOT(about()), CTRL+Key_A );
    help->insertItem("About &Qt", this, SLOT(aboutQt()) );

    //the standard toolbar
    stoolbar = new CGAL::Qt_widget_standard_toolbar (widget, this, "ST");
    //the new tools toolbar
    newtoolbar = new Tools_toolbar(widget, this, &list_of_points);
    //the layers toolbar
    vtoolbar = new Layers_toolbar(widget, this, &list_of_points);

    *widget << CGAL::LineWidth(2) << CGAL::BackgroundColor (CGAL::BLACK);

    resize(w,h);
    widget->set_window(-1, 1, -1, 1);
    widget->setMouseTracking(TRUE);

    //connect the widget to the main function that receives the objects
    connect(widget, SIGNAL(new_cgal_object(CGAL::Object)),
      this, SLOT(get_new_object(CGAL::Object)));

    //application flag stuff
    old_state = 0;
  };

private:
  void something_changed(){current_state++;};

public slots:
  void new_instance()
  {
    widget->lock();
    list_of_points.clear();
    stoolbar->clear_history();
    // set the Visible Area to the Interval
    widget->set_window(-1.1, 1.1, -1.1, 1.1);
    widget->unlock();
    something_changed();
  }

private slots:
  void get_new_object(CGAL::Object obj)
  {
    if(const Point_2 *p = CGAL::object_cast<Point_2>(&obj)) {
      list_of_points.push_back(*p);
      something_changed();
    }
  };

  void about()
  {
    QMessageBox::about( this, my_title_string,
		"This is a demo for Minimum enclosing quadrilateral\n"
  		"Copyright CGAL @2003");
  };

  void aboutQt()
  {
    QMessageBox::aboutQt( this, my_title_string );
  }

  void howto(){
    QString home;
    home = "help/index.html";
    CGAL::Qt_help_window *help = new
      CGAL::Qt_help_window(home, ".", 0, "help viewer");
    help->resize(400, 400);
    help->setCaption("Demo HowTo");
    help->show();
  }

  void new_window(){
    MyWindow *ed = new MyWindow(500, 500);
    ed->setCaption("Layer");
    ed->stoolbar->clear_history();
    ed->widget->set_window(-1.1, 1.1, -1.1, 1.1);
    ed->show();
    something_changed();
  }

  void timer_done()
  {
    if(old_state!=current_state){
      widget->redraw();
      old_state = current_state;
    }
  }

  void gen_points()
  {
    stoolbar->clear_history();
    widget->set_window(-1.1, 1.1, -1.1, 1.1);
	// set the Visible Area to the Interval

    // send resizeEvent only on show.
    CGAL::Random_points_in_disc_2<Point_2> g(0.5);
    for(int count=0; count<200; count++) {
      list_of_points.push_back(*g++);
    }
    something_changed();
  }



private:
  CGAL::Qt_widget       *widget;
  CGAL::Qt_widget_standard_toolbar
                        *stoolbar;
  Tools_toolbar         *newtoolbar;
  Layers_toolbar        *vtoolbar;
  int                   old_state;
};

#include "min_quadrilateral_2.moc"


int
main(int argc, char **argv)
{
  QApplication app( argc, argv );
  MyWindow widget(500, 500); // physical window size
  app.setMainWidget(&widget);
  widget.setCaption(my_title_string);
  widget.setMouseTracking(TRUE);
#if !defined (__POWERPC__)
  QPixmap cgal_icon = QPixmap((const char**)demoicon_xpm);
  widget.setIcon(cgal_icon);
#endif
  widget.show();
  current_state = -1;
  return app.exec();
}

