// Copyright (c) 1997-2007  ETH Zurich (Switzerland).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/QP_solver/include/CGAL/QP_solver/Unbounded_direction.h $
// $Id: Unbounded_direction.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Sven Schoenherr
//                 Bernd Gaertner <gaertner@inf.ethz.ch>
//                 Franz Wessendorp
//                 Kaspar Fischer

#ifndef CGAL_QP_SOLVER_UNBOUNDED_DIRECTION_H
#define CGAL_QP_SOLVER_UNBOUNDED_DIRECTION_H

namespace CGAL {
template < typename Q, typename ET, typename Tags >
ET QP_solver<Q, ET, Tags>::unbounded_direction_value(int i) const
{
 if (is_basic(i)) {                  // basic variable?
   return direction == 1 ? -q_x_O[in_B[i]] : q_x_O[in_B[i]];
 } else {                            // non-basic variable?
   if (i == j)                       // most recent entering variable?
     return direction == 1 ? d : -d;
   return et0;
 }
}
} //namespace CGAL

#endif // CGAL_QP_SOLVER_UNBOUNDED_DIRECTION_H

// ===== EOF ==================================================================
