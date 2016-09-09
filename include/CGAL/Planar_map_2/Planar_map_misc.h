// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Planar_map_2/Planar_map_misc.h
// package       : Planar_map (5.113)
// source        :
// revision      :
// revision_date :
// author(s)     : Iddo Hanniel
//                 Eyal Flato
//                 Oren Nechushtan
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_PLANAR_MAP_MISC_H
#define CGAL_PLANAR_MAP_MISC_H

#ifndef CGAL_POLYHEDRON_ITERATOR_3_H
#include <CGAL/Polyhedron_iterator_3.h>
#endif

CGAL_BEGIN_NAMESPACE

//--------------------------------------------------------------------------
// Planar_map_traits_wrap - 
//     Geometric Look Up Table. This class extends the user supplied 
// interface to include various less "shallow" operations that are
// impelemented through the interface.
//--------------------------------------------------------------------------

template <class PlanarMapTraits_2>
class Planar_map_traits_wrap : public PlanarMapTraits_2
{
public:
//  typedef  typename I::Info_vertex     Info_vertex;
//  typedef  typename I::Info_edge       Info_edge;
//  typedef  typename I::Info_face       Info_face;
  
  typedef PlanarMapTraits_2          Base;
  typedef typename Base::X_curve X_curve;
  typedef typename Base::Point Point;
  typedef Point Point_2;
  //typedef  typename PlanarMapTraits_2::Point_2 Point; // for backward compat.
  
  Planar_map_traits_wrap() : Base()
  {
  }

  Planar_map_traits_wrap(const Base& i) : Base(i)
  {
  }
  
  
  bool point_is_left( const Point_2  & p1, const Point_2  & p2 ) const
  {
    return (compare_x(p1, p2) == SMALLER); 
  }
  
    bool point_is_right( const Point_2  & p1, const  Point_2  & p2 ) const
  {
    return (compare_x(p1, p2) == LARGER); 
  }
  
  bool point_is_same_x( const Point_2  & p1, const Point_2  & p2 ) const
  {
    return (compare_x(p1, p2) == EQUAL); 
  }
  
  bool point_is_lower( const Point_2  & p1, const Point_2  & p2 ) const
  { 
    return (compare_y(p1, p2) == SMALLER); 
  }
  
  bool point_is_higher( const Point_2  & p1, const Point_2  & p2 ) const
  {
    return (compare_y(p1, p2) == LARGER); 
  }
  
  bool point_is_same_y( const Point_2  & p1, const Point_2  & p2 ) const
  {
    return (compare_y(p1, p2) == EQUAL); 
  }
  
  bool point_is_same( const Point_2  & p1, const Point_2  & p2 ) const
  { 
#ifdef PM_MISC_USE_ISSAME
    return is_same(p1, p2);
#else
    return ( (compare_y(p1, p2) == EQUAL) &&
             (compare_x(p1, p2) == EQUAL)   );	
#endif
  }
  
