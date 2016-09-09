// Copyright (c) 2006-2010 Inria Lorraine (France). All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Algebraic_kernel_d/include/CGAL/Algebraic_kernel_rs_gmpq_d_1.h $
// $Id: Algebraic_kernel_rs_gmpq_d_1.h 59002 2010-10-04 11:00:27Z lrineau $
//
// Author: Luis Peñaranda <luis.penaranda@loria.fr>

#ifndef CGAL_ALGEBRAIC_KERNEL_RS_GMPQ_1
#define CGAL_ALGEBRAIC_KERNEL_RS_GMPQ_1

#include <CGAL/Gmpq.h>
#include <CGAL/RS/Algebraic_kernel_rs_1.h>

namespace CGAL{

typedef Algebraic_kernel_rs_1<Gmpq>     Algebraic_kernel_rs_gmpq_d_1;

}

#endif  // CGAL_ALGEBRAIC_KERNEL_RS_GMPQ_1
