// Copyright (c) 2006 Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Arrangement_on_surface_2/include/CGAL/Arr_enums.h $
// $Id: Arr_enums.h 53356 2009-12-09 09:53:05Z lrineau $
// 
//
// Author(s): Ron Wein          <wein@post.tau.ac.il>
//            Efi Fogel         <efif@post.tau.ac.il>

#ifndef CGAL_ARR_ENUM_H
#define CGAL_ARR_ENUM_H

/*! \file
 * Definition of the enumeration types for the arrangement package.
 */

#include <CGAL/enum.h>

CGAL_BEGIN_NAMESPACE

/*! \enum
 * Selection of a curve end.
 */
enum Arr_curve_end
{
  ARR_MIN_END,
  ARR_MAX_END
};

//! \brief prints curve end (for debugging)
template< class OutputStream >
inline
OutputStream& operator<<(
        OutputStream& os,
        const Arr_curve_end& ce) {
    
    switch(ce) {
    case CGAL::ARR_MIN_END:
        os << "ARR_MIN_END";
        break;
    case CGAL::ARR_MAX_END:
        os << "ARR_MAX_END";
        break;
    default:
        CGAL_error_msg("bogus curve end");
    }
    return os;
}


/*! \enum
 * Indicator whether a halfedge is directed from left to right (from the
 * xy-lexicographically smaller vertex to the larger one), or from right to
 * left.
 */
enum Arr_halfedge_direction
{
  ARR_LEFT_TO_RIGHT = -1,
  ARR_RIGHT_TO_LEFT = 1
};

//! \brief prints halfedge direction (for debugging)
template< class OutputStream >
inline
OutputStream& operator<<(
        OutputStream& os,
        const Arr_halfedge_direction& dir) {
    
    switch(dir) {
    case CGAL::ARR_LEFT_TO_RIGHT:
        os << "ARR_LEFT_TO_RIGHT";
        break;
    case CGAL::ARR_RIGHT_TO_LEFT:
        os << "ARR_RIGHT_TO_LEFT";
        break;
    default:
        CGAL_error_msg("bogus halfedge direction");
    }
    return os;
}

/*! \enum The various surface boundary types.
 * For example:
 * - The plain has unbounded boundaries.
 * - The sphere has 2 contraction points and one identification curve.
 */
enum Arr_boundary_type {
  ARR_OBLIVIOUS = 0,
  ARR_OPEN,
  ARR_CLOSED,
  ARR_CONTRACTION,
  ARR_IDENTIFICATION
};

//! \brief prints boundary type (for debugging)
template< class OutputStream >
inline
OutputStream& operator<<(
        OutputStream& os,
        const Arr_boundary_type& bt) {
    
    switch(bt) {
    case CGAL::ARR_OPEN:
        os << "ARR_OPEN";
        break;
    case CGAL::ARR_CLOSED:
        os << "ARR_CLOSED";
        break;
    case CGAL::ARR_CONTRACTION:
        os << "ARR_CONTRACTION";
        break;
    case CGAL::ARR_IDENTIFICATION:
        os << "ARR_IDENTIFICATION";
        break;
    case CGAL::ARR_OBLIVIOUS:
        os << "ARR_OBLIVIOUS";
        break;
    default:
        CGAL_error_msg("bogus boundary type");
    }
    return os;
}


/*! \enum The various surface parameter space options categorizing the
 * surface range according to the parameter domain.
 */
enum Arr_parameter_space {
  ARR_LEFT_BOUNDARY = 0,
  ARR_RIGHT_BOUNDARY,
  ARR_BOTTOM_BOUNDARY,
  ARR_TOP_BOUNDARY,
  ARR_INTERIOR
};


//! \brief prints parameter space (for debugging)
template< class OutputStream >
inline
OutputStream& operator<<(
        OutputStream& os,
        const Arr_parameter_space& ps) {
    
    switch(ps) {
    case CGAL::ARR_LEFT_BOUNDARY:
        os << "ARR_LEFT_BOUNDARY";
        break;
    case CGAL::ARR_RIGHT_BOUNDARY:
        os << "ARR_RIGHT_BOUNDARY";
        break;
    case CGAL::ARR_BOTTOM_BOUNDARY:
        os << "ARR_BOTTOM_BOUNDARY";
        break;
    case CGAL::ARR_TOP_BOUNDARY:
        os << "ARR_TOP_BOUNDARY";
        break;
    case CGAL::ARR_INTERIOR:
        os << "ARR_INTERIOR";
        break;
    default:
        CGAL_error_msg("bogus parameter space");
    }
    return os;
}


CGAL_END_NAMESPACE

#endif

