// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/predicate_objects_on_points_2.h
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_PREDICATE_OBJECTS_ON_POINTS_2_H
#define CGAL_PREDICATE_OBJECTS_ON_POINTS_2_H

#include <CGAL/user_classes.h>
template <class Point>
class CGAL_p_Left_of_line_2p
{
public:
        CGAL_p_Left_of_line_2p(const Point& a, const Point& b)
         : p_a(a), p_b(b)
        {}

  bool  operator()(const Point& c) const
        { return CGAL_leftturn( p_a, p_b, c ); }

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
        { return CGAL_rightturn( p_a, p_b, c ); }

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
struct CGAL_p_Less_xy
{
  bool operator()( const Point& p1, const Point& p2)
       { return CGAL_lexicographically_xy_smaller( p1, p2); }
};

template <class Point>
struct CGAL_p_Greater_xy
{
  bool operator()( const Point& p1, const Point& p2)
       { return CGAL_lexicographically_xy_larger( p1, p2); }
};

template <class Point>
struct CGAL_p_Less_yx
{
  bool operator()( const Point& p1, const Point& p2)
       { return CGAL_lexicographically_yx_smaller( p1, p2); }
};

template <class Point>
struct CGAL_p_Greater_yx
{
  bool operator()( const Point& p1, const Point& p2)
       { return CGAL_lexicographically_yx_larger( p1, p2); }
};

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

  bool  operator()(const Point& p, const Point& q)
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
              if (p == q)         return false;
              return  CGAL_collinear_are_ordered_along_line( rot_point, q, p);
          }
        }

  void  set_rotation_center( const Point& p)
        { rot_point = p; }


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

  bool  operator()(const Point& p, const Point& q)
        {
          if (p == rot_point) return false;
          if (q == rot_point) return true;
          if (p == q)         return false;
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
  
  void  set_rotation_center( const Point& p)
        { rot_point = p; }


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

  bool  operator()(const Point& p, const Point& q)
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

  void  set_rotation_center( const Point& p)
        { rot_point = p; }


private:
  Point  rot_point;
};

template <class R>
class CGAL_r_Right_of_line
{
public:
        CGAL_r_Right_of_line(const CGAL_Point_2<R>& a, 
                             const CGAL_Point_2<R>& b)
         : l_ab( a, b )
        {}

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
        { return (l_ab.oriented_side(c) == CGAL_ON_POSITIVE_SIDE); }

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

template <class R>
class CGAL_r_Less_in_direction
{
public:
        typedef typename  R::RT   RT;

        CGAL_r_Less_in_direction( const CGAL_Direction_2<R>& dir )
        : l( CGAL_Point_2<R>( RT(0) , RT(0) ),
             CGAL_Direction_2<R>(-(dir.dy()), dir.dx() ))
        {}

  bool  operator()(const CGAL_Point_2<R>& c, const CGAL_Point_2<R>& d)
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

template <class Point>
struct CGAL_p_Leftturn
{
  bool  operator()(const Point& p, const Point& q, const Point& r) const
        { return CGAL_leftturn(p,q,r); }
};

template <class Point>
struct CGAL_p_Rightturn
{
  bool  operator()(const Point& p, const Point& q, const Point& r) const
        { return CGAL_rightturn(p,q,r); }
};

template <class Point>
struct CGAL_p_Orientation
{
  CGAL_Orientation  
        operator()(const Point& p, const Point& q, const Point& r) const
        { return CGAL_orientation(p,q,r); }
};


#endif // CGAL_PREDICATE_OBJECTS_ON_POINTS_2_H
