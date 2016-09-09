// Copyright (c) 2006 Fernando Luis Cacciola Carballal. All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Straight_skeleton_2/demo/Straight_skeleton_2/cgal_types.h $
// $Id: cgal_types.h 37003 2007-03-10 16:55:12Z spion $
//
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_TYPES
#define CGAL_TYPES

#include <CGAL/basic.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_2.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

#include <boost/shared_ptr.hpp>
#include <vector>

#if USE_BIG_FLOAT

#include <CGAL/CORE_BigFloat.h>

#endif

namespace demo
{

//typedef CGAL::Simple_cartesian<double> K ;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
//typedef CGAL::Simple_cartesian<CORE::BigFloat> K ;

typedef CGAL::Polygon_2<K>            CGAL_Polygon ;

typedef K::FT                         FT ;
typedef K::Point_2                    Point;
typedef std::vector<Point>            Polygon;
typedef boost::shared_ptr<Polygon>    PolygonPtr;
typedef CGAL::Segment_2<K>            Segment;
typedef std::vector<PolygonPtr>       Region ;
typedef boost::shared_ptr<Region>     RegionPtr ;
typedef std::vector<RegionPtr>        Regions ;
typedef std::set<double>              Doubles ;

}
#endif
