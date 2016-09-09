// Copyright (c) 2005-2006  INRIA Sophia-Antipolis (France).
// All rights reserved.
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
// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Circular_kernel_3/include/CGAL/Spherical_kernel_type_equality_wrapper.h $
// $Id: Spherical_kernel_type_equality_wrapper.h 46206 2008-10-11 20:21:08Z spion $
//
// Author(s) : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>
//             Sylvain Pion
//             Pedro Machado    <tashimir@gmail.com>
//             Julien Hazebrouck
//             Damien Leroy

#ifndef CGAL_SPHERICAL_KERNEL_TYPE_EQUALITY_WRAPPER_H
#define CGAL_SPHERICAL_KERNEL_TYPE_EQUALITY_WRAPPER_H

#include <CGAL/user_classes.h>
#include <CGAL/Kernel/Type_equality_wrapper.h>

namespace CGAL {

template < typename K_base, typename Kernel >
struct Spherical_kernel_type_equality_wrapper
  : public Type_equality_wrapper<K_base, Kernel>
{
    typedef K_base                                                                      Kernel_base;
    typedef CGAL::Circular_arc_point_3<Kernel>                                          Circular_arc_point_3;
    typedef CGAL::Circular_arc_3<Kernel>                                                Circular_arc_3;
    typedef CGAL::Line_arc_3<Kernel>                                                    Line_arc_3;
    //~ typedef CGAL::Root_of_2<typename Kernel_base::FT>  Root_of_2;
};

}

#endif // CGAL_SPHERICAL_KERNEL_TYPE_EQUALITY_WRAPPER_H
