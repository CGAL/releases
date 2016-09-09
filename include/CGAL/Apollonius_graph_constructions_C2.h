// Copyright (c) 2003  INRIA Sophia-Antipolis (France).
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
// $Source: /CVSROOT/CGAL/Packages/Apollonius_graph_2/include/CGAL/Apollonius_graph_constructions_C2.h,v $
// $Revision: 1.6 $ $Date: 2003/09/18 10:19:20 $
// $Name: CGAL_3_0_1  $
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>



#ifndef CGAL_APOLLONIUS_GRAPH_CONSTRUCTIONS_2_H
#define CGAL_APOLLONIUS_GRAPH_CONSTRUCTIONS_2_H

#include <CGAL/Parabola_segment_2.h>
#include <CGAL/Hyperbola_2.h>
#include <CGAL/Hyperbola_segment_2.h>
#include <CGAL/Hyperbola_ray_2.h>


#include <CGAL/Apollonius_graph_constructions_ftC2.h>



CGAL_BEGIN_NAMESPACE

//***********************************************************************
//***********************************************************************
//                            CONSTRUCTIONS
//***********************************************************************
//***********************************************************************


//-----------------------------------------------------------------------
//                        Apollonius vertex
//-----------------------------------------------------------------------

template < class Gt >
inline
typename Gt::Point_2
ad_circumcenter_2(const typename Gt::Site_2& p,
		  const typename Gt::Site_2& q,
		  const typename Gt::Site_2& r)
{
  typedef typename Gt::Point_2  Point_2;

  typename Gt::FT     x,y;
  ad_circumcenterC2(p.x(),p.y(),p.weight(),
	       	    q.x(),q.y(),q.weight(),
		    r.x(),r.y(),r.weight(),x,y);
  return Point_2(x,y);
}


template < class Gt >
class Construct_Apollonius_vertex_2
{
public:
  typedef typename Gt::Point_2              Point_2;
  typedef typename Gt::Site_2               Site_2;

  Point_2 operator() (const Site_2& p, const Site_2& q,
                      const Site_2& r) const
  {
    return ad_circumcenter_2< Gt >(p,q,r);
  }
};


//-----------------------------------------------------------------------
//                     Apollonius site (dual site)
//-----------------------------------------------------------------------
template < class Gt >
inline
typename Gt::Site_2
ad_circumcircle_2(const typename Gt::Site_2& p,
                  const typename Gt::Site_2& q,
                  const typename Gt::Site_2& r)
{
  typedef typename Gt::Site_2   Site_2;
  typedef typename Gt::Point_2  Point_2;

  typename Gt::FT x, y, wt;
  ad_circumcircleC2(p.x(),p.y(),p.weight(),
		    q.x(),q.y(),q.weight(),
		    r.x(),r.y(),r.weight(),x,y,wt);
  return Site_2(Point_2(x,y), wt);
}

template < class Gt >
inline
typename Gt::Line_2
ad_left_bitangent_line_2(const typename Gt::Site_2& p,
			 const typename Gt::Site_2& q)
{
  typedef typename Gt::Line_2  Line_2;

  typename Gt::FT a, b, c;
  ad_left_bitangent_lineC2(p.x(),p.y(),p.weight(),
			   q.x(),q.y(),q.weight(),
			   a,b,c);
  return Line_2(a, b, c);
}


template < class Gt >
class Construct_Apollonius_site_2
{
public:
  typedef typename Gt::Line_2             Line_2;
  typedef typename Gt::Point_2            Point_2;
  typedef typename Gt::Site_2             Site_2;

  inline Site_2 operator()(const Site_2& p,
			   const Site_2& q,
			   const Site_2& r) const
  {
    //      CGAL_precondition( ! collinear(p, q, r) );
    return ad_circumcircle_2< Gt >(p,q,r);
  }

  inline Line_2 operator()(const Site_2 &p,
			   const Site_2 &q) const
  {
    return ad_left_bitangent_line_2< Gt >(p, q);
  }
};


//-----------------------------------------------------------------------
//                        Apollonius bisector
//-----------------------------------------------------------------------


