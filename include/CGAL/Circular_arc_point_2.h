// Copyright (c) 2003-2008  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Circular_kernel_2/include/CGAL/Circular_arc_point_2.h $
// $Id: Circular_arc_point_2.h 46608 2008-10-31 17:08:32Z pmachado $
//
// Author(s)     : Monique Teillaud, Sylvain Pion, Pedro Machado

// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_CIRCULAR_ARC_POINT_2_H
#define CGAL_CIRCULAR_ARC_POINT_2_H

CGAL_BEGIN_NAMESPACE

template < typename CircularKernel >
class Circular_arc_point_2
  : public CircularKernel::Kernel_base::Circular_arc_point_2
{
  typedef typename CircularKernel::Kernel_base::Circular_arc_point_2 
                                               RCircular_arc_point_2;
  typedef typename CircularKernel::Point_2     Point_2;
  typedef typename CircularKernel::Circle_2    Circle_2;

  typedef typename CircularKernel::Root_of_2   Root_of_2;

public:
  typedef typename CircularKernel::Root_for_circles_2_2 
                                               Root_for_circles_2_2;
  typedef CircularKernel                       R; 
  typedef RCircular_arc_point_2                Rep;
  

  const Rep& rep() const
  {
    return *this;
  }

  Rep& rep()
  {
    return *this;
  }

  Circular_arc_point_2()
    : RCircular_arc_point_2(typename R::Construct_circular_arc_point_2()())
  {}


  Circular_arc_point_2(const Root_for_circles_2_2 & np)
    : RCircular_arc_point_2(typename R::Construct_circular_arc_point_2()(np))
  {}

  Circular_arc_point_2(const RCircular_arc_point_2 & p)
    : RCircular_arc_point_2(p)
  {}
      
  Circular_arc_point_2(const Point_2 & p)
    : RCircular_arc_point_2(typename R::Construct_circular_arc_point_2()(p))
  {}
      
  typename Qualified_result_of
  <typename R::Compute_circular_x_2,Circular_arc_point_2>::type
  //const Root_of_2 &
  x() const
  { 
    return typename R::Compute_circular_x_2()(*this); 
  }

  typename Qualified_result_of
  <typename R::Compute_circular_y_2,Circular_arc_point_2>::type
  //const Root_of_2 &
  y() const
  { 
    return typename R::Compute_circular_y_2()(*this); 
  }

  Bbox_2  bbox() const
  { 
    return typename R::Construct_bbox_2()(*this); 
  }

};

  template < typename CircularKernel >
  inline
  bool
  operator==(const Circular_arc_point_2<CircularKernel> &p,
	     const Circular_arc_point_2<CircularKernel> &q)
  {
    return CircularKernel().equal_2_object()(p, q);
  }
  
  template < typename CircularKernel >
  inline
  bool
  operator!=(const Circular_arc_point_2<CircularKernel> &p,
	     const Circular_arc_point_2<CircularKernel> &q)
  {
    return ! (p == q);
  }

  template < typename CircularKernel >
  inline
  bool
  operator<(const Circular_arc_point_2<CircularKernel> &p,
	     const Circular_arc_point_2<CircularKernel> &q)
  {
    return CircularKernel().compare_xy_2_object()(p, q) == CGAL::SMALLER;
  }

  template < typename CircularKernel >
  inline
  bool
  operator>(const Circular_arc_point_2<CircularKernel> &p,
     const Circular_arc_point_2<CircularKernel> &q)
  {
    return CircularKernel().compare_xy_2_object()(p, q) == CGAL::LARGER;
  }

  template < typename CircularKernel >
  inline
  bool
  operator<=(const Circular_arc_point_2<CircularKernel> &p,
	     const Circular_arc_point_2<CircularKernel> &q)
	{
		CGAL::Comparison_result c = CircularKernel().compare_xy_2_object()(p, q);
    return (c == CGAL::SMALLER) || (c == CGAL::EQUAL);
	}

  template < typename CircularKernel >
  inline
  bool
  operator>=(const Circular_arc_point_2<CircularKernel> &p,
     const Circular_arc_point_2<CircularKernel> &q)
  {
    CGAL::Comparison_result c = CircularKernel().compare_xy_2_object()(p, q);
    return (c == CGAL::LARGER) || (c == CGAL::EQUAL);
  }
  
  template < typename CK >
  std::istream &
  operator>>(std::istream & is, Circular_arc_point_2<CK> &p)
  {
    typedef typename CK::Root_of_2               Root_of_2;
    typedef typename CK::Root_for_circles_2_2 Root_for_circles_2_2;
    
    Root_for_circles_2_2 r;
    is >> r;
    if(is)
      p = Circular_arc_point_2<CK>(r);
    return is;
  }

  template < class CK >
  std::ostream&
  operator<<(std::ostream &os, const Circular_arc_point_2<CK> &p)
  {
    return os << p.x() << " " << p.y() << " ";
  }

