// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Triangulation_indirect_traits_2.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/07/10 12:58:39 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Traits class for triangulation of circulators over points
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_INDIRECT_TRAITS_2_H
#define CGAL_TRIANGULATION_INDIRECT_TRAITS_2_H

#include <CGAL/Kernel/function_objects.h>

namespace CGAL {

template <class Circulator>
class Indirect_segment 
{
public:
   Indirect_segment() {}
   Indirect_segment(Circulator s, Circulator t) : _source_ref(s), 
                                                  _target_ref(t)
   {}
   Circulator source() {return _source_ref;}
   Circulator target() {return _target_ref;}

private:
   Circulator _source_ref;
   Circulator _target_ref;
};

template <class Circulator>
class Indirect_triangle 
{
public:
   Indirect_triangle() {}
   Indirect_triangle(Circulator p0, Circulator p1, Circulator p2): 
       _p0(p0), _p1(p1), _p2(p2) 
   {}

private:
   Circulator _p0, _p1, _p2;
};

template <class Compare_x_2>
class Indirect_compare_x_2
{
public:
   Indirect_compare_x_2(): _compare_x_2(Compare_x_2())
   {}

   template <class Point_2_ptr>
   Comparison_result operator()(Point_2_ptr p1, Point_2_ptr p2)
   {
      return _compare_x_2(*p1, *p2);
   }

private:
   Compare_x_2 _compare_x_2;
};

template <class Compare_y_2>
class Indirect_compare_y_2
{
public:
   Indirect_compare_y_2(): _compare_y_2(Compare_y_2())
   {}

   template <class Point_2_ptr>
   Comparison_result operator()(Point_2_ptr p1, Point_2_ptr p2)
   {
      return _compare_y_2(*p1, *p2);
   }

private:
   Compare_y_2 _compare_y_2;
};

template <class Orientation_2>
class Indirect_orientation_2
{
public:
   Indirect_orientation_2(): _orientation_2(Orientation_2())
   {}

   template <class Point_2_ptr>
   Orientation operator()(Point_2_ptr p1, Point_2_ptr p2, Point_2_ptr p3)
   {
      return _orientation_2(*p1, *p2, *p3);
   }

private:
   Orientation_2 _orientation_2;
};

template <class Circulator, class Traits>
class Triangulation_indirect_traits_2 
{
public:

  typedef Circulator                      Point_2;
  typedef Indirect_segment<Circulator>    Segment_2;
  typedef Indirect_triangle<Circulator>   Triangle_2;
  typedef Indirect_orientation_2<typename Traits::Orientation_2> Orientation_2;
  typedef Indirect_compare_x_2<typename Traits::Compare_x_2>     Compare_x_2;
  typedef Indirect_compare_y_2<typename Traits::Compare_y_2>     Compare_y_2;
  typedef CGALi::Construct<Segment_2>      Construct_segment_2;

   Compare_x_2 compare_x_2_object() const
   {
      return Compare_x_2();
   }  

   Compare_y_2 compare_y_2_object() const
   {
      return Compare_y_2();
   }  

   Orientation_2 orientation_2_object() const
   {
      return Orientation_2();
   }

   Construct_segment_2
   construct_segment_2_object() const
   { return Construct_segment_2(); }

private:
   Orientation_2 _orientation_2;
   Compare_x_2 _compare_x_2;
   Compare_y_2 _compare_y_2;
};

}

#endif // CGAL_TRIANGULATION_INDIRECT_TRAITS_2_H
