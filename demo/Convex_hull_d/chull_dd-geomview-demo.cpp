// Copyright (c) 2001, 2002, 2004  Max-Planck-Institute Saarbruecken (Germany).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Convex_hull_d/demo/Convex_hull_d/chull_dd-geomview-demo.cpp $
// $Id: chull_dd-geomview-demo.cpp 41714 2008-01-20 20:24:20Z spion $
//
//
// Author(s)     : Michael Seel <seel@mpi-sb.mpg.de>

#include <CGAL/basic.h>
#include <CGAL/Homogeneous_d.h>
#include <CGAL/Convex_hull_d.h>
#include <CGAL/random_selection.h>

#include <CGAL/Homogeneous.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Convex_hull_d_to_polyhedron_3.h>
#include <CGAL/IO/Polyhedron_geomview_ostream.h>
#include <iostream>
#include <string>
#include <cstdlib>

#if !defined(_MSC_VER)

#ifdef CGAL_USE_LEDA
#include <CGAL/leda_integer.h>
typedef leda_integer RT;
#else
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz RT;
#else
#include <CGAL/double.h>
typedef double RT;
#endif
#endif

typedef CGAL::Homogeneous_d<RT> Kernel;
typedef CGAL::Convex_hull_d<Kernel> Convex_hull_d;
typedef Convex_hull_d::Point_d Point_d;
typedef Convex_hull_d::Simplex_handle Simplex_handle;

template <class R>
CGAL::Point_d<R> random_point_in_range(int d,int l,int h,
                                       CGAL::Point_d<R>)
{
  std::vector<int> V(d+1); V[d]=1;
  for(int i = 0; i<d; ++i)
    V[i] = CGAL::default_random.get_int(l,h);
  return CGAL::Point_d<R>(d,V.begin(),V.end());
}

template <class R>
void random_points_in_range(int n, int d,int l,int h,
                            std::list< CGAL::Point_d<R> >& L)
{ CGAL::Point_d<R> dummy;
  for(int i = 0; i<n; ++i)
    L.push_back(random_point_in_range(d,l,h,dummy));
}

typedef  CGAL::Homogeneous<RT> Kernel_3;
typedef  CGAL::Point_3<Kernel_3> Point_3;
typedef  CGAL::Polyhedron_3<Kernel_3> Polyhedron;

int main(int argc, char* argv[]) {
  int dimension = 3;
  int n = 100;
  if (argc > 1 && std::string(argv[1])=="-h") {
    std::cout << "usage: chddemo [#points]\n";
    std::exit(1);
  }
  if (argc > 1) n = std::atoi(argv[1]);

  int r = 2*n;
  CGAL::Geomview_stream gv(CGAL::Bbox_3(-r, -r, -r, r, r, r));
  gv.clear();


  Convex_hull_d T(dimension);
  std::list<Point_d> L;
  random_points_in_range(n,dimension,-n,n,L);
  int i(0);
  std::list<Point_d>::iterator it;
  for(it = L.begin(); it!=L.end(); ++it) {
    T.insert(*it); i++;
    if (i%10==0) std::cout << i << " points inserted" << std::endl;
  }
  T.is_valid(true);

  Polyhedron P;
  CGAL::convex_hull_d_to_polyhedron_3(T,P);
  gv << P;
  std::cout << "Enter a key to finish" << std::endl;
  char ch;
  std::cin >> ch;

  return 0;
}

#else

int main()
{
  std::cout << "Geomview is not supported on MS windows.\n";
  return 0;
}

#endif
