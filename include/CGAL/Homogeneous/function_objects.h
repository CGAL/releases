// Copyright (c) 1999,2002  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
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
// $Source: /CVSROOT/CGAL/Packages/H2/include/CGAL/Homogeneous/function_objects.h,v $
// $Revision: 1.15 $ $Date: 2003/10/21 12:16:13 $
// $Name: current_submission $
//
// Author(s)     : Stefan Schirra, Sylvain Pion, Michael Hoffmann

#ifndef CGAL_HOMOGENEOUS_FUNCTION_OBJECTS_H
#define CGAL_HOMOGENEOUS_FUNCTION_OBJECTS_H

#include <CGAL/Kernel/function_objects.h>

CGAL_BEGIN_NAMESPACE

namespace HomogeneousKernelFunctors {

// VC++ 7.0 doesn't have a using namespace that works, and for better
// testing, I prefer to use its workaround on all compilers for now.
#if 0 // !defined CGAL_CFG_USING_NAMESPACE_BUG
  using namespace CommonKernelFunctors;
#else
  using CommonKernelFunctors::Are_ordered_along_line_2;
  using CommonKernelFunctors::Are_ordered_along_line_3;
  using CommonKernelFunctors::Are_strictly_ordered_along_line_2;
  using CommonKernelFunctors::Are_strictly_ordered_along_line_3;
  using CommonKernelFunctors::Assign_2;
  using CommonKernelFunctors::Assign_3;
  using CommonKernelFunctors::Bounded_side_2;
  using CommonKernelFunctors::Bounded_side_3;
  using CommonKernelFunctors::Compute_area_2;
  using CommonKernelFunctors::Compute_squared_area_3;
  using CommonKernelFunctors::Compute_squared_distance_2;
  using CommonKernelFunctors::Compute_squared_distance_3;
  using CommonKernelFunctors::Compute_squared_length_2;
  using CommonKernelFunctors::Compute_squared_length_3;
  using CommonKernelFunctors::Compute_volume_3;
  using CommonKernelFunctors::Construct_center_2;
  using CommonKernelFunctors::Construct_center_3;
  using CommonKernelFunctors::Construct_circle_2;
  using CommonKernelFunctors::Construct_direction_2;
  using CommonKernelFunctors::Construct_direction_3;
  using CommonKernelFunctors::Construct_iso_cuboid_3;
  using CommonKernelFunctors::Construct_iso_rectangle_2;
  using CommonKernelFunctors::Construct_object_2;
  using CommonKernelFunctors::Construct_object_3;
  using CommonKernelFunctors::Construct_opposite_circle_2;
  using CommonKernelFunctors::Construct_opposite_direction_2;
  using CommonKernelFunctors::Construct_opposite_direction_3;
  using CommonKernelFunctors::Construct_opposite_line_2;
  using CommonKernelFunctors::Construct_opposite_line_3;
  using CommonKernelFunctors::Construct_opposite_plane_3;
  using CommonKernelFunctors::Construct_opposite_ray_2;
  using CommonKernelFunctors::Construct_opposite_ray_3;
  using CommonKernelFunctors::Construct_opposite_segment_2;
  using CommonKernelFunctors::Construct_opposite_segment_3;
  using CommonKernelFunctors::Construct_opposite_sphere_3;
  using CommonKernelFunctors::Construct_opposite_triangle_2;
  using CommonKernelFunctors::Construct_orthogonal_vector_3;
  using CommonKernelFunctors::Construct_perpendicular_direction_2;
  using CommonKernelFunctors::Construct_perpendicular_line_2;
  using CommonKernelFunctors::Construct_perpendicular_line_3;
  using CommonKernelFunctors::Construct_perpendicular_plane_3;
  using CommonKernelFunctors::Construct_perpendicular_vector_2;
  using CommonKernelFunctors::Construct_plane_3;
  using CommonKernelFunctors::Construct_point_on_2;
  using CommonKernelFunctors::Construct_point_on_3;
  using CommonKernelFunctors::Construct_point_2;
  using CommonKernelFunctors::Construct_point_3;
  using CommonKernelFunctors::Construct_projected_point_2;
  using CommonKernelFunctors::Construct_projected_point_3;
  using CommonKernelFunctors::Construct_projected_xy_point_2;
  using CommonKernelFunctors::Construct_ray_2;
  using CommonKernelFunctors::Construct_ray_3;
  using CommonKernelFunctors::Construct_segment_2;
  using CommonKernelFunctors::Construct_segment_3;
  using CommonKernelFunctors::Construct_sphere_3;
  using CommonKernelFunctors::Construct_supporting_line_2;
  using CommonKernelFunctors::Construct_supporting_line_3;
  using CommonKernelFunctors::Construct_supporting_plane_3;
  using CommonKernelFunctors::Construct_tetrahedron_3;
  using CommonKernelFunctors::Construct_triangle_2;
  using CommonKernelFunctors::Construct_triangle_3;
  using CommonKernelFunctors::Construct_vertex_2;
  using CommonKernelFunctors::Construct_vertex_3;
  using CommonKernelFunctors::Construct_bbox_2;
  using CommonKernelFunctors::Construct_bbox_3;
  using CommonKernelFunctors::Construct_cartesian_const_iterator_2;
  using CommonKernelFunctors::Construct_cartesian_const_iterator_3;
  using CommonKernelFunctors::Counterclockwise_in_between_2;
  using CommonKernelFunctors::Do_intersect_2;
  using CommonKernelFunctors::Do_intersect_3;
  using CommonKernelFunctors::Equal_2;
  using CommonKernelFunctors::Equal_3;
  using CommonKernelFunctors::Has_on_boundary_2;
  using CommonKernelFunctors::Has_on_boundary_3;
  using CommonKernelFunctors::Has_on_bounded_side_2;
  using CommonKernelFunctors::Has_on_bounded_side_3;
  using CommonKernelFunctors::Has_on_negative_side_2;
  using CommonKernelFunctors::Has_on_negative_side_3;
  using CommonKernelFunctors::Has_on_positive_side_2;
  using CommonKernelFunctors::Has_on_positive_side_3;
  using CommonKernelFunctors::Has_on_unbounded_side_2;
  using CommonKernelFunctors::Has_on_unbounded_side_3;
  using CommonKernelFunctors::Has_on_2;
  using CommonKernelFunctors::Has_on_3;
  using CommonKernelFunctors::Intersect_2;
  using CommonKernelFunctors::Intersect_3;
  using CommonKernelFunctors::Is_degenerate_2;
  using CommonKernelFunctors::Is_degenerate_3;
  using CommonKernelFunctors::Is_horizontal_2;
  using CommonKernelFunctors::Is_vertical_2;
  using CommonKernelFunctors::Left_turn_2;
  using CommonKernelFunctors::Less_rotate_ccw_2;
  using CommonKernelFunctors::Oriented_side_2;
  using CommonKernelFunctors::Oriented_side_3;
#ifndef CGAL_NO_DEPRECATED_CODE
  using CommonKernelFunctors::Equal_xy_2;
  using CommonKernelFunctors::Leftturn_2;
  using CommonKernelFunctors::Equal_xyz_3;
  using CommonKernelFunctors::Construct_direction_of_line_2;
  using CommonKernelFunctors::Construct_direction_of_ray_2;
  using CommonKernelFunctors::Construct_direction_of_line_3;
  using CommonKernelFunctors::Construct_direction_of_ray_3;
  using CommonKernelFunctors::Construct_max_point_2;
  using CommonKernelFunctors::Construct_max_point_3;
  using CommonKernelFunctors::Construct_min_point_2;
  using CommonKernelFunctors::Construct_min_point_3;
  using CommonKernelFunctors::Construct_source_point_2;
  using CommonKernelFunctors::Construct_source_point_3;
  using CommonKernelFunctors::Construct_target_point_2;
  using CommonKernelFunctors::Construct_target_point_3;
  using CommonKernelFunctors::Construct_second_point_on_2;
  using CommonKernelFunctors::Construct_second_point_on_3;
  using CommonKernelFunctors::Transform_2;
  using CommonKernelFunctors::Transform_3;
  using CommonKernelFunctors::Construct_aff_transformation_2;
  using CommonKernelFunctors::Construct_aff_transformation_3;
  using CommonKernelFunctors::Compute_y_at_x_2;
#endif
#endif

  template <typename K>
  class Angle_2
  {
    typedef typename K::Point_2             Point_2;
    typedef typename K::Construct_vector_2  Construct_vector_2;
    Construct_vector_2 c;
  public:
    typedef Angle            result_type;
    typedef Arity_tag< 3 >   Arity;
  
    Angle_2() {}
    Angle_2(const Construct_vector_2& c_) : c(c_) {}

    Angle
    operator()(const Point_2& p, const Point_2& q, const Point_2& r) const
    { return (Angle) CGAL_NTS sign(c(q,p) * c(q,r)); } 
    // FIXME: scalar product
  };

  template <typename K>
  class Angle_3
  {
    typedef typename K::Point_3             Point_3;
    typedef typename K::Construct_vector_3  Construct_vector_3;
    Construct_vector_3 c;
  public:
    typedef Angle            result_type;
    typedef Arity_tag< 3 >   Arity;

    Angle_3() {}
    Angle_3(const Construct_vector_3& c_) : c(c_) {}

    Angle
    operator()(const Point_3& p, const Point_3& q, const Point_3& r) const
    { return (Angle) CGAL_NTS sign(c(q,p) * c(q,r)); } 
    // FIXME: scalar product
  };

  template <typename K>
  class Collinear_are_ordered_along_line_2
  {
    typedef typename K::RT              RT;
    typedef typename K::Point_2         Point_2;
#ifdef CGAL_kernel_exactness_preconditions 
    typedef typename K::Collinear_2 Collinear_2;
    Collinear_2 c;
#endif // CGAL_kernel_exactness_preconditions 
  public:
    typedef bool             result_type;
    typedef Arity_tag< 3 >   Arity;

#ifdef CGAL_kernel_exactness_preconditions 
    Collinear_are_ordered_along_line_2() {}
    Collinear_are_ordered_along_line_2(const Collinear_2& c_) : c(c_) {}
#endif // CGAL_kernel_exactness_preconditions 

    bool
    operator()(const Point_2& p, const Point_2& q, const Point_2& r) const
    {
      CGAL_kernel_exactness_precondition( c(p, q, r) );

      const RT& phx = p.hx();
      const RT& phy = p.hy();
      const RT& phw = p.hw();
      const RT& qhx = q.hx();
      const RT& qhy = q.hy();
      const RT& qhw = q.hw();
      const RT& rhx = r.hx();
      const RT& rhy = r.hy();
      const RT& rhw = r.hw();

      if ( !(phx * rhw == rhx * phw ) )          // non-vertical ?
	{
	  return !( (  ( phx * qhw < qhx * phw)
		       &&( rhx * qhw < qhx * rhw))
		    ||(  ( qhx * phw < phx * qhw)
			 &&( qhx * rhw < rhx * qhw)) );
	}
      else if ( !(phy * rhw == rhy * phw ) )
	{
	  return !( (  ( phy * qhw < qhy * phw)
		       &&( rhy * qhw < qhy * rhw))
		    ||(  ( qhy * phw < phy * qhw)
			 &&( qhy * rhw < rhy * qhw)) );
	}
      else
	return (( phx*qhw == qhx*phw) && ( phy*qhw == qhy*phw));
    }
  };

  template <typename K>
  class Collinear_are_ordered_along_line_3
  {
    typedef typename K::Point_3         Point_3;
#ifdef CGAL_kernel_exactness_preconditions 
    typedef typename K::Collinear_3 Collinear_3;
    Collinear_3 c;
#endif // CGAL_kernel_exactness_preconditions 
  public:
    typedef bool             result_type;
    typedef Arity_tag< 3 >   Arity;

#ifdef CGAL_kernel_exactness_preconditions 
    Collinear_are_ordered_along_line_3() {}
    Collinear_are_ordered_along_line_3(const Collinear_3& c_) : c(c_) {}
#endif // CGAL_kernel_exactness_preconditions 

