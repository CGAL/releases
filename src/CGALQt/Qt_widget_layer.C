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
// file          : src/CGALQt/Qt_widget_layer.C
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

#ifdef CGAL_USE_QT

#include <CGAL/IO/Qt_widget_layer.h>

namespace CGAL {
	void	Qt_widget_layer::attach(Qt_widget *w) {
				widget=w;
        if(activate())
				  emit(activated(this));
	}
  void Qt_widget_layer::stateChanged(int i){
    if(i==2)
      activate();
    else if(i == 0)
      deactivate();
  }
  bool Qt_widget_layer::activate(){
    if(active)
      return false;
    else {
      active = true;
      activating();
      emit(activated(this));
      return true;
    }
  }
  bool Qt_widget_layer::deactivate(){
    if(!active)
      return false;
    else {
      active = false;
      deactivating();
      emit(deactivated(this));
      return true;
    }
      
  }
} // namespace CGAL

#include "Qt_widget_layer.moc"

#endif // CGAL_USE_QT