  bool point_is_left_low( const Point_2  & p1,  
                          const Point_2  & p2 ) const
  { 
    Comparison_result k = compare_x(p1, p2);
    if (k == SMALLER)
      return true;
    if ( (k == EQUAL) && (point_is_lower(p1, p2)) )
      return true;
    return false;
  }
  bool point_is_right_top( const Point_2  & p1,  
                          const Point_2  & p2 ) const
  { 
	  return point_is_left_low(p2,p1);
  }
  const Point_2& point_leftmost(const Point_2 &p1, const Point_2 &p2) const
  { return (point_is_left(p1, p2) ? p1 : p2); }
  const Point_2& point_rightmost(const Point_2 &p1, const Point_2 &p2) const
  { return (point_is_right(p1, p2) ? p1 : p2); }
  const Point_2& point_lowest(const Point_2 &p1, const Point_2 &p2) const
  { return (point_is_lower(p1, p2) ? p1 : p2); }
  const Point_2& point_highest(const Point_2 &p1, const Point_2 &p2) const
  { return (point_is_higher(p1, p2) ? p1 : p2); }
  const Point_2& point_leftlow_most(const Point_2 &p1, const Point_2 &p2) const
  { return (point_is_left_low(p1, p2) ? p1 : p2); }
  const Point_2& point_righttop_most(const Point_2 &p1, const Point_2 &p2)const
  { return (point_is_right_top(p1, p2) ? p1 : p2); }
  Point_2 curve_leftmost(const X_curve& cv) const 
  {
    return point_leftmost(curve_source(cv),curve_target(cv));
  }
  Point_2 curve_rightmost(const X_curve& cv) const
  {
    return point_rightmost(curve_source(cv),curve_target(cv));
  }
  Point_2 curve_lowest(const X_curve& cv) const
  {
    return point_lowest(curve_source(cv),curve_target(cv));
  }
  Point_2 curve_highest(const X_curve& cv) const
  {
    return point_highest(curve_source(cv),curve_target(cv));
  }
  Point_2 curve_leftlow_most(const X_curve& cv) const 
  {
    if (!curve_is_vertical(cv)) return curve_leftmost(cv);
    return curve_lowest(cv);
  }
  Point_2 curve_righttop_most(const X_curve& cv) const
  {
    if (!curve_is_vertical(cv)) return curve_rightmost(cv);
    return curve_highest(cv);
  }
  bool curve_merge_condition(const X_curve& whole,
			     const X_curve& part1,
			     const X_curve& part2) const
  {
    return 
      point_is_same(curve_leftlow_most(whole),curve_leftlow_most(part1))&&
      point_is_same(curve_righttop_most(part1),curve_leftlow_most(part2))&&
      point_is_same(curve_righttop_most(whole),curve_righttop_most(part2))||
      point_is_same(curve_leftlow_most(whole),curve_leftlow_most(part2))&&
      point_is_same(curve_righttop_most(part2),curve_leftlow_most(part1))&&
      point_is_same(curve_righttop_most(whole),curve_righttop_most(part1));
  }
  inline bool curve_is_degenerate(const X_curve& cv) const
  {
    return point_is_same(curve_source(cv),curve_target(cv));
  }
public:
  /* precondition:
       cv1,cv2 are adjacent to q
     postcondition:
       returns which of cv1,cv2 is first in clockwise sweep around q
       starting from bottom direction.
  */
  Comparison_result 
  curve_compare_at_x_from_bottom(const X_curve &cv1, 
				 const X_curve &cv2, 
				 const Point_2& q) const 
    {
      if (!curve_is_vertical(cv1))
        if (!curve_is_vertical(cv2))
          if (point_is_same(curve_rightmost(cv1),q)) 
            // cv1 extends leftwards from q
            {
              if (point_is_same(curve_rightmost(cv2),q))
				// cv2 extends leftwards from q
                {
                  return curve_compare_at_x_left(cv1,cv2,q);
                }
              else // cv2 extends rightwards from q
                {
                  return SMALLER;
                }
            }
          else  // cv1 extends rightwards from q
            {
              if (point_is_same(curve_leftmost(cv2),q))
				// cv2 extends rightwards from q
                {
                  return curve_compare_at_x_right(cv2,cv1,q);
                }
              else // cv2 extends leftwards from q
                {
                  return LARGER;
                }
            }
        else // cv2 is vertical, cv1 is not vertical 
          {
            if (point_is_same(curve_rightmost(cv1),q) && 
		point_is_same(curve_lowest(cv2),   q))
              return SMALLER;
            else
              return LARGER;
          }
      else // cv1 is vertical
	{
          if (point_is_same(curve_highest(cv1),q))
            if (!curve_is_vertical(cv2) || point_is_same(curve_lowest(cv2),q))
              return SMALLER;
            else
              return EQUAL; // both curves extend downwards
          else // cv1 extends from q upwards
            if (point_is_same(curve_righttop_most(cv2),q))
              return LARGER;
            else if (!curve_is_vertical(cv2)) // extends rightwards
              return SMALLER;
            else // cv2 extends upwards
              return EQUAL;
	}
    }
  
  Comparison_result 
  curve_compare_at_x_from_top(const X_curve &cv1, 
			      const X_curve &cv2, 
			      const Point_2& q) 
    const 
    {
      if (!curve_is_vertical(cv1))
        if (!curve_is_vertical(cv2))
          if (point_is_same(curve_rightmost(cv1),q)) 
            // cv1 extends leftwards from q
            {
              if (point_is_same(curve_rightmost(cv2),q))
				// cv2 extends leftwards from q
                {
                  return curve_compare_at_x_left(cv1,cv2,q);
                }
              else // cv2 extends rightwards from q
                {
                  return LARGER;
                }
            }
          else  // cv1 extends rightwards from q
            {
              if (point_is_same(curve_leftmost(cv2),q))
				// cv2 extends rightwards from q
                {
                  return curve_compare_at_x_right(cv2,cv1,q);
                }
              else // cv2 extends leftwards from q
                {
                  return SMALLER;
                }
            }
        else // cv2 is vertical, cv1 is not vertical 
          {
            if (point_is_same(curve_leftmost(cv1),q) &&
		point_is_same(curve_highest(cv2), q))
              return SMALLER;
            else
              return LARGER;
          }
      else // cv1 is vertical
	{
          if (point_is_same(curve_lowest(cv1),q))
            if (!curve_is_vertical(cv2) || point_is_same(curve_highest(cv2),q))
              return SMALLER;
            else
              return EQUAL; // both curves extend upwards
          else // cv1 extends from q downwards
            if (point_is_same(curve_leftlow_most(cv2),q))
              return LARGER;
            else if (!curve_is_vertical(cv2)) // extends leftwards
              return SMALLER;
            else // cv2 extends downwards
              return EQUAL;
	}
    }
  bool curve_is_unbounded(const X_curve& cv) const 
  {
    return 
      curve_is_source_unbounded(cv)||
      curve_is_target_unbounded(cv);
  }

  Comparison_result
  compare_xy(const Point &p, const Point &q)
  {
    Comparison_result c = compare_x(p,q);
    return (c != EQUAL) ? c : compare_y(p,q);
  }

};


CGAL_END_NAMESPACE
 
#endif  //CGAL_PLANAR_MAP_MISC_H 

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 *     
 * Planar_map_misc.h - End of File
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
