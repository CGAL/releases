// Copyright (c) 2008  INRIA Sophia-Antipolis (France), ETHZ (Suisse).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.4-branch/AABB_tree/include/CGAL/AABB_tree/Bbox_3_Bbox_3_do_intersect.h $
// $Id: Bbox_3_Bbox_3_do_intersect.h 46267 2008-10-14 12:15:10Z palliez $
// 
//
// Author(s)     :  Camille Wormser, Jane Tournois, Pierre Alliez

#ifndef CGAL_BBOX_3_BBOX_3_DO_INTERSECT_H
#define CGAL_BBOX_3_BBOX_3_DO_INTERSECT_H

CGAL_BEGIN_NAMESPACE

namespace CGALi {

  // assumes that the intersection with the supporting plane has
  // already been checked.
  template <class K>
  bool do_intersect(const CGAL::Bbox_3& c1, 
    const CGAL::Bbox_3& c2,
    const K& kernel)
  {
    for(int i = 0; i < 3; ++i)
      if(c1.max(i) < c2.min(i) || c1.min(i) > c2.max(i))
	return false;
    return true;
  }

} // namespace CGALi

template <class K>
bool do_intersect(const CGAL::Bbox_3& c, 
		  const CGAL::Bbox_3& bbox)
{
  return typename K::Do_intersect_3()(c, bbox);
}

CGAL_END_NAMESPACE

#endif  // CGAL_BBOX_3_BBOX_3_DO_INTERSECT_H
