// Copyright (c) 1997   INRIA Sophia-Antipolis (France).
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
// $Source: /CVSROOT/CGAL/Packages/Triangulation_2/include/CGAL/Regular_triangulation_euclidean_traits_2.h,v $
// $Revision: 1.25 $ $Date: 2003/09/18 10:26:07 $
// $Name: current_submission $
//
// Author(s)     : Mariette Yvinec <Mariette.Yvinec@sophia.inria.fr>
//                 Sylvain Pion <Sylvain.Pion@sophia.inria.fr>

#ifndef CGAL_REGULAR_TRIANGULATION_EUCLIDEAN_TRAITS_2_H
#define CGAL_REGULAR_TRIANGULATION_EUCLIDEAN_TRAITS_2_H

#include <CGAL/Triangulation_euclidean_traits_2.h>
#include <CGAL/Weighted_point.h>
#include <CGAL/number_utils_classes.h>

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#if defined CGAL_CARTESIAN_H || defined CGAL_SIMPLE_CARTESIAN_H
#include <CGAL/predicates/Regular_triangulation_ftC2.h>
#include <CGAL/constructions_on_weighted_points_cartesian_2.h>
#endif

#if defined CGAL_HOMOGENEOUS_H || defined CGAL_SIMPLE_HOMOGENEOUS_H
#include <CGAL/predicates/Regular_triangulation_rtH2.h>
#include <CGAL/constructions_on_weighted_points_homogeneous_2.h>
#endif

CGAL_BEGIN_NAMESPACE 

// constructions for DUALITY: weighted_circumcenter and radical 
//  axis
template < class Bare_point, class We >
inline
Bare_point
weighted_circumcenter(const Weighted_point< Bare_point,We >& p,
		      const Weighted_point< Bare_point,We >& q,
		      const Weighted_point< Bare_point,We >& r,
		      Cartesian_tag )
{
  
  typename Bare_point::R::RT x,y;
  weighted_circumcenterC2(p.x(),p.y(),p.weight(),
			  q.x(),q.y(),q.weight(),
			  r.x(),r.y(),r.weight(),x,y);
  return Bare_point(x,y);
}

template < class Bare_point, class We >
inline
Bare_point
weighted_circumcenter(const Weighted_point< Bare_point,We >& p,
		      const Weighted_point< Bare_point,We >& q,
		      const Weighted_point< Bare_point,We >& r,
		      Homogeneous_tag )
{
  
  typename Bare_point::R::RT x,y,w;
  weighted_circumcenterH2(p.hx(),p.hy(),p.hw(),p.weight(),
			  q.hx(),q.hy(),q.hw(),q.weight(),
			  r.hx(),r.hy(),r.hw(),r.weight(),
			  x,y,w);
  return Bare_point(x,y,w);
}


template < class Bare_point, class We >
inline
Bare_point
weighted_circumcenter(const Weighted_point< Bare_point,We >& p,
		      const Weighted_point< Bare_point,We >& q,
		      const Weighted_point< Bare_point,We >& r)
{
  typedef typename Bare_point::R::Rep_tag Tag;
  return weighted_circumcenter(p, q, r, Tag()); 
}


template <class Bare_point, class Weight>
class Construct_weighted_circumcenter_2
{
public:
  typedef CGAL::Weighted_point <Bare_point, Weight>        Weighted_point;
  Bare_point operator() ( Weighted_point p,
		     Weighted_point q,
		     Weighted_point r) 
    {
      CGAL_triangulation_precondition( ! collinear(p, q, r) );
      return CGAL::weighted_circumcenter(p,q,r);
    }
};
 


template < class Bare_point, class We >
inline
Line_2<typename Bare_point::R>
radical_axis(const Weighted_point< Bare_point,We >& p,
	     const Weighted_point< Bare_point,We >& q,
	     Cartesian_tag )
{
  typedef typename Bare_point::R::RT RT;
  typedef typename Bare_point::R     Rep;
  RT a,b,c;
  radical_axisC2(p.x(),p.y(),p.weight(),q.x(),q.y(),q.weight(),a,b,c);
  return Line_2<Rep>(a,b,c);
}

