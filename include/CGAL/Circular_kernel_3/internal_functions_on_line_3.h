// Copyright (c) 2008  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Circular_kernel_3/include/CGAL/Circular_kernel_3/internal_functions_on_line_3.h $
// $Id: internal_functions_on_line_3.h 44381 2008-07-24 09:26:28Z pmachado $
//
// Author(s) : Monique Teillaud, Sylvain Pion, Pedro Machado

// Partially supported by the IST Programme of the EU as a 
// STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_SPHERICAL_KERNEL_PREDICATES_ON_LINE_3_H
#define CGAL_SPHERICAL_KERNEL_PREDICATES_ON_LINE_3_H

namespace CGAL {
  namespace SphericalFunctors {

    template < class SK >
    typename SK::Line_3
    construct_line_3(const typename SK::Polynomials_for_line_3 &eq)
    {
      typedef typename SK::Line_3 Line_3;
      typedef typename SK::Point_3 Point_3;
      typedef typename SK::Vector_3 Vector_3;
      return Line_3(Point_3(eq.b1(),eq.b2(),eq.b3()),
                    Vector_3(eq.a1(),eq.a2(),eq.a3()));
    }

  }//SphericalFunctors
}//CGAL

#endif //CGAL_SPHERICAL_KERNEL_PREDICATES_ON_LINE_3_H
