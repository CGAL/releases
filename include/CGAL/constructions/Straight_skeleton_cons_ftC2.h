// Copyright (c) 2005, 2006 Fernando Luis Cacciola Carballal. All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.2-branch/Straight_skeleton_2/include/CGAL/constructions/Straight_skeleton_cons_ftC2.h $
// $Id: Straight_skeleton_cons_ftC2.h 29640 2006-03-20 21:25:42Z fcacciola $
//
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_STRAIGHT_SKELETON_CONS_FTC2_H
#define CGAL_STRAIGHT_SKELETON_CONS_FTC2_H 1


CGAL_BEGIN_NAMESPACE 

namespace CGAL_SS_i
{

template<class NT>
inline NT inexact_sqrt( NT const& n )
{
  return CGAL_NTS sqrt(n);
}

inline MP_Float inexact_sqrt( MP_Float const& n )
{
  double d = CGAL::to_double(n);
  
  if ( !CGAL_NTS is_finite(d) )
    d = CGAL_NTS sign(n) == NEGATIVE ? - std::numeric_limits<double>::max() 
                                     :   std::numeric_limits<double>::max() ;
       
  return MP_Float( CGAL_NTS sqrt(d) ) ;
}

inline Quotient<MP_Float> inexact_sqrt( Quotient<MP_Float> const& q )
{
  CGAL_precondition(q > 0);
  return Quotient<MP_Float>(CGAL_SS_i::inexact_sqrt(q.numerator()*q.denominator())
                           ,q.denominator()
                           );
}

// Given an oriented 2D stright line edge (px,py)->(qx,qy), computes the normalized coefficients (a,b,c) of the
// supporting line.
// POSTCONDITION: [a,b] is the leftward normal _unit_ (a�+b�=1) vector.
// POSTCONDITION: In case of overflow, an empty optional<> is returned.
template<class FT>
optional< Line<FT> > compute_normalized_line_ceoffC2( Edge<FT> const& e )
{
  bool finite = true ;
  
  FT a (0.0),b (0.0) ,c(0.0)  ;

  if(e.s().y() == e.t().y())
  {
    a = 0 ;
    if(e.t().x() > e.s().x())
    {
      b = 1;
      c = -e.s().y();
    }
    else if(e.t().x() == e.s().x())
    {
      b = 0;
      c = 0;
    }
    else
    {
      b = -1;
      c = e.s().y();
    }

    CGAL_SSTRAITS_TRACE("Line coefficients for HORIZONTAL line:\npx=" << e.s().x() << "\npy=" << e.s().y()
                        << "\nqx=" << e.t().x() << "\nqy=" << e.t().y()
                        << "\na="<< a << "\nb=" << b << "\nc=" << c
                       ) ;
  }
  else if(e.t().x() == e.s().x())
  {
    b = 0;
    if(e.t().y() > e.s().y())
    {
      a = -1;
      c = e.s().x();
    }
    else if (e.t().y() == e.s().y())
    {
      a = 0;
      c = 0;
    }
    else
    {
      a = 1;
      c = -e.s().x();
    }

    CGAL_SSTRAITS_TRACE("Line coefficients for VERTICAL line:\npx=" << e.s().x() << "\npy=" << e.s().y()
                        << "\nqx=" << e.t().x() << "\nqy=" << e.t().y()
                        << "\na="<< a << "\nb=" << b << "\nc=" << c
                       ) ;
  }
  else
  {
    FT sa = e.s().y() - e.t().y();
    FT sb = e.t().x() - e.s().x();
    FT l2 = (sa*sa) + (sb*sb) ;

    if ( CGAL_NTS is_finite(l2) )
    {
      FT l = CGAL_SS_i :: inexact_sqrt(l2);
  
      a = sa / l ;
      b = sb / l ;
  
      c = -e.s().x()*a - e.s().y()*b;
    }
    else finite = false ;
    
    CGAL_SSTRAITS_TRACE("Line coefficients for line:\npx=" << e.s().x() << "\npy=" << e.s().y() << "\nqx="
                        << e.t().x() << "\nqy=" << e.t().y()
                        << "\na="<< a << "\nb=" << b << "\nc=" << c << "\nl:" << l
                       ) ;
  }
  
  if ( !finite )
    if ( !CGAL_NTS is_finite(a) || !CGAL_NTS is_finite(b) || !CGAL_NTS is_finite(c) ) 
      finite = false ;

  return make_optional( finite, Line<FT>(a,b,c) ) ;
}

// Given 3 oriented straight line segments: e0, e1, e2 [each segment is passed as (sx,sy,tx,ty)]
// returns the OFFSET DISTANCE (n/d) at which the offsetted lines
// intersect at a single point, IFF such intersection exist.
// If the lines intersect to the left, the returned distance is positive.
// If the lines intersect to the right, the returned distance is negative.
// If the lines do not intersect, for example, for collinear edges, or parallel edges but with the same orientation,
// returns 0 (the actual distance is undefined in this case, but 0 is a usefull return)
// NOTE: The result is a explicit rational number returned as a tuple (num,den); the caller must check that den!=0 manually
// (a predicate for instance should return indeterminate in this case)
template<class FT>
optional< Rational<FT> > compute_normal_offset_lines_isec_timeC2 ( SortedTriedge<FT> const& triedge )
{
  FT num(0.0), den(0.0) ;
  
  // DETAILS:
  //
  // An offset line is given by:
  //
  //   a*x(t) + b*y(t) + c - t = 0
  //
  // were 't>0' being to the left of the line.
  // If 3 such offset lines intersect at the same offset distance, the intersection 't',
  // or 'time', can be computed solving for 't' in the linear system formed by 3 such equations.
  //
  //  t = a2*b0*c1 - a2*b1*c0 - b2*a0*c1 + b2*a1*c0 + b1*a0*c2 - b0*a1*c2
  //      ---------------------------------------------------------------
  //             -a2*b1 + a2*b0 + b2*a1 - b2*a0 + b1*a0 - b0*a1 ;

  bool ok = false ;
  
  optional< Line<FT> > l0 = compute_normalized_line_ceoffC2(triedge.e0()) ;
  optional< Line<FT> > l1 = compute_normalized_line_ceoffC2(triedge.e1()) ;
  optional< Line<FT> > l2 = compute_normalized_line_ceoffC2(triedge.e2()) ;

  if ( l0 && l1 && l2 )
  {
    num = (l2->a()*l0->b()*l1->c())
         -(l2->a()*l1->b()*l0->c())
         -(l2->b()*l0->a()*l1->c())
         +(l2->b()*l1->a()*l0->c())
         +(l1->b()*l0->a()*l2->c())
         -(l0->b()*l1->a()*l2->c());
      
    den = (-l2->a()*l1->b())
         +( l2->a()*l0->b())
         +( l2->b()*l1->a())
         -( l2->b()*l0->a())
         +( l1->b()*l0->a())
         -( l0->b()*l1->a());
         
    ok = CGAL_NTS is_finite(num) && CGAL_NTS is_finite(den);     
  }
  
  CGAL_SSTRAITS_TRACE("Normal Event:\nn=" << num << "\nd=" << den  )

  return make_optional(ok,Rational<FT>(num,den)) ;
}


template<class FT>
FT compute_squared_distance ( Vertex<FT> const& p, Vertex<FT> const& q )
{
  return CGAL_NTS square(q.x() - p.x()) + CGAL_NTS square(q.y() - p.y()) ;
}

template<class FT>
optional< Vertex<FT> > compute_oriented_midpoint ( Edge<FT> const& e0, Edge<FT> const& e1 )
{
  bool ok = false ;
  
  FT x(0.0),y(0.0) ;
  
  FT const two(2.0);
  
  FT delta01 = compute_squared_distance(e0.t(),e1.s());
  FT delta10 = compute_squared_distance(e1.t(),e0.s());
  
  if ( CGAL_NTS is_finite(delta01) &&  CGAL_NTS is_finite(delta10) )
  {
    if ( delta01 <= delta10 )
    {
      x = ( e0.t().x() + e1.s().x() ) / two ;
      y = ( e0.t().y() + e1.s().y() ) / two ;
    }
    else
    {
      x = ( e1.t().x() + e0.s().x() ) / two ;
      y = ( e1.t().y() + e0.s().y() ) / two ;
    }
    
    ok = CGAL_NTS is_finite(x) && CGAL_NTS is_finite(y);
  }
  
  return make_optional(ok,Vertex<FT>(x,y));
}

// Given 3 oriented straight line segments: e0, e1, e2 [each segment is passed as (sx,sy,tx,ty)]
// such that e0 and e1 are collinear, not neccesarily consecutive but with the same orientaton, and e2 is NOT
// collinear with e0 and e1; returns the OFFSET DISTANCE (n/d) at which a line perpendicular to e0 (and e1) passing through
// the midpoint of e0.t and e1.s, intersects the offset line of e2
// If the lines intersect to the left of e0, the returned distance is positive.
// If the lines intersect to the right of e0, the returned distance is negative.
// If the lines do not intersect, for example, the three edges are collinear edges, or e0,e1 are not,
// returns 0 (the actual distance is undefined in this case, but 0 is a usefull return)
// NOTE: The result is a explicit rational number returned as a tuple (num,den); the caller must check that den!=0 manually
// (a predicate for instance should return indeterminate in this case)
template<class FT>
optional< Rational<FT> > compute_degenerate_offset_lines_isec_timeC2 ( SortedTriedge<FT> const& triedge )
{
  // DETAILS:
  //
  //   (1)
  //   The bisecting line of e0 and e1 (which are required to be collinear) is a line perpendicular to e0 (and e1)
  //   which passes through the midpoint of e0.target and e1.source (called q)
  //   This "degenerate" bisecting line is given by:
  //
  //     B0(t) = q + t*[l0.a,l0.b]
  //
  //   where l0.a and l0.b are the _normalized_ line coefficients for e0.
  //   Since [a,b] is a _unit_ vector pointing perpendicularly to the left of e0 (and e1);
  //   any point B0(k) is at a distance k from the line supporting e0 and e1.
  //
  //   (2)
  //   The bisecting line of e0 and e2 (which are required to be oblique) is given by the following SEL
  //
  //    l0.a*x(t) + l0.b*y(t) + l0.c + t = 0
  //    l2.a*x(t) + l2.b*y(t) + l2.c + t = 0
  //
  //   where (l0.a,l0.b,l0.c) and (l2.a,l2.b,l0.c) are the normalized line coefficientes of e0 and e2 resp.
  //
  //     B1(t)=[x(t),y(t)]
  //
  //   (3)
  //   These two bisecting lines B0(t) and B1(t) intersect (if they do) in a single point 'p' whose distance
  //   to the lines supporting the 3 edges is exactly 't' (since those expressions are precisely parametrized in a distance)
  //   Solving the following vectorial equation:
  //
  //     [x(y),y(t)] = q + t*[l0.a,l0.b]
  //
  //   for t gives the result we want.
  //
  //
  bool ok = false ;

  optional< Line<FT> > l0 = compute_normalized_line_ceoffC2(triedge.e0()) ;
  optional< Line<FT> > l2 = compute_normalized_line_ceoffC2(triedge.e2()) ;

  optional< Vertex<FT> > q = compute_oriented_midpoint(triedge.e0(),triedge.e1());
  
  FT num(0.0), den(0.0) ;

  if ( l0 && l2 && q )
  {
    if ( ! CGAL_NTS is_zero(l0->b()) ) // Non-vertical
    {
      num = (l2->a() * l0->b() - l0->a() * l2->b() ) * q->x() + l0->b() * l2->c() - l2->b() * l0->c() ;
      den = (l0->a() * l0->a() - 1) * l2->b() + ( 1 - l2->a() * l0->a() ) * l0->b() ;
      
      CGAL_SSTRAITS_TRACE("Non-vertical Degenerate Event:\nn=" << num << "\nd=" << den  )
    }
    else
    {
      num = (l2->a() * l0->b() - l0->a() * l2->b() ) * q->y() - l0->a() * l2->c() + l2->a() * l0->c() ;
      den = l0->a() * l0->b() * l2->b() - l0->b() * l0->b() * l2->a() + l2->a() - l0->a() ;
      
      CGAL_SSTRAITS_TRACE("Vertical Degenerate Event:\nn=" << num << "\nd=" << den  )
    }
    
    ok = CGAL_NTS is_finite(num) && CGAL_NTS is_finite(den);     
  }
  

  return make_optional(ok,Rational<FT>(num,den)) ;
}

template<class FT>
optional< Rational<FT> > compute_offset_lines_isec_timeC2 ( SortedTriedge<FT> const& triedge )
{
  CGAL_precondition ( triedge.collinear_count() < 3 ) ;
  
  return triedge.collinear_count() == 0 ? compute_normal_offset_lines_isec_timeC2    (triedge)
                                        : compute_degenerate_offset_lines_isec_timeC2(triedge);
}

// Given 3 oriented lines l0:(l0.a,l0.b,l0.c), l1:(l1.a,l1.b,l1.c) and l2:(l2.a,l2.b,l2.c)
// such that their offsets at a certian distance intersect in a single point, returns the coordinates (x,y) of such a point.
//
// PRECONDITIONS:
// The line coefficients must be normalized: a�+b�==1 and (a,b) being the leftward normal vector
// The offsets at a certain distance do intersect in a single point.
//
template<class FT>
optional< Vertex<FT> > construct_normal_offset_lines_isecC2 ( SortedTriedge<FT> const& triedge )
{
  FT x(0.0),y(0.0) ;
  
  optional< Line<FT> > l0 = compute_normalized_line_ceoffC2(triedge.e0()) ;
  optional< Line<FT> > l1 = compute_normalized_line_ceoffC2(triedge.e1()) ;
  optional< Line<FT> > l2 = compute_normalized_line_ceoffC2(triedge.e2()) ;

  bool ok = false ;
  
  if ( l0 && l1 && l2 )
  {
    FT den = l0->a()*l2->b() - l0->a()*l1->b() - l1->a()*l2->b() + l2->a()*l1->b() + l0->b()*l1->a() - l0->b()*l2->a();
  
    CGAL_SSTRAITS_TRACE("Event Point:\n  d=" << den  )
  
    CGAL_assertion ( ! CGAL_NTS certified_is_zero(den) ) ;
  
    FT numX = l0->b()*l2->c() - l0->b()*l1->c() - l1->b()*l2->c() + l2->b()*l1->c() + l1->b()*l0->c() - l2->b()*l0->c();
    FT numY = l0->a()*l2->c() - l0->a()*l1->c() - l1->a()*l2->c() + l2->a()*l1->c() + l1->a()*l0->c() - l2->a()*l0->c();
  
    if ( CGAL_NTS is_finite(den) && CGAL_NTS is_finite(numX) && CGAL_NTS is_finite(numY)  )
    {
      ok = true ;
      
      x =  numX / den ;
      y = -numY / den ;
    }
    
  }
    
  CGAL_SSTRAITS_TRACE("\n  x=" << x << "\n  y=" << y )
    
  return make_optional(ok,Vertex<FT>(x,y)) ;
}

// Given 3 oriented lines l0:(l0.a,l0.b,l0.c), l1:(l1.a,l1.b,l1.c) and l2:(l2.a,l2.b,l2.c)
// such that their offsets at a certian distance intersect in a single point, returns the coordinates (x,y) of such a point.
//
// PRECONDITIONS:
// The line coefficients must be normalized: a�+b�==1 and (a,b) being the leftward normal vector
// The offsets at a certain distance do intersect in a single point.
//
template<class FT>
optional< Vertex<FT> > construct_degenerate_offset_lines_isecC2 ( SortedTriedge<FT> const& triedge )
{
  FT x(0.0),y(0.0) ;
  
  optional< Line<FT> > l0 = compute_normalized_line_ceoffC2(triedge.e0()) ;
  optional< Line<FT> > l1 = compute_normalized_line_ceoffC2(triedge.e1()) ;
  optional< Line<FT> > l2 = compute_normalized_line_ceoffC2(triedge.e2()) ;
  
  optional< Vertex<FT> > q = compute_oriented_midpoint(triedge.e0(),triedge.e1());

  bool ok = false ;
  
  if ( l0 && l1 && l2 && q )
  {
  
    FT num, den ;
  
    if ( ! CGAL_NTS is_zero(l0->b()) ) // Non-vertical
    {
      num = (l2->a() * l0->b() - l0->a() * l2->b() ) * q->x() + l0->b() * l2->c() - l2->b() * l0->c() ;
      den = (l0->a() * l0->a() - 1) * l2->b() + ( 1 - l2->a() * l0->a() ) * l0->b() ;
    }
    else
    {
      num = (l2->a() * l0->b() - l0->a() * l2->b() ) * q->y() - l0->a() * l2->c() + l2->a() * l0->c() ;
      den = l0->a() * l0->b() * l2->b() - l0->b() * l0->b() * l2->a() + l2->a() - l0->a() ;
    }
  
    CGAL_precondition( den != static_cast<FT>(0.0) ) ;
  
    if ( CGAL_NTS is_finite(den) && CGAL_NTS is_finite(num) )
    {
      x = q->x() + l0->a() * num / den  ;
      y = q->y() + l0->b() * num / den  ;
      
      ok = CGAL_NTS is_finite(x) && CGAL_NTS is_finite(y) ;
    }
  }
  

  CGAL_SSTRAITS_TRACE("\n  x=" << x << "\n  y=" << y )

  return make_optional(ok,Vertex<FT>(x,y)) ;
}


template<class FT>
optional< Vertex<FT> > construct_offset_lines_isecC2 ( SortedTriedge<FT> const& triedge )
{
  CGAL_precondition ( triedge.collinear_count() < 3 ) ;
  
  return triedge.collinear_count() == 0 ? construct_normal_offset_lines_isecC2    (triedge)
                                        : construct_degenerate_offset_lines_isecC2(triedge) ;
}

// Give a point (px,py) and 3 oriented lines l0:(l0.a,l0.b,l0.c), l1:(l1.a,l1.b,l1.c) and l2:(l2.a,l2.b,l2.c),
// such that their offsets at a certian distance intersect in a single point (ix,iy),
// returns the squared distance between (px,py) and (ix,iy)
//
// PRECONDITIONS:
// The line coefficients must be normalized: a�+b�==1 and (a,b) being the leftward normal vector
// The offsets at a certain distance do intersect in a single point.
//
template<class FT>
optional< FT > compute_offset_lines_isec_dist_to_pointC2 ( optional< Vertex<FT> > const& p, SortedTriedge<FT> const& triedge )
{
  FT sdist ;
    
  optional< Vertex<FT> > i = construct_offset_lines_isecC2(triedge);

  bool ok = false ;
  
  if ( p && i )
  {
    FT dx  = i->x() - p->x() ;
    FT dy  = i->y() - p->y() ;
    FT dx2 = dx * dx ;
    FT dy2 = dy * dy ;
  
    sdist = dx2 + dy2 ;
    
    ok = CGAL_NTS is_finite(sdist);
  }

  return make_optional(ok,sdist);
}

} // namnepsace CGAIL_SS_i

CGAL_END_NAMESPACE

#endif // CGAL_STRAIGHT_SKELETON_CONS_FTC2_H //
// EOF //