    bool
    operator()(const Point_3& p, const Point_3& q, const Point_3& r) const
    {
      CGAL_kernel_exactness_precondition( c(p, q, r) );
      typedef typename K::RT RT;
      const RT phx = p.hx();
      const RT phw = p.hw();
      const RT qhx = q.hx();
      const RT qhw = q.hw();
      const RT rhx = r.hx();
      const RT rhw = r.hw();

      const RT pqx = phx*qhw;
      const RT qpx = qhx*phw;
      const RT prx = phx*rhw;
      const RT qrx = qhx*rhw;
      const RT rqx = rhx*qhw;
      const RT rpx = rhx*phw;

      if ( prx != rpx )   // px != rx
	{
	  //    (px <= qx)&&(qx <= rx) || (px >= qx)&&(qx >= rx)
	  // !(((qx <  px)||(rx <  qx))&&((px <  qx)||(qx <  rx)))
	  return ! (   ((qpx < pqx) || (rqx < qrx))
		       && ((pqx < qpx) || (qrx < rqx))  );
	}

      const RT phy = p.hy();
      const RT qhy = q.hy();
      const RT rhy = r.hy();

      const RT pqy = phy*qhw;
      const RT qpy = qhy*phw;
      const RT pry = phy*rhw;
      const RT qry = qhy*rhw;
      const RT rqy = rhy*qhw;
      const RT rpy = rhy*phw;

      if ( pry != rpy )
	{
	  return ! (   ((qpy < pqy) || (rqy < qry))
		       && ((pqy < qpy) || (qry < rqy))  );
	}

      const RT phz = p.hz();
      const RT qhz = q.hz();
      const RT rhz = r.hz();

      const RT pqz = phz*qhw;
      const RT qpz = qhz*phw;
      const RT prz = phz*rhw;
      const RT qrz = qhz*rhw;
      const RT rqz = rhz*qhw;
      const RT rpz = rhz*phw;

      if ( prz != rpz )
	{
	  return ! (   ((qpz < pqz) || (rqz < qrz))
		       && ((pqz < qpz) || (qrz < rqz))  );
	}
      // p == r
      return  ((rqx == qrx) && (rqy == qry) && (rqz == qrz));
    }  
  };

  template <typename K>
  class Collinear_are_strictly_ordered_along_line_2
  {
    typedef typename K::Point_2         Point_2;
#ifdef CGAL_kernel_exactness_preconditions 
    typedef typename K::Collinear_2 Collinear_2;
    Collinear_2 c;
#endif // CGAL_kernel_exactness_preconditions 
  public:
    typedef bool             result_type;
    typedef Arity_tag< 3 >   Arity;

#ifdef CGAL_kernel_exactness_preconditions 
    Collinear_are_strictly_ordered_along_line_2() {}
    Collinear_are_strictly_ordered_along_line_2(const Collinear_2& c_) : c(c_) 
    {}
#endif // CGAL_kernel_exactness_preconditions 

    bool
    operator()(const Point_2& p, const Point_2& q, const Point_2& r) const
    {
      CGAL_kernel_exactness_precondition( c(p, q, r) );
      typedef typename K::RT RT;

      const RT& phx = p.hx();
      const RT& phy = p.hy();
      const RT& phw = p.hw();
      const RT& qhx = q.hx();
      const RT& qhy = q.hy();
      const RT& qhw = q.hw();
      const RT& rhx = r.hx();
      const RT& rhy = r.hy();
      const RT& rhw = r.hw();

      if ( !(phx * rhw == rhx * phw ) )
	{
	  return (   ( phx * qhw < qhx * phw)
		     &&( qhx * rhw < rhx * qhw))
	    ||(   ( qhx * phw < phx * qhw)    // ( phx * qhw > qhx * phw)
		  &&( rhx * qhw < qhx * rhw));  // ( qhx * rhw > rhx * qhw)
	}
      else
	{
	  return (   ( phy * qhw < qhy * phw)
		     &&( qhy * rhw < rhy * qhw))
	    ||(   ( qhy * phw < phy * qhw)    // ( phy * qhw > qhy * phw)
		  &&( rhy * qhw < qhy * rhw));  // ( qhy * rhw > rhy * qhw)
	}
    }
  };

  template <typename K>
  class Collinear_are_strictly_ordered_along_line_3
  {
    typedef typename K::Point_3         Point_3;
    typedef typename K::Direction_3     Direction_3;
#ifdef CGAL_kernel_exactness_preconditions 
    typedef typename K::Collinear_3 Collinear_3;
    Collinear_3 c;
#endif // CGAL_kernel_exactness_preconditions 
  public:
    typedef bool             result_type;
    typedef Arity_tag< 3 >   Arity;

#ifdef CGAL_kernel_exactness_preconditions 
    Collinear_are_strictly_ordered_along_line_3() {}
    Collinear_are_strictly_ordered_along_line_3(const Collinear_3& c_) : c(c_)
    {}
#endif // CGAL_kernel_exactness_preconditions 

    bool
    operator()(const Point_3& p, const Point_3& q, const Point_3& r) const
    {
      CGAL_kernel_exactness_precondition( c(p, q, r) );
      if ( p == r) return false;
      Direction_3 dir_pq = (p - q).direction();
      Direction_3 dir_rq = (r - q).direction();
      return (dir_pq == -dir_rq);
    }  // FIXME
  };

  template <typename K>
  class Collinear_has_on_2
  {
    typedef typename K::Point_2               Point_2;
    typedef typename K::Direction_2           Direction_2;
    typedef typename K::Ray_2                 Ray_2;
    typedef typename K::Segment_2             Segment_2;
    typedef typename K::Construct_point_on_2  Construct_point_on_2;
    typedef typename K::Compare_xy_2          Compare_xy_2;
    Construct_point_on_2 cp;
    Compare_xy_2 cxy;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    Collinear_has_on_2() {}
    Collinear_has_on_2(const Construct_point_on_2& cp_,
		       const Compare_xy_2& cxy_)
      : cp(cp_), cxy(cxy_)
    {}

    bool
    operator()( const Ray_2& r, const Point_2& p) const
    {
      Point_2 source = cp(r,0);      
      return p == source || Direction_2(p - source) == r.direction();
    } // FIXME
  
    bool
    operator()( const Segment_2& s, const Point_2& p) const
    { 
      return cxy(p, cp(s,1)) != LARGER && cxy(cp(s,0), p) != LARGER;
    }
  };

  template <typename K>
  class Collinear_2
  {
    typedef typename K::Point_2        Point_2;
    typedef typename K::Orientation_2  Orientation_2;
    Orientation_2 o;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 3 >   Arity;

    Collinear_2() {}
    Collinear_2(const Orientation_2 o_) : o(o_) {}

    bool
    operator()(const Point_2& p, const Point_2& q, const Point_2& r) const
    {
      typedef typename K::RT RT;

      const RT& phx = p.hx();
      const RT& phy = p.hy();
      const RT& phw = p.hw();
      const RT& qhx = q.hx();
      const RT& qhy = q.hy();
      const RT& qhw = q.hw();
      const RT& rhx = r.hx();
      const RT& rhy = r.hy();
      const RT& rhw = r.hw();
      const RT  RT0 = RT(0);

      // | A B |
      // | C D |

      RT  A = phx*rhw - phw*rhx;
      RT  B = phy*rhw - phw*rhy;
      RT  C = qhx*rhw - qhw*rhx;
      RT  D = qhy*rhw - qhw*rhy;

      RT  det =  A*D - B*C;

      /*
	RT det_old =   p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
	+ p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
	+ p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );
	
	if ( !(CGAL_NTS sign(det) == CGAL_NTS sign(det_old)) )
	{
	std::cerr << "det: " << det << " det_old: " << det_old << flush;
	}
      */
      
      return ( det == RT0 );
    }
  };

  template <typename K>
  class Collinear_3
  {
    typedef typename K::Point_3      Point_3;
    typedef typename K::Direction_3  Direction_3;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 3 >   Arity;

    bool
    operator()(const Point_3& p, const Point_3& q, const Point_3& r) const
    {
      Direction_3 dir_pq = (p - q).direction();
      Direction_3 dir_rq = (r - q).direction();
      
      return ( dir_pq == dir_rq ) || (dir_pq == -dir_rq)
	|| ( p == q ) || ( p == r ) || ( q == r ) ;
    } // FIXME
  };

  template <typename K>
  class Compare_angle_with_x_axis_2
  {
    typedef typename K::Point_2      Point_2;
    typedef typename K::Vector_2     Vector_2;
    typedef typename K::Direction_2  Direction_2;
  public:
    typedef Comparison_result        result_type;
    typedef Arity_tag< 2 >           Arity;

    Comparison_result
    operator()(const Direction_2& d1, const Direction_2& d2) const
    {
      typedef typename K::RT  RT;
      CGAL_kernel_precondition(
          static_cast<int>(COUNTERCLOCKWISE) == static_cast<int>(LARGER)
       && static_cast<int>(COLLINEAR)        == static_cast<int>(EQUAL)
       && static_cast<int>(CLOCKWISE)        == static_cast<int>(SMALLER) );

      const RT RT0(0);

      Vector_2 dirvec1(d1.x(), d1.y());      // Added
      Point_2   p1 = CGAL::ORIGIN + dirvec1; // Added
      Vector_2 dirvec2(d2.x(), d2.y());      // Added
      Point_2   p2 = ORIGIN + dirvec2;       // Added
      //  Point_2   p1 = ORIGIN + d1.vector(); // Commented out
      //  Point_2   p2 = ORIGIN + d2.vector(); // Commented out

      CGAL_kernel_precondition( RT0 < p1.hw() );
      CGAL_kernel_precondition( RT0 < p2.hw() );

      int       x_sign1 = static_cast<int>(CGAL_NTS sign( p1.hx() ));
      int       x_sign2 = static_cast<int>(CGAL_NTS sign( p2.hx() ));
      int       y_sign1 = static_cast<int>(CGAL_NTS sign( p1.hy() ));
      int       y_sign2 = static_cast<int>(CGAL_NTS sign( p2.hy() ));

      if ( y_sign1 * y_sign2 < 0)
	{
	  return (0 < y_sign1 ) ? SMALLER : LARGER;
	}

      Point_2   origin( RT0  , RT0   );

      if ( 0 < y_sign1 * y_sign2 )
	{
	  return static_cast<Comparison_result>(static_cast<int>(
			 orientation(origin, p2, p1)));

	  // Precondition on the enums:
	  // COUNTERCLOCKWISE == LARGER   ( ==  1 )
	  // COLLINEAR        == EQUAL    ( ==  0 )
	  // CLOCKWISE        == SMALLER  ( == -1 )
	}
      
      // ( y_sign1 * y_sign2 == 0 )
      
      bool b1 = (y_sign1 == 0) && (x_sign1 >= 0);
      bool b2 = (y_sign2 == 0) && (x_sign2 >= 0);
      
      if ( b1 ) { return  b2 ? EQUAL : SMALLER; }
      if ( b2 ) { return  b1 ? EQUAL : LARGER; }
      if ( y_sign1 == y_sign2 )  // == 0
	{
	  return EQUAL;
	}
      else
	{
	  return (orientation(origin, p1, p2) == COUNTERCLOCKWISE) ?
	    static_cast<Comparison_result>(SMALLER) :
	    static_cast<Comparison_result>(LARGER);
	}
    }
  };

  template <typename K>
  class Compare_distance_2
  {
    typedef typename K::Point_2   Point_2;
  public:
    typedef Comparison_result     result_type;
    typedef Arity_tag< 3 >        Arity;

    Comparison_result
    operator()(const Point_2& p, const Point_2& q, const Point_2& r) const
    {
      typedef typename K::RT RT;

      const RT phx = p.hx();
      const RT phy = p.hy();
      const RT phw = p.hw();
      const RT qhx = q.hx();
      const RT qhy = q.hy();
      const RT qhw = q.hw();
      const RT rhx = r.hx();
      const RT rhy = r.hy();
      const RT rhw = r.hw();
      const RT RT0 = RT(0);
      const RT RT2 = RT(2);

      RT dosd =   // difference of squared distances

	//            phx * phx   *   qhw * qhw * rhw * rhw
	//   -RT(2) * phx * qhx   *   phw * qhw * rhw * rhw
	//   +        qhx * qhx   *   phw * phw * rhw * rhw
	//
	//   +        phy * phy   *   qhw * qhw * rhw * rhw
	//   -RT(2) * phy * qhy   *   phw * qhw * rhw * rhw
	//   +        qhy * qhy   *   phw * phw * rhw * rhw
	//
	// - (        phx * phx   *   qhw * qhw * rhw * rhw
	//   -RT(2) * phx * rhx   *   phw * qhw * qhw * rhw
	//   +        rhx * rhx   *   phw * phw * qhw * qhw
	//
	//   +        phy * phy   *   qhw * qhw * rhw * rhw
	//   -RT(2) * phy * rhy   *   phw * qhw * qhw * rhw
	//   +        rhy * rhy   *   phw * phw * qhw * qhw
	
	rhw*rhw * (         phw * ( qhx*qhx + qhy*qhy )
			    - RT2 * qhw * ( phx*qhx + phy*qhy )
			    )
	- qhw*qhw * (         phw * ( rhx*rhx + rhy*rhy )
			      - RT2 * rhw * ( phx*rhx + phy*rhy )
			      );


      if ( RT0 < dosd )
	{
	  return LARGER;
	}
      else
	{
	  return (dosd < RT0) ? SMALLER : EQUAL;
	}
    }
  };

