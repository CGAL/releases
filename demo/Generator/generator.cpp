// Copyright (c) 2002  Max Planck Institut fuer Informatik (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Generator/demo/Generator/generator.cpp $
// $Id: generator.cpp 45457 2008-09-09 22:17:19Z lrineau $
//
//
// Author(s)     :Radu Ursu

#include <CGAL/basic.h>

#include <CGAL/Cartesian.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/function_objects.h>
#include <CGAL/Join_input_iterator.h>
#include <CGAL/Counting_iterator.h>
#include <CGAL/algorithm.h>

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_standard_toolbar.h>
#include <CGAL/IO/Qt_help_window.h>
#include <CGAL/IO/Qt_widget_layer.h>
#include <CGAL/IO/pixmaps/demoicon.xpm>


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


#include <fstream>
#include <stack>
#include <set>
#include <string>
#include <list>

typedef double                          Coord_type;
typedef CGAL::Cartesian<Coord_type>     Rep;

typedef Rep::Point_2                    Point_2;
typedef Rep::Segment_2                  Segment;
typedef CGAL::Creator_uniform_2<double,Point_2>
                                        Creator;

//global flags and variables
int current_state;
std::list<Point_2>                      list_of_points;
std::list<Segment>                      list_of_segments;

const QString my_title_string("Generator Demo with"
			      " CGAL Qt_widget");

class Qt_layer_show_ch : public CGAL::Qt_widget_layer
{
public:

  Qt_layer_show_ch(){};

  void draw()
  {
    widget->lock();
      *widget << CGAL::PointSize(3);
      *widget << CGAL::GREEN;
      std::list<Point_2>::iterator itp = list_of_points.begin();
      while(itp!=list_of_points.end())
      {
        *widget << (*itp++);
      }

      std::list<Segment>::iterator its = list_of_segments.begin();
      while(its!=list_of_segments.end())
      {
        *widget << (*its++);
      }
    widget->unlock();
  };

};//end class

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
    file->insertItem("Print", widget, SLOT(print_to_ps()), CTRL+Key_P);
    file->insertSeparator();
    file->insertItem( "&Close", this, SLOT(close()), CTRL+Key_X );
    file->insertItem( "&Quit", qApp, SLOT( closeAllWindows() ), CTRL+Key_Q );

    // drawing menu
    QPopupMenu * generate = new QPopupMenu( this );
    menuBar()->insertItem( "&Generate", generate );
    generate->insertItem("&Points in disc", this,
				SLOT(in_disc()), CTRL+Key_D );
    generate->insertItem("&Points in square", this,
				SLOT(in_square()), CTRL+Key_S );
    generate->insertItem("&Points on square", this,
				SLOT(on_square()), CTRL+Key_E );
    generate->insertItem("&Points on circle", this,
				SLOT(on_circle()), CTRL+Key_C );
    generate->insertItem("&Points on square grid", this,
				SLOT(on_square_grid()), CTRL+Key_G );

    generate->insertItem("&Segments", this,
				SLOT(segments()), CTRL+Key_T );
    generate->insertItem("&Fan of Segments", this,
				SLOT(segment_fan()), CTRL+Key_F );

    // help menu
    QPopupMenu * help = new QPopupMenu( this );
    menuBar()->insertItem( "&Help", help );
    help->insertItem("How To", this, SLOT(howto()), Key_F1);
    help->insertSeparator();
    help->insertItem("&About", this, SLOT(about()), CTRL+Key_A );
    help->insertItem("About &Qt", this, SLOT(aboutQt()) );

    //the standard toolbar
    stoolbar = new CGAL::Qt_widget_standard_toolbar (widget, this, "ST");

    *widget << CGAL::LineWidth(1) << CGAL::BackgroundColor (CGAL::BLACK);

    resize(w,h);
    widget->set_window(-1, 1, -1, 1);
    widget->setMouseTracking(TRUE);

    //application flag stuff
    old_state = 0;

    //layers
    widget->attach(&testlayer);
  };

private:
  void something_changed(){current_state++;};

public slots:
  void new_instance()
  {
    widget->lock();
    list_of_points.clear();
    list_of_segments.clear();
    stoolbar->clear_history();
    widget->set_window(-1.1, 1.1, -1.1, 1.1);
		// set the Visible Area to the Interval
    widget->unlock();
    something_changed();
  }

