
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
// release       : CGAL-2.4
// release_date  : 2002, May 16
// 
// file          : examples/ConvexHull/ch_of_polyline.C
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/12/05 15:16:08 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#include <CGAL/Cartesian.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/ch_melkman.h>

#ifdef CGAL_USE_LEDA
#include <CGAL/IO/leda_ps_file.h>
#include <CGAL/IO/leda_window.h>
#endif // CGAL_USE_LEDA

#include <CGAL/Polygon_2.h>
#include <CGAL/IO/Window_stream.h>
#include <CGAL/IO/Ostream_iterator.h>

typedef  CGAL::Cartesian<double>      K;
typedef  K::Point_2                   Point_2;
typedef  CGAL::Polygon_2<K>           Polygon;

CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(Point_2*)

int main()
{
  CGAL::set_ascii_mode(std::cin);
  CGAL::set_ascii_mode(std::cout);
  std::istream_iterator< Point_2>  in_start( std::cin );
  std::istream_iterator< Point_2>  in_end;
  std::vector<Point_2> V ;
  std::copy( in_start, in_end, std::back_inserter(V) );
#ifdef CGAL_USE_LEDA
  std::vector<Point_2> CH;
#ifdef NO_DISPLAY
  typedef CGAL::ps_file  OutStream;
#else
  typedef CGAL::Window_stream  OutStream;
#endif
  OutStream W;
  CGAL::Bbox_2 b = V.begin()->bbox();
  for ( std::vector<Point_2>::iterator it = V.begin(); it != V.end(); ++it)
  { b = b + (*it).bbox(); }
  double x_span = b.xmax() - b.xmin();
  double y_span = b.ymax() - b.ymin();
  double span = CGAL::max( x_span, y_span);
  span *= 1.1;
  W.init((b.xmin()+b.xmax()-span)/2,
         (b.xmin()+b.xmax()+span)/2,
         (b.ymin()+b.ymax()-span)/2 );
  CGAL::cgalize(W);
  W.display();
  CGAL::ch_melkman( V.begin(), V.end(), std::back_inserter(CH) );
  std::cout << "Convex Hull has size " << CH.size() << std::endl;
  W << CGAL::Color(200,200,200);
  W << Polygon( CH.begin(), CH.end());
  W << CGAL::GREEN;
  W << Polygon( V.begin(), V.end());
  W << CGAL::RED;
  std::copy( CH.begin(), CH.end(),
             CGAL::Ostream_iterator<Point_2,OutStream>(W));
  leda_wait( 5);
#else
  CGAL::ch_melkman( V.begin(), V.end(),
                    std::ostream_iterator<Point_2>(std::cout,"\n"));
#endif //   CGAL_USE_LEDA
  return 0;
}