  template <typename K>
  class Compare_distance_3
  {
    typedef typename K::Point_3   Point_3;
  public:
    typedef Comparison_result     result_type;
    typedef Arity_tag< 3 >        Arity;

    Comparison_result
    operator()(const Point_3& p, const Point_3& q, const Point_3& r) const
    { 
      typedef typename K::RT RT;

      const RT phx = p.hx();
      const RT phy = p.hy();
      const RT phz = p.hz();
      const RT phw = p.hw();
      const RT qhx = q.hx();
      const RT qhy = q.hy();
      const RT qhz = q.hz();
      const RT qhw = q.hw();
      const RT rhx = r.hx();
      const RT rhy = r.hy();
      const RT rhz = r.hz();
      const RT rhw = r.hw();
      const RT RT0 = RT(0);
      const RT RT2 = RT(2);

      RT dosd =   // difference of squared distances

	rhw*rhw * (         phw * ( qhx*qhx + qhy*qhy + qhz*qhz )
			    - RT2 * qhw * ( phx*qhx + phy*qhy + phz*qhz )
			    )
	- qhw*qhw * (         phw * ( rhx*rhx + rhy*rhy + rhz*rhz )
			      - RT2 * rhw * ( phx*rhx + phy*rhy + phz*rhz )
			      );

      if ( RT0 < dosd )
	{ return LARGER; }
      else
	{ return (dosd < RT0) ? SMALLER : EQUAL; }
    }
  };

  template <typename K>
  class Compare_slope_2
  {
    typedef typename K::Line_2     Line_2;
    typedef typename K::Segment_2  Segment_2;
  public:
    typedef Comparison_result      result_type;
    typedef Arity_tag< 2 >         Arity;

    Comparison_result
    operator()(const Line_2& l1, const Line_2& l2) const
    { 
      typedef typename K::RT RT;
      if (l1.is_horizontal())
	return l2.is_vertical() ? 
	  SMALLER : Comparison_result(CGAL_NTS sign<RT>(l2.a() * l2.b()));
      if (l2.is_horizontal()) 
	return l1.is_vertical() ? 
	  LARGER : Comparison_result(- CGAL_NTS sign<RT>(l1.a() * l1.b()));
      if (l1.is_vertical()) return l2.is_vertical() ? EQUAL : LARGER;
      if (l2.is_vertical()) return SMALLER;
      int l1_sign = CGAL_NTS sign<RT>(-l1.a() * l1.b());
      int l2_sign = CGAL_NTS sign<RT>(-l2.a() * l2.b());

      if (l1_sign < l2_sign) return SMALLER;
      if (l1_sign > l2_sign) return LARGER;

      if (l1_sign > 0)
	return CGAL_NTS compare( CGAL_NTS abs<RT>(l1.a() * l2.b()),
				 CGAL_NTS abs<RT>(l2.a() * l1.b()) );

      return CGAL_NTS compare( CGAL_NTS abs<RT>(l2.a() * l1.b()),
			       CGAL_NTS abs<RT>(l1.a() * l2.b()) );
    } // FIXME

    Comparison_result
    operator()(const Segment_2& s1, const Segment_2& s2) const
    {  
      typedef typename K::FT        FT;

      Comparison_result cmp_y1 = compare_y(s1.source(), s1.target());
      if (cmp_y1 == EQUAL) // horizontal
	{
	  Comparison_result cmp_x2 = compare_x(s2.source(), s2.target());

	  if (cmp_x2 == EQUAL) return SMALLER;
	  FT s_hw = s2.source().hw();
	  FT t_hw = s2.target().hw();
	  return Comparison_result (
	    - CGAL_NTS sign((s2.source().hy()*t_hw - s2.target().hy()*s_hw) *
			    (s2.source().hx()*t_hw - s2.target().hx()*s_hw)) );
	}

      Comparison_result cmp_y2 = compare_y(s2.source(), s2.target());
      if (cmp_y2 == EQUAL)
	{
	  Comparison_result cmp_x1 = compare_x(s1.source(), s1.target());

	  if (cmp_x1 == EQUAL) return LARGER;
	  FT s_hw = s1.source().hw();
	  FT t_hw = s1.target().hw();
	  return Comparison_result (
	    CGAL_NTS sign((s1.source().hy()*t_hw - s1.target().hy()*s_hw) *
			  (s1.source().hx()*t_hw - s1.target().hx()*s_hw)) );
	}

      Comparison_result cmp_x1 = compare_x(s1.source(), s1.target());
      Comparison_result cmp_x2 = compare_x(s2.source(), s2.target());
      if (cmp_x1 == EQUAL)
	return cmp_x2 == EQUAL ? EQUAL : LARGER;

      if (cmp_x2 == EQUAL) return SMALLER;

      FT s1_s_hw = s1.source().hw();
      FT s1_t_hw = s1.target().hw();
      FT s2_s_hw = s2.source().hw();
      FT s2_t_hw = s2.target().hw();
      FT s1_xdiff = s1.source().hx()*s1_t_hw - s1.target().hx()*s1_s_hw;
      FT s1_ydiff = s1.source().hy()*s1_t_hw - s1.target().hy()*s1_s_hw;
      FT s2_xdiff = s2.source().hx()*s2_t_hw - s2.target().hx()*s2_s_hw;
      FT s2_ydiff = s2.source().hy()*s2_t_hw - s2.target().hy()*s2_s_hw;
      Sign s1_sign = CGAL_NTS sign(s1_ydiff * s1_xdiff);
      Sign s2_sign = CGAL_NTS sign(s2_ydiff * s2_xdiff);
 
      if (s1_sign < s2_sign) return SMALLER;
      if (s1_sign > s2_sign) return LARGER;

      if (s1_sign > 0)
	return Comparison_result(
	 CGAL_NTS sign ( CGAL_NTS abs(s1_ydiff * s2_xdiff) -
			 CGAL_NTS abs(s2_ydiff * s1_xdiff)) );

      return Comparison_result(
       CGAL_NTS sign ( CGAL_NTS abs(s2_ydiff * s1_xdiff) -
		       CGAL_NTS abs(s1_ydiff * s2_xdiff)) );
    }
  };

  template <typename K>
  class Compare_x_at_y_2
  {
    typedef typename K::Point_2    Point_2;
    typedef typename K::Line_2     Line_2;
  public:
    typedef Comparison_result      result_type;
    typedef Arity_tag< 3 >         Arity;

    Comparison_result
    operator()( const Point_2& p, const Line_2& h) const
    { 
      typedef typename K::RT RT;
      CGAL_kernel_precondition( ! h.is_horizontal() );
      Oriented_side ors = h.oriented_side( p );
      if ( h.a() < RT(0) )
	{
	  ors = opposite( ors );
	}
      if ( ors == ON_POSITIVE_SIDE )
	{
	  return LARGER;
	}
      return ( ors == ON_NEGATIVE_SIDE ) ? SMALLER : EQUAL;
    } // FIXME

    Comparison_result
    operator()( const Point_2& p, const Line_2& h1, const Line_2& h2) const
    { return CGAL_NTS compare(h1.x_at_y( p.y() ), h2.x_at_y( p.y() )); }
    // FIXME

    Comparison_result
    operator()( const Line_2& l1, const Line_2& l2, const Line_2& h) const
    { return compare_x_at_y( gp_linear_intersection( l1, l2 ), h); }
    // FIXME

    Comparison_result
    operator()( const Line_2& l1, const Line_2& l2,
	        const Line_2& h1, const Line_2& h2) const
    { return compare_x_at_y( gp_linear_intersection( l1, l2 ), h1, h2 ); }
    // FIXME
  };

  template <typename K>
  class Compare_xyz_3
  {
    typedef typename K::Point_3    Point_3;
  public:
    typedef Comparison_result  result_type;
    typedef Arity_tag< 2 >     Arity;

    Comparison_result
    operator()( const Point_3& p, const Point_3& q) const
    { 
      typedef typename K::RT RT;
      RT pV = p.hx()*q.hw();
      RT qV = q.hx()*p.hw();
      if ( pV < qV )
	{
	  return SMALLER;
	}
      if ( qV < pV )    //   ( pV > qV )
	{
	  return LARGER;
	}
      // same x
      pV = p.hy()*q.hw();
      qV = q.hy()*p.hw();
      if ( pV < qV )
	{
	  return SMALLER;
	}
      if ( qV < pV )    //   ( pV > qV )
	{
	  return LARGER;
	}
      // same x and y
      pV = p.hz()*q.hw();
      qV = q.hz()*p.hw();
      if ( pV < qV )
	{
	  return SMALLER;
	}
      else
	{
	  return (qV < pV) ? LARGER : EQUAL;
	}
    }
  };

  template <typename K>
  class Compare_xy_2
  {
    typedef typename K::Point_2    Point_2;
  public:
    typedef Comparison_result  result_type;
    typedef Arity_tag< 2 >     Arity;

    Comparison_result
    operator()( const Point_2& p, const Point_2& q) const
    { 
      typedef typename K::RT RT;

      const RT& phx = p.hx();
      const RT& phy = p.hy();
      const RT& phw = p.hw();
      const RT& qhx = q.hx();
      const RT& qhy = q.hy();
      const RT& qhw = q.hw();

      RT pV = phx*qhw;
      RT qV = qhx*phw;
      if ( pV == qV )
	{
	  pV = phy*qhw;
	  qV = qhy*phw;
	}
      if ( pV < qV )
	{
	  return SMALLER;
	}
      else
	{
	  return (qV < pV) ? LARGER : EQUAL;
	}
    }
  };

  template <typename K>
  class Compare_xy_3
  {
    typedef typename K::Point_3    Point_3;
  public:
    typedef Comparison_result  result_type;
    typedef Arity_tag< 2 >     Arity;

    Comparison_result
    operator()( const Point_3& p, const Point_3& q) const
    { 
      typedef typename K::RT RT;
      RT pV = p.hx()*q.hw();
      RT qV = q.hx()*p.hw();
      if ( pV < qV )
	{
	  return SMALLER;
	}
      if ( qV < pV )    //   ( pV > qV )
	{
	  return LARGER;
	}
      // same x
      pV = p.hy()*q.hw();
      qV = q.hy()*p.hw();
      if ( pV < qV )
	{
	  return SMALLER;
	}
      if ( qV < pV )    //   ( pV > qV )
	{
	  return LARGER;
	}
      // same x and y
      return EQUAL;
    }
  };

  template <typename K>
  class Compare_x_2
  {
    typedef typename K::Point_2    Point_2;
    typedef typename K::Line_2     Line_2;
  public:
    typedef Comparison_result      result_type;
    typedef Arity_tag< 2 >         Arity;

    Comparison_result
    operator()( const Point_2& p, const Point_2& q) const
    {
      return (Comparison_result) CGAL_NTS sign(p.hx()*q.hw() - q.hx()*p.hw());
    }

    Comparison_result
    operator()( const Point_2& p, const Line_2& l1, const Line_2& l2) const
    {
      Point_2 ip = gp_linear_intersection( l1, l2 );
      return compare_x( p, ip );
    } // FIXME

    Comparison_result
    operator()( const Line_2& l, const Line_2& h1, const Line_2& h2) const
    {
      return compare_x(l, h1, l, h2);
    } // FIXME

    Comparison_result
    operator()( const Line_2& l1, const Line_2& l2,
	        const Line_2& h1, const Line_2& h2) const
    { 
      Point_2 lip = gp_linear_intersection( l1, l2 );
      Point_2 hip = gp_linear_intersection( h1, h2 );
      return compare_x( lip, hip );
    } // FIXME
  };

  template <typename K>
  class Compare_x_3
  {
    typedef typename K::Point_3    Point_3;
  public:
    typedef Comparison_result      result_type;
    typedef Arity_tag< 2 >         Arity;

    Comparison_result
    operator()( const Point_3& p, const Point_3& q) const
    { return CGAL_NTS compare(p.hx() * q.hw(), q.hx() * p.hw() ); }
  };

