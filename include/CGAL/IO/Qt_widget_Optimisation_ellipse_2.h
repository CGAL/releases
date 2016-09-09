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
// file          : include/CGAL/IO/Qt_widget_Optimisation_ellipse_2.h
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


#ifndef CGAL_QT_WIDGET_OPTIMISATION_ELLIPSE_2_H
#define CGAL_QT_WIDGET_OPTIMISATION_ELLIPSE_2_H

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_Conic_2.h>

namespace CGAL{

template< class Traits_ >
Qt_widget&
operator << ( Qt_widget &ws,
              const CGAL::Optimisation_ellipse_2<Traits_>& oe)
{

  typedef Cartesian<double> Rep;
  typedef Point_2<Rep>	    Point;
  typedef Segment_2<Rep>    Segment;
  
  switch ( oe.n_boundary_points) {
      case 0:
        break;
      case 1:
        ws << oe.boundary_point1;
        break;
      case 2: {
	      double  px1( CGAL::to_double( oe.boundary_point1.x()));
        double  py1( CGAL::to_double( oe.boundary_point1.y()));
        double  px2( CGAL::to_double( oe.boundary_point2.x()));
        double  py2( CGAL::to_double( oe.boundary_point2.y()));
        ws << Segment( Point(px1, py1), Point(px2, py2)); 
	      }
        break;
      case 3:
      case 4:
      case 5:
        ws << oe.to_double();
        break;
      default:
        CGAL_optimisation_assertion( ( oe.n_boundary_points >= 0) &&
                                     ( oe.n_boundary_points <= 5) ); }
    return( ws);
}

}//end namespace CGAL

#endif





