// Copyright (c) 2005-2006  INRIA Sophia-Antipolis (France).
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
// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Algebraic_kernel_for_spheres/include/CGAL/global_functions_on_root_for_sphere_2_3.h $
// $Id: global_functions_on_root_for_sphere_2_3.h 56667 2010-06-09 07:37:13Z sloriot $
//
// Author(s) : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>
//             Sylvain Pion
//             Pedro Machado
//             Julien Hazebrouck
//             Damien Leroy

#ifndef CGAL_ALGEBRAIC_KERNEL_GLOBAL_FUNCTIONS_ON_ROOT_FOR_SPHERE_2_3_H
#define CGAL_ALGEBRAIC_KERNEL_GLOBAL_FUNCTIONS_ON_ROOT_FOR_SPHERE_2_3_H

namespace CGAL {

template < class AK >
inline 
Comparison_result 
compare_x(const typename AK::Root_for_spheres_2_3& r1,
	   const typename AK::Root_for_spheres_2_3& r2)
{ return AK().compare_x_object()(r1, r2); }

template < class AK >
inline 
Comparison_result 
compare_y(const typename AK::Root_for_spheres_2_3& r1,
	   const typename AK::Root_for_spheres_2_3& r2)
{ return AK().compare_y_object()(r1, r2); }

template < class AK >
inline 
Comparison_result 
compare_z(const typename AK::Root_for_spheres_2_3& r1,
	     const typename AK::Root_for_spheres_2_3& r2)
{ return AK().compare_z_object()(r1, r2); }

template < class AK >
inline 
Comparison_result 
compare_xy(const typename AK::Root_for_spheres_2_3& r1,
	     const typename AK::Root_for_spheres_2_3& r2)
{ return AK().compare_xy_object()(r1, r2); }

template < class AK >
inline 
Comparison_result 
compare_xyz(const typename AK::Root_for_spheres_2_3& r1,
	     const typename AK::Root_for_spheres_2_3& r2)
{ return AK().compare_xyz_object()(r1, r2); }

} //namespace CGAL

#endif //CGAL_ALGEBRAIC_KERNEL_GLOBAL_FUNCTIONS_ON_ROOT_FOR_SPHERE_2_3_H
