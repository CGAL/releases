// Copyright (c) 2005  Stanford University (USA).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Kinetic_data_structures/include/CGAL/Polynomial/CORE_kernel.h $
// $Id: CORE_kernel.h 39016 2007-06-11 00:08:13Z drussel $ $Date: 2007-06-11 02:08:13 +0200 (Mon, 11 Jun 2007) $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_POLYNOMIAL_POLYNOMIAL_CORE_KERNEL_H
#define CGAL_POLYNOMIAL_POLYNOMIAL_CORE_KERNEL_H
#include <CGAL/Polynomial/basic.h>
#include <CGAL/CORE_Expr.h>
#include <CGAL/Polynomial/Kernel.h>
#include <CGAL/Polynomial/internal/CORE_polynomial.h>
#include <CGAL/Polynomial/CORE_Expr_root_stack.h>

CGAL_POLYNOMIAL_BEGIN_NAMESPACE



// CORE_Expr_root_stack::FT
class CORE_kernel: public Kernel<internal::CORE_polynomial, CORE_Expr_root_stack,
				 CORE::Expr >
{
  typedef CORE_kernel This;
  typedef Kernel<internal::CORE_polynomial, CORE_Expr_root_stack, CORE::Expr> P;
public:

  CORE_kernel(const CORE_Expr_root_stack::Traits &tr=CORE_Expr_root_stack::Traits()):
    P(tr){}

};

CGAL_POLYNOMIAL_END_NAMESPACE
#endif
