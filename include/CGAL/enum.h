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
// file          : include/CGAL/enum.h
// package       : Kernel_basic (3.90)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/07/23 17:36:52 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ENUM_H
#define CGAL_ENUM_H

CGAL_BEGIN_NAMESPACE

enum  Sign
      {
        NEGATIVE   = -1,
        ZERO,
        POSITIVE
      };

typedef Sign Orientation;

const Orientation  LEFT_TURN  = POSITIVE;
const Orientation  RIGHT_TURN = NEGATIVE;

#ifndef CGAL_NO_DEPRECATED_CODE
const Orientation  LEFTTURN   = POSITIVE;
const Orientation  RIGHTTURN  = NEGATIVE;
#endif

const Orientation  CLOCKWISE  = NEGATIVE;
const Orientation  COUNTERCLOCKWISE = POSITIVE;

const Orientation  COLLINEAR  = ZERO;
const Orientation  COPLANAR   = ZERO;
const Orientation  DEGENERATE = ZERO;

enum  Oriented_side
      {
        ON_NEGATIVE_SIDE = -1,
        ON_ORIENTED_BOUNDARY,
        ON_POSITIVE_SIDE
      };

enum  Bounded_side
      {
        ON_UNBOUNDED_SIDE = -1,
        ON_BOUNDARY,
        ON_BOUNDED_SIDE
      };

enum  Comparison_result
      {
        SMALLER   = -1,
        EQUAL,
        LARGER
      };

enum  Angle
      {
	  OBTUSE = -1,
	  RIGHT,
	  ACUTE
      };

CGAL_END_NAMESPACE

#include <CGAL/functions_on_enums.h>

#endif // CGAL_ENUM_H
