// Copyright (c) 2002  Max Planck Institut fuer Informatik (Germany).
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
// $Source: /CVSROOT/CGAL/Packages/Partition_2/demo/Partition_2/cgal_types.h,v $
// $Revision: 1.1.6.1 $ $Date: 2004/12/19 16:37:39 $
// $Name:  $
//
// Author(s)     : Radu Ursu

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/MP_Float.h>
#include <CGAL/random_polygon_2.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/point_generators_2.h>


typedef CGAL::MP_Float				                      NT;
typedef CGAL::Cartesian<NT>                         K;
typedef CGAL::Partition_traits_2<K>                 Traits;
typedef Traits::Point_2                             Point_2;
typedef Traits::Polygon_2                           Cgal_Polygon;
typedef CGAL::Random_points_in_square_2<Point_2>    Point_generator;
