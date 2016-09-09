// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Circle_repC2.h
// package       : C2 (1.7)
// source        : web/CircleC2.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1999/01/04 06:54:12 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL__CIRCLEC2_H
#define CGAL__CIRCLEC2_H

template < class T >
class CGAL__CircleC2 : public CGAL_Rep
{
public:

  CGAL_PointC2<T>  center;
  T  squared_radius;
  CGAL_Orientation orientation;


  CGAL__CircleC2()
    {}

  CGAL__CircleC2(const CGAL_PointC2<T> & c,
                 const T & r,
                 const CGAL_Orientation &o)
    : center(c), squared_radius(r), orientation(o)
    {}

  ~CGAL__CircleC2()
    {}
};
#endif  // CGAL__CIRCLEC2_H
