// Copyright (c) 2008 ETH Zurich (Switzerland)
// Copyright (c) 2008-2009  INRIA Sophia-Antipolis (France) 
// Copyright (c) 2009  GeometryFactory (France)
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Intersections_3/include/CGAL/internal/Intersections_3/Bbox_3_Bbox_3_do_intersect.h $
// $Id: Bbox_3_Bbox_3_do_intersect.h 53496 2009-12-18 15:12:59Z stayeb $
//
//
// Author(s)     :  Laurent Rineau, Camille Wormser, Jane Tournois, Pierre Alliez

#ifndef CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_BBOX_3_DO_INTERSECT_H
#define CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_BBOX_3_DO_INTERSECT_H

// Turn off Visual C++ warning
#ifdef _MSC_VER
#pragma warning ( disable : 4003 )
#endif

#include <CGAL/Bbox_3.h>

CGAL_BEGIN_NAMESPACE

bool
inline
do_intersect(const CGAL::Bbox_3& c,
             const CGAL::Bbox_3& bbox)
{
  return CGAL::do_overlap(c, bbox);
}

CGAL_END_NAMESPACE

#endif  // CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_BBOX_3_DO_INTERSECT_H
