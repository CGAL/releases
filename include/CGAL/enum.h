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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Kernel_23/include/CGAL/enum.h $
// $Id: enum.h 44129 2008-07-12 21:09:38Z spion $
// 
//
// Author(s)     : Stefan Schirra

#ifndef CGAL_ENUM_H
#define CGAL_ENUM_H

#include <CGAL/config.h>
#include <CGAL/Kernel/Same_uncertainty.h>

// If you add/change one type here, please update Is_a_predicate.h as well.

CGAL_BEGIN_NAMESPACE

enum  Sign
{
    NEGATIVE = -1, ZERO = 0, POSITIVE = 1,

    // Orientation constants:
    RIGHT_TURN = -1, LEFT_TURN = 1,

    CLOCKWISE = -1, COUNTERCLOCKWISE = 1,

    COLLINEAR = 0, COPLANAR = 0, DEGENERATE = 0,

    // Oriented_side constants:
    ON_NEGATIVE_SIDE = -1, ON_ORIENTED_BOUNDARY = 0, ON_POSITIVE_SIDE = 1,

    // Comparison_result constants:
    SMALLER = -1, EQUAL = 0, LARGER = 1
};

typedef Sign Orientation;
typedef Sign Oriented_side;
typedef Sign Comparison_result;

enum  Bounded_side
      {
        ON_UNBOUNDED_SIDE = -1,
        ON_BOUNDARY,
        ON_BOUNDED_SIDE
      };

enum  Angle
      {
	  OBTUSE = -1,
	  RIGHT,
	  ACUTE
      };


template <class T>
inline
T
opposite(const T& t)
{ return -t; }

inline
Sign
operator-(Sign o)
{ return static_cast<Sign>( - static_cast<int>(o)); }

inline
Bounded_side
opposite(Bounded_side bs)
{ return static_cast<Bounded_side>( - static_cast<int>(bs)); }

inline
Angle
opposite(Angle a)
{ return static_cast<Angle>( - static_cast<int>(a)); }

inline Sign operator* (Sign s1, Sign s2)
{
    return static_cast<Sign> (static_cast<int> (s1) * static_cast<int> (s2));
}

#ifdef CGAL_CFG_MATCHING_BUG_5

template < typename T, typename U >
inline
T enum_cast_bug(const U& u, const T*)
{ return static_cast<T>(u); }

template < typename T, typename U >
inline
typename Same_uncertainty<T,U>::type enum_cast(const U& u)
{ return enum_cast_bug(u, (const T*)0); }

#else

template < typename T, typename U >
inline
T enum_cast(const U& u)
{ return static_cast<T>(u); }

#endif

CGAL_END_NAMESPACE

#endif // CGAL_ENUM_H