  template <typename K>
  class Compare_y_at_x_2
  {
    typedef typename K::Point_2    Point_2;
    typedef typename K::Line_2     Line_2;
    typedef typename K::Segment_2  Segment_2;
  public:
    typedef Comparison_result      result_type;
    typedef Arity_tag< 3 >         Arity;

    Comparison_result
    operator()( const Point_2& p, const Line_2& h) const
    { 
      typedef typename K::RT RT;
      CGAL_kernel_precondition( ! h.is_vertical() );
      Oriented_side ors = h.oriented_side( p );
      if ( h.b() < RT(0) )
	{
	  ors = opposite( ors );
	}
      if ( ors == ON_POSITIVE_SIDE )
	{
	  return LARGER;
	}
      return ( ors == ON_NEGATIVE_SIDE ) ? SMALLER : EQUAL;
    } // FIXME
  
    Comparison_result
    operator()( const Point_2& p, const Line_2& h1, const Line_2& h2) const
    { return CGAL_NTS compare(h1.y_at_x( p.x() ), h2.y_at_x( p.x() )); }
    // FIXME

    Comparison_result
    operator()( const Line_2& l1, const Line_2& l2, const Line_2& h) const
    { return compare_y_at_x( gp_linear_intersection( l1, l2 ), h); }
    // FIXME

    Comparison_result
    operator()( const Line_2& l1, const Line_2& l2,
	        const Line_2& h1, const Line_2& h2) const
    { return compare_y_at_x( gp_linear_intersection( l1, l2 ), h1, h2 ); }
    // FIXME

    Comparison_result
    operator()( const Point_2& p, const Segment_2& s) const
    {
      // compares the y-coordinates of p and the vertical projection of p on s.
      // Precondition : p is in the x-range of s.

      if (compare_x(s.source(), s.target()) == SMALLER) {
        CGAL_kernel_precondition(compare_x(s.source(), p) != LARGER
				 && compare_x(p, s.target()) != LARGER);
        return (Comparison_result) orientation(p, s.source(), s.target());
      }
      else if (compare_x(s.source(), s.target()) == LARGER) {
        CGAL_kernel_precondition(compare_x(s.target(), p) != LARGER
				 && compare_x(p, s.source()) != LARGER);
        return (Comparison_result) orientation(p, s.target(), s.source());
      }
      else {
        CGAL_kernel_precondition(compare_x(s.target(), p) == EQUAL);
	if (compare_y(p, s.source()) == SMALLER &&
	    compare_y(p, s.target()) == SMALLER)
	  return SMALLER;
	if (compare_y(p, s.source()) == LARGER &&
	    compare_y(p, s.target()) == LARGER)
	  return LARGER;
	return EQUAL;
      }
    } // FIXME

    Comparison_result
    operator()( const Point_2& p,
	        const Segment_2& s1, const Segment_2& s2) const
    {
      // compares the y-coordinates of the vertical projections 
      //   of p on s1 and s2
      // Precondition : p is in the x-range of s1 and s2.
      // - if one or two segments are vertical :
      //   - if the segments intersect, return EQUAL
      //   - if not, return the obvious SMALLER/LARGER.

      typedef typename K::FT FT;
      FT px = p.x();
      FT s1sx = s1.source().x();
      FT s1sy = s1.source().y();
      FT s1tx = s1.target().x();
      FT s1ty = s1.target().y();
      FT s2sx = s2.source().x();
      FT s2sy = s2.source().y();
      FT s2tx = s2.target().x();
      FT s2ty = s2.target().y();

      CGAL_kernel_precondition(px >= min(s1sx, s1tx) && px <= max(s1sx, s1tx));
      CGAL_kernel_precondition(px >= min(s2sx, s2tx) && px <= max(s2sx, s2tx));

      if (s1sx != s1tx && s2sx != s2tx) {
	FT s1stx = s1sx-s1tx;
	FT s2stx = s2sx-s2tx;

	return Comparison_result(
	 CGAL_NTS compare(s1sx, s1tx) *
	 CGAL_NTS compare(s2sx, s2tx) *
	 CGAL_NTS compare(-(s1sx-px)*(s1sy-s1ty)*s2stx,
			  (s2sy-s1sy)*s2stx*s1stx
			  -(s2sx-px)*(s2sy-s2ty)*s1stx ));
      }
      else {
	if (s1sx == s1tx) { // s1 is vertical
	  Comparison_result c1, c2;
	  c1 = compare_y_at_x(s1.source(), s2);
	  c2 = compare_y_at_x(s1.target(), s2);
	  if (c1 == c2)
	    return c1;
	  return EQUAL;
	}
	// s2 is vertical
	Comparison_result c3, c4;
	c3 = compare_y_at_x(s2.source(), s1);
	c4 = compare_y_at_x(s2.target(), s1);
	if (c3 == c4)
	  return opposite(c3);
	return EQUAL;
      }
    } // FIXME
  };

  template <typename K>
  class Compare_y_2
  {
    typedef typename K::Point_2   Point_2;
    typedef typename K::Line_2    Line_2;
  public:
    typedef Comparison_result     result_type;
    typedef Arity_tag< 2 >         Arity;

    Comparison_result
    operator()( const Point_2& p, const Point_2& q) const
    { 
      typedef typename K::RT RT;
      
      const RT& phy = p.hy();
      const RT& phw = p.hw();
      const RT& qhy = q.hy();
      const RT& qhw = q.hw();
      const RT  RT0 = RT(0);
      RT com = phy * qhw - qhy * phw;
      if ( com < RT0 )
	{
	  return SMALLER;
	}
      else if ( RT0 < com )
	{
	  return LARGER;
	}
      return EQUAL;
    }

    Comparison_result
    operator()( const Point_2& p, const Line_2& l1, const Line_2& l2) const
    { 
      Point_2 ip = gp_linear_intersection( l1, l2 );
      return compare_y( p, ip );
    } // FIXME

    Comparison_result
    operator()( const Line_2& l, const Line_2& h1, const Line_2& h2) const
    {
      return this->operator()(l, h1, l, h2);
    }

    Comparison_result
    operator()( const Line_2& l1, const Line_2& l2,
	        const Line_2& h1, const Line_2& h2) const
    {
      Point_2 lip = gp_linear_intersection( l1, l2 );
      Point_2 hip = gp_linear_intersection( h1, h2 );
      return this->operator()( lip, hip );
    } // FIXME
  };

  template <typename K>
  class Compare_y_3
  {
    typedef typename K::Point_3   Point_3;
  public:
    typedef Comparison_result     result_type;
    typedef Arity_tag< 2 >        Arity;

    Comparison_result
    operator()( const Point_3& p, const Point_3& q) const
    { return CGAL_NTS compare(p.hy() * q.hw(), q.hy() * p.hw() ); }
  };

  template <typename K>
  class Compare_z_3
  {
    typedef typename K::Point_3   Point_3;
  public:
    typedef Comparison_result     result_type;
    typedef Arity_tag< 2 >        Arity;

    Comparison_result
    operator()( const Point_3& p, const Point_3& q) const
    { return CGAL_NTS compare(p.hz() * q.hw(), q.hz() * p.hw() ); }
  };

  // TODO ...
  template <typename K>
  class Compute_squared_radius_2
  {
    typedef typename K::FT          FT;
    typedef typename K::Point_2     Point_2;
    typedef typename K::Circle_2    Circle_2;
  public:
    typedef FT               result_type;
    typedef Arity_tag< 1 >   Arity;

    FT
    operator()( const Circle_2& c) const
    { return c.squared_radius(); }

    FT
    operator()( const Point_2& p, const Point_2& q) const
    { 
      typedef typename K::FT FT;
      return squared_distance(p, q)/FT(4);
    }  // FIXME

    FT
    operator()( const Point_2& p, const Point_2& q, const Point_2& r) const
    { return squared_distance(p, circumcenter(p, q, r)); }
    // FIXME
  };

  template <typename K>
  class Compute_squared_radius_3
  {
    typedef typename K::FT          FT;
    typedef typename K::Point_3     Point_3;
    typedef typename K::Sphere_3    Sphere_3;
  public:
    typedef FT               result_type;
    typedef Arity_tag< 1 >   Arity;

    FT
    operator()( const Sphere_3& s) const
    { return s.squared_radius(); }

    FT
    operator()( const Point_3& p, const Point_3& q) const
    {
      typedef typename K::FT FT;
      return squared_distance(p, q) / FT(4);
    } // FIXME

    FT
    operator()( const Point_3& p, const Point_3& q, const Point_3& r) const
    {
      return squared_distance(p, circumcenter(p, q, r));
    } // FIXME

    FT
    operator()( const Point_3& p, const Point_3& q,
	        const Point_3& r, const Point_3& s) const
    { 
      return squared_distance(p, circumcenter(p, q, r, s));
    } // FIXME
  };

  template <typename K>
  class Construct_base_vector_3
  {
    typedef typename K::Vector_3   Vector_3;
    typedef typename K::Plane_3    Plane_3;
    typedef typename K::RT         RT;
    typedef typename K::Construct_orthogonal_vector_3 
    Construct_orthogonal_vector_3;
    Construct_orthogonal_vector_3 co;
  public:
    typedef Vector_3         result_type;
    typedef Arity_tag< 2 >   Arity;

    Construct_base_vector_3() {}
    Construct_base_vector_3(const Construct_orthogonal_vector_3& co_)
      : co(co_)
    {}
  
    Vector_3
    operator()( const Plane_3& h, int index ) const
    {
      if (index == 1) {
	// point():
	// a() != RT0 : Point_3( -d(), RT0, RT0, a() );
	// b() != RT0 : Point_3( RT0, -d(), RT0, b() );
	//            : Point_3( RT0, RT0, -d(), c() );
	// point1():
	// a() != RT0 : Point_3( -b()-d(), a(), RT0, a() );
	// b() != RT0 : Point_3( RT0, -c()-d(), b(), b() );
	//            : Point_3( c(), RT0, -a()-d(), c() );
	 
	const RT RT0(0);
	if ( h.a() != RT0 )
	  {
	    return Vector_3( -h.b(), h.a(), RT0, h.a() );
	  }
	if ( h.b() != RT0 )
	  {
	    return Vector_3( RT0, -h.c(), h.b(), h.b() );
	  }
	CGAL_kernel_assertion ( h.c() != RT(0) );
	return Vector_3( h.c(), RT0, -h.a(), h.c() );
      } else {
	Vector_3 a = co(h);
	Vector_3 b = this->operator()(h, 1);
	return Vector_3(a.hy()*b.hz() - a.hz()*b.hy(),
			a.hz()*b.hx() - a.hx()*b.hz(),
			a.hx()*b.hy() - a.hy()*b.hx(),
			a.hw()*b.hw() );
      }
    }
  };

  template <typename K>
  class Construct_bisector_2
  {
    typedef typename K::FT      FT;
    typedef typename K::Point_2 Point_2;
    typedef typename K::Line_2  Line_2;
  public:
    typedef Line_2           result_type;
    typedef Arity_tag< 2 >   Arity;

    Line_2
    operator()(const Point_2& p, const Point_2& q) const
    {
      typedef typename K::RT RT;

      // Bisector equation is based on equation
      // ( X - p.x())^2 + (Y - p.y())^2 == ( X - q.x())^2 + (Y - q.y())
      // and x() = hx()/hw() ...

      RT phx = p.hx();
      RT phy = p.hy();
      RT phw = p.hw();
      RT qhx = q.hx();
      RT qhy = q.hy();
      RT qhw = q.hw();

      RT a = RT(2) * ( qhx*qhw*phw*phw - phx*phw*qhw*qhw );
      RT b = RT(2) * ( qhy*qhw*phw*phw - phy*phw*qhw*qhw );
      RT c = phx*phx*qhw*qhw + phy*phy*qhw*qhw 
	- qhx*qhx*phw*phw - qhy*qhy*phw*phw;

      return Line_2( a, b, c );
    }
  };

  template <typename K>
  class Construct_centroid_2
  {
    typedef typename K::FT       FT;
    typedef typename K::Point_2  Point_2;
  public:
    typedef Point_2          result_type;
    typedef Arity_tag< 3 >   Arity;

