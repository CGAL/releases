// Copyright (c) 2009  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/STL_Extension/include/CGAL/Location_policy.h $
// $Id: Location_policy.h 52863 2009-11-03 15:17:02Z spion $
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_LOCATION_POLICY_H
#define CGAL_LOCATION_POLICY_H

#include <CGAL/Complexity_tags.h>

namespace CGAL {

// A policy to select the complexity of point location of a data-structure.

template < typename Tag >
struct Location_policy {};

typedef Location_policy<Fast>     Fast_location;
typedef Location_policy<Compact>  Compact_location;

} // namespace CGAL

#endif // CGAL_LOCATION_POLICY_H
