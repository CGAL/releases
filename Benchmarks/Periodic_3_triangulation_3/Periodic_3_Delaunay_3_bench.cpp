// Copyright (c) 1998  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Periodic_3_triangulation_3/Benchmarks/Periodic_3_triangulation_3/Periodic_3_Delaunay_3_bench.cpp $
// $Id: Periodic_3_Delaunay_3_bench.cpp 48683 2009-04-07 11:17:49Z mcaroli $
// 
//
// Author(s)     : Manuel Caroli

#include "types.h"

#include <CGAL/Periodic_3_Delaunay_triangulation_3.h>
#include <CGAL/Periodic_3_triangulation_traits_3.h>

typedef CGAL::Periodic_3_triangulation_traits_3<K> GT;
typedef CGAL::Periodic_3_Delaunay_triangulation_3<GT> Triang;

int main(int argc, char* argv[]) {
  Triang T;
  return bench_triang<Triang>(argc,argv,T,true);
}
