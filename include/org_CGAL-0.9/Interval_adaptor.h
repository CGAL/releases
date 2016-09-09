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


// file  : include/CGAL/Interval_adaptor.h
// source: include/CGAL/Interval_adaptor.h
// author: Gabriele Neyer
// $Revision: 1.1.1.1 $
// $Date: 1997/05/16 11:18:52 $

#ifndef __CGAL_Interval_adaptor__
#define __CGAL_Interval_adaptor__

template <class _Segment, class _Point>
class CGAL_Segment_interval_adaptor_2
{
 private:
  _Segment segment;
 public:
  typedef _Point T1;
  typedef _Point T2;
  typedef _Segment RepClass;
  typedef _Point  Point;

  CGAL_Segment_interval_adaptor_2<_Segment, _Point>(_Segment r)
  {
    segment = r;
  }
  CGAL_Segment_interval_adaptor_2<_Segment, _Point>(){}
  /* return lower point */
  T1 low_1() const {return segment.source();}
  T2 low_2() const {return segment.source();}
  /* return upper point */
  T1 high_1() const {return segment.target();}
  T2 high_2() const {return segment.target();}
};

template <class _Rectangle, class _Point>
class CGAL_Iso_rectangle_interval_adaptor_2
{
 private:
  _Rectangle rectangle;
 public:
  typedef _Point T1;
  typedef _Point T2;
  typedef _Rectangle RepClass;
  typedef _Point  Point;

  CGAL_Iso_rectangle_interval_adaptor_2<_Rectangle, _Point>(_Rectangle r)
  {
    rectangle = r;
  }
  CGAL_Iso_rectangle_interval_adaptor_2<_Rectangle, _Point>(){}
  /* return lower left point */
  T1 low_1() const {return rectangle.min();}
  T2 low_2() const {return rectangle.min();}
  /* return upper right point */
  T2 high_1() const {return rectangle.max();}
  T2 high_2() const {return rectangle.max();}
};


#endif
