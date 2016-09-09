// Copyright (c) 2008  INRIA Sophia-Antipolis (France), ETHZ (Suisse).
// Copyright (c) 2009  GeometryFactory (France)
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/AABB_tree/include/CGAL/AABB_intersections/Bbox_3_bbox_3_do_intersect.h $
// $Id: Bbox_3_bbox_3_do_intersect.h 51932 2009-09-14 13:32:24Z lrineau $
// 
//
// Author(s)     :  Laurent Rineau, Camille Wormser, Jane Tournois, Pierre Alliez

#ifndef CGAL_BBOX_3_BBOX_3_DO_INTERSECT_H
#define CGAL_BBOX_3_BBOX_3_DO_INTERSECT_H

// Turn off Visual C++ warning
#ifdef _MSC_VER
#pragma warning ( disable : 4003 )
#endif

CGAL_BEGIN_NAMESPACE

bool do_intersect(const CGAL::Bbox_3& c, 
		  const CGAL::Bbox_3& bbox)
{
  return CGAL::do_overlap(c, bbox);
}

CGAL_END_NAMESPACE

#endif  // CGAL_BBOX_3_BBOX_3_DO_INTERSECT_H
