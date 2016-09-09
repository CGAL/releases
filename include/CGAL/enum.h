// Copyright (c) 1999  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Kernel_23/include/CGAL/enum.h,v $
// $Revision: 1.9 $ $Date: 2003/10/21 12:18:22 $
// $Name: current_submission $
//
// Author(s)     : Stefan Schirra

#ifndef CGAL_ENUM_H
#define CGAL_ENUM_H

// If you add/change one type here, please update Is_a_predicate.h as well.

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
