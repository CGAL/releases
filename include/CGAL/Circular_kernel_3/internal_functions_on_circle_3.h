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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.4-branch/Circular_kernel_3/include/CGAL/Circular_kernel_3/internal_functions_on_circle_3.h $
// $Id: internal_functions_on_circle_3.h 44381 2008-07-24 09:26:28Z pmachado $
//
// Author(s) : Monique Teillaud, Sylvain Pion, Pedro Machado, 
//             Julien Hazebrouck, Damien Leroy

// Partially supported by the IST Programme of the EU as a 
// STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_SPHERICAL_KERNEL_PREDICATES_ON_CIRCLE_3_H
#define CGAL_SPHERICAL_KERNEL_PREDICATES_ON_CIRCLE_3_H

namespace CGAL {
  namespace SphericalFunctors {
            
    template < class SK >
    typename SK::Circle_3
    construct_circle_3(const typename SK::Polynomials_for_circle_3 &eq)
    {
      typedef typename SK::Point_3 Point_3;
      typedef typename SK::Plane_3 Plane_3;
      typedef typename SK::Circle_3 Circle_3;
      typedef typename SK::Sphere_3 Sphere_3;
      typedef typename SK::FT FT;
      Sphere_3 s = construct_sphere_3<SK>(eq.first);
      Plane_3 p = construct_plane_3<SK>(eq.second);
      const FT d2 = CGAL::square(p.a()*s.center().x() + 
                                 p.b()*s.center().y() + 
                                 p.c()*s.center().z() + p.d()) /
       (CGAL::square(p.a()) + CGAL::square(p.b()) + CGAL::square(p.c()));
      // We do not accept circles with radius 0 (should we?)
      CGAL_kernel_precondition(d2 <  s.squared_radius());
      // d2 < s.squared_radius()
      Point_3 center = p.projection(s.center());
      return Circle_3(center,s.squared_radius() - d2,p);
    }

  }//SphericalFunctors
}//CGAL

#endif //CGAL_SPHERICAL_KERNEL_PREDICATES_ON_CIRCLE_3_H
