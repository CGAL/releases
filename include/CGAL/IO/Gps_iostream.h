// Copyright (c) 2009  Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Boolean_set_operations_2/include/CGAL/IO/Gps_iostream.h $
// $Id: Gps_iostream.h 52831 2009-11-01 10:57:26Z efif $
// 
//
// Author(s)     : Efi Fogel <efif@post.tau.ac.il>

#ifndef CGAL_GPS_IOSTREAM_H
#define CGAL_GPS_IOSTREAM_H

#include <iostream>
#include <list>

#include <CGAL/basic.h>
#include <CGAL/General_polygon_set_2.h>

CGAL_BEGIN_NAMESPACE

template <typename Traits>
std::ostream & operator<< (std::ostream& os,
                           const CGAL::General_polygon_set_2<Traits> & pgn_set)
{
  typedef typename CGAL::General_polygon_set_2<Traits>::Polygon_with_holes_2
                                                        Polygon_with_holes_2;
  typedef std::list<Polygon_with_holes_2>               Pgn_with_holes_container;

  Pgn_with_holes_container res;
  pgn_set.polygons_with_holes (std::back_inserter (res));

  std::cout << pgn_set.number_of_polygons_with_holes() << std::endl;
  std::copy(res.begin(), res.end(),
            std::ostream_iterator<Polygon_with_holes_2>(std::cout, "\n"));
  
  return os;
}

CGAL_END_NAMESPACE

#endif