    Point_2
    operator()(const Point_2& p, const Point_2& q, const Point_2& r) const
    {
      typedef typename K::RT  RT;
      const RT phw(p.hw());
      const RT qhw(q.hw());
      const RT rhw(r.hw());
      RT hx(p.hx()*qhw*rhw + q.hx()*phw*rhw + r.hx()*phw*qhw);
      RT hy(p.hy()*qhw*rhw + q.hy()*phw*rhw + r.hy()*phw*qhw);
      RT hw( phw*qhw*rhw * 3);
      return Point_2(hx, hy, hw);
    }

    Point_2
    operator()(const Point_2& p, const Point_2& q, 
               const Point_2& r, const Point_2& s) const
    {
      typedef typename K::RT  RT;
      const RT phw(p.hw());
      const RT qhw(q.hw());
      const RT rhw(r.hw());
      const RT shw(s.hw());
      RT hx(p.hx()*qhw*rhw*shw + q.hx()*phw*rhw*shw + r.hx()*phw*qhw*shw 
	    + s.hx()*phw*qhw*rhw);
      RT hy(p.hy()*qhw*rhw*shw + q.hy()*phw*rhw*shw + r.hy()*phw*qhw*shw
	    + s.hy()*phw*qhw*rhw);
      RT hw( phw*qhw*rhw*shw * 4);
      return Point_2(hx, hy, hw);
    }
  };

  template <typename K>
  class Construct_centroid_3
  {
    typedef typename K::FT       FT;
    typedef typename K::Point_3  Point_3;
  public:
    typedef Point_3          result_type;
    typedef Arity_tag< 3 >   Arity;

    Point_3
    operator()(const Point_3& p, const Point_3& q, const Point_3& r) const
    { 
      typedef typename K::RT  RT;
      const RT phw(p.hw());
      const RT qhw(q.hw());
      const RT rhw(r.hw());
      RT hx(p.hx()*qhw*rhw + q.hx()*phw*rhw + r.hx()*phw*qhw);
      RT hy(p.hy()*qhw*rhw + q.hy()*phw*rhw + r.hy()*phw*qhw);
      RT hz(p.hz()*qhw*rhw + q.hz()*phw*rhw + r.hz()*phw*qhw);
      RT hw( phw*qhw*rhw * RT(3));
      return Point_3(hx, hy, hz, hw);
    }

    Point_3
    operator()(const Point_3& p, const Point_3& q, 
               const Point_3& r, const Point_3& s) const
    {
      typedef typename K::RT  RT;
      const RT phw(p.hw());
      const RT qhw(q.hw());
      const RT rhw(r.hw());
      const RT shw(s.hw());
      RT hx(p.hx()*qhw*rhw*shw + q.hx()*phw*rhw*shw + r.hx()*phw*qhw*shw
	    + s.hx()*phw*qhw*rhw);
      RT hy(p.hy()*qhw*rhw*shw + q.hy()*phw*rhw*shw + r.hy()*phw*qhw*shw
	    + s.hy()*phw*qhw*rhw);
      RT hz(p.hz()*qhw*rhw*shw + q.hz()*phw*rhw*shw + r.hz()*phw*qhw*shw
	    + s.hz()*phw*qhw*rhw);
      RT hw( phw*qhw*rhw*shw * RT(4));
      return Point_3(hx, hy, hz, hw);
    }
  };

  template <typename K>
  class Construct_circumcenter_2
  {
    typedef typename K::FT       FT;
    typedef typename K::Point_2  Point_2;
  public:
    typedef Point_2          result_type;
    typedef Arity_tag< 3 >   Arity;

    Point_2
    operator()(const Point_2& p, const Point_2& q, const Point_2& r) const
    { 
      typedef typename K::RT RT;
      RT phx = p.hx();
      RT phy = p.hy();
      RT phw = p.hw();
      RT qhx = q.hx();
      RT qhy = q.hy();
      RT qhw = q.hw();
      RT rhx = r.hx();
      RT rhy = r.hy();
      RT rhw = r.hw();

#ifdef CGAL_EXPANDED_CIRCUMCENTER_COMPUTATION
      RT vvx =
	( qhy*qhw*phw*phw - phy*phw*qhw*qhw )
	*( phx*phx*rhw*rhw + phy*phy*rhw*rhw - 
	   rhx*rhx*phw*phw - rhy*rhy*phw*phw )
	-  ( rhy*rhw*phw*phw - phy*phw*rhw*rhw )
	*( phx*phx*qhw*qhw + phy*phy*qhw*qhw - 
	   qhx*qhx*phw*phw - qhy*qhy*phw*phw );

      RT vvy =
	-  ( qhx*qhw*phw*phw - phx*phw*qhw*qhw )
	*( phx*phx*rhw*rhw + phy*phy*rhw*rhw - 
	   rhx*rhx*phw*phw - rhy*rhy*phw*phw )
	+  ( rhx*rhw*phw*phw - phx*phw*rhw*rhw )
	*( phx*phx*qhw*qhw + phy*phy*qhw*qhw - 
	   qhx*qhx*phw*phw - qhy*qhy*phw*phw );

      RT vvw = RT(2) *
	(  ( qhx*qhw*phw*phw - phx*phw*qhw*qhw )
	   *( rhy*rhw*phw*phw - phy*phw*rhw*rhw )
	   -  ( rhx*rhw*phw*phw - phx*phw*rhw*rhw )
	   *( qhy*qhw*phw*phw - phy*phw*qhw*qhw ) );
#endif // CGAL_EXPANDED_CIRCUMCENTER_COMPUTATION

      RT qy_py = ( qhy*qhw*phw*phw - phy*phw*qhw*qhw );
      RT qx_px = ( qhx*qhw*phw*phw - phx*phw*qhw*qhw );
      RT rx_px = ( rhx*rhw*phw*phw - phx*phw*rhw*rhw );
      RT ry_py = ( rhy*rhw*phw*phw - phy*phw*rhw*rhw );

      RT px2_py2_rx2_ry_2 =
	phx*phx*rhw*rhw + phy*phy*rhw*rhw - 
	rhx*rhx*phw*phw - rhy*rhy*phw*phw ;
      RT px2_py2_qx2_qy_2 =
	phx*phx*qhw*qhw + phy*phy*qhw*qhw - 
	qhx*qhx*phw*phw - qhy*qhy*phw*phw ;

      RT vvx = qy_py * px2_py2_rx2_ry_2 - ry_py * px2_py2_qx2_qy_2;
      RT vvy = rx_px * px2_py2_qx2_qy_2 - qx_px * px2_py2_rx2_ry_2;
      RT vvw = RT(2) * ( qx_px * ry_py - rx_px * qy_py );

      return Point_2( vvx, vvy, vvw );
    }
  };

  template <typename K>
  class Construct_circumcenter_3
  {
    typedef typename K::FT       FT;
    typedef typename K::Point_3  Point_3;
    typedef typename K::Plane_3  Plane_3;
  public:
    typedef Point_3          result_type;
    typedef Arity_tag< 4 >   Arity;

    Point_3
    operator()(const Point_3& p, const Point_3& q, const Point_3& r) const
    { 
      return gp_linear_intersection( Plane_3(p,q,r),
				     bisector(p,q),
				     bisector(p,r));
    } // FIXME

    Point_3
    operator()(const Point_3& p, const Point_3& q,
	       const Point_3& r, const Point_3& s) const
    {
      typedef typename K::RT RT;

      RT phw( p.hw() );
      RT qhw( q.hw() );
      RT rhw( r.hw() );
      RT shw( s.hw() );

      RT phx( p.hx() );
      RT phy( p.hy() );
      RT phz( p.hz() );
      RT qhx( q.hx() );
      RT qhy( q.hy() );
      RT qhz( q.hz() );
      RT rhx( r.hx() );
      RT rhy( r.hy() );
      RT rhz( r.hz() );
      RT shx( s.hx() );
      RT shy( s.hy() );
      RT shz( s.hz() );

      RT pssq( phx*phx + phy*phy + phz*phz );
      RT qssq( qhx*qhx + qhy*qhy + qhz*qhz );
      RT rssq( rhx*rhx + rhy*rhy + rhz*rhz );
      RT sssq( shx*shx + shy*shy + shz*shz );

      phx *= phw;
      phy *= phw;
      phz *= phw;
      phw *= phw;
      qhx *= qhw;
      qhy *= qhw;
      qhz *= qhw;
      qhw *= qhw;
      rhx *= rhw;
      rhy *= rhw;
      rhz *= rhw;
      rhw *= rhw;
      shx *= shw;
      shy *= shw;
      shz *= shw;
      shw *= shw;

      RT chx =  det4x4_by_formula(phy, phz, pssq, phw,
				  qhy, qhz, qssq, qhw,
				  rhy, rhz, rssq, rhw,
				  shy, shz, sssq, shw );
      RT chy =  det4x4_by_formula(phx, phz, pssq, phw,
				  qhx, qhz, qssq, qhw,
				  rhx, rhz, rssq, rhw,
				  shx, shz, sssq, shw );
      RT chz =  det4x4_by_formula(phx, phy, pssq, phw,
				  qhx, qhy, qssq, qhw,
				  rhx, rhy, rssq, rhw,
				  shx, shy, sssq, shw );
      RT chw =  det4x4_by_formula(phx, phy, phz, phw,
				  qhx, qhy, qhz, qhw,
				  rhx, rhy, rhz, rhw,
				  shx, shy, shz, shw );

      return Point_3( chx, -chy, chz, RT(2)*chw);
    }
  };

  template <typename K>
  class Construct_cross_product_vector_3
  {
    typedef typename K::Vector_3  Vector_3;
  public:
    typedef Vector_3         result_type;
    typedef Arity_tag< 2 >   Arity;

    Vector_3
    operator()(const Vector_3& a, const Vector_3& b) const
    {
      return Vector_3(a.hy()*b.hz() - a.hz()*b.hy(),
		      a.hz()*b.hx() - a.hx()*b.hz(),
		      a.hx()*b.hy() - a.hy()*b.hx(),
		      a.hw()*b.hw() );
    }
  };

  template <typename K>
  class Construct_lifted_point_3
  {
    typedef typename K::RT                         RT;
    typedef typename K::Point_2                    Point_2;
    typedef typename K::Point_3                    Point_3;
    typedef typename K::Plane_3                    Plane_3;
  public:
    typedef Point_3          result_type;
    typedef Arity_tag< 2 >   Arity;

    Point_3
    operator()(const Plane_3& h, const Point_2& p) const
    {  
      Point_3 hp( p.hx(), p.hy(), RT(0.0), p.hw());
      return hp.transform( h.transform_to_2d().inverse() );
    }
  };

  template <typename K>
  class Construct_line_2
  {
    typedef typename K::RT                        RT;
    typedef typename K::FT                        FT;
    typedef typename K::Point_2                   Point_2;
    typedef typename K::Vector_2                  Vector_2;
    typedef typename K::Direction_2               Direction_2;
    typedef typename K::Segment_2                 Segment_2;
    typedef typename K::Ray_2                     Ray_2;
    typedef typename K::Line_2                    Line_2;
    typedef typename K::Construct_point_on_2      Construct_point_on_2;
    Construct_point_on_2 cp;
  public:
    typedef Line_2            result_type;
    typedef Arity_tag< 2 >    Arity;

    Construct_line_2() {}
    Construct_line_2(const Construct_point_on_2& cp_) : cp(cp_) {}

    Line_2
    operator()() const
    { return Line_2(); }

#ifndef CGAL_NO_DEPRECATED_CODE
    Line_2
    operator()(const RT& a, const RT& b, const RT& c) const
    { return Line_2(a, b, c); }
#endif // CGAL_NO_DEPRECATED_CODE

    Line_2
    operator()(const Point_2& p, const Point_2& q) const
    { 
      return Line_2(
		    //  a() * X + b() * Y + c() * W() == 0
		    //      |    X        Y       W     |
		    //      |  p.hx()   p.hy()  p.hw()  |
		    //      |  q.hx()   q.hy()  q.hw()  |
		    
		    p.hy()*q.hw() - p.hw()*q.hy(),
		    p.hw()*q.hx() - p.hx()*q.hw(),
		    p.hx()*q.hy() - p.hy()*q.hx() );
    }

    Line_2
    operator()(const Point_2& p, const Vector_2& v) const
    { 
      Point_2 q = p + v;
      return Line_2( p.hy()*q.hw() - p.hw()*q.hy(),
		     p.hw()*q.hx() - p.hx()*q.hw(),
		     p.hx()*q.hy() - p.hy()*q.hx() );
    }

    Line_2
    operator()(const Point_2& p, const Direction_2& d) const
    { 
      Point_2 q = p + d.to_vector();
      return Line_2( p.hy()*q.hw() - p.hw()*q.hy(),
		     p.hw()*q.hx() - p.hx()*q.hw(),
		     p.hx()*q.hy() - p.hy()*q.hx() );
    }

