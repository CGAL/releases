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
// file          : include/CGAL/IO/Qt_widget_toolbar.h
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


#ifndef CGAL_QT_WIDGET_TOOLBAR_H
#define CGAL_QT_WIDGET_TOOLBAR_H

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/Filtered_kernel.h>

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

typedef double                              Coord_type;
typedef CGAL::Cartesian<Coord_type>  K1;
typedef CGAL::Filtered_kernel<K1>           Rp;

typedef CGAL::Exact_predicates_tag          Itag;
typedef CGAL::Triangulation_vertex_base_2<Rp>
                                            Vb1;
typedef CGAL::Constrained_triangulation_face_base_2<Rp>
                                            Fb1;
typedef CGAL::Triangulation_data_structure_2<Vb1, Fb1>
                                            TDS1;
typedef CGAL::Exact_predicates_tag          Itag;

typedef CGAL::Constrained_Delaunay_triangulation_2<Rp, TDS1, Itag>
                                            CT1;
typedef CGAL::Constrained_triangulation_plus_2<CT1>
                                            CDT1;
typedef CDT1::Constraint                    Constraint;
typedef CGAL::Partition_traits_2<Rp>        Traits1;
typedef Traits1::Polygon_2                  Polygon;


namespace CGAL {
class Tools_toolbar : public QObject
{
	Q_OBJECT
public:
  Tools_toolbar(Qt_widget *w, QMainWindow *mw, CDT1 *t);

  QToolBar*	toolbar(){return maintoolbar;}

signals:
  void new_object(CGAL::Object);
  void was_repainted();

private slots:
  void get_new_object(CGAL::Object obj) { emit(new_object(obj)); }

private:
  QToolBar		  *maintoolbar;
  QToolButton		*but[10];
  Qt_widget		  *widget;
  QButtonGroup  *button_group;
  int			      activebutton;
  bool			    is_active;
  void			    setActiveButton(int i);
  void			    addToolButton(QToolButton *b);
  int			      nr_of_buttons;
	
  CGAL::Qt_widget_get_segment<Rp>   segmentbut;
  CGAL::Qt_widget_get_point<Rp>	    pointbut;
  CGAL::Qt_widget_get_polygon<Polygon>   polygonbut;
};//end class

};//end namespace

#endif
