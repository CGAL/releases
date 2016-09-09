// Copyright (c) 1997  INRIA Sophia-Antipolis (France).
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
// $Source: /CVSROOT/CGAL/Packages/Alpha_shapes_3/include/CGAL/smallest_radius_3.h,v $
// $Revision: 1.5 $ $Date: 2003/09/18 10:19:16 $
// $Name: current_submission $
//
// Author(s)     : Tran Kai Frank DA

#ifndef CGAL_SMALLEST_RADIUS_3_H
#define CGAL_SMALLEST_RADIUS_3_H

#include <CGAL/Point_3.h>

CGAL_BEGIN_NAMESPACE

template <class R >
CGAL_KERNEL_MEDIUM_INLINE
typename R::FT
squared_radius_smallest_circumsphere(const Point_3<R> &p,
				     const Point_3<R> &q)
{
  Vector_3<R> v(p - q);
  return typename R::FT ((v*v)/R::FT(4));
}

CGAL_END_NAMESPACE

#endif // CGAL_SMALLEST_RADIUS_3_H
