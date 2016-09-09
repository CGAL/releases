// ============================================================================
//
// Copyright (c) 1998-1999 The CGAL Consortium

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
// file          : demo/Triangulation3/demo_color.C
// revision      : $Revision: 1.14 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis (Mariette Yvinec)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// Geomview doesn't work on M$ at the moment, so we don't compile this file.
#if defined(__BORLANDC__) || defined(_MSC_VER)
#include <iostream>
int main()
{
  std::cerr << "Geomview doesn't work on Windows, so this demo doesn't work"
            << std::endl;
  return 0;
}
#else

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Filtered_kernel.h>

#include <CGAL/Delaunay_triangulation_3.h>

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/IO/Triangulation_geomview_ostream_3.h>

template < class Traits >
class My_vertex_base
  : public CGAL::Triangulation_vertex_base_3<Traits>
{
public :
  CGAL::Color color;

  My_vertex_base() 
    : CGAL::Triangulation_vertex_base_3<Traits>(), color(CGAL::WHITE)
    {}
};

struct K : public CGAL::Filtered_kernel<CGAL::Simple_cartesian<double> > {};

typedef K::Point_3 Point;

typedef CGAL::Triangulation_cell_base_3<K> Cb;
typedef My_vertex_base<K> Vb;
typedef CGAL::Triangulation_data_structure_3<Vb,Cb> Tds;
typedef CGAL::Delaunay_triangulation_3<K, Tds> Delaunay;

int main()
{
  CGAL::Geomview_stream gv(CGAL::Bbox_3(0,0,0, 2, 2, 2));
  gv.set_bg_color(CGAL::Color(0, 200, 200));
  gv.clear();

  Delaunay T;

  T.insert(Point(0,0,0));
  T.insert(Point(1,0,0));  
  T.insert(Point(0,1,0));  
  T.insert(Point(0,0,1));  
  T.insert(Point(2,2,2));  
  T.insert(Point(-1,0,1));  

  Delaunay::Finite_vertices_iterator vit;
  for (vit = T.finite_vertices_begin(); vit != T.finite_vertices_end(); ++vit)
    if (T.degree(vit) == 6)
      vit->color = CGAL::RED;

  std::cout << "           Visualization of T" << std::endl;
  gv.set_wired(true);
  gv << T;

  std::cout << "           Vertices of T with their own color" << std::endl
	    << "           red for degree 6 (counting infinite vertex)" 
	    << std::endl 
	    << "           white otherwise" << std::endl;
  for (vit = T.finite_vertices_begin(); vit != T.finite_vertices_end(); ++vit) {
    gv << vit->color;
    gv << vit->point();
  }

  char ch;
  std::cout << "Enter any character to quit" << std::endl;
  std::cin >> ch;

  return 0;
}

#endif // if defined(__BORLANDC__) || defined(_MSC_VER)