    Line_2
    operator()(const Segment_2& s) const
    { return this->operator()(cp(s, 0), cp(s, 1)); }

    Line_2
    operator()(const Ray_2& r) const
    { return this->operator()(cp(r, 0), cp(r, 1)); }
  };

  template <typename K>
  class Construct_line_3
  {
    typedef typename K::Point_3                   Point_3;
    typedef typename K::Direction_3               Direction_3;
    typedef typename K::Segment_3                 Segment_3;
    typedef typename K::Ray_3                     Ray_3;
    typedef typename K::Line_3                    Line_3;
    typedef typename K::Construct_vector_3        Construct_vector_3;
    typedef typename K::Construct_direction_3     Construct_direction_3;
    typedef typename K::Construct_point_on_3      Construct_point_on_3;
    Construct_vector_3 cv;
    Construct_direction_3 cd;
    Construct_point_on_3 cp;
  public:
    typedef Line_3            result_type;
    typedef Arity_tag< 2 >    Arity;

    Construct_line_3() {}
    Construct_line_3(const Construct_vector_3& cv_,
		     const Construct_direction_3& cd_,
		     const Construct_point_on_3& cp_) 
      : cv(cv_), cd(cd_), cp(cp_) 
    {}

    Line_3
    operator()() const
    { return Line_3(); }

    Line_3
    operator()(const Point_3& p, const Point_3& q) const
    { return Line_3(p, cd(cv(p, q))); }

    Line_3
    operator()(const Point_3& p, const Direction_3& d) const
    { return Line_3(p, d); }

    Line_3
    operator()(const Segment_3& s) const
    { return Line_3(cp(s,0), cd(cv(cp(s,1), cp(s,0)))); }

    Line_3
    operator()(const Ray_3& r) const
    { return Line_3(cp(r,0), cd(cv(cp(r,1), cp(r,0)))); }
  };

  template <typename K>
  class Construct_midpoint_2
  {
    typedef typename K::FT        FT;
    typedef typename K::Point_2   Point_2;
  public:
    typedef Point_2          result_type;
    typedef Arity_tag< 2 >   Arity;

    Point_2
    operator()(const Point_2& p, const Point_2& q) const
    { 
      typedef typename K::RT RT;
      const RT& phw = p.hw();
      const RT& qhw = q.hw();
      return Point_2( p.hx()*qhw + q.hx()*phw, 
		      p.hy()*qhw + q.hy()*phw,
		      phw * qhw * RT( 2));
    }
  };

  template <typename K>
  class Construct_midpoint_3
  {
    typedef typename K::FT        FT;
    typedef typename K::Point_3   Point_3;
  public:
    typedef Point_3          result_type;
    typedef Arity_tag< 2 >   Arity;

    Point_3
    operator()(const Point_3& p, const Point_3& q) const
    { 
      typedef typename K::RT RT;
      RT phw = p.hw();
      RT qhw = q.hw();
      return Point_3( p.hx()*qhw + q.hx()*phw,
		      p.hy()*qhw + q.hy()*phw,
		      p.hz()*qhw + q.hz()*phw,
		      RT(2) * phw * qhw );
    }
  };

  // TODO ...
  template <typename K>
  class Construct_opposite_vector_2
  {
    typedef typename K::Vector_2    Vector_2;
  public:
    typedef Vector_2         result_type;
    typedef Arity_tag< 1 >   Arity;

    Vector_2
    operator()( const Vector_2& v) const
    { return Vector_2(-v.hx(), -v.hy(), v.hw()); }
  };

  template <typename K>
  class Construct_opposite_vector_3
  {
    typedef typename K::Vector_3    Vector_3;
  public:
    typedef Vector_3         result_type;
    typedef Arity_tag< 1 >   Arity;

    Vector_3
    operator()( const Vector_3& v) const
    { return Vector_3(-v.hx(), -v.hy(), -v.hz(), v.hw()); }
  };

  template <typename K>
  class Construct_scaled_vector_2
  {
    typedef typename K::RT         RT;
    typedef typename K::Vector_2   Vector_2;
  public:
    typedef Vector_2         result_type;
    typedef Arity_tag< 2 >   Arity;

    Vector_2
    operator()( const Vector_2& v, const RT& c) const
    {  
      return Vector_2(c * v.hx(), c * v.hy(), v.hw());
    }
  };

  template <typename K>
  class Construct_scaled_vector_3
  {
    typedef typename K::RT         RT;
    typedef typename K::Vector_3   Vector_3;
  public:
    typedef Vector_3         result_type;
    typedef Arity_tag< 2 >   Arity;

    Vector_3
    operator()( const Vector_3& v, const RT& c) const
    {  
      return Vector_3(c * v.hx(), c * v.hy(), c * v.hz(), v.hw());
    }
  };

  template <typename K>
  class Construct_translated_point_2
  {
    typedef typename K::Point_2   Point_2;
    typedef typename K::Vector_2  Vector_2;
  public:
    typedef Point_2          result_type;
    typedef Arity_tag< 2 >   Arity;

    Point_2
    operator()( const Point_2& p, const Vector_2& v) const
    {  
      return Point_2( p.hx()*v.hw() + v.hx()*p.hw(),
		      p.hy()*v.hw() + v.hy()*p.hw(),
		      p.hw()*v.hw() );
    }
  };

  template <typename K>
  class Construct_translated_point_3
  {
    typedef typename K::Point_3   Point_3;
    typedef typename K::Vector_3  Vector_3;
  public:
    typedef Point_3          result_type;
    typedef Arity_tag< 2 >   Arity;

    Point_3
    operator()( const Point_3& p, const Vector_3& v) const
    { 
      return Point_3(p.hx()*v.hw() + v.hx()*p.hw(),
		     p.hy()*v.hw() + v.hy()*p.hw(),
		     p.hz()*v.hw() + v.hz()*p.hw(),
		     p.hw()*v.hw() );
    }
  };

  template <typename K>
  class Construct_vector_2
  {
    typedef typename K::RT           RT;
    typedef typename K::FT           FT;
    typedef typename K::Segment_2    Segment_2;
    typedef typename K::Ray_2        Ray_2;
    typedef typename K::Line_2       Line_2;
    typedef typename K::Vector_2     Vector_2;
    typedef typename K::Point_2      Point_2;
  public:
    typedef Vector_2         result_type;
    typedef Arity_tag< 2 >   Arity;

    Vector_2
    operator()() const
    { return Vector_2(); }

    Vector_2
    operator()( const Point_2& p, const Point_2& q) const
    { 
      return Vector_2( q.hx()*p.hw() - p.hx()*q.hw(),
		       q.hy()*p.hw() - p.hy()*q.hw(),
		       p.hw()*q.hw() );
    }

    Vector_2
    operator()( const Segment_2& s) const
    { return Vector_2(s); }

    Vector_2
    operator()( const Ray_2& r) const
    { return Vector_2(r); }

    Vector_2
    operator()( const Line_2& l) const
    { return Vector_2(l); }

    Vector_2
    operator()( Null_vector) const
    { return Vector_2(RT(0), RT(0), RT(1)); }

#ifndef CGAL_NO_DEPRECATED_CODE
    Vector_2
    operator()( const RT& x, const RT& y) const
    { return Vector_2(x, y); }

    Vector_2
    operator()( const RT& x, const RT& y, const RT& w) const
    { return Vector_2(x, y, w); }
#endif // CGAL_NO_DEPRECATED_CODE
  };

  template <typename K>
  class Construct_vector_3
  {
    typedef typename K::RT           RT;
    typedef typename K::FT           FT;
    typedef typename K::Segment_3    Segment_3;
    typedef typename K::Ray_3        Ray_3;
    typedef typename K::Line_3       Line_3;
    typedef typename K::Vector_3     Vector_3;
    typedef typename K::Point_3      Point_3;
  public:
    typedef Vector_3         result_type;
    typedef Arity_tag< 2 >   Arity;

    Vector_3
    operator()() const
    { return Vector_3(); }

    Vector_3
    operator()( const Point_3& p, const Point_3& q) const
    { 
      return Vector_3(q.hx()*p.hw() - p.hx()*q.hw(),
		      q.hy()*p.hw() - p.hy()*q.hw(),
		      q.hz()*p.hw() - p.hz()*q.hw(),
		      q.hw()*p.hw() );
    }

    Vector_3
    operator()( const Segment_3& s) const
    { return Vector_3(s); }

    Vector_3
    operator()( const Ray_3& r) const
    { return Vector_3(r); }

    Vector_3
    operator()( const Line_3& l) const
    { return Vector_3(l); }

    Vector_3
    operator()( const Null_vector&) const
    { return Vector_3(RT(0), RT(0), RT(0), RT(1)); }

#ifndef CGAL_NO_DEPRECATED_CODE
    Vector_3
    operator()( const RT& x, const RT& y, const RT& z) const
    { return Vector_3(x, y, z); }

    Vector_3
    operator()( const RT& x, const RT& y, const RT& z, const RT& w) const
    { return Vector_3(x, y, z, w); }
#endif // CGAL_NO_DEPRECATED_CODE
  };

  template <typename K>
  class Coplanar_orientation_3
  {
    typedef typename K::Point_3      Point_3;
#ifdef CGAL_kernel_exactness_preconditions 
    typedef typename K::Coplanar_3   Coplanar_3;
    typedef typename K::Collinear_3  Collinear_3;
    Coplanar_3 cp;
    Collinear_3 cl;
#endif // CGAL_kernel_exactness_preconditions 
  public:
    typedef Orientation  result_type;
    typedef Arity_tag< 4 >   Arity;

#ifdef CGAL_kernel_exactness_preconditions 
    Coplanar_orientation_3() {}
    Coplanar_orientation_3(const Coplanar_3& cp_, const Collinear_3& cl_) 
      : cp(cp_), cl(cl_)
    {}
#endif // CGAL_kernel_exactness_preconditions 

    Orientation
    operator()(const Point_3& p, const Point_3& q, const Point_3& r) const
    { 
      Orientation oxy_pqr = orientationH2(p.hx(), p.hy(), p.hw(),
					  q.hx(), q.hy(), q.hw(),
					  r.hx(), r.hy(), r.hw());
      if (oxy_pqr != COLLINEAR)
	return oxy_pqr;

      Orientation oyz_pqr = orientationH2(p.hy(), p.hz(), p.hw(),
					  q.hy(), q.hz(), q.hw(),
					  r.hy(), r.hz(), r.hw());
      if (oyz_pqr != COLLINEAR)
	return oyz_pqr;

      return orientationH2(p.hx(), p.hz(), p.hw(),
			   q.hx(), q.hz(), q.hw(),
			   r.hx(), r.hz(), r.hw());
    }

    Orientation
    operator()( const Point_3& p, const Point_3& q,
	        const Point_3& r, const Point_3& s) const
    { 
      // p,q,r,s supposed to be coplanar
      // p,q,r supposed to be non collinear
      // tests whether s is on the same side of p,q as r
      // returns :
      // COLLINEAR if pqr collinear
      // POSITIVE if qrp and qrs have the same orientation
      // NEGATIVE if qrp and qrs have opposite orientations
      CGAL_kernel_exactness_precondition( ! cl(p, q, r) );
      CGAL_kernel_exactness_precondition( cp(p, q, r, s) );

      // compute orientation of p,q,s in this plane P:
      Orientation save;
      if ( (save = orientationH2( p.hy(), p.hz(), p.hw(),
				  q.hy(), q.hz(), q.hw(),
				  r.hy(), r.hz(), r.hw())) != COLLINEAR)
	{ return
	    static_cast<Orientation>(
	     static_cast<int>( save)
	     * static_cast<int>( orientationH2( p.hy(), p.hz(), p.hw(),
						q.hy(), q.hz(), q.hw(),
						s.hy(), s.hz(), s.hw())) );
	}
      if ( (save = orientationH2( p.hx(), p.hz(), p.hw(),
				  q.hx(), q.hz(), q.hw(),
				  r.hx(), r.hz(), r.hw())) != COLLINEAR)
	{ return
	    static_cast<Orientation>(
	     static_cast<int>( save)
	     * static_cast<int>( orientationH2( p.hx(), p.hz(), p.hw(),
						q.hx(), q.hz(), q.hw(),
						s.hx(), s.hz(), s.hw())) );
	}
      if ( (save = orientationH2( p.hx(), p.hy(), p.hw(),
				  q.hx(), q.hy(), q.hw(),
				  r.hx(), r.hy(), r.hw())) != COLLINEAR)
	{ return
	    static_cast<Orientation>(
	     static_cast<int>( save)
	     * static_cast<int>( orientationH2( p.hx(), p.hy(), p.hw(),
						q.hx(), q.hy(), q.hw(),
						s.hx(), s.hy(), s.hw())) );
	}
      CGAL_kernel_assertion( false);
      return COLLINEAR;
    }
  };

