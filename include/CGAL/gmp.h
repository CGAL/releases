// Copyright (c) 2010 GeometryFactory (France). All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Number_types/include/CGAL/gmp.h $
// $Id: gmp.h 56920 2010-06-21 13:36:47Z afabri $
// 
// Author: Andreas Fabri

#ifndef CGAL_GMP_H
#define CGAL_GMP_H 1

#include <CGAL/config.h>

#if defined(BOOST_MSVC)
#  pragma warning(push)
#  pragma warning(disable:4244 4146) // conversion with loss of data
                                     // warning on - applied on unsigned number
#endif

#include <gmp.h>


#if defined(BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif // CGAL_GMP_H
