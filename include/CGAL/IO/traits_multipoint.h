// Copyright (c) 2018  GeometryFactory Sarl (France).
// All rights reserved.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-5.0-beta1/Stream_support/include/CGAL/IO/traits_multipoint.h $
// $Id: traits_multipoint.h e107612 %aI Maxime Gimeno
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Maxime Gimeno

#ifndef CGAL_IO_TRAITS_MULTIPOINT_H
#define CGAL_IO_TRAITS_MULTIPOINT_H
#if BOOST_VERSION >= 105600 && (! defined(BOOST_GCC) || BOOST_GCC >= 40500)
#include <CGAL/internal/Geometry_container.h>
#include <boost/geometry/io/wkt/write.hpp>
#include <boost/geometry/io/wkt/read.hpp>

namespace boost{
namespace geometry{
namespace traits{
// WKT traits for MultiPoint
template< typename R >
struct tag<CGAL::internal::Geometry_container<R, multi_point_tag > >
{ typedef multi_point_tag type; };

}//end traits
}//end geometry
}//end boost
#endif // TRAITS_MULTIPOINT_H
#endif
