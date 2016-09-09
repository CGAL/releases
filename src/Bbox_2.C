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
// source        : Bbox_2.fw
// file          : src/Bbox_2.C
// package       : _2 (1.3)
// revision      : 1.3
// revision_date : 15 Dec 1998 
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_BBOX_2_H
#include <CGAL/Bbox_2.h>
#endif // CGAL_BBOX_2_H

CGAL_Bbox_2::CGAL_Bbox_2()
{
  PTR = new CGAL__Fourtuple<double>();
}

CGAL_Bbox_2::CGAL_Bbox_2(const CGAL_Bbox_2 &b) :
  CGAL_Handle(b)
{}

CGAL_Bbox_2::CGAL_Bbox_2(double x_min, double y_min,
                         double x_max, double y_max)
{
  PTR = new CGAL__Fourtuple<double>(x_min, y_min, x_max, y_max);
}

CGAL_Bbox_2::~CGAL_Bbox_2()
{}

CGAL_Bbox_2 &CGAL_Bbox_2::operator=(const CGAL_Bbox_2 &b)
{
  CGAL_Handle::operator=(b);
  return *this;
}
bool CGAL_Bbox_2::operator==(const CGAL_Bbox_2 &b) const
{
  return xmin() == b.xmin() && xmax() == b.xmax()
         && ymin() == b.ymin() && ymax() == b.ymax();
}

bool CGAL_Bbox_2::operator!=(const CGAL_Bbox_2 &b) const
{
  return ! (b == *this);
}

