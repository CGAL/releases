// Copyright (c) 2003, 2004  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Triangulation_2/demo/Triangulation_2/regular_cgal_types.h $
// $Id: regular_cgal_types.h 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Mariette Yvinec <Mariette.Yvinec@sophia.inria.fr>


//CGAL headers
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Regular_triangulation_euclidean_traits_2.h>
#include <CGAL/Regular_triangulation_2.h>

typedef CGAL::Simple_cartesian<double> Rp;
typedef Rp::Point_2 Point_2;
typedef Rp::Circle_2 Circle;
typedef double W;
typedef CGAL::Regular_triangulation_euclidean_traits_2<Rp,W>  Gt;
// typedef CGAL::Triangulation_vertex_base_2<Gt> Vb;
// typedef CGAL::Regular_triangulation_face_base_2<> Fb;
// typedef CGAL::Triangulation_data_structure_2<Vb,Fb > Tds;
typedef CGAL::Regular_triangulation_2<Gt> Regular_triangulation;
typedef Regular_triangulation::Finite_vertices_iterator
                                          Finite_vertices_iterator;
