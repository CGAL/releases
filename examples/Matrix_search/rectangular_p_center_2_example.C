// ============================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : rectangular_p_center_2_example.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Matrix_search $
// source        : pcenter.aw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1999/06/01 14:07:47 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// 2-4-Centering Axis-Parallel 2D-Rectangles - example program
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_H
#include <CGAL/Cartesian.h>
#endif // CGAL_CARTESIAN_H
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H
#ifndef CGAL_POINT_GENERATORS_2_H
#include <CGAL/point_generators_2.h>
#endif // CGAL_POINT_GENERATORS_2_H
#ifndef CGAL_RECTANGULAR_P_CENTER_2_H
#include <CGAL/rectangular_p_center_2.h>
#endif // CGAL_RECTANGULAR_P_CENTER_2_H
#ifndef CGAL_IO_OSTREAM_ITERATOR_H
#include <CGAL/IO/Ostream_iterator.h>
#endif // CGAL_IO_OSTREAM_ITERATOR_H
#ifndef CGAL_COPY_N_H
#include <CGAL/copy_n.h>
#endif // CGAL_COPY_N_H
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using CGAL::set_pretty_mode;
using CGAL::rectangular_p_center_2;

typedef double                                   FT;
typedef CGAL::Cartesian< FT >                    R;
typedef CGAL::Point_2< R >                       Point;
typedef std::vector< Point >                     Cont;
typedef CGAL::Creator_uniform_2< FT, Point >     Creator;
typedef CGAL::Random_points_in_square_2< Point, Creator >
                                                 Point_generator;
typedef CGAL::Ostream_iterator< Point, ostream > Ostream_iterator_point;

int main() {

  int number_of_points( 10);
  int p( 2);
  Ostream_iterator_point cout_ip( cout);
  set_pretty_mode( cout);

  Cont points;
  CGAL::copy_n( Point_generator( 1),
                number_of_points,
                back_inserter( points));
  cout << "Generated Point Set:" << endl;
  copy( points.begin(), points.end(), cout_ip);

  Cont centers;
  FT p_radius;
  rectangular_p_center_2(
    points.begin(),
    points.end(),
    back_inserter( centers),
    p_radius,
    p);
  cout << "\n\n" << p << "-centers:" << endl;
  copy( centers.begin(), centers.end(), cout_ip);
  cout << "\n\n" << p << "-radius = " << p_radius << endl;

} 
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

