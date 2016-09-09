// Copyright (c) 2001  Tel-Aviv University (Israel).
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
// $Source: /CVSROOT/CGAL/Packages/Planar_map/include/CGAL/Planar_map_2/Pm_segment_utilities_2.h,v $
// $Revision: 1.9 $ $Date: 2003/09/18 10:24:48 $
// $Name: current_submission $
//
// Author(s)     : Shai Hirsch       <shaihi@post.tau.ac.il>
//                 Efi Fogel         <efif@post.tau.ac.il>

#ifndef CGAL_PM_SEGMENT_UTILITIES_2_H
#define CGAL_PM_SEGMENT_UTILITIES_2_H

CGAL_BEGIN_NAMESPACE

/*! Construct a direction in the same direction as a given segment which source
 * is the given point
 * \pre the given point must be one of the segment end-points
 */
template <class Kernel_, class Segment_2_>
struct Construct_direction_at_endpoint_2 : 
public Kernel_::Construct_direction_2
{
  typedef Kernel_                                Kernel;
  typedef Segment_2_                             Segment_2;
    
  typedef typename Kernel::Construct_direction_2 Base;
  typedef typename Kernel::Direction_2           Direction_2;
  typedef typename Kernel::Point_2               Point_2;

  Construct_direction_at_endpoint_2()
  {
    Kernel kernel;
    is_equal = kernel.equal_2_object();
    construct_vertex = kernel.construct_vertex_2_object();
    construct_opposite_direction =
      kernel.construct_opposite_direction_2_object();
  }

  Construct_direction_at_endpoint_2(const Kernel & in_kernel) 
  {
    is_equal = in_kernel.equal_2_object();
    construct_vertex = in_kernel.construct_vertex_2_object();
    construct_opposite_direction =
      in_kernel.construct_opposite_direction_2_object();
    construct_direction = in_kernel.construct_direction_2_object();
  }
    
  Direction_2 operator()(const Segment_2 & cv, const Point_2 & point) const
  { 
    if (is_equal(construct_vertex(cv, 0), point)) return Base::operator()(cv);
    return construct_opposite_direction(construct_direction(cv));
  }

private:
  typename Kernel::Equal_2 is_equal;
  typename Kernel::Construct_vertex_2 construct_vertex;
  typename Kernel::Construct_direction_2 construct_direction;
  typename Kernel::Construct_opposite_direction_2 construct_opposite_direction;
};

/*!
 */
template<class Kernel_>
class Is_vertex_for_segments_2 
{
public:
  typedef Kernel_                     Kernel;
  typedef typename Kernel::Point_2    Point_2;
  typedef typename Kernel::Segment_2  Segment_2;

  Is_vertex_for_segments_2()
  {
    Kernel kernel;
    is_equal = kernel.equal_2_object();
    construct_vertex = kernel.construct_vertex_2_object();
  }

  Is_vertex_for_segments_2(const Kernel & in_kernel)
  {
    is_equal = in_kernel.equal_2_object();
    construct_vertex = in_kernel.construct_vertex_2_object();
  }

  bool operator()(const Point_2 & point, Segment_2 cv)
  {
    if (is_equal(construct_vertex(cv, 0), point) ||
        is_equal(construct_vertex(cv, 1), point)) return true; 
    return false;
  }

private:
  typename Kernel::Equal_2 is_equal;
  typename Kernel::Construct_vertex_2 construct_vertex;
};

/*! 
 */
template <class Kernel_, class Segment_2_>
struct Counterclockwise_in_between_for_segments_2 :
public Kernel_::Counterclockwise_in_between_2
{
  typedef Kernel_                                        Kernel;
  typedef Segment_2_                                     Segment_2;

  typedef typename Kernel::Counterclockwise_in_between_2 Base;
  typedef typename Kernel::Point_2                       Point_2;
  typedef typename Kernel::Direction_2                   Direction_2;

  typedef Is_vertex_for_segments_2<Kernel>               Is_vertex_2;
    
  typedef CGAL::Construct_direction_at_endpoint_2<Kernel, Segment_2>
                                                         Construct_direction_2;
  Counterclockwise_in_between_for_segments_2()
  {
    Kernel kernel;
    construct_direction = Construct_direction_2(kernel);
    counterclockwise_in_between =
        kernel.counterclockwise_in_between_2_object();
  }

  Counterclockwise_in_between_for_segments_2(const Kernel & in_kernel)
      : construct_direction(in_kernel)
  {
    counterclockwise_in_between =
        in_kernel.counterclockwise_in_between_2_object();
  }

  bool operator()(const Point_2 & point, const Segment_2 & cv, 
                  const Segment_2 & first, const Segment_2 & second) const
  {
    // Preconditions:
    CGAL_precondition_code(Is_vertex_2 is_vertex;);
    CGAL_precondition_msg(is_vertex(point, cv),
                          "point should be an endpoint of cv.");
    CGAL_precondition_msg(is_vertex(point, first),
                          "point should be an endpoint of first.");
    CGAL_precondition_msg(is_vertex(point, second),
                          "point should be an endpoint of second.");
    
    const Direction_2 & d  = construct_direction(cv,     point);
    const Direction_2 & d1 = construct_direction(first,  point);
    const Direction_2 & d2 = construct_direction(second, point);

    return counterclockwise_in_between(d, d1, d2);
  }

private:
  Construct_direction_2 construct_direction;
  typename Kernel::Counterclockwise_in_between_2 counterclockwise_in_between;
};

CGAL_END_NAMESPACE

#endif
