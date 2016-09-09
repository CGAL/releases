// Copyright (c) 1997-2000  Max-Planck-Institute Saarbruecken (Germany).
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
// $Source: /CVSROOT/CGAL/Packages/Nef_3/include/CGAL/Nef_3/quotient_coordinates_to_homogeneous_point.h,v $
// $Revision: 1.1.4.1 $ $Date: 2004/12/06 15:22:19 $
// $Name:  $
//
// Author(s)     : Miguel Granados <granados@mpi-sb.mpg.de>

#ifndef QUOTIENT_COORDINATES_TO_HOMOGENEOUS_POINT_H
#define QUOTIENT_COORDINATES_TO_HOMOGENEOUS_POINT_H

CGAL_BEGIN_NAMESPACE

template <typename Homogeneous>
typename Homogeneous::Point_3
quotient_coordinates_to_homogeneous_point(
				  typename Homogeneous::FT x,
				  typename Homogeneous::FT y,
				  typename Homogeneous::FT z) {
  typedef typename Homogeneous::Point_3 Point_3;
  if( (x.denominator() == y.denominator()) && 
      (x.denominator() == z.denominator())) {
    Point_3 p( x.numerator(),
	       y.numerator(),
	       z.numerator(),
	       x.denominator());
    return normalized(p);
  }
  else {
    Point_3 p( x.numerator()   * y.denominator() * z.denominator(),
	       x.denominator() * y.numerator()   * z.denominator(),
	       x.denominator() * y.denominator() * z.numerator(),
	       x.denominator() * y.denominator() * z.denominator());
    return normalized(p);
  }
}

CGAL_END_NAMESPACE

#endif // QUOTIENT_COORDINATES_TO_HOMOGENEOUS_POINT_H
