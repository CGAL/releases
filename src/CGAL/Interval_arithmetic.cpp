// Copyright (c) 1999-2004  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Number_types/src/CGAL/Interval_arithmetic.cpp $
// $Id: Interval_arithmetic.cpp 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Sylvain Pion
 
#include <CGAL/basic.h>
#include <CGAL/FPU.h>

namespace CGAL {

#ifdef CGAL_CFG_DENORMALS_COMPILE_BUG
// For compilers which bug on denormalized values at compile time.
// We generate CGAL_IA_MIN_DOUBLE at run time.
namespace {
double init_min_double()
{
    double d = 1;
    double e = 1;
    do {
	d = e;
	e = CGAL_IA_FORCE_TO_DOUBLE(e/2);
    } while (e != 0);
    return d;
}
} // anonymous namespace

namespace internal {
double minimin = init_min_double();
}
#endif

#ifdef _MSC_VER
namespace {
int dummy_symbol_for_stopping_VC_linker_warning;
} // namespace
#endif

} //namespace CGAL