template< class Gt >
class Construct_Apollonius_bisector_2
{
public:
  typedef typename Gt::Point_2                Point_2;
  typedef typename Gt::Line_2                 Line_2;
  typedef typename Gt::Site_2                 Site_2;
  typedef typename Gt::Object_2               Object_2;
  typedef typename Gt::Construct_object_2     Construct_object_2;
  typedef CGAL::Hyperbola_2<Gt>               Hyperbola_2;

private:
  template<class T>
  Object_2 make_object(const T& t) const
  {
    return Construct_object_2()(t);
  }

public:
  Object_2 operator() (const Site_2& p,	const Site_2& q) const
  {
    Comparison_result cr = CGAL::compare(p.weight(), q.weight());
    if ( cr == EQUAL ) {
      Line_2 l1(p.point(), q.point());
      Line_2 l = l1.perpendicular(midpoint(p.point(), q.point()));
      return make_object(l);
    }

    Hyperbola_2 h(p, q);
    return make_object(h);
  }
};

//-----------------------------------------------------------------------
//                      Apollonius bisector ray
//-----------------------------------------------------------------------


template< class Gt >
class Construct_Apollonius_bisector_ray_2
{
public:
  typedef typename Gt::Point_2               Point_2;
  typedef typename Gt::Line_2                Line_2;
  typedef typename Gt::Ray_2                 Ray_2;
  typedef typename Gt::Site_2                Site_2;
  typedef typename Gt::Object_2              Object_2;
  typedef typename Gt::Construct_object_2    Construct_object_2;
  typedef CGAL::Hyperbola_ray_2<Gt>          Hyperbola_ray_2;
  typedef CGAL::Sign                              Hyperbola_direction;
  typedef CGAL::Construct_Apollonius_vertex_2<Gt> Apollonius_vertex_2;

private:
  template<class T>
  Object_2 make_object(const T& t) const
  {
    return Construct_object_2()(t);
  }

public:
  Object_2
  operator() (const Site_2& p,
	      const Site_2& q,
	      const Point_2& r,
	      const Hyperbola_direction& direction) const {
    //
    Comparison_result cr = CGAL::compare(p.weight(), q.weight());
    if ( cr == EQUAL ) {
      Line_2 l1(q, p);
      Line_2 l = l1.perpendicular(midpoint(p.point(), q.point()));
      Ray_2 ray(r, l.direction());
      return make_object(ray);
    }
    Hyperbola_ray_2 hr(p, q, r, direction);
    return make_object(hr);
  }

  Object_2
  operator() (const Site_2& p,
	      const Site_2& q,
	      const Site_2& r) const {
    Point_2 c = Apollonius_vertex_2()(p, q, r);
    Comparison_result cr = CGAL::compare(p.weight(), q.weight());
    if ( cr == EQUAL ) {
      Line_2 l1(q.point(), p.point());
      Line_2 l = l1.perpendicular(midpoint(p.point(), q.point()));
      Ray_2 ray(c, l.direction());
      return make_object(ray);
    }
    Hyperbola_ray_2 hr(p, q, c, NEGATIVE);
    return make_object(hr);
  }
};

//-----------------------------------------------------------------------
//                    Apollonius bisector segment
//-----------------------------------------------------------------------

template< class Gt >
class Construct_Apollonius_bisector_segment_2
{
public:
  typedef typename Gt::Point_2                 Point_2;
  typedef typename Gt::Segment_2               Segment_2;
  typedef typename Gt::Site_2                  Site_2;
  typedef typename Gt::Object_2                Object_2;
  typedef typename Gt::Construct_object_2      Construct_object_2;
  typedef CGAL::Hyperbola_segment_2<Gt>        Hyperbola_segment_2;
  typedef CGAL::Construct_Apollonius_vertex_2<Gt>     Apollonius_vertex_2;

private:
  template<class T>
  Object_2 make_object(const T& t) const
  {
    return Construct_object_2()(t);
  } 

public:
  inline Object_2 operator() (const Site_2& p,
			      const Site_2& q,
			      const Point_2& r, const Point_2& s) const {
    //
    Comparison_result cr = CGAL::compare(p.weight(), q.weight());
    if ( cr == EQUAL ) {
      Segment_2 seg(r, s);
      return make_object(seg);
    }
    Hyperbola_segment_2 hs(p, q, r, s);
    return make_object(hs);
  }

  inline Object_2 operator() (const Site_2& p,
			      const Site_2& q,
			      const Site_2& r,
			      const Site_2& s) const {
    Apollonius_vertex_2 apollonius_vertex_2;
    Point_2 c_pqr = apollonius_vertex_2(p,q,r);
    Point_2 c_qps = apollonius_vertex_2(q,p,s);
    //
    Comparison_result cr = CGAL::compare(p.weight(), q.weight());
    if ( cr == EQUAL ) {
      Segment_2 seg(c_pqr, c_qps);
      return make_object(seg);
    }
    Hyperbola_segment_2 hs(p, q, c_pqr, c_qps);
    return make_object(hs);
  }

};

