// Copyright (c) 2007-2009 Inria Lorraine (France). All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Number_types/include/CGAL/mpfr_coercion_traits.h $
// $Id: mpfr_coercion_traits.h 53126 2009-11-20 16:58:58Z penarand $
// 
// Author: Luis Pe�aranda <luis.penaranda@loria.fr>

#ifndef CGAL_MPFR_COERCION_TRAITS_H
#define CGAL_MPFR_COERCION_TRAITS_H

#ifdef CGAL_USE_MPFR

#include <CGAL/number_type_basic.h>
#include <CGAL/GMP/Gmpfr_type.h>
#include <CGAL/Coercion_traits.h>

namespace CGAL{

CGAL_DEFINE_COERCION_TRAITS_FOR_SELF(Gmpfr)

// coercion with native types
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(long        ,Gmpfr)
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(unsigned long       ,Gmpfr)
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(int         ,Gmpfr)
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(short       ,Gmpfr)
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(double      ,Gmpfr)
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(float       ,Gmpfr)
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(long double ,Gmpfr)

// coercion with gmp types
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(Gmpz        ,Gmpfr)
CGAL_DEFINE_COERCION_TRAITS_FROM_TO(Gmpq        ,Gmpfr)

}

#endif  // CGAL_USE_MPFR
#endif  // CGAL_MPFR_COERCION_TRAITS_H

// vim: tabstop=8: softtabstop=8: smarttab: shiftwidth=8: expandtab
