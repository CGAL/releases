// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Circle_repC2.h
// package       : C2 (2.1.4)
// source        : web/CircleC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:31 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL__CIRCLEC2_H
#define CGAL__CIRCLEC2_H

#ifndef CGAL_BASIC_CONSTRUCTIONSC2_H
#include <CGAL/basic_constructionsC2.h>
#endif // CGAL_BASIC_CONSTRUCTIONSC2_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class _CircleC2 : public Rep
{
public:

  PointC2<FT>  center;
  FT  squared_radius;
  Orientation orient;


  _CircleC2()
    {}

  _CircleC2(const PointC2<FT> & c,
                 const FT & r,
                 const Orientation &o)
    : center(c), squared_radius(r), orient(o)
    {}

  ~_CircleC2()
    {}
};

CGAL_END_NAMESPACE

#endif  // CGAL__CIRCLEC2_H
