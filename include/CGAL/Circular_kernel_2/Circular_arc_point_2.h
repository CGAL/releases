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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Circular_kernel_2/include/CGAL/Circular_kernel_2/Circular_arc_point_2.h $
// $Id: Circular_arc_point_2.h 51456 2009-08-24 17:10:04Z spion $
//
// Author(s)     : Monique Teillaud, Sylvain Pion, Pedro Machado

// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_CIRCULAR_KERNEL_CIRCULAR_ARC_POINT_2_H
#define CGAL_CIRCULAR_KERNEL_CIRCULAR_ARC_POINT_2_H

#include <iostream>
#include <CGAL/Bbox_2.h>
#include <CGAL/Interval_nt.h>
#include <boost/type_traits/is_same.hpp>

namespace CGAL {
namespace internal {

  template <class CK >
  class Circular_arc_point_2
  {
    typedef typename CK::FT                      FT;
    typedef typename CK::Root_of_2               Root_of_2;
    typedef typename CK::Point_2                 Point_2;
    
  public: // fixme ?
    typedef typename CK::Root_for_circles_2_2 Root_for_circles_2_2;
    typedef typename CK::template Handle<Root_for_circles_2_2>::type  Base;
    
    Circular_arc_point_2() 
    {}
    
    Circular_arc_point_2(const Root_for_circles_2_2 & np)
      :  _p(np)
    {}

    Circular_arc_point_2(const Point_2 & p)
      :  _p(p.x(),p.y()/*,1,1,-p.x()-p.y()*/)
    {}

    const Root_of_2 & x() const 
    { return get(_p).x(); }
    
    const Root_of_2 & y() const 
    { return get(_p).y(); }
    
    CGAL::Bbox_2 bbox() const
    {
      return get(_p).bbox();
    }

    const Root_for_circles_2_2 & coordinates() const 
    { return get(_p); }

    bool equal_ref(const Circular_arc_point_2 &p) const
    {
      return CGAL::identical(_p, p._p);      
    }

  private:
    Base _p;
  };

  template < typename CK >
  std::ostream &
  print(std::ostream & os, const Circular_arc_point_2<CK> &p)
  {
    return os << "CirclArcEndPoint_2(" << std::endl
	      << p.x() << ", " << p.y() << ')';
  }

} // namespace internal
} // namespace CGAL

#endif // CGAL_CIRCULAR_KERNEL_CIRCULAR_ARC_POINT_2_H