private slots:
  void about()
  {
    QMessageBox::about( this, my_title_string,
		"This is a demo for Generator\n"
  		"Copyright CGAL @2003");
  };

  void aboutQt()
  {
    QMessageBox::aboutQt( this, my_title_string );
  }

  void howto(){
    QString home;
    home = "help/index.html";
    CGAL::Qt_help_window *help = new CGAL::Qt_help_window(home, ".",
							  0, "help viewer");
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

  void in_square(){
    //stoolbar->clear_history();
    //widget->set_window(-1.1, 1.1, -1.1, 1.1);
    // set the Visible Area to the Interval
    CGAL::Random_points_in_square_2<Point_2> g(1);
    for(int count=0; count<200; count++) {
      list_of_points.push_back(*g++);
    }
    something_changed();
  }

  void in_disc()
  {
    //stoolbar->clear_history();
    //widget->set_window(-1.1, 1.1, -1.1, 1.1);
    // set the Visible Area to the Interval

    CGAL::Random_points_in_disc_2<Point_2> g(1);
    for(int count=0; count<200; count++) {
      list_of_points.push_back(*g++);
    }
    something_changed();
  }


  void on_square()
  {
    //stoolbar->clear_history();
    //widget->set_window(-1.1, 1.1, -1.1, 1.1);
    // set the Visible Area to the Interval

    CGAL::Random_points_on_square_2<Point_2> g(1);
    for(int count=0; count<200; count++) {
      list_of_points.push_back(*g++);
    }
    something_changed();
  }

  void on_square_grid()
  {
    //    stoolbar->clear_history();
    //widget->set_window(-1.1, 1.1, -1.1, 1.1);
    // set the Visible Area to the Interval

    CGAL::points_on_square_grid_2(2, 100,
				  std::back_inserter(list_of_points),
				  Creator());

    something_changed();
  }

  void on_circle()
  {
    //stoolbar->clear_history();
    //widget->set_window(-1.1, 1.1, -1.1, 1.1);
    // set the Visible Area to the Interval

    CGAL::Random_points_on_circle_2<Point_2> g(0.7);
    for(int count=0; count<200; count++) {
      list_of_points.push_back(*g++);
    }
    something_changed();
  }



  void segments()
  {
   // Create test segment set. Prepare a vector for 200 segments.
    std::vector<Segment> segs;
    segs.reserve(200);

    // Prepare point generator for the horizontal segment, length 200.
    typedef  CGAL::Random_points_on_segment_2<Point_2,Creator>  P1;
    P1 p1( Point_2(-0.1,0), Point_2(0.4,0));

    // Prepare point generator for random points on circle, radius 250.
    typedef  CGAL::Random_points_on_circle_2<Point_2,Creator>  P2;
    P2 p2(1);

    // Create 200 segments.
    typedef CGAL::Creator_uniform_2< Point_2, Segment> Seg_creator;
    typedef CGAL::Join_input_iterator_2< P1, P2, Seg_creator> Seg_iterator;
    Seg_iterator g( p1, p2);
    CGAL::copy_n( g, 200, std::back_inserter(list_of_segments));
    something_changed();
  }


  void segment_fan()
  {
   // Create test segment set. Prepare a vector for 100 segments.
    std::vector<Segment> segs;
    segs.reserve(100);
    typedef CGAL::Points_on_segment_2<Point_2>              PG;
    typedef CGAL::Creator_uniform_2< Point_2, Segment>      Seg_creator;
    typedef CGAL::Join_input_iterator_2< PG, PG, Seg_creator>   Segm_iterator;
    typedef CGAL::Counting_iterator<Segm_iterator,Segment>  Count_iterator;

    // A horizontal like fan.
    PG p1( Point_2(-1, -0.05), Point_2(-1, 0.05),50);   // Point generator.
    PG p2( Point_2( 1,-1), Point_2( 1,1),50);
    Segm_iterator  t1( p1, p2);                     // Segment generator.
    Count_iterator t1_begin( t1);                   // Finite range.
    Count_iterator t1_end( 50);
    std::copy( t1_begin, t1_end, std::back_inserter(list_of_segments));

    // A vertical like fan.
    PG p3( Point_2( -0.05,-1), Point_2(  0.05,-1),50);
    PG p4( Point_2(-1, 1), Point_2( 1, 1),50);
    Segm_iterator  t2( p3, p4);
    Count_iterator t2_begin( t2);
    Count_iterator t2_end( 50);
    std::copy( t2_begin, t2_end, std::back_inserter(list_of_segments));

    something_changed();
  }





private:
  CGAL::Qt_widget        *widget;
  CGAL::Qt_widget_standard_toolbar
                         *stoolbar;
  int                    old_state;
  Qt_layer_show_ch       testlayer;
};

#include "generator.moc"

int
main(int argc, char **argv)
{
  QApplication app( argc, argv );
  MyWindow widget(500,500); // physical window size
  app.setMainWidget(&widget);
  widget.setCaption(my_title_string);
  widget.setMouseTracking(TRUE);
#if !defined(__POWERPC__)
  QPixmap cgal_icon = QPixmap((const char**)demoicon_xpm);
  widget.setIcon(cgal_icon);
#endif
  widget.show();
  current_state = -1;
  return app.exec();
}
