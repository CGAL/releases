// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/kernel_to_kernel.h
// package       : Kernel_basic (3.90)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2002/04/22 23:43:29 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_KERNEL_TO_KERNEL_H
#define CGAL_KERNEL_TO_KERNEL_H

#ifdef CGAL_USE_LEDA
#include <CGAL/LEDA_basic.h>
#include <CGAL/leda_integer.h>
#include <LEDA/rat_point.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class NumberType>
struct Cartesian_double_to_Homogeneous
{
  typedef Point_2< Homogeneous< NumberType> >    Point2;
  typedef Segment_2< Homogeneous< NumberType> >  Segment;

  Cartesian_double_to_Homogeneous() {}

  Point2
  operator()(  const Point_2<Cartesian<double> >& p) const
  { return Point2( NumberType(p.x()), NumberType(p.y()) ); }

  Segment
  operator()(  const Segment_2<Cartesian<double> >& s) const
  {
    return Segment( Point2( NumberType(s.source().x()),
                            NumberType(s.source().y()) ),
                    Point2( NumberType(s.target().x()),
                            NumberType(s.target().y()) ) );
  }
};

#ifdef CGAL_USE_LEDA
struct Cartesian_double_to_H_double_int
{
  typedef Point_2< Homogeneous< double> >    Point2;
  typedef Segment_2< Homogeneous< double> >  Segment;

  Segment
  operator()(  const Segment_2< Cartesian< double> >& s) const
  {
    leda_rat_point rs =  leda_point(s.source().x(), s.source().y());
    leda_rat_point rt =  leda_point(s.target().x(), s.target().y());

    return Segment(
      Point2(CGAL_LEDA_SCOPE::to_double(rs.X()),
             CGAL_LEDA_SCOPE::to_double(rs.Y()),
             CGAL_LEDA_SCOPE::to_double(rs.W())),
      Point2(CGAL_LEDA_SCOPE::to_double(rt.X()),
             CGAL_LEDA_SCOPE::to_double(rt.Y()),
             CGAL_LEDA_SCOPE::to_double(rt.W())) );
  }
};

struct Cartesian_float_to_H_double_int
{
  typedef Point_2< Homogeneous< double> >    Point2;
  typedef Segment_2< Homogeneous< double> >  Segment;

  Segment
  operator()(  const Segment_2< Cartesian< float> >& s) const
  {
    leda_rat_point rs =  leda_point(s.source().x(), s.source().y());
    leda_rat_point rt =  leda_point(s.target().x(), s.target().y());

    return Segment(
      Point2(CGAL_LEDA_SCOPE::to_double(rs.X()),
             CGAL_LEDA_SCOPE::to_double(rs.Y()),
             CGAL_LEDA_SCOPE::to_double(rs.W())),
      Point2(CGAL_LEDA_SCOPE::to_double(rt.X()),
             CGAL_LEDA_SCOPE::to_double(rt.Y()),
             CGAL_LEDA_SCOPE::to_double(rt.W())) );
  }
};
#endif // CGAL_USE_LEDA

CGAL_END_NAMESPACE

#endif // CGAL_KERNEL_TO_KERNEL_H
