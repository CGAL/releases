// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Planar_map_misc.h
// package       : pm (2.052)
// source        :
// revision      :
// revision_date :
// author(s)     : Iddo Hanniel
//                 Eyal Flato
//                 Oren Nechushtan
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_PLANAR_MAP_MISC_H
#define CGAL_PLANAR_MAP_MISC_H

#ifndef CGAL_PM_CONFIG_H
#include <CGAL/Pm_config.h>
#endif

#ifndef CGAL_POLYHEDRON_ITERATOR_3_H
#include <CGAL/Polyhedron_iterator_3.h>
#endif

//--------------------------------------------------------------------------
// CGAL_Planar_map_traits_wrap - 
//     Geometric Look Up Table. This class extends the user supplied 
// interface to include various less "shallow" operations that are
// impelemented through the interface.
//--------------------------------------------------------------------------

template <class I>
class CGAL_Planar_map_traits_wrap : public I
{
public:
//  typedef  typename I::Info_vertex     Info_vertex;
//  typedef  typename I::Info_edge       Info_edge;
//  typedef  typename I::Info_face       Info_face;
  
  typedef  typename I::X_curve         X_curve;
  typedef  typename I::Point           Point;
  
  CGAL_Planar_map_traits_wrap() : I()
  {
  }
  
  bool point_is_left( const Point  & p1, const Point  & p2 ) const
  {
    return (compare_x(p1, p2) == CGAL_SMALLER); 
  }
  
    bool point_is_right( const Point  & p1, const  Point  & p2 ) const
  {
    return (compare_x(p1, p2) == CGAL_LARGER); 
  }
  
  bool point_is_same_x( const Point  & p1, const Point  & p2 ) const
  {
    return (compare_x(p1, p2) == CGAL_EQUAL); 
  }
  
  bool point_is_lower( const Point  & p1, const Point  & p2 ) const
  { 
    return (compare_y(p1, p2) == CGAL_SMALLER); 
  }
  
  bool point_is_higher( const Point  & p1, const Point  & p2 ) const
  {
    return (compare_y(p1, p2) == CGAL_LARGER); 
  }
  
  bool point_is_same_y( const Point  & p1, const Point  & p2 ) const
  {
    return (compare_y(p1, p2) == CGAL_EQUAL); 
  }
  
  bool point_is_same( const Point  & p1, const Point  & p2 ) const
  { 
    return ( (compare_y(p1, p2) == CGAL_EQUAL) &&
             (compare_x(p1, p2) == CGAL_EQUAL)   );	
  }
  
