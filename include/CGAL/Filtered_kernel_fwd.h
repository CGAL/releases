// Copyright (c) 2001,2004  INRIA Sophia-Antipolis (France).
// Copyright (c) 2009  GeometryFactory Sarl (France)
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Filtered_kernel/include/CGAL/Filtered_kernel_fwd.h $
// $Id: Filtered_kernel_fwd.h 53184 2009-11-25 14:42:45Z lrineau $
// 
//
// Author(s)     : Sylvain Pion, Laurent Rineau

#ifndef CGAL_FILTERED_KERNEL_FWD_H
#define CGAL_FILTERED_KERNEL_FWD_H

#include <CGAL/config.h>

namespace CGAL {

#ifdef CGAL_NO_STATIC_FILTERS
template < typename CK, bool UseStaticFilters = false >
#else
template < typename CK, bool UseStaticFilters = true >
#endif
struct Filtered_kernel;

} // end namespace CGAL

#endif // CGAL_FILTERED_KERNEL_FWD_H
