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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Algebraic_kernel_for_spheres/include/CGAL/global_functions_on_roots_and_polynomials_1_3.h $
// $Id: global_functions_on_roots_and_polynomials_1_3.h 46224 2008-10-13 11:22:46Z pmachado $
//
// Author(s) : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>
//             Sylvain Pion
//             Pedro Machado
//             Julien Hazebrouck
//             Damien Leroy

#ifndef CGAL_CURVED_KERNEL_GLOBAL_FUNCTIONS_ON_ROOTS_AND_POLYNOMIALS_1_3_H
#define CGAL_CURVED_KERNEL_GLOBAL_FUNCTIONS_ON_ROOTS_AND_POLYNOMIALS_1_3_H

CGAL_BEGIN_NAMESPACE

template < class AK >
inline 
typename AK::Polynomial_1_3
construct_polynomial_1_3(const typename AK::FT& a,
			 const typename AK::FT& b,
			 const typename AK::FT& c,
			 const typename AK::FT& d)
{ return AK().construct_polynomial_1_3_object()(a, b, c, d); }

template < class AK >
inline 
typename AK::Polynomials_for_line_3
construct_polynomials_for_line_3(const typename AK::FT& a1,
			         const typename AK::FT& b1,
			         const typename AK::FT& a2,
			         const typename AK::FT& b2,
                                 const typename AK::FT& a3,
			         const typename AK::FT& b3)
{ return AK().construct_polynomials_for_line_3_object()(a1, b1, a2, b2, a3, b3); }

CGAL_END_NAMESPACE

#endif // CGAL_CURVED_KERNEL_GLOBAL_FUNCTIONS_ON_ROOTS_AND_POLYNOMIALS_1_3_H
