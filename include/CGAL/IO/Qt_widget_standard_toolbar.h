// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

// Copyright (c) 2002 ENS de Paris
//
// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// The Qt widget we provide for CGAL is distributed under the QPL,
// which is Trolltech's open source license. For more information see 
//     http://www.trolltech.com/developer/licensing/qpl.html
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// file          : include/CGAL/IO/Qt_widget_standard_toolbar.h
// package       : Qt_widget (1.2.30)
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


#ifndef CGAL_QT_WIDGET_STANDARD_TOOLBAR_H
#define CGAL_QT_WIDGET_STANDARD_TOOLBAR_H

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>


// TODO: check if some of those includes shouldn't be in the .C file
#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_focus.h>
#include <CGAL/IO/Qt_widget_zoomrect.h>
#include <CGAL/IO/Qt_widget_handtool.h>


#include <qobject.h>
#include <qtoolbutton.h>
#include <qtoolbar.h>
#include <qmainwindow.h>
#include <qbuttongroup.h>

namespace CGAL {

class Qt_widget_standard_toolbar : public QObject
{
	Q_OBJECT
public:
  Qt_widget_standard_toolbar(Qt_widget *w, QMainWindow *mw);
  QToolBar*	toolbar(){return maintoolbar;}


private slots:
  void zoomin();
  void zoomout();
  void back();
  void forward();
  
private:
  QToolBar		  *maintoolbar;
  QToolButton	  *but[10];
  Qt_widget		  *widget;
  QButtonGroup  *button_group;
  int			      nr_of_buttons;
	
  CGAL::Qt_widget_focus         zoombut;
  CGAL::Qt_widget_zoomrect	    zoomrectbut;
  CGAL::Qt_widget_handtool	    handtoolbut;
};//end class

};//end namespace

#endif //CGAL_QT_WIDGET_STANDARD_TOOLBAR_H