  template <typename K>
  class Coplanar_side_of_bounded_circle_3
  {
    typedef typename K::Point_3   Point_3;
#ifdef CGAL_kernel_exactness_preconditions 
    typedef typename K::Coplanar_3   Coplanar_3;
    typedef typename K::Collinear_3  Collinear_3;
    Coplanar_3 cp;
    Collinear_3 cl;
#endif // CGAL_kernel_exactness_preconditions 
  public:
    typedef Bounded_side     result_type;
    typedef Arity_tag< 4 >   Arity;

#ifdef CGAL_kernel_exactness_preconditions 
    Coplanar_side_of_bounded_circle_3() {}
    Coplanar_side_of_bounded_circle_3(const Coplanar_3& cp_, 
				      const Collinear_3& cl_) 
      : cp(cp_), cl(cl_)
    {}
#endif // CGAL_kernel_exactness_preconditions 

    Bounded_side
    operator()( const Point_3& p, const Point_3& q,
	        const Point_3& r, const Point_3& t) const
    { 
      // p,q,r,t are supposed to be coplanar.
      // p,q,r determine an orientation of this plane (not collinear).
      // returns the equivalent of side_of_bounded_circle(p,q,r,t) 
      // in this plane
      CGAL_kernel_exactness_precondition( cp(p,q,r,t) );
      CGAL_kernel_exactness_precondition( !cl(p,q,r) );
      return (Bounded_side)
	side_of_oriented_sphere(p, q, r, t+cross_product(q-p, r-p), t);
    } // FIXME
  };

  template <typename K>
  class Coplanar_3
  {
    typedef typename K::Point_3       Point_3;
    typedef typename K::Orientation_3 Orientation_3;
    Orientation_3 o;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 4 >   Arity;

    Coplanar_3() {}
    Coplanar_3(const Orientation_3& o_) : o(o_) {}

    bool
    operator()( const Point_3& p, const Point_3& q,
	        const Point_3& r, const Point_3& s) const
    { 
      return o(p, q, r, s) == COPLANAR;
    }
  };

