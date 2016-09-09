/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/

// Author: Stefan Schirra


#ifndef CGAL_PREDICATE_OBJECTS_ON_POINTS_2_H
#define CGAL_PREDICATE_OBJECTS_ON_POINTS_2_H

// #include <CGAL/predicates_on_points_2.h>
template <class Point>
class CGAL_p_Left_of_line_2p
{
public:
        CGAL_p_Left_of_line_2p(const Point& a, const Point& b)
         : p_a(a), p_b(b)
        {}

  bool  operator()(const Point& c) const
        {
          return CGAL_leftturn( p_a, p_b, c );
        }

private:
      
    Point p_a;
    Point p_b;
};

template <class Point>
class CGAL_p_Right_of_line_2p
{
public:
        CGAL_p_Right_of_line_2p(const Point& a, const Point& b)
         : p_a(a), p_b(b)
        {}

  bool  operator()(const Point& c) const
        {
          return CGAL_rightturn( p_a, p_b, c );
        }

private:
      
    Point p_a;
    Point p_b;
};

template <class Point>
class CGAL_p_Right_of_line_2p_safer
{
public:
        CGAL_p_Right_of_line_2p_safer(const Point& a, const Point& b)
         : p_a(a), p_b(b)
        {}

  bool  operator()(const Point& c) const
        {
          if ( (c == p_a) || ( c == p_b ) ) return false;
          return CGAL_rightturn( p_a, p_b, c );
        }

private:
      
    Point p_a;
    Point p_b;
};


template <class Point>
class CGAL_p_Less_xy
{
 public:

  bool
  operator()( const Point& p1, const Point& p2)
  {
    return CGAL_lexicographically_xy_smaller( p1, p2);
  }
};

template <class Point>
class CGAL_p_Greater_xy
{
 public:

 bool
 operator()( const Point& p1, const Point& p2)
 {
   return CGAL_lexicographically_xy_larger( p1, p2);
 }
};

template <class Point>
class CGAL_p_Less_yx
{
 public:

 bool
 operator()( const Point& p1, const Point& p2)
 {
   return CGAL_lexicographically_yx_smaller( p1, p2);
 }
};

template <class Point>
class CGAL_p_Greater_yx
{
 public:

 bool
 operator()( const Point& p1, const Point& p2)
 {
   return CGAL_lexicographically_yx_larger( p1, p2);
 }
};



// #include <CGAL/distance_predicates_2.h>
template <class Point>
class CGAL_p_Less_dist_to_line_2p
{
public:
        CGAL_p_Less_dist_to_line_2p(const Point& a, const Point& b)
         : p_a(a), p_b(b)
        {}

  bool  operator()(const Point& c, const Point& d) const
        {
          CGAL_Comparison_result 
            res = CGAL_cmp_signed_dist_to_line( p_a, p_b, c, d);
          if ( res == CGAL_LARGER )
          {
              return false;
          }
          else if ( res == CGAL_SMALLER )
          {
              return true;
          }
          else
          {
              return CGAL_lexicographically_xy_smaller( c, d );
          }
        }

private:

  Point           p_a;
  Point           p_b;
};

template <class Point>
class CGAL_p_Less_negative_dist_to_line_2p
{
public:
        CGAL_p_Less_negative_dist_to_line_2p(const Point& a, const Point& b)
         : p_a(a), p_b(b)
        {}

  bool  operator()(const Point& c, const Point& d) const
        {
          CGAL_Comparison_result 
            res = CGAL_cmp_signed_dist_to_line( p_a, p_b, c, d);
          if ( res == CGAL_LARGER )
          {
              return true;
          }
          else if ( res == CGAL_SMALLER )
          {
              return false;
          }
          else
          {
              return CGAL_lexicographically_xy_smaller( c, d );
          }
        }

private:

  Point           p_a;
  Point           p_b;
};

template <class Point>
class CGAL_p_Less_rotate_ccw
{
public:
        CGAL_p_Less_rotate_ccw(const Point& p)
        : rot_point(p)
        {}

bool    operator()(const Point& p, const Point& q)
        {
          CGAL_Orientation ori = CGAL_orientation(rot_point, p, q);
          if ( ori == CGAL_LEFTTURN )
          {
              return true;
          }
          else if ( ori == CGAL_RIGHTTURN )
          {
              return false;
          }
          else
          {
              if (p == rot_point) return false;
              if (q == rot_point) return true;
              return  CGAL_collinear_are_ordered_along_line( rot_point, q, p);
          }
        }

 private:

 Point  rot_point;
};

