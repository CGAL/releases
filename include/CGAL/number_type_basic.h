// Copyright (c) 1999,2007  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Number_types/include/CGAL/number_type_basic.h $
// $Id: number_type_basic.h 44867 2008-08-11 12:31:35Z spion $
//
//
// Author(s)     : Stefan Schirra, Michael Hemmer


#ifndef CGAL_NUMBER_TYPE_BASIC_H
#define CGAL_NUMBER_TYPE_BASIC_H

#define CGAL_PI 3.14159265358979323846


#ifdef CGAL_USE_NTS_NAMESPACE

#define CGAL_NTS_BEGIN_NAMESPACE namespace NTS {
#define CGAL_NTS_END_NAMESPACE }
#define CGAL_NTS ::CGAL::NTS::

#else

#define CGAL_NTS_BEGIN_NAMESPACE
#define CGAL_NTS_END_NAMESPACE
#define CGAL_NTS ::CGAL::

#endif

#include <CGAL/basic.h>

// basic tools needed in several files
#include <boost/type_traits/is_same.hpp>
#include <functional>

#include <CGAL/Kernel/mpl.h>      // First_if_different
#include <CGAL/known_bit_size_integers.h>
#include <CGAL/enum.h>            // CGAL::Sign etc.
#include <CGAL/tags.h>            // Tag_true / Tag_false

#include <CGAL/Coercion_traits.h>
#include <CGAL/Algebraic_structure_traits.h>
#include <CGAL/Real_embeddable_traits.h>

#include <CGAL/Fraction_traits.h>
#include <CGAL/Rational_traits.h>

#include <CGAL/Scalar_factor_traits.h>       // not part of CGAL 3.3
#include <CGAL/Algebraic_extension_traits.h> // not part of CGAL 3.3 

#include <CGAL/Needs_parens_as_product.h>

#include <CGAL/utils_classes.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>
#include <CGAL/number_utils_classes.h>

#include <CGAL/FPU.h>

#include <CGAL/float.h>
#include <CGAL/double.h>
#include <CGAL/long_double.h>
#include <CGAL/int.h>

#include <CGAL/Interval_nt.h> // needed by To_interval(long double)
#ifdef CGAL_USE_LONG_LONG
#include <CGAL/long_long.h>
#endif

#include <CGAL/Root_of_traits.h>


#ifdef CGAL_USE_GMP
#ifdef CGAL_USE_GMPXX
#include <CGAL/gmpxx.h>
#endif // CGAL_USE_GMPXX
#endif // CGAL_USE_GMP

#endif // CGAL_NUMBER_TYPE_BASIC_H
