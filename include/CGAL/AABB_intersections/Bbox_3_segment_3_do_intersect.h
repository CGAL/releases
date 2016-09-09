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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/AABB_tree/include/CGAL/AABB_intersections/Bbox_3_segment_3_do_intersect.h $
// $Id: Bbox_3_segment_3_do_intersect.h 51931 2009-09-14 13:22:12Z stayeb $
// 
//
// Author(s)     : Camille Wormser, Jane Tournois, Pierre Alliez


#ifndef CGAL_SEGMENT_3_BBOX_3_DO_INTERSECT_H
#define CGAL_SEGMENT_3_BBOX_3_DO_INTERSECT_H

#include <CGAL/Segment_3.h>
#include <CGAL/Bbox_3.h>

// inspired from http://cag.csail.mit.edu/~amy/papers/box-jgt.pdf

CGAL_BEGIN_NAMESPACE

namespace CGALi {

  template <class K>
  bool do_intersect(const typename K::Segment_3& segment, 
    const CGAL::Bbox_3& bbox,
    const K&)
  {
    typedef typename K::FT FT;
    typedef typename K::Point_3 Point;
    typedef typename K::Vector_3 Vector;
    typedef typename K::Segment_3 Segment;

    Point parameters[2];
    parameters[0] = Point(bbox.xmin(), bbox.ymin(), bbox.zmin());
    parameters[1] = Point(bbox.xmax(), bbox.ymax(), bbox.zmax());

    const Point source = segment.source();
    const Point target = segment.target();

    const Vector direction = target - source;
    FT tmin(0.0);
    FT tmax(1.0);
    
    if ( ! CGAL_NTS is_zero(direction.x()) )
    {
      FT inv_direction_x = (FT)1.0/direction.x();
      const int sign_x = inv_direction_x < (FT)0.0;
      
      tmin = (parameters[sign_x].x() - source.x()) * inv_direction_x;
      tmax = (parameters[1-sign_x].x() - source.x()) * inv_direction_x;
      
      // premature exit
      if(tmax < (FT)0.0 || tmin > (FT)1.0)
        return false;
      
      if(tmin < (FT)0.0)
        tmin = (FT)0.0;
      if(tmax > (FT)1.0)
        tmax = (FT)1.0;
    }
    else
    {
      // premature exit if x value of segment is outside bbox
      if ( source.x() < parameters[0].x() || source.x() > parameters[1].x() )
        return false;
    }
    
    if ( ! CGAL_NTS is_zero(direction.y()) )
    {
      FT inv_direction_y = (FT)1.0/direction.y();
      const int sign_y = inv_direction_y < (FT)0.0;
      
      const FT tymin = (parameters[sign_y].y() - source.y()) * inv_direction_y;
      const FT tymax = (parameters[1-sign_y].y() - source.y()) * inv_direction_y;
      
      if(tmin > tymax || tymin > tmax) 
        return false;
      
      if(tymin > tmin)
        tmin = tymin;
      
      if(tymax < tmax)
        tmax = tymax;
    }
    else
    {
      // premature exit if y value of segment is outside bbox
      if ( source.y() < parameters[0].y() || source.y() > parameters[1].y() )
        return false;
    }
    
    if ( ! CGAL_NTS is_zero(direction.z()) )
    {
      FT inv_direction_z = (FT)1.0/direction.z();
      const int sign_z = inv_direction_z < (FT)0.0;
      
      FT tzmin = (parameters[sign_z].z() - source.z()) * inv_direction_z;
      FT tzmax = (parameters[1-sign_z].z() - source.z()) * inv_direction_z;
      
      if(tmin > tzmax || tzmin > tmax) 
        return false;
    }
    else
    {
      // premature exit if z value of segment is outside bbox
      if ( source.z() < parameters[0].z() || source.z() > parameters[1].z() )
        return false;
    }
    
  return true;
  }

  template <class K>
  bool do_intersect(const CGAL::Bbox_3& bbox,
                    const typename K::Segment_3& segment, 
                    const K& k)
  {
    return do_intersect(segment, bbox, k);
  }

} // namespace CGALi

template <class K>
bool do_intersect(const CGAL::Segment_3<K>& segment, 
		  const CGAL::Bbox_3& bbox)
{
  return typename K::Do_intersect_3()(segment, bbox);
}

template <class K>
bool do_intersect(const CGAL::Bbox_3& bbox, 
		  const CGAL::Segment_3<K>& segment)
{
  return typename K::Do_intersect_3()(segment, bbox);
}

CGAL_END_NAMESPACE

#endif  // CGAL_SEGMENT_3_BBOX_3_DO_INTERSECT_H
