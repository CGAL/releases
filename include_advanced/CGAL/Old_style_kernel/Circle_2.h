// ============================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : web_2/advanced_2.fw
// file          : include/CGAL/Old_style_kernel/Circle_2.h
// revision      : 3.2
// revision_date : 06 Apr 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_OLD_STYLE_KERNEL_CIRCLE_2_H
#define CGAL_OLD_STYLE_KERNEL_CIRCLE_2_H

namespace CGAL {

template <class R_>
class Circle_2< R_, Old_style_tag> : public R_::Circle_2_base
{
 public:
  typedef  R_                        R;
  typedef typename R::RT             RT;
  typedef typename R::FT             FT;
  typedef typename R::Point_2_base   RPoint_2;
  typedef typename R::Circle_2_base  RCircle_2;

    Circle_2() : RCircle_2() {}
    Circle_2(const RCircle_2& t) : RCircle_2(t) {}
    Circle_2(const RPoint_2& center,
             const FT &squared_radius,
             const Orientation &orientation)
      : RCircle_2(center, squared_radius, orientation) {}
    Circle_2(const RPoint_2 &center,
             const FT &squared_radius)
      : RCircle_2(center, squared_radius, COUNTERCLOCKWISE) {}
    Circle_2(const RPoint_2& p,
             const RPoint_2& q,
             const RPoint_2& r)
      : RCircle_2(p,q,r) {}
    Circle_2(const RPoint_2& p,
             const RPoint_2& q,
             const Orientation &orientation)
      : RCircle_2(p,q,orientation) {}
    Circle_2(const RPoint_2& p,
             const RPoint_2& q)
      : RCircle_2(p,q,COUNTERCLOCKWISE) {}
    Circle_2(const RPoint_2& center,
             const Orientation& orientation)
      : RCircle_2(center,FT(0),orientation) {}
    Circle_2(const RPoint_2& center)
      : RCircle_2(center,FT(0),COUNTERCLOCKWISE) {}
};

} // namespace CGAL
#endif // CGAL_OLD_STYLE_KERNEL_CIRCLE_2_H
