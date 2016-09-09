#line 162 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/IntersectionC2.fw"
// Source: IntersectionC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_INTERSECTIONC2_H
#define CGAL_INTERSECTIONC2_H

#include <CGAL/LineC2.h>

#line 23 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/IntersectionC2.fw"
template <class FT>
CGAL_INTERSECTIONTYPE  CGAL_intersectiontype(const CGAL_LineC2<FT> &l1,
                                             const CGAL_LineC2<FT> &l2)
{
  assert (0);  // not implemented
  return CGAL_NO_INTERSECTION;
}
#line 170 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/IntersectionC2.fw"


#line 38 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/IntersectionC2.fw"
template <class FT>
inline CGAL_PointC2<FT> CGAL_intersection(const CGAL_LineC2<FT> &l1,
                                         const CGAL_LineC2<FT> &l2)
{
  // Precondition: lines l1 and l2 are not collinear
  FT n = l1.a()*l2.b() - l2.a()*l1.b();
  assert(n != FT(0.0));
  return CGAL_PointC2<FT>( (l1.b()*l2.c() - l2.b()*l1.c())/n,
                          (l2.a()*l1.c() - l1.a()*l2.c())/n );
}
#line 172 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/IntersectionC2.fw"


#line 55 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/IntersectionC2.fw"
template <class FT>
bool CGAL_are_intersecting( const CGAL_SegmentC2<FT> &s1,
                            const CGAL_SegmentC2<FT> &s2,
                            CGAL_PointC2<FT> &intersectionpoint)
{
  // Precondition: segments s1 and s2 are not collinear!
  // BoundingBox test (still missing)
  CGAL_PointC2<FT> line_intersection_point =
    CGAL_intersection(s1.supporting_line(),
                      s2.supporting_line() );
  if (  s1.collinear_is_on(line_intersection_point)
        && s2.collinear_is_on(line_intersection_point) )
    {
      intersectionpoint = line_intersection_point;
      return true;
    }
  else
    {
      return false;
    }
}

template <class FT>
bool CGAL_are_intersecting( const CGAL_SegmentC2<FT> &s,
                            const CGAL_LineC2<FT> &l,
                            CGAL_PointC2<FT> &intersectionpoint)
{
  // Precondition: segment s and line l are not collinear!
  CGAL_PointC2<FT> line_intersection_point =
    CGAL_intersection(s.supporting_line(),l);
  if ( s.collinear_is_on(line_intersection_point) )
    {
      intersectionpoint = line_intersection_point;
      return true;
    }
  else
    {
      return false;
    }
}

template <class FT>
inline bool CGAL_are_intersecting( const CGAL_LineC2<FT> &l,
                                   const CGAL_SegmentC2<FT> &s,
                                   CGAL_PointC2<FT> &intersectionpoint)
{
  // Precondition: segment s and line l are not collinear!
  return CGAL_are_intersecting(s, l, intersectionpoint);
}

template <class FT>
bool
CGAL_are_intersecting( const CGAL_RayC2<FT> &r,
                       const CGAL_SegmentC2<FT> &s,
                       CGAL_PointC2<FT> &intersectionpoint)
{
  // Precondition: segment s and ray r are not collinear!
  CGAL_PointC2<FT> line_intersection_point =
    CGAL_intersection(r.supporting_line(),
                      s.supporting_line() );
  if (s.collinear_is_on(line_intersection_point)
      && r.collinear_is_on(line_intersection_point) )
    {
      intersectionpoint = line_intersection_point;
      return true;
    }
  else
    {
      return false;
    }
}

template <class FT>
inline bool CGAL_are_intersecting( const CGAL_SegmentC2<FT> &s,
                                   const CGAL_RayC2<FT> &r,
                                   CGAL_PointC2<FT> &intersectionpoint)
{
  // Precondition: segment s and ray r are not collinear!
  return CGAL_are_intersecting(r, s, intersectionpoint);
}

template <class FT>
bool CGAL_are_intersecting( const CGAL_RayC2<FT> &r1,
                            const CGAL_RayC2<FT> &r2,
                            CGAL_PointC2<FT> &intersectionpoint)
{
  // Precondition: rays r1 and r2 are not collinear!
  CGAL_PointC2<FT> line_intersection_point =
    CGAL_intersection(r1.supporting_line(),
                      r2.supporting_line() );

  if ( r1.collinear_is_on(line_intersection_point)
       && r2.collinear_is_on(line_intersection_point) )
    {
      intersectionpoint = line_intersection_point;
      return true;
    }
  else
    {
      return false;
    }
}
#line 174 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/IntersectionC2.fw"


#endif
