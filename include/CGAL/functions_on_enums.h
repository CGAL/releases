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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : functions_on_enums.fw
// file          : include/CGAL/functions_on_enums.h
// package       : Kernel_basic (1.2)
// revision      : 1.2
// revision_date : 12 Jun 1998 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_FUNCTIONS_ON_ENUMS_H
#define CGAL_FUNCTIONS_ON_ENUMS_H

#ifndef CGAL_ENUM_H
#include <CGAL/enum.h>
#endif // CGAL_ENUM_H

inline
CGAL_Orientation
CGAL_opposite(const CGAL_Orientation &o)
{
  return (o == CGAL_COUNTERCLOCKWISE) ?
               CGAL_CLOCKWISE :
               (o == CGAL_CLOCKWISE) ?
                     CGAL_COUNTERCLOCKWISE :
                     CGAL_COLLINEAR;
}

inline
CGAL_Oriented_side
CGAL_opposite(const CGAL_Oriented_side &os)
{
  return (os == CGAL_ON_POSITIVE_SIDE) ?
                CGAL_ON_NEGATIVE_SIDE :
                (os == CGAL_ON_NEGATIVE_SIDE) ?
                      CGAL_ON_POSITIVE_SIDE :
                      CGAL_ON_ORIENTED_BOUNDARY;
}

inline
CGAL_Bounded_side
CGAL_opposite(const CGAL_Bounded_side &bs)
{
  return (bs == CGAL_ON_UNBOUNDED_SIDE) ?
                CGAL_ON_BOUNDED_SIDE :
                (bs == CGAL_ON_BOUNDED_SIDE) ?
                       CGAL_ON_UNBOUNDED_SIDE :
                       CGAL_ON_BOUNDARY;
}


#endif // CGAL_FUNCTIONS_ON_ENUMS_H
