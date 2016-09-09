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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kinetic_data_structures/include/CGAL/Kinetic/basic.h $
// $Id: basic.h 56668 2010-06-09 08:45:58Z sloriot $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_KINETIC_BASIC_H
#define CGAL_KINETIC_BASIC_H

/*!
  \file CGAL/Kinetic/basic.h The header which defines the standard things for the KDS namespace and module.

  \todo cgal documentation

  \namespace CGAL The CGAL project namespace

  \namespace CGAL::KDS The namespace for classes which involve the Kinetic Data Structures framework.

*/

#include <CGAL/basic.h>

#include <CGAL/Kinetic/internal/config.h>

#ifdef CGAL_CHECK_EXPENSIVE
#ifndef CGAL_KINETIC_CHECK_EXPENSIVE
#define CGAL_KINETIC_CHECK_EXPENSIVE
#endif
#endif

#ifdef CGAL_CHECK_EXACTNESS
#ifndef CGAL_KINETIC_CHECK_EXACTNESS
#define CGAL_KINETIC_CHECK_EXACTNESS
#endif
#endif


#ifdef CGAL_USE_GMP
#include <CGAL/Gmpq.h>
namespace CGAL { namespace Kinetic {
typedef CGAL::Gmpq Default_field_nt;
} } //namespace CGAL::Kinetic
#else
#include <CGAL/MP_Float.h>
namespace CGAL { namespace Kinetic {
typedef CGAL::MP_Float Default_field_nt;
} } //namespace CGAL::Kinetic
#endif

namespace CGAL { namespace Kinetic {

} } //namespace CGAL::Kinetic

#include <CGAL/Tools/Log.h>


#include <CGAL/Tools/utility_macros.h>

#endif
