// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/LEDA/window_point.h
// package       : cgal_window (1.0.4)
// revision      : 1.0.3
// revision_date : 25 June 2001
// author(s)     : Matthias Baesken, Algorithmic Solutions
//
// coordinator   : Matthias Baesken, Trier  (<baesken>) 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_WINDOW_POINT_H
#define CGAL_WINDOW_POINT_H

#if defined(CGAL_USE_CGAL_HEADERS)
#include <CGAL/basic.h>
#endif

#include <CGAL/LEDA/basic.h>

/*{\Manpage {window_point} {} {Points}}*/

namespace CGAL {

class __exportC window_point {

/*{\Mdefinition
The data type $window\_point$ is a simple point data type used in the interface of
the window class.
}*/

  double xw, yw; // x and y coordinates ...

public:

/*{\Mcreation wpt}*/

  window_point() : xw(0), yw(0) { }
/*{\Mcreate  creates a window point with coordinates $(0,0)$. }*/

  window_point(double xc, double yc) : xw(xc), yw(yc) { }
/*{\Mcreate  creates a window point with coordinates $(xc,yc)$. }*/
  
  window_point(const window_point& p) : xw(p.xw), yw(p.yw) { }

  window_point& operator=(const window_point& p) { xw=p.xw; yw=p.yw; return *this; }

/*{\Moperations }*/

  // retrieving x and y coordinates ...
  
  double x() const { return xw; }
/*{\Mop  returns the $x$-coordinate of |\Mvar|. }*/
  
  double y() const { return yw; }
/*{\Mop  returns the $y$-coordinate of |\Mvar|. }*/
  
  double xcoord() const { return xw; }
/*{\Mop  returns the $x$-coordinate of |\Mvar|. }*/
  
  double ycoord() const { return yw; }  
/*{\Mop  returns the $y$-coordinate of |\Mvar|. }*/  

  bool operator==(const window_point& q) const { return ((x()==q.x()) && (y()==q.y()) ); }
  bool operator!=(const window_point& q) const { return !operator==(q);}

};



}

#endif