template < class Bare_point, class We >
inline
Line_2<typename Bare_point::R>
radical_axis(const Weighted_point< Bare_point,We >& p,
	     const Weighted_point< Bare_point,We >& q,
	      Homogeneous_tag)
{
  typedef typename Bare_point::R::RT RT;
  typedef typename Bare_point::R     Rep;
  RT a,b,c;
  radical_axisH2(p.hx(),p.hy(), p.hw(), p.weight(),
		 q.hx(),q.hy(), q.hw(), q.weight(),a,b,c);
  return Line_2<Rep>(a,b,c);
}

template < class Bare_point, class We >
inline
Line_2<typename Bare_point::R>
radical_axis(const Weighted_point< Bare_point,We >& p,
	     const Weighted_point< Bare_point,We >& q)
{
  typedef typename Bare_point::R::Rep_tag Tag;
  return radical_axis(p, q, Tag()); 
}


template <class Bare_point, class Weight>
class Construct_radical_axis_2
{
public:
  typedef CGAL::Weighted_point <Bare_point, Weight>   Weighted_point;
  typedef typename Bare_point::R  R;

  Line_2<R> operator() ( Weighted_point p, Weighted_point q) 
  {
    return CGAL::radical_axis(p,q);
  }
};

///-----------------------------------------------------------


template < class Bare_point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Bare_point, Weight> &p,
           const Weighted_point<Bare_point, Weight> &q,
           const Weighted_point<Bare_point, Weight> &r,
           const Weighted_point<Bare_point, Weight> &t,
	   Cartesian_tag )
{
  typedef typename Bare_point::R::FT  FT;
  return power_testC2(p.x(), p.y(), FT(p.weight()),
		      q.x(), q.y(), FT(q.weight()),
		      r.x(), r.y(), FT(r.weight()),
		      t.x(), t.y(), FT(t.weight()));
}

template < class Bare_point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Bare_point, Weight> &p,
           const Weighted_point<Bare_point, Weight> &q,
           const Weighted_point<Bare_point, Weight> &r,
           const Weighted_point<Bare_point, Weight> &t,
	   Homogeneous_tag )
{
  typedef typename Bare_point::R::RT  RT;
  return power_testH2(p.hx(), p.hy(), p.hw(), RT(p.weight()),
		      q.hx(), q.hy(), q.hw(), RT(q.weight()),
		      r.hx(), r.hy(), r.hw(), RT(r.weight()),
		      t.hx(), t.hy(), t.hw(), RT(t.weight()));
}

template < class Bare_point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Bare_point, Weight> &p,
           const Weighted_point<Bare_point, Weight> &q,
           const Weighted_point<Bare_point, Weight> &r,
           const Weighted_point<Bare_point, Weight> &t)
{
  typedef typename Bare_point::R::Rep_tag Tag;
  return power_test(p, q, r, t, Tag());
}
  
template < class Bare_point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Bare_point, Weight> &p,
           const Weighted_point<Bare_point, Weight> &q,
           const Weighted_point<Bare_point, Weight> &t,
	   Cartesian_tag )
{
    typedef typename Bare_point::R::FT  FT;
    return power_testC2(p.x(), p.y(), FT(p.weight()),
                        q.x(), q.y(), FT(q.weight()),
                        t.x(), t.y(), FT(t.weight()));
}


template < class Bare_point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Bare_point, Weight> &p,
           const Weighted_point<Bare_point, Weight> &q,
           const Weighted_point<Bare_point, Weight> &t,
	   Homogeneous_tag )
{
   typedef typename Bare_point::R::RT  RT;
    return power_testH2(p.hx(), p.hy(), p.hw(), RT(p.weight()),
                        q.hx(), q.hy(), q.hw(), RT(q.weight()),
                        t.hx(), t.hy(), t.hw(), RT(t.weight()));
}