  bool point_is_left_low( const Point  & p1,  
                          const Point  & p2 ) const
  { 
    CGAL_Comparison_result k = compare_x(p1, p2);
    if (k == CGAL_SMALLER)
      return true;
    if ( (k == CGAL_EQUAL) && (point_is_lower(p1, p2)) )
      return true;
    return false;
  }
  bool point_is_right_top( const Point  & p1,  
                          const Point  & p2 ) const
  { 
	  return point_is_left_low(p2,p1);
  }
  const Point& point_leftmost(const Point &p1, const Point &p2) const
  { return (point_is_left(p1, p2) ? p1 : p2); }
  const Point& point_rightmost(const Point &p1, const Point &p2) const
  { return (point_is_right(p1, p2) ? p1 : p2); }
  const Point& point_lowest(const Point &p1, const Point &p2) const
  { return (point_is_lower(p1, p2) ? p1 : p2); }
  const Point& point_highest(const Point &p1, const Point &p2) const
  { return (point_is_higher(p1, p2) ? p1 : p2); }
  const Point& point_leftlow_most(const Point &p1, const Point &p2) const
  { return (point_is_left_low(p1, p2) ? p1 : p2); }
  const Point& point_righttop_most(const Point &p1, const Point &p2) const
  { return (point_is_right_top(p1, p2) ? p1 : p2); }
  Point curve_leftmost(const X_curve& cv) const 
  {
    return point_leftmost(curve_source(cv),curve_target(cv));
  }
  Point curve_rightmost(const X_curve& cv) const
  {
    return point_rightmost(curve_source(cv),curve_target(cv));
  }
  Point curve_lowest(const X_curve& cv) const
  {
    return point_lowest(curve_source(cv),curve_target(cv));
  }
  Point curve_highest(const X_curve& cv) const
  {
    return point_highest(curve_source(cv),curve_target(cv));
  }
  Point curve_leftlow_most(const X_curve& cv) const 
  {
	  if (!curve_is_vertical(cv)) return curve_leftmost(cv);
	  return curve_lowest(cv);
  }
  Point curve_righttop_most(const X_curve& cv) const
  {
	  if (!curve_is_vertical(cv)) return curve_rightmost(cv);
	  return curve_highest(cv);
  }
  bool curve_merge_condition(const X_curve& whole,const X_curve& part1,const X_curve& part2) const
  {
	  return 
		  point_is_same(curve_leftlow_most(whole),curve_leftlow_most(part1))&&
		  point_is_same(curve_righttop_most(part1),curve_leftlow_most(part2))&&
		  point_is_same(curve_righttop_most(whole),curve_righttop_most(part2))||
		  point_is_same(curve_leftlow_most(whole),curve_leftlow_most(part2))&&
		  point_is_same(curve_righttop_most(part2),curve_leftlow_most(part1))&&
		  point_is_same(curve_righttop_most(whole),curve_righttop_most(part1));
  }
public:
  /* precondition:
		cv1,cv2 are adjacent to q
	 postcondition:
		returns which of cv1,cv2 is first in clockwise sweep around q
		starting from bottom direction.
	*/
    CGAL_Comparison_result 
  curve_compare_at_x_from_bottom(const X_curve &cv1, const X_curve &cv2, const Point& q) 
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
					return CGAL_SMALLER;
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
					return CGAL_LARGER;
				}
			}
		else // cv2 is vertical, cv1 is not vertical 
		{
			if (point_is_same(curve_rightmost(cv1),q)&&point_is_same(curve_lowest(cv2),q))
				return CGAL_SMALLER;
			else
				return CGAL_LARGER;
		}
	else // cv1 is vertical
	{
		if (point_is_same(curve_highest(cv1),q))
			if (!curve_is_vertical(cv2) || point_is_same(curve_lowest(cv2),q))
				return CGAL_SMALLER;
			else
				return CGAL_EQUAL; // both curves extend downwards
		else // cv1 extends from q upwards
			if (point_is_same(curve_righttop_most(cv2),q))
				return CGAL_LARGER;
			else if (!curve_is_vertical(cv2)) // extends rightwards
				return CGAL_SMALLER;
			else // cv2 extends upwards
				return CGAL_EQUAL;
	}
  }

  CGAL_Comparison_result 
  curve_compare_at_x_from_top(const X_curve &cv1, const X_curve &cv2, const Point& q) 
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
					return CGAL_LARGER;
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
					return CGAL_SMALLER;
				}
			}
		else // cv2 is vertical, cv1 is not vertical 
		{
			if (point_is_same(curve_leftmost(cv1),q)&&point_is_same(curve_highest(cv2),q))
				return CGAL_SMALLER;
			else
				return CGAL_LARGER;
		}
	else // cv1 is vertical
	{
		if (point_is_same(curve_lowest(cv1),q))
			if (!curve_is_vertical(cv2) || point_is_same(curve_highest(cv2),q))
				return CGAL_SMALLER;
			else
				return CGAL_EQUAL; // both curves extend upwards
		else // cv1 extends from q downwards
			if (point_is_same(curve_leftlow_most(cv2),q))
				return CGAL_LARGER;
			else if (!curve_is_vertical(cv2)) // extends leftwards
				return CGAL_SMALLER;
			else // cv2 extends downwards
				return CGAL_EQUAL;
	}
  }
};


#else   //CGAL_PLANAR_MAP_MISC_H 
#error  Header file Planar_map_misc.h included twice
#endif  //CGAL_PLANAR_MAP_MISC_H 

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 *     
 * Planar_map_misc.h - End of File
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
