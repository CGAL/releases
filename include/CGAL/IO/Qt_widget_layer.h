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
// file          : include/CGAL/IO/Qt_widget_layer.h
// package       : Qt_widget (1.2.30)
// author(s)     : Laurent Rineau & Radu Ursu
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// coordinator   : Laurent Rineau
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_QT_WIDGET_LAYER_H
#define CGAL_QT_WIDGET_LAYER_H

#include <CGAL/IO/Qt_widget.h>
#include <qobject.h>
#include <list>


namespace CGAL {

class Qt_widget_layer : public QObject {
  Q_OBJECT
public:
  Qt_widget_layer() : active(false){};
  // Event handlers
  virtual void mousePressEvent(QMouseEvent *) {} ;
  virtual void mouseReleaseEvent(QMouseEvent *) {};
  virtual void wheelEvent(QMouseEvent *) {};
  virtual void mouseDoubleClickEvent(QMouseEvent *) {};
  virtual void mouseMoveEvent(QMouseEvent *) {};
  virtual void keyPressEvent(QKeyEvent *) {};
  virtual void keyReleaseEvent(QKeyEvent *) {};
  virtual void enterEvent(QEvent *) {};
  virtual void leaveEvent(QEvent *) {};
  virtual bool event(QEvent *e) {QObject::event(e); return true;};

  bool    is_active(){return active;};	//return true if this layer is active

public slots:
	virtual void draw(){};
  void    stateChanged(int);
  bool    activate(); //activate and return true if it was not active
  bool    deactivate();//deactivate and return true if it was active
signals:
  void		activated(Qt_widget_layer*);
  void		deactivated(Qt_widget_layer*);
private:
  void		attach(Qt_widget *w);//attach Qt_widget to the tool
  bool		active;	//true if this layers is active
  friend class		Qt_widget;
protected:
	Qt_widget	*widget;//the pointer to the widget
  virtual void activating(){};
  virtual void deactivating(){};
};

} // namespace CGAL end

#endif // CGAL_QT_WIDGET_LAYER_H
