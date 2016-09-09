// ============================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : orientation.fw
// file          : demo/Robustness/cocircular_2.C
// revision      : 1.5
// revision_date : 20 Sep 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#include <CGAL/basic.h>
#ifndef CGAL_USE_LEDA
int main() { std::cout << "\nSorry, this demo needs LEDA\n"; return 0; }
#else
#include <CGAL/Homogeneous.h>
#include <CGAL/Cartesian.h>
#include <cassert>
#include <vector>
#include <algorithm>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/copy_n.h>
#include <CGAL/IO/leda_window.h>
#include <CGAL/IO/Ostream_iterator.h>
#include <CGAL/leda_real.h>
#include <CGAL/Interval_arithmetic.h>
#include <CGAL/kernel_to_kernel.h>
#include <CGAL/orientation_test_statistics.h>

#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_ellipse_2_traits_2.h>
#include <CGAL/Min_ellipse_2.h>
#include <CGAL/Triangulation_euclidean_traits_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/IO/Window_stream.h>
typedef CGAL::Cartesian<double>                          CartesianDouble;
typedef CGAL::Point_2<CartesianDouble>                   Point;
typedef CGAL::Creator_uniform_2<double,Point>            Pt_creator;
typedef std::vector<Point>                               Vector;
typedef CGAL::Cartesian<leda_real>                       CartesianLedaReal;
typedef CGAL::Min_circle_2_traits_2<CartesianDouble>     Traits;

typedef CGAL::Min_circle_2_traits_2<CartesianDouble>     Traits;
typedef CGAL::Min_circle_2<Traits>                       Min_circle;
typedef CGAL::Min_ellipse_2_traits_2<CartesianDouble>    ETraits;
typedef CGAL::Min_ellipse_2<ETraits>                     Min_ellipse;
typedef CGAL::Triangulation_euclidean_traits_2<CartesianDouble> Gtd;
typedef CGAL::Triangulation_vertex_base_2<Gtd>           Vbd;
typedef CGAL::Triangulation_face_base_2<Gtd>             Fbd;
typedef CGAL::Triangulation_default_data_structure_2<Gtd,Vbd,Fbd> Tdsd;
typedef CGAL::Delaunay_triangulation_2<Gtd,Tdsd>         DT_double;


int
main(int argc, char** argv)
{
    int N = (argc > 1) ? CGAL_CLIB_STD::atoi(argv[1]) : 30;
    
    typedef leda_window  CGAL_Stream;
    CGAL_Stream W( 500, 550);
    CGAL_Stream W1( 400, 400);
    CGAL::cgalize(W);
    CGAL::cgalize(W1);
    
    W.init( 0, 500, 0);
    W1.init(-0.12, 0.12, -0.12);
    W.display();
    W1.display(W,50,50);
    
    
    Vector points1;
    typedef CGAL::Random_points_on_circle_2<Point,Pt_creator>   P_on_circle;
    P_on_circle  pc1( 0.1);
    CGAL::copy_n( pc1, N, std::back_inserter(points1));
    
    W1.set_fg_color(leda_pink);
    std::copy( points1.begin(), points1.end(),
               CGAL::Ostream_iterator< Point, CGAL_Stream>( W1));

    Min_circle  mc2( points1.begin(), points1.end(), true);
    W1 << mc2.circle();
    W.draw_ctext(250, 80, "min circle computed");

    Min_ellipse  me2( points1.begin(), points1.end(), true);
    W1.set_fg_color(leda_blue);
    W1 << me2.ellipse();
    W.draw_ctext(250, 60, "min ellipse computed");

    DT_double DTD;
    std::copy( points1.begin(), points1.end(), std::back_inserter( DTD ));
    W1.set_fg_color(leda_grey1);
    W1 << DTD;
    W1.set_fg_color(leda_pink);
    W1 << mc2.circle();
    W1.set_fg_color(leda_blue);
    W1 << me2.ellipse();
    W1.set_fg_color(leda_pink);
    std::copy( points1.begin(), points1.end(),
               CGAL::Ostream_iterator< Point, CGAL_Stream>( W1));
    W.draw_ctext(250, 40, "Delaunay triangulation computed");

    W.read_mouse();

    return 0;
}
#endif // USE_LEDA