  template <typename K>
  class Equal_xy_3
  {
    typedef typename K::Point_3    Point_3;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_3& p, const Point_3& q) const
    { 
      return   (p.hx() * q.hw() == q.hx() * p.hw() )
        && (p.hy() * q.hw() == q.hy() * p.hw() );
    }
  };

  template <typename K>
  class Equal_x_2
  {
    typedef typename K::Point_2    Point_2;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_2& p, const Point_2& q) const
    { return p.x()*q.hw() == q.x()*p.hw(); }
  };

  template <typename K>
  class Equal_x_3
  {
    typedef typename K::Point_3    Point_3;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_3& p, const Point_3& q) const
    { return p.x()*q.hw() == q.x()*p.hw(); }
  };

  template <typename K>
  class Equal_y_2
  {
    typedef typename K::Point_2    Point_2;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_2& p, const Point_2& q) const
    { return p.y()*q.hw() == q.y()*p.hw(); }
  };

  template <typename K>
  class Equal_y_3
  {
    typedef typename K::Point_3    Point_3;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_3& p, const Point_3& q) const
    { return p.y()*q.hw() == q.y()*p.hw(); }
  };

  template <typename K>
  class Equal_z_3
  {
    typedef typename K::Point_3    Point_3;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_3& p, const Point_3& q) const
    { return p.z()*q.hw() == q.z()*p.hw(); }
  };

  template <typename K>
  class Less_distance_to_point_2
  {
    typedef typename K::Point_2   Point_2;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 3 >   Arity;

    bool
    operator()(const Point_2& p, const Point_2& q, const Point_2& r) const
    { 
      typedef typename K::RT RT;

      const RT phx = p.hx();
      const RT phy = p.hy();
      const RT phw = p.hw();
      const RT qhx = q.hx();
      const RT qhy = q.hy();
      const RT qhw = q.hw();
      const RT rhx = r.hx();
      const RT rhy = r.hy();
      const RT rhw = r.hw();
      const RT RT0 = RT(0);
      const RT RT2 = RT(2);

      RT dosd =   // difference of squared distances

	//            phx * phx   *   qhw * qhw * rhw * rhw
	//   -RT(2) * phx * qhx   *   phw * qhw * rhw * rhw
	//   +        qhx * qhx   *   phw * phw * rhw * rhw
	//
	//   +        phy * phy   *   qhw * qhw * rhw * rhw
	//   -RT(2) * phy * qhy   *   phw * qhw * rhw * rhw
	//   +        qhy * qhy   *   phw * phw * rhw * rhw
	//
	// - (        phx * phx   *   qhw * qhw * rhw * rhw
	//   -RT(2) * phx * rhx   *   phw * qhw * qhw * rhw
	//   +        rhx * rhx   *   phw * phw * qhw * qhw
	//
	//   +        phy * phy   *   qhw * qhw * rhw * rhw
	//   -RT(2) * phy * rhy   *   phw * qhw * qhw * rhw
	//   +        rhy * rhy   *   phw * phw * qhw * qhw
	
	rhw*rhw * (         phw * ( qhx*qhx + qhy*qhy )
			    - RT2 * qhw * ( phx*qhx + phy*qhy )
			    )
	- qhw*qhw * (         phw * ( rhx*rhx + rhy*rhy )
			      - RT2 * rhw * ( phx*rhx + phy*rhy )
			      );
      
      
      return ( dosd < RT0 );
    }
  };

  template <typename K>
  class Less_distance_to_point_3
  {
    typedef typename K::Point_3   Point_3;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 3 >   Arity;

    bool
    operator()(const Point_3& p, const Point_3& q, const Point_3& r) const
    { 
      typedef typename K::RT RT;

      const RT phx = p.hx();
      const RT phy = p.hy();
      const RT phz = p.hz();
      const RT phw = p.hw();
      const RT qhx = q.hx();
      const RT qhy = q.hy();
      const RT qhz = q.hz();
      const RT qhw = q.hw();
      const RT rhx = r.hx();
      const RT rhy = r.hy();
      const RT rhz = r.hz();
      const RT rhw = r.hw();
      const RT RT0 = RT(0);
      const RT RT2 = RT(2);

      RT dosd =   // difference of squared distances

	rhw*rhw * (         phw * ( qhx*qhx + qhy*qhy + qhz*qhz )
			    - RT2 * qhw * ( phx*qhx + phy*qhy + phz*qhz )
			    )
	- qhw*qhw * (         phw * ( rhx*rhx + rhy*rhy + rhz*rhz )
			      - RT2 * rhw * ( phx*rhx + phy*rhy + phz*rhz )
			      );

      return ( dosd < RT0 );
    }
  };

  template <typename K>
  class Less_signed_distance_to_line_2
  {
    typedef typename K::Point_2   Point_2;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 4 >   Arity;

    bool
    operator()(const Point_2& p, const Point_2& q,
               const Point_2& r, const Point_2& s) const
    {
      typedef typename K::RT RT;

      const RT phx= p.hx();
      const RT phy= p.hy();
      const RT phw= p.hw();
      const RT qhx= q.hx();
      const RT qhy= q.hy();
      const RT qhw= q.hw();
      const RT rhx= r.hx();
      const RT rhy= r.hy();
      const RT rhw= r.hw();
      const RT shx= s.hx();
      const RT shy= s.hy();
      const RT shw= s.hw();
      const RT RT0  = RT(0);

      RT  scaled_dist_r_minus_scaled_dist_s =
	( rhx*shw - shx*rhw ) * (phy*qhw - qhy*phw)
	- ( rhy*shw - shy*rhw ) * (phx*qhw - qhx*phw);

      return ( scaled_dist_r_minus_scaled_dist_s < RT0 );
    }
  };

  template <typename K>
  class Less_signed_distance_to_plane_3
  {
    typedef typename K::RT       RT;
    typedef typename K::Point_3  Point_3;
    typedef typename K::Plane_3  Plane_3;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 3 >   Arity;

    bool
    operator()( const Plane_3& pl, const Point_3& p, const Point_3& q) const
    { 
      const RT pla = pl.a();
      const RT plb = pl.b();
      const RT plc = pl.c();
      const RT phx = p.hx();
      const RT phy = p.hy();
      const RT phz = p.hz();
      const RT phw = p.hw();
      const RT qhx = q.hx();
      const RT qhy = q.hy();
      const RT qhz = q.hz();
      const RT qhw = q.hw();
      const RT RT0 = RT(0);

      RT scaled_dist_p_minus_scaled_dist_q =
	pla*( phx*qhw - qhx*phw )
	+ plb*( phy*qhw - qhy*phw )
	+ plc*( phz*qhw - qhz*phw );

      return ( scaled_dist_p_minus_scaled_dist_q < RT0 );
    }
  };

  template <typename K>
  class Less_xyz_3
  {
    typedef typename K::Point_3 Point_3;
    typedef typename K::Compare_xyz_3 Compare_xyz_3;
    Compare_xyz_3 c;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    Less_xyz_3() {}
    Less_xyz_3(const Compare_xyz_3& c_) : c(c_) {}

    bool
    operator()( const Point_3& p, const Point_3& q) const
    { return c(p, q) == SMALLER; }
  };

  template <typename K>
  class Less_xy_2
  {
    typedef typename K::Point_2 Point_2;
    typedef typename K::Compare_xy_2 Compare_xy_2;
    Compare_xy_2 c;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    Less_xy_2() {}
    Less_xy_2(const Compare_xy_2& c_) : c(c_) {}

    bool
    operator()( const Point_2& p, const Point_2& q) const
    { return c(p, q) == SMALLER; }
  };

  template <typename K>
  class Less_xy_3
  {
    typedef typename K::Point_3 Point_3;
    typedef typename K::Compare_xy_3 Compare_xy_3;
    Compare_xy_3 c;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    Less_xy_3() {}
    Less_xy_3(const Compare_xy_3& c_) : c(c_) {}

    bool
    operator()( const Point_3& p, const Point_3& q) const
    { return c(p, q) == SMALLER; }
  };

  template <typename K>
  class Less_x_2
  {
    typedef typename K::Point_2 Point_2;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_2& p, const Point_2& q) const
    { return ( p.hx()*q.hw() < q.hx()*p.hw() ); }
  };

  template <typename K>
  class Less_x_3
  {
    typedef typename K::Point_3 Point_3;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_3& p, const Point_3& q) const
    { return ( p.hx()*q.hw() < q.hx()*p.hw() ); }
  };

  template <typename K>
  class Less_yx_2
  {
    typedef typename K::Point_2       Point_2;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_2& p, const Point_2& q) const
    { 
      typedef typename K::RT RT;

      const RT& phx = p.hx();
      const RT& phy = p.hy();
      const RT& phw = p.hw();
      const RT& qhx = q.hx();
      const RT& qhy = q.hy();
      const RT& qhw = q.hw();

      RT pV = phy * qhw;
      RT qV = qhy * phw;
      if ( qV < pV )
	{
	  return false;
	}
      else if ( pV < qV )
	{
	  return true;
	}
      pV = phx * qhw;
      qV = qhx * phw;
      return ( pV < qV );
    }
  };

  template <typename K>
  class Less_y_2
  {
    typedef typename K::Point_2 Point_2;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_2& p, const Point_2& q) const
    { return ( p.hy()*q.hw() < q.hy()*p.hw() ); }
  };

  template <typename K>
  class Less_y_3
  {
    typedef typename K::Point_3 Point_3;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_3& p, const Point_3& q) const
    { return ( p.hy()*q.hw() < q.hy()*p.hw() ); }
  };

  template <typename K>
  class Less_z_3
  {
    typedef typename K::Point_3 Point_3;
  public:
    typedef bool             result_type;
    typedef Arity_tag< 2 >   Arity;

    bool
    operator()( const Point_3& p, const Point_3& q) const
    { return   (p.hz() * q.hw() < q.hz() * p.hw() ); }
  };

  template <typename K>
  class Orientation_2
  {
    typedef typename K::Point_2 Point_2;
  public:
    typedef Orientation      result_type;
    typedef Arity_tag< 3 >   Arity;

    Orientation
    operator()(const Point_2& p, const Point_2& q, const Point_2& r) const
    { 
      typedef typename K::RT RT;

      const RT& phx = p.hx();
      const RT& phy = p.hy();
      const RT& phw = p.hw();
      const RT& qhx = q.hx();
      const RT& qhy = q.hy();
      const RT& qhw = q.hw();
      const RT& rhx = r.hx();
      const RT& rhy = r.hy();
      const RT& rhw = r.hw();
      const RT  RT0 = RT(0);

      // | A B |
      // | C D |

      RT  A = phx*rhw - phw*rhx;
      RT  B = phy*rhw - phw*rhy;
      RT  C = qhx*rhw - qhw*rhx;
      RT  D = qhy*rhw - qhw*rhy;

      RT  det =  A*D - B*C;

      /*
	RT det_old =   p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
	+ p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
	+ p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );
	
	if ( !(CGAL_NTS sign(det) == CGAL_NTS sign(det_old)) )
	{
	std::cerr << "det: " << det << " det_old: " << det_old << flush;
	}
      */
      
      if (det < RT0  )
	{
	  return CLOCKWISE;
	}
      else
	{
	  return (RT0 < det) ? COUNTERCLOCKWISE : COLLINEAR;
	}
    }
  };

  template <typename K>
  class Orientation_3
  {
    typedef typename K::Point_3 Point_3;
  public:
    typedef Orientation      result_type;
    typedef Arity_tag< 4 >   Arity;

    Orientation
    operator()( const Point_3& p, const Point_3& q,
	        const Point_3& r, const Point_3& s) const
    { 
      // Two rows are switched, because of the homogeneous column.
      return (Orientation) 
	sign_of_determinant4x4( p.hx(), p.hy(), p.hz(), p.hw(),
				r.hx(), r.hy(), r.hz(), r.hw(),
				q.hx(), q.hy(), q.hz(), q.hw(),
				s.hx(), s.hy(), s.hz(), s.hw());
    }
  };

  template <typename K>
  class Side_of_bounded_circle_2
  {
    typedef typename K::Point_2        Point_2;
  public:
    typedef Bounded_side     result_type;
    typedef Arity_tag< 4 >   Arity;

    Bounded_side
    operator()( const Point_2& p, const Point_2& q, const Point_2& t) const
    { 
      typedef typename K::RT RT;

      const RT& phx = p.hx();
      const RT& phy = p.hy();
      const RT& phw = p.hw();
      const RT& qhx = q.hx();
      const RT& qhy = q.hy();
      const RT& qhw = q.hw();
      const RT& thx = t.hx();
      const RT& thy = t.hy();
      const RT& thw = t.hw();

      return Bounded_side( 
	    CGAL_NTS compare((thx*phw-phx*thw)*(qhx*thw-thx*qhw),
			     (thy*phw-phy*thw)*(thy*qhw-qhy*thw)) );
    }

    Bounded_side
    operator()( const Point_2& q, const Point_2& r,
	        const Point_2& s, const Point_2& t) const
    { 
      typedef typename K::RT RT;

      const RT& qhx = q.hx();
      const RT& qhy = q.hy();
      const RT& qhw = q.hw();
      const RT& rhx = r.hx();
      const RT& rhy = r.hy();
      const RT& rhw = r.hw();
      const RT& shx = s.hx();
      const RT& shy = s.hy();
      const RT& shw = s.hw();
      const RT& thx = t.hx();
      const RT& thy = t.hy();
      const RT& thw = t.hw();
      const RT  RT0 = RT(0);

      CGAL_kernel_precondition( ! collinear(q,r,s) );

      // compute sign of      |qx  qy  qx^2+qy^2  1 |   | a b c d |
      //                      |      --  r  --      | = | e f g h |
      //     determinant      |      --  s  --      | = | i j k l |
      //                      |      --  t  --      |   | m n o p |
      //           where

      RT a = qhx*qhw;
      RT b = qhy*qhw;
      RT c = qhx*qhx + qhy*qhy;
      RT d = qhw*qhw;

      RT e = rhx*rhw;
      RT f = rhy*rhw;
      RT g = rhx*rhx + rhy*rhy;
      RT h = rhw*rhw;

      RT i = shx*shw;
      RT j = shy*shw;
      RT k = shx*shx + shy*shy;
      RT l = shw*shw;

      RT m = thx*thw;
      RT n = thy*thw;
      RT o = thx*thx + thy*thy;
      RT p = thw*thw;

      RT det =   a * ( f*(k*p - l*o) + j*(h*o - g*p) + n*(g*l - h*k) )
	- e * ( b*(k*p - l*o) + j*(d*o - c*p) + n*(c*l - d*k) )
	+ i * ( b*(g*p - h*o) + f*(d*o - c*p) + n*(c*h - d*g) )
	- m * ( b*(g*l - h*k) + f*(d*k - c*l) + j*(c*h - d*g) );


      if ( det == RT0 )
	{
	  return ON_BOUNDARY;
	}
      else
	{
	  if (orientation(q,r,s) == CLOCKWISE)
	    {
	      det = -det;
	    }
	  return (RT0 < det ) ? ON_BOUNDED_SIDE : ON_UNBOUNDED_SIDE;
	}
    }
  };

  template <typename K>
  class Side_of_bounded_sphere_3
  {
    typedef typename K::Point_3        Point_3;
  public:
    typedef Bounded_side   result_type;
    typedef Arity_tag< 5 >   Arity;

    Bounded_side
    operator()( const Point_3& p, const Point_3& q, const Point_3& t) const
    { 
      typedef typename K::RT RT;

      const RT& phx = p.hx();
      const RT& phy = p.hy();
      const RT& phz = p.hz();
      const RT& phw = p.hw();
      const RT& qhx = q.hx();
      const RT& qhy = q.hy();
      const RT& qhz = q.hz();
      const RT& qhw = q.hw();
      const RT& thx = t.hx();
      const RT& thy = t.hy();
      const RT& thz = t.hz();
      const RT& thw = t.hw();

      return Bounded_side( 
	  CGAL_NTS sign<RT>((thx*phw-phx*thw)*(qhx*thw-thx*qhw)
			    + (thy*phw-phy*thw)*(qhy*thw-thy*qhw)
			    + (thz*phw-phz*thw)*(qhz*thw-thz*qhw)));
    }

    Bounded_side
    operator()( const Point_3& p, const Point_3& q,
	        const Point_3& r, const Point_3& t) const
    {
      Point_3 center = circumcenter(p, q, r);
      return Bounded_side( compare_distance_to_point(center, p, t) );
    } // FIXME

    Bounded_side
    operator()( const Point_3& p, const Point_3& q, const Point_3& r,
	        const Point_3& s, const Point_3& test) const
    {
      Oriented_side  oside = side_of_oriented_sphere(p,q,r,s,test);
      if ( are_positive_oriented( p,q,r,s) )
	{
	  switch (oside)
	    {
	    case ON_POSITIVE_SIDE    :   return ON_BOUNDED_SIDE;
	    case ON_ORIENTED_BOUNDARY:   return ON_BOUNDARY;
	    case ON_NEGATIVE_SIDE    :   return ON_UNBOUNDED_SIDE;
	    }
	}
      else
	{
	  switch (oside)
	    {
	    case ON_POSITIVE_SIDE    :   return ON_UNBOUNDED_SIDE;
	    case ON_ORIENTED_BOUNDARY:   return ON_BOUNDARY;
	    case ON_NEGATIVE_SIDE    :   return ON_BOUNDED_SIDE;
	    }
	}
      return ON_BOUNDARY;  // Pls, no warnings anylonger
    } // FIXME
  };

  template <typename K>
  class Side_of_oriented_circle_2
  {
    typedef typename K::Point_2        Point_2;
  public:
    typedef Oriented_side    result_type;
    typedef Arity_tag< 4 >   Arity;

    Oriented_side
    operator()( const Point_2& q, const Point_2& r,
	        const Point_2& s, const Point_2& t) const
    {
      typedef typename K::RT RT;

      const RT& qhx = q.hx();
      const RT& qhy = q.hy();
      const RT& qhw = q.hw();
      const RT& rhx = r.hx();
      const RT& rhy = r.hy();
      const RT& rhw = r.hw();
      const RT& shx = s.hx();
      const RT& shy = s.hy();
      const RT& shw = s.hw();
      const RT& thx = t.hx();
      const RT& thy = t.hy();
      const RT& thw = t.hw();
      const RT  RT0 = RT(0);

      CGAL_kernel_precondition( ! collinear(q,r,s) );

      // compute sign of      |qx  qy  qx^2+qy^2  1 |   | a b c d |
      //                      |      --  r  --      | = | e f g h |
      //     determinant      |      --  s  --      | = | i j k l |
      //                      |      --  t  --      |   | m n o p |
      //           where

      RT a = qhx*qhw;
      RT b = qhy*qhw;
      RT c = qhx*qhx + qhy*qhy;
      RT d = qhw*qhw;

      RT e = rhx*rhw;
      RT f = rhy*rhw;
      RT g = rhx*rhx + rhy*rhy;
      RT h = rhw*rhw;

      RT i = shx*shw;
      RT j = shy*shw;
      RT k = shx*shx + shy*shy;
      RT l = shw*shw;

      RT m = thx*thw;
      RT n = thy*thw;
      RT o = thx*thx + thy*thy;
      RT p = thw*thw;

      RT det =   a * ( f*(k*p - l*o) + j*(h*o - g*p) + n*(g*l - h*k) )
	- e * ( b*(k*p - l*o) + j*(d*o - c*p) + n*(c*l - d*k) )
	+ i * ( b*(g*p - h*o) + f*(d*o - c*p) + n*(c*h - d*g) )
	- m * ( b*(g*l - h*k) + f*(d*k - c*l) + j*(c*h - d*g) );


      if ( det < RT0 )
	{
	  return ON_NEGATIVE_SIDE;
	}
      else
	{
	  return (RT0 < det ) ? ON_POSITIVE_SIDE : ON_ORIENTED_BOUNDARY;
	}
    }
  };

  template <typename K>
  class Side_of_oriented_sphere_3
  {
    typedef typename K::Point_3        Point_3;
  public:
    typedef Oriented_side    result_type;
    typedef Arity_tag< 5 >   Arity;

    Oriented_side
    operator()( const Point_3& p, const Point_3& q, const Point_3& r,
	        const Point_3& s, const Point_3& t) const
    { 
      typedef typename K::RT RT;
      CGAL_kernel_precondition( !coplanar(p,q,r,s) );
      const RT phx = p.hx();
      const RT phy = p.hy();
      const RT phz = p.hz();
      const RT phw = p.hw();
      const RT phw2 = phw*phw;

      const RT qhx = q.hx();
      const RT qhy = q.hy();
      const RT qhz = q.hz();
      const RT qhw = q.hw();
      const RT qhw2 = qhw*qhw;

      const RT rhx = r.hx();
      const RT rhy = r.hy();
      const RT rhz = r.hz();
      const RT rhw = r.hw();
      const RT rhw2 = rhw*rhw;

      const RT shx = s.hx();
      const RT shy = s.hy();
      const RT shz = s.hz();
      const RT shw = s.hw();
      const RT shw2 = shw*shw;

      const RT thx = t.hx();
      const RT thy = t.hy();
      const RT thz = t.hz();
      const RT thw = t.hw();
      const RT thw2 = thw*thw;

      const RT det = det5x5_by_formula<RT>(
	   phx*phw, phy*phw, phz*phw, phx*phx + phy*phy + phz*phz, phw2,
	   qhx*qhw, qhy*qhw, qhz*qhw, qhx*qhx + qhy*qhy + qhz*qhz, qhw2,
	   rhx*rhw, rhy*rhw, rhz*rhw, rhx*rhx + rhy*rhy + rhz*rhz, rhw2,
	   shx*shw, shy*shw, shz*shw, shx*shx + shy*shy + shz*shz, shw2,
	   thx*thw, thy*thw, thz*thw, thx*thx + thy*thy + thz*thz, thw2);
      if (det < RT(0))
	{
	  return ON_POSITIVE_SIDE;
	}
      else
	{
	  return (RT(0) < det) ? ON_NEGATIVE_SIDE : ON_ORIENTED_BOUNDARY;
	}
    }
  };

} // namespace HomogeneousKernelFunctors

CGAL_END_NAMESPACE

#endif // CGAL_HOMOGENEOUS_FUNCTION_OBJECTS_H
