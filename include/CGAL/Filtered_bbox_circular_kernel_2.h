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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Circular_kernel_2/include/CGAL/Filtered_bbox_circular_kernel_2.h $
// $Id: Filtered_bbox_circular_kernel_2.h 51456 2009-08-24 17:10:04Z spion $
//
// Author(s)     : Monique Teillaud, Sylvain Pion, Pedro Machado

// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_FILTERED_BBOX_CIRCULAR_KERNEL_2_H
#define CGAL_FILTERED_BBOX_CIRCULAR_KERNEL_2_H

#include <CGAL/Circular_arc_2.h>
#include <CGAL/Line_arc_2.h>
#include <CGAL/Circular_arc_point_2.h>
#include <CGAL/Filtered_bbox_circular_kernel_2/bbox_filtered_predicates.h>

CGAL_BEGIN_NAMESPACE

namespace internal {

template < class FilteredBboxKernel, class CircularKernel >
struct Filtered_bbox_circular_kernel_base_ref_count : public CircularKernel
{
	
	typedef CGAL::Circular_arc_2<FilteredBboxKernel>           Circular_arc_2;
  typedef CGAL::Line_arc_2<FilteredBboxKernel>               Line_arc_2;
  typedef CGAL::Circular_arc_point_2<FilteredBboxKernel>     Circular_arc_point_2;
	
  // The mechanism that allows to specify reference-counting or not.
  template < typename T >
  struct Handle { typedef Handle_for<T>    type; };

  template < typename Kernel2 >
  struct Base { typedef Filtered_bbox_circular_kernel_base_ref_count<Kernel2, CircularKernel>  Type; };  

  template < typename T >
  struct Ambient_dimension {
      typedef typename T::Ambient_dimension type;
  };

  template < typename T >
  struct Feature_dimension {
      typedef typename T::Feature_dimension type;
  };

  #define CGAL_Filtered_Bbox_Circular_Kernel_pred(Y,Z) \
    typedef Bbox_functors::Y< FilteredBboxKernel > Y; \
    Y Z() const { return Y(); }
  #define CGAL_Filtered_Bbox_Circular_Kernel_cons(Y,Z) CGAL_Filtered_Bbox_Circular_Kernel_pred(Y,Z)

  #include <CGAL/Filtered_bbox_circular_kernel_2/interface_macros.h>

};

} // namespace internal

template < typename K_base, typename FbcKernel >
struct Filtered_bbox_circular_kernel_type_equality_wrapper
  : public Type_equality_wrapper<K_base, FbcKernel>
{
    typedef K_base                                  Kernel_base;
    typedef CGAL::Circular_arc_2<FbcKernel>            Circular_arc_2;     
    typedef CGAL::Line_arc_2<FbcKernel>                Line_arc_2;
    typedef CGAL::Circular_arc_point_2<FbcKernel>      Circular_arc_point_2;
};

template < class CircularKernel >
struct Filtered_bbox_circular_kernel_2
  : public Filtered_bbox_circular_kernel_type_equality_wrapper
     < internal::Filtered_bbox_circular_kernel_base_ref_count
         < Filtered_bbox_circular_kernel_2< CircularKernel >,
           typename CircularKernel:: template 
           Base<Filtered_bbox_circular_kernel_2< CircularKernel > >::Type
	 >,
       Filtered_bbox_circular_kernel_2< CircularKernel >
     >
{
  typedef CircularKernel                                         Circular_kernel;
  typedef Filtered_bbox_circular_kernel_2< CircularKernel >      Self;
};

CGAL_END_NAMESPACE

#endif // CGAL_FILTERED_BBOX_CIRCULAR_KERNEL_2_H
