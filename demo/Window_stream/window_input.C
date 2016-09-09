// ============================================================================
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
// file          : demo/Window_stream/window_input.C
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/20 15:39:24 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Circle_2.h>
#include <CGAL/IO/Window_stream.h>

typedef CGAL::Cartesian< double >             RepCls;
typedef CGAL::Point_2<RepCls>                 Point;
typedef CGAL::Segment_2<RepCls>               Segment;
typedef CGAL::Line_2<RepCls>                  Line;
typedef CGAL::Ray_2<RepCls>                   Ray;
typedef CGAL::Iso_rectangle_2<RepCls>         Iso;
typedef CGAL::Triangle_2<RepCls>              Triangle;
typedef CGAL::Circle_2<RepCls>                Circle;


#if defined(CGAL_USE_CGAL_WINDOW) 
#define leda_red     CGAL::red
#define leda_yellow  CGAL::yellow
#endif

int
main()
{
  CGAL::Window_stream W;
  CGAL::cgalize( W);
  W.set_fg_color( leda_red);
  W.set_bg_color( leda_yellow);
  W.display();

  CGAL::set_pretty_mode( std::cout);

  W.acknowledge("Input Points");
  W.clear();
  Point p;
  while ( W >> p) { std::cout << p << std::endl; }

  W.acknowledge("Input Segments");
  W.clear();
  Segment s;
  while ( W >> s) { std::cout << s << std::endl; }

  W.acknowledge("Input Lines");
  W.clear();
  Line l;
  while ( W >> l) { std::cout << l << std::endl; }

  W.acknowledge("Input Rays");
  W.clear();
  Ray ray;
  while ( W >> ray) { std::cout << ray << std::endl; }

  W.acknowledge("Input Triangles");
  W.clear();
  Triangle t;
  while ( W >> t) { std::cout << t << std::endl; }

  W.acknowledge("Input Iso_rectangles");
  W.clear();
  Iso x;
  while ( W >> x) { std::cout << x << std::endl; }

  W.acknowledge("Input Circles");
  W.clear();
  Circle c;
  while ( W >> c) { std::cout << c << std::endl; }

  W.acknowledge("Read Functions");
  W.clear();
  W.message("Point");
  CGAL::read( W, p);
  W.message("Segment");
  CGAL::read( W, s);
  W.message("Line");
  CGAL::read( W, l);
  W.message("Ray");
  CGAL::read( W, ray);
  W.message("Triangle");
  CGAL::read( W, t);
  W.message("Iso_rectangle");
  CGAL::read( W, x);
  W.message("Circle");
  CGAL::read( W, c);


  W.acknowledge("THE END");
  return 0;
}

