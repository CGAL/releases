// Copyright (c) 2011  GeometryFactory (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/releases/CGAL-3.9-branch/STL_Extension/include/CGAL/internal/boost/property_map.h $
// $Id: property_map.h 64275 2011-06-21 10:22:47Z lrineau $
//
// Author(s)     : Laurent Rineau

// This file includes either <boost/property_map/property_map.hpp> or
// <boost/property_map.hpp> depending on the version of Boost.

#ifndef CGAL_INTERNAL_BOOST_PROPERTY_MAP_H
#define CGAL_INTERNAL_BOOST_PROPERTY_MAP_H

#include <boost/version.hpp>
#if BOOST_VERSION >= 104000
  #include <boost/property_map/property_map.hpp>
#else
  #include <boost/property_map.hpp>
#endif

#endif // CGAL_INTERNAL_BOOST_PROPERTY_MAP_H