//-----------------------------------------------------------------------
//                    Apollonius primal ray
//-----------------------------------------------------------------------


template< class Gt >
class Construct_Apollonius_primal_ray_2
{
private:
  typedef typename Gt::RT                             RT;

public:
  typedef typename Gt::Point_2                        Point_2;
  typedef typename Gt::Line_2                         Line_2;
  typedef typename Gt::Ray_2                          Ray_2;
  typedef typename Gt::Site_2                         Site_2;
  typedef CGAL::Construct_Apollonius_site_2<Gt>       Apollonius_circle_2;

  inline Ray_2 operator() (const Site_2& p,
			   const Site_2& r,
			   const Site_2& s) const {
    //
    Apollonius_circle_2 apollonius_circle_2;
    Line_2 l1 = apollonius_circle_2(r, p);
    Line_2 l2 = apollonius_circle_2(p, s);

    RT d1 = CGAL::sqrt( CGAL::square(l1.a()) + CGAL::square(l1.b()) );
    RT d2 = CGAL::sqrt( CGAL::square(l2.a()) + CGAL::square(l2.b()) );
    RT a = l1.a() / d1 - l2.a() / d2;
    RT b = l1.b() / d1 - l2.b() / d2;
    Point_2 c(p.x() + b, p.y() - a);
    return Ray_2(p.point(), c);
  }
};

//-----------------------------------------------------------------------
//                    Apollonius primal segment
//-----------------------------------------------------------------------

template< class Gt >
class Construct_Apollonius_primal_segment_2
{
public:
  typedef typename Gt::Point_2                        Point_2;
  typedef typename Gt::Line_2                         Line_2;
  typedef typename Gt::Segment_2                      Segment_2;
  typedef typename Gt::Site_2                         Site_2;
  typedef typename Gt::Object_2                       Object_2;
  typedef typename Gt::Construct_object_2             Construct_object_2;
  typedef typename Gt::RT                             Weight;
  typedef CGAL::Hyperbola_segment_2<Gt>               Hyperbola_segment_2;
  typedef CGAL::Parabola_segment_2<Gt>                Parabola_segment_2;
  typedef CGAL::Construct_Apollonius_site_2<Gt>       Apollonius_circle_2;


private:
  template<class T>
  Object_2 make_object(const T& t) const
  {
    return Construct_object_2()(t);
  }

public:

  inline Segment_2
  operator() (const Site_2& p,
	      const Site_2& q) const {
    //
    return Segment_2(p.point(), q.point());
  }

  inline Object_2
  operator() (const Site_2& p,
	      const Site_2& q,
	      const Point_2& r, const Point_2& s) const {
    //
    Comparison_result cr = CGAL::compare(p.weight(), q.weight());
    if ( cr == EQUAL ) {
      Segment_2 seg(r, s);
      return make_object(seg);
    }
    Hyperbola_segment_2 hs(p, q, r, s);
    return make_object(hs);
  }

  inline Object_2
  operator() (const Site_2& p,
	      const Site_2& q,
	      const Site_2& r,
	      const Site_2& s) const {
    Apollonius_circle_2 apollonius_circle_2;
    Site_2 c_pqr = apollonius_circle_2(p, q, r);
    Site_2 c_qps = apollonius_circle_2(q, p, s);
    //
    Comparison_result cr = CGAL::compare(c_pqr.weight(), c_qps.weight());
    if ( cr == EQUAL ) {
      Segment_2 seg(p.point(), q.point());
      return make_object(seg);
    }
    Hyperbola_segment_2 hs(c_pqr, c_qps, p.point(), q.point());
    return make_object(hs);
  }

  inline Parabola_segment_2
  operator() (const Site_2& p,
	      const Site_2& q,
	      const Site_2& r) const {
    //
    Apollonius_circle_2 apollonius_circle_2;
    Site_2 c = apollonius_circle_2(p, q, r);
    Line_2 l = apollonius_circle_2(q, p);
    return Parabola_segment_2(c, l, q.point(), p.point());
  }
};


CGAL_END_NAMESPACE

#endif // CGAL_APOLLONIUS_GRAPH_CONSTRUCTIONS_C2_H
