// ======================================================================
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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Cartesian/Segment_d.h
// package       : Cd (1.1.1)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1999/12/07 18:53:26 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_SEGMENT_D_H
#define CGAL_CARTESIAN_SEGMENT_D_H

#include <CGAL/Cartesian/redefine_names_d.h>
#include <CGAL/Twotuple.h>

CGAL_BEGIN_NAMESPACE

template < class _R >
class SegmentCd
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
// This is a partial specialization
<_R,Cartesian_tag>
#endif
  : public Handle
{
public:
  typedef _R                               R;
  typedef typename R::FT                   FT;
  typedef typename R::RT                   RT;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef SegmentCd<R CGAL_CTAG>           Self;
  typedef typename R::Point_d              Point_d;
  typedef typename R::Direction_d          Direction_d;
  typedef typename R::Line_d               Line_d;
  typedef typename R::Aff_transformation_d Aff_transformation_d;
#else
  typedef SegmentCd<R>                          Self;
  typedef typename R::Point_d_base              Point_d;
  typedef typename R::Direction_d_base          Direction_d;
  typedef typename R::Line_d_base               Line_d;
  typedef typename R::Aff_transformation_d_base Aff_transformation_d;
#endif

  SegmentCd();
  SegmentCd(const Self  &s);
  SegmentCd(const Point_d &sp, const Point_d &ep);
  ~SegmentCd();

  Self        &operator=(const Self &s);

  bool        has_on(const Point_d &p) const;
  bool        collinear_has_on(const Point_d &p) const;

  bool        operator==(const Self &s) const;
  bool        operator!=(const Self &s) const;
  long        id() const;

  Point_d     start() const;
  Point_d     end() const;

  Point_d     source() const;
  Point_d     target() const;

  Point_d     min() const;
  Point_d     max() const;
  Point_d     vertex(int i) const;
  Point_d     point(int i) const;
  Point_d     operator[](int i) const;

  FT          squared_length() const;

  Direction_d direction() const;
  Line_d      supporting_line() const;
  Self        opposite() const;
  Self        transform(const Aff_transformation_d &t) const;

  bool        is_degenerate() const;
  // Bbox_d      bbox() const;

private:
  _Twotuple< Point_d >*   ptr() const;
};

CGAL_END_NAMESPACE

#ifndef CGAL_CARTESIAN_CLASS_DEFINED
#include <CGAL/Cartesian/Segment_d.C>
#endif 

#endif // CGAL_CARTESIAN_SEGMENT_D_C