template < class CK >
struct Filtered_bbox_circular_kernel_2;

template < typename CK >
class Circular_arc_point_2 < Filtered_bbox_circular_kernel_2 < CK > > {

	  typedef Filtered_bbox_circular_kernel_2 < CK >             BK;
    typedef typename CK::FT                                    FT;
    typedef typename CK::RT                                    RT;
    typedef typename BK::Point_2                               Point_2;
    typedef typename CK::Line_2                                Line_2;
    typedef typename CK::Circle_2                              Circle_2;
    typedef typename CK::Circular_arc_point_2                  Rcircular_arc_point_2;
    typedef typename CK::Circular_arc_2                        Circular_arc_2;
    typedef typename CK::Root_of_2                             Root_of_2;

public:
    typedef typename Rcircular_arc_point_2::Root_for_circles_2_2 
     Root_for_circles_2_2;
    typedef BK                          R; 
	  typedef Circular_arc_point_2<BK>    Rep;

	  const Rep& rep() const
	  {
	    return *this;
	  }

	  Rep& rep()
	  {
	    return *this;
	  }

  ////Construction/////
  Circular_arc_point_2()
    : P_point(),bb(NULL)
    {}

  Circular_arc_point_2(const Root_for_circles_2_2 & np)
    : P_point(np), bb(NULL)
      {}

  Circular_arc_point_2(const Point_2 & p)
	  : P_point(p), bb(NULL)
	{}

  Circular_arc_point_2(const Rcircular_arc_point_2 & p)
    : P_point(p),bb(NULL)
      {}

	Circular_arc_point_2(const Circular_arc_point_2 &c) : P_point(c.P_point) 
	{
		if(c.bb) bb = new Bbox_2(*(c.bb));
		else bb = NULL;
	}
	
	~Circular_arc_point_2() { if(bb) delete bb; }

  ////Accesors////
  const Rcircular_arc_point_2& point() const
  {return P_point;}
            
  typename Qualified_result_of<typename R::Compute_circular_x_2,Rcircular_arc_point_2>::type
  x() const
    { return P_point.x();}

  typename Qualified_result_of<typename R::Compute_circular_y_2,Rcircular_arc_point_2>::type
  y() const
    { return P_point.y();}


  ////Bbox related accessors////
  
bool has_no_bbox() const
  { return (bb==NULL);}

  Bbox_2  bbox() const
    { 
      if(this->has_no_bbox())
        bb= new Bbox_2(P_point.bbox());
              
        return *bb;     
    }

    const Root_for_circles_2_2 & coordinates() const 
    { return P_point.coordinates(); }

		bool equal_ref(const Circular_arc_point_2 &p) const
    {
      return CGAL::identical(P_point, p.P_point);      
    }

private:

   Rcircular_arc_point_2  P_point;
   mutable Bbox_2         *bb;

};
  
CGAL_END_NAMESPACE

#endif // CGAL_CIRCULAR_ARC_POINT_2_H