template <class Point>
class CGAL_p_Less_rotate_ccw_safer
{
public:
        CGAL_p_Less_rotate_ccw_safer(const Point& p)
        : rot_point(p)
        {}

bool    operator()(const Point& p, const Point& q)
        {
          if (p == rot_point) return false;
          if (q == rot_point) return true;
          CGAL_Orientation ori = CGAL_orientation(rot_point, p, q);
          if ( ori == CGAL_LEFTTURN )
          {
              return true;
          }
          else if ( ori == CGAL_RIGHTTURN )
          {
              return false;
          }
          else
          {
              return  CGAL_collinear_are_ordered_along_line( rot_point, q, p);
          }
        }

 private:

 Point  rot_point;
};

template <class Point>
class CGAL_p_Less_rotate_ccw_E
{
public:
        CGAL_p_Less_rotate_ccw_E(const Point& p)
        : rot_point(p)
        {}

bool    operator()(const Point& p, const Point& q)
        {
          CGAL_Orientation ori = CGAL_orientation(rot_point, p, q);
          if ( ori == CGAL_LEFTTURN )
          {
              return true;
          }
          else if ( ori == CGAL_RIGHTTURN )
          {
              return false;
          }
          else
          {
              return  CGAL_has_larger_dist_to_point( rot_point, p, q) ;
          }
        }

 private:

 Point  rot_point;
};


// #include <CGAL/Line_2.h>
template <class R>
class CGAL_r_Right_of_line
{
public:
        CGAL_r_Right_of_line(const CGAL_Point_2<R>& a, 
                           const CGAL_Point_2<R>& b)
         : l_ab( a, b )
        {
        }

  bool  operator()(const CGAL_Point_2<R>& c) const
        {
          if ( l_ab.is_degenerate() ) return false;
          return (l_ab.oriented_side(c) == CGAL_ON_NEGATIVE_SIDE);
        }

private:
      
  CGAL_Line_2<R>    l_ab;
};

template <class R>
class CGAL_r_Left_of_line
{
public:
        CGAL_r_Left_of_line(const CGAL_Point_2<R>& a, 
                          const CGAL_Point_2<R>& b)
         : l_ab( a, b )
        {}

  bool  operator()(const CGAL_Point_2<R>& c) const
        {
          return (l_ab.oriented_side(c) == CGAL_ON_POSITIVE_SIDE);
        }

private:
      
  CGAL_Line_2<R>    l_ab;
};

template <class R>
class CGAL_r_Less_dist_to_line
{
public:
        CGAL_r_Less_dist_to_line(const CGAL_Point_2<R>& a, 
                               const CGAL_Point_2<R>& b)
         : l_ab( a, b )
        {}

  bool  operator()(const CGAL_Point_2<R>& c, const CGAL_Point_2<R>& d) const
        {
          CGAL_Comparison_result res = CGAL_cmp_signed_dist_to_line(l_ab, c, d);
          if ( res == CGAL_LARGER )
          {
              return false;
          }
          else if ( res == CGAL_EQUAL )
          {
              return CGAL_lexicographically_xy_smaller( c, d );
          }
          else
          {
              return true;
          }
        }

private:

  CGAL_Line_2<R>    l_ab;
};

template <class R>
class CGAL_r_Less_negative_dist_to_line
{
public:
        CGAL_r_Less_negative_dist_to_line(const CGAL_Point_2<R>& a, 
                               const CGAL_Point_2<R>& b)
         : l_ab( a, b )
        {}

  bool  operator()(const CGAL_Point_2<R>& c, const CGAL_Point_2<R>& d) const
        {
          CGAL_Comparison_result res = CGAL_cmp_signed_dist_to_line(l_ab, c, d);
          if ( res == CGAL_LARGER )
          {
              return true;
          }
          else if ( res == CGAL_EQUAL )
          {
              return CGAL_lexicographically_xy_smaller( c, d );
          }
          else
          {
              return false;
          }
        }

private:

  CGAL_Line_2<R>    l_ab;
};



// #include <CGAL/Direction_2.h>
template <class R>
class CGAL_r_Less_in_direction
{
 public:

        CGAL_r_Less_in_direction( const CGAL_Direction_2<R>& dir )
        : l( CGAL_Point_2<R>( R::RT(0) , R::RT(0) ),
             CGAL_Direction_2<R>(-(dir.dy()), dir.dx() ))
        {}

 bool   operator()(const CGAL_Point_2<R>& c, const CGAL_Point_2<R>& d)
        {
          CGAL_Comparison_result res = CGAL_cmp_signed_dist_to_line(l, c, d);
          if ( res == CGAL_LARGER )
          {
              return true;
          }
          else if ( res == CGAL_EQUAL )
          {
              return  CGAL_lexicographically_xy_smaller( c, d) ;
          }
          else
          {
              return false;
          }
        }

 private:

  CGAL_Line_2<R>  l;
};


#endif // CGAL_PREDICATE_OBJECTS_ON_POINTS_2_H