template < class Bare_point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Bare_point, Weight> &p,
           const Weighted_point<Bare_point, Weight> &q,
           const Weighted_point<Bare_point, Weight> &t)
{
  typedef typename Bare_point::R::Rep_tag Tag;
  return power_test(p, q, t, Tag());
}

template < class Bare_point, class Weight >
inline
Oriented_side
power_test(const Weighted_point<Bare_point, Weight> &p,
           const Weighted_point<Bare_point, Weight> &t)
{
  typedef typename Bare_point::R::RT  RT;
  Comparison_result r = Compare<RT>()(p.weight(), t.weight());
  if(r == LARGER)    return ON_NEGATIVE_SIDE;
  else if (r == SMALLER) return ON_POSITIVE_SIDE;
  return ON_ORIENTED_BOUNDARY;
}


template <class Bare_point, class Weight>
class Power_test_2
{
public:
  typedef CGAL::Weighted_point <Bare_point, Weight>        Weighted_point;
  Oriented_side operator() ( Weighted_point p,
			     Weighted_point q,
			     Weighted_point r,
			     Weighted_point s) 
    {
      //CGAL_triangulation_precondition( ! collinear(p, q, r) );
      return CGAL::power_test(p,q,r,s);
    }
};

template <class Bare_point, class Weight>
class Power_test_degenerated_2
{
public:
  typedef CGAL::Weighted_point <Bare_point, Weight>        Weighted_point;
  Oriented_side operator() ( Weighted_point p,
			     Weighted_point q,
			     Weighted_point r)
    {
      //CGAL_triangulation_precondition( collinear(p, q, r) );
      //CGAL_triangulation_precondition( p.point() != q.point() );
      return CGAL::power_test(p,q,r);
    }  

  Oriented_side operator() ( Weighted_point p,
			     Weighted_point r)
    {
      //CGAL_triangulation_precondition( p.point() == r.point() );
      return CGAL::power_test(p,r);
    }
};

template < class R, class W = CGAL_TYPENAME_MSVC_NULL  R::RT>
class Regular_triangulation_euclidean_traits_2
  : public Triangulation_euclidean_traits_2<R>
{
public:
  typedef R                                     Rep;
  typedef W                                     Weight;
  typedef Triangulation_euclidean_traits_2 <R>  Traits;
  typedef typename Traits::Point_2              Bare_point;
  typedef CGAL::Weighted_point <Bare_point, W>  Weighted_point;
  // This is required for the point() function of vertex base class
  // to be correctly return a weighted_point;
  // patch 27/11/00
  // 18/03/03 I put now the same typedef in Regulat_triangulation_2
  // for the need of hierarchy
  // don't know if this is definitive
  typedef Weighted_point                        Point_2;

  typedef CGAL::Power_test_2<Bare_point, W>     Power_test_2;
  typedef CGAL::Power_test_degenerated_2<Bare_point, W>  
                                                Power_test_degenerated_2;
 //concstruction objects
  typedef CGAL::Construct_weighted_circumcenter_2<Bare_point, W> 
                                            Construct_weighted_circumcenter_2;
  typedef CGAL::Construct_radical_axis_2<Bare_point, W> 
                                            Construct_radical_axis_2;
  
  Power_test_2 
  power_test_2_object() const
    {  return Power_test_2();}

  Power_test_degenerated_2
  power_test_degenerated_2_object() const
    {return Power_test_degenerated_2();}

  //constructions for dual:
  Construct_weighted_circumcenter_2
  construct_weighted_circumcenter_2_object() const
    {return Construct_weighted_circumcenter_2();}
  
  Construct_radical_axis_2
  construct_radical_axis_2_object() const
    {return Construct_radical_axis_2();}

};
 
CGAL_END_NAMESPACE

#endif // CGAL_REGULAR_TRIANGULATION_EUCLIDEAN_TRAITS_2_H
